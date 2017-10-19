/* 
* Motor3.h
*
* Created: 5/25/2017 9:22:26 AM
* Author: Bibek Shrestha
*/


#ifndef __MOTOR3_H__
#define __MOTOR3_H__
#include "headers.h"


class Motor3
{
	private:

	public:

	uint16_t Ocr;
	
	
	void Initialise();
	
	void InitPWM();
	
	void SetForwardDirection();
	void SetReverseDirection();
	void StopMotor();
	void SetOcrValue(int x);
	void IncreaseSpeed();
	void DecreaseSpeed();
	bool Operate(unsigned char &rx, unsigned char &Command);
	
};

#endif //__MOTOR3_H__
