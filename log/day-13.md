# day 13 — 2026-07-23

**goal:** back to the arduino. firmware that receives pan/tilt angles over serial and drives **two servos**. define a clean serial protocol (it gets reused for the recording LED later).

## what i built
- `firmware/pan-tilt-serial/pan-tilt-serial.ino` — two `Servo` objects on pins 9 and 10, `Serial.begin(9600)`, both centered at 90° on startup. in the loop it reads a command char + an angle, constrains it, and moves the matching servo.
- **the serial protocol i landed on:** one axis per message, `<letter><angle>`:
  - `p120` → pan to 120°
  - `t60` → tilt to 60°
  - echoes back what it did for confirmation.
  simpler than the `P90 T90` two-value line i first considered, and still extends cleanly — day 18's recording LED just becomes another letter (`l1`/`l0`) on the same channel.
- realized this is basically the day-7 `servo-4` exercise (write an angle to a servo) doubled up and driven by serial parsing instead of hardcoded values.

## power (the setup, done right this time)
- two MG996R off an **external 5V supply**, NOT the arduino 5V pin (they can pull ~1A each at stall). **1000µF 25V cap** across the servo rail for brownout smoothing, and the servo ground tied to the arduino ground (**common ground**). servos bench-tested loose, not in the bracket yet.

## what broke
- on power-up, one servo started **twitching on its own** before i'd uploaded anything. first thought it was a fault. it wasn't — the **common-ground jumper was loose**, so the servo had no stable reference for the PWM signal and jittered. tightened the ground and it went dead quiet. good reminder that "the wire everyone forgets" is exactly the one that bit me, and that a floating ground looks like a code bug when it isn't.

## what i learned
- **check power/ground before blaming code.** the twitch was pure hardware — a loose ground reference, not the sketch.
- an arduino runs whatever sketch is already flashed the instant it gets power — it doesn't wait for me.
- reading serial: grab the command char first, then `parseInt()` the number after it. `constrain()` the angle so a bad command can't jam a servo.

## checkpoint — hit
typed `p120` / `t60` / `p90` in the serial monitor → both servos obey, snap to angle, hold steady, no board resets. the neck takes commands.

## next
day 14 — close the loop: replace my typing with the live `cx, cy → angles` from python, so the camera drives the servos and the neck follows my face. jerky/overshooting is expected (that's what day-15's PID fixes).
