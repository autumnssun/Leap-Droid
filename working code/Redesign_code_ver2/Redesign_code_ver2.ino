// Re-desgin approarch for the quacopter.
// Learn from PID: Try to balance the quadcopter, 
// and monitor the sensor readings
// Basicaly the idea is try to alter the sensor reading to the
// balace reading.

#include <Wire.h>
#include <Servo.h>
#include <ADXL345.h>   // Accelerometer library
#include <L3G4200D.h>  // Gyrocopter library
#include <HMC5883.h>   // Compass library
#include <QUADCOPTER.h>//My quadcopter library
#include <math.h>


//L3G4200D gyro;
ADXL345 accel;
HMC5883 compass;
QUADCOPTER quad;
float fXg,fYg,fZg,alpha=0.7;
int a[]={123,330,120,140};
void setup(){
  Serial.begin(115200);
  Wire.begin();
  
  /*Start up all the sensor before the motors*/
  
  //accel.enableDefault();
  //compass.enableDefault();
  //gyro.enableDefault();
  quad.setupQuadcopter();
  //quad.setRotorSpeed(a);
}

void loop(){
  //gyro.read();
  //compass.read();
  //accel.read();
  //printJsonPitchYawn();
  //quad.readSerial();
  //quad.motors[3].write(70);
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
     //x=gyro.g.x;
     //y=gyro.g.y;
     //z=gyro.g.z;
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

