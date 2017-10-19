/*
 * Stewart New Code architecture.cpp
 *
 * Created: 5/24/2017 10:07:10 PM
 * Author : Bibek Shrestha
 */ 


 #ifndef F_CPU 
 #define F_CPU 16000000UL
 #endif


 
 #include "Declaration.h"
 #include "Leg1.h"
 #include "Leg2.h"
 #include "Leg3.h"
 #include "LengthCalculator.h"
 #include "LineTracker.h"

 #include "headers.h"


 void LoadEEPROMData();

 typedef struct 
 {
	float Height;
	float Roll;
	float Pitch;	
 } State;


 State LandingData[10]; 
 /*
  = {
					92  + 740 ,D_2_PI(15 + 19), D_2_PI(-18 +27),								//0			//None

					288 + 740, D_2_PI(20 + 19), D_2_PI(-24 +27),								//1			//First
					126 + 740, D_2_PI(16 + 19), D_2_PI(-16 +27),								//2			//Second
					236 + 740, D_2_PI(16 + 19), D_2_PI(-21 +27),								//3			//Third
					294 + 740, D_2_PI(20 + 19), D_2_PI(-24 +27),								//4			//Fourth
					236 + 740, D_2_PI(16 + 19), D_2_PI(-21 +27),								//5			//Fifth
					126 + 740, D_2_PI(16 + 19), D_2_PI(-16 +27),								//6			//Sixth
					436 + 740, D_2_PI(17 + 19), D_2_PI(-19 +27),								//7			//Seventh

					92  + 740, D_2_PI(16 + 19), D_2_PI(-21 +27),								//8			//ReadyPosition
					4   + 740, D_2_PI(0  + 19), D_2_PI(  0 +27)									//9			//HomePosition
}; 
*/
 
 State EEMEM EEPROMLandingData[10]; 
 /*
 = {
					 92  + 740 ,D_2_PI(15 + 19), D_2_PI(-18 +27),								//0			//None

					 288 + 740, D_2_PI(20 + 19), D_2_PI(-24 +27),								//1			//First
					 126 + 740, D_2_PI(16 + 19), D_2_PI(-16 +27),								//2			//Second
					 236 + 740, D_2_PI(16 + 19), D_2_PI(-21 +27),								//3			//Third
					 294 + 740, D_2_PI(20 + 19), D_2_PI(-24 +27),								//4			//Fourth
					 236 + 740, D_2_PI(16 + 19), D_2_PI(-21 +27),								//5			//Fifth
					 126 + 740, D_2_PI(16 + 19), D_2_PI(-16 +27),								//6			//Sixth
					 436 + 740, D_2_PI(17 + 19), D_2_PI(-19 +27),								//7			//Seventh

					 92  + 740, D_2_PI(16 + 19), D_2_PI(-21 +27),								//8			//ReadyPosition
					 4   + 740, D_2_PI(0  + 19), D_2_PI(  0 +27)								//9			//HomePosition
 };
 
 */


 #define PRE_MOTOR1_PIN A,3
 #define PRE_MOTOR2_PIN A,5
 #define PRE_MOTOR3_PIN A,4



 

LengthCalculator Calculator;
Leg1 Leg11;
Leg2 Leg22;
Leg3 Leg33;


extern line_tracker LineTracker1, LineTracker2;
unsigned char rx;
unsigned char Rx_Buffer = 0;

uint8_t CurrentLoadedData = 0;
uint8_t EepromLoadedData = 0;

State CurrentState;
bool EepromUpdateFlag = false;

bool CalculatorReturn = false;


bool AddressReceivedFlag = false;


volatile uint8_t ReceivedData[2];


uint8_t UartRecieved[2];

bool Leg11Return = false;
bool Leg22Return = false;
bool Leg33Return = false;

bool ManualInputFlag = false;
bool AutoMaticFlag	 = false;

unsigned char Command;
unsigned char Yaw;

unsigned char LineData;



