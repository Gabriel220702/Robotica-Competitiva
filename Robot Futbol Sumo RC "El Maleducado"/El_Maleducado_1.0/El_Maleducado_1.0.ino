//                            Gabriel Carrizales García - - - - Samantha Elena Camacho Badillo - - - - Miguel Ángel Rodríguez Hernández
//                                                           El Maleducado 1.0 - Futbol Sumo 2025
//                                                               Arduino Nano - L298N - 11.1v

#include <SoftwareSerial.h>

// Definir pines de dirección del motor
#define IN1 2   
#define IN2 3   
#define IN3 4   
#define IN4 5   

// Pines de velocidad PWM
#define ENA 9  // Motor izquierdo (PWM)
#define ENB 10 // Motor derecho (PWM)

// Configurar pines de comunicación serial UART
#define RX_PIN 6
#define TX_PIN 7

SoftwareSerial Bluetooth(RX_PIN, TX_PIN); // Comunicación Bluetooth

// Definir velocidades
#define MAX_SPEED 255  // Velocidad máxima de los motores
#define GIROS_PROPIO_EJE 255 // Velocidad para giros en su propio eje
#define TURN_SPEED 150  // Velocidad reducida para giros suaves

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  if (Bluetooth.available() > 0) {
    char value = Bluetooth.read();
    Serial.println(value);

    if (value == 'F') {
      Forward();                        // Avanzar hacía Adelante
    } else if (value == 'B') {
      Backward();                       // Avanzar hacía Atrás
    } else if (value == 'S') {
      Stop();                           // Detenerse
    } else if (value == 'L') {
      Left();                           // Girar hacía Izquierda sobre su propio eje
    } else if (value == 'R') {
      Right();                          // Girar hacía Derecha sobre su propio eje
    } else if (value == 'G') {
      ForwardLeft();                    // Avanzar hacía Adelante mientras gira a la Izquierda
    } else if (value == 'I') {
      ForwardRight();                   // Avanzar hacía Adelante mientras gira a la Derecha
    } else if (value == 'H') {
      BackLeft();                       // Avanzar hacía Atrás mientras gira a la Izquierda
    } else if (value == 'J') {
      BackRight();                      // Avanzar hacía Atrás mientras gira a la Derecha
    }
  }
}

void Forward() {
  analogWrite(ENA, MAX_SPEED);
  analogWrite(ENB, MAX_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Backward() {
  analogWrite(ENA, MAX_SPEED);
  analogWrite(ENB, MAX_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Left() {
  analogWrite(ENA, GIROS_PROPIO_EJE);
  analogWrite(ENB, GIROS_PROPIO_EJE);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Right() {
  analogWrite(ENA, GIROS_PROPIO_EJE);
  analogWrite(ENB, GIROS_PROPIO_EJE);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void ForwardLeft() {
  analogWrite(ENB, TURN_SPEED);  
  analogWrite(ENA, GIROS_PROPIO_EJE);   
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void ForwardRight() {
  analogWrite(ENB, GIROS_PROPIO_EJE);   
  analogWrite(ENA, TURN_SPEED);  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void BackLeft() {
  analogWrite(ENB, TURN_SPEED);
  analogWrite(ENA, GIROS_PROPIO_EJE);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void BackRight() {
  analogWrite(ENB, GIROS_PROPIO_EJE);
  analogWrite(ENA, TURN_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
