const int potPin = A3;
const int ledPin = 9;
int bright = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int knobRead = analogRead(potPin);
  int target = map(knobRead, 0, 1023, 0, 255);
  bright = (bright * 15 + target) / 16; // this is a simple averaging filter to smooth out the noise

  analogWrite(ledPin, bright);
  Serial.println(bright);
}