int main(void)
{

	PULLUP_ON(PRE_MOTOR1_PIN);
	PULLUP_ON(PRE_MOTOR2_PIN);
	PULLUP_ON(PRE_MOTOR3_PIN);

	DDRF = 0xFF;
	PORTF = reverse(75);

	sei();

	LoadEEPROMData();


	if(true)
	{	
		Motor1 PreMotor1;
		Motor2 PreMotor2;
		Motor3 PreMotor3;

		PreMotor1.Initialise();
		PreMotor2.Initialise();
		PreMotor3.Initialise();
		

		
		PreMotor1.SetOcrValue(60);
		PreMotor1.SetForwardDirection();

		PreMotor2.SetOcrValue(60);
		PreMotor2.SetForwardDirection();

		PreMotor3.SetOcrValue(60);
		PreMotor3.SetForwardDirection();
		_delay_ms(600);

		PreMotor1.SetReverseDirection();
		PreMotor2.SetReverseDirection();
		PreMotor3.SetReverseDirection();
		


		
		char C1 = 0, C2 = 0, C3 = 0;

		while(true)
		{	

			if(!(READ(PRE_MOTOR1_PIN)))
			{
				C1++;
				if(C1 > 30)
				PreMotor1.StopMotor();
			}
			if(!(READ(PRE_MOTOR2_PIN)))
			{
				C2++;
				if(C2 > 10)
				PreMotor2.StopMotor();
			}
			if(!(READ(PRE_MOTOR3_PIN)))
			{
				C3++;
				if(C3 > 10)
				PreMotor3.StopMotor();
			}

			if(! (READ(PRE_MOTOR1_PIN) || READ(PRE_MOTOR2_PIN) || READ(PRE_MOTOR3_PIN)))
			{
				PreMotor1.StopMotor();
				PreMotor2.StopMotor();
				PreMotor3.StopMotor();
				break;
			}
		}

	}	
	

	Initialise();
	
	LineTracker1.Initialise();
	LineTracker2.Initialise();
	Calculator.Initialise();
	Leg11.Initialise(Calculator.length[0]);
	Leg22.Initialise(Calculator.length[1]);
	Leg33.Initialise(Calculator.length[2]);
	
	
	

	unsigned char LineDataUnreversed;
  
    while (1) 
    {

		LineDataUnreversed = get_linetracker_data();
		
		
		uart0_putint(LineDataUnreversed);
		uart0_puts("\n\r");

		LineData = reverse(LineDataUnreversed);


		


		PORTF = LineData;

		Rx_Buffer = COMPIN;
			
		if(STATUS_DE_STROBE(Rx_Buffer))
		{
			

			if(!(STATUS_DE_ACKNOWLEDGE(Rx_Buffer)))
			{
				COMPORT |=  ( 1 << ACKNOWLEDGE);
			
 				Rx_Buffer = 0;
			}
			else
				Rx_Buffer = 0;
		}
		else
		{
			if(STATUS_DE_ACKNOWLEDGE(Rx_Buffer))
			{
				COMPORT &= ~(1 << ACKNOWLEDGE);
				
				Rx_Buffer = COMPIN;
				if( Rx_Buffer != 0x00)
				{
					uart0_putint(Rx_Buffer);
				}

			}
			else
				Rx_Buffer = 0;
		}
		
		

		

		lcd_gotoxy(0,0);

		lcd_puts("H:");
		lcd_unum(Calculator.height - 740);
		uart0_putc(' ');

		lcd_gotoxy(8,0);
		
		lcd_puts("P:");
		lcd_num(PI_2_D(Calculator.pitch) - 27, 10);
		uart0_putc(' ');

		lcd_gotoxy(15,0);

		lcd_puts("R:");
		lcd_num(PI_2_D(Calculator.roll ) - 19, 10);
		uart0_putc(' ');


		lcd_gotoxy(0,1);

		lcd_puts("Y: ");
		lcd_num(Yaw,10);
		uart0_putc(' ');
		
		lcd_gotoxy(8,1);
		lcd_puts("L: ");
		lcd_num(LineDataUnreversed,10);
		uart0_putc(' ');
		
		

		
		if( uart0_available() )
		{
			UartRecieved[0] = UartRecieved[1];
			UartRecieved[1] = uart0_getc();


			uart0_putint( UartRecieved[0] );
			uart0_putc(' ');
			uart0_putint( UartRecieved[1] );
			uart0_puts("\n\r\n\r");
		}

		/*
		uart0_putint(UartRecieved[0]);
		uart0_putc(' ');
		uart0_putint(UartRecieved[1]);

		uart0_puts("\n\r");
		*/


		/*
		if(ReceivedData[0] == 'R')
		{
			uart0_putc(ReceivedData[1]);
			uart0_puts("\n\r");
		}
		*/

		/*
		if(UartRecieved[0] == 'I');
		{
			Calculator.height += 100;
			Calculator.roll += D_2_PI(2);
			Calculator.pitch += D_2_PI(3);
			UartRecieved[0] = 0;
		}

		if(UartRecieved[0] == 'i');
		{
			Calculator.height -= 100;
			Calculator.roll -= D_2_PI(2);
			Calculator.pitch -= D_2_PI(3);
			UartRecieved[0] = 0;
		}
		*/

		/*
		uart0_putint(ReceivedData[0]);
		uart0_putc(' ');
		uart0_putint(ReceivedData[1]);
		uart0_putc(' ');
		*/

		ProcessInput(ReceivedData,Command,Yaw);



		if(!ManualInputFlag)
		{
			Rx_Buffer = 0;
		}



		if( Command && (Leg11.ReachedFlag && Leg22.ReachedFlag && Leg33.ReachedFlag ) )
		{
			

			if(Command > '0' && Command <= '9')
			{
				Command -= '0';

				CurrentLoadedData = Command;

				Calculator.set_parameters( LandingData[Command].Height,LandingData[Command].Roll,LandingData[Command].Pitch );


				uart0_putc('[');
				uart0_putc(' ');
				uart0_putint(LandingData[Command].Height - 740);
				uart0_putc(' ');
				uart0_putint( int(PI_2_D(LandingData[Command].Roll )) - 19 );
				uart0_putc(' ');
				uart0_putint( int(PI_2_D(LandingData[Command].Pitch)) - 27);
				uart0_putc(' ');

				uart0_putc(']');
				uart0_puts("\n\r");

				Calculator.calc_lengths();
				AutoMaticFlag = true;
				ManualInputFlag = false;

			}
			if( Command == 'w' )
			{
				EepromUpdateFlag	= true;
				CurrentState.Roll   = Calculator.roll;
				CurrentState.Pitch  = Calculator.pitch;
				CurrentState.Height = Calculator.height;
				EepromLoadedData	= CurrentLoadedData;
				
			}
		}

		
		if(EepromUpdateFlag)
		{
			
			if( eeprom_is_ready() )
			{
				eeprom_update_block( (void *)&CurrentState, (void *)(EEPROMLandingData + EepromLoadedData), sizeof(State) );
				LandingData[EepromLoadedData] = CurrentState;
				EepromUpdateFlag = false;
			}

			uart0_puts("written");
			
		}



		if(AutoMaticFlag)
		{
			
			Leg11.Operate( (Calculator.length + 0) ,true);
			Leg22.Operate( (Calculator.length + 1) ,true);
			Leg33.Operate( (Calculator.length + 2) ,true);

			AutoMaticFlag = false;
			ManualInputFlag = true;
		}
		else if(ManualInputFlag)
		{
			if( Calculator.Operate(Rx_Buffer ) )
			{
				Leg11.Operate( (Calculator.length + 0) ,true);
				Leg22.Operate( (Calculator.length + 1) ,true);
				Leg33.Operate( (Calculator.length + 2) ,true);

			}
			else
			{
				Leg11.Operate( (Calculator.length + 0) ,false);
				Leg22.Operate( (Calculator.length + 1) ,false);
				Leg33.Operate( (Calculator.length + 2) ,false);
				
			}
		}
		
				
		CalculatorReturn = false;
		AutoMaticFlag = false;
		ManualInputFlag = true;
		Rx_Buffer = 0;
		rx  = 0;
		Command = 0;
    }
}








