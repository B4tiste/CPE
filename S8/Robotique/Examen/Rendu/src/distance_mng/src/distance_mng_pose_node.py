#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32
from turtlesim.msg import Pose

"""
L'origine de la fenetre de la tortue est en bas a gauche (0,0)
La fenetre fait 11x11 (valeur max : 11.0)
"""

HEIGHT = 11.0
WIDTH = 11.0

def getQuart(poseData):
    if poseData.x < WIDTH/2:
        if poseData.y < HEIGHT/2:
            return "bas gauche"
        else:
            return "haut gauche"
    else:
        if poseData.y < HEIGHT/2:
            return "bas droite"
        else:
            return "haut droite"

# Renvoi "haut", "bas", "gauche" ou "droite" en fonction de la position de la tortue pour indiquer le bord le plus proche
def nearestBorder(poseData):
    # On determine dans quel quart de la fenetre se trouve la tortue
    quart = getQuart(poseData)

    if quart == "bas gauche":
        if poseData.x < poseData.y:
            return "gauche"
        else:
            return "bas"
    elif quart == "haut gauche":
        if poseData.x < HEIGHT - poseData.y:
            return "gauche"
        else:
            return "haut"
    elif quart == "bas droite":
        if WIDTH - poseData.x < poseData.y:
            return "droite"
        else:
            return "bas"
    elif quart == "haut droite":
        if WIDTH - poseData.x < HEIGHT - poseData.y:
            return "droite"
        else:
            return "haut"
        
    

def distanceToBorder(border, poseData):
    if border == "gauche":
        return poseData.x
    elif border == "droite":
        return WIDTH - poseData.x
    elif border == "haut":
        return HEIGHT - poseData.y
    elif border == "bas":
        return poseData.y    


def PoseCallback(msg):
    
    poseData = Pose()
    poseData.x = msg.x
    poseData.y = msg.y
    poseData.theta = msg.theta

    # Bord le plus proche
    bord = nearestBorder(poseData)

    # Calcul de la distance au bord le plus proche
    distance = distanceToBorder(bord, poseData)

    # Publication de la distance sur /distance_minimale
    pub.publish(distance)


if __name__ == '__main__':
    rospy.init_node('distance_mng_pose_node')
    rospy.Subscriber('/turtle1/pose', Pose, PoseCallback)
    
    # Creer un publisher pour envoyer le distance sur /distance_minimale
    pub = rospy.Publisher('/distance_minimale', Float32, queue_size=1) # Accessible dans les fonctions de callback

    rospy.spin()

# Lancer le noeud : rosrun distance_mng distance_mng_pose_node.py