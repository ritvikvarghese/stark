#include <Servo.h>
int lightPin = A0;
int servoPin = 9;
int lightVal; 
int servoPos = 0;
String status1 = "light is off";
String status2 = "light is medium";
String status3 = "light is bright";
int lastState = -1;   // remembers the previous band so we only print on a change (-1 = unknown, forces the first print)
Servo myServo;

void setup() {
    Serial.begin(9600);
    pinMode(lightPin, INPUT);
    myServo.attach(servoPin);
}

void loop() {
    lightVal = analogRead(lightPin);

    // one chained decision — every value 0-1023 lands in exactly one band, no gaps.
    // state: 0 = dark, 1 = medium, 2 = bright. pick the matching servo angle + label.
    int state;
    String status;
    if (lightVal < 400) {
        state = 0; servoPos = 0;   status = status1;   // dark
    } else if (lightVal < 800) {
        state = 1; servoPos = 90;  status = status2;   // medium
    } else {
        state = 2; servoPos = 180; status = status3;   // bright
    }

    // print only when the band actually changes...
    if (state != lastState) {
        Serial.println(String(lightVal) + " - " + status);
        Serial.flush();   // ...and BLOCK until the line is fully sent, while the rail is still quiet
        lastState = state;
    }

    myServo.write(servoPos);   // move the servo AFTER serial is done, so its current spike can't corrupt the print
    delay(200);
}
