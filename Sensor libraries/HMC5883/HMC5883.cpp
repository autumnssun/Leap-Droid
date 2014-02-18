#include <HMC5883.h>
#include <Wire.h>
#include <math.h>

#define HMC5883_ADDRESS 0x1E


void HMC5883::enableDefault(void){
	Wire.beginTransmission(HMC5883_ADDRESS);
	Wire.write(0x02);
	Wire.write(0x00);
	Wire.endTransmission();
}

void HMC5883::writeReg(byte reg, byte value){
	Wire.beginTransmission(HMC5883_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

byte HMC5883::readReg(byte reg)
{
	byte value;
	Wire.beginTransmission(HMC5883_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(HMC5883_ADDRESS, 1);
	value = Wire.read();
	Wire.endTransmission();
	
	return value;
}

void HMC5883::read()
{
	Wire.beginTransmission(HMC5883_ADDRESS);
	Wire.write(0x03); //select register 3, X MSB register
	Wire.endTransmission();
	
	Wire.requestFrom(HMC5883_ADDRESS, 6);
	if(6<=Wire.available()){
    g.x = Wire.read()<<8; //X msb
    g.x |= Wire.read(); //X lsb
    g.z = Wire.read()<<8; //Z msb
    g.z |= Wire.read(); //Z lsb
    g.y = Wire.read()<<8; //Y msb
    g.y |= Wire.read(); //Y lsb
  }
  
// 	while (Wire.available() < 6);
// 	
// 	uint8_t xla = Wire.read();
// 	uint8_t xha = Wire.read();
// 	uint8_t zla = Wire.read();
// 	uint8_t zha = Wire.read();
// 	uint8_t yla = Wire.read();
// 	uint8_t yha = Wire.read();
// 
// 	g.x = xha << 8 | xla;
// 	g.z = zha << 8 | zla;
// 	g.y = yha << 8 | yla;

}

void HMC5883::vector_cross(const vector *a,const vector *b, vector *out)
{
  out->x = a->y*b->z - a->z*b->y;
  out->y = a->z*b->x - a->x*b->z;
  out->z = a->x*b->y - a->y*b->x;
}

float HMC5883::vector_dot(const vector *a,const vector *b)
{
  return a->x*b->x+a->y*b->y+a->z*b->z;
}

void HMC5883::vector_normalize(vector *a)
{
  float mag = sqrt(vector_dot(a,a));
  a->x /= mag;
  a->y /= mag;
  a->z /= mag;
}