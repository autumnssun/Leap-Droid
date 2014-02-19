#include "Arduino.h"
#include "QUADCOPTER.h"
#include "Wire.h"
#include "Servo.h"
#include "string.h"
QUADCOPTER::QUADCOPTER()
{
	handPresented=false, 
	stacking=false,
	greenLight=false,
	autoPilotOn=true,
	
	stableSpeed=70,
	lowLimit=29, 
	highLimit=140,
	
	compensation=0.4;
	static const int pins[4]={3,5,7,8};
	double speeds[4]={0,0,0,0};
}

void QUADCOPTER::setupQuadcopter(void)
{
	for (int i=0; i<4;i++)
	{
		motors[i].attach(pins[i]);
		speeds[i]=30;
	}
	setRotorSpeed();
}

void QUADCOPTER::setRotorSpeed()
{
	for (int i=0;i<4;i++)
	{
		if (speeds[i]>lowLimit&& speeds[i]<highLimit)
		{
			(i==3)?(motors[i].write(speeds[i]-compensation)):(motors[i].write(speeds[i]));
		}
  	}
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
          Serial.print ("Char Val: ");
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

void QUADCOPTER::takeOff(){
}

void QUADCOPTER::land(){
}
