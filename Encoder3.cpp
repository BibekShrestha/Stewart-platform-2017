/*
 * Encoder3.cpp
 *
 * Created: 5/27/2017 7:37:07 AM
 *  Author: Rajesh
 */ 

#include "Encoder3.h"


//81.25 COUNT = 1 MM


#define ENCODERA E,5
#define ENCODERB A,1

#define ENCODERINTA			INT5


#define ENCODER_EICR		EICRB
#define ENCODER_INT			INT5
#define ENCODER_INTPIN		E,5
#define ENCODER_ISC0		ISC50
#define ENCODER_ISC1		ISC51
#define ENCODER_INTF		INTF5
#define ENCODER_INT_vect	INT5_vect





void Encoder3::Initialise(void)
{	
	//Configure pins
	
	INPUT(ENCODERA);
	INPUT(ENCODERB);
	PULLUP_ON(ENCODERA);
	PULLUP_ON(ENCODERB);	
	
	//setting INT2 to falling edge sensitive
	//enabling external interrupt
	//clearing interrupt flag

	
	REGISTER_SET1(ENCODER_EICR,ENCODER_ISC1);
	REGISTER_SET1(EIMSK,ENCODER_INT );
	REGISTER_SET1(EIFR ,ENCODER_INTF);

	UpFlag = false;
}




