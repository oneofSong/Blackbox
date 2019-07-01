import cv2

img = cv2.imread('./data/apple.jpeg', cv2.IMREAD_COLOR)
#img = cv2.resize(img, dsize=(512,512), interpolation=cv2.INTER_AREA)

# gray 이미지
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
img_gray = cv2.cvtColor(img_gray, cv2.COLOR_GRAY2BGR)

hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
lower_blue = (0, 0, 0)
upper_blue = (30, 255,255)
img_mask = cv2.inRange(hsv, lower_blue, upper_blue)

img_result = cv2.bitwise_and(img, img, mask = img_mask)

dst = cv2.add(img_gray, img_result)

cv2.imshow("image", img_gray)
cv2.imshow('img_result', img_result)
cv2.imshow("dst", dst)

cv2.waitKey(0)
cv2.destroyAllWindows()

