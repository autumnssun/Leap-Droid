#include <IMU.h>
#include <Wire.h>  

IMU imu;
boolean debug=true;
float alphaFillter=0.93;//lowpassfilter
float betaFilter=0.5;//combination filter
int zeroRateSample=10;
void setup(){
  Serial.begin(115200);
  Wire.begin();
  imu.start(debug,alphaFillter,betaFilter,zeroRateSample);
}
 
void loop(){
  imu.readsensors();
  buckprint();
}

void buckprint(){
  Serial.print("{");
  Serial.print("ax:");
  Serial.print(imu.accel.x,DEC);
  Serial.print(",");
  Serial.print("ay:");
  Serial.print(imu.accel.y,DEC);
  Serial.print(",");
  Serial.print("az:");
  Serial.print(imu.accel.z,DEC);
  Serial.print(",");
  Serial.print("TimeStamp:");
  Serial.print(imu.accel.timestamp,DEC);
  
  
//  Serial.print("gx:");
//  Serial.print(imu.gyro.x,DEC);
//  Serial.print(",");
//  Serial.print("gy:");
//  Serial.print(imu.gyro.y,DEC);
//  Serial.print(",");
//  Serial.print("gz:");
//  Serial.print(imu.gyro.z,DEC);
//  Serial.print(",");
//  Serial.print("TimeStamp:");
//  Serial.print(imu.gyro.timestamp,DEC);

//  Serial.print(",");
//  Serial.print("mx:");
//  Serial.print(imu.magn.x,DEC);
//  Serial.print(",");
//  Serial.print("my:");
//  Serial.print(imu.magn.y,DEC);
//  Serial.print(",");
//  Serial.print("mz:");
//  Serial.print(imu.magn.z,DEC);  
  Serial.print("}");
  Serial.println();
}
