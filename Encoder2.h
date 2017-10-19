/*
 * Encoder2.h
 *
 * Created: 5/27/2017 7:36:01 AM
 *  Author: Rajesh
 */ 


#ifndef ENCODER2_H_
#define ENCODER2_H_


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "headers.h"

#define PPR			100


class Encoder2
{
  public:
	long Count;
	bool UpFlag;
  
  public:
		void Initialise();				      	
};




#endif /* ENCODER2_H_ */