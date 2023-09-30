#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <Servo.h>


#define FIREBASE_HOST "pakan-ikan-with-app-inventor-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "LqJ0JZm8L0HCX3vorxyKl3LZumQsIEjrR6i32ft0"

#define WIFI_SSID "SUKKI 7888"
#define WIFI_PASSWORD "12345678"

FirebaseData firebaseData;
FirebaseData ledData;
FirebaseJson json;
Servo servo;

int led = 2;
#define Turb A0

void setup() {
  pinMode(led, OUTPUT);
  pinMode(Turb, INPUT);
  servo.attach(14);  //D5
  servo.write(0);
  Serial.begin(9115200);
  // pinMode(led,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
void loop() {
  int sensorValue = analogRead(A0);
  

  if (Firebase.getString(ledData, "/led_testing/led/kekeruhan/NTU")) {
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
      digitalWrite(led, LOW);
      servo.write(0);


      Serial.println(kekeruhan);
      Serial.println("NTU");
      delay(1000);

      // Memberikan oembacaan sensor kepada firebase
      Firebase.setInt(firebaseData, "/led_testing/led/kekeruhan/NTU", kekeruhan);
    }
  }
  if (ledData.stringData() == "0") {
    digitalWrite(led, HIGH);
    servo.write(180);
  }
}
