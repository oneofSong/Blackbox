import cv2
import numpy as np

# 함수 정의

img = np.full((512,512,3), (255,255,255), dtype=np.uint8)

pt1 = 100,100
pt2 = 400,400
center_pt = 250, 250
cv2.rectangle(img, pt1,pt2, (0,0,255),-1)

cv2.line(img, (center_pt[0]+200,center_pt[1]),(center_pt[0]-200,center_pt[1]),(255,0,0),1)
cv2.line(img, (center_pt[0],center_pt[1]+200),(center_pt[0],center_pt[1]-200),(255,0,0),1)

# cv2.clipLine( rect_size(x,y,H,W), line_start, line_end)
imgRect = (pt1[0], pt1[1], pt2[0]-pt1[0], pt2[1]-pt1[1])
retval1, rpt1, rpt2 = cv2.clipLine(imgRect, (center_pt[0]+200,center_pt[1]),(center_pt[0]-200,center_pt[1]))

retval2, rpt21, rpt22 = cv2.clipLine(imgRect, (center_pt[0],center_pt[1]+200),(center_pt[0],center_pt[1]-200))
if retval1:
	cv2.circle(img, rpt1, radius = 5, color=(0,255,0), thickness=-1)
	cv2.circle(img, rpt2, radius = 5, color=(0,255,0), thickness=-1)

if retval2:
	cv2.circle(img, rpt21, radius = 5, color=(0,255,0), thickness=-1)
	cv2.circle(img, rpt22, radius = 5, color=(0,255,0), thickness=-1)

cv2.imshow('img',img)
cv2.waitKey()
cv2.destroyAllWinows()
