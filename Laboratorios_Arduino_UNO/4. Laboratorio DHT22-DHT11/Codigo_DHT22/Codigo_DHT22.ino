
#include <LiquidCrystal.h>
#include <DHT.h>

// Conservar las conexiones originales de la LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Usar el mismo pin DAT con el que ya funcionó el sensor
#define DHTPIN A0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Iniciando DHT22");

  delay(2000);
  lcd.clear();
}

void loop() {
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  if (isnan(temperatura) || isnan(humedad)) {
    lcd.setCursor(0, 0);
    lcd.print("Error sensor    ");
    lcd.setCursor(0, 1);
    lcd.print("Revise conexion ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatura, 1);
    lcd.write(byte(223));
    lcd.print("C   ");

    lcd.setCursor(0, 1);
    lcd.print("Humedad: ");
    lcd.print(humedad, 1);
    lcd.print("%   ");
  }

  // El DHT22 necesita un intervalo entre lecturas
  delay(2500);
}
