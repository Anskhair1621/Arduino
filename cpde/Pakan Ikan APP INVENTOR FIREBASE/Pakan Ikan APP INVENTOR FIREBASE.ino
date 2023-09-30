#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Servo.h>

// Define NTP Client untuk mendapatkan waktu
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


//define firebase untuk realtime database
#define FIREBASE_HOST "https://aquarium-c3a6e-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "BzuRqW2RAdZGxx4XxhpbnQ0ZMTFRN0KGfSQ51TXk"

//define Wifi yang akan disambungkan
#define WIFI_SSID "SUKKI 7888"
#define WIFI_PASSWORD "12345678"

#define Turb A0

// mendeklarasikan objek data dari FirebaseESP8266
FirebaseData firebaseData;
FirebaseJson json;

//
Servo servo;

void setup() {
  //memulai komunikasi serial dan setup pin yg diapakai di ESP8266
  Serial.begin(115200);
  pinMode(Turb, OUTPUT);
  servo.attach(14);  //D5
  servo.write(0);

  // Koneksi ke Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // memulai cient waktu dan menentukan wilayah waktu (GMT +7)
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600 //per GMT+1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(25200);  // 25200 meurpakan wilayah waktu GMT+7, didapatakan dari 3600*7

  //menunjukkan status koneksi di Serial Monitor
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

  //delklarasi setpoint waktu untuk mendapatakan data dari firebase
  int setpointjam = 0;
  int setpointmenit = 0;

  //menadapatkan waktu skrg
  timeClient.update();
  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute);

  //mendapatakan data jam di firebase
  if (Firebase.RTDB.getInt(&firebaseData, "/feeding/hour")) {

    String hour = firebaseData.stringData();
    setpointjam = hour.toInt();  //merubah data string menjadi integer
    Serial.println(hour);
  }

  //mendapatakan data menit di firebase
  if (Firebase.RTDB.getInt(&firebaseData, "/feeding/minute")) {

    String minute = firebaseData.stringData();
    setpointmenit = minute.toInt();  //merubah data string menjadi integer
    Serial.println(minute);
  }

  //membuat perbandingan antara setpoint dan jam skrg
  if (currentHour == setpointjam && currentMinute == setpointmenit) {
    Serial.println("beri makan ON");
    servo.write(180);
  }

  else {
    Serial.println("beri makan OFF");
    servo.write(0);
  }

  Serial.println(setpointjam);
  Serial.println(setpointmenit);

  //pembacaan sensor turbidity
  int ADC = analogRead(A0);
  int kekeruhan = map(ADC, 1024, 190, 248, 3);  // mapping sensor dimana ADC 1024 = 3 NTU sampai 190 ADC = 248 NTU

  //mengirim pembacaan sensor ke Firebase
  Firebase.setInt(firebaseData, "/kekeruhan/NTU", kekeruhan);

  // Delay satu detik
  delay(1000);
}
