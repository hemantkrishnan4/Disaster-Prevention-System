// Define the pin numbers
const int switch1Pin = 7; // Pin for first switch
const int switch2Pin = 8; // Pin for second switch
const int led1Pin = 3;    // Pin for first LED
const int led2Pin = 4;    // Pin for second LED

void setup() {
  // Set switch pins as inputs
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);

  // Set LED pins as outputs
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  // Read the state of the switches
  int switch1State = digitalRead(switch1Pin);
  int switch2State = digitalRead(switch2Pin);

  // If the first switch is pressed, turn on LED1
  if (switch1State == HIGH) {
    digitalWrite(led1Pin, HIGH);
  } else {
    digitalWrite(led1Pin, LOW);
  }

  // If the second switch is pressed, turn on both LEDs
  if (switch2State == HIGH) {
    digitalWrite(led2Pin, HIGH);
  } else {
    digitalWrite(led2Pin, LOW);
  }
}
