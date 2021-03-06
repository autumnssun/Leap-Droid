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
 24/Jan/2014 
 Problem: ESC not armed properply.... 
 trying to port from the example to make thing works beter.
*/
 
#include <Servo.h>
// Declare some global variables
String stack;
boolean handPresented=false,
        stacking=false,
        greenLight=false,
        autoPilotOn=true;

int const stableSpeed=80;
Servo motor[4];
int const pins[4]={3,5,7,9};
int speeds[4];

int commaIndex;

void setup() {
  Serial.begin(115200);
  setup_rotors();
}

void loop() {
//  Serial.println("Hello leap");
//  delay(3000);
//  rx();
//  prt();
//  if (autoPilotOn){
//    autoPilot();
//  }else{
//    setRotorSpeed();
//  }

  swipe();
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
        if(chr=='L'){land();}
        else{
          autoPilotOn=false;
          stack+=chr; /*read the character and add it in the stack*/
        }
      }
    }
  }
}

void autoPilot(){
  Serial.println("auto piloting");
}

void land(){
  Serial.println("Landing");
}


void setup_rotors(){  
  
  for (int i=0;i<4;i++){
    motor[i].attach(pins[i]);
  }
  
  //arming code port form arm_demo
  for (int i=0;i<4;i++){
    speeds[i]=50;
  } 
  setRotorSpeed();
  delay(1000);
  
  for (int i=0;i<4;i++){
    speeds[i]=179;
  }
  setRotorSpeed();
  
// int speed;
//  for(speed = 0; speed <= 180; speed+= 1){
//    for (int i=0;i<4;i++){
//      speeds[i]=speed;
//    }
//    setRotorSpeed();
//    delay(50);
//  }
//  delay(2000);  
//  for(speed = 180; speed > 0; speed -=1){
//    for (int i=0;i<4;i++){speeds[i]=speed;}
//    setRotorSpeed();
//    delay(); 
//  }
//  delay(2000);
//  for (int i=0;i<4;i++){speeds[i]=stableSpeed;}
//  setRotorSpeed();
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
  //speeds array contains 4 values each should range from 30-179
  for (int i=0;i<4;i++){
    motor[i].write(speeds[i]);
  }
}


void swipe(){
  for(int v = 50; v < 180; v+= 1){
    for (int i=0;i<4;i++){
      speeds[i]=v;
    }
    setRotorSpeed();
    delay(50);
  }
}
