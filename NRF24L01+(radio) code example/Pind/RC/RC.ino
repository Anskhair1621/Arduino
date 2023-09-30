#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

const int PIN_CE = 9;
const int PIN_CSN = 10;

const uint64_t pipe = 0xE8E8F0F0E2LL;
RF24 radio(PIN_CE, PIN_CSN);

char pesan[20];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  Serial.println("Siap Menerima Data!");
}

void loop() {
  if (radio.available()) {
    radio.read(pesan, sizeof(pesan));
    Serial.println("Pesan Terima: ");
    Serial.println(pesan);
  }
}
