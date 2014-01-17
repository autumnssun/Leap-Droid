/*
 *PROJECT: LEAPDROID 
 *PLATFORM ARDUINO
 *STATE: PROTOTYPING
 *--------------------------------------
 *Arduino code version 5
 *Description:
 *Listen to the serial xbee AT- AT connection
 *the message should comein in as a string 
 *starts with { and ends with }
 *the value then will be update to the servo pins as PWM signnal
 2/Jan/2014 ADDED function
 *the rotor is armed and set to a certain speed before it can be controlled
 *by the server
 9/Jan/2014 - ADDED function
 *TIme and increased bund rate for faster communication,
*/
 
#include <Servo.h>
#include <Event.h>
#include <Timer.h>
// Declare some global variables
String stack;
boolean handPresented=false,
        stacking=false,
        greenLight=false;
        
int const stableSpeed=90,
          stablizeTime=1000;

Servo motor[4];
int const pins[4]={3,5,7,9};
int speeds[4];

int commaIndex;
long timer;
int t=4;

void setup() {
  Serial.begin(115200);
  setup_rotors();
}

void loop() {
  rx();
}

//package listener is called by the main loop
boolean rx(){
  if(!Serial.available()){
    if (timer>115200*t){
      Serial.println("[auto]");
      timer=0;
    }
  }else{
    while (Serial.available()){
      //reset the stablizer timer.
      timer=0;
      char chr=(char) Serial.read();
      if (chr=='{'){
        stack="";//reset the stack
        stacking=true; // start stacking
      }
      
      if(chr=='}'){ 
        stacking=false;
        speeds[3]=stack.toInt();
        prt(speeds);
        commaIndex=0;
      }else{
        if (chr==','&&stacking){
         commaIndex++;
         switch (commaIndex) {
            case 1:
              speeds[0]=stack.toInt();
              break;
            case 2:
              speeds[1]=stack.toInt();
              break;
            default: 
              speeds[2]=stack.toInt();
          }
          stack="";
        }else{stack+=chr; /*read the character and add it in the stack*/}
      }
    }
  } 
  timer++;
}



void setup_rotors(){
  int speed;
  for (int i=0;i<4;i++){motor[i].attach(pins[i]);}
  for(speed = 0; speed <= 180; speed+= 1){
   for (int i=0;i<4;i++){speeds[i]=speed;}
    setRotorSpeed();
    delay(1);
  }
  delay(2000);  
  for(speed = 180; speed >0; speed -=1){
    for (int i=0;i<4;i++){speeds[i]=speed;}
    setRotorSpeed();
    delay(1); 
  }
  delay(2000);
  for (int i=0;i<4;i++){speeds[i]=stableSpeed;}
  setRotorSpeed();
}

void prt(int arr[4]){
   for (int i=0;i<4;i++){
     if(i=0){
       Serial.print(arr[i]);
     }else{
       Serial.print(" ");
       Serial.print(arr[i]);
     }
   }
   Serial.println();
}

void tx(String message){
  Serial.println(message);
}

void setRotorSpeed(){
  for (int i=0;i<4;i++){motor[i].write(speeds[i]);}
}
