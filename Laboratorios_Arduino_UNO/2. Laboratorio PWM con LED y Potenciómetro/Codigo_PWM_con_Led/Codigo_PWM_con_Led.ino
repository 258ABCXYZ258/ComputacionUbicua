// Declaración de entradas/pines del receptor RF
int forward = 13;
int backwards = 12;
int left = 11;
int right = 10;

void setup() {
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT); 
  pinMode(4, OUTPUT); 

  // Pines de entrada para las señales RF
  pinMode(forward, INPUT);
  pinMode(backwards, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Lectura de los estados de entrada
  int forwardValue = digitalRead(forward);
  int backwardsValue = digitalRead(backwards);
  int leftValue = digitalRead(left);
  int rightValue = digitalRead(right);

  // Control de movimiento condicional
  if (forwardValue == HIGH) {
    adelante(85, 85);
  } 
  else if (backwardsValue == HIGH) {
    atras(85, 85);
  } 
  else if (leftValue == HIGH) {
    izquierda(85, 85);
  } 
  else if (rightValue == HIGH) {
    derecha(85, 85);
  } 
  else {
    parar();
  }
}

// Funciones de movimiento
void adelante(int velIzquierda, int velDerecha) {
  digitalWrite(7, HIGH);
  analogWrite(6, velDerecha);
  analogWrite(5, velIzquierda);
  digitalWrite(4, HIGH);
}

void atras(int velIzquierda, int velDerecha) {
  digitalWrite(7, LOW);
  analogWrite(6, velDerecha);
  analogWrite(5, velIzquierda);
  digitalWrite(4, LOW);
}

void izquierda(int velIzquierda, int velDerecha) {
  digitalWrite(7, HIGH);
  analogWrite(6, velDerecha);
  analogWrite(5, velIzquierda);
  digitalWrite(4, LOW);
}

void derecha(int velIzquierda, int velDerecha) {
  digitalWrite(7, LOW);
  analogWrite(6, velDerecha);
  analogWrite(5, velIzquierda);
  digitalWrite(4, HIGH);
}

void parar() {
  analogWrite(6, 0);
  analogWrite(5, 0);
}