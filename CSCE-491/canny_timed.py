import cv2
import glob
import numpy as np
import time

images = glob.glob('*.png')
times = [0] * 117
count = 0
for image_file in images:
	#count = count + 1
	t0 = time.time_ns()
	# Read the original image
	img = cv2.imread(image_file) 
	# Display original image
	cv2.imshow('Original', img)
	#cv2.waitKey(1)

	# Convert to graycsale
	img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	# Blur the image for better edge detection
	img_blur = cv2.GaussianBlur(img_gray, (3,3), 0) 
	cv2.imshow('Blurred', img_blur)
	cv2.waitKey(1)

	# Canny Edge Detection
	edges = cv2.Canny(image=img_blur, threshold1=100, threshold2=200) # Canny Edge Detection
	# Display Canny Edge Detection Image
	cv2.imshow('Canny Edge Detection', edges)
	cv2.waitKey(1)
	
	cv2.destroyAllWindows()
		
	# Create the output file name by removing the '.png' part
	size = len(image_file)
	new_filename = image_file[:size - 4]
	new_filename = "Canny/"+new_filename + "_Canny.png"
	     
	# Save the Canny image
	cv2.imwrite(new_filename, edges)
	
	t1 = time.time_ns()
	times[count] = t1 - t0
	count = count + 1
#print(count)

average = 0
for time in times:
	average += time
average = average / len(times)
print("Average in nanoseconds:", average)
print("Average in seconds:", average/(10**9))
