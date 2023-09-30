#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(7, 8);
int led = 13;  // LED is connected to digital pin 13

void setup() {
  // Initialize the NRF24L01 module
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  // Configure the LED pin as an output
  pinMode(led, OUTPUT);
}

void loop() {
  if (radio.available()) {
    char receivedData[8];
    radio.read(receivedData, sizeof(receivedData));
    if (strcmp(receivedData, "LED_ON") == 0) {
      digitalWrite(led, HIGH);
    } else if (strcmp(receivedData, "LED_OFF") == 0) {
      digitalWrite(led, LOW);
    }
  }
}
