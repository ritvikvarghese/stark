import cv2 as cv
import mediapipe as mp
import serial
import time
from angles import calculate_angle, calculate_tilt

# follow2 = PAN + TILT (two servos). same self-calibrating idea as follow1,
# extended to the tilt axis. for when the tilt neck is rebuilt.

PORT   = "/dev/cu.usbmodem1101"
BAUD   = 9600
FOV_H  = 60
FOV_V  = 34
DEADZONE = 4.0
GAIN     = 0.06
MAX_STEP = 3.0
PAN_MIN,  PAN_MAX  = 40, 140
TILT_MIN, TILT_MAX = 50, 130
cam_index = 0   # ZEB neck cam (verified: index 0 = ZEB, 1 = laptop)

ser = serial.Serial(PORT, BAUD)
time.sleep(2)
cap = cv.VideoCapture(cam_index)
detector = mp.solutions.face_detection.FaceDetection(min_detection_confidence=0.5)

def send(ch, a, lo, hi):
    a = int(max(lo, min(hi, a)))
    ser.write(f"{ch}{a}\n".encode())
    return a

def find_face(frame):
    h, w = frame.shape[:2]
    res = detector.process(cv.cvtColor(frame, cv.COLOR_BGR2RGB))
    if res.detections:
        best = max(res.detections,
                   key=lambda d: d.location_data.relative_bounding_box.width *
                                 d.location_data.relative_bounding_box.height)
        b = best.location_data.relative_bounding_box
        return (b.xmin + b.width / 2) * w, (b.ymin + b.height / 2) * h, best, w, h
    return None, None, None, w, h

def settle(ch, target, lo, hi, axis, frames=8):
    send(ch, target, lo, hi)
    vals = []
    for _ in range(frames):
        ok, frame = cap.read()
        if not ok:
            continue
        cx, cy, det, w, h = find_face(frame)
        v = cx if axis == 'x' else cy
        if v is not None:
            vals.append(v)
            mp.solutions.drawing_utils.draw_detection(frame, det)
        cv.putText(frame, "CALIBRATING - look at the camera, hold still",
                   (10, 30), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 255), 2)
        cv.imshow("follow2", frame)
        cv.waitKey(30)
    return (sum(vals) / len(vals)) if vals else None

def calibrate(ch, lo, hi, axis):
    while True:
        a = settle(ch, 85, lo, hi, axis)
        b = settle(ch, 105, lo, hi, axis)
        if a is None or b is None:
            continue
        d = b - a
        if abs(d) < 10:
            continue
        return -1 if d > 0 else 1

pan_sign  = calibrate('p', PAN_MIN,  PAN_MAX,  'x')
tilt_sign = calibrate('t', TILT_MIN, TILT_MAX, 'y')
print("pan_sign", pan_sign, "tilt_sign", tilt_sign)

send('p', 90, PAN_MIN, PAN_MAX)
send('t', 90, TILT_MIN, TILT_MAX)
servo_pan = servo_tilt = 90.0
last_p = last_t = 90

while True:
    ok, frame = cap.read()
    if not ok:
        cv.waitKey(30)
        continue
    cx, cy, det, w, h = find_face(frame)
    have = cx is not None
    if have:
        mp.solutions.drawing_utils.draw_detection(frame, det)
        ex = calculate_angle(cx, w, FOV_H)
        ey = calculate_tilt(cy, h, FOV_V)
        if abs(ex) < DEADZONE: ex = 0
        if abs(ey) < DEADZONE: ey = 0
        sp = max(-MAX_STEP, min(MAX_STEP, GAIN * pan_sign  * ex))
        st = max(-MAX_STEP, min(MAX_STEP, GAIN * tilt_sign * ey))
        servo_pan  = max(PAN_MIN,  min(PAN_MAX,  servo_pan  + sp))
        servo_tilt = max(TILT_MIN, min(TILT_MAX, servo_tilt + st))
        p, t = int(round(servo_pan)), int(round(servo_tilt))
        if p != last_p: last_p = send('p', p, PAN_MIN, PAN_MAX)
        if t != last_t: last_t = send('t', t, TILT_MIN, TILT_MAX)
    cv.putText(frame, f"PAN+TILT  pan {pan_sign:+d} tilt {tilt_sign:+d}  q=quit",
               (10, 30), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    if not have:
        cv.putText(frame, "no face", (10, 60), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
    cv.imshow("follow2", frame)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
ser.close()
cv.destroyAllWindows()
