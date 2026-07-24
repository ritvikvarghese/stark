import math

def calculate_angle(cx, width, fov_h): # cx is the x-center of the face (px), width is the FRAME width (px), fov_h is the horizontal field of view (deg)
    offset_x = (cx - (width / 2))
    angle = (offset_x / width) * fov_h
    return angle

def calculate_tilt (cy, height, fov_v): # cy is the y-center of the face (px), height is the FRAME height (px), fov_v is the vertical field of view (deg)
    offset_y = (cy - (height / 2))
    tilt = (offset_y / height) * fov_v
    return tilt

def calculate_angle_trig(cx, width, fov_h): # same as calculate_angle but the trig-correct (pinhole) version; f is the focal length in pixels
    offset_x = (cx - (width / 2))
    f = (width / 2) / math.tan(math.radians(fov_h / 2))
    return math.degrees(math.atan(offset_x / f))
