#include <Wire.h>

// Definición de pines para el Motor Shield L298P
const int DIRA = 12;  // Dirección Motor A (Izquierdo)
const int PWMA = 10;  // Velocidad Motor A (PWM)
const int DIRB = 13;  // Dirección Motor B (Derecho)
const int PWMB = 11;  // Velocidad Motor B (PWM)

// Dirección I2C del MPU6050
const int MPU_ADDR = 0x68;
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ, Temp;

// Variables de tiempo y ángulo
unsigned long tiempo_prev;
float angulo_pitch = 0;

// Constantes PID (Deberás ajustar estas 3 variables para tu robot)
float Kp = 10.5; // Fuerza de empuje principal
float Ki = 0.0;  // Corrección a largo plazo
float Kd = 1.5 ; // Suavizado de la oscilación

// Variables de control
float setpoint = 5.75; // Tu punto de equilibrio exacto
float error, error_prev, integral, derivada, output;

// Compensación de zona muerta de los motores (medida con Diagnostico_Umbral_PWM:
// una rueda gira desde PWM 70 y las dos desde PWM 75)
const int PWM_MIN = 110;       // PWM mínimo con el que se mueven las dos ruedas
const int BANDA_MUERTA = 10;  // Si la salida del PID es menor que esto, motores quietos

void setup() {
  Serial.begin(9600);
  
  // Configurar los pines del shield como salidas
  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMB, OUTPUT);

  // Inicializar los motores apagados
  digitalWrite(DIRA, LOW);
  analogWrite(PWMA, 0);
  digitalWrite(DIRB, LOW);
  analogWrite(PWMB, 0);

  // Inicialización del sensor MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Registro de gestión de energía
  Wire.write(0);    // Despierta el sensor
  Wire.endTransmission(true);

  tiempo_prev = millis();
}

void loop() {
  // 1. Leer datos del sensor MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true); 

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Temp = Wire.read() << 8 | Wire.read(); 
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  // 2. Calcular el ángulo usando un Filtro Complementario
  unsigned long tiempo_actual = millis();
  float dt = (tiempo_actual - tiempo_prev) / 1000.0;
  tiempo_prev = tiempo_actual;

  // Calculamos el ángulo X usando las mismas variables que funcionaron en tu diagnóstico
  float accel_pitch = atan2(AcY, AcZ) * 180 / PI;
  float gyro_rate = GyX / 131.0;

  angulo_pitch = 0.98 * (angulo_pitch + gyro_rate * dt) + 0.02 * accel_pitch;

  // 3. Calcular el control PID
  error = setpoint - angulo_pitch;
  integral += error * dt;
  
  // Límite para evitar la saturación de la integral (Windup)
  integral = constrain(integral, -150, 150); 
  
  // La derivada del error es -(velocidad angular): el giroscopio la entrega directa y sin ruido de dt
  derivada = -gyro_rate;
  output = (Kp * error) + (Ki * integral) + (Kd * derivada);
  error_prev = error;

  // 4. Transformar salida PID a movimiento de motores
  int velocidad = abs(output);
  velocidad = constrain(velocidad, 0, 255);

  // Compensar la zona muerta: si el PID pide algo, que el motor realmente se mueva
  if (velocidad < BANDA_MUERTA) {
    velocidad = 0;
  } else {
    velocidad = map(velocidad, BANDA_MUERTA, 255, PWM_MIN, 255);
  }

  // Apagar motores si el robot se cae (inclinación mayor a 40 grados)
  if (abs(error) > 60) {
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
    integral = 0; // Evita que los motores arranquen a máxima velocidad al levantarlo
  } 
  else {
    // Determinar la dirección basada en el signo del PID
    if (output > 0) {
      // Compensar hacia adelante
      digitalWrite(DIRA, HIGH);
      digitalWrite(DIRB, HIGH);
    } else {
      // Compensar hacia atrás
      digitalWrite(DIRA, LOW);
      digitalWrite(DIRB, LOW);
    }
    
    // Aplicar la velocidad a los motores
    analogWrite(PWMA, velocidad);
    analogWrite(PWMB, velocidad);
  }
}