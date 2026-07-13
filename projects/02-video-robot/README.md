# 02 — video robot

a webcam on a motorized neck that follows my face, listens, and records on command
(days 11-24). python (opencv + mediapipe) finds the face and sends pan/tilt corrections
over serial to two servos; a hand-built pid smooths the motion; local speech recognition
arms and stops recording on voice. a complete sense-think-act loop with ears. it then
films every demo in this repo, including the arm.
