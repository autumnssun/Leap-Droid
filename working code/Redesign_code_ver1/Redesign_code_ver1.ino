// Re-desgin approarch for the quacopter.
// Learn from PID: Try to balance the quadcopter, 
// and monitor the sensor reading
// Basicaly the idea is try to alter the sensor reading to the
// balace reading.
#include <Wire.h>
#include <Servo.h>
#include <ADXL345.h>
#include <L3G4200D.h>// Gyrocopter library
#include <HMC5883.h> // Compass library

ADXL345 accel;
L3G4200D gyro;
HMC5883 compass;

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
double accel_x,accel_y,accel_z;
int commaIndex;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  
  accel.enableDefault();
  gyro.enableDefault();
  compass.enableDefault();
  
  Serial.println("Count,G_X,G_Y,G_Z,A_X,A_Y,A_Z,C_X,C_Y,C_Z");
   //TODO
   // setup the quadcopter arm motor
   // setup all the sensors
}

boolean stable(){
  return true;
}

void loop(){
  gyro.read();
  compass.read();
  accel.read();
  //
  if(stable()){
  }else{
    //make change to motor accordingly
  }
}

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
          case 1:speeds[0]=stack.toInt(); break;
          case 2:speeds[1]=stack.toInt(); break;
          default:speeds[2]=stack.toInt(); break;
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

void setup_rotors(){  
  for (int i=0;i<4;i++){
    motor[i].attach(pins[i]);
    speeds[i]=30;
  }
  setRotorSpeed();
  delay(2000); 
}

void setRotorSpeed(){
  //speeds array contains 4 values each should range from 30-179
  for (int i=0;i<4;i++){
    if (speeds[i]>lowLimit&& speeds[i]<highLimit){
      //if i is equal to 3 then write the speed with compensation value, otherwise just write the speed
      (i==3)?(motor[i].write(speeds[i]-compensation)):(motor[i].write(speeds[i]));
    }
  }
}

void land(){
  Serial.println("Landing");
}

void pitch (float angle){
}

void roll (float angle){
}

void yawn (float angle){
}

void accending(float height){
}

void decending(float height){
}


