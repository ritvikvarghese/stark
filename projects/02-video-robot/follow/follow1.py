import cv2 as cv
import mediapipe as mp
import serial
import time
import threading
from angles import calculate_angle

# follow1 = CLOSED LOOP: the ZEB rides ON the servo and follows my face.
# now with the full low-latency stack the earlier attempts never had:
#   - fast line-buffered firmware (follow1.ino)   <- already flashed
#   - fresh-frame background grabber
#   - small 640x480 frames (fast detection)
#   - rate-limited sends (serial can't back up)
# control is a plain P (proportional) nudge. DAY 15: replace the single
# `GAIN * err` term with the full PID (Kp*e + Ki*integral + Kd*derivative).

PORT = "/dev/cu.usbmodem1101"
BAUD = 9600
FOV_H = 60
DEADZONE = 3.0
GAIN = 0.30                 # proportional gain (this is the term PID will expand)
CTRL_INTERVAL = 0.04        # correct ~25x/sec, on fresh frames
PAN_MIN, PAN_MAX = 30, 150
CAM = 0                     # ZEB (on the servo). if it shows the laptop, change to 1
PAN_SIGN = -1               # confirmed via clean measurement

ser = serial.Serial(PORT, BAUD)
time.sleep(2)
ser.reset_output_buffer()
ser.write(b"p90\n")

cam = cv.VideoCapture(CAM)
cam.set(cv.CAP_PROP_FRAME_WIDTH, 640)
cam.set(cv.CAP_PROP_FRAME_HEIGHT, 480)
try:
    cam.set(cv.CAP_PROP_BUFFERSIZE, 1)
except Exception:
    pass

# background grabber: always keep the freshest frame (this matters a LOT for a
# closed loop -- stale frames are what make it unstable)
_state = {"frame": None, "on": True}
def _grab():
    while _state["on"]:
        ok, f = cam.read()
        if ok:
            _state["frame"] = f
threading.Thread(target=_grab, daemon=True).start()
time.sleep(0.5)

faces = mp.solutions.face_detection.FaceDetection(model_selection=0,
                                                  min_detection_confidence=0.5)

servo = 90.0
last_angle = 90
last_ctrl = 0.0

while True:
    frame = _state["frame"]
    if frame is None:
        if cv.waitKey(20) & 0xFF == ord('q'):
            break
        continue
    frame = frame.copy()
    h, w = frame.shape[:2]
    result = faces.process(cv.cvtColor(frame, cv.COLOR_BGR2RGB))

    have, err = False, 0.0
    if result.detections:
        face = result.detections[0]
        mp.solutions.drawing_utils.draw_detection(frame, face)
        box = face.location_data.relative_bounding_box
        cx = (box.xmin + box.width / 2) * w
        have = True
        err = calculate_angle(cx, w, FOV_H)      # how far off-center my face is (deg)

    now = time.time()
    if have and abs(err) >= DEADZONE and now - last_ctrl >= CTRL_INTERVAL:
        # ---------- P controller (Day 14). Day-15 PID goes right here. ----------
        servo += GAIN * PAN_SIGN * err
        # ------------------------------------------------------------------------
        servo = max(PAN_MIN, min(PAN_MAX, servo))
        angle = int(round(servo))
        if angle != last_angle:
            ser.write(f"p{angle}\n".encode())
            last_angle = angle
        last_ctrl = now

    cv.line(frame, (w // 2, 0), (w // 2, h), (0, 255, 255), 1)
    cv.putText(frame, f"CLOSED LOOP   servo {int(servo)}   err {err:+.0f}   q=quit",
               (10, 30), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    if not have:
        cv.putText(frame, "no face", (10, 60), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
    cv.imshow("follow1-closed", frame)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

_state["on"] = False
time.sleep(0.2)
cam.release()
ser.close()
cv.destroyAllWindows()
