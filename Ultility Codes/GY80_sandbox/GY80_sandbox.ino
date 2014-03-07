#include <IMU.h>
#include <Wire.h>

float accel_v[3];

IMU imu;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  sensors.Accel_Init();
  sensors.Gyro_Init();
  sensors.Magn_Init();
}

void loop(){
  sensors.Read_Accel(accel_v);
  Serial.println(accel_v[0]);
}
