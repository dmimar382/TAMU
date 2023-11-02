import cv2
import glob
import numpy as np

images = glob.glob('*.png')
count = 0
for image_file in images:
	count = count + 1

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

	# Sobel Edge Detection
	sobelx = cv2.Sobel(src=img_blur, ddepth=cv2.CV_64F, dx=1, dy=0, ksize=5) # Sobel Edge Detection on the X axis
	sobely = cv2.Sobel(src=img_blur, ddepth=cv2.CV_64F, dx=0, dy=1, ksize=5) # Sobel Edge Detection on the Y axis
	sobelxy = cv2.Sobel(src=img_blur, ddepth=cv2.CV_64F, dx=1, dy=1, ksize=5) # Combined X and Y Sobel Edge Detection
	
	# Create the output file name by removing the '.png' part
	size = len(image_file)
	new_filename2 = image_file[:size - 4]
	new_filename2 = "Sobel/"+new_filename2 + "_Sobel.png"
	     
	# Save the Canny image
	cv2.imwrite(new_filename2, sobelxy)
	
	# Display Sobel Edge Detection Images
	cv2.imshow('Sobel X', sobelx)
	cv2.waitKey(1)
	cv2.imshow('Sobel Y', sobely)
	cv2.waitKey(1)
	cv2.imshow('Sobel X Y using Sobel() function', sobelxy)
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

print(count)
