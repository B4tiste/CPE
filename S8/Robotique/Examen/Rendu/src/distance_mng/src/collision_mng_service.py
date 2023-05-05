#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from std_msgs.msg import Float32
from turtlesim.srv import TeleportAbsolute
from std_srvs.srv import SetBool, SetBoolResponse

HEIGHT = 11.0
WIDTH = 11.0
X_RESPAWN, Y_RESPAWN = WIDTH/2, HEIGHT/2
SEUIL = 0.1

# Ce noeud represente un service "config_respawn_pose" qui permet de modifier la position de respawn de la tortue et de modifier le seuil de collision

def teleport(x, y):
    teleportAbsolute = rospy.ServiceProxy('/turtle1/teleport_absolute', TeleportAbsolute)
    teleportAbsolute(x, y, 0.0)

def distanceCallback(data):
    if data.data <= SEUIL:
        rospy.loginfo("Collision !")
        teleport(X_RESPAWN, Y_RESPAWN)

def handleConfig(req):
    # Res = "x,y,seuil"

    global X_RESPAWN, Y_RESPAWN, SEUIL
    data = req.data.split(",")
    X_RESPAWN, Y_RESPAWN, SEUIL = float(data[0]), float(data[1]), float(data[2])

def confServiceServer():
    rospy.init_node('collision_mng_service')
    rospy.Subscriber('/distance_minimale', Float32, distanceCallback)
    rospy.Service('config_respawn_pose', #String ?#, handleConfig)
    rospy.loginfo("Service config_respawn_pose lance")

if __name__ == '__main__':
    confServiceServer()
    rospy.spin()

# Lancer le noeud : rosrun distance_mng collision_mng_service.py