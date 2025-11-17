//                                  Gabriel Carrizales García - Samantha Elena Camacho Badillo - Miguel Ángel Rodríguez Hernández
//                                                           El Maleducado 4.0 - Futbol Sumo 2025
//                                                       ESP32 - TB6612FNG - LM2596S - MP1584 - 11.1v

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define AIN1  18
#define AIN2  19
#define BIN1  17
#define BIN2  16
#define PWMA  21
#define PWMB  4
#define STBY  5
#define LED_STATUS 32
#define LED_BT 2

// Velocidades para manejo fluido
int velocidadAlta = 255;  // Velocidad máxima por defecto
int velocidadMedia = 200;
int velocidadBaja = 100;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("El Maleducado 4.0");

  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT); pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT); pinMode(LED_STATUS, OUTPUT);
  pinMode(LED_BT, OUTPUT);

  digitalWrite(LED_BT, LOW);
  digitalWrite(STBY, HIGH);
  digitalWrite(LED_STATUS, LOW);
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();
    Serial.println(comando);

    // Si es comando de velocidad
    if ((comando >= '0' && comando <= '9') || comando == ':') {
      actualizarVelocidades(comando);
    } else {
      switch (comando) {
        case 'F': Forward(); break;
        case 'B': Backward(); break;
        case 'S': Stop(); break;
        case 'L': Left(); break;
        case 'R': Right(); break;
        case 'G': ForwardLeft(); break;
        case 'I': ForwardRight(); break;
        case 'H': BackLeft(); break;
        case 'J': BackRight(); break;
        case 'W': digitalWrite(LED_STATUS, HIGH); break;
        case 'w': digitalWrite(LED_STATUS, LOW); break;
      }
    }
  }

  // LED indica conexión Bluetooth
  digitalWrite(LED_BT, SerialBT.hasClient() ? HIGH : LOW);
}

void actualizarVelocidades(char comandoSlider) {
  int basePWM;

  if (comandoSlider >= '0' && comandoSlider <= '9') {
    basePWM = (comandoSlider - '0') * 28;
  } else if (comandoSlider == ':') {
    basePWM = 255;
  } else {
    return;
  }

  velocidadAlta = basePWM;
  velocidadMedia = basePWM * 2 / 3;
  velocidadBaja = basePWM / 3;
}

// --- FUNCIONES DE MOVIMIENTO ---
void Forward() {
  analogWrite(PWMA, velocidadAlta); analogWrite(PWMB, velocidadAlta);
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
}
void Backward() {
  analogWrite(PWMA, velocidadAlta); analogWrite(PWMB, velocidadAlta);
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
}
void Stop() {
  analogWrite(PWMA, 0); analogWrite(PWMB, 0);
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, LOW);
}
void Left() {
  analogWrite(PWMA, velocidadMedia); analogWrite(PWMB, velocidadMedia);
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
}
void Right() {
  analogWrite(PWMA, velocidadMedia); analogWrite(PWMB, velocidadMedia);
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
}
void ForwardLeft() {
  analogWrite(PWMA, velocidadBaja); analogWrite(PWMB, velocidadMedia);
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
}
void ForwardRight() {
  analogWrite(PWMA, velocidadMedia); analogWrite(PWMB, velocidadBaja);
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
}
void BackLeft() {
  analogWrite(PWMA, velocidadBaja); analogWrite(PWMB, velocidadMedia);
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
}
void BackRight() {
  analogWrite(PWMA, velocidadMedia); analogWrite(PWMB, velocidadBaja);
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
}
