//Universidad Del Valle de Guatemala
//BE3015: Electrónica Digital 2
//José Trujillo
//LAB  4
//LCD 
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//Librerías
//----------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <LiquidCrystal.h> 
//----------------------------------------------------------------------------------------------------------------------
//Definición de pines
//----------------------------------------------------------------------------------------------------------------------
#define Incremento 21
#define Decremento 19
#define Voltaje1 13
#define Voltaje2 12

#define D4 32
#define D5 33
#define D6 25
#define D7 26

#define RS 27
#define E 14

//----------------------------------------------------------------------------------------------------------------------
//Prototipos de funciones
//----------------------------------------------------------------------------------------------------------------------
void LectorVoltajes(void); 
void Contador(void); 
//---------------------------------------------------------------------------------------------------------------------
//Variables Globales
//----------------------------------------------------------------------------------------------------------------------

//Creación de las variables que reciben el dato analogico del voltaje
float V1 = 0.0; 
float V2 = 0.0; 
//Generación para las variables de cada uno de los datos mostrados en la LCD 
int decenas1 = 0; 
int unidades1 = 0; 
int decimales1 = 0;

int decenas2 = 0; 
int unidades2 = 0; 
int decimales2 = 0;

int contador = 0; 
LiquidCrystal LCD(RS, E, D4, D5, D6, D7);
//----------------------------------------------------------------------------------------------------------------------
//ISR  (interrupciones)
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//CONFIGURACIÓN
//----------------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200); 
  // Este comando limpia la LCD
  LCD.begin(16, 2);

  pinMode(Incremento, INPUT_PULLUP);
  pinMode(Decremento, INPUT_PULLUP);

}

//---------------------------------------------------------------------------------------------------------------------
//Loop principal
//---------------------------------------------------------------------------------------------------------------------
void loop() {
  LectorVoltajes();
  Contador();

  LCD.clear(); //limpia la LCD
  LCD.print("Pot1:"); //IMPRIMER EN LA LCD
  LCD.print(" "); 
  Serial.print("Pot1:");
  Serial.print(decenas1);
  Serial.print(unidades1);
  Serial.println(decimales1);
  
 //esta función permite colocar el potenciometro en un espacio específico del LCD
  LCD.print("Pot2:"); 
  LCD.print(" "); 
  Serial.print("Pot2:");
  Serial.print(decenas2);
  Serial.print(unidades2);
  Serial.println(decimales2);


  LCD.print("CPU:");
  Serial.print("CPU:");
  Serial.print(contador);

  LCD.setCursor(1, 1);
  LCD.print(decenas1);
  LCD.print('.');
  LCD.print(unidades1);
  LCD.print(decimales1);
  LCD.print('V');
  LCD.print(" "); 
  LCD.print(decenas2);
  LCD.print('.');
  LCD.print(unidades2);
  LCD.print(decimales2);
  LCD.print('V');
  LCD.print(" "); 
  
  LCD.print(contador);  

  delay(250); 

  
}

//---------------------------------------------------------------------------------------------------------------------
//Lector analogico de voltajes
//---------------------------------------------------------------------------------------------------------------------
void LectorVoltajes(void){
  V1 = analogReadMilliVolts(Voltaje1);
  V2 = analogReadMilliVolts(Voltaje2);

  //Conversor de decenas, unidades y decimales para V1
  decenas1 = V1/100.0;
  V1 = V1 - decenas1*100.0;
  unidades1 = V1/10.0;
  V1 = V1 - unidades1*10.0; 
  decimales1 = V1; 

  //Conversor de decenas, unidades y decimales para V2
  decenas2 = V2/100.0;
  V2 = V2 - decenas2*100.0;
  unidades2 = V2/10.0;
  V2 = V2 - unidades2*10.0; 
  decimales2 = V2;
}

//---------------------------------------------------------------------------------------------------------------------
//Contador
//---------------------------------------------------------------------------------------------------------------------
void Contador(void){
  if (digitalRead(Incremento)==0){
    delay(200);
    if (digitalRead(Incremento)==1){
      if (contador < 255){
        contador++;
      }
      else if (contador >= 255){
        contador = 0; 
      }
    }
  }

  if (digitalRead(Decremento)==0){
    delay(200);
    if (digitalRead(Decremento)==1){
      if (contador > 0){
        contador--;
      }

      else if (contador <= 0){
        contador = 255; 
      }
       
    }
  }
}