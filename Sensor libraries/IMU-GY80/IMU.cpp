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


void IMU::start(void)
{
	accelInit();
	gyroInit();
	magnInit();
}


void IMU::accelInit(void){
	byte data = 0x08;
	writeRegister(ADXL345_ADDRESS,ADXL345_POWER_CTL, 1, &data);
}

void IMU::gyroInit(void){
	byte data = 0x0F;
	writeRegister(L3G4200D_ADDRESS,L3G4200D_CTRL_REG1,1,&data);
}

void IMU::magnInit(void){
	byte data = 0x00;
	writeRegister(HMC5883_ADDRESS,HCM5883_MODE_REG,1,&data);
	
}


void IMU::read(void){
	readAccel();
	readGyro();
	readMagn();
}


void IMU::readAccel(void)
{
	byte buffer[6];
	if(readRegister(ADXL345_ADDRESS,ADXL345_DATAX0, 6, buffer)!=0){
		accel.x= ((float) ((uint16_t) buffer[1] << 8 | buffer[0])- z_accel_v.x);
		accel.y= ((float) ((uint16_t) buffer[3] << 8 | buffer[2])- z_accel_v.y);
		accel.z= ((float) ((uint16_t) buffer[5] << 8 | buffer[4])- z_accel_v.z);
	}
}


void IMU::readGyro(void){
	
	byte g_buffer[6];
	if(readRegister(L3G4200D_ADDRESS,L3G4200D_OUT_X_L, 6, g_buffer)!=0){
		gyro.x= ((float) ((uint16_t) g_buffer[1] << 8 | g_buffer[0])- z_gyro_v.x);
		gyro.y= ((float) ((uint16_t) g_buffer[3] << 8 | g_buffer[2])- z_gyro_v.y);
		gyro.z= ((float) ((uint16_t) g_buffer[5] << 8 | g_buffer[4])- z_gyro_v.z);
	}
	
}

void IMU::readMagn(void){
	byte m_buffer[6];
	if(readRegister(HMC5883_ADDRESS,HCM5883_X_MSB, 6, m_buffer)!=0){
		magn.x= ((float) ((uint16_t) m_buffer[1] << 8 | m_buffer[0])- z_magn_v.x);
		magn.y= ((float) ((uint16_t) m_buffer[3] << 8 | m_buffer[2])- z_magn_v.y);
		magn.z= ((float) ((uint16_t) m_buffer[5] << 8 | m_buffer[4])- z_magn_v.z);
	}
}

//Private functions

int IMU::writeRegister(info_t device_addr, byte reg_addr, int nbytes, byte *buffer)
{
	int written_bytes;
	
	//Wire.beginTransmission(IMU::ADXL345_ADDRESS);
	Wire.beginTransmission(device_addr);
	Wire.write(reg_addr);
	written_bytes = Wire.write(buffer, nbytes);
	Wire.endTransmission();
	
	return written_bytes;
}

int IMU::readRegister(info_t device_addr, byte reg_addr, int nbytes, byte *buffer)
{
	int idx = 0;

	Wire.beginTransmission(device_addr);
	Wire.write(reg_addr);
	Wire.endTransmission(); 
		
	Wire.requestFrom(device_addr,nbytes);
	while(Wire.available() && idx < nbytes)
	{ 
		buffer[idx++] = Wire.read();
	}
	
	return idx;
}

void IMU::setZeroAccel (vector z_accel){
	z_accel_v=z_accel;
}

void IMU::setZeroGyro (vector z_gyro){
	z_gyro_v=z_gyro;
}
void IMU::setZeroMang (vector z_magn){
	z_magn_v=z_magn;
}