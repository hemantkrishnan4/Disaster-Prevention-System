const int trigPin = 9; // Trigger Pin
const int echoPin = 10; // Echo Pin

#include <LiquidCrystal.h>

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set trigPin as output and echoPin as input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds to send out the pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate the distance
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm (speed of sound = 343 m/s)
  // distance = (duration / 2) * (speed of sound / 10000)
  // = (duration / 2) * 0.0343
  float height = (duration * 0.0343) / 2;

  // Print the distance on the serial monitor
  Serial.print("Height: ");
  Serial.print(height);
  Serial.println(" cm");

  delay(500); // Wait for half a second before the next measurement
}
