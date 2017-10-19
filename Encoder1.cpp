/*
 * Encoder1.cpp
 *
 * Created: 5/27/2017 7:37:07 AM
 *  Author: Rajesh
 */ 

#include "Encoder1.h"


//81.25 COUNT = 1 MM


#define ENCODERA D,2
#define ENCODERB A,0

#define ENCODERINTA			INT2


#define ENCODER_EICR		EICRA
#define ENCODER_INT			INT2
#define ENCODER_INTPIN		D,2
#define ENCODER_ISC0		ISC20
#define ENCODER_ISC1		ISC21
#define ENCODER_INTF		INTF2
#define ENCODER_INT_vect	INT2_vect





void Encoder1::Initialise(void)
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




