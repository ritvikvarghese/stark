# day 7 — 2026-07-16 (finished 2026-07-18)

**goal:** the power/brownout lesson on purpose — run a big servo off USB, watch the board brown out, then fix it with a separate supply and build the pan/tilt neck. **the lesson happened on the 16th; the fix + neck waited on parts and got finished on the 18th.**

## part 1 — the brownout, on my own bench (done the 16th)
wired one **MG996R** (the big metal-gear servo) straight off the Arduino's USB 5V — deliberately the wrong way — and ran the sweep on it.
- **unloaded, it swept fine.** a free-running servo only sips current, so USB coped.
- **the moment i stalled it** (pinched the horn so the motor had to fight), it drew hard, the **5V collapsed, and the board's self-resetting fuse (polyfuse) tripped** — the servo went dead, then would **move a bit and just sit there buzzing**. that buzz is a starving servo: energized, commanded to move, but without the current to actually do it.
- so: **the Arduino physically cannot power an MG996R.** USB is fused at ~0.5A; the servo wants ~2.5A at stall. that mismatch *is* the whole lesson, and i watched the protection kick in to save the board.

a sneaky second proof: while the servo's power wire was connected, **the board wouldn't even accept a new upload** — "programmer not in sync." the servo was loading the rail during the reset-into-bootloader, so the flash couldn't sync. pull the servo's red wire → uploads instantly.

## what i learned about power
- **back-EMF / the current spike:** a spinning motor coil is also a generator whose voltage opposes the supply — but **at startup and stall there's no back-EMF yet**, so nothing limits the current and it gulps a huge spike. that spike dips the shared rail below what the microcontroller needs → reset. that's exactly why motors get their own supply.
- **polyfuse = resettable protection.** it trips and cools back, doesn't blow. nothing was damaged.
- volts vs amps: **both the Arduino and the wall supply push 5V** — the difference is how many *amps* they can deliver. it was never a voltage problem, it was a current problem.

## part 3 — the fix (done the 18th)
the parts finally came: a **5V 3A wall supply**, the **dc barrel-jack screw-terminal connector** to tap it onto the breadboard solder-free, and the inline jack.
- fed the servo's **red off the separate 5V rail**, kept the **signal on pin 9**, and **tied the grounds** (supply GND ↔ Arduino GND on the − rail — without that common ground the servo can't read the signal).
- multimetered the rail first to confirm ~5V before connecting anything (an MG996R cooks above ~6V).
- re-ran the sweep and **stalled it again** — this time the rail held. no polyfuse trip, no buzz, just the motor pushing against my hand. **same stall, opposite outcome.** that contrast is the proof the fix works.
- later re-confirmed it with **two** servos on the rail at once (the neck) — held steady, no brownout.

## part 4 — the pan/tilt neck (done the 18th)
mounted both MG996R perpendicular: **pan** at the bottom (spins left/right), **tilt** on top (nods up/down). then wrote two sketches:
- **`servo-4`** — type `p120` / `t45` in the serial monitor to aim pan or tilt. read the letter with `Serial.read()`, the angle with `parseInt()`, `constrain(0,180)`, write to the right servo. (learned the hard way: you can't glue a `char` and a text literal with `+` — that's pointer math, not concatenation. wrap it in `String()`.)
- **`servo-5`** — tilt windmills forever on its own while i still steer pan by typing. the trick is the tilt sweep runs on **`millis()` not `delay()`**, so it never blocks the serial reading — both happen at once. (if i'd used `delay()`, pan would freeze every sweep.)

## what actually broke — the mechanics (honest)
the code was intuitive and the wiring was easy — i'm solid at wiring now. **the whole fight today was mechanical.**
- **the terminology was all new.** pan, tilt, horn, carrier, cradle — figuring out which bracket does what and how they stack took most of the session.
- **the screws don't fit.** most of the screws i have don't go into the tiny horn holes, so i couldn't tighten the joints properly. everything ended up **loose**.
- **loose joints won't hold.** after even 3–5 minutes of running, the **pan horn works itself loose** and stops executing commands — i'd send it to an angle and it just wouldn't go, because the joint had slop and wasn't transmitting the servo's torque.
- **the arm killed the balance.** the tilt servo is fine as-is (no arm on it yet), but the moment i tried to add an arm, the **weight on a long lever + the shifted center of mass** made the whole thing lose balance, and the loose pan joint couldn't hold it upright anymore.

**the mechanics i now understand:** torque = force × how far out the weight sits (a long arm multiplies the load), the center of mass has to sit over the pan axis or it tips, and a **loose joint wastes the servo's torque in the slop** — the motor isn't weak, the connection is. it's a preview of arm dynamics (why gravity compensation exists), met early by feel.

## what's next
the looseness is a **hardware-supply problem, not a design one** — i need the right small screws (or a better way to lock the horns) to get rigid joints. over the next few days i'll sort the screws, keep the payload close to the axis, and probably watch a few other people's pan/tilt bracket builds to see how they solve the tightness. added proper micro screws to the shopping list.

honest status: a great *learning* day. i proved the power fix end to end, built a two-servo neck, and wrote non-blocking code that drives both at once — and i hit a real mechanical wall (loose joints) that i understand now and know how to fix.

## clips / photos

https://github.com/user-attachments/assets/781cc445-ebf3-46e2-ba15-0b502aaeeca0

https://github.com/user-attachments/assets/08c572dc-ccd4-4ef5-9e17-930a6d09d9e8

https://github.com/user-attachments/assets/86ad595c-777e-4860-b569-4feb8db0aec7

<img width="3024" height="4032" alt="day-07-1" src="https://github.com/user-attachments/assets/4f1211f3-6460-45ee-b644-27c63296266a" />

<img width="3024" height="4032" alt="day-07-2" src="https://github.com/user-attachments/assets/f5ad8177-2399-4f08-bc7e-83e7b6d78af3" />
