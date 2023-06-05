#define LED_ROJO 8
#define LED_AZUL 9
#define BOTON_START 7

int estado = 0;
int estadoAnterior = 0;
int salida = 0;


void setup() {
  //                                                -->  GENERALES  <--                                                 //
  Serial.begin(9600);
  //                                                -->  LEDS  <--                                                 //
  pinMode(LED_ROJO,OUTPUT);
  pinMode(LED_AZUL,OUTPUT);
  //                                                -->  BOTON START  <--                                                 //
  pinMode(BOTON_START,INPUT_PULLUP);

}

void loop() {
  //                                                -->  BOTON START  <--                                                 //

  estado = digitalRead(BOTON_START);
  if ( (estado == HIGH)&&(estadoAnterior == LOW) )
  {
    salida = 1 - salida;  //Modifica el estado de la variable salida
    delay(20);             //Evita el rebote del pulsador
  }
  estadoAnterior = estado;//Guarda el valor actual 

  //  -----------------------------                -->  PROGRAMA GENERAL  <--           -----------------------------          //
  if (salida==1)
  {
    Serial.println("Botón en espera de ser presionado");
    digitalWrite(LED_ROJO,LOW);
    digitalWrite(LED_AZUL,LOW);
  }
  else
  {
    Serial.println("Presionado");
    digitalWrite(LED_ROJO,HIGH);
    digitalWrite(LED_AZUL,HIGH);
  }
  
  

}
