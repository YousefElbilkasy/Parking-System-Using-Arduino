#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Configuration ---
// LCD Address: usually 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

// --- Pin Definitions ---
#define IR_ENTER 2   // Entrance sensor
#define IR_BACK 4    // Exit/Back sensor
#define SERVO_PIN 3  // Servo motor pin

#define IR_CAR1 12  // Slot 1 sensor
#define IR_CAR2 5  // Slot 2 sensor
#define IR_CAR3 13  // Slot 3 sensor

// --- Variables ---
int S1 = 0, S2 = 0, S3 = 0;
int flag1 = 0, flag2 = 0;
int slot = 3;  // Total available slots

void setup() {
  Serial.begin(9600);

  // 1. Initialize Sensors
  pinMode(IR_CAR1, INPUT);
  pinMode(IR_CAR2, INPUT);
  pinMode(IR_CAR3, INPUT);
  pinMode(IR_ENTER, INPUT);
  pinMode(IR_BACK, INPUT);

  // 2. Initialize Servo
  myservo.attach(SERVO_PIN);
  myservo.write(97);  // Initial State: Barrier Closed

  // 3. Initialize LCD
  lcd.init();
  lcd.backlight();

  // 4. Show Welcome Screen
  lcd.setCursor(0, 0);
  lcd.print("  Car Parking   ");
  lcd.setCursor(0, 1);
  lcd.print("     System     ");
  delay(2000);
  lcd.clear();

  // 5. Initial Sensor Read
  // Calculate occupied slots on startup to set correct counter
  Read_Sensor();
  int total = S1 + S2 + S3;
  slot = slot - total;
}

void loop() {
  Read_Sensor();

  // ==========================================
  //            LCD DISPLAY LOGIC
  // ==========================================

  // Line 1: Available Slots
  lcd.setCursor(0, 0);
  lcd.print("Have Slots: ");
  lcd.print(slot);
  lcd.print("   ");  // Clear trailing characters

  // Line 2: Slot Status (F=Full, E=Empty)
  lcd.setCursor(0, 1);

  lcd.print("S1:");
  lcd.print(S1 == 1 ? "F" : "E");

  lcd.print(" S2:");
  lcd.print(S2 == 1 ? "F" : "E");

  lcd.print(" S3:");
  lcd.print(S3 == 1 ? "F" : "E");

  // ==========================================
  //            ENTRY LOGIC
  // ==========================================
  if (digitalRead(IR_ENTER) == 0 && flag1 == 0) {
    // Only open if there is space
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(7);  // Open Barrier
        slot = slot - 1;
      }
    } else {
      // Parking is Full
      lcd.setCursor(0, 0);
      lcd.print(" Sorry Parking Full ");
      delay(1500);
      lcd.clear();
    }
  }

  // ==========================================
  //            EXIT LOGIC
  // ==========================================
  if (digitalRead(IR_BACK) == 0 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(7);  // Open Barrier
      slot = slot + 1;
    }
  }

  // ==========================================
  //         BARRIER CLOSING LOGIC
  // ==========================================
  // If car has passed both sensors (Entered or Exited completely)
  if (flag1 == 1 && flag2 == 1) {
    delay(1000);        // Wait for car to clear the boom
    myservo.write(97);  // Close Barrier
    flag1 = 0;          // Reset flags
    flag2 = 0;
  }

  delay(100);  // Stability delay
}

//Function to read IR sensors (Active LOW)
void Read_Sensor() {
  S1 = 0;
  S2 = 0;
  S3 = 0;

  if (digitalRead(IR_CAR1) == 0) { S1 = 1; }
  if (digitalRead(IR_CAR2) == 0) { S2 = 1; }
  if (digitalRead(IR_CAR3) == 0) { S3 = 1; }
}