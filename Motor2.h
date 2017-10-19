/* 
* Motor2.h
*
* Created: 5/25/2017 9:13:41 AM
* Author: Bibek Shrestha
*/


#ifndef __MOTOR2_H__
#define __MOTOR2_H__

#include "headers.h"

class Motor2
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

#endif //__MOTOR2_H__
