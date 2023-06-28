/*#include <LiquidCrystal.h>

LiquidCrystal lcd(2,23, 4, 5, 13, 12);

const int ledPins[] = {26, 21, 22, 25};      // LED pins connected to GPIOs
const int buttonPins[] = {18, 19, 14, 27};    // Button pins connected to GPIOs

int sequence[100];       // Max sequence length of 100
int sequenceLength = 0;
int playerIndex = 0;
int score = 0;

void setup() {
  lcd.begin(16, 2);  // Initialize LCD display
  lcd.print("Simon Says");

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);       // Set LED pins as output
    pinMode(buttonPins[i], INPUT);     // Set button pins as input
    digitalWrite(ledPins[i], LOW);     // Turn off LEDs
  }

  randomSeed(analogRead(0));   // Seed the random number generator
  generateSequence();          // Generate initial sequence
  delay(1000);                 // Pause before starting the game
  lcd.clear();
}

void loop() {
  if (playerIndex == sequenceLength) {
    playerIndex = 0;
    delay(1000);
    addToSequence();
    playSequence();
    score++;
  }

  checkButtonPress();

  lcd.setCursor(0, 1);
  lcd.print("Score: " + String(score));
}

void generateSequence() {
  for (int i = 0; i < 100; i++) {
    sequence[i] = random(0, 4);  // Generate random numbers between 0 and 3
  }
}

void addToSequence() {
  sequence[sequenceLength] = random(0, 4);
  sequenceLength++;
}

void playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    int led = sequence[i];
    flashLED(led, 500);
    delay(300);
  }
}

void flashLED(int led, int duration) {
  digitalWrite(ledPins[led], HIGH);
  delay(duration);
  digitalWrite(ledPins[led], LOW);
}

void checkButtonPress() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == HIGH) {
      flashLED(i, 200);
      if (i == sequence[playerIndex]) {
        playerIndex++;
      } else {
        gameOver();
      }
      delay(100);
    }
  }
}

void gameOver() {
  lcd.clear();
  lcd.print("Game Over!");
  while (true) {
    // You can add any additional logic here for the game over state
  }
}

*/
#include <LiquidCrystal.h>

LiquidCrystal lcd(2,23, 4, 5, 13, 12);

const int ledPins[] = {26, 21, 22, 25};      // LED pins connected to GPIOs
const int buttonPins[] = {18, 19, 14, 27};    // Button pins connected to GPIOs

int sequence[100];       // Max sequence length of 100
int sequenceLength = 0;
int playerIndex = 0;
int score = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // Initialize LCD display
  lcd.print("Simon Says");

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);       // Set LED pins as output
    pinMode(buttonPins[i], INPUT_PULLUP);     // Set button pins as input with internal pull-up resistors
    //digitalWrite(ledPins[i], LOW);     // Turn off LEDs
  }

  randomSeed(analogRead(0));   // Seed the random number generator
  generateSequence();          // Generate initial sequence
  delay(1000);                 // Pause before starting the game
  lcd.clear();
}

void loop() {
  if (playerIndex == sequenceLength) {
    playerIndex = 0;
    delay(1000);
    addToSequence();
    playSequence();
    score++;
  }

  checkButtonPress();

  lcd.setCursor(0, 1);
  lcd.print("Score: " + String(score));
}

void generateSequence() {
  for (int i = 0; i < 100; i++) {
    sequence[i] = random(0, 4);  // Generate random numbers between 0 and 3
  }
}

void addToSequence() {
  sequence[sequenceLength] = random(0, 4);
  sequenceLength++;
}

void playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    int led = sequence[i];
    flashLED(led, 500);
    delay(300);
  }
}

void flashLED(int led, int duration) {
  digitalWrite(ledPins[led], HIGH);
  delay(duration);
  digitalWrite(ledPins[led], LOW);
}

void checkButtonPress() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {  // Changed to LOW to match INPUT_PULLUP
      flashLED(i, 200);
      if (i == sequence[playerIndex]) {
        playerIndex++;
      } else {
        gameOver();
      }
      delay(100);
    }
  }
}

/*void gameOver() {
  lcd.clear();
  lcd.print("Game Over!");
  while (true) {
    // You can add any additional logic here for the game over state
  }
}*/
void gameOver() {
  Serial.print("Game over! your score: ");
  Serial.println(playerIndex - 1);
  playerIndex = 0;
  delay(200);
}
