int counter = 0;
String message = "counter: ";

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(message + counter); // print the value of counter to the serial monitor
  counter = counter + 1; // counter++ is the same as counter = counter + 1;
  delay(1000); // wait for 1 second
}

--------------------------------

int counter = 0;
int x = 5;
int y = 10;
int z;
message = "x + y = ";

void setup() {
  Serial.begin(9600);
}

void loop() {
  z = x + y;
  Serial.println(message + z); // print the value of z to the serial monitor
  delay(1000);
}