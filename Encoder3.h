/*
 * Encoder3.h
 *
 * Created: 5/27/2017 7:36:44 AM
 *  Author: Rajesh
 */ 



#ifndef ENCODER3_H_
#define ENCODER3_H_


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "headers.h"

#define PPR						100

class Encoder3
{
  public:
	long Count;
	bool UpFlag;
  
  public:
		void Initialise();				      	
};




#endif /* ENCODER3_H_ */

