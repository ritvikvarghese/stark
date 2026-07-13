int pin = A2;
int val;
float v2;
int bluePin = 9;

void setup() {
    Serial.begin(9600);
    pinMode(bluePin, OUTPUT);
    pinMode(pin, INPUT);
}

void loop() {
    val = analogRead(pin);
    v2 = val * (5.0 / 1023.0);
    Serial.println(v2);
    if (v2 > 4) {
        digitalWrite(bluePin, HIGH); // turn on the blue LED
    } else {
        digitalWrite(bluePin, LOW); // turn off the blue LED
    }
    delay(1000); // wait for 1 second
}