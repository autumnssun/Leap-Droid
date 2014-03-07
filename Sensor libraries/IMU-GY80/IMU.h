/********************************************************************************
* IMU_GY80 Library - IMU GY80.h                                                 *
* Copyright (C) 2014 Khoa_Tran (khoa.tran.nano@gmail.com)     					*
* Addapted from 2011 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#ifndef _IMU_H
#define _IMU_H

#include <Arduino.h>

// All functions return -1 on error and 0 on success

// SENSOR CALIBRATION
/*****************************************************************/
// How to calibrate? Read the tutorial at http://dev.qu.tu-berlin.de/projects/sf-razor-9dof-ahrs
// Put MIN/MAX and OFFSET readings for your board here!
// Accelerometer
// "accel x,y,z (min/max) = X_MIN/X_MAX  Y_MIN/Y_MAX  Z_MIN/Z_MAX"
#define ACCEL_X_MIN (-255.0f)
#define ACCEL_X_MAX (260.0f)
#define ACCEL_Y_MIN (-267.0f)
#define ACCEL_Y_MAX (255.0f)
#define ACCEL_Z_MIN (-278.0f)
#define ACCEL_Z_MAX (238.0f)

// Magnetometer
// "magn x,y,z (min/max) = X_MIN/X_MAX  Y_MIN/Y_MAX  Z_MIN/Z_MAX"
#define MAGN_X_MIN (-520.0f)
#define MAGN_X_MAX (850.0f)
#define MAGN_Y_MIN (-640.0f)
#define MAGN_Y_MAX (684.0f)
#define MAGN_Z_MIN (-213.0f)
#define MAGN_Z_MAX (850.0f)

// Gyroscope
// "gyro x,y,z (current/average) = .../OFFSET_X  .../OFFSET_Y  .../OFFSET_Z
#define GYRO_X_OFFSET (-20.5f)
#define GYRO_Y_OFFSET (0.5f)
#define GYRO_Z_OFFSET (10.5f)

//*****************************************************************************/

#define GRAVITY 255.0f  //this equivalent to 1G in the raw data coming from the accelerometer 

#define ACCEL_X_OFFSET ((ACCEL_X_MIN + ACCEL_X_MAX) / 2.0f)
#define ACCEL_Y_OFFSET ((ACCEL_Y_MIN + ACCEL_Y_MAX) / 2.0f)
#define ACCEL_Z_OFFSET ((ACCEL_Z_MIN + ACCEL_Z_MAX) / 2.0f)
#define ACCEL_X_SCALE (GRAVITY / (ACCEL_X_MAX - ACCEL_X_OFFSET))
#define ACCEL_Y_SCALE (GRAVITY / (ACCEL_Y_MAX - ACCEL_Y_OFFSET))
#define ACCEL_Z_SCALE (GRAVITY / (ACCEL_Z_MAX - ACCEL_Z_OFFSET))

#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0f)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0f)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0f)
#define MAGN_X_SCALE (100.0f / (MAGN_X_MAX - MAGN_X_OFFSET))
#define MAGN_Y_SCALE (100.0f / (MAGN_Y_MAX - MAGN_Y_OFFSET))
#define MAGN_Z_SCALE (100.0f / (MAGN_Z_MAX - MAGN_Z_OFFSET))

// Gyro gain (conversion from raw to degree per seconds)
#define GYRO_GAIN 0.061035156f
#define GYRO_GAIN_X 0.061035156f //X axis Gyro gain
#define GYRO_GAIN_Y 0.061035156f //Y axis Gyro gain
#define GYRO_GAIN_Z 0.061035156f //Z axis Gyro gain

#define DEG2RAD(x) (x * 0.01745329252)  // *pi/180
#define RAD2DEG(x) (x * 57.2957795131)  // *180/pi

class IMU
{
	
	public:
	
		typedef struct vector
		{
			float x, y, z;
		} vector;
		
		vector accel,gyro,magn;
		
		
		enum range_t
		{
			ADXL345_RANGE_16G = 0x0B,
			ADXL345_RANGE_8G  = 0x0A,
			ADXL345_RANGE_4G  = 0x09,
			ADXL345_RANGE_2G  = 0x08
		};
		
		void start(void);
		void read(void);
		void readAccel(void);
		void readGyro(void);
		void readMagn(void);
		
