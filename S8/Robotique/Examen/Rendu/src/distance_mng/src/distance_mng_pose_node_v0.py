#!/usr/bin/env python
import rospy
from turtlesim.msg import Pose

# Noeud permettant d'afficher dans un terminal la position de la tortue

def PoseCallback(msg):
    rospy.loginfo("Pose de la tortue : x = %f, y = %f, theta = %f", msg.x, msg.y, msg.theta)

if __name__ == '__main__':
    rospy.init_node('distance_mng_pose_node')
    rospy.Subscriber('/turtle1/pose', Pose, PoseCallback)
    rospy.spin()

# Lancer le noeud : rosrun distance_mng distance_mng_pose_node_v0.py