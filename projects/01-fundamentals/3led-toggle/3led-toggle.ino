// 3led-switch — click the button to START the color cycle, click again to STOP.
//
// this is a TOGGLE: each press flips a running/stopped state. while running,
// red -> blue -> green cycle (2s each, non-blocking). while stopped, all off.
//
// two ideas make a clean toggle:
//   edge detection — act only on the moment of press (HIGH -> LOW), not the
//     whole time it's held, so one press = one toggle.
//   debouncing — a button's contacts bounce for a few ms; we ignore changes
//     until the reading is stable, so one click isn't read as several.
//
// button wiring: one leg -> pin 2, diagonal leg -> GND. internal pull-up,
// so a pressed button reads LOW.

const int redPin    = 13;   // red LED (also lights the on-board LED)
const int bluePin   = 12;   // blue LED
const int greenPin  = 11;   // green LED
const int buttonPin = 2;    // pushbutton

const unsigned long interval     = 2000;   // ms each color stays on
const unsigned long debounceDelay = 50;    // ms the reading must be stable

bool running = false;          // is the cycle currently running?
int phase = 0;                 // 0 = red, 1 = blue, 2 = green
unsigned long phaseStart = 0;  // when the current color started

int lastReading = HIGH;              // previous raw button reading
int buttonState = HIGH;              // debounced, stable button state
unsigned long lastDebounceTime = 0;  // when the raw reading last changed

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // --- read + debounce the button ---
  int reading = digitalRead(buttonPin);
  if (reading != lastReading) {
    lastDebounceTime = millis();          // raw reading changed -> restart the timer
  }
  if (millis() - lastDebounceTime >= debounceDelay) {
    // the reading has held steady long enough, so trust it
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {           // a fresh press (HIGH -> LOW)
        running = !running;               // TOGGLE start/stop
        phase = 0;                        // always begin the cycle at red
        phaseStart = millis();
      }
    }
  }
  lastReading = reading;

  // --- run the cycle, or hold everything off ---
  if (running) {
    if (millis() - phaseStart >= interval) {
      phaseStart = millis();
      phase = (phase + 1) % 3;            // red -> blue -> green -> red
    }
    digitalWrite(redPin,   phase == 0 ? HIGH : LOW);
    digitalWrite(bluePin,  phase == 1 ? HIGH : LOW);
    digitalWrite(greenPin, phase == 2 ? HIGH : LOW);
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
  }
}
