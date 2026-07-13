int redPin = 6;
int bluePin = 9;
int redTime = 1000;
int blueTime = 1000;
int redBlink = 2;
int blueBlink = 5;
int j; // for loop counter

void setup() {
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    for (j = 1; j <= redBlink; j++) {  // when j is smaller than or equal to 2, the loop will run, so 2 times. 
        digitalWrite(redPin, HIGH);
        delay(redTime);
        digitalWrite(redPin, LOW);
        delay(redTime);
    }
    for (j = 1; j <= blueBlink; j++) { // when j is smaller than or equal to 5, the loop will run, so 5 times.
        digitalWrite(bluePin, HIGH);
        delay(blueTime);
        digitalWrite(bluePin, LOW);
        delay(blueTime);
    }
}