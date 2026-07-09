// 3led-hold — HOLD the button to cycle the LEDs, RELEASE to stop instantly.
//
// while the button is held: red -> blue -> green cycle, 2s each.
// the moment you let go: all LEDs go off immediately.
//
// stays instant because loop() never blocks on delay() — it checks the button
// every pass and uses millis() to time the color changes (the day-1 pattern).
//
// button wiring: one leg -> pin 2, diagonal leg -> GND. internal pull-up,
// so a pressed button reads LOW.

const int redPin    = 13;   // red LED (also lights the on-board LED)
const int bluePin   = 12;   // blue LED
const int greenPin  = 11;   // green LED
const int buttonPin = 2;    // pushbutton

const unsigned long interval = 2000;   // ms each color stays on

unsigned long phaseStart = 0;   // when the current color started
int phase = 0;                  // 0 = red, 1 = blue, 2 = green

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {           // held -> cycle the colors
    if (millis() - phaseStart >= interval) {     // time for the next color?
      phaseStart = millis();
      phase = (phase + 1) % 3;                    // red -> blue -> green -> red
    }
    digitalWrite(redPin,   phase == 0 ? HIGH : LOW);
    digitalWrite(bluePin,  phase == 1 ? HIGH : LOW);
    digitalWrite(greenPin, phase == 2 ? HIGH : LOW);
  } else {                                        // released -> all off, reset to red
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
    phase = 0;
    phaseStart = millis();
  }
}
