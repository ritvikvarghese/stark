# project stark

*one person, 60 working days, zero to a robot arm that learned to tidy a desk by watching me. every day documented in public, failures included.*

i have always wanted to build physical machines. this is me doing it in the open, from a cheap arduino starter kit to a robot arm that learns, with claude as a full-time pair. the shape of the project changed once i understood the field: value in robotics has moved out of the machine and into the learning and deployment layer. five scattered builds prove curiosity; one arm taken from zero to a published reliability curve proves capability. so this is two builds, not five, and most of the calendar goes to the hard part — teaching the arm. everything is at `/log` with real timestamps, nothing cleaned up.

---

## the two builds

it looks like two projects but it's really one loop — sense the world, decide, move — built once small and once for real. the small one teaches every skill the big one needs, then films it.

1. **the video robot.** a webcam on a motorized neck that follows my face, listens, and records on command. i say "start recording," it films me and keeps me centered; i say "i'm done," it stops and saves the clip. a complete sense-think-act loop with ears. it teaches vision, servos, serial, pid, and voice, and then becomes the camera crew for the rest of the project — it films every demo in this repo, including the arm.

2. **the desk organizer.** the so-101 arm pair, a desk-lamp-sized pair of 6-joint arms. i build both, then puppet the main one with a lighter twin to record 100+ demonstrations of tidying real desk objects into a tray. i train an imitation policy on my own recordings, then push it up a difficulty ladder — one pen, then three object types, then clutter, then objects it has never seen — publishing a reliability curve and a failure taxonomy at every level. the headline artifact of this repo is a graph, not a demo clip.

---

## demos

*(filled in as they ship. each is 30 to 90 seconds: the machine working, then me explaining it on camera.)*

- [ ] day 10: soldered gadget + electronics layer explained
- [ ] day 24: video robot demo (it records the demo of itself) + see-think-move explained
- [ ] day 38: arm scripted pick + teleop + the geometry explained
- [ ] day 60: the reliability curve + failure taxonomy + the full story

---

## the phases

day numbers are working days, one rest day per 6, so ~60 working days is roughly 70 calendar days. the full day-by-day lives in `/course/` (private); the public map is `roadmap.md`.

| phase | days | outcome |
|---|---|---|
| 1 — fundamentals sprint | 1-10 | io, pwm, serial, a timed sensor, two servos, solder. days 1-3 done |
| 2 — the video robot | 11-24 | a see-think-move-listen unit i can explain line by line |
| 3 — the arm, classical | 25-38 | both arms assembled, calibrated, commanded with math i derived |
| 4 — the desk organizer learns | 39-60 | the reliability loop: datasets, training, evals, the curve |

---

## small glossary

- **microcontroller**: a tiny cheap computer on one chip (the arduino) that runs a single program forever and controls electronics directly
- **firmware**: the program that lives on the microcontroller
- **breadboard**: a plastic board with holes for building temporary circuits, no soldering
- **servo**: a small motor you command to a specific angle
- **pwm**: switching power on and off very fast to control brightness or speed
- **pid**: the standard recipe for "how hard should i correct my error," tuned by hand
- **cad**: designing 3d parts in software before printing them
- **kinematics**: the geometry of an arm. if i want the hand there, what angle is each joint
- **imitation learning**: training a robot by showing it demonstrations instead of programming rules
- **imitation learning ladder**: teaching the same task at rising difficulty — one object, then several, then clutter, then unseen objects — and measuring reliability at each rung
- **episode**: one recorded demonstration, or one attempt of the task, start to finish
- **policy**: the trained model that maps what the cameras see to what the joints do
- **teleoperation**: driving the follower arm live by moving the leader arm by hand — how the demonstrations get recorded
- **failure taxonomy**: the fixed buckets every failed attempt is sorted into — perception, grasp, trajectory, release — so failures are countable, not anecdotal
- **eval protocol**: the frozen rules for testing a policy — placement grid, what counts as success, trials per eval, no mid-run interventions — set once so the numbers compare across days

---

## repo structure

two layers. polish on top, raw underneath. the raw layer is the proof: learning speed is only believable when the struggle is visible and timestamped.

```
/README.md          <- this file, the front door
/roadmap.md         <- the public phase map + checkpoints
/CLAUDE.md          <- agent pairing rules (private, local only)
/course/            <- day-by-day plan, private (local only)
/log/               <- daily entries, raw, failure photos included
/projects/
    /01-fundamentals/   <- phase 1 arduino programs
    /02-video-robot/    <- the video robot (python + firmware)
    /03-rover/          <- cut in v4 (tombstone; pid moved into the video robot)
    /04-arm/            <- so-101 code, calibration, geometry, teleop
    /05-learning/       <- the desk organizer: datasets, training, evals, results
/writeups/          <- one short post per phase (four total)
/media/             <- demo videos, build photos
```

log rules: every working day gets an entry even if it's three lines. what i built, what broke, what i learned. commit daily so the graph tells the story. never clean up history, never delete a failed approach — tombstone it and say why. one rest day per 6.

---

## how i work each day

everyday, i work with claude on this repo. it reads `CLAUDE.md` and the day's entry in `/course/`, then works as a full pair programmer: brief me, build with me, unblock me fast.

1. it gives me the day's brief: goal, build steps, theory block, checkpoint
2. i build, hands on hardware for most of the session, the agent writing and debugging code alongside me
3. when stuck, i ask. the agent explains the concept, we write the code together, and we keep moving
4. end of day i write my own log entry, commit, push

daily starter prompt:

```
read CLAUDE.md and course/ for day N. give me today's brief: goal,
build steps, theory block with the exact resource, and the checkpoint
i must hit. then help me build it: write code, explain the parts that
are new to me as we go, and keep me moving.
```

---

## changelog

fin.
