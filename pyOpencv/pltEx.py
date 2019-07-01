import cv2
from matplotlib import pyplot as plt

imageFile = './data/lena_mat.png'

imgBGR = cv2.imread(imageFile)

plt.axis('off')
plt.imshow(imgBGR)
plt.show()

imgRGB = cv2.cvtColor(imgBGR, cv2.COLOR_BGR2RGB)
plt.imshow(imgRGB)
plt.show()

