/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <XBee.h>
char val;
String stack;
boolean stacking;

/*
This example is for Series 2 XBee
Receives a ZB RX packet and sets a PWM value based on packet data.
Error led is flashed if an unexpected packet is received
*/

XBee xbee = XBee();

void setup() {

  // start serial
  Serial.begin(9600);
  xbee.begin(Serial);
  myServo.attach(9);
  myArm();
  //flashLed(statusLed, 3, 50);// flash 3 times with the interval of 50 miliseconds in between
}

// continuously reads packets, looking for ZB Receive or Modem Status
void loop() {
  
  if (Serial.available()>0){
    val=Serial.read();
    String com=String(val);
    if (com=="@"){
      stacking=true;
      //Serial.println("Start stacking");
    }else if(com=="#"){
      stacking=false;
      Serial.println(stack);// update the sevo thing
      setSpeed(int(stack));
      stack="";
      //Serial.println("Stop stacking");
      Serial.flush();
    }else{
      if (stacking){
        stack+=com;
      }
    }   
  }
}

void myArm(){
  int speed;
  for(speed = 0; speed <= 100; speed+= 1){
    setSpeed(speed);
    delay(100);
  }
  delay(1000);  
  for(speed = 100; speed >0; speed -=1){
    setSpeed(speed);
    delay(100); 
  }

}

void setSpeed(int speed)
{
  // speed is from 0 to 100 where 0 is off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  int angle = map(speed, 0, 100, 0, 180);
  Serial.write("speed=");
  Serial.println(angle);
  myServo.write(angle);
  
}
