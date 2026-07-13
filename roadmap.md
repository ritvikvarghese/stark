# roadmap

*two builds, 60 working days, zero to a robot arm that learned to tidy my desk by watching me.*

the public phase map. the private day-by-day lives in `/course/` (local only). day numbers
are working days, one rest day per 6, so ~60 working days is roughly 70 calendar days.
days 1-3 are already done (see `/log`): blink, buttons + leds, analog read + pwm.

## the two builds

- **the video robot.** a webcam on a motorized neck that follows my face, listens, and
  records on command: i say "start recording," it films me and keeps me centered; i say
  "i'm done," it stops and saves the clip. a full sense-think-act loop with ears. it
  teaches every skill the arm needs — vision, servos, serial, pid, voice — and then films
  every demo in this repo, including the arm.
- **the desk organizer.** the so-101 arm pair. i build both arms, puppet the main one with
  a lighter twin to record 100+ demonstrations of tidying real desk objects into a tray,
  train an imitation policy on my own recordings, then push it up a difficulty ladder —
  one pen, three object types, clutter, objects it has never seen — publishing a
  reliability curve and a failure taxonomy at every level. the headline artifact is a
  graph, not a demo clip.

## the phases

| phase | days | what gets built |
|---|---|---|
| 1 — fundamentals sprint | 1-10 | io, pwm, serial, a timed sensor, two servos, soldering. days 1-3 done |
| 2 — the video robot | 11-24 | a see-think-move-listen unit i can explain line by line |
| 3 — the arm, classical | 25-38 | both arms assembled, calibrated, hand-commanded with math i derived |
| 4 — the desk organizer learns | 39-60 | the reliability loop: datasets, training, evals, the curve |

## checkpoints (each filmed, each shipped)

- [ ] day 10 — soldered gadget + the electronics layer explained
- [ ] day 24 — video robot demo, filmed by the robot itself, + see-think-move explained
- [ ] day 38 — arm scripted pick + teleop + the geometry explained
- [ ] day 60 — the reliability curve + failure taxonomy + the full story, front door live

## the rules

- every working day gets a log entry, even three lines: what i built, what broke, what i learned.
- commit daily so the graph tells the story. never delete a failed approach — tombstone it and say why.
- one rest day per 6. non-negotiable, the calendar is compressed enough already.
