const int readPin = A3;
int readval;
float v2 = 0;

void setup() {
    pinMode(readPin, INPUT); 
    Serial.begin(9600);
} 

void loop() {
    readval = analogRead(readPin);
    v2 = readval * (5.0 / 1023.0);
    Serial.println(v2);
    delay(1000);
}