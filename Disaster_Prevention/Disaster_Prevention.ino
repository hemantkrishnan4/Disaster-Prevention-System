#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// Initialize objects
MPU6050 mpu;
Servo myServo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define pin numbers
const int switch1Pin = 6;  // Pin for first switch (landslide detection)
const int switch2Pin = 7;  // Pin for second switch (landslide detection)
const int trigPin = 8;     // Trigger Pin (rain gauge)
const int echoPin = 9;     // Echo Pin (rain gauge)
const int threshold = 17000; // Threshold for vibration detection

int16_t ax, ay, az;
unsigned long lastMoveTime = 0;
const unsigned long moveInterval = 60000; // 30 seconds

void setup() {
    // Initialize Serial Communication
    Serial.begin(9600);

    // Landslide detection setup
    pinMode(switch1Pin, INPUT);
    pinMode(switch2Pin, INPUT);
    pinMode(switch1Pin,LOW);

    // Vibration detection setup
    Wire.begin();
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }
    Serial.println("MPU6050 connection successful!");

    // Servo control setup
    myServo.attach(10);
    myServo.write(90); // Set servo to default position 90 degrees

    // Rain gauge setup
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Set the analog pins A0, A1, A2, and A3 as input
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);

    // LCD setup
    lcd.begin(16, 2);
    lcd.noCursor();
}

void loop() {
    unsigned long currentMillis = millis();
    
    // Move servo every 30 seconds
    if (currentMillis - lastMoveTime >= moveInterval) {
        // Switch servo position
        if (myServo.read() == 90) {
            myServo.write(0);
            Serial.println("Servo moving to 0 degrees");
        } else {
            myServo.write(90);
            Serial.println("Servo moving to 90 degrees");
        }
        lastMoveTime = currentMillis;
    }

    // Read switch states
    int switch1State = digitalRead(switch1Pin);
    int switch2State = digitalRead(switch2Pin);
    Serial.println(switch1State);
    Serial.println(switch2State);

    // Vibration detection logic
    mpu.getAcceleration(&ax, &ay, &az);
    long magnitude = sqrt((long)ax * ax + (long)ay * ay + (long)az * az);

    // Rain gauge logic
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float height = (duration * 0.0343) / 2;

    // Read the analog values from the pins
    int value1 = analogRead(A0);
    int value2 = analogRead(A1);
    int value3 = analogRead(A2);
    int value4 = analogRead(A3);

    // Print values to Serial Monitor for debugging
    // Serial.print("Vibration Magnitude: ");
    // Serial.println(magnitude);
    // Serial.print("Water Height: ");
    // Serial.print(height);
    // Serial.println(" cm");

    // // LCD display logic
    // lcd.clear();
    // lcd.setCursor(0, 0);

    // // Display sequence for landslide, earthquake, and flood
    if (switch1State == HIGH && switch2State == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Land Slide:");
        lcd.setCursor(0, 1);
        lcd.print(" Warning High");
        delay(2000);
    } else if (switch2State == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Land Slide:");
        lcd.setCursor(0, 1);
        lcd.print(" Warning Medium");
        delay(2000);
    } else{
      lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Land Slide:");
        lcd.setCursor(0, 1);
        lcd.print(" Not Detected");
        delay(2000);



    // }
    // if (magnitude > threshold) {
    //     lcd.clear();
    //     lcd.setCursor(0, 0);
    //     lcd.print("Earthquake");
    //     lcd.setCursor(0, 1);
    //     lcd.print("Detected");
    //     delay(2000);
    // }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rain Level");
    lcd.setCursor(0, 1);
    lcd.print("     ");
    lcd.print(5 - height);

    // lcd.print(" cm");

    // delay(2000);
    // lcd.clear();

    //Check for each flood level and update the LCD and Serial Monitor
    // if (value1 == 0 && value2 != 0 && value3 != 0 && value4 != 0) {
    //     lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    //     lcd.print("Flood Level 1");
    //     Serial.println("Flood Level 1 Detected");
    // }
    // else if (value1 == 0 && value2 == 0 && value3 != 0 && value4 != 0) {
    //     lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    //     lcd.print("Flood Level 2");
    //     Serial.println("Flood Level 2 Detected");
    // }
    // else if (value1 == 0 && value2 == 0 && value3 == 0 && value4 != 0) {
    //     lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    //     lcd.print("Flood Level 3");
    //     Serial.println("Flood Level 3 Detected");
    // }
    // else if (value1 == 0 && value2 == 0 && value3 == 0 && value4 == 0) {
    //     lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    //     lcd.print("Flood Level 4");
    //     Serial.println("Flood Level 4 Detected");
    // }
    // else {
    //     lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
    //     lcd.print("Flood Level:");
    //     lcd.setCursor(0,1);
    //     lcd.print("No Flood");
    //     Serial.println("No Flood Detected");
    //     Serial.print("A0: "); Serial.println(value1);
    //     Serial.print("A1: "); Serial.println(value2);
    //     Serial.print("A2: "); Serial.println(value3);
    //     Serial.print("A3: "); Serial.println(value4);
     }

    delay(1000);
}

// Servo control functions
void moveTo90Degrees() {
    myServo.write(90);
}

void moveTo0Degrees() {
    myServo.write(0);
}
