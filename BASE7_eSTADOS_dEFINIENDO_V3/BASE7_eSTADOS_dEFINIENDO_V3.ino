#define LED_ROJO 6
#define LED_AZUL 7
#define BOTON_START 8

int estado = 0;
int estadoAnterior_btn_start = 0;
int salida = 0;

// DEFINICION DE ESTADOS
enum estados
{
  EST_DETECCION_MOTOR_A,
  EST_ENCENDIDO,
  EST_APAGADO,
  EST_CERRADO
};

// DEFINICION PARA EL SWITCH CASE
int estado_actual   = EST_ENCENDIDO;
int estado_anterior = EST_APAGADO;

//DEFINICION PARA MOTORES
int IN1 = 2;
int IN2 = 3;
int ENA = 11;  
// ---------------------------------------------------------------------------------------------------- setup -----------------------------------------------------------------------------
void setup() {
  //                                                -->  GENERALES  <--                                                 //
  Serial.begin(9600);
  //                                                -->  LEDS  <--                                                 //
  pinMode(LED_ROJO,OUTPUT);
  pinMode(LED_AZUL,OUTPUT);
  //                                                -->  BOTON START  <--                                                 //
  pinMode(BOTON_START,INPUT_PULLUP);
  //                                                -->  MOTOR_A  <--                                                 //
  pinMode( ENA, OUTPUT );
  pinMode( IN1, OUTPUT );
  pinMode( IN2, OUTPUT );
}

// ---------------------------------------------------------------------------------------------------- loop -----------------------------------------------------------------------------

void loop() {
  //                                                -->  BOTON START  <--                                                 //
  arrancar();
  //                                                -->  SWITCH CASE  <--                                                 //
  while(salida == 0){
    
    switch(estado_actual)
    {
      case EST_DETECCION_MOTOR_A:
      Serial.println("Caso1");
      encenderMotorA();
      break;

      case EST_CERRADO:
      Serial.println("Caso2");
      apagarMotorA();
      break;

      default:
      break;   
    }
     
  }
}

// ---------------------------------------------------------------------------------------------------- FUNCIONES -----------------------------------------------------------------------------

void arrancar()
{
  if (estado_actual == EST_ENCENDIDO)
  {
            estado = digitalRead(BOTON_START);
            
            if ( (estado == HIGH)&&(estadoAnterior_btn_start == LOW) )
            {
              salida = 1 - salida;  //Modifica el estado de la variable salida
              delay(20);             //Evita el rebote del pulsador   
            }
            
            estadoAnterior_btn_start = estado;//Guarda el valor actual 
          
            if (salida==1)
            {
              Serial.println("Botón en espera de ser presionado");
            }
            else
            {
              Serial.println("Presionado");
              estado_actual = EST_DETECCION_MOTOR_A;  
            }
  }
}

// APAGAR LED

void apagarLed()
{
    digitalWrite(LED_ROJO,LOW);
    digitalWrite(LED_AZUL,LOW);
}

//ENCERNDER LED

void encenderLed()
{
    digitalWrite(LED_ROJO,HIGH);
    digitalWrite(LED_AZUL,HIGH);
}


// FUNCION MOTOR_A

void encenderMotorA()
{
  if(estado_actual == EST_DETECCION_MOTOR_A)
  {
  analogWrite(ENA,70);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  encenderLed();
  delay(5000);
  estado_actual = EST_CERRADO;//*********************************************************************************************************************
  }
}

// FUNCION APAGAR MOTOR_A

void apagarMotorA()
{
  if(estado_actual == EST_CERRADO)
  {
  analogWrite(ENA,70);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  apagarLed();
//  salida = 0;
  estado_actual = EST_ENCENDIDO;
//  estadoAnterior_btn_start == LOW;
//  arrancar();
  

  }
  
}
