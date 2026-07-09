// led-2 — three LEDs in sequence, on a loop.
// red glows 2s, then blue 2s, then green 2s, then the whole thing repeats.
//
// wiring (change these pin numbers to match YOUR breadboard):
//   each pin -> LED long leg (+), short leg (-) -> resistor -> "-" ground rail
//   Arduino GND -> the "-" ground rail (shared by all three)

const int redPin   = 13;   // red LED (note: pin 13 also lights the on-board LED)
const int bluePin  = 12;   // blue LED
const int greenPin = 11;   // green LED

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // red on for 3 seconds
  digitalWrite(redPin, HIGH);
  delay(2000);
  digitalWrite(redPin, LOW);

  // blue on for 5 seconds
  digitalWrite(bluePin, HIGH);
  delay(2000);
  digitalWrite(bluePin, LOW);

  // green on for 10 seconds
  digitalWrite(greenPin, HIGH);
  delay(2000);
  digitalWrite(greenPin, LOW);

  // loop() repeats on its own, so the sequence starts over from red
}
