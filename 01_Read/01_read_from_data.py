#!/usr/bin/env python

import numpy as np 
from matplotlib import pyplot as plt
pixel = np.loadtxt('img_dat.txt')
img = pixel.reshape((480,640))

plt.figure("Image Test")
plt.imshow(img,cmap='gray')
plt.axis('on')
plt.title('Image')
plt.show()

