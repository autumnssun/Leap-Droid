#include "Arduino.h"
#include "QUADCOPTER.h"
#include "Wire.h"
#include "Servo.h"
#include "string.h"

const int a = 3;             
const int b = 5;              
const int c = 7;
const int d = 8;

QUADCOPTER::QUADCOPTER()
{
	    handPresented=false, 
		stacking=false,
		greenLight=false,
		autoPilotOn=true;
	    stableSpeed=70,
		lowLimit=29, 
		highLimit=140,
		compensation=0.4;
		
}

void QUADCOPTER::setupQuadcopter(void)
{	
	int servoPins[SERVOS]={a,b,c,d};
	
	for (int i=0; i<SERVOS;i++){	
		//For some reason every time we want to write the speed, 
		//you need to attache the servo to the pin
		motors[i].attach(servoPins[i]);		
		motors[i].write(30);
  	  
	  Serial.print("speed of motor [");
  	  Serial.print(i);
  	  Serial.print("]= ");
  	  Serial.println(motors[i].read());
  	  motors[i].write(speeds[i]);
	  
	}
	delay(2000);
	Serial.println("________________________");
	//takeOff();
	
}

void QUADCOPTER::setRotorSpeed()
{	
	//const int servoPins[SERVOS]={3,5,7,8};
	
}

void QUADCOPTER::setRotorSpeed(int a[])
{
	int servoPins[SERVOS]={a,b,c,d};
	
	for (int i=0;i<SERVOS;i++){
		motors[i].attach(servoPins[i]);
		Serial.print("Change motor [");
		Serial.print(i);
		Serial.print("] on pin ");
		Serial.print(servoPins[i]);
		Serial.print(" from ");
		Serial.print(motors[i].read());
		Serial.print(" to ");
    	motors[i].write(a[i]);	
		Serial.println(motors[i].read());
  	}
	delay(10);
}

void QUADCOPTER::readSerial()
{
	while (Serial.available()){
    int chr_raw= Serial.read();
	char chr=(char) chr_raw;
    if (chr=='{'){
      //reset the stack
      memset(stack,0, sizeof(stack));
      stacking=true; // start stacking
    }
    if(chr=='}'){ 
      stacking=false;
      speeds[3]=atoi(stack);
      commaIndex=0;
      break;
    }else{
      if (chr==','){
       commaIndex++;
       switch (commaIndex) {
          case 1:speeds[0]=atoi(stack); break;
          case 2:speeds[1]=atoi(stack); break;
          default:speeds[2]=atoi(stack);break;
        }
        memset(stack,0, sizeof(stack));
      }else
      if (chr!='{'){
        //Do more trick here
        if(chr=='A'){autoPilotOn=true;}
        if(chr=='L'){land();}
        else{
          autoPilotOn=false;
          stack=appendCharToCharArray(stack,chr);
          
          //read the character and add it in the stack
        }
      }
    }
  }
}

char* QUADCOPTER::appendCharToCharArray(char* array, char a)
{
    size_t len = strlen(array);
    char* ret = new char[len+2];
    strcpy(ret, array);    
    ret[len] = a;
    ret[len+1] = '\0';
    Serial.println(ret);
    return ret;
}
void QUADCOPTER::pitch(float angle){
}

void QUADCOPTER::yawn(float angle){
}

void QUADCOPTER::roll(float andle){
}

void QUADCOPTER::takeOff(void){
	for (int i=0; i<SERVOS;i++){	
		motors[i].attach(servoPins[i]);
		motors[i].write(70);
	}
}

void QUADCOPTER::land(){
}

void QUADCOPTER::accending(float andle){
}

void QUADCOPTER::decending(float andle){
}
