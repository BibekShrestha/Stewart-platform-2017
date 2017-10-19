/* 
* Leg2.h
*
* Created: 5/25/2017 9:59:52 AM
* Author: Bibek Shrestha
*/


#ifndef __LEG2_H__
#define __LEG2_H__



#include "headers.h"
#include "Motor2.h"
#include "Encoder2.h"



class Leg2
{
	public:
	Motor2 Motor;
	Encoder2 Encoder;
	
	long TargetCount;
	float HomeLength;

	bool ReachedFlag;
	bool MoveFlag;


	void Initialise(float HomeLength_);
	
	bool Operate( float * Length , bool ChangeFlag);



}; //Leg2

#endif //__LEG2_H__
