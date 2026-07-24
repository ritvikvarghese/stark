# day 14 — close the loop

up to now the three pieces lived apart and i drove the neck by typing `p120` into
the serial monitor by hand. today the camera does the typing. one program runs the
whole chain:

```
camera  ->  face box (cx,cy)  ->  angles.py  ->  serial write  ->  neck moves
 eyes          think               think           move            move
```

no new hardware, no new math. it's pure wiring. the file is `follow.py`.

## what reuses what

- **eyes** — the opencv + mediapipe loop, copied in from `cam-test.py`. finds the
  face, gives `cx, cy` (the center of the face in pixels).
- **think** — `follow.py` **imports** `angles.py`, which now sits right next to it
  in this `follow/` folder, and calls `calculate_angle` and `calculate_tilt`. i did
  not rewrite that math, i borrowed it — a plain `from angles import ...`, no path
  juggling, because python always looks in a script's own folder.
- **move** — `serial` (the pyserial library, installed today) writes to the
  arduino, using the day-13 protocol from `firmware/follow`.

## the part i write (not scaffolded)

`follow.py` is filled in for me EXCEPT three TODO lines in the middle. those are the
whole point of the day:

`calculate_angle` gives a **signed error** around zero (0 = face centered, +30 =
face at the right edge). but the servo doesn't want an error — it wants an
**absolute position, 0..180, centered at 90**. so i convert: start at 90, add or
subtract the error.

which sign? **can't reason it from the desk — find it by testing.** move my face
right; if the neck turns the wrong way, flip the sign. pan and tilt are independent,
so find each one separately. that 30-second experiment is the actual content of
day 14.

## wiring + power (current reality)

no neck is built yet. the two MG996R servos are **loose on a breadboard**, cap and
all, not in a bracket. that's fine for today. what matters:

- **power the servos from the external PSU, not the arduino 5V pin.** MG996Rs pull
  way more current than the arduino can source — driving them off the 5V pin
  browns out the board and it resets mid-move.
- **common ground:** the PSU ground and the arduino ground must be tied together on
  the breadboard, or the servo signal has nothing to reference and twitches.
- the **capacitor across the servo power rail** is already there — it soaks up the
  current spikes when both servos snap at once. keep it.
- because the servos are loose, the neck moves are meaningless as "aim," but that's
  ok — today's checkpoint is just "does it respond to my face." the `constrain(0,180)`
  in the firmware keeps them from trying to drive past their limit and buzzing.

## how to run

1. arduino: `firmware/follow/follow.ino` must be **uploaded** and
   the **serial monitor CLOSED** (an open monitor holds the port, python can't get it).
2. power the servo rail from the PSU (see above).
3. from **Terminal.app** (not Cursor — macOS camera permission is per-app), from the
   `02-video-robot` folder:

   ```
   ./.venv/bin/python follow/follow.py
   ```

4. a camera window opens. move around. press `q` to quit.
5. port is `/dev/cu.usbmodem101` today. if it errors with "could not open port",
   check `ls /dev/cu.usbmodem*` — it sometimes flips to `...1101` on replug — and
   update `PORT` in `follow.py`.

## expect it to be jerky and overshoot — that's correct

the neck will snap around, overshoot my face, and jitter when i hold still. **do not
smooth it. do not add damping.** that mess is exactly the problem day-15's PID exists
to solve, and the PID is mine to write by hand — so leaving the mess here is the
point. smoothing it now would rob tomorrow of its reason to exist.

## done when

the neck **visibly follows my face**, however badly. face left, it tracks left.
ugly counts as done.
