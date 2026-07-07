# project stark

*90 days of learning mechatronics and building things.*

starting with a cheap arduino starter kit and claude, i plan to to build 4 working machines: a camera that turns to follow my face, a small car that steers itself along a line, a robot arm i printed and assembled myself, and that same arm doing a task it learned by watching me demonstrate it.  follow everything at `/log` with real timestamps.

---

## the five thing i'm planning to build 

the course looks like five projects but it's really one idea built five times, each time with one new layer. every robot on earth runs the same loop: sense the world, decide what to do, move. i build the smallest honest version of that loop, then keep upgrading it.

1. **warmups (weeks 1 to 3).** tiny exercises with the starter kit. make a light blink. make a button work. make a knob dim a light. make a distance sensor beep faster as your hand gets closer, like a car parking sensor. make a small motor turn to an exact angle. each takes a day and teaches one skill: wiring things without frying them, and writing the small programs that control them. at the end i solder one project together permanently so it works without a laptop, a real gadget instead of a pile of wires.

2. **the face tracker.** a webcam on a small motorized neck. i walk left, it turns left. i stand up, it tilts up. my laptop finds my face in the video, works out "he's too far right," and tells two motors to nudge the camera over. this see, think, move loop is the skeleton of every robot ever made. first real demo.

3. **the line follower.** a little car that drives itself around a black tape track on the floor, correcting when it drifts. the lesson is the correcting: steer too gently and it wanders off, too hard and it wobbles like a drunk. tuning that correction is a famous engineering idea called pid, and it's inside thermostats, drones, and cruise control. i tune it by hand and watch the wobble disappear.

4. **the robot arm.** the so-101, a desk lamp sized 6 joint arm. the plastic skeleton comes off my 3d printer, the joints are smart motors from a kit, i bolt it together and then command it with math i derived myself: draw a square in the air, pick up a block and place it. i actually build two arms, the main one plus a lighter twin. move the twin by hand and the main arm copies me live, like a puppet. that puppet setup is not a toy, it's how build 5 gets its data.

5. **the learned policy.** in build 4 i programmed the arm step by step, like a recipe. here i do something different: i physically demonstrate the pick task with the puppet arm about 50 times while two webcams record. i feed the recordings to a training program, and the arm learns to attempt the task on its own by imitating me. it will be clumsy, 50 demos is tiny, and that clumsiness is the honest lesson about how modern robot learning actually works. this demonstrate, record, train, run pipeline is what the current wave of robotics companies is built on.

---

## demos

*(filled in as they ship. each is 30 to 90 seconds: the machine working, then me explaining it on camera.)*

- [ ] day 21: soldered gadget + explanation of the electronics layer
- [ ] day 40: face tracker + explanation of the see think move loop
- [ ] day 58: line follower + explanation of feedback control
- [ ] day 82: arm doing scripted pick and place + explanation of the geometry
- [ ] day 90: arm running the learned policy + the full 90 day story

---

## small glossary

- **microcontroller**: a tiny cheap computer on one chip (the arduino) that runs a single program forever and controls electronics directly
- **firmware**: the program that lives on the microcontroller
- **breadboard**: a plastic board with holes for building temporary circuits, no soldering
- **servo**: a small motor you command to a specific angle
- **stepper**: a motor that moves in precise fixed clicks, good for exact positioning
- **pwm**: switching power on and off very fast to control brightness or speed
- **pid**: the standard recipe for "how hard should i correct my error," tuned by hand
- **cad**: designing 3d parts in software before printing them
- **kinematics**: the geometry of an arm. if i want the hand there, what angle is each joint
- **imitation learning**: training a robot by showing it demonstrations instead of programming rules

---

## repo structure

two layers. polish on top, raw underneath. the raw layer is the proof: learning speed is only believable when the struggle is visible and timestamped.

```
/README.md          <- this file, the front door
/CLAUDE.md          <- agent pairing rules (private, local only)
/course/            <- day-by-day plan, kept private (local only)
/log/               <- daily entries, raw, failure photos included
/projects/
    /01-fundamentals/   <- phase 1 programs
    /02-tracker/        <- face tracker (python + firmware)
    /03-rover/          <- pid line follower
    /04-arm/            <- so-101 code, calibration, geometry, teleop
    /05-learning/       <- mujoco experiments, lerobot configs
/writeups/          <- one short post per phase
/media/             <- demo videos, build photos
```

log rules: every working day gets an entry even if it's three lines. what i built, what broke, what i learned. commit daily so the graph tells the story. never clean up history, never delete a failed approach, move it to the log and say why it failed.

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

## phase map

| phase | days | what happens | ships publicly |
|---|---|---|---|
| 0 | day 0 | orders placed, laptop set up, repo goes public | this readme, first log entry |
| 1 | 1-21 | electronics and firmware basics on the starter kit | soldered gadget demo, writeup 1 |
| 2 | 22-40 | cad, 3d printing, the face tracker | tracker demo, writeup 2 |
| 3 | 41-58 | pid control with the line follower, a taste of the esp32 | rover demo, writeup 3 |
| 4 | 59-82 | arm geometry + building both so-101 arms | arm demos, writeup 4 |
| 5 | 83-90 | simulation, robot learning, portfolio front door | learned policy demo, writeup 5 |

---

## changelog
