/* 
* Leg2.cpp
*
* Created: 5/25/5017 9:59:52 AM
* Author: Bibek Shrestha
*/


#include "Leg2.h"

#define BAND 10
#define RECIEVE_BAND 80


#define P_TERMU	0.003
#define OFFSETU	45

#define P_TERMD	0.003
#define OFFSETD	45



void Leg2::Initialise(float HomeLength_)
{
	
	HomeLength		= HomeLength_;
	TargetCount		= 0;
	MoveFlag = false;
	ReachedFlag = true;
	Encoder.Initialise();
	Motor.Initialise();

}


bool Leg2::Operate(float * Length, bool ChangeFlag)
{
	static bool UpFlag;

	if(ChangeFlag)
	{
		TargetCount = MM_2_COUNT( *Length - HomeLength);
		ReachedFlag = false;
		
	}

	UpFlag =  (TargetCount >= Encoder.Count);

	
	if(abs(TargetCount - Encoder.Count) < RECIEVE_BAND)
	{
		ReachedFlag = true;
	}

	if(abs(TargetCount - Encoder.Count) < BAND || TargetCount < -5 || TargetCount > MM_2_COUNT(500))
	{
		Motor.StopMotor();
		UpFlag = true;
		return true;
	}
	
	
	
	if(UpFlag)
	{
		Motor.SetForwardDirection();
		Motor.SetOcrValue(abs(TargetCount - Encoder.Count) * P_TERMU  + OFFSETU);

	}
	else
	{
		Motor.SetReverseDirection();
		Motor.SetOcrValue(abs(TargetCount - Encoder.Count) * P_TERMD  + OFFSETD);

	}
	
	/*
	uart0_puts("B:");
	uart0_putint(TargetCount);
	uart0_putc(' ');
	uart0_putint(Encoder.Count);
	uart0_puts("   ");
	*/
	


	return false;

}