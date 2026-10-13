#include "DHT.h"

#define SENSOR_PIN 2     // Pin digital conectado al DHT22

// Inicialización del sensor DHT22
DHT dht(SENSOR_PIN, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Iniciando sensor DHT22...");
}

void loop() {
  // Esperar 2 segundos entre lecturas (requerido por el DHT22)
  delay(2000);

  // Leer humedad y temperatura
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verificar si hubo un fallo en la lectura
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error al leer el sensor DHT22");
    return;
  }

  // Mostrar resultados en el Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C  |  Humedad: ");
  Serial.print(humedad);
  Serial.println(" %");
}