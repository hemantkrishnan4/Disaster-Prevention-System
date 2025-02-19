#include <LiquidCrystal.h>

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the analog pins A0, A1, A2, and A3 as input
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  // Initialize the LCD
  lcd.begin(16, 2);
}

void loop() {
  // Read the analog values from the pins
  int value1 = analogRead(A0);
  int value2 = analogRead(A1);
  int value3 = analogRead(A2);
  int value4 = analogRead(A3);

  // Clear the LCD before printing new messages
  lcd.clear();

  // Check for each flood level and update the LCD and Serial Monitor
  if (value1 == 2 && value2 != 2 && value3 != 2 && value4 != 2) {
    lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    lcd.print("Flood Level 1");
    Serial.println("Flood Level 1 Detected");
  }
  else if (value1 == 2 && value2 == 2 && value3 != 2 && value4 != 2) {
    lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    lcd.print("Flood Level 2");
    Serial.println("Flood Level 2 Detected");
  }
  else if (value1 == 2 && value2 == 2 && value3 == 2 && value4 != 2) {
    lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    lcd.print("Flood Level 3");
    Serial.println("Flood Level 3 Detected");
  }
  else if (value1 == 2 && value2 == 2 && value3 == 2 && value4 == 2) {
    lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    lcd.print("Flood Level 4");
    Serial.println("Flood Level 4 Detected");
  }
  else {
    lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    lcd.print("No Flood");
    Serial.println("No Flood Detected");
    Serial.print("A0: "); Serial.println(value1);
    Serial.print("A1: "); Serial.println(value2);
    Serial.print("A2: "); Serial.println(value3);
    Serial.print("A3: "); Serial.println(value4);
  }

  delay(1000); // Delay for 1 second before updating the display again
}
