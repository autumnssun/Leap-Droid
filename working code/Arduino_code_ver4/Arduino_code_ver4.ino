/*
 *PROJECT: LEAPDROID 
 *PLATFORM ARDUINO
 *STATE: PROTOTYPING
 *--------------------------------------
 *Arduino code version 4
 *Description:
 *Listen to the serial xbee AT- AT connection
 *the message should comein in as a string 
 *starts with { and ends with }
 *the value then will be update to the servo pins as PWM signnal
 2/Jan/2014 ADDED function
 *the rotor is armed and set to a certain speed before it can be controlled
 *by the server
 9/Jan/2014 - ADDED function
 *Timer: for better auto flight control
*/
 
#include<Servo.h>
#include <Event.h>
#include <Timer.h>
#include <Time.h>

// Declare some global variables
String stack;
boolean stacking;
int index;
boolean greenLight=false;
int const stableSpeed=90;

//those are the rotor pin,
const int p_1 = 6, p_2 = 7, p_3 = 8, p_4 = 9; //pin 9

Servo rotor1, rotor2, rotor3, rotor4;

int r1_val=0, r2_val=0, r3_val=0, r4_val=0;// storing the value from the serial control.
int r1_his_val=0, r2_his_val=0, r3_his_val=0, r4_his_val=0;// store the value of the previous speed.


void setup() {
  Serial.begin(115200);
  setup_rotors();
}

void loop() {
  if(greenLight){
    packageListener();
  }
  // after listen to package the value from the serial should be stored in 4 variables.
}

void setup_rotors(){
  rotor1.attach(p_1);
  rotor2.attach(p_2);
  rotor3.attach(p_3);
  rotor4.attach(p_4);
  
   /* Arm all 4 esc at once
  * ARMING PROCESS FOR SKYWALER 20C
  * After armed start the rotor
  */
  
  int speed;
  for(speed = 0; speed <= 100; speed+= 1){
    setVariableSpeed(speed);
    delay(5);
  }
  delay(2000);  
  for(speed = 100; speed >0; speed -=1){
    setVariableSpeed(speed);
    delay(5); 
  }
  delay(2000);
  
  setStableSpeed();
  Serial.println("{A}");
  greenLight=true;
}



//package listener is called by the main loop
void packageListener(){
  if (Serial.available()>0){
    char val=Serial.read();
    String chr=String(val);
    if (chr=="{"){
      stack="";//reset the stack
      stacking=true; // start stacking
    }else
    if(chr=="}"){ 
      stacking=false;
      stack.replace(" ","");
      index=0;
      r4_val=stack.toInt();
      //this is for deaying
      long unixTime = now();
      Serial.println(r4_val-unixTime);
      
      Serial.flush();
      setRotorSpeed();
      prt();
    }else
   
    if (stacking){
      if (chr==","){
       index++;
       switch (index) {
          case 1:
            r1_val=stack.toInt();
            break;
          case 2:
            r2_val=stack.toInt();
            break;
          default: 
            r3_val=stack.toInt();
        }
        stack="";
      }else{
        stack+=chr; //read the character and add it in the stack  
      }
    }
  }else{
    
  }  
}

void reader(){
}

void prt(){
  Serial.println(r1_val);
  Serial.println(r2_val);
  Serial.println(r3_val);
  Serial.println(r4_val);
}

void setVariableSpeed(int sp){
  rotor1.write(sp);
  rotor2.write(sp);
  rotor3.write(sp);
  rotor4.write(sp);
}
void setRotorSpeed(){
  rotor1.write(r1_val);
  rotor2.write(r2_val);
  rotor3.write(r3_val);
  rotor4.write(r4_val);
  r1_his_val=r1_val;
  r2_his_val=r2_val;
  r3_his_val=r3_val;
  r4_his_val=r4_val;
}
void setStableSpeed(){
  rotor1.write(stableSpeed);
  rotor2.write(stableSpeed);
  rotor3.write(stableSpeed);
  rotor4.write(stableSpeed);
  r1_his_val=r2_his_val=r3_his_val=r4_his_val=stableSpeed;
}
