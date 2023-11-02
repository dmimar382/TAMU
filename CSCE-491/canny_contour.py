# source https://learnopencv.com/contour-detection-using-opencv-python-c/

import cv2
import glob
import numpy as np
import matplotlib.pyplot as plt



images = glob.glob('*.png')

for image_file in images:


	# Read the original image
	#img = cv2.imread(image_file)
	img = cv2.imread(image_file)  
	# Display original image
	cv2.imshow('Original', img)
	cv2.waitKey(1)

	# convert the image to grayscale format
	img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

	# apply binary thresholding
	ret, thresh = cv2.threshold(img_gray, 150, 255, cv2.THRESH_BINARY)
	# visualize the binary image
	#cv2.imshow('Binary image', thresh)
	#cv2.waitKey(0)
	#cv2.imwrite('image_thres1.jpg', thresh)
	#cv2.destroyAllWindows()

	# detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
	contours, hierarchy = cv2.findContours(image=thresh, mode=cv2.RETR_TREE, method=cv2.CHAIN_APPROX_NONE)
		                             
	# draw contours on the original image
	image_copy = img.copy()
	cv2.drawContours(image=image_copy, contours=contours, contourIdx=-1, color=(0, 255, 0), thickness=2, lineType=cv2.LINE_AA)
	
	# detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
	contours, hierarchy = cv2.findContours(image=thresh, mode=cv2.RETR_TREE, method=cv2.CHAIN_APPROX_NONE)
		                             

		       
	# see the results
	cv2.imshow('None approximation', image_copy)
	cv2.waitKey(1)
	
	# Create the output file name by removing the '.png' part
	size = len(image_file)
	new_filename = image_file[:size - 4]
	new_filename = "CannyContour/"+new_filename + "_Contour.png"
	     
	# Save the Canny image
	cv2.imwrite(new_filename, image_copy)
	
	#cv2.imwrite('contours_none_image1.jpg', image_copy)
	cv2.destroyAllWindows()

