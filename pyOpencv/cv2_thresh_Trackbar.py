import numpy as np
import cv2

def onChange(pos):
	global raw_img 
	img = raw_img
	
	low = cv2.getTrackbarPos('threshold_low','img')
	high = cv2.getTrackbarPos('threshold_high','img')
	
	_, img = cv2.threshold(img, low, high, cv2.THRESH_BINARY)
	cv2.imshow('img', img)
	
raw_img = cv2.imread("./lena.jpg", cv2.IMREAD_GRAYSCALE);
raw_img = cv2.resize(raw_img, dsize=(512,512), interpolation=cv2.INTER_AREA)

cv2.imshow("img", raw_img)

cv2.createTrackbar('threshold_low', 'img', 0, 255, onChange)
cv2.createTrackbar('threshold_high', 'img', 0, 255, onChange)

while True:
	if cv2.waitKey(20) & 0xFF == 27:
		break
cv2.DestroyAllWindow()


