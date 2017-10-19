/*
 * Definition.cpp
 *
 * Created: 5/25/2017 10:35:59 AM
 *  Author: Bibek Shrestha
 */ 


 #include "Declaration.h"

 line_tracker LineTracker1(1), LineTracker2(2);


 
 static unsigned char lookup[16] = {
	 0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
 0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };



 void Initialise()
 {
	uart0_init(UART_BAUD_SELECT(57600,   F_CPU));
	uart2_init(UART_BAUD_SELECT(38400,   F_CPU));
	uart3_init(UART_BAUD_SELECT(38400,   F_CPU));
	uart0_puts("You can be the greatest. You can be the best.");
	lcd_init();
	i2c_init();
	InitI2CSlave();
	DDRK = 0x80;										//Communication
	DDRF = 0xFF;										//linetrackerData
	
 }
 
 void InitI2CSlave(void)
 {
	 TWAR = (STEWART_WRITE_ADDRESS);
	 TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	 sei();
 }


 unsigned char get_linetracker_data()
 {
	 unsigned char DataA, DataB;
	 static unsigned char LastA, LastB;
	 DataB=LineTracker1.get_line_data();
	 DataA=LineTracker2.get_line_data();
	 
	 /*
	 uart0_putc(' ');
	 uart0_putint(DataA);
	 uart0_putc(' ');
	 uart0_putint(DataB);
	 uart0_putc(' ');
	 */

	 /*
	 uart0_putc(' ');
	 uart0_putint(LastA);
	 uart0_putc(' ');
	 uart0_putint(LastB);
	 uart0_putc(' ');
	 */

	 
	 

	 if( (abs(LastB - DataB) > 40) && (DataB != 255 && LastB != 255))
		DataB = LastB;

		
	if( ( abs(LastA - DataA) > 40) && (DataA != 255 && LastA != 255))
		DataA = LastA;

	 LastA = DataA;
	 LastB = DataB;
	 /*
	 uart0_putc(' ');
	 uart0_putint(DataA);
	 uart0_putc(' ');
	 uart0_putint(DataB);
	 uart0_putc(' ');
	 */
	 if(DataA==255)
	 {
		 if(DataB==255)
		 {
			 DataA=255;
		 }
		 
		 else
		 
		 DataA=80+DataB;
	 }
	 
	 else
	 {
		 if(DataB==255);
		 
		 
		 else
		 DataA=(DataA+DataB+80)>>1;
		 
	 }
	// uart0_puts("COM:");
	// uart0_putint(DataA);
	 return DataA;
	 
 }


 
 uint8_t reverse(uint8_t n) {
	 // Reverse the top and bottom nibble then swap them.
	 return (lookup[n&0b1111] << 4) | lookup[n>>4];
 }


 void ProcessInput( volatile uint8_t *Recieved, unsigned char &Command , unsigned char &Yaw)
 {
	if ( *(Recieved + 0 ) == COMMAND_HEADER )
	{	
	uart0_puts("Got it\n\r");
		Command = * (Recieved + 1);
		*(Recieved + 0) = 0;
		*(Recieved + 1) = 0;
	}
	else if  ( *(Recieved + 0 ) == YAW_HEADER  )
	{	
		Yaw = * (Recieved + 1);
		 
		    *(Recieved + 0) = 0;
		    *(Recieved + 1) = 0;
		
	}
 }


bool DoNothing()
{
	uart0_puts("This is Something");
	return false;
}


