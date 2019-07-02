import numpy as np
import cv2

def onChange(pos):
	global img
	h = cv2.getTrackbarPos('H','img')
	v = cv2.getTrackbarPos('V','img')
	s = cv2.getTrackbarPos('S','img')
	img[:] = (h,s,v)
	img = cv2.cvtColor(img,cv2.COLOR_HSV2BGR)
	cv2.imshow('img',img)

#img = cv2.imread('./lena.jpg')
#img = cv2.resize(img, dsize=(512,512), interpolation=cv2.INTER_AREA)
#img = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)

img = np.zeros((512,512,3), np.uint8)
img = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
cv2.imshow('img',img)

cv2.createTrackbar('H', 'img', 0, 180, onChange)
cv2.createTrackbar('S', 'img', 0, 255, onChange)
cv2.createTrackbar('V', 'img', 0, 255, onChange)

cv2.setTrackbarPos('V', 'img', 255)

cv2.waitKey()
cv2.destroyAllWinows()
