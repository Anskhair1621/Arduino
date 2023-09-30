#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi objek untuk LCD 16x2 I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inisialisasi pin-pen driver L298N
int ENA = 5;
int IN1 = 6;
int IN2 = 7;
int ENB = 10;
int IN3 = 8;
int IN4 = 9;

void setup() {
  // Inisialisasi pin-pen driver L298N
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Inisialisasi koneksi serial
  Serial.begin(9600);

  // Inisialisasi objek untuk LCD 16x2 I2C
  lcd.init();
  lcd.backlight();
  lcd.clear();
 }

void loop() {
  if (Serial.available()) {
    int error = Serial.parseInt();
    lcd.setCursor(0, 0);
    Serial.print("Error: ");
    Serial.println(error);

    // Kontrol arah putaran motor DC berdasarkan nilai error
    if (error > 0) {
      // Motor berputar ke kanan
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 255);
      analogWrite(ENB, 255);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("putar kanan");     
    } else if (error < 0) {
      // Motor berputar ke kiri
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENA, 255);
      analogWrite(ENB, 255);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("putar kiri");
      
    } else {
      // Motor berhenti
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Motor Berhenti");
    }
  }
}
