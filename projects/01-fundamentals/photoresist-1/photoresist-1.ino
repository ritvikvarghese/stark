// as the light intensity of the photoresistor increases, the resistance decreases
// it is a semiconductor device that changes its resistance based on the light intensity

int lightPin = A0;
int redPin = 8;
int greenPin = 7;
String status1 = "above threshold, light is on";
String status2 = "below threshold, light is off";
int threshold = 500;
int lightVal;
int lastState = -1;   // remembers the previous state so we only print on a change (-1 = unknown, forces the first print)

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(lightPin, INPUT);
}

void loop() {
  lightVal = analogRead(lightPin);
  int state = (lightVal > threshold) ? 1 : 0;   // 1 = above threshold (light), 0 = below (dark)

  // drive the LEDs every loop so they always match the current light
  if (state == 1) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  } else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }

  // but only print when the state actually flips
  if (state != lastState) {
    Serial.println(state == 1 ? status1 : status2);
    lastState = state;
  }

  delay(200);
}