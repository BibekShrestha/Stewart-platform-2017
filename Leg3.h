/* 
* Leg3.h
*
* Created: 5/25/2017 10:06:08 AM
* Author: Bibek Shrestha
*/




#ifndef __LEG3_H__
#define __LEG3_H__





#include "headers.h"
#include "Motor3.h"
#include "Encoder3.h"




class Leg3
{
	public:
	Motor3 Motor;
	Encoder3 Encoder;
	
	long TargetCount;
	float HomeLength;
	
	bool ReachedFlag;
	bool MoveFlag;
	void Initialise(float HomeLength_);
	
	bool Operate( float * Length , bool ChangeFlag);



}; //Leg3

#endif //__LEG3_H__
