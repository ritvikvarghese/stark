import cv2 as cv
import mediapipe as mp
import serial
import time

# the LAPTOP camera watches my face, and the servo turns to point where i am.
# the camera does NOT move with the servo, so there is no feedback loop and it
# can't run away. simple and stable.

PORT = "/dev/cu.usbmodem1101"   # the arduino's address (flips 101 / 1101 on replug)
BAUD = 9600                     # talking speed, must match the arduino code
CAM = 1                         # 1 = laptop camera (0 = the ZEB). change if it shows the room
SIGN = -1                       # flip to +1 if the servo turns the wrong way
RANGE = 55                      # how far the servo swings (deg) when my face is at the edge
SMOOTH = 0.9                    # 0..1, higher = snappier
PAN_MIN, PAN_MAX = 30, 150      # keep the servo in a safe range

# --- open the arduino and the camera (runs once) ---
ser = serial.Serial(PORT, BAUD)
time.sleep(2)                   # the arduino resets when we connect, so wait for it
ser.write(b"p90\n")             # start centered at 90

cam = cv.VideoCapture(CAM)
cam.set(cv.CAP_PROP_FRAME_WIDTH, 640)    # small picture = faster face-finding
cam.set(cv.CAP_PROP_FRAME_HEIGHT, 480)

faces = mp.solutions.face_detection.FaceDetection(model_selection=0,
                                                  min_detection_confidence=0.5)

servo = 90.0        # where we think the servo should point
last_angle = 90     # the last angle we actually sent
last_time = 0.0     # when we last sent (used to not spam the arduino)

# --- the loop (runs over and over) ---
while True:
    ok, frame = cam.read()
    if not ok:
        continue

    h, w = frame.shape[:2]
    result = faces.process(cv.cvtColor(frame, cv.COLOR_BGR2RGB))

    if result.detections:
        face = result.detections[0]          # just take the first face it sees
        mp.solutions.drawing_utils.draw_detection(frame, face)
        box = face.location_data.relative_bounding_box
        cx = (box.xmin + box.width / 2) * w  # x-center of my face, in pixels

        offset = (cx - w / 2) / (w / 2)      # -1 = far left, 0 = middle, +1 = far right
        target = 90 + SIGN * offset * RANGE  # where the servo should point
        servo = (1 - SMOOTH) * servo + SMOOTH * target   # glide toward it
        servo = max(PAN_MIN, min(PAN_MAX, servo))        # keep it in range

        angle = int(round(servo))
        now = time.time()
        # only send if it changed a bit AND a moment has passed (so serial can't clog up)
        if abs(angle - last_angle) >= 2 and now - last_time >= 0.02:
            ser.write(f"p{angle}\n".encode())
            last_angle = angle
            last_time = now

    cv.putText(frame, f"servo {int(servo)}   q=quit", (10, 30),
               cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv.imshow("laptop-follow", frame)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cam.release()
ser.close()
cv.destroyAllWindows()
