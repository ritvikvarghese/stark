const int redPin = 9;

int levels[] = {0, 64, 128, 192, 255};
int numLevels = 5;
int currentLevel = 0;

void setup() {
  pinMode(redPin, OUTPUT);
}

void loop() {
  analogWrite(redPin, levels[currentLevel]);

  currentLevel++;
  if (currentLevel >= numLevels) {
    currentLevel = 0;
  }

  delay(1000);
}
