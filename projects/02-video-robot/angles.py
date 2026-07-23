import math

def calculate_angle(cx, width, fov_h): # cx is the x-center of the face (px), width is the FRAME width (px), fov_h is the horizontal field of view (deg)
    offset_x = (cx - (width / 2))
    angle = (offset_x / width) * fov_h
    return angle

print(calculate_angle(960, 1920, 60))    # expect ~0
print(calculate_angle(1920, 1920, 60))   # expect ~+30
print(calculate_angle(0, 1920, 60))     # expect ~-30

def calculate_tilt (cy, height, fov_v): # cy is the y-center of the face (px), height is the FRAME height (px), fov_v is the vertical field of view (deg)
    offset_y = (cy - (height / 2))
    tilt = (offset_y / height) * fov_v
    return tilt

print(calculate_tilt(540, 1080, 34))    # expect ~0
print(calculate_tilt(1080, 1080, 34))   # expect ~+17
print(calculate_tilt(0, 1080, 34))     # expect ~-17

def calculate_angle_trig(cx, width, fov_h): # same as calculate_angle but the trig-correct (pinhole) version; f is the focal length in pixels
    offset_x = (cx - (width / 2))
    f = (width / 2) / math.tan(math.radians(fov_h / 2))
    return math.degrees(math.atan(offset_x / f))

print(calculate_angle_trig(960, 1920, 60))    # expect ~0
print(calculate_angle_trig(1920, 1920, 60))   # expect ~+30
print(calculate_angle_trig(0, 1920, 60))     # expect ~-30

# linear vs trig at the 3/4 mark (1440) — this is where they DISAGREE
print("linear:", calculate_angle(1440, 1920, 60))       # 15.0
print("trig:  ", calculate_angle_trig(1440, 1920, 60))  # a bit more — the real projection
