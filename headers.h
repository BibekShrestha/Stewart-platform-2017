/*
 * headers.h
 *
 * Created: 5/24/2017 10:21:39 PM
 *  Author: Bibek Shrestha
 */ 


#ifndef HEADERS_H_
#define HEADERS_H_


#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#ifndef ENCODER_INTVECT_
#define ENCODER_INTVECT_

#define INT_ENCODER1A_VECT	INT2_vect
#define INT_ENCODER2A_VECT	INT4_vect
#define INT_ENCODER3A_VECT	INT5_vect

#define ENCODER1B	A,0
#define ENCODER2B	A,2
#define ENCODER3B	A,1

#endif  //ENCODER_INTVECT_

#define STEWART_WRITE_ADDRESS	(0x1F << 1)
#define STEWART_READ_ADDRESS	((0x1F << 1) | 1)

#define RADIUS_OF_BASE 425.5
#define RADIUS_OF_PLATFORM 250
#define P_ROW RADIUS_OF_PLATFORM/RADIUS_OF_BASE



#ifndef _COMM_PORT_
#define  _COMM_PORT_

#define COMPORT		PORTK
#define COMPIN		PINK

#endif




#ifndef _ANGLE_UNIT_CONVERSION_
#define _ANGLE_UNIT_CONVERSION_

#define COUNT_2_MM(x)	(x) * 0.0123
#define MM_2_COUNT(x)  (x) * 81.25

#define D_2_PI(x)  (x) * 0.01745
#define PI_2_D(x)  (x) * 57.2958

#endif //_ANGLE_UNIT_CONVERSION_


#define YAW_HEADER		240
#define YAW_TRAILER		')'


#define COMMAND_HEADER		250
#define COMMAND_TRAILER		'}'


#define FIRST_POSITION		1
#define SECOND_POSITION		2
#define THIRD_POSITION		3
#define FOURTH_POSITION		4
#define FIFTH_POSITION		5
#define SIXTH_POSITION		6
#define SEVENTH_POSITION	7

#define READY_POSITION      8
#define RETURN_POSITION     9





#define INPUT2(port,pin) DDR ## port &= ~_BV(pin)
#define OUTPUT2(port,pin) DDR ## port |= _BV(pin)
#define CLEAR2(port,pin) PORT ## port &= ~_BV(pin)
#define SET2(port,pin) PORT ## port |= _BV(pin)
#define TOGGLE2(port,pin) PORT ## port ^= _BV(pin)
#define READ2(port,pin) ((PIN ## port & _BV(pin))?1:0)
#define REGISTER_SET1( REGISTER, BIT1 ) REGISTER|=_BV( BIT1 )
#define REGISTER_SET2( REGISTER, BIT1, BIT2 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )
#define REGISTER_SET3( REGISTER, BIT1, BIT2, BIT3 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )|_BV( BIT3 )
#define REGISTER_SET4( REGISTER, BIT1, BIT2, BIT3, BIT4 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )|_BV( BIT3 )|_BV( BIT4 )
#define REGISTER_SET5( REGISTER, BIT1, BIT2, BIT3, BIT4, BIT5 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )|_BV( BIT3 )|_BV( BIT4 )|_BV( BIT5 )
#define REGISTER_SET6( REGISTER, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )|_BV( BIT3 )|_BV( BIT4 )|_BV( BIT5 )|_BV( BIT6 )
#define REGISTER_RESET( REGISTER,BIT ) REGISTER&=~_BV( BIT )
#define READVALUE(REGISTER) REGISTER
#define REGISTER_CLEAR(REGISTER) REGISTER = 0


#define INPUT(x) INPUT2(x)
#define OUTPUT(x) OUTPUT2(x)
#define CLEAR(x) CLEAR2(x)
#define SET(x) SET2(x)
#define TOGGLE(x) TOGGLE2(x)
#define READ(x) READ2(x)
#define PULLUP_ON(x) INPUT2(x); SET2(x)
#define PULLUP_OFF(x) INPUT2(x); CLEAR2(x)






#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <math.h>
#include <avr/eeprom.h>
#include "uart.h"
#include "communication.h"
#include "LineTracker.h"
#include "TWI.h"
#include "lcd.h"




#endif /* HEADERS_H_ */