# day 9 — 2026-07-21

**goal:** take the day-5 breadboard parking sensor and make it permanent — solder the `ultrasonic-2` circuit onto perfboard and run it as a standalone gadget off a 9V battery.

## what i built
- the full parking sensor, **soldered permanent** on a fresh perfboard: HC-SR04 in a 4-pin female header socket, LED + resistor indicator, everything routed by hand. same circuit as day-5 `ultrasonic-2` (VCC→5V, trig→12, echo→11, LED on pin 6), just permanent instead of on a breadboard.
- built it in **halves and tested each** — the LED/indicator half first (blink test on pin 6 → confirmed lit), then added the sensor half once the female header arrived. isolating the halves meant any fault had a small place to hide.
- it runs **standalone off a 9V battery** (red→Vin, black→GND), no laptop. that's the day-9 gadget.

## what broke
- the sensor read **distance = 0, constantly**, and the LED was stuck on. realized the stuck LED was just a symptom (`0 < 10` is always true), so the real bug was the zero.
- since the sensor + code both worked on day 5, the fault had to be in my **new solder joints**. it was: **echo wasn't actually connected to pin 11** — a cold joint that looked soldered but wasn't passing current. `pulseIn` never saw the echo pulse, timed out, returned 0.
- found it with the multimeter's **continuity mode** — beeped fine on trig→12, dead silent on echo→11. reflowed that joint with a bit of flux, got the beep, and it worked. (wrote up the continuity theory separately in `theory-notes/electronics/continuity.md`.)

## what i learned
- **continuity testing is how you find invisible breaks.** a cold joint can look perfectly soldered and still not conduct — your eyes can't tell, but the beep can. that's exactly how i pinned the echo joint.
- **the code lives on the chip, not the laptop.** uploading over USB burns the sketch into the Arduino's flash permanently; the battery just supplies power and it runs the stored sketch on its own. USB is for uploading, not running.
- **let the symptom point you.** distance = 0 → `pulseIn` timed out → echo never arrived. one clean thread from symptom straight to the exact joint. and check power/connections before touching code.

## what i'm struggling with (honest)
- **my soldering isn't clean yet.** the joints aren't pretty and some of them break — that's what caused the echo fault. first-permanent-build reality; it'll come with reps.
- **the wiring is a real fight.** the solid-core hookup wire is thicker and stiffer than what seats nicely in the Arduino headers. jumper wires fit perfectly, but this wire is hard to get in even after tinning the ends, so i end up with loose connections and too much exposed copper. need a better approach — thinner wire, or put jumper-style ends on the board side.
- overall the connections aren't as strong as they should be. i know it'll come with practice.

## clips / photos

https://github.com/user-attachments/assets/08b76b24-8b6f-4c48-a061-6b4b4ae600f6

<img width="3024" height="4032" alt="IMG_7390" src="https://github.com/user-attachments/assets/a3ad3611-0a0a-4275-aec7-770b340e1fe6" />
