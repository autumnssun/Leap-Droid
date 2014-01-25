/*
 *PROJECT: LEAPDROID 
 *PLATFORM ARDUINO
 *STATE: PROTOTYPING
 *--------------------------------------
 *Arduino code version 6
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
 15/Jan/2014
 Threading for tx and rx
*/
 
#include <Servo.h>
// Declare some global variables
String stack;
boolean handPresented=false,
        stacking=false,
        greenLight=false,
        autoPilotOn=true;

int const stableSpeed=120;
Servo motor[4];
int const pins[4]={3,5,7,9};
int speeds[4];

int commaIndex;

void setup() {
  Serial.begin(115200);
  //setup_rotors();
}

void loop() {
  rx();
  setRotorSpeed();
  prt();
}

//package listener is called by the main loop
void rx(){
  while (Serial.available()){
    char chr=(char) Serial.read();

    if (chr=='{'){
      stack="";//reset the stack
      stacking=true; // start stacking
    }
    if(chr=='}'){ 
      stacking=false;
      speeds[3]=stack.toInt();
      commaIndex=0;
      break;
    }else{
      if (chr==','){
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
      }else
      if (chr!='{'){
        //Do more trick here
        if(chr=='A'){autoPilotOn=true;}
        if(chr=='L'){}
        else{
          autoPilotOn=false;
          stack+=chr; /*read the character and add it in the stack*/
        }
      }
    }
  }
}

void prt(){
  Serial.print(speeds[0]);
  Serial.print(" ");
  Serial.print(speeds[1]);
  Serial.print(" ");
  Serial.print(speeds[2]);
  Serial.print(" ");
  Serial.println(speeds[3]);
}


void setRotorSpeed(){
  for (int i=0;i<4;i++){
    motor[i].write(speeds[i]);
  }
}

