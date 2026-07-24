# day 14 — 2026-07-24

**goal:** close the loop. camera finds my face, servo moves so the neck follows me. this was supposed to be the easy wiring day. it was the hardest day so far.

## the build (and the tilt servo i had to kill)
setup was mostly ready from yesterday. i started with **both pan and tilt servos** stacked into a neck. then i realized the tilt was useless — i'd mounted it so it spins in a 180° circle just like the pan does, not up/down like an actual neck. it wasn't tilting, it was just a second pan. no point, so i **removed the tilt entirely** and went pan-only.

the other problem was purely physical: there was no legit way to attach the camera to the servo. i ended up using zip ties (the tying straps) for the camera. and i had no base — the pan servo needs something heavy to sit on and hold the whole neck up, and i couldn't 3D print one and didn't have a part for it. i found a **solid metal laptop stand**, strapped the pan servo onto that, and that became the base. circuit complete, rig standing on its own.

## what broke (a lot)
this is where the day went sideways. once it was wired up and running:
- **first attempts:** my face would just slide off-screen and it would not follow me. the servo swung off to one side and lost me.
- **then it flipped the other way:** it wouldn't move at all, or it'd shoot straight to a limit and sit there.
- we tried a lot — flipping the direction, changing the gain, slowing it down, an aiming step, even checking if the servo was damaged. nothing actually fixed it. it felt random.

4-5 hours in, i was about ready to give up.

## how i actually solved it (debug end-to-end)
instead of guessing, i decided to isolate it piece by piece.
- **laptop test:** wrote a separate python script that uses the **laptop's own camera** (which doesn't move) to drive the servo. this worked. the trick was killing the latency — dropped the video quality (smaller frames), cranked the smoothness up to ~0.9 so it's snappy and near-instant, kept pan min/max at 30 and 150. suddenly it tracked me fine.
- **isolate the ZEB:** ran the same script on the ZEB camera but held **static**, off the neck. worked too. so the camera, the math, the servo — all fine.
- that proved it: the only thing that broke it was the camera **riding the servo** (the closed loop), plus lag.
- **then rebuilt the real script (follow1)** to match what made the laptop/ZEB tests work — all the low-latency stuff. put the camera back on the neck. and it worked. it now follows my face almost instantly.

## what the problem actually was
**latency was the whole thing.** underneath it was a traffic jam: the arduino was reading commands slowly and python was firing them faster than they could be handled, so they piled up — the servo was basically acting on where my face was ~15 seconds ago. no closed loop can survive that. once i fixed the plumbing (faster firmware, fewer/smaller frames, don't flood the wire), the exact same setup that failed all day just worked. 

## checkpoint — hit
camera on the neck, closed loop, follows my face in near real-time. jerky on fast moves, but it holds and re-centers. that's day 14 done.

## honest note
this was brutal — 4-5 hours of debugging and a lot of code i didn't write myself. i'm okay with that. i'm not going to learn every line at this point and there's no real reason to; what i'm proud of is that i **engineered** the thing and pushed it until it worked. that's the part that counts to me.

## videos/images
version 1: 

<img width="484" height="443" alt="Screenshot 2026-07-24 at 8 32 31 PM" src="https://github.com/user-attachments/assets/1099282c-57e8-47de-8b24-e51d8d27ec10" />

version 2:

<img width="3024" height="4032" alt="IMG_7411" src="https://github.com/user-attachments/assets/709b0d4d-c8d1-442b-a892-34ff038af7d6" />

videos:

https://github.com/user-attachments/assets/c5e73c92-3480-4683-8528-0b7edfb8b075

https://github.com/user-attachments/assets/4cd1d2c9-6e30-466b-9fe5-6b995fc22090

https://github.com/user-attachments/assets/6143a451-a6b0-463d-b645-f2094d3220f1
