# day 12 — 2026-07-23

**goal:** the math module. turn the face's pixel center `(cx, cy)` from day 11 into **pan/tilt angles** — the "think" step between seeing and moving. derive it on paper, then write it in python.

## what i built
- `angles.py` with three small functions:
  - `calculate_angle(cx, width, fov_h)` — pan angle from the horizontal offset off-center. linear/proportional: `(offset_x / width) * fov_h`.
  - `calculate_tilt(cy, height, fov_v)` — same idea, vertical.
  - `calculate_angle_trig(...)` — the trig-correct (pinhole) version using `arctan` and a focal length in pixels.
- verified against cases i know: centered → 0°, edges → ±30° (pan) / ±17° (tilt). the linear and trig versions agree at center and edges and differ by ~1° in between (linear 15° vs trig 16.1° at the 3/4 mark) — which is exactly why the trig one is more accurate.
- FOV: used `fov_h = 60°`, `fov_v ≈ 34°` as estimates — the ZEB webcam doesn't publish a FOV spec, so these are placeholders i can measure or tune later. (wrote a note on how to self-measure FOV.)

## honest note on today
a lot of this was AI-accelerated. i tried to understand as much as i could and wrote the functions myself, but some of the deeper stuff (the pinhole/arctan reasoning) went a bit over my head — and that's okay. right now **progress matters more than mastering every topic**. the objective is a solid base understanding across the whole build, not sinking days into one idea. i can always relearn this or get AI to walk me through it again when it actually matters (day 15 PID, the arm kinematics). understanding is slightly low here, and that's a fine trade for momentum.

nothing broke. no bugs, no blockers. a clean math day.

## next
day 13 — arduino firmware: receive pan/tilt angles over serial and move the two servos. then day 14 wires today's angles to the live camera and closes the loop.
