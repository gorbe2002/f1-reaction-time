const int startButton = 3;
const int reactionButton = 2;

int startState;
int reactionState;
int randomDelay;

unsigned long endSeqTime;
unsigned long reactionPressedTime;
int reactionTime;

void setup() {
  Serial.begin(9600);

  pinMode(startButton, INPUT);
  pinMode(reactionButton, INPUT);

  for (int x=12; x>7; x--) {
    pinMode(x, OUTPUT);
  }
}

void loop() {
  startState = digitalRead(startButton);
  randomDelay = random(200, 3000); // .2 secs to 3 secs

  if (startState == HIGH) {
    for (int x=12; x>7; x--) {
      delay(1000);
      digitalWrite(x, HIGH);
    }

    delay(randomDelay);
    for (int x=12; x>7; x--) {
      digitalWrite(x, LOW);
    }
    endSeqTime = millis();

    reactionState = digitalRead(reactionButton);
    if (reactionState == HIGH) { // happens when button is held down
      Serial.println("DISQUALIFIED CHEATER");
      return;
    }
    while (reactionState == LOW) {
      reactionState = digitalRead(reactionButton);
    }

    reactionPressedTime = millis();
    reactionTime = reactionPressedTime - endSeqTime;
    Serial.print("Your reaction time: ");
    Serial.print(reactionTime);
    Serial.println("ms");
  }
}