int pin = A2;
int val;
float v2;
String message = "potentiometer voltage: ";

void setup() {
    Serial.begin(9600);
}

void loop() {
    val = analogRead(pin);
    v2 = val * (5.0 / 1023.0);
    Serial.println(message + v2);
    delay(1000);
}