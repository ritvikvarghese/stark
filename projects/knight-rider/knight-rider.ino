// Knight Rider
int greenPin = 2;
int bluePin = 3;
int redPin = 4;
int green2Pin = 5;
int blue2Pin = 6;
int leds[] = {greenPin, bluePin, redPin, green2Pin, blue2Pin};
int ledCount = 5;

void setup() {
    for (int i = 0; i < ledCount; i++) {
        pinMode(leds[i], OUTPUT);
    }
}

void loop() {
    // sweep right: 0 -> 4
    for (int i = 0; i < ledCount; i++) {
        digitalWrite(leds[i], HIGH);
        delay(80);
        digitalWrite(leds[i], LOW);
    }
    // sweep left: 3 -> 1 (the two end LEDs were just lit, so skip them to avoid a double-blink at the turn)
    for (int i = ledCount - 2; i >= 1; i--) {
        digitalWrite(leds[i], HIGH);
        delay(80);
        digitalWrite(leds[i], LOW);
    }
}