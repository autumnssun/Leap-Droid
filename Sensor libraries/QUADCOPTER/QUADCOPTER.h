#ifndef QUADCOPTER_h
#define QUADCOPTER_h

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "string.h"
#define SERVOS 4

class QUADCOPTER
{

	public: 
		char *stack;
		bool stacking,
			 greenLight,
			 autoPilotOn;
		int stableSpeed,
				  lowLimit, 
				  highLimit;
		int commaIndex;
		//functions declarations
		
		//function classification: IO
		int* readSerial(void); // aka rx() in arduino code verion 7

		char* appendCharToCharArray(char* array, char a);
};
#endif