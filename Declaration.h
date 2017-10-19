/*
 * Declaration.h
 *
 * Created: 5/25/2017 10:35:40 AM
 *  Author: Bibek Shrestha
 */ 


#ifndef DECLARATION_H_
#define DECLARATION_H_



#include "headers.h"

extern line_tracker LineTracker1, LineTracker2;

void Initialise();
unsigned char get_linetracker_data();

uint8_t reverse(uint8_t n);
void InitI2CSlave(void);


void ProcessInput(volatile uint8_t *Recieved, unsigned char &Command , unsigned char &Yaw);



bool DoNothing();


#endif /* DECLARATION_H_ */