#include <Wire.h>
#include <math.h>
#include <HMC5883.h>

void HMC5883::enableDefault(void)
{
	writeReg(0x02,0x00);
}


void HMC5883::writeReg(byte reg, byte value){
	Wire.beginTransmission(HMC5883_WHO_AM_I);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}


void HMC5883::read()
{
	Wire.beginTransmission(HMC5883_WHO_AM_I);
	Wire.write(0x03); //select register 3, X MSB register
	Wire.endTransmission();
	
	Wire.requestFrom(GYR_ADDRESS, 6);
	while (Wire.available() < 6);
	
	uint8_t xla = Wire.read();
	uint8_t xha = Wire.read();
	uint8_t yla = Wire.read();
	uint8_t yha = Wire.read();
	uint8_t zla = Wire.read();
	uint8_t zha = Wire.read();

	g.x = xha << 8 | xla;
	g.y = yha << 8 | yla;
	g.z = zha << 8 | zla;
}
