# PIL 사용

#from PIL import Image

#im = Image.open('lena.jpg')
#im = im.resize((512,512))
#cropImage = im.crop((100,100,350,350))
#im.show()
#cropImage.show()

# cv2
import cv2
import numpy as np

def handle_button_release(event):
	cv2.destroyAllWindows()

#def handle_button_press(event):

def img_crop(img):
	max_x = 100
	max_y = 100
	x = np.random.randint(0, max_x)
	y = np.random.randint(0, max_y)

	crop = img[y:y + 350, x: x+350]

	return crop

img = cv2.imread('./lena.jpg')
img = cv2.resize(img, dsize=(521,521), interpolation=cv2.INTER_AREA)

crop = img_crop(img)

cv2.imshow("crop", crop)
cv2.waitKey(0)
cv2.destroyAllWindows()
