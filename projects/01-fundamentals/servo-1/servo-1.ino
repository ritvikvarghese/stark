#include <Servo.h>
int servoPin = 9;
int servoPos = 0;
int dT = 15;
Servo myServo;

void setup() {
    Serial.begin(9600);
    myServo.attach(servoPin);
    myServo.write(0);
}

void loop() {
    for (servoPos = 0; servoPos < 180; servoPos++) {
        myServo.write(servoPos);
        Serial.println(servoPos);
        delay(dT);
    }
    for (servoPos = 180; servoPos >= 0; servoPos--) {
        myServo.write(servoPos);
        Serial.println(servoPos);
        delay(dT);
    }
}
