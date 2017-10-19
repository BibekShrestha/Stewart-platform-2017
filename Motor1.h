/* 
* Motor1.h
*
* Created: 5/24/2017 10:09:54 PM
* Author: Bibek Shrestha
*/


#ifndef __MOTOR1_H__
#define __MOTOR1_H__

#include "headers.h"


class Motor1 
{
	private:

	public:
	int16_t Ocr;
	
	
	
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

#endif //__MOTOR1_H__
