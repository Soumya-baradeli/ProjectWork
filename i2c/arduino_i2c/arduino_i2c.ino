#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Set the LCD control pins

void setup() {
  Serial.begin(115200);
  
  lcd.begin(16, 2);
  lcd.print("Ready!");
}

void loop() {
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n');
    lcd.clear();
    lcd.print("Received:");
    lcd.setCursor(0, 1);
    lcd.print(receivedData);

    Serial.print("Received: ");
    Serial.println(receivedData);
  }
}
