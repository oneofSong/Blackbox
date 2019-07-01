# cv2
import cv2
import numpy as np


def img_crop(img):
	max_x = 100
	max_y = 100
	x = np.random.randint(0, max_x)
	y = np.random.randint(0, max_y)

	crop = img[y:y + 350, x: x+350]

	return crop
def img_rotate(img):
	angle = 90
	scale = 1.
	H = img.shape[0]
	W = img.shape[1]
	matrix = cv2.getRotationMatrix2D((W/2,H/2), angle, scale)
	rotated = cv2.warpAffine(img, matrix, (W,H)) 
	return rotated

def mouse_callback(event, x, y, flags, param):
	global crop
	if event == cv2.EVENT_LBUTTONDBLCLK:
		img=img_crop(param)
		crop = img
		cv2.imshow("image", img)
	elif event == cv2.EVENT_MBUTTONDOWN: 
		crop = img_rotate(crop)
		cv2.imshow("image", crop)
		
img = cv2.imread('./lena.jpg')
img = cv2.resize(img, dsize = (521,521), interpolation=cv2.INTER_AREA)

crop = img_crop(img)
cv2.namedWindow('image')
cv2.setMouseCallback('image', mouse_callback,param = img)

cv2.imshow("image", crop)
while True:
	if cv2.waitKey(20) & 0xFF == 27:
		break
cv2.destroyAllWindows()
