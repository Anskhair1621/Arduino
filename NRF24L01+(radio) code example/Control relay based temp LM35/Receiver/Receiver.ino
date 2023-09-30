#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(7, 8);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // Initialize the NRF24L01 module
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  // Initialize the I2C LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Temperature: ");
  lcd.setCursor(0,1);
  lcd.print("Relay Status: ");
}

void loop() {
  if (radio.available()) {
    char receivedMessage[32];
    radio.read(receivedMessage, sizeof(receivedMessage));
    String message = String(receivedMessage);
    if (message.startsWith("Temperature")) {
      lcd.setCursor(13,0);
      lcd.print(message.substring(12));
    } else {
      lcd.setCursor(14,1);
      lcd.print(message);
    }
  }
}
