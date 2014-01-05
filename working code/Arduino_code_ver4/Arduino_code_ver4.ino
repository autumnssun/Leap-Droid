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
*/
 
#include<Servo.h>

// Declare some global variables
String stack;
boolean stacking;
int index;
boolean greenLight=false;

//those are the rotor pin,
const int p_1 = 6, p_2 = 7, p_3 = 8, p_4 = 9; //pin 9

Servo rotor1, rotor2, rotor3, rotor4;

int r1_val=0, r2_val=0, r3_val=0, r4_val=0;// storing the value from the serial control.
int r1_his_val=0, r2_his_val=0, r3_his_val=0, r4_his_val=0;// store the value of the previous speed.


void setup() {
  Serial.begin(9600);
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
  
   // Arm all 4 esc at once
  int speed;
  for(speed = 0; speed <= 100; speed+= 1){
    setRotorSpeed(speed,rotor1);
    setRotorSpeed(speed,rotor2);
    setRotorSpeed(speed,rotor3);
    setRotorSpeed(speed,rotor4);
    delay(5);
  }
  delay(2000);  
  for(speed = 100; speed >0; speed -=1){
    //updateSpeed(speed);
    setRotorSpeed(speed,rotor1);
    setRotorSpeed(speed,rotor2);
    setRotorSpeed(speed,rotor3);
    setRotorSpeed(speed,rotor4);
    delay(5); 
  }
  delay(2000);
  
  /* ARMING PROCESS FOR SKYWALER 20C
  * After armed start the rotor
  */
  
  setRotorSpeed(30,rotor1);
  setRotorSpeed(30,rotor2);
  setRotorSpeed(30,rotor3);
  setRotorSpeed(30,rotor4);
    
  
  Serial.println("{A}");
  greenLight=true;
//  if(Serial.available()>0&&!greenLight){
//    String confirm=Serial.readString();
//    Serial.println(confirm);
//    if (confirm=="{B}"){
//      Serial.println("Greenlight is on");
//      greenLight=true;
//    }
//  }
}

void setRotorSpeed(int speed,Servo rot){
  // speed is from 0 to 100 where 0 is off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  //Serial.write("speed=");
  //Serial.println(speed);
  rot.write(speed);
}

//package listener is called by the main loop
void packageListener(){
  if (Serial.available()>0){
    //Serial.println(Serial.readString());
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
      Serial.println(r1_val);
      Serial.println(r2_val);
      Serial.println(r3_val);
      Serial.println(r4_val);
      Serial.flush();
    }else
   
    
    if (stacking){
      if (chr==","){
       index++;
       //Serial.println(index);
       switch (index) {
          case 1:
            //do something when var equals 1
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
  }  
}

