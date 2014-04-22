#include <IMU.h>
#include <Wire.h>

IMU imu;
boolean debug=true;
float alphaFillter=0.85;//lowpassfilter
float betaFilter=0.5;//combination filter
int zeroRateSample=10;
void setup(){
  Serial.begin(115200);
  Wire.begin();
  imu.start(debug,alphaFillter,betaFilter,zeroRateSample);
}
 
void loop(){
  imu.readsensors();
  Serial.print("{gx:");
  Serial.print(imu.gyro.x);
  Serial.print(",");
  Serial.print("gy:");
  Serial.print(imu.gyro.y);
  Serial.print(",");
  Serial.print("gz:");
  Serial.print(imu.gyro.z);
  Serial.print(",");
  Serial.print("ax:");
  Serial.print(imu.accel.x);
  Serial.print(",");
  Serial.print("ay:");
  Serial.print(imu.accel.y);
  Serial.print(",");
  Serial.print("az:");
  Serial.print(imu.accel.z);
  Serial.print("}");
  Serial.println();
}
