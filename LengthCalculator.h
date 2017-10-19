/* 
* LengthCalculator.h
*
* Created: 5/24/2017 11:24:06 PM
* Author: Bibek Shrestha
*/


#ifndef __LENGTHCALCULATOR_H__
#define __LENGTHCALCULATOR_H__

#include "headers.h"



class LengthCalculator
{
	
	public:
	

	bool  ChangeFlag;
	bool  GoFlag;
	float length[3];
	float pRb[3][3];
	unsigned int  height;
	float roll, pitch;
	float length_1_square,length_2_square,length_3_square,length_11_square,length_22_square,length_33_square,length_square_1,length_square_2,length_111_square,length_222_square,length_333_square,length_square_3;
	

	void Initialise();	
	void calc_lengths();
	bool Operate(unsigned char &rx);				//return true if any change is made to leg lengths
	bool set_parameters( unsigned int _height, float _roll, float _pitch);


	/*
	float pRb[3][3];         //full rotation matrix relative to base
	float Ti[3];             //translation vector giving positional linear displacement of origin of platform w.r.t base framework
	float TotalHeight;       //total final length of respective leg

	float cos_roll,cos_pitch,cos_yaw,sin_roll,sin_pitch,sin_yaw;
	float length_1_square,length_2_square,length_3_square,length_square_1,length_leg1;
	float length_11_square,length_22_square,length_33_square,length_square_2,length_leg2;
	float length_111_square,length_222_square,length_333_square,length_square_3,length_leg3;
	*/



	/*
	int get_length1(void);
	int get_length2(void);
	int get_length3(void);

	
	void rotation_matrix(float roll,float pitch,float yaw);
	void translation_matrix(float height);	
	float leg1_length();
	float leg2_length();
	float leg3_length();
	*/


}; //LengthCalculator

#endif //__LENGTHCALCULATOR_H__
