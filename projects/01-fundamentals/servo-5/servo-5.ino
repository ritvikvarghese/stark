// servo-5 — tilt windmills on its own while you aim pan from serial
//
// wiring (same as servo-4, both off the external 5V rail):
//   pan  signal -> pin 9   tilt signal -> pin 10
//   both RED -> +5V rail    both BROWN -> - rail    Arduino GND -> - rail
//
// behaviour: tilt sweeps back-and-forth forever (windmill); type p<angle>
// in the Serial Monitor (e.g. p120) to aim the pan servo whenever you like.
//
// key idea: the tilt sweep uses millis() (NOT delay) so it never blocks the
// serial reading — that's how pan stays responsive while tilt keeps moving.

#include <Servo.h>

Servo pan;
Servo tilt;
const int panPin = 9;
const int tiltPin = 10;

// tilt windmill state (non-blocking sweep)
int tiltAngle = 0;
int tiltStep = 2;                    // degrees moved per update (bigger = faster)
unsigned long lastTiltMove = 0;
const unsigned long tiltInterval = 10;  // ms between updates (smaller = faster)

void setup() {
    Serial.begin(9600);
    pan.attach(panPin);
    tilt.attach(tiltPin);
    pan.write(90);                   // pan starts centered
    tilt.write(tiltAngle);           // tilt starts at 0 and begins sweeping
    Serial.println("servo-5: tilt windmills; type p<angle> to aim pan, e.g. p120");
}

void loop() {
    // 1) keep the tilt sweeping like a windmill, without blocking serial
    if (millis() - lastTiltMove >= tiltInterval) {
        lastTiltMove = millis();
        tiltAngle += tiltStep;
        if (tiltAngle >= 180 || tiltAngle <= 0) {
            tiltStep = -tiltStep;              // hit an end -> reverse direction
            tiltAngle = constrain(tiltAngle, 0, 180);
        }
        tilt.write(tiltAngle);
    }

    // 2) listen for pan commands the whole time
    if (Serial.available()) {
        char cmd = Serial.read();
        if (cmd == 'p') {
            int angle = Serial.parseInt();
            angle = constrain(angle, 0, 180);
            pan.write(angle);
            Serial.println(String("pan -> ") + angle);
        }
    }
}
