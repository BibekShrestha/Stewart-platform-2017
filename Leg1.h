/* 
* Leg1.h
*
* Created: 5/24/2017 10:23:29 PM
* Author: Bibek Shrestha
*/


#ifndef __LEG1_H__
#define __LEG1_H__

#include "headers.h"
#include "Motor1.h"
#include "Encoder1.h"




class Leg1
{
	public:
	Motor1 Motor;
	Encoder1 Encoder;
	long TargetCount;
	float HomeLength;
	
	
	bool ReachedFlag;
	bool MoveFlag;
	void Initialise(float HomeLength_);
	
	bool Operate( float * Length , bool ChangeFlag);



}; //Leg1

#endif //__LEG1_H__
