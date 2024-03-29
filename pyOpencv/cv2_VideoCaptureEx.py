import cv2

# Video 불러오기
cap = cv2.VideoCapture('./data/record0.mkv')

frame_size = (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),\
	int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
print('frame_size =', frame_size)

while True:
	retval, frame = cap.read()
	if not retval:
		break

	cv2.imshow('frame', frame)

	key=cv2.waitKey(25)
	if key==27:
		break


if cap.isOpened():
	cap.release()
cv2.destroyAllWindows()
