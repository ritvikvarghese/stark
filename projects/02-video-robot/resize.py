import cv2 as cv 

def rescaleFrame(frame, scale=0.75):
    width = int(frame.shape[1] * scale)
    height = int(frame.shape[0] * scale)
    dimensions = (width, height)
    return cv.resize(frame, dimensions, interpolation=cv.INTER_AREA) 
    #INTER_AREA is the method of resizing the image. 

cap = cv.VideoCapture("/Users/rivar/Downloads/day-08-led-demo.mp4")

while True:
    isTrue, frame = cap.read()
    frame_resized = rescaleFrame(frame)
    cv.imshow("Video Resized", frame_resized) #"" has no effect on the video. it is just a name.
    if cv.waitKey(20) & 0xFF == ord('d'):
        break

cap.release()
cv.destroyAllWindows()