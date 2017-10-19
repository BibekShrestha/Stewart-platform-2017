/* 
* Motor2.cpp
*
* Created: 5/25/2017 9:13:41 AM
* Author: Bibek Shrestha
*/


#include "Motor2.h"




#define ICR_TOP   249
#define MAX_VALUE 200
#define MIN_VALUE 0


#define DD_F G,2
#define DD_B G,0


//OC1A

#define DD_PWM			L,4
#define PWM_TCCRA		TCCR5A
#define PWM_TCCRB		TCCR5B
#define PWM_ICR			ICR5
#define PWM_OCR			OCR5B
	    
#define PWM_COM0		COM5B0
#define PWM_COM1		COM5B1
	    
#define PWM_WGM0		WGM50
#define PWM_WGM1		WGM51
#define PWM_WGM2		WGM52
#define PWM_WGM3		WGM53
#define PWM_CS0			CS50
#define PWM_CS1			CS51
#define PWM_CS2			CS52






void Motor2::Initialise()
{
	InitPWM();

	SetForwardDirection();
	SetOcrValue(0);
	
}

void Motor2::InitPWM()
{
	OUTPUT(DD_F);
	OUTPUT(DD_B);

	OUTPUT(DD_PWM);

	PWM_TCCRA	|=  ( 1 << PWM_COM1 ) | ( 1 << PWM_WGM1 );														//
	PWM_TCCRB	|=  ( 1 << PWM_WGM2 ) | ( 1 << PWM_WGM3 ) | ( 1 << PWM_CS1);									//PRESCALAR 8
	PWM_ICR		 =         ICR_TOP;
}

void Motor2::SetForwardDirection()
{
	SET		(DD_F);
	CLEAR	(DD_B);

}
void Motor2::SetReverseDirection()
{
	CLEAR	(DD_F);
	SET		(DD_B);
	
}

void Motor2::StopMotor()
{
	SET(DD_F);
	SET(DD_B);
	
	PWM_OCR = 0;
}


void Motor2::SetOcrValue(int x)
{
	if(x < 0)
	{
		Ocr = 0;
	}
	else
	{
		Ocr	= 2.49 * x;
	}
	
	if( Ocr >= MAX_VALUE)
		Ocr = MAX_VALUE;
	if( Ocr <= MIN_VALUE)
		Ocr = MIN_VALUE;

	PWM_OCR	= Ocr;
}

void Motor2::IncreaseSpeed()
{
	
	static uint16_t yy = (PWM_OCR + 25);
	PWM_OCR			   = yy;

	
}

void Motor2::DecreaseSpeed()
{
	static uint16_t yy = (PWM_OCR - 25);
	PWM_OCR			   = yy;

}



bool Motor2::Operate(unsigned char &rx, unsigned char &Command)
{
	return false;
}
