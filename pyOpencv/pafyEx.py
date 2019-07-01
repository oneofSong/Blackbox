import cv2, pafy

url = 'https://youtu.be/YlKY4EImAWM'

video = pafy.new(url)
print('title=', video.title)
print('video.rating=', video.rating)
print('video.duration=', video.duration)

best = video.getbest()
print('best.resolution', best.resolution)
#print('best.url', best.url)

cap = cv2.VideoCapture(best.url)
while(True):
	retval, frame = cap.read()

	if not retval:
		 break
	cv2.imshow('frame',frame)

#	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#	edges = cv2.Canny(gray,100,200)
#	cv2.imshow('edges',edges)

	key = cv2.waitKey(25)
	if key == 27: # Esc
		break

cv2.destroyAllWindows()
