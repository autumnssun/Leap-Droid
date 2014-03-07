/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/
#include <ADXL345.h>
#include <PID_v1.h>
#include <Wire.h>
//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters (Kp=2, Ki=5, Kd=1)
PID myPID(&Input, &Output, &Setpoint,4,0,1, REVERSE);
ADXL345 accel;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  
  //initialize the variables we're linked to
  Setpoint = 0;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  accel.enableDefault();
  accel.read();
  accel.setZeroG(accel.g.x,accel.g.y,accel.g.z);
}

void loop()
{ 
  accel.read();
  Input = accel.g.x;
  myPID.Compute();
  Serial.print(Input);
  Serial.print(",");
  Serial.print(Output);
  delay(100);
  Serial.println();
}


