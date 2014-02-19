#ifndef QUADCOPTER_h
#define QUADCOPTER_h

#include <Arduino.h>
#include <Servo.h>
#include "string.h"
class QUADCOPTER
{
	public: 
		char *stack;
		bool handPresented, 
			 stacking,
			 greenLight,
			 autoPilotOn;
		int stableSpeed,
				  lowLimit, 
				  highLimit;
		float compensation;
		QUADCOPTER();
		Servo motors[4];
		int pins[4];
		double speeds[4];
		
		int commaIndex;
		
		//functions declarations
		
		void setupQuadcopter(void);
		
		//function classification: IO
		void readSerial(void); // aka rx() in arduino code verion 7
		void setRotorSpeed(void);
		char* appendCharToCharArray(char* array, char a);
		
		//function classification: computational
		// This three functions are added for better control
		// Those function basically update the speeds[] array to the value
		
		void pitch(float angle);
		void yawn(float angle);
		void roll(float andle); 
		
		void takeOff(void);
		void land(void);
};
#endif