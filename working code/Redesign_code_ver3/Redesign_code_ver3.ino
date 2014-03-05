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

// Re-desgin approarch for the quacopter.
// Learn from PID: Try to balance the quadcopter, 
// and monitor the sensor readings
// Basicaly the idea is try to alter the sensor reading to the
// balace reading.
// modify the motor array and put it back to the main 
// arduino class


#include <Servo.h>
#include <Wire.h>
//Sensors libraries.
#include <ADXL345.h>   // Accelerometer library
#include <L3G4200D.h>  // Gyrocopter library
#include <HMC5883.h>   // Compass library

#include <QUADCOPTER.h>//My quadcopter library
#include <math.h>
int servoCount=4;
Servo motors[4];
int const pins[4]={3,5,7,8};
double spd[4]={30,30,30,30};

L3G4200D gyro;
ADXL345 accel;
HMC5883 compass;

float fXg,fYg,fZg,alpha=0.5;
void setup(){
  Serial.begin(115200);
  Wire.begin();
  setupDroid();
  
  
  /*Start up all the sensor before the motors*/
  accel.enableDefault();
  compass.enableDefault();
  gyro.enableDefault();
}

void loop(){
  //Reads sensors informations
  gyro.read();
  compass.read();
  accel.read();
  
  //Print out variables for debug
  //printDebug('a');
  //printDebug('g');
  printJsonPitchYawn();
  
  Serial.println();
}

void setupDroid(){
  
  for (int i=0;i<4;i++){
    motors[i].attach(pins[i]);
    motors[i].write(30);
  }
  delay(2000);
  takeOff();
}
void takeOff(){
  double cache[4]={60,60,60,60};
  setRotorSpeed(cache);
}
void setRotorSpeed(double spds[4] ){
  for (int i=0;i<4;i++){
      motors[i].write(spds[i]);
  }
}

void printJsonPitchYawn (){
    double pitch, roll, yaw;
    fXg = accel.g.x * alpha + (fXg * (1.0 - alpha));
    fYg = accel.g.y * alpha + (fYg * (1.0 - alpha));
    fZg = accel.g.z * alpha + (fZg * (1.0 - alpha));
    
     /*Roll and Pitch Equations*/
    roll  = (atan2(-fYg, fZg)*180.0)/M_PI;
    pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;

    Serial.print("{\"pitch\":");
    Serial.print(pitch-11.4);
    Serial.print(",\"roll\":");
    Serial.print(roll-5.6);
    Serial.println("}");
    
    delay(10);
}


void printDebug(char type){
  double x,y,z;
  if (type=='a'){
     x=accel.g.x;
     y=accel.g.y;
     z=accel.g.z;
  }else if(type=='g'){
     x=gyro.g.x;
     y=gyro.g.y;
     z=gyro.g.z;
  }else{
     x=compass.g.x;
     y=compass.g.y;
     z=compass.g.z;
  }
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.print(",");
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

