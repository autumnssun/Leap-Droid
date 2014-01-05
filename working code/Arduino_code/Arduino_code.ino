/*
 *PROJECT: LEAPDROID 
 *PLATFORM ARDUINO
 *STATE: PROTOTYPING
 *--------------------------------------
 *Arduino code version 1
 *Description:
 *Listen to the serial xbee AT- AT connection
 *the message should comein in as a string 
 *starts with @ and ends with # 
 *the value then will be update to the servo pins as PWM signnal
*/
 
#include <XBee.h>
String stack;
boolean stacking;

int r_1 = 6; //pin 6
int r_2 = 7; //pin 7
int r_3 = 8; //pin 8
int r_4 = 9; //pin 9

Servo rotor1; 
Servo rotor2;
Servo rotor3;
Servo rotor4;

XBee xbee = XBee();

void setup() {
  Serial.begin(9600);
  setup_rotors();
  arms_esc();
  
}


void loop() {
  listener();
}

void setup_xbee(){
  xbee.begin(Serial);
}

void setup_rotors(){
  rotor1.attach(r_1);
  rotor2.attach(r_2);
  rotor3.attach(r_3);
  rotor4.attach(r_4);
}

void listener(){
  if (Serial.available()>0){
    char val=Serial.read();
    String string=String(val);
    if (string=="@"){
      stacking=true;
    }else if(string=="#"){
      stacking=false;
      Serial.println(stack);// update the sevo thing
      setSpeed(int(stack)); // set the speed to the motor
      stack=""; // reset the stack
      Serial.flush();
    }else{
      if (stacking){stack+=string;}
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

void updateSpeed(int speed,rot)
{
  // speed is from 0 to 100 where 0 is off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  int angle = map(speed, 0, 100, 0, 180);
  Serial.write("speed=");
  Serial.println(angle);
  myServo.write(angle);
  
}
