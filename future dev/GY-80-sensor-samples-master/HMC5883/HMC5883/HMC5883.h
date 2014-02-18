#ifndef HMC5883_h
#define HMC5883_h
#include <Arduino.h> // for byte data type

#define HMC5883_WHO_AM_I 0x1E;
#define HCM5883_MODE_REG 0x02; //select mode register
#define HCM5883_MODE  0x00; // continuous measurement mode

class HMC5883{
	typedef struct vector
		{
			float x, y, z;
		} vector;
	vector g;
	
	void enableDefault(void);
	void writeReg(byte reg, byte value);
	void read(void);
}
#endif
