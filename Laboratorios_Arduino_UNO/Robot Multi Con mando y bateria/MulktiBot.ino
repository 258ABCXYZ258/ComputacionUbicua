// =======================================================
// PINES DE LA L298P MOTOR SHIELD (Fijos por hardware)
// =======================================================
const int E1 = 10; // PWM Velocidad Motor A
const int M1 = 12; // Dirección Motor A

const int E2 = 11; // PWM Velocidad Motor B
const int M2 = 13; // Dirección Motor B

// =======================================================
// PINES ENTRADA RECEPTOR RF YK04 (Usando entradas analógicas)
// =======================================================
const int forward  = A0; // Conectar a salida D0 del RF
const int backward = A1; // Conectar a salida D1 del RF
const int left     = A2; // Conectar a salida D2 del RF
const int right    = A3; // Conectar a salida D3 del RF

// Ajusta este valor si requiere más potencia para vencer el rozamiento (máx 255)
int VELOCIDAD = 200; 

void setup() {
  configurarPines();
  
  pinMode(forward, INPUT);
  pinMode(backward, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
}

void loop() {
  int forwardValue  = digitalRead(forward);
  int backwardValue = digitalRead(backward);
  int leftValue     = digitalRead(left);
  int rightValue    = digitalRead(right);

  if (forwardValue == HIGH) {
    moverAdelante();
  } else if (backwardValue == HIGH) {
    moverAtras();
  } else if (leftValue == HIGH) {
    girarIzquierda();
  } else if (rightValue == HIGH) {
    girarDerecha();
  } else {
    parar();
  }
}

// =======================================================
// FUNCIONES DE CONTROL DE MOTORES
// =======================================================

void configurarPines() {
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M2, OUTPUT);
}

void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}

void moverAdelante() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, VELOCIDAD);
  analogWrite(E2, VELOCIDAD);
}

void moverAtras() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, VELOCIDAD);
  analogWrite(E2, VELOCIDAD);
}

void girarIzquierda() {
  digitalWrite(M1, LOW); 
  digitalWrite(M2, HIGH); 
  analogWrite(E1, VELOCIDAD);
  analogWrite(E2, VELOCIDAD);
}

void girarDerecha() {
  digitalWrite(M1, HIGH); 
  digitalWrite(M2, LOW); 
  analogWrite(E1, VELOCIDAD);
  analogWrite(E2, VELOCIDAD);
}