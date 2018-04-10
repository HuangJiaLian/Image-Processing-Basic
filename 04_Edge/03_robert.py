#!/usr/bin/env python
import cv2
import numpy as np 
from matplotlib import pyplot as plt


# Get the convolution value at  position (row,col)
def computeCov( img, kernel, row, col ):
	# kernel = [[a,b],
	# 		    [c,d]]

	a = kernel[0][0]
	b = kernel[0][1]
	c = kernel[1][0]
	d = kernel[1][1]

	# Ref: http://homepages.inf.ed.ac.uk/rbf/HIPR2/roberts.htm
	result = d*img[row-1][col-1] + c*img[row-1][col] +\
			 b*img[row][col-1] + a*img[row][col]

	return result




width = 640
height = 480

Gx = np.zeros((480,640))
Gy = np.zeros((480,640))
G  = np.zeros((480,640))

# Robert cross 
kernel_x = [[1,0],
		   [0,-1]]

kernel_y = [[0,1],
		   [-1,0]]

# Load image
pixel = np.loadtxt('img_dat.txt')
img = pixel.reshape((height,width))


# Compute kernel*img (where "*" represent convolution)
for j in range(height):
	for i in range(width):
		if i == 0 or j == 0 :
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
