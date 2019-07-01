import cv2

imageFile = './lena.jpg'

img = cv2.imread(imageFile)

cv2.imwrite('./data/lena.bmp', img)

cv2.imwrite('./data/lena.png', img)

cv2.imwrite('./data/lena2.png',img, [cv2.IMWRITE_PNG_COMPRESSION,9])
cv2.imwrite('./data/lena2.jpg',img, [cv2.IMWRITE_JPEG_QUALITY,90])
