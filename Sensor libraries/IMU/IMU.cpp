/********************************************************************************
* IMU_GY80 Library - IMU GY80.cpp                                               *
* Copyright (C) 2014 Khoa_Tran (khoa.tran.nano@gmail.com)     					*
* Addapted from 2011 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/
#include <IMU.h>
#include <Wire.h>
#include <Arduino.h>
#include <math.h>

// #include <vector.h>

void IMU::start(bool _debug,float _alpha,float _beta,int _z_sample_rate)
{
	accelInit();
	gyroInit();
	magnInit();
	delay(100);
	//after start read the sensor and then set the balance.
	setBalanceState();
	debug=_debug;
	alpha=_alpha;
	beta=_beta;
	
}

void IMU::readsensors(void){
	last_accel=accel;
	last_gyro=gyro;
	last_magn=magn;
	
	accel=readAccel();
	gyro=readGyroAngularRate();
	magn=readMagn();
	
	//gyro=deltaVector(last_gyro,gyro);
}

IMU::vector IMU::readAccel(void){
	byte buffer[6];
	vector ac;
	if(readRegister(ADXL345_ADDRESS,ADXL345_DATAX0, 6, buffer)!=0){
		ac.x= ((float) ((uint8_t) buffer[1] << 8 | buffer[0]))/255- z_accel_v.x;
		ac.y= ((float) ((uint8_t) buffer[3] << 8 | buffer[2]))/255- z_accel_v.y;
		ac.z= ((float) ((uint8_t) buffer[5] << 8 | buffer[4]))/255- z_accel_v.z;
		ac.timestamp=millis();
	}
	//return applyLowPass(ac,last_accel);
	return ac;
}
IMU::vector IMU::readGyroAngularRate(void){
	vector gy;
	float gyro_scale=0.0175/2;
	
	Wire.beginTransmission(L3G4200D_ADDRESS);
	Wire.write(L3G4200D_OUT_X_L | (1 << 7)); 
	Wire.endTransmission();	
	Wire.requestFrom(L3G4200D_ADDRESS, 6);
	
	while (Wire.available() < 6);
	{
		uint8_t xla = Wire.read();
		uint8_t xha = Wire.read();
		uint8_t yla = Wire.read();
		uint8_t yha = Wire.read();
		uint8_t zla = Wire.read();
		uint8_t zha = Wire.read();

		gy.x = (xha << 8 | xla);
		gy.y = (yha << 8 | yla);
		gy.z = (zha << 8 | zla);
		gy.timestamp=millis();
	}
	//substract with the zero rate vector to balance out the reading
	//gy=scaleVector((substract2Vectors(gy,z_gyro_v)),gyro_scale);
	gy=substract2Vectors(scaleVector(gy,gyro_scale),z_gyro_v);
	//Gy value's unit is degree percecons
	return gy;
}
IMU::vector IMU::readMagn(void){
	byte m_buffer[6];
	vector ma;
	if(readRegister(HMC5883_ADDRESS,HCM5883_X_MSB, 6, m_buffer)!=0){
		ma.x= ((float) ((uint8_t) m_buffer[1] << 8 | m_buffer[0]))/255- z_magn_v.x;
		ma.y= ((float) ((uint8_t) m_buffer[3] << 8 | m_buffer[2]))/255- z_magn_v.y;
		ma.z= ((float) ((uint8_t) m_buffer[5] << 8 | m_buffer[4]))/255- z_magn_v.z;
		ma.timestamp=millis();
	}
	//return applyLowPass(ma,last_magn);
	return ma;
}


/********************************************************************************
*			Private function used within class only 							*
*********************************************************************************/

//Read raw data from sensors functions
int IMU::writeRegister(info_t device_addr, byte reg_addr, int nbytes, byte *buffer){
	int written_bytes;
	
	Wire.beginTransmission(device_addr);
	Wire.write(reg_addr);
	written_bytes = Wire.write(buffer, nbytes);
	Wire.endTransmission();
	
	return written_bytes;
}
int IMU::readRegister(info_t device_addr, int nbytes, byte *buffer){
	int idx = 0;

	Wire.beginTransmission(device_addr);		
	Wire.requestFrom(device_addr,nbytes);
	while(Wire.available() && idx < nbytes)
	{ 
		buffer[idx++] = Wire.read();
	}
	Wire.endTransmission(); 
	return idx;
}
int IMU::readRegister(info_t device_addr, byte reg_addr, int nbytes, byte *buffer){
	int idx = 0;

	Wire.beginTransmission(device_addr);
	Wire.write(reg_addr);
	
	Wire.requestFrom(device_addr,nbytes);
	while(Wire.available() && idx < nbytes)
	{ 
		buffer[idx++] = Wire.read();
	}
	Wire.endTransmission(); 
	
	return idx;
}

