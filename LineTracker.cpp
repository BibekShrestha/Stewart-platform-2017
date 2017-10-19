/*
 * line_trackercpp.cpp
 *
 * Created: 12/19/2016 12:36:34 AM
 *  Author: Rajesh
 */ 
#include "LineTracker.h"

unsigned char dat;
unsigned char command;
unsigned char checksum;


void line_tracker::Initialise(void)
{

	//Calibrate();
	Set_Line_Mode(LINE_ON_MODE);
	Set_Data_Mode(MODE2);
	Set_Backlight(10);
	Set_Contrast(90);
	Set_Baudrate(BAUDRATE_38400);
	
}


void line_tracker::Calibrate(void)
{
	command=CALIBRATION;
	dat=0x00;
	checksum=address+command+dat;
	if (address==1)
	{
		uart0_puts("LineTracker1 Calibrating");
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart0_puts("LineTracker2 Calibrating");
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
	
}


void line_tracker::Set_Line_Mode(unsigned char a)
{
	command=MODE;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
}
void line_tracker::Set_Line_Threshold(unsigned char a)
{
	command=THRESHOLD;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
}
	
void line_tracker::Set_Junction_Width(unsigned char a)
{
	command=JUNCTION_WIDTH;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
}

void line_tracker::Set_Address(unsigned char a)
{
	command=ADDRESS;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
}

void line_tracker::Set_Backlight(unsigned char a)
{

	command=BACKLIGHT;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}

}
void line_tracker::Set_Contrast(unsigned char a)
{
	command=CONTRAST;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
}
void line_tracker::Set_Baudrate(unsigned char a)
{
	command=BAUDRATE;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
}
void line_tracker::Set_Data_Mode(unsigned char a)
{
	command=OUTPUT_MODE;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
}
unsigned char line_tracker::Get_Junction_Count(void)
{
	command=JUNCTION_INFORMATION;
	dat=1;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);

		if(uart2_available())
			junction_count=uart2_getc();

		return junction_count;
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);

		if(uart3_available())
			junction_count=uart3_getc();

		return junction_count;
	}
	else
	 return 0;
	
}
void line_tracker::Reset_Junction_Count(void)
{
	command=JUNCTION_INFORMATION;
	dat=0;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);
	}
	
}
unsigned char line_tracker::Get_Sensor_Information(unsigned char a)
{
	command=LINE_POSITION;
	dat=a;
	checksum=address+command+dat;
	if (address==1)
	{
		uart2_putc(address);
		uart2_putc(command);
		uart2_putc(dat);
		uart2_putc(checksum);
		
		if(uart2_available())
			line_data=uart2_getc();

		return dat;
	}
	else if (address==2)
	{
		uart3_putc(address);
		uart3_putc(command);
		uart3_putc(dat);
		uart3_putc(checksum);

		if(uart3_available())
			line_data=uart3_getc();

		return dat;
	}
	else
		return 0;
}

unsigned char line_tracker::get_line_data(void)
{
	LastLineData = line_data;
	
	if(address==1 )
	{
		if(uart2_available())
		{
			line_data = uart2_getc();
		}
		else
		{
			line_data = LastLineData;
		}
		return line_data;
	}
	else if (address==2)
	{
		if(uart3_available())
		{
			line_data = uart3_getc();
		}
		else
		{
			line_data = LastLineData;
		}
		return line_data;
}
return 0;
}
