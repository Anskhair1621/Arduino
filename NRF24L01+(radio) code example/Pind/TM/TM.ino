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
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  // put your main code here, to run repeatedly:
  static int x = 1;
  sprintf(pesan, "pesan #%d", x);
  Serial.print(pesan);

  bool ok = radio.write(pesan, strlen(pesan));
  if (ok)
    Serial.println(" ok...");
  else
    Serial.println(" gagal...");
  x + 1;
  if (x > 500)
    x = 1;
  radio.powerDown();
  delay(1000);
  radio.powerUp();
}
