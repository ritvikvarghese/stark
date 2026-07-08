// blink-millis — blink the on-board LED WITHOUT delay(), using the clock.
//
// same visible behavior as blink.ino, but the loop never freezes. instead of
// "wait 250ms", it checks the clock every pass and flips the LED only when
// enough time has gone by. this is the non-blocking pattern you'll reuse
// everywhere later (e.g. read a sensor AND blink at the same time).

const int ledPin = LED_BUILTIN;       // pin 13, the on-board LED
const unsigned long interval = 250;   // ms between flips — change this to change the rate

unsigned long previousMillis = 0;     // the moment we last flipped the LED
int ledState = LOW;                   // the LED's current state (LOW = off, HIGH = on)

void setup() {
  pinMode(ledPin, OUTPUT);            // pin 13 is an output — runs once
}

void loop() {
  unsigned long currentMillis = millis();   // read the clock: ms since the board booted

  // has 'interval' ms passed since the last flip?
  // (writing it as a subtraction keeps working even when millis() rolls
  //  over back to 0 after ~49 days — the canonical, correct form.)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;                  // reset the timer to now
    ledState = (ledState == LOW) ? HIGH : LOW;       // flip: off->on or on->off
    digitalWrite(ledPin, ledState);                  // apply the new state to the pin
  }

  // loop() keeps spinning freely down here — nothing is frozen. you could do
  // other work in this space and the blink would still keep perfect timing.
}