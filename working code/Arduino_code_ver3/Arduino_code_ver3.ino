/*
 *PROJECT: LEAPDROID 
 *PLATFORM ARDUINO
 *STATE: PROTOTYPING
 *--------------------------------------
 *Arduino code version 3
 *Description:
 *Listen to the serial xbee AT- AT connection
 *the message should comein in as a string 
 *starts with @ and ends with # 
 *the value then will be update to the servo pins as PWM signnal
 *adding json library for ease of accessing the data
 
 {123,333,121,111}
*/
 
#include<Servo.h>

// Declare some global variables
String stack;
boolean stacking;
//those are the rotor pin,
int r_1 = 6; //pin 6
int r_2 = 7; //pin 7
int r_3 = 8; //pin 8
int r_4 = 9; //pin 9


Servo rotor1, rotor2, rotor3, rotor4;
int rotor1_val=0, rotor2_val=0, rotor3_val=0, rotor4_val=0;// storing the value from the serial control.
int r1_his_val=0, r2_his_val=0, r3_his_val=0, r4_his_val=0;// store the value of the previous speed.
int index;

boolean synced=false;


void setup() {
  Serial.begin(9600);
  //setup_rotors();
  //arms_escs();
  if(!synced&&armed){
    //keep arming
    
  }else{
    Serial.println("{ready for flying}");
  }
}


void loop() {
  flyCommandsListener();
  // after listen to package the value from the serial should be stored in 4 variables.
}

void flyCommandsListener(){
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
      rotor4_val=stack.toInt();
      printSerial();
      Serial.flush();
    }else
   
    
    if (stacking){
      if (chr==","){
       index++;
       //Serial.println(index);
       switch (index) {
          case 1:
            //do something when var equals 1
            rotor1_val=stack.toInt();
            break;
          case 2:
            rotor2_val=stack.toInt();
            break;
          default: 
            rotor3_val=stack.toInt();
            // if nothing else matches, do the default
            // default is optional
        }
        stack="";
      }else{
        stack+=chr; //read the character and add it in the stack  
      }
    }
  }  
}

void printSerial(){
  Serial.println(rotor1_val);
  Serial.println(rotor2_val);
  Serial.println(rotor3_val);
  Serial.println(rotor4_val); 
}
