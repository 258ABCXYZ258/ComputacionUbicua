int pinLED = 3;
int pinPot = A0;

void setup() {
  pinMode(pinLED, OUTPUT);
}

void loop() {
  int valorPot = analogRead(pinPot);
  int brillo = map(valorPot, 0, 1023, 0, 255);
  analogWrite(pinLED, brillo);
  delay(10);
}