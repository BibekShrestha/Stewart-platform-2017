/*
 * Line_tracker.h
 *
 * Created: 12/19/2016 12:30:09 AM
 *  Author: Rajesh
 */ 


#ifndef LINE_TRACKER_H_
#define LINE_TRACKER_H_

#define CALIBRATION 'C'
#define MODE 'L'
#define THRESHOLD 'T'
#define JUNCTION_WIDTH 'J'
#define ADDRESS 'A'
#define BACKLIGHT 'B'
#define CONTRAST 'S'
#define BAUDRATE 'R'
#define OUTPUT_MODE 'D'
#define JUNCTION_INFORMATION 'X'
#define LINE_POSITION 'P'

#define LINE_ON_MODE 0
#define LINE_OFF_MODE 1

#define BAUDRATE_9600 0
#define BAUDRATE_19200 1
#define BAUDRATE_38400 2
#define BAUDRATE_57600 3
#define BAUDRATE_115200 4
#define BAUDRATE_230400 5

#define MODE0 0//stop sending byte
#define MODE1 1//a byte of digital value of signals
#define MODE2 2//detected line position from 0 to 70; 255 for not detecting line
#define MODE3 3//9 byte with 00x following eight byte of sensor raw data

#define SENSOR_DIGITAL_DATA 1
#define SENSOR_RELATIVE_POSITION 2


#include "headers.h"

class line_tracker
{
	
	unsigned char address;
	unsigned char junction_count;
	unsigned char line_data;
	unsigned char LastLineData;
	
	public:
	line_tracker(unsigned char a) :address(a){}
	void Initialise(void);
	void Calibrate(void);
	void Set_Line_Mode(unsigned char a);
	void Set_Line_Threshold(unsigned char a);
	void Set_Junction_Width(unsigned char a);
	void Set_Address(unsigned char a);
	void Set_Backlight(unsigned char a);
	void Set_Contrast(unsigned char a);
	void Set_Baudrate(unsigned char a);
	void Set_Data_Mode(unsigned char a);
	unsigned char Get_Junction_Count(void);
	void Reset_Junction_Count(void);
	unsigned char Get_Sensor_Information(unsigned char a);
	unsigned char get_line_data(void);
	
	
	
	
	
	
};





#endif /* LINE_TRACKER_H_ */