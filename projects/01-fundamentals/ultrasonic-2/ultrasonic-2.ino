// day 5 — hc-sr04, part 2: the parking sensor (our deliverable)
// starts from your working ultrasonic-1 code (trigger pulse + pulseIn), then adds:
//   - the distance formula (the "answer" to part 1's slope)
//   - proximity feedback: an LED (or buzzer) that reacts as the target gets closer
// this is the real day-5 gadget: distance in cm + a signal you can feel.

int trigPin = 12;          // same wiring as part 1
int echoPin = 11;
int ledPin = 6;            // proximity LED (pick a PWM pin ~ if you want to fade it)
long pingTravelTime;       // microseconds, from pulseIn
float distance;            // centimeters
String message = "distance (cm): ";

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);   // driving the proximity LED
}

void loop() {
  // --- 1 + 2. fire the trigger and read the echo (brought over from ultrasonic-1) ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTravelTime = pulseIn(echoPin, HIGH);

  distance = (pingTravelTime * 0.0343) / 2; // speed of sound = 0.0343 cm/us. divide by 2 because the ping went to the target AND back.
  if (distance < 10) { // if the distance is less than 10 cm, turn on the LED
    digitalWrite(ledPin, HIGH);
  } else { // if the distance is greater than 10 cm, turn off the LED, we can also use an if statement to turn on the LED when the distance is less than 10 cm and turn off the LED when the distance is greater than 10 cm.
    digitalWrite(ledPin, LOW);
  }
  Serial.println(message + distance);
  delay(200);
}