#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(7, 8);

int button = 2;    // button is connected to digital pin 2

void setup() {
  // Initialize the NRF24L01 module
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.stopListening();
  
  // Configure the button pin as an input
  pinMode(button, INPUT);
}

void loop() {
  // Read the button state
  int buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    sendData("LED_ON");
  } else {
    sendData("LED_OFF");
  }
  delay(100);
}

void sendData(String data) {
    radio.write(data.c_str(), data.length());
}