ISR(INT_ENCODER1A_VECT)
{
	//uart0_puts("A\n\r");
	if(READ(ENCODER1B))
	{
		Leg11.Encoder.UpFlag = true;
		++Leg11.Encoder.Count;
	}
	else
	{
		Leg11.Encoder.UpFlag = false;
		--Leg11.Encoder.Count;
	}

}


void LoadEEPROMData()
{
	eeprom_busy_wait();
	eeprom_read_block( (void *)LandingData, (void * )EEPROMLandingData, 10 * sizeof(State));
}





ISR(INT_ENCODER2A_VECT)
{
	//uart0_puts("B\n\r");
	if(!READ(ENCODER2B))
	{
		Leg22.Encoder.UpFlag = true;
		++Leg22.Encoder.Count;
	}
	else
	{
		Leg22.Encoder.UpFlag = false;
		--Leg22.Encoder.Count;
	}

}


ISR(INT_ENCODER3A_VECT)

{
	//uart0_puts("C\n\r");
	if(READ(ENCODER3B))
	{
		Leg33.Encoder.UpFlag = true;
		++Leg33.Encoder.Count;
	}
	else
	{
		Leg33.Encoder.UpFlag = false;
		--Leg33.Encoder.Count;
	}
}


ISR(TWI_vect){
	
	uint8_t I2Cdata;
	
	
	if( (TWSR & 0xF8) == TW_SR_SLA_ACK )
	{
		AddressReceivedFlag = true;
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	
	else if( (TWSR & 0xF8) == TW_SR_DATA_ACK )
	{
		
		I2Cdata = TWDR;
		
		
		if(AddressReceivedFlag)
		{
			AddressReceivedFlag = false;
				
			ReceivedData[0] = ReceivedData[1];
			ReceivedData[1]	= I2Cdata;
			
			TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);

		}
		else
		{
			
			TWCR |= (1<<TWIE) | (1<<TWINT) | (0<<TWEA) | (1<<TWEN);
			
		}
	}
	
	
	else{
		
		TWCR |= (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
	}
}



