#include <Servo.h>
int servoPin = 9;
int potPin = A0;
int potVal;
Servo myServo;
int angle = 0;
int dT = 15;

void setup() {
    Serial.begin(9600);
    myServo.attach(servoPin);
    myServo.write(0);
}

void loop() {
    potVal = analogRead(potPin);
    angle = map(potVal, 0, 1023, 0, 180);
    myServo.write(angle);
    Serial.println(String(potVal) + " - " + String(angle));
    delay(dT);
}












