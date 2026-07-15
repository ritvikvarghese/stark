int potVal;
int potPin = A0;
int redPin = 7;
int delayTime = 500;
String message = "Potentiometer is at ";

void setup() {
    Serial.begin(9600);
    pinMode(potPin, INPUT);
    pinMode(redPin, OUTPUT);
}

void loop() {
    potVal = analogRead(potPin);
    Serial.println(message + String(potVal));
    delay (delayTime);
    
    while (potVal > 1000) {
        digitalWrite(redPin, HIGH);
        potVal = analogRead(potPin);
        Serial.println(message + String(potVal));
        delay (50);
    }
    digitalWrite(redPin, LOW);
    Serial.println(message + String(potVal));
    delay (delayTime);
}