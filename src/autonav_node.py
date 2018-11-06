#!/usr/bin/env python
from __future__ import division
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge
import numpy as np
import random
import threading

class AutonavNode(object):

	def __init__(self):
		self.min_distance = 600 #millimeters
		#self.speed = rospy.get_param("mmm/leftWheelSpeed/max")/2
		self.avoiding = False
		self.threading= False
		rospy.init_node("autonav_node")
		self.cv_bridge = CvBridge()
		print("Estamos funcionando")
		# Create subscriber for Kinect images
		self.sub = rospy.Subscriber("camera/depth_registered/image_raw", Image, self.process_depth_image)
		# Create publisher for movement commands
		self.pub = rospy.Publisher("/RosAria/cmd_vel", Twist, queue_size=1)
		# Allow MMM node to start
		rospy.sleep(4)
		# Start moving forward initially
		msg=Twist()
		msg.linear.x=0.08
		self.pub.publish(msg)
		print("Hemos publicado")
		rospy.spin()
		
	def process_depth_image(self, msg):
		#threading.Thread(target=self.process_publisher).start()
		im = self.cv_bridge.imgmsg_to_cv2(msg)
		min_point = im[im.nonzero()].min()
		print(min_point)
		if min_point < self.min_distance:
			if not self.avoiding:
				threading.Thread(target=self.avoid_obstacle).start()
		else:
			self.avoiding = False
			threading.Thread(target=self.process_publisher).start()
	
	def avoid_obstacle(self):
		print("AVOIDING")
		self.avoiding = True
		msg= Twist()
		while self.avoiding:
			rospy.sleep(1/30)
			msg.linear.x=0.0
			msg.angular.z=0.3
			self.pub.publish(msg)
		print("DONE AVOIDING")
	
	def process_publisher(self):
		self.pub = rospy.Publisher("/RosAria/cmd_vel", Twist, queue_size=1)
		msg=Twist()
		msg.linear.x=0.08
		self.pub.publish(msg)
		
		
if __name__ == '__main__':
	autonav_node = AutonavNode()	
	
	
	
	
	
	
	
