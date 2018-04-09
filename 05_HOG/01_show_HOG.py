# To calculate HOG and display the HOG image
import matplotlib.pyplot as plt
import cv2
from skimage.feature import hog
from skimage import  exposure

image = cv2.cvtColor(cv2.imread("sunflower.jpg"),
                   cv2.COLOR_BGR2GRAY)

# image = cv2.cvtColor(cv2.imread("Original_Image.png"),
#                    cv2.COLOR_BGR2GRAY)

fd, hog_image = hog(image, orientations=8, pixels_per_cell=(16, 16),
                cells_per_block=(1, 1), block_norm='L2-Hys',visualise=True)

# fd, hog_image = hog(image, orientations=8, pixels_per_cell=(32, 32),
#                 cells_per_block=(1, 1), block_norm='L2-Hys',visualise=True)
# use visulaize or visualise is OK, but for this version of skimage, use 'visualise'.

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 8), sharex=True, sharey=True)
ax1.axis('off')
ax1.imshow(image, cmap=plt.cm.gray)
ax1.set_title('Input image')

# Rescale histogram for better display
hog_image_rescaled = exposure.rescale_intensity(hog_image, in_range=(0, 10))


ax2.axis('off')
ax2.imshow(hog_image_rescaled, cmap=plt.cm.gray)
ax2.set_title('Histogram of Oriented Gradients')
plt.show()