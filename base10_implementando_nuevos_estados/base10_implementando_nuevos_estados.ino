#include <infrarrojo.h>                  
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
  EST_CERRADO,
  //
  EST_DETECCION,
  EST_DET_PIEZA_S1
};

// DEFINICION PARA EL SWITCH CASE
int estado_actual   = EST_ENCENDIDO;
int estado_anterior = EST_APAGADO;

//DEFINICION PARA MOTORES
int IN1 = 2;
int IN2 = 3;
int ENA = 10;  
int ENB = 11;  

//DEFINICION INFRARROJO
infrarrojo estado_a(9);                 
infrarrojo estado_b(12);      
int VALOR_a;
int VALOR_b;
int infrarrojo_estado_a;
int infrarrojo_estado_b;

//DEFINICION RELES
#define RELE_VALVULA 5
#define RELE_VENTILADOR 13



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
  pinMode( ENB, OUTPUT );
  pinMode( IN1, OUTPUT );
  pinMode( IN2, OUTPUT );
  //                                                -->  INFRARROJOS  <--                                                 //
  pinMode(RELE_VALVULA,OUTPUT);
  pinMode(RELE_VENTILADOR,OUTPUT);
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

      case EST_DETECCION:
      Serial.println("Caso2");
      detectar_objeto();
      break;

      case EST_DET_PIEZA_S1:
      detectar_objeto_inicio();
      Serial.println("Caso3");
      break;


      case EST_CERRADO:
      Serial.println("Caso Final");
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

// FUNCION MOTOR_A

void encenderMotorA()
{
  if(estado_actual == EST_DETECCION_MOTOR_A)
  {
  analogWrite(ENA,70);

  encenderLed();
  delay(3000);
  
  encenderValvula();
  encenderMotorB();
  encenderVentilador();
  
  estado_actual = EST_DETECCION;//*********************************************************************************************************************
  
  }
}
//*********************************************************************************************************************ONTERMEDIO


void detectar_objeto(){
  if (estado_actual == EST_DETECCION)
  {
    if(estado_a.lectura(VALOR_a) == 0)
    {
      
      apagarMotorB();
      apagarValvula();
      delay(1000);
      estado_actual = EST_DET_PIEZA_S1;   
    }
  }    
}

void detectar_objeto_inicio(){
  if (estado_actual == EST_DET_PIEZA_S1)
  {
    //cambiar marcha motor b
    
    cambiarMarchaMotorB();

    if(estado_b.lectura(VALOR_b) == 0)
    {
      estado_actual = EST_CERRADO;   
    }    
  }
}

//*********************************************************************************************************************ESTADO CERRADO
// FUNCION APAGAR MOTOR_A

void apagarMotorA()
{
  if(estado_actual == EST_CERRADO)//*********************************************************************************************************************
  {
    
  analogWrite(ENA,0);
  apagarMotorB();
  apagarLed();
  apagarVentilador();
  
  estado_actual = EST_ENCENDIDO;
  
  }
  
}

// ---------------------------------------------------------------------------------------------------- FUNCIONES NO IMPORTANTES -----------------------------------------------------------------------------

//APAGAR MOTOR B
void apagarMotorB()
{
  analogWrite(ENB,0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

//ENCENDER MOTOR B
void encenderMotorB()
{
  analogWrite(ENB,70);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

//CAMBIAR MARCHA MOTOR B
void cambiarMarchaMotorB()
{
  analogWrite(ENB,70);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

// APAGAR VENTILADOR

void apagarVentilador()
{
    digitalWrite(RELE_VENTILADOR,LOW);
}

//ENCENDER VENTILADOR

void encenderVentilador()
{
    digitalWrite(RELE_VENTILADOR,HIGH);
}


// APAGAR VALVULA

void apagarValvula()
{
    digitalWrite(RELE_VALVULA,LOW);
}

//ENCENDER VALVULA

void encenderValvula()
{
    digitalWrite(RELE_VALVULA,HIGH);
}

// APAGAR LED

void apagarLed()
{
    digitalWrite(LED_ROJO,LOW);
    digitalWrite(LED_AZUL,LOW);
}

//ENCENDER LED

void encenderLed()
{
    digitalWrite(LED_ROJO,HIGH);
    digitalWrite(LED_AZUL,HIGH);
}

// INFRARROJO A

void infrarrojoJaime_a()
{
  infrarrojo_estado_a = estado_a.lectura(VALOR_a);//LED QUE RECOGE EL ESTADO DEL SENSOR


  if(infrarrojo_estado_a == 1)//ETAPA DE COMPARACION PARA ACTIVAR UN LED SEGUN EL ESTADO DEL SENSOR
  {
    Serial.print("El valor del estado debe ser 1 verdad? -->");
    Serial.println(estado_a.lectura(VALOR_a));
  }
  else
  {
    Serial.print("El valor del estado debe ser 0 verdad? -->");
    Serial.println(estado_a.lectura(VALOR_a));
    apagarMotorB();
  }
  //delay(100);
}
