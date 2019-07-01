import cv2

# droid cam 사용해서 Video 불러오기
cap = cv2.VideoCapture('http://192.168.1.2:4747/mjpegfeed')

frame_size = (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),\
	int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
print('frame_size =', frame_size)

fourcc = cv2.VideoWriter_fourcc(*'XVID')

out = cv2.VideoWriter('./data/record0.mp4',fourcc, 20.0, frame_size)

while True:
	retval, frame = cap.read()
	if not retval:
		break
	out.write(frame)

	cv2.imshow('frame', frame)

	key=cv2.waitKey(25)
	if key==27:
		break


if cap.isOpened():
	cap.release()
out.release()
cv2.destroyAllWindows()
