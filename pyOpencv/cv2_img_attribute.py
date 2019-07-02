import cv2
import numpy as np

img = cv2.imread('./lena.jpg')

print("img.ndim=",img.ndim)
print("img.shape=", img.shape)
print("img.dtype=", img.dtype)

img = img.astype(np.int32)
print("img.dtype=", img.dtype)

img = np.uint8(img)
print("img.dtype=", img.dtype)

