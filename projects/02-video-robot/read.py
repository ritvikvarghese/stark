import cv2 as cv 
import numpy as np 

# img = cv.imread("/Users/rivar/Desktop/rivar hq/images/physical.jpg") 

# cv.imshow("physical", img) shows the image 

# read video
cap = cv.VideoCapture("/Users/rivar/Downloads/day-08-led-demo.mp4")

while True: 
    isTrue, frame = cap.read() #reads the video frame by frame
    cv.imshow("Video", frame) #shows the video frame by frame

    if cv.waitKey(20) & 0xFF == ord('d'): #press d to stop the video
        break

cap.release() #releases the video means it closes the video
cv.destroyAllWindows() #closes the window