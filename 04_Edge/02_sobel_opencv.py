#!/usr/bin/env python
import cv2
import numpy as np 
from matplotlib import pyplot as plt


# Get the convolution value at  position (row,col)
def computeCov( img, kernel, row, col ):
	# kernel = [[a,b,c],
	# 		  [d,e,f],
	# 		  [g,h,i]]

	a = kernel[0][0]
	b = kernel[0][1]
	c = kernel[0][2]
	d = kernel[1][0]
	e = kernel[1][1]
	f = kernel[1][2]
	g = kernel[2][0]
	h = kernel[2][1]
	i = kernel[2][2]
	# Ref: https://en.wikipedia.org/wiki/Kernel_(image_processing)#Convolution
	result = i*img[row-1][col-1] + h*img[row-1][col] + g*img[row-1][col+1] +\
			 f*img[row][col-1] + e*img[row][col] + d*img[row][col+1] +\
			 c*img[row+1][col-1] + b*img[row+1][col] + a*img[row+1][col+1] 

	return result




width = 640
height = 480

Gx = np.zeros((480,640))
Gy = np.zeros((480,640))
G  = np.zeros((480,640))

kernel_x = [[1,0,-1],
		   [2,0,-2],
		   [1,0,-1]]

kernel_y = [[1,2,1],
		   [0,0,0],
		   [-1,-2,-1]]

# Load image
pixel = np.loadtxt('img_dat.txt')
img = pixel.reshape((height,width))


# Compute kernel*img (where "*" represent convolution)
for j in range(height):
	for i in range(width):
		if i == 0 or j == 0 or i == width - 1 or j == height - 1:
			Gx[j][i] = 0
			Gy[j][i] = 0
			G[j][i] = 0
		else:
			Gx[j][i] = computeCov(img, kernel_x, j, i)
			Gy[j][i] = computeCov(img, kernel_y, j, i)
			G[j][i] = ((Gx[j][i])**2 + (Gy[j][i])**2 )**0.5


plt.subplot(2, 2, 1)
plt.imshow(img, cmap=plt.cm.gray)
plt.axis('off')
plt.title('Original')

plt.subplot(2, 2, 2)
plt.imshow(Gx, cmap=plt.cm.gray)
plt.axis('off')
plt.title('Gx')

plt.subplot(2, 2, 3)
plt.imshow(Gy, cmap=plt.cm.gray)
plt.axis('off')
plt.title('Gy')

plt.subplot(2, 2, 4)
plt.imshow(G, cmap=plt.cm.gray)
plt.axis('off')
plt.title('G')

plt.show()

# Use opencv inbuilt fuction to do 
# the same thing as above. 
# You can find they are almost the same
sobelx = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=3)
sobely = cv2.Sobel(img,cv2.CV_64F,0,1,ksize=3)
mag, angle = cv2.cartToPolar(sobelx, sobely, angleInDegrees=True)

print("GX:")
print(Gx)
print("sobelx:")
print(sobelx)

print("Gy:")
print(Gy)
print("sobely:")
print(sobely)

print("mag")
print(mag)
print("G")
print(G)