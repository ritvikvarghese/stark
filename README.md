# project stark

*90 days of mechatronics.*

**one person, 90 working days, zero to a robot arm running a learned policy. every day documented in public, failures included.**

this repo is a self built course. i start with a cheap arduino starter kit and math i last touched 8 years ago. i end with four working machines: a camera that turns to follow my face, a small car that steers itself along a line, a robot arm i printed and assembled myself, and that same arm doing a task it learned by watching me demonstrate it. everything in between, the wiring mistakes, the failed prints, the debugging sessions, lives in `/log` with real timestamps.

if you're a recruiter or hiring manager: watch [the demos](#demos) and skim the five short writeups in `/writeups`. that's the 90 second version.

if you're trying to learn this yourself: the whole course is below. steal it.

---

## the five builds, in plain words

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

so nobody has to google mid read:

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

every morning i open claude code in this repo. it reads `CLAUDE.md` and the day's entry in `/course/`, then works as a full pair programmer: brief me, build with me, unblock me fast.

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

## the rules i hold myself to

**acceleration policy.** i'm fluent with ai coding agents and new to c++, so i use them the way i actually work: as a pair programmer from day 1. agents write, scaffold, and debug across every phase. my bar is understanding, not authorship. i ship fast and make sure i can explain what each system does and why, because the role i want is explaining these systems to humans. how the code got typed matters less than whether i understand it.

**check power first.** most hardware bugs are power problems. measure the voltage before blaming the code, every single time.

**just in time math.** no math courses. small modules of 2 to 4 hours injected exactly when a project needs them: triangle math for the tracker, rate of change intuition for pid, vectors and matrices for the arm, basic probability for the learning week. plus a standing drip: from week 5 onward, one short 3blue1brown linear algebra video every second or third evening, so the arm math arrives as review instead of cold.

**one full rest day per week.** non negotiable. 90 working days is about 15 weeks, call it 105 calendar days. a plan abandoned at day 40 is worth less than one finished at day 105. day numbers below are working days.

**everything public from day 0.** the empty public repo on day 0 is the commitment device.

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

why this order: you can't design parts before you can cad, can't cad usefully before you can measure and print, can't do arm geometry before you understand motors and vectors, and can't appreciate a learned policy before you've built a control loop by hand. each phase feeds the next. the tracker sits mid course on purpose: it's the first thing that feels alive, placed right where motivation usually dips.

---

## risks, called in advance

- **shipping blocks progress.** mitigation: phase 1 needs only the starter kit, orders are phased, the arms land three weeks before the bench needs them
- **print failures.** mitigation: the p2s auto calibrates, extra filament from day 0, arm prints run overnight with a week of slack
- **math avoidance.** mitigation: modules stay under 4 hours, always tied to a part on the bench, and the evening drip makes the scariest block arrive as review
- **burnout.** mitigation: one real rest day a week, and an honest calendar of ~105 days instead of pretending 90 straight
- **optimism about hardware.** mitigation: arm assembly gets three days not one, days 51, 56, 57, and 89 are explicit overflow, day numbers are sequence not calendar
- **overclaiming.** the frame in every interview: i built these to understand what your engineers do, not to claim i am one. the fastest way to torch this portfolio is inflating it in a technical screen, the second fastest is shipping systems i can't explain, so i lean on agents to build fast and make sure i understand what i built
- **scope creep.** the skip list (in my private plan) is law. new ideas go in a `later.md`, not in the plan

---

## changelog

**v4 (this version):** acceleration pass. ai coding agents are now a full pair programmer from day 1 instead of a restricted tutor: dropped the phase 1 firmware ban, the "explain every line before it flashes" gate, the 30/30 rule, and the handwritten-forever mandate on the pid class and arm geometry. rewrote CLAUDE.md, the handwriting policy (now the acceleration policy), and the risk section to match. the credibility bar shifts from "i handwrote it" to "i built it fast and can explain it."

**v3:** plain language pass throughout so a beginner can read it cold, added the glossary and the five builds section, and settled the printer and phased-orders decisions (details in my private plan).

**v2:** leader arm added (keyboard teleop makes bad training data). one rest day per week, honest ~105 day calendar. linear algebra drip from week 5 evenings. arm assembly expanded to 3 days plus overflow. esp32 block compressed from 5 days to 3. pca9685 demoted to a 1 hour detour. self balancer made optional. cleanrl cut to a half day. everything public from day 0 with the two layer repo, five writeups, five recorded explanations, and filming scheduled as real days.

**v1:** original 90 day plan.
