import cv2
import numpy as np

img = np.full((512,512,3), (255,255,255), dtype=np.uint8)

pt1 = 100,100
pt2 = 400,400

cv2.rectangle(img, pt1,pt2, (0,0,255),1)
cv2.rectangle(img, (100,50),pt2, (0,0,255),1)

cv2.line(img, (120,50),(300,500),(255,0,0),1)

# cv2.clipLine( rect_size(x,y,H,W), line_start, line_end)
imgRect = (pt1[0], pt1[1], pt2[0]-pt1[0], pt2[1]-pt1[1])
retval, rpt1, rpt2 = cv2.clipLine(imgRect, (120,50), (300,500))

if retval:
	cv2.circle(img, rpt1, radius = 5, color=(0,255,0), thickness=-1)
	cv2.circle(img, rpt2, radius = 5, color=(0,255,0), thickness=-1)

cv2.imshow('img',img)
cv2.waitKey()
cv2.detroyAllWinows()
