#!/usr/bin/env python

import numpy as np 
from matplotlib import pyplot as plt
import matplotlib.image as mpimg

flower=mpimg.imread('sunflower.jpg')
plt.imshow(flower)
# "plt.savefig" should place before "plt.show()"
plt.savefig("python_write.png")
plt.show()
