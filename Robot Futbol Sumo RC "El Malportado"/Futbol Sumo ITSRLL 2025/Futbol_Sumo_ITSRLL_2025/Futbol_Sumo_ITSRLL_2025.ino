// Pines de dirección del motor A (Izquierdo)
#define AIN1 4
#define AIN2 6

// Pines de dirección del motor B (Derecho)
#define BIN1 3
#define BIN2 2

// Pines de PWM para velocidad
#define PWMA 10
#define PWMB 9

// STBY está conectado directamente a 5V

// Velocidades
#define MAX_SPEED 255
#define GIROS_PROPIO_EJE 255
#define TURN_SPEED 50

void setup() {
  Serial.begin(9600); // Se usa Serial directamente para Bluetooth

  // Dirección motores
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // PWM
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char value = Serial.read();
    Serial.println(value); // Opcional: para debug, recuerda que solo funciona si no está el Bluetooth conectado

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
