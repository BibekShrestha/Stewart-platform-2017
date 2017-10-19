/*
 * StraightThrowingDualMotor.cpp
 * Created: 2/18/2017 3:21:34 PM
 * Author : Bibek Shrestha
 */ 


#include "declarations.h"
#include "headers.h"
#include "MotorA.h"
#include "MotorB.h"


MotorA MotorAA;
MotorB MotorBB;


unsigned char rx = 0;
unsigned char Rx_Buffer = 0x00;
unsigned int Rx_Word  = UART_NO_DATA;

unsigned char Tm;
volatile bool StartFlag  = false;

int main(void)
{
	
	bool MotorA_Return = false;
	bool MotorB_Return = false;


	initialise();
	MotorAA.Initialise();
	MotorBB.Initialise();
	
	MotorAA.StopMotor();
	MotorBB.StopMotor();

	sei();
	bluetooth_check();
	

	while(1)
	{ 
		if(uart3_available())
		{

			Rx_Buffer = uart3_getc();
			if(STATUS_DE_START_PLATFORM_MOTOR_BIT(Rx_Buffer))
				StartFlag = true;
			else if(STATUS_DE_STOP_PLATFORM_MOTOR_BIT(Rx_Buffer))
				StartFlag = false;

			if(STATUS_DE_DATA_RQ_BIT(Rx_Buffer))
				{
					lcd_clear();
					lcd_puts("AS:");
					lcd_unum(MotorAA.Controller.setpoint);
					lcd_putch(' ');
	
					lcd_puts("A:");
					lcd_unum(MotorAA.RPM);
					lcd_putch(' ');
					lcd_gotoxy(0,1);
					lcd_putch(' ');
					lcd_puts("BS:");
					lcd_unum(MotorBB.Controller.setpoint);
	
					lcd_puts("B:");
					lcd_unum(MotorBB.RPM);
	
					RESET_START_PLATFORM_MOTOR_BIT(Rx_Buffer);
					StartFlag = false;
				}
		}


		if(StartFlag == true)
		{
			uart0_putc('0');
			uart0_putc(' ');
			uart0_putint(MotorAA.RPM);
			uart0_putc(' ');
			uart0_putint(MotorBB.RPM);
			uart0_putc('\n');
			uart0_putc('\r');
			MotorA_Return = MotorAA.Operate(rx, Rx_Buffer);
			MotorB_Return = MotorBB.Operate(rx, Rx_Buffer); 
			//	Rx_Buffer = 0;
		
		}
		else
		{
				
				MotorAA.StopMotor();
				MotorBB.StopMotor();
				
				uart0_putc('0');
				uart0_putc(' ');
				uart0_putint(MotorAA.RPM);
				uart0_putc(' ');
				uart0_putint(MotorBB.RPM);
				uart0_putc('\n');
				uart0_putc('\r');
		}

		Rx_Buffer = 0;			
	}
	
	
}


ISR(TIMER3_OVF_vect)
{
	MotorAA.RPM = 0;
}


ISR(INT4_vect)
{
	MotorAA.Count   = READVALUE(TCNT3);
	TCNT3 = 0;
	MotorAA.IntFlag = true;
}


ISR(TIMER5_OVF_vect)
{
	MotorBB.RPM = 0;
}


ISR(INT1_vect)
{
	MotorBB.Count   = READVALUE(TCNT5);
	TCNT5 = 0;
	MotorBB.IntFlag = true;
}

ISR(TIMER1_OVF_vect)
{

		 ++MotorAA.Controller.timer;
		 ++MotorBB.Controller.timer;
}






