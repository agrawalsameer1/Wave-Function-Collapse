import cv2

image = cv2.imread("../images/Forest.png")
(h, w) = image.shape[:2]
fhand = open("pixels.txt","w")
for y in range(h):
	for x in range(w):
		(b,g,r) = image[y,x]
		fhand.write("(%s,%s,%s) " % (r,g,b))
	fhand.write("\n")
fhand.close()