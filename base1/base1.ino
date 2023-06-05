#define LED_ROJO 8
#define LED_AZUL 9


void setup() {
  pinMode(LED_ROJO,OUTPUT);
  pinMode(LED_AZUL,OUTPUT);

}

void loop() {
  digitalWrite(LED_ROJO,HIGH);
  digitalWrite(LED_AZUL,HIGH);
  delay(2000);
  digitalWrite(LED_ROJO,LOW);
  digitalWrite(LED_AZUL,HIGH);
  delay(2000);

}
