#define LED_ROJO 8
#define LED_AZUL 9
#define BOTON_START 7

int estado = 0;
int estadoAnterior_btn_start = 0;
int salida = 0;




// DEFINICION DE ESTADOS

enum estados
{
  EST_DETECCION,
  EST_ENCENDIDO,
  EST_APAGADO,
  EST_CERRADO
};
// DEFINICION PARA EL SWITCH CASE
int estado_actual   = EST_ENCENDIDO;
int estado_anterior = EST_APAGADO;



//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  //                                                -->  GENERALES  <--                                                 //
  Serial.begin(9600);
  //                                                -->  LEDS  <--                                                 //
  pinMode(LED_ROJO,OUTPUT);
  pinMode(LED_AZUL,OUTPUT);
  //                                                -->  BOTON START  <--                                                 //
  pinMode(BOTON_START,INPUT_PULLUP);

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop()
{
  apagarLed();
  Serial.println(" 0 Esperando Detección....... ");
  //                                                -->  BOTON START  <--                                                 //
  arrancar();
  //                                                -->  SWITCH CASE  <--                                                 //
  while(salida == 0){
    switch(estado_actual)
    {
      case EST_DETECCION:
      Serial.println(" 1 Botón Presionado....... ");
      encenderLed();
      Serial.println("Caso1");
      break;

      case EST_CERRADO:
      apagarLed();
      cerrar();
      Serial.println("Caso2");
      break;

      default:
      break;
      
    }
    
    
  }
  

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                -->  FUNCION PULSADOR SOSTENIDO START  <--                                                 //


void arrancar()
{ Serial.println(" 0.1 Esperando Detección....... ");
  if(estado_actual == EST_ENCENDIDO)
  {
    Serial.println(" 0.1 Esperando Detección.......entro al if ");
    estado = digitalRead(BOTON_START);
    if ( (estado == HIGH)&&(estadoAnterior_btn_start == LOW) )
    {
      salida = 1 - salida;  //Modifica el estado de la variable salida
      delay(20);             //Evita el rebote del pulsador
      estado_actual = EST_DETECCION;//******************************************************************************************************************************************************* 
    }
    estadoAnterior_btn_start = estado;//Guarda el valor actual 
  
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
  Serial.println(" 0.1 Esperando Detección.......NO ENTRO al if ");
  
}







//                                                -->  FUNCION PENCENDER LED  <--                                                 //

void encenderLed()
{
  if(estado_actual == EST_DETECCION)
  {
    digitalWrite(LED_ROJO,HIGH);
    digitalWrite(LED_AZUL,HIGH);
    estado_actual = EST_CERRADO;//******************************************************************************************************************************************************* 
  }
}
//                                                -->  FUNCION APAGAR LED  <--                                                 //

void apagarLed()
{
  if(estado_actual == EST_DETECCION)
  {
    digitalWrite(LED_ROJO,LOW);
    digitalWrite(LED_AZUL,LOW);
    estado_actual = EST_CERRADO;//******************************************************************************************************************************************************* 
  }
}







//                                                -->  FUNCION CERRAR que vuelva a iniciar en el estado EST_DETECCION <--                                                 //


void cerrar()
{
    if(estado_actual == EST_ENCENDIDO)
  {
    estado_actual = EST_DETECCION;//******************************************************************************************************************************************************* 
  }
}













 
