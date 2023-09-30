float Res1_Panel_1 = 15000.0;
float Res2_Panel_1 = 5600.0;
float Res1_Aki_1 = 15000.0;
float Res2_Aki_1 = 5600.0;

int Sensor_Volt_Panel = A0;
int Sensor_Volt_Aki = A1;

float vModul_Panel;
float vModul_Aki;

float voltage_Panel1;
float voltage_Aki1;

float bBawah_vAki =12.6;
float bAtas_vAki =13.6;

float daya;

float pSekarang;
float pSebelum =0;

const int pinADC = A1;
int sensitivitas = 185; //5A
int valueADC = 00;
int teganganOffset = 2500;
double nilaiArus = 00;
double nilaiTegangan = 00;

int pwm = 150;

#define mosfet 6

void setup(){
  Serial.begin(9600);
  pinMode(mosfet, OUTPUT);
}

void loop(){
  int analog_Panel = analogRead(Sensor_Volt_Panel);
  int analog_Aki = analogRead(Sensor_Volt_Aki);

  valueADC = analogRead(pinADC);
  nilaiTegangan = (valueADC/1024.0)*5000;
  nilaiArus = ((nilaiTegangan - teganganOffset)/sensitivitas); //Nilai arus
  
  vModul_Panel = (analog_Panel*5)/1024.0;
  vModul_Aki = (analog_Aki*5)/1024.0;

  voltage_Panel1 = vModul_Panel/(Res2_Panel_1/(Res1_Panel_1 + Res2_Panel_1)); //Tegangan Panel 1
  voltage_Aki1 = vModul_Aki/(Res2_Aki_1/(Res1_Aki_1 + Res2_Aki_1)); //Tegangan Aki 1

  daya = voltage_Panel1*nilaiArus;
  pSekarang = daya; 
  if(pSekarang>pSebelum){
    pwm +=1;   
  }
  else if(pSekarang<pSebelum){
    pwm -=1;
  }
  pSebelum = pSekarang;

  if(voltage_Aki1<bAtas_vAki){
    analogWrite(mosfet, pwm);
  }
  if(voltage_Aki1>=bAtas_vAki){
    analogWrite(mosfet, 0);
  }
}