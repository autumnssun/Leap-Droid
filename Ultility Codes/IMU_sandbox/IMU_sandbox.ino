#include <IMU.h>
#include <Wire.h>

IMU imu;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  imu.start();
}

void loop(){
  imu.read();
  Serial.print(imu.gyro.x);
  Serial.print(',');
  Serial.print(imu.gyro.y);
  Serial.print(',');
  Serial.print(imu.gyro.z);
  Serial.print(',');
  Serial.print(imu.accel.x);
  Serial.print(',');
  Serial.print(imu.accel.y);
  Serial.print(',');
  Serial.print(imu.accel.z);
  Serial.print(',');
  Serial.print(imu.magn.x);
  Serial.print(',');
  Serial.print(imu.magn.y);
  Serial.print(',');
  Serial.print(imu.magn.z);
  Serial.println(',');
}
