// LIBRARY YANG DUNAKAN
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

// MENDEFINISKAN PIN
#define DHTPIN 0 //D3 PADA ESP8266
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// HOSTING DATABASE UNTUK MENGHUBUNGKAN MIT DENAN ESP8266
#define FIREBASE_HOST "https://dht11-with-esp8266-17b93-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "dKHvc57y97xSUUWy5ppnqkcQCyFB4RjRlq2y1IRi"
//WIFI UNTUK JARINGAN KONEKSI ESP DAN APP INVENTOR
#define WIFI_SSID "SUKKI 7888"   
#define WIFI_PASSWORD "12345678"  

// mendeklarasikan objek data dari FirebaseESP8266
FirebaseData firebaseData;

void setup() {
  
  Serial.begin(115200);
  
  dht.begin();
  
  // Koneksi ke Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
  
  // Sensor DHT11 membaca suhu dan kelembaban
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Memeriksa apakah sensor berhasil mambaca suhu dan kelembaban
  if (isnan(t) || isnan(h)) {
    Serial.println("Gagal membaca sensor DHT11");
    return;
  }

  // Menampilkan suhu dan kelembaban pada serial monitor
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Kelembapan: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println();

  // Memberikan status suhu dan kelembaban kepada firebase
  if (Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/suhu", t)){
      Serial.println("Suhu terkirim");
    } else{
      Serial.println("Suhu tidak terkirim");
      Serial.println("Karena: " + firebaseData.errorReason());
    } 
    
  if (Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/kelembaban", h)){
      Serial.println("Kelembaban terkirim");
      Serial.println();
    } else{
      Serial.println("Kelembaban tidak terkirim");
      Serial.println("Karena: " + firebaseData.errorReason());
    }
    
  delay(1000);
}
