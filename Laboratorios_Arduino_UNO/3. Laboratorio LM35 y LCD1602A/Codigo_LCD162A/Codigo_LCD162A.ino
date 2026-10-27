
#include <LiquidCrystal.h>

// Conexiones originales de tu pantalla LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("PANTALLA LCD");

  lcd.setCursor(0, 1);
  lcd.print("FUNCIONANDO OK");
}

void loop() {
  // La pantalla mantiene el mensaje
}
