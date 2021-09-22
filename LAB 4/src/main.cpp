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
#define Voltaje1 18
#define Voltaje2 5

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
float V1 = 0.0; 
float V2 = 0.0; 

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
}

//---------------------------------------------------------------------------------------------------------------------
//Loop principal
//---------------------------------------------------------------------------------------------------------------------
void loop() {
  LectorVoltajes();
  Contador();

  LCD.clear(); //limpia la LCD
  LCD.print("Pot1:"); //IMPRIMER EN LA LCD

  LCD.setCursor(1, 7); //esta función permite colocar el potenciometro en un espacio específico del LCD
  LCD.print("Pot2:"); 

  LCD.setCursor(1, 13);
  LCD.print("CPU:");

  LCD.setCursor(2, 1);
  LCD.print(decenas1);
  LCD.print('.');
  LCD.print(unidades1);
  LCD.print(decimales1);
  LCD.print('V');

  LCD.setCursor(2,7);
  LCD.print(decenas2);
  LCD.print('.');
  LCD.print(unidades2);
  LCD.print(decimales2);
  LCD.print('V');

  
}

//---------------------------------------------------------------------------------------------------------------------
//Lector analogico de voltajes
//---------------------------------------------------------------------------------------------------------------------
void LectorVoltajes(void){
  V1 = analogReadMilliVolts(Voltaje1);
  V2 = analogReadMilliVolts(Voltaje2);

  //Conversor de decenas, unidades y decimales para V1
  decenas1 = V1/10;
  unidades1 = V1 - decenas1*10;
  decimales1 = (V1*10) - (decenas1*100) - (unidades1*10); 

  //Conversor de decenas, unidades y decimales para V2
  decenas2 = V2/10;
  unidades2 = V2 - decenas1*10;
  decimales2 = (V2*10) - (decenas2*100) - (unidades2*10); 
}

//---------------------------------------------------------------------------------------------------------------------
//Contador
//---------------------------------------------------------------------------------------------------------------------
void Contador(void){
  if (digitalRead(Incremento)==1){
    delay(20);
    if (digitalRead(Incremento)==0){
      contador++; 
    }
  }

  if (digitalRead(Decremento)==1){
    delay(20);
    if (digitalRead(Decremento)==0){
      contador--; 
    }
  }
}