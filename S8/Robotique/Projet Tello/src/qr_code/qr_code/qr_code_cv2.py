#!/usr/bin/env python3

import sys
import time
import datetime
import cv2
import imutils
import numpy as np
import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Joy, Image
from std_msgs.msg import Empty, String, Bool
from geometry_msgs.msg import Twist
from cv_bridge import CvBridge, CvBridgeError

class qr_code_cv2(Node):

    def __init__(self):
        super().__init__('qr_code_cv2')
        self.imageSub = self.create_subscription(Image, "image_raw", self.image_callback, 1)
        self.qrSub = self.create_subscription(Bool, "qr", self.qr_callback, 1)
        self.pubTakeoff = self.create_publisher(Empty, 'takeoff', 1)
        self.pubLand = self.create_publisher(Empty, 'land', 1)
        self.pubReset = self.create_publisher(Empty, 'emergency', 1)
        self.pub = self.create_publisher(Twist, 'control', 1)
        self.bridge = CvBridge()
        self.qr_decoder = cv2.QRCodeDetector()
        self.wait = False
        self.flying = False
        self.follow_mode = False
    
    def display(self, frame, box):
        # Récupérer les coordonnées des angles en haut à gauche et en bas à droite
        pt1 = int(box[0][0][0]), int(box[0][0][1])    # angle en haut à gauche
        pt2 = int(box[0][2][0]), int(box[0][2][1])    # angle en bas à droite
        
        # Couleur du rectangle (rouge)
        color = (0, 0, 255)

        # Dessiner la diagonale du rectangle
        cv2.line(frame, pt1, pt2, color, 3)

        # Calculer les coordonnées du centre du QR code
        centre = (int((pt1[0]+pt2[0])/2), int((pt1[1]+pt2[1])/2))

        # Mettre à jour l'affichage avec la diagonale 
        cv2.imshow("Image window", frame)

        # self.get_logger().info les coordonnées du point et sa différence par rapport au centre de l'image
        height, width, channels = frame.shape
        self.get_logger().info(f"Coord : {centre} -- Diff : {centre[0]-width/2}|{centre[1]-height/2}")
    
    def position_handler(self, frame, box):

        max_diag = 175
        tresh_tolerance = 60
        self.wait = False

        # Récupérer les coordonnées des angles en haut à gauche et en bas à droite
        pt1 = int(box[0][0][0]), int(box[0][0][1])    # angle en haut à gauche
        pt2 = int(box[0][2][0]), int(box[0][2][1])    # angle en bas à droite

        # Calculer la longueur de la diagonale du QR code
        diag = np.sqrt((pt2[0]-pt1[0])**2 + (pt2[1]-pt1[1])**2)

        speed = 10 * max_diag/diag

        # Caluler les coordonnées du centre du QR code
        centre = (int((pt1[0]+pt2[0])/2), int((pt1[1]+pt2[1])/2)) # (x,y)

        height, width, channels = frame.shape
        
        cmd = Twist()

        # Init à 0 de cmd
        cmd.linear.x = 0.0
        cmd.linear.y = 0.0
        cmd.linear.z = 0.0
        cmd.angular.z = 0.0

        x, y = centre[0], centre[1]

        # Controle du drone

        # Si il est dans la zone morte (Une carre de 100px autour du centre)
        if x < width/2 + tresh_tolerance and x > width/2 - tresh_tolerance and y < height/2 + tresh_tolerance and y > height/2 - tresh_tolerance and not diag < max_diag + 25 :
            # Ne rien faire
            cmd.linear.x = 0.0
            cmd.linear.y = 0.0
            cmd.linear.z = 0.0
            cmd.angular.z = 0.0
            # INFO
            self.get_logger().info("Je ne bouge pas")

            self.wait = True

        if x > width/2 + tresh_tolerance: 
            # Se déplacer vers la droite
            cmd.linear.x = float(speed)
            # INFO
            self.get_logger().info("Je vais à gauche")

        if y < height/2 - tresh_tolerance: 
            # Se déplacer vers le haut
            cmd.linear.z = 2*float(speed)
            # INFO
            self.get_logger().info("Je vais en haut")

        if y > height/2 + tresh_tolerance: 
            # Se déplacer vers le bas
            cmd.linear.z = -2*float(speed)
            # INFO
            self.get_logger().info("Je vais en bas")
            
        if diag < max_diag + 25 :
            # S'approcher
            cmd.linear.y = float(speed)
            # INFO
            self.get_logger().info("Je m'approche")
            
        if diag > max_diag - 25:
            # Reculer
            cmd.linear.y = -float(speed)
            # INFO
            self.get_logger().info("Je recule")
        
        self.get_logger().info(f" {cmd.linear.x}|{cmd.linear.y}|{cmd.linear.z} -- {cmd.angular.z}")
        self.pub.publish(cmd)
    
    def qr_callback(self, data):
        if data.data == True:
            self.follow_mode = True
            self.get_logger().info("Follow mode : ON")
        else :
            self.follow_mode = False
            self.get_logger().info("Follow mode : OFF")
            # Fermer les fenêtres
            # cv2.destroyAllWindows()

    
    def image_callback(self, data):
        if self.follow_mode : 
            try :
                cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
            except CvBridgeError as e:
                self.get_logger().info(e)

            cv2.imshow("Image window", cv_image)

            data, qr_box, rectified_image = self.qr_decoder.detectAndDecode(cv_image)

            # Si on voit un QRcode
            if len(data) > 0 :
                self.get_logger().info(f"{datetime.datetime.now()} : {data}")

                # Vérifier le contenu du QR Code
                if data == "start" and not self.flying :
                    # Takeoff
                    self.flying = True
                    self.get_logger().info("  Takeoff !!")
                    self.pubTakeoff.publish(Empty())

                elif data == "finish" and self.flying:
                    # Land
                    self.flying = False
                    self.get_logger().info("  Land !!")
                    self.pubLand.publish(Empty())

                elif data == "BITE" or data == "red_block":
                    # Follow
                    self.display(cv_image, qr_box)
                    self.position_handler(cv_image, qr_box)
                    

                elif data == "blue_block":
                    # Land
                    cmd = Twist()
                    cmd.linear.x = 0.0
                    cmd.linear.y = 0.0
                    cmd.linear.z = 0.0
                    cmd.angular.z = 0.0
                    self.get_logger().info("  Do not move !!")
                    self.pub.publish(cmd)

                elif data == "stop":
                    self.get_logger().info("  STOP !!")
                    self.pubReset.publish(Empty())

                else :
                    self.get_logger().info('Invalid behaviour: "%s"' % data)


            else:
                cmd = Twist()
                cmd.linear.x = 0.0
                cmd.linear.y = 0.0
                cmd.linear.z = 0.0
                cmd.angular.z = 0.0
                self.pub.publish(cmd)

                pass
            
            if self.wait :
                time.sleep(2)
                self.wait = False

            cv2.waitKey(1)
        else:
            pass

def main():

    rclpy.init()

    tello_cv2_qr = qr_code_cv2()
    
    try :
        rclpy.spin(tello_cv2_qr)
    except KeyboardInterrupt:
        pass

    cv2.destroyAllWindows()      

if __name__ == '__main__':
    main()
