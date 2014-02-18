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
 try arming each motor seperately might help.
*/
 
#include <Servo.h>
// Declare some global variables
String stack;
boolean handPresented=false,
        stacking=false,
        greenLight=false,
        autoPilotOn=true;

int const stableSpeed=70,
          compensation=1,
          lowLimit=29,
          highLimit=140;
          
Servo motor[4];
int const pins[4]={3,5,7,8};
int speeds[4];


int commaIndex;

void setup() {
  Serial.begin(115200);
  setup_rotors();
}

void loop() {
  rx();
  if (autoPilotOn){
    autoPilot();
  }else{
    setRotorSpeed();
  }

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
      //print out the result
      prt();
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
  Serial.println("auto");
  //for now just set the speed to stable speed,
  //TODO: adding auto balancing code using input from the sensor.
  for (int i=0;i<4;i++){
    speeds[i]=stableSpeed;
  }
  setRotorSpeed();
}

void land(){
  Serial.println("Landing");
}


void setup_rotors(){  
  for (int i=0;i<4;i++){
    motor[i].attach(pins[i]);
  }
  for (int i=0;i<4;i++){
    speeds[i]=30;
  }
  setRotorSpeed();
  delay(2000); 
  
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
    if (speeds[i]>lowLimit&& speeds[i]<highLimit){
      if(i==3){
        motor[i].write(speeds[i]-compensation);
      }else{
        motor[i].write(speeds[i]);
      }
    }
  }
  prt();
}
