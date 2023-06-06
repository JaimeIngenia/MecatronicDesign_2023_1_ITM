int IN1 = 2;
int IN2 = 4;
int PWM_salida = 5;

void setup() {
  pinMode( IN1, OUTPUT );
  pinMode( IN2, OUTPUT );
  pinMode(PWM_salida, OUTPUT);

}

void loop() {
  analogWrite(PWM_salida,70);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  

}
