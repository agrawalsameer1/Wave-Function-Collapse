import cv2
import numpy as np
from ast import literal_eval

fhand = open("pixels.txt")
arr = []
for line in fhand:
    line = line.strip()
    lineArr = line.split()
    for i in range(len(lineArr)):
        lineArr[i] = literal_eval(lineArr[i])
    arr.append(lineArr)
arr = np.array(arr)
cv2.imwrite('output.png', arr)