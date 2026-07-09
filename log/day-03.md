# day 3 — 2026-07-09

**goal:** learn analog input and analog output. read a real voltage into the arduino (analog read) and dim a light with PWM (analog write). math: ohm's law / voltage divider.

## what i built
- a voltage divider on the breadboard: 5V from the arduino into the board, two resistors in series (330Ω then 220Ω), a jump wire closing the circuit to ground, and a jump wire from **A3** to the junction between the two resistors. that middle point sits at a fixed 2V, and the arduino reads it with `analogRead`. sketch is `analog-read-1`.
- i didn't have a potentiometer today, so the fixed resistor divider stood in as my analog input — a steady voltage instead of a knob i can turn. i'm picking up a pot tomorrow to do the real "turn a knob, dim a light" version and i'll add it on top of this log.
- **analog write (PWM):** dimmed an LED by writing values 0–255 to a pin. tried fixed brightness levels and a 5-step sequence that cycles through brightness. sketch is `analog-1`, video below. this maybe wasn't strictly on today's list but i did it and it fits the "analog" theme, so it's in.

## what broke
- uploads kept failing with `not in sync` — the board just wouldn't take the new code. turned out the USB serial connection had wedged; unplugging the cable and plugging it back in fixed it.
- the big confusing one: the analog read looked completely dead, no numbers showing up at all — even though the arduino was reading and printing fine the whole time. the giveaway was the **TX light blinking once a second**, which is literally the board sending data down the cable. so the board was never the problem. the problem was on the laptop side: the tool reading the serial port kept snapping back to the wrong baud rate, so it read garbage or nothing. claude finally locked the baud rate correctly and the numbers came through.
- at first A3 read a flat **0**. the tap wire was sitting on the ground side of the divider instead of on the junction between the two resistors. moved it up to the junction and it jumped to the right value.

## what i learned
- **ohm's law / voltage divider:** two resistors in series split the 5V in proportion to their size. the 330Ω drops 3V, the 220Ω drops 2V, and they add back to 5V. i checked it on the multimeter and it matched.
- **analogRead gives a number, not volts.** it's a 0–1023 scale (10-bit): 0 means 0V, 1023 means 5V. to turn it into real voltage: `voltage = reading / 1023 × 5`. my reading of 414 came out to **2.02V** — same as the multimeter's 2V. that conversion (turning the chip's internal scale into volts i can actually understand) was the click moment of the day.
- **the int vs float trap:** if you write `(5 / 1023)` as plain integers, it divides down to 0 and your voltage is always 0. you have to write `5.0 / 1023.0` and store the result in a `float`. that's the whole reason paul splits the code into `readval` (the raw number) and `V2` (the real voltage).
- both analog **read** and analog **write** are done. the knob + LED version is tomorrow.

## clips

https://github.com/user-attachments/assets/7f760f3f-fbec-4146-95f3-0cb343952909

## photos

![two-resistor voltage divider into A3](../media/day-03/two-resistors.jpg)
