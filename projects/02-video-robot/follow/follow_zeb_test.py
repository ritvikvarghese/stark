import cv2 as cv
import mediapipe as mp
import serial
import time

# ISOLATION TEST: same open-loop code as follow_laptop.py, but using the ZEB
# camera -- which is now mounted FIXED (not on the servo).
#   - if this tracks my face just like the laptop did  -> the ZEB camera is fine,
#     and the closed loop (camera-on-servo) was the WHOLE problem. proven.
#   - if this ALSO misbehaves -> the ZEB camera itself is the culprit.
# only ONE thing changed from the working laptop version: CAM 1 -> 0.

PORT = "/dev/cu.usbmodem1101"
BAUD = 9600
CAM = 0                          # 0 = ZEB (fixed). if it shows the laptop selfie, change to 1
SIGN = -1                        # flip to +1 if the servo turns the wrong way
RANGE = 55
SMOOTH = 0.9
PAN_MIN, PAN_MAX = 30, 150

ser = serial.Serial(PORT, BAUD)
time.sleep(2)
ser.write(b"p90\n")

cam = cv.VideoCapture(CAM)
cam.set(cv.CAP_PROP_FRAME_WIDTH, 640)
cam.set(cv.CAP_PROP_FRAME_HEIGHT, 480)

faces = mp.solutions.face_detection.FaceDetection(model_selection=0,
                                                  min_detection_confidence=0.5)

servo = 90.0
last_angle = 90
last_time = 0.0

while True:
    ok, frame = cam.read()
    if not ok:
        continue

    h, w = frame.shape[:2]
    result = faces.process(cv.cvtColor(frame, cv.COLOR_BGR2RGB))

    if result.detections:
        face = result.detections[0]
        mp.solutions.drawing_utils.draw_detection(frame, face)
        box = face.location_data.relative_bounding_box
        cx = (box.xmin + box.width / 2) * w

        offset = (cx - w / 2) / (w / 2)
        target = 90 + SIGN * offset * RANGE
        servo = (1 - SMOOTH) * servo + SMOOTH * target
        servo = max(PAN_MIN, min(PAN_MAX, servo))

        angle = int(round(servo))
        now = time.time()
        if abs(angle - last_angle) >= 2 and now - last_time >= 0.02:
            ser.write(f"p{angle}\n".encode())
            last_angle = angle
            last_time = now

    cv.putText(frame, f"ZEB FIXED -> servo {int(servo)}   q=quit", (10, 30),
               cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv.imshow("zeb-test", frame)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cam.release()
ser.close()
cv.destroyAllWindows()
