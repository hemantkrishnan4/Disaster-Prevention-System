#include <Servo.h>  // Include the Servo library

Servo myServo;  // Create a Servo object

const int controlPin = 3;  // Define the pin that will control the servo

void setup() {
  Serial.begin(9600);           // Initialize serial communication at 9600 bps
  myServo.attach(9);            // Attach the servo to pin 9
  pinMode(controlPin, INPUT);   // Set pin 3 as an input
  Serial.println("Servo Control Initialized");
}

void loop() {
  int pinState = digitalRead(controlPin);  // Read the state of pin 3

  if (pinState == HIGH) {
    moveTo0Degrees();  // Move to 180 degrees if pin 3 is high
  } else {
    moveTo90Degrees();   // Move to 90 degrees if pin 3 is low
  }

  delay(100);  // Small delay for stability
}

// Function to move the servo to 90 degrees
void moveTo90Degrees() {
  myServo.write(90);  // Move the servo to 90 degrees
  Serial.println("Moving to 90 degrees");  // Print status to Serial Monitor
}

// Function to move the servo to 180 degrees
void moveTo0Degrees() {
  myServo.write(0);  // Move the servo to 180 degrees
  Serial.println("Moving to 180 degrees");  // Print status to Serial Monitor
}
