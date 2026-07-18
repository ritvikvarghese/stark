#include <Servo.h>
Servo pan;
Servo tilt;
const int panPin = 9;
const int tiltPin = 10;

void setup() {
    Serial.begin(9600);
    pan.attach(panPin);
    tilt.attach(tiltPin);
    pan.write(90);
    tilt.write(90);
}

void loop() {
    if (Serial.available()) {
        char cmd = Serial.read();
        int angle = Serial.parseInt();
        angle = constrain(angle, 0, 180);
        if (cmd == 'p') pan.write(angle);
        if (cmd == 't') tilt.write(angle);
        Serial.println(String(cmd) + " " + angle);
    }
}