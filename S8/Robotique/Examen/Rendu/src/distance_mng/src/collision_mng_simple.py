#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from std_msgs.msg import Float32
from turtlesim.srv import TeleportAbsolute


HEIGHT = 11.0
WIDTH = 11.0
SEUIL = 0.1

# Noeud qui utilise le service /turtle1/teleport_absolute pour placer la tortue au centre de la fenetre lorsque la valeur de distance sur le topic /distance_minimal est <= 1.0

def teleport(x, y):
    teleportAbsolute = rospy.ServiceProxy('/turtle1/teleport_absolute', TeleportAbsolute)
    teleportAbsolute(x, y, 0.0)

def distanceCallback(data):
    if data.data <= SEUIL:
        rospy.loginfo("Collision !")
        teleport(WIDTH/2, HEIGHT/2)

if __name__ == '__main__':

    rospy.init_node('collision_mng_simple')
    rospy.Subscriber('/distance_minimale', Float32, distanceCallback)
    rospy.spin()

# Lancer le noeud : rosrun distance_mng collision_mng_simple.py