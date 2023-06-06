#include <infrarrojo.h>                  //SENSORES DE PRESENCIA      
infrarrojo estado_1(9);                 //S1 (sensor de arranque banda 1)

int VALOR_1;//VARIBLE QUE RECIBE EL DATO
int led_estado;//VARIABLE

void setup() {

  Serial.begin(9600);
}

void loop() {
  //Serial.print(estado.lectura(VALOR));//IMPRIME EL ESTADO DEL Vo DEL SENSOR MEDIANTE LA VARIABLE VALOR
  led_estado = estado_1.lectura(VALOR_1);//LED QUE RECOGE EL ESTADO DEL SENSOR


  if(led_estado == 1)//ETAPA DE COMPARACION PARA ACTIVAR UN LED SEGUN EL ESTADO DEL SENSOR
  {
    Serial.println(estado_1.lectura(VALOR_1));
  }
  else
  {
    Serial.println(estado_1.lectura(VALOR_1));
  }
  delay(100);
  
}
