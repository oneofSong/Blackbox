import cv2

img = cv2.imread('./data/apple.jpeg', cv2.IMREAD_COLOR)
#img = cv2.resize(img, dsize=(512,512), interpolation=cv2.INTER_AREA)

# gray 이미지
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
img_gray = cv2.cvtColor(img_gray, cv2.COLOR_GRAY2BGR)

hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
lower_red = (0,70, 50)
upper_red = (20, 255,255)

img_mask1 = cv2.inRange(hsv, lower_red, upper_red)
img_mask2 = cv2.inRange(hsv, (160,70,50), (180,255,255))

img_mask = img_mask1 |  img_mask2
img_result = cv2.bitwise_and(img, img, mask = img_mask)

cv2.imshow('image', img)
#cv2.imshow("image_gray", img_gray)
cv2.imshow('img_result', img_result)

cv2.waitKey(0)
cv2.destroyAllWindows()