		void setZeroAccel(vector z_accel);
		void setZeroGyro(vector z_gyro);
		void setZeroMang(vector z_magn);
		
		void accelInit(void);
		void gyroInit(void);
		void magnInit(void);
		
	private:
		/* Registers */
		
		
		enum info_t 
		{
			ADXL345_DEVID          = 0x00,
			ADXL345_THRESH_TAP     = 0x1D,
			ADXL345_OFSX           = 0x1E,
			ADXL345_OFSY           = 0x1F,
			ADXL345_OFSZ           = 0x20,
			ADXL345_DUR            = 0x21,
			ADXL345_Latent         = 0x22,
			ADXL345_Window         = 0x23,
			ADXL345_THRESH_ACT     = 0x24,
			ADXL345_THRESH_INACT   = 0x25,
			ADXL345_TIME_INACT     = 0x26,
			ADXL345_ACT_INACT_CTL  = 0x27,
			ADXL345_THRESH_FF      = 0x28,
			ADXL345_TIME_FF        = 0x29,
			ADXL345_TAP_AXES       = 0x2A,
			ADXL345_ACT_TAP_STATUS = 0x2B,
			ADXL345_BW_RATE        = 0x2C,
			ADXL345_POWER_CTL      = 0x2D,
			ADXL345_INT_ENABLE     = 0x2E,
			ADXL345_INT_MAP        = 0x2F,
			ADXL345_INT_SOURCE     = 0x30,
			ADXL345_DATA_FORMAT    = 0x31,
			ADXL345_DATAX0         = 0x32,
			ADXL345_DATAX1         = 0x33,
			ADXL345_DATAY0         = 0x34,
			ADXL345_DATAY1         = 0x35,
			ADXL345_DATAZ0         = 0x36,
			ADXL345_DATAZ1         = 0x37,
			ADXL345_FIFO_CTL       = 0x38,
			ADXL345_FIFO_STATUS    = 0x39,
			ADXL345_ADDRESS        = 0xA7 >> 1,
			
		    L3G4200D_WHO_AM_I      =0x0F,
		    L3G4200D_CTRL_REG1     =0x20,
		    L3G4200D_CTRL_REG2     =0x21,
		    L3G4200D_CTRL_REG3     =0x22,
		    L3G4200D_CTRL_REG4     =0x23,
		    L3G4200D_CTRL_REG5     =0x24,
		    L3G4200D_REFERENCE     =0x25,
		    L3G4200D_OUT_TEMP      =0x26,
		    L3G4200D_STATUS_REG    =0x27,
		    L3G4200D_OUT_X_L       =0x28,
		    L3G4200D_OUT_X_H       =0x29,
		    L3G4200D_OUT_Y_L       =0x2A,
		    L3G4200D_OUT_Y_H       =0x2B,
		    L3G4200D_OUT_Z_L       =0x2C,
		    L3G4200D_OUT_Z_H       =0x2D,
		    L3G4200D_FIFO_CTRL_REG =0x2E,
		    L3G4200D_FIFO_SRC_REG  =0x2F,
		    L3G4200D_INT1_CFG      =0x30,
		    L3G4200D_INT1_SRC      =0x31,
		    L3G4200D_INT1_THS_XH   =0x32,
		    L3G4200D_INT1_THS_XL   =0x33,
		    L3G4200D_INT1_THS_YH   =0x34,
		    L3G4200D_INT1_THS_YL   =0x35,
		    L3G4200D_INT1_THS_ZH   =0x36,
		    L3G4200D_INT1_THS_ZL   =0x37,
		    L3G4200D_INT1_DURATION =0x38,
			L3G4200D_ADDRESS	   =0xD2 >> 1,
			
			HMC5883_ADDRESS 	   =0x1E,
			HMC5883_CONF_REG_A	   =0X00,
			HMC5883_CONF_REG_B	   =0X01,
			HCM5883_MODE_REG       =0x02,
			HCM5883_X_MSB  		   =0X03,
			
		};

		int readRegister(info_t device_addr, byte reg_addr, int nbytes, byte *buffer);
		int writeRegister(info_t device_addr, byte reg_addr, int nbytes, byte *buffer);
		
		vector z_accel_v,z_gyro_v,z_magn_v;
		
		
	
};

#endif // _IMU_H
