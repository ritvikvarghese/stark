// day 5 — hc-sr04, part 1: mcwhorter's version (characterize the sensor)
// goal: print the raw PING TRAVEL TIME in microseconds. no distance formula yet.
// homework: with a ruler, measure travel-time vs distance, graph it, find the slope.
// (the slope IS the distance formula — you'll add that in ultrasonic-2 once you've earned it.)
// read the datasheet first: trigger wants a short pulse; echo then stays HIGH for
// exactly as long as the sound was in flight.

int trigPin = 12;          // we send the trigger pulse out of this pin
int echoPin = 11;          // we time how long this pin stays HIGH
long pingTravelTime;       // echo time in microseconds (pulseIn returns a long)
String message = "ping travel time (us): ";

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);  // we drive the trigger
  pinMode(echoPin, INPUT);   // we read the echo
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTravelTime = pulseIn(echoPin, HIGH);
  Serial.println(message + pingTravelTime);
  delay(200);  // 5 readings/sec — fast enough to feel live, slow enough to read
}
