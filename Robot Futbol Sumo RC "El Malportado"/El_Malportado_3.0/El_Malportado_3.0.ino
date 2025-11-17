//                                 Gabriel Carrizales García - - - - Bryam Muñiz Galvan - - - - Miguel Ángel Rodríguez Hernández
//                                                           El Malportado 3.0 - Futbol Sumo 2025
//                                                            ESP32 - TB6612FNG - MP1584 - 11.1v

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define AIN1  1
#define AIN2  22
#define BIN1  21
#define BIN2  19
#define PWMA  23
#define PWMB  18
#define STBY  3
#define LED_BT 2

void setup() {
  Serial.begin(115200);
  SerialBT.begin("El Malportado 3.0");
  pinMode(AIN1, OUTPUT); 
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); 
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT); 
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT); 
  pinMode(LED_BT, OUTPUT);
  digitalWrite(LED_BT, LOW);  
  digitalWrite(STBY, HIGH);
}

void loop() {
  if (SerialBT.available()) {
    char value = SerialBT.read();
    Serial.println(value);
    switch (value) {
      case 'F': Forward(); break;
      case 'B': Backward(); break;
      case 'S': Stop(); break;
      case 'L': Left(); break;
      case 'R': Right(); break;
      case 'G': ForwardLeft(); break;
      case 'I': ForwardRight(); break;
      case 'H': BackLeft(); break;
      case 'J': BackRight(); break;
    }
  }

  // LED indica conexión Bluetooth
  if (SerialBT.hasClient()) {
    digitalWrite(LED_BT, HIGH);
  } else {
    digitalWrite(LED_BT, LOW);
  }
}

void Forward() {
  analogWrite(PWMA, 255); 
  analogWrite(PWMB, 255);
  digitalWrite(AIN1, HIGH); 
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); 
  digitalWrite(BIN2, LOW);
}
void Backward() {
  analogWrite(PWMA, 255); 
  analogWrite(PWMB, 255);
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW); 
  digitalWrite(BIN2, HIGH);
}
void Stop() {
  analogWrite(PWMA, 0); 
  analogWrite(PWMB, 0);
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW); 
  digitalWrite(BIN2, LOW);
}
void Left() {
  analogWrite(PWMA, 190); 
  analogWrite(PWMB, 190);
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH); 
  digitalWrite(BIN2, LOW);
}
void Right() {
  analogWrite(PWMA, 190); 
  analogWrite(PWMB, 190);
  digitalWrite(AIN1, HIGH); 
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW); 
  digitalWrite(BIN2, HIGH);
}
void ForwardLeft() {
  analogWrite(PWMA, 90); 
  analogWrite(PWMB, 190);
  digitalWrite(AIN1, HIGH); 
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); 
  digitalWrite(BIN2, LOW);
}
void ForwardRight() {
  analogWrite(PWMA, 190); 
  analogWrite(PWMB, 90);
  digitalWrite(AIN1, HIGH); 
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); 
  digitalWrite(BIN2, LOW);
}
void BackLeft() {
  analogWrite(PWMA, 90); 
  analogWrite(PWMB, 190);
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW); 
  digitalWrite(BIN2, HIGH);
}
void BackRight() {
  analogWrite(PWMA, 190); 
  analogWrite(PWMB, 90);
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW); 
  digitalWrite(BIN2, HIGH);
}
