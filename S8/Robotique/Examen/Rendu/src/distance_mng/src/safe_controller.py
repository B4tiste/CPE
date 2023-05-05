#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32

# Ce node permet de diminuer la vitesse transmise par turtle_teleop_key lorsque que la valeur se trouvant sur le topic /distance_minimale est inferieure a 1.0

def distanceCallback(data):
    if data.data <= 1.0:
        # rospy.loginfo("Collision !")
        rospy.set_param('/turtle_teleop_key/turtle_laser_linear', 0.1)
    else:
        rospy.set_param('/turtle_teleop_key/turtle_laser_linear', 1.0)

if __name__ == '__main__':
    rospy.init_node('collision_mng')
    rospy.Subscriber('/distance_minimale', Float32, distanceCallback)
    rospy.spin()

# Lancer le noeud : rosrun distance_mng safe_controller.py