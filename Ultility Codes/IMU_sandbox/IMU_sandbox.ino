#include <IMU.h>
#include <Wire.h>

IMU imu;
boolean debug=true;
float alphaFillter=0.5;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  imu.start(debug,alphaFillter);
}

void loop(){
  imu.readsensors();
}
