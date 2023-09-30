#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(7, 8);

int tempPin = A0;  // LM35 sensor is connected to analog pin A0
int relay = 8;    // Relay is connected to digital pin 8

void setup() {
  // Initialize the NRF24L01 module
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.stopListening();

  // Configure the relay pin as an output
  pinMode(relay, OUTPUT);
}

void loop() {
  // Read the temperature from the LM35 sensor
  int temp = analogRead(tempPin);
  float temperature = (temp * 0.48828125); // convert value to Celsius

  // Control the relay based on the temperature
  if (temperature >= 50) {
    digitalWrite(relay, HIGH);
    sendData("Relay on");
  } else {
    digitalWrite(relay, LOW);
    sendData("Relay off");
  }
  delay(1000);
}

void sendData(String data) {
    radio.write(data.c_str(), data.length());
}
