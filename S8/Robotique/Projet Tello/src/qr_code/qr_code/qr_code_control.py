#!/usr/bin/env python3

import sys
import time
import cv2
import imutils
import numpy as np
import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Joy
from std_msgs.msg import Empty, String
from geometry_msgs.msg import Twist


class qr_code_control(Node):

    def __init__(self):
        super().__init__('qr_code_control')
        self.subscription = self.create_subscription(String, 'barcode', self.listener_callback, 1)
        # Publishers
        self.pubTakeoff = self.create_publisher(Empty, 'takeoff', 1)
        self.pubLand = self.create_publisher(Empty, 'land', 1)
        self.pubReset = self.create_publisher(Empty, 'emergency', 1)
        self.pubTricks = self.create_publisher(Empty, 'flip', 1)
        self.pub = self.create_publisher(Twist, 'control', 1)
        self.subscription  # prevent unused variable warning
        self.flying = False

    def listener_callback(self, msg):
        behaviour = msg.data
        self.get_logger().info('I heard: "%s"' % behaviour)

        if behaviour == "start" and not self.flying :
            # Takeoff
            self.flying = True
            self.get_logger().info("  Takeoff !!")
            self.pubTakeoff.publish(Empty())

        elif behaviour == "finish" and self.flying:
            # Land
            self.flying = False
            self.get_logger().info("  Lrospyand !!")
            self.pubLand.publish(Empty())

        elif behaviour == "red_block":
            # Follow
            pass

        elif behaviour == "blue_block":
            # Land
            cmd = Twist()
            cmd.linear.x = 0.0
            cmd.linear.y = 0.0
            cmd.linear.z = 0.0
            cmd.angular.z = 0.0
            self.get_logger().info(f" {cmd.linear.x}|{cmd.linear.y}|{cmd.linear.z} -- {cmd.angular.z}")
            self.pub.publish(cmd)

        elif behaviour == "stop":
            self.get_logger().info("  STOP !!")
            self.pubReset.publislistener_callbackh(Empty())

        else :
            self.get_logger().info('Invalid behaviour: "%s"' % behaviour)

        time.sleep(1)                

def main():

    rclpy.init()

    tello_qr = qr_code_control()
    
    rclpy.spin(tello_qr)        

if __name__ == '__main__':
    main()
