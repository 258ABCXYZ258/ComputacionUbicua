const int pinLED = 3;

void setup() {
  pinMode(pinLED, OUTPUT);
}

void loop() {
  for (int brillo = 0; brillo <= 255; brillo++) {
    analogWrite(pinLED, brillo);
    delay(1);
  }
  for (int brillo = 255; brillo >= 0; brillo--) {
    analogWrite(pinLED, brillo);
    delay(10);
  }
}