//start the sensors with optimized registery
void IMU::accelInit(void){
	byte data;
	data = ADXL345_RANGE_2G;
	writeRegister(ADXL345_ADDRESS,ADXL345_POWER_CTL, 1, &data);
}
void IMU::gyroInit(void){
	byte data;
	data = 0x1F;//normal mode all axis enabled
	writeRegister(L3G4200D_ADDRESS,L3G4200D_CTRL_REG1,1,&data);
	delay(1);
	
	data=0x08;
	writeRegister(L3G4200D_ADDRESS,L3G4200D_CTRL_REG3,1,&data);
	delay(1);
		
	data = L3G4200D_RANGE_500;//set the range to 2000 dps
	writeRegister(L3G4200D_ADDRESS,L3G4200D_CTRL_REG4,1,&data);
	delay(100);
}
void IMU::magnInit(void){
	byte data;
	data = 0x00;
	writeRegister(HMC5883_ADDRESS,HCM5883_MODE_REG,1,&data);
}

//Calculations & fillters
IMU::pyr IMU::calculatePYR(vector _v){
	pyr _pyr;	
	return _pyr;
}
IMU::vector IMU::applyLowPass(vector _raw, vector _filtered){
	_filtered.x=_raw.x*alpha + (_filtered.x*(1-alpha));
	_filtered.y=_raw.y*alpha + (_filtered.y*(1-alpha));
	_filtered.z=_raw.z*alpha + (_filtered.z*(1-alpha));
	_filtered.timestamp=_raw.timestamp;
	return _filtered;
}

//balance state setting;
void IMU::setBalanceState(void){
	zeroRateSample=10;
	setZeroAccel(zeroRateSample);
	setZeroGyro(zeroRateSample);
	setZeroMagn(zeroRateSample);
}
void IMU::setZeroAccel (int rate){
	
	for (int i=0; i<rate;i++){
		z_accel_v=add2Vectors(z_accel_v,readAccel());
	}
	z_accel_v=avgVector(z_accel_v,rate);
}
void IMU::setZeroGyro (int rate){
	for (int i=0; i<rate;i++){
		z_gyro_v=add2Vectors(z_gyro_v,readGyroAngularRate());
	}
	z_gyro_v=avgVector(z_gyro_v,rate);
}
void IMU::setZeroMagn (int rate){
	for (int i=0; i<rate;i++){
		z_magn_v=add2Vectors(z_magn_v,readMagn());
	}
	z_magn_v=avgVector(z_magn_v,rate);
}

//Vector calculations
IMU::vector IMU::add2Vectors(vector v1, vector v2){	
	v1.x=v1.x+v2.x;
	v1.y=v1.y+v2.y;
	v1.z=v1.z+v2.z;
	return v1;
}

IMU::vector IMU::substract2Vectors(vector v1, vector v2){	
	v1.x=v1.x-v2.x;
	v1.y=v1.y-v2.y;
	v1.z=v1.z-v2.z;
	return v1;
}

IMU::vector IMU::scaleVector(vector v1, float scaleFactor){
	v1.x=v1.x*scaleFactor;
	v1.y=v1.y*scaleFactor;
	v1.z=v1.z*scaleFactor;
	return v1;
}

IMU::vector IMU::avgVector(vector v1, float avgFactor){	
	v1.x=v1.x/avgFactor;
	v1.y=v1.y/avgFactor;
	v1.z=v1.z/avgFactor;
	return v1;
}

IMU::vector IMU::deltaVector(vector before, vector after){
	vector delta;
	delta.timestamp=after.timestamp-before.timestamp;
	delta.x=(after.x-before.x);
	delta.y=(after.y-before.y);
	delta.z=(after.z-before.z);
	return delta;	
}