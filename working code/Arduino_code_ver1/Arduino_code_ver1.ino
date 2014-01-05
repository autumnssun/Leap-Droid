

/*
 *PROJECT: LEAPDROID 
 *PLATFORM ARDUINO
 *STATE: PROTOTYPING
 *--------------------------------------
 *Arduino code version 2
 *Description:
 *Listen to the serial xbee AT- AT connection
 *the message should comein in as a string 
 *starts with @ and ends with # 
 *the value then will be update to the servo pins as PWM signnal
 *adding json library for ease of accessing the data
*/
 
#include <XBee.h>
#include<Servo.h>
#include <aJSON.h>
String stack;
boolean stacking;

int r_1 = 6; //pin 6
int r_2 = 7; //pin 7
int r_3 = 8; //pin 8
int r_4 = 9; //pin 9

Servo rotor1, rotor2, rotor3, rotor4;

int rotor1_val=0, rotor2_val=0, rotor3_val=0, rotor4_val=0;// storing the value from the serial control.
int r1_his_val=0, r2_his_val=0, r3_his_val=0, r4_his_val=0;// store the value of the previous speed.

XBee xbee = XBee();

void setup() {
  Serial.begin(9600);
  //setup_rotors();
  //arms_escs();
}


void loop() {
  packageListener();
  // after listen to package the value from the serial should be stored in 4 variables.
  update_rotors_speed();
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

void arms_escs(){
   // Arm all 4 esc at once
  int speed;
  for(speed = 0; speed <= 100; speed+= 1){
    updateSpeed(speed,rotor1,0,180);
    updateSpeed(speed,rotor2,0,180);
    updateSpeed(speed,rotor3,0,180);
    updateSpeed(speed,rotor4,0,180);
    delay(10);
  }
  delay(1000);  
  for(speed = 100; speed >0; speed -=1){
    //updateSpeed(speed);
    updateSpeed(speed,rotor1,0,180);
    updateSpeed(speed,rotor2,0,180);
    updateSpeed(speed,rotor3,0,180);
    updateSpeed(speed,rotor4,0,180);
    delay(10); 
  }
}

void updateSpeed(int speed,Servo rot, int lowVal, int highVal){
  // speed is from 0 to 100 where 0 is off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  int angle = map(speed, lowVal, highVal, 0, 180);
  Serial.write("speed=");
  Serial.println(angle);
  rot.write(angle);
}

void update_rotors_speed(){
 /*Check if the update value change too low 
 *compare to the previous value 
 *then adjust the changes to avoid dammmaging the droid.
 */
 Serial.println(rotor1_val);
 Serial.println(rotor2_val);
 Serial.println(rotor3_val);
 Serial.println(rotor4_val);
}

void reset_rotors_value(){
  // reset the rotors values
  rotor1_val=0;
  rotor2_val=0;
  rotor3_val=0;
  rotor4_val=0;
}

void packageListener(){
  // expecting: @this is the message#
  int counting=0;
  
  if (Serial.available()>0){    
    char val=Serial.read();
    String chr=String(val);
    
    if (chr=="@"){
      stacking=true; // start stacking
      Serial.println("Start Stacking");
    }else{
      if(chr=="#"){ 
        stacking=false;
        Serial.println("Stop Stacking");
        rotor4_val=stack.toInt();// if see the end of the package save the stack to value 4
        stack=""; //after printing the stack, reset the stack 
        //Serial.flush();
      }else{
        if (stacking){
          stack+=chr; //read the character and add it in the stack  
          if (chr==","){
            if (counting==0){
               rotor1_val=stack.toInt();
              stack="";
            }else
            if (counting==1){
              rotor2_val=stack.toInt();
              stack="";
            }else
            if (counting==2){
              rotor3_val=stack.toInt();
              stack="";
            }
          }
        } 
      }
    }   
  }  
}
