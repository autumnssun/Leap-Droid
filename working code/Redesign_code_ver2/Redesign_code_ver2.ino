// Re-desgin approarch for the quacopter.
// Learn from PID: Try to balance the quadcopter, 
// and monitor the sensor reading
// Basicaly the idea is try to alter the sensor reading to the
// balace reading.

// TRY TO INTEGRATING QUADCOPTER LIBARY. 
#include <Wire.h>
#include <Servo.h>
#include <ADXL345.h>
#include <L3G4200D.h>// Gyrocopter library
#include <HMC5883.h> // Compass library
#include <QUADCOPTER.h>

ADXL345 accel;
L3G4200D gyro;
HMC5883 compass;
QUADCOPTER quad;
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
//
double accel_x,accel_y,accel_z;
int commaIndex;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  quad.setupQuadcopter();
  accel.enableDefault();
  gyro.enableDefault();
  compass.enableDefault();
  
  //Serial.println("Count,G_X,G_Y,G_Z,A_X,A_Y,A_Z,C_X,C_Y,C_Z");
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
  quad.readSerial();
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


