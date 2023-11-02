#source of information: https://medium.com/srm-mic/color-segmentation-using-opencv-93efa7ac93e2


import cv2
import glob
import numpy as np
import matplotlib.pyplot as plt



images = glob.glob('*.png')

for image_file in images:


	# Read the original image
	img = cv2.imread(image_file) 
	# Display original image
	cv2.imshow('Original', img)
	cv2.waitKey(1)

	#blur image
	blur = cv2.blur(img,(5,5))
	blur0=cv2.medianBlur(blur,5)
	blur1= cv2.GaussianBlur(blur0,(5,5),0)
	blur2= cv2.bilateralFilter(blur1,9,75,75)

	#transform image to hue saturation value
	hsv = cv2.cvtColor(blur2, cv2.COLOR_BGR2HSV)

	#range of values for all pixels we want to extract
	low_color = np.array([56, 0, 0]) #dark 12, 15, 23
	high_color = np.array([118, 255, 255]) #light 85, 96, 117]
	mask = cv2.inRange(hsv, low_color, high_color)

	res = cv2.bitwise_and(img,img, mask= mask)

	cv2.imshow('Color_SEG', res)
	cv2.waitKey(1)
	
	# Create the output file name by removing the '.png' part
	size = len(image_file)
	new_filename2 = image_file[:size - 4]
	new_filename2 = "Color_Seg/"+new_filename2 + "_Segmentation.png"
	     
	# Save the Canny image
	cv2.imwrite(new_filename2, res)



