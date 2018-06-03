import numpy as np
import cv2

def bgrFilter(src, bgr):
	for y in range(len(src)):
		for x in range(len(src[y])):
			if (src[y, x, 0] == bgr[0] and src[y, x, 1] == bgr[1] and src[y, x, 2] == bgr[2]) == False:
				src[y, x, 0] = 255
				src[y, x, 1] = 255
				src[y, x, 2] = 255
				
colors = {0 : [255, 0, 255], 1 : [255, 0, 0], 2 : [255, 255, 0], 3 : [0, 0, 0], 4 : [0, 255, 0], 5 : [0, 255, 255], 6 : [0, 0, 255]}

order = [0, 1, 2, 3, 4, 5, 6]

for i in order:
	color = colors[i]

	img = cv2.imread("targets.png")
	
	for i in range(100):
		kernel = np.ones((5, 5), np.float32) / 25
		img = cv2.filter2D(img, -1, kernel)

	bgrFilter(img, color)
	print("color=", color)
	
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	gray = cv2.medianBlur(gray, 5)
	
	circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 20, param1 = 50, param2 = 30, minRadius = 0, maxRadius = 0)
	#circles = np.uint16(np.around(circles))
	
	if circles is not None:
		circle = circles[0, 0, :]
		print("x=%d, y=%d, radius=%d" % (circle[0], circle[1], circle[2]))
