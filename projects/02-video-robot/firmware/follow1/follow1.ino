// follow1 - PAN ONLY. reads "p<angle>\n" and moves the pan servo.
// line-buffered parser: drains serial INSTANTLY (no parseInt timeout stalls),
// so commands can't pile up and lag the servo.

#include <Servo.h>
Servo pan;
const int panPin = 9;
char buf[8];
int idx = 0;

void setup() {
  Serial.begin(9600);
  pan.attach(panPin);
  pan.write(90);       // center on boot
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (idx > 1 && buf[0] == 'p') {
        buf[idx] = '\0';
        int angle = atoi(buf + 1);
        if (angle < 0)   angle = 0;
        if (angle > 180) angle = 180;
        pan.write(angle);
      }
      idx = 0;
    } else if (idx < 7) {
      buf[idx++] = c;
    }
  }
}
