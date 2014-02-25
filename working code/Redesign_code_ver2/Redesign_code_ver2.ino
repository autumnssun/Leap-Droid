// Re-desgin approarch for the quacopter.
// Learn from PID: Try to balance the quadcopter, 
// and monitor the sensor reading
// Basicaly the idea is try to alter the sensor reading to the
// balace reading.

// TRY TO INTEGRATING QUADCOPTER LIBARY. 
#include <Wire.h>
#include <Servo.h>
#include <ADXL345.h>   // Accelerometer library
#include <L3G4200D.h>  // Gyrocopter library
#include <HMC5883.h>   // Compass library
#include <QUADCOPTER.h>//My quadcopter library

ADXL345 accel;
L3G4200D gyro;
HMC5883 compass;
QUADCOPTER quad;
float fXg,fYg,fZg,alpha=.5;
// Declare some global variables
void setup(){
  Serial.begin(115200);
  Wire.begin();
  
  quad.setupQuadcopter();
  accel.enableDefault();
  gyro.enableDefault();
  compass.enableDefault();
}

void loop(){
  gyro.read();
  compass.read();
  accel.read();
  quad.readSerial();
  //printDebug('a');
  printJsonPitchYawn();
  //Serial.println();
}
void printJsonPitchYawn (){
    double pitch, roll;
    
    fXg = accel.g.x * alpha + (fXg * (1.0 - alpha));
    fYg = accel.g.y * alpha + (fYg * (1.0 - alpha));
    fZg = accel.g.z * alpha + (fZg * (1.0 - alpha));
    
    Serial.print("{\"pitch\":");
    Serial.print(fXg);
    Serial.print(",\"yaw\":");
    Serial.print(fYg);
    Serial.print(",\"roll\":");
    Serial.print(fZg);
    Serial.println("}");
    
    //Roll and Pitch Equations
//    roll  = (atan2(-fYg, fZg)*180.0)/M_PI;
//    pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;
    
//    Serial.print("{\"pitch\":");
//    Serial.print(pitch);
//    Serial.print(",\"roll\":");
//    Serial.print(roll);
//    Serial.println("}");
    
//    Serial.print(pitch);
//    Serial.print(":");
//    Serial.println(roll);
    delay(10);
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

