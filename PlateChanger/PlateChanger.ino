#include "DualTB9051FTGMotorShield.h"

DualTB9051FTGMotorShield md;


//variables de sensor
int estadoActualStart = 0;
int estadoAnteriorStart =0;
int estadoActualStop = 0;
int estadoAnteriorStop =0;

int valueSensor = 0;
int bufferSensor =0;
int finalValue = 0;
int estadoActualSensor = 0;
int estadoAnteriorSensor = 0;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long currentMillis2;
unsigned long startMillis2; 

int bandera1=0;
int bandera2=0;
int bandera3=0;
int bandera4=0;

int count = 0;

int velocidad = 175;
int AnRead = 0;

long debouncing_time = 50; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


////falling ramp
int y1=velocidad;
int x1=0;
int y2=0;
int x2=75;
int OneStep=0;

void setup() {
  // put your setup code here, to run once:
 // pinMode(A3,INPUT); ////sensor hall 
  pinMode(A3,INPUT_PULLUP); ////start
  pinMode(A4,INPUT_PULLUP); ///stop
  
  pinMode(2,INPUT); ///fordward
  pinMode(3,INPUT); ///backward

  //attachInterrupt(digitalPinToInterrupt(3), debounceInterrupt, RISING);
  Serial.begin(9600);
  md.init();
  delay(5);
  startMillis=millis();
  startMillis2=millis();
  }

void loop() {
   currentMillis = millis();
   currentMillis2 = millis();
   md.enableDrivers();
  // put your main code here, to run repeatedly:
   AnRead = analogRead(A2);
   //Serial.println(AnRead);

   ////lectura de pines
   estadoActualStart = digitalRead(A3);
   estadoActualStop  = digitalRead(A4);

   estadoActualSensor = digitalRead(3);
  // Serial.println(estadoActualStop);

 
  
   
   if(estadoActualStart!=estadoAnteriorStart){
    //Serial.println("Start activado");
      if(estadoActualStart == LOW){
         ///activar estados
         Serial.println("Start activado");
         bandera1 = 1;
         //md.setM2Speed(150);
        }
    }
   estadoAnteriorStart = estadoActualStart;



   if(estadoActualStop!=estadoAnteriorStop){
      if(estadoActualStop == LOW){
         ///para ciclo estados
         Serial.println("stop activado");
         md.setM2Speed(0);
         bandera2=0;
         bandera1=0;
        }
    }
    estadoAnteriorStop = estadoActualStop; 

 
   if(bandera1 == 1){
    
      md.setM2Speed(-230);
      if(estadoActualSensor!=estadoAnteriorSensor){
      //  Serial.println(estadoActualStop);
      if(estadoActualStop == HIGH){
         ///para ciclo estados
         Serial.println("sensor  activado");
         bandera2=1;
         bandera1=0;
        }
         estadoAnteriorSensor = estadoActualSensor; 
    }
   
    }
//   
//    
//   if(OneStep<x2 && bandera2==1){
//    ///rampa
//      
//   if (currentMillis - startMillis >= 5)
//  {
//      float P = (((y2-y1)*OneStep/(x2-x1)))+y1;
//
//     
//      int vel2=(int)P;
//      OneStep++;
//      md.setM2Speed(vel2);
//      startMillis = currentMillis;
//     
//       if(OneStep>=x2){
//       
//        bandera2=0;
//        bandera3=1;
//        OneStep=0;
//      }
//  }
//      
//      
//    }


  if(bandera2 == 1){
     estadoAnteriorSensor = estadoActualSensor; 
    delay(900);
    estadoAnteriorSensor = estadoActualSensor; 
    Serial.println(estadoActualSensor-estadoAnteriorStop);
      md.setM2Speed(0);
     if(currentMillis2 - startMillis2 >= 6000){
         
       startMillis2 = currentMillis2; 
       bandera2=0;
       bandera1 = 1;
      }
    }
   
}


void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    blink();
    last_micros = micros();
  }
}

void blink() {
  int val = digitalRead(3);
    Serial.println(val);
    Serial.println("change");
  if(bandera1 == 1){
    bandera2=1;
    bandera1=0;
    }
    
         
}
