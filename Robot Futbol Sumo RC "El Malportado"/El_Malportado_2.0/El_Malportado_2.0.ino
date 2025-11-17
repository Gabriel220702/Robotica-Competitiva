//                                 Gabriel Carrizales García - - - - Bryam Muñiz Galvan - - - - Miguel Ángel Rodríguez Hernández
//                                                          El Malportado 2.0 - Futbol Sumo 2025
//                                                        Arduino Nano - TB6612FNG - MP1584 - 11.1v

#define AIN1 9
#define AIN2 10
#define BIN1 7
#define BIN2 6

#define PWMA 11  // PWM motor A (izquierdo)
#define PWMB 5   // PWM motor B (derecho)

#define STBY 8  // Pin de standby

// Velocidades
#define MAX_SPEED 255
#define GIROS_PROPIO_EJE 190
#define TURN_SPEED 90

void setup() {
  Serial.begin(9600); // Bluetooth HC-05 en pines 0 (RX) y 1 (TX)

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // Activar motores
}

void loop() {
  if (Serial.available()) {
    char value = Serial.read();
    Serial.println(value); // Solo para pruebas en monitor serial

    if (value == 'F') {
      Forward();
    } else if (value == 'B') {
      Backward();
    } else if (value == 'S') {
      Stop();
    } else if (value == 'L') {
      Left();
    } else if (value == 'R') {
      Right();
    } else if (value == 'G') {
      ForwardLeft();
    } else if (value == 'I') {
      ForwardRight();
    } else if (value == 'H') {
      BackLeft();
    } else if (value == 'J') {
      BackRight();
    }
  }
}

void Forward() {
  analogWrite(PWMA, MAX_SPEED);
  analogWrite(PWMB, MAX_SPEED);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void Backward() {
  analogWrite(PWMA, MAX_SPEED);
  analogWrite(PWMB, MAX_SPEED);
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
  analogWrite(PWMA, GIROS_PROPIO_EJE);
  analogWrite(PWMB, GIROS_PROPIO_EJE);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void Right() {
  analogWrite(PWMA, GIROS_PROPIO_EJE);
  analogWrite(PWMB, GIROS_PROPIO_EJE);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void ForwardLeft() {
  analogWrite(PWMA, GIROS_PROPIO_EJE);
  analogWrite(PWMB, TURN_SPEED);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void ForwardRight() {
  analogWrite(PWMA, TURN_SPEED);
  analogWrite(PWMB, GIROS_PROPIO_EJE);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void BackLeft() {
  analogWrite(PWMA, GIROS_PROPIO_EJE);
  analogWrite(PWMB, TURN_SPEED);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void BackRight() {
  analogWrite(PWMA, TURN_SPEED);
  analogWrite(PWMB, GIROS_PROPIO_EJE);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}
