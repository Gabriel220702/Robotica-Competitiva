//                                 Gabriel Carrizales García - - - - Bryam Muñiz Galvan - - - - Miguel Ángel Rodríguez Hernández
//                                                          El Malportado 1.0 - Futbol Sumo 2025
//                                                    Arduino Nano - TB6612FNG - 4CH RC - LM2596S - 7.4V

#define U 3

// Entradas del receptor actualizadas
#define CH0 11   // Dirección (Izquierda / Derecha)
#define CH1 12   // Movimiento (Adelante / Atrás)

// Pines del puente H TB6612FNG actualizados
#define AIN1 4   // Dirección Motor A
#define AIN2 6
#define PWMA 10  // PWM Motor A

#define BIN1 3   // Dirección Motor B
#define BIN2 2
#define PWMB 9   // PWM Motor B

const int STBY = 8;

int ch[U];

void setup() {
  Serial.begin(9600);
  pinMode(CH0, INPUT);
  pinMode(CH1, INPUT);

  // Motor A
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  // Motor B
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  // Standby
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);  // Activar el puente H
}

void loop() {
  ch[0] = pulseIn(CH0, HIGH);  // Dirección
  ch[1] = pulseIn(CH1, HIGH);  // Movimiento

  int vel_adelante = map(ch[1], 1080, 1500, 0, 255);
  int vel_atras = map(ch[1], 1080, 680, 0, 255);
  int giro_izq = map(ch[0], 1076, 600, 0, 150);
  int giro_der = map(ch[0], 1076, 1560, 0, 150);

  if (ch[1] > 1100) {  // Avanzar
    motores(vel_adelante, vel_adelante, true, true);
  } else if (ch[1] < 1050) {  // Retroceder
    motores(vel_atras, vel_atras, false, false);
  } else if (ch[0] < 1030) {  // Giro a la izquierda
    motores(giro_izq, giro_izq, false, true);
  } else if (ch[0] > 1130) {  // Giro a la derecha
    motores(giro_der, giro_der, true, false);
  } else {
    motores(0, 0, true, true); // Detener
  }

  Serial.print("CH0: "); Serial.print(ch[0]);
  Serial.print("  CH1: "); Serial.println(ch[1]);
}

void motores(int velA, int velB, bool dirA, bool dirB) {
  // Motor A
  digitalWrite(AIN1, dirA ? HIGH : LOW);
  digitalWrite(AIN2, dirA ? LOW : HIGH);
  analogWrite(PWMA, velA);

  // Motor B
  digitalWrite(BIN1, dirB ? HIGH : LOW);
  digitalWrite(BIN2, dirB ? LOW : HIGH);
  analogWrite(PWMB, velB);
}
