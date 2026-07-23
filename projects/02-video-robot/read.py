import cv2 as cv 

# img = cv.imread("/Users/rivar/Desktop/rivar hq/images/physical.jpg") 

# cv.imshow("physical", img) shows the image 

# read video
cap = cv.VideoCapture("/Users/rivar/Downloads/day-08-led-demo.mp4")

while True: # while true is a loop that will run until the video is over
    isTrue, frame = cap.read() # is true is a boolean that tells if the video is running and frame is the video frame
    cv.imshow("Video", frame) # shows the video frame by frame

    if cv.waitKey(20) & 0xFF == ord('d'): # if the user presses d, the video will stop
        break

cap.release() # releases the video means it closes the video after the video is over
cv.destroyAllWindows() # closes the window after the video is over