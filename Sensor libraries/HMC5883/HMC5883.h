#ifndef HMC5883_h
#define HMC5883_h
#include <Arduino.h>
#define HMC5883_ADDRESS 0x1E;
#define HCM5883_MODE_REG 0x02; //select mode register
#define HCM5883_MODE  0x00; // continuous measurement mode

class HMC5883{
	public:
	
		typedef struct vector
		{
			int x, y, z;
		} vector;
		vector g;
	
		void enableDefault(void);
		
		void writeReg(byte reg, byte value);
		byte readReg(byte reg);
		
		void read(void);
		static void vector_cross(const vector *a, const vector *b, vector *out);
		static float vector_dot(const vector *a,const vector *b);
		static void vector_normalize(vector *a);
};
#endif