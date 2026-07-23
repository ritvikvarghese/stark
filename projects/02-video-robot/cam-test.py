import cv2 as cv 
import mediapipe as mp # mediapipe is a library that provides a face detection model.
cap = cv.VideoCapture(0) 
cap.isOpened() # is opened is a function that checks if the camera is open.
detector = mp.solutions.face_detection.FaceDetection(min_detection_confidence=0.5) 
#min_detection_confidence is the confidence level of the face detection.
# 0.5 means 50% confidence level. 

while True:
    isTrue, frame = cap.read()
    if not isTrue:
        print("Failed to grab frame")
        break
    rgb = cv.cvtColor(frame, cv.COLOR_BGR2RGB) # Now the frame is in RGB format. 
    results = detector.process(rgb) # results is the output of the face detection model.

    if results.detections:
        for detection in results.detections:
            mp.solutions.drawing_utils.draw_detection(frame, detection)
            bbox = detection.location_data.relative_bounding_box 
            #bbox is the bounding box of the face.
            h, w = frame.shape[:2] 
            #h is the height of the frame, w is the width of the frame.
            cx = int((bbox.xmin + bbox.width / 2) * w)
            #cx is the x coordinate of the center of the face.
            cy = int((bbox.ymin + bbox.height / 2) * h)
            #cy is the y coordinate of the center of the face.
            print(cx, cy) #print the x and y coordinates of the center of the face.

    cv.imshow("Frame", frame)
    if cv.waitKey(1) == ord('q'): # if the user presses q, the loop will break.
        break

cap.release()
cv.destroyAllWindows()