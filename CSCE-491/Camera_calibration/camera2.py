 #https://automaticaddison.com
# Description: Perform camera calibration using a chessboard.
 
import cv2 # Import the OpenCV library to enable computer vision
import numpy as np # Import the NumPy scientific computing library
import glob # Used to get retrieve files that have a specified pattern
 
# Path to the image that you want to undistort
distorted_img_filename = 'WIN_20211013_09_05_14_Pro.jpg'
 
# Chessboard dimensions
number_of_squares_X = 9	   # Number of chessboard squares along the x-axis
number_of_squares_Y = 7  # Number of chessboard squares along the y-axis
nX = number_of_squares_X - 1 # Number of interior corners along x-axis
nY = number_of_squares_Y - 1 # Number of interior corners along y-axis
 
# Store vectors of 3D points for all chessboard images (world coordinate frame)
object_points = []
 
# Store vectors of 2D points for all chessboard images (camera coordinate frame)
image_points = []
 
# Set termination criteria. We stop either when an accuracy is reached or when
# we have finished a certain number of iterations.
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30 , 0.001)
 
# Define real world coordinates for points in the 3D coordinate frame
# Object points are (0,0,0), (1,0,0), (2,0,0) ...., (5,8,0)
object_points_3D = np.zeros((nX * nY, 3), np.float32)       
 
# These are the x and y coordinates                                              
object_points_3D[:,:2] = np.mgrid[0:nY, 0:nX].T.reshape(-1, 2) 
 
def main():
     
  # Get the file path for images in the current directory
  images = glob.glob('*.jpg')

     
  # Go through each chessboard image, one by one
  for image_file in images:
  
    # Load the image
    
    image = cv2.imread(image_file)
    imageres = image
    #imageres = cv2.resize(image, (1280,800))  
 
    # Convert the image to grayscale
    gray = cv2.cvtColor(imageres, cv2.COLOR_BGR2GRAY)  
 
    # Find the corners on the chessboard
    success, corners = cv2.findChessboardCorners(gray, (nY, nX), None)
     
    # If the corners are found by the algorithm, draw them
    if success == True:
 
      # Append object points
      object_points.append(object_points_3D)
 
      # Find more exact corner pixels       
      corners_2 = cv2.cornerSubPix(gray, corners, (11,11), (-1,-1), criteria)       
       
            # Append image points
      image_points.append(corners)
 
      # Draw the corners
      cv2.drawChessboardCorners(imageres, (nY, nX), corners_2, success)
 
      # Display the image. Used for testing.
      cv2.imshow("Image", imageres) 
     
      # Display the window for a short period. Used for testing.
      cv2.waitKey(200) 
                                                                                                                     
  # Now take a distorted image and undistort it 
  distorted_image = cv2.imread(distorted_img_filename)

 
  # Perform camera calibration to return the camera matrix, distortion coefficients, rotation and translation vectors etc 
  success, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(object_points, 
                                                    image_points, 
                                                    (1280,720), 
                                                    None, 
                                                    None)
 
  # Get the dimensions of the image 
  height, width = distorted_image.shape[:2]
     
  # Refine camera matrix
  # Returns optimal camera matrix and a rectangular region of interest
  optimal_camera_matrix, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, 
                                                            (width,height), 
                                                            1, 
                                                            (width,height))
 
  # Undistort the image
  undistorted_image = cv2.undistort(distorted_image, mtx, dist, None, 
                                    optimal_camera_matrix)
   
  # Crop the image. Uncomment these two lines to remove black lines
  # on the edge of the undistorted image.
  #x, y, w, h = roi
  #undistorted_image = undistorted_image[y:y+h, x:x+w]
     
  # Display key parameter outputs of the camera calibration process
  print("Optimal Camera matrix:") 
  print(optimal_camera_matrix) 
 
  print("\n Distortion coefficient:") 
  print(dist) 
   
  print("\n Rotation Vectors:") 
  print(rvecs) 
   
  print("\n Translation Vectors:") 
  print(tvecs) 
 
  # Create the output file name by removing the '.jpg' part
  size = len(distorted_img_filename)
  new_filename = distorted_img_filename[:size - 4]
  new_filename = new_filename + '_undistorted.jpg'
     
  # Save the undistorted image
  cv2.imwrite(new_filename, undistorted_image)
 
  # Close all windows
  cv2.destroyAllWindows() 
  
#Reprojection error calculation 
  mean_error = 0
  objpoints = object_points
  imgpoints = image_points
  
  #for each of the 3D points do the following:
  for i in range(len(objpoints)):
    #project the 3D points to an image plane
    imgpoints2, _ = cv2.projectPoints(objpoints[i], rvecs[i], tvecs[i], mtx, dist)
    print("Image points are \n")
    print(imgpoints)
    #calculate the distance between the points in the original image and the reprojected image
    error = cv2.norm(imgpoints[i], imgpoints2, cv2.NORM_L2)/len(imgpoints2)
    #add up the errors
    mean_error += error
   
  #calculate and print the total error  
  print( "total error: {}".format(mean_error/len(objpoints)) )
  
  
  # path
  path = distorted_img_filename
   
# Reading an image in default mode
  image = cv2.imread(path)
   
# Window name in which image is displayed
  window_name = 'Image'
  
# Center coordinates
  center_coordinates = (348, 459)
 
# Radius of circle
  radius = 20
  
# Blue color in BGR
  color = (255, 0, 0)
  
# Line thickness of 2 px
  thickness = 2
  
# Using cv2.circle() method
# Draw a circle with blue line borders of thickness of 2 px
  image2 = cv2.circle(image, center_coordinates, radius, color, thickness)
  
# Displaying the image
  cv2.imshow(window_name, image)
  cv2.waitKey(20000) 
  
  
     
main()
