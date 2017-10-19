/* 
* LengthCalculator.cpp
*
* Created: STEPPING/24/5017 11:24:06 PM
* Author: Bibek Shrestha
*/


#include "LengthCalculator.h"


#define MAX_HEIGHT  1250
#define MAX_ROLL	  D_2_PI(60)
#define MAX_PITCH	  D_2_PI(60)


#define HOME_HEIGHT  740
#define MIN_ROLL	 0
#define MIN_PITCH	 0

#define PSTEPPING	  0.6				//0.8
#define RSTEPPING	  0.35 				//0.45
#define HSTEPPING	  2.0				//3.0


float leg1_Pi[3]={RADIUS_OF_PLATFORM,0,0};        //vector defining the coordinates of upper anchor point Pi with respect to platform framework
float leg2_Pi[3]={(-0.5*RADIUS_OF_PLATFORM),(0.866*RADIUS_OF_PLATFORM),0};
float leg3_Pi[3]={(-0.5*RADIUS_OF_PLATFORM),(-0.866*RADIUS_OF_PLATFORM),0};


float leg1_Bi[3]={RADIUS_OF_BASE,0,0};           //vector defining the coordinates of lower anchor point Bi with respect to base framework
float leg2_Bi[3]={(-0.5*RADIUS_OF_BASE),(0.866*RADIUS_OF_BASE),0};
float leg3_Bi[3]={(-0.5*RADIUS_OF_BASE),(0.866*RADIUS_OF_BASE),0};




void LengthCalculator::Initialise()
{
	
	ChangeFlag	= false;
	GoFlag		= false;
	pitch		= 0.48;
	roll		= 0.34;
	height		= HOME_HEIGHT;
	calc_lengths();
}


bool LengthCalculator::set_parameters( unsigned int _height, float _roll, float _pitch)
{

	height	=	_height;
	roll	=	_roll;
	pitch	=	_pitch;
		
	return true;

}

void LengthCalculator::calc_lengths(void)
{
 
		float n1=cos((float)pitch);
		float o2=cos((float)roll);
		float n2=sqrt(fabs(1-n1))*sqrt(fabs(1-o2));
		float n3=-sqrt(n1-pow(n1,2)+o2-n1*o2);
		float o1=n2;
		float o3=sqrt(1-pow(o1,2)-pow(o2,2));
		
		
		
		float z			= height/RADIUS_OF_BASE;


		float x			= (  0.5   * P_ROW   * ( n1 - o2 ));
		float y			= ( -P_ROW * n2);
		length[0]		= pow(( n1* P_ROW + x - 1), 2) + pow(( n2 * P_ROW + y), 2) + pow((n3 * P_ROW + z), 2);
		length[1]		= 0.25 * ( pow(( -n1 * P_ROW + 2 * x + 1+1.732*o1*P_ROW), 2) + pow(( -n2 * P_ROW + 1.732 * o2 * P_ROW + 2 * y - 1.732), 2) + pow(( -n3 * P_ROW + 1.732 *o3 * P_ROW + 2 * z), 2));
		length[2]		= 0.25 * ( pow(( -n1 * P_ROW + 2 * x + 1-1.732*o1*P_ROW), 2) + pow(( -n2 * P_ROW - 1.732 *o2 * P_ROW + 2 * y + 1.732), 2) + pow(( -n3 * P_ROW - 1.732 * o3 * P_ROW + 2 * z), 2));

		
		length[0] = sqrt( length[0] ) * RADIUS_OF_BASE;
		length[1] = sqrt( length[1] ) * RADIUS_OF_BASE;
		length[2] = sqrt( length[2] ) * RADIUS_OF_BASE;	

		//uart0_putint(n1*100);
		//uart0_puts("    ");
		//uart0_putint(o2*100);
		//uart0_puts("    ");
		//uart0_putint(length[0]);
		//uart0_puts("    ");
		//uart0_putint(length[1]);
		//uart0_puts("    ");
		//uart0_putint(length[2]);
		//uart0_puts("\n\r");
	

	
}



bool LengthCalculator::Operate(unsigned char &rx)
{



	if(STATUS_DE_INCREASE_HEIGHT_BIT(rx))
	{
		height += HSTEPPING;
		if( height >= MAX_HEIGHT)
		height =  MAX_HEIGHT;
		ChangeFlag = true;
		//uart0_puts("H INC \n\r");

		RESET_INCREASE_HEIGHT_BIT(rx);
	
	}
	if(STATUS_DE_DECREASE_HEIGHT_BIT(rx))
	{
		height -= HSTEPPING;
		if(	height <= HOME_HEIGHT)
		height =  HOME_HEIGHT;
		ChangeFlag = true;
		//uart0_puts("H dec \n\r");
		RESET_DECREASE_HEIGHT_BIT(rx);
			
	}

	if(STATUS_DE_INCREASE_ROLL_BIT(rx))
	{
		roll += D_2_PI(RSTEPPING);
		if( roll >= MAX_ROLL)
		roll =  MAX_ROLL;
		ChangeFlag = true;
		//uart0_puts("R INC \n\r");
		RESET_INCREASE_ROLL_BIT(rx);
		
	}

	if(STATUS_DE_DECREASE_ROLL_BIT(rx))
	{
		roll -= D_2_PI(RSTEPPING);
		if( roll <= MIN_ROLL)
		roll =  MIN_ROLL;
		ChangeFlag = true;
		//uart0_puts("R dec \n\r");
		RESET_DECREASE_ROLL_BIT(rx);
	}
	if(STATUS_DE_INCREASE_PITCH(rx))
	{
		pitch += D_2_PI(PSTEPPING);
		if( pitch >= MAX_PITCH)
		pitch =  MAX_PITCH;
		ChangeFlag = true;
		//uart0_puts("P INC \n\r");

		RESET_INCREASE_PITCH(rx);
	}

	if(STATUS_DE_DECREASE_PITCH(rx))
	{
		pitch -= D_2_PI(PSTEPPING);
		if( pitch <= MIN_PITCH)
		pitch =  MIN_PITCH;
		ChangeFlag = true;
		//uart0_puts("P dec \n\r");
		RESET_DECREASE_PITCH(rx);		
	}
	/*
	switch(rx)
	{
		case 'q':
			height += HSTEPPING;
			if( height >= MAX_HEIGHT)
				height =  MAX_HEIGHT;
				ChangeFlag = true;
			break;
		
		case 'w':
			height -= HSTEPPING;
			if(	height <= HOME_HEIGHT)
				height =  HOME_HEIGHT;
			ChangeFlag = true;
			break;
		
		case 'e':
			roll += D_2_PI(RSTEPPING);
			if( roll >= MAX_ROLL)
				roll =  MAX_ROLL;
			ChangeFlag = true;
			break;
		
		case 'r':
			roll -= D_2_PI(RSTEPPING);
			if( roll <= MIN_ROLL)
				roll =  MIN_ROLL;
			ChangeFlag = true;
			break;
		
		case 't':
			pitch += D_2_PI(PSTEPPING);
			if( pitch >= MAX_PITCH)
				pitch =  MAX_PITCH;
			ChangeFlag = true;
			break;
		
		case 'y':
			pitch -= D_2_PI(PSTEPPING);
			if( pitch <= MIN_PITCH)
				pitch =  MIN_PITCH;
			ChangeFlag = true;
			break;

		case 'g':
			GoFlag = true;
			break;
		
		case 'v' :
			uart0_puts("H:");
			uart0_putint(height);
			uart0_puts("  R:");
			uart0_putint(PI_2_D(roll));
			uart0_puts("  P:");
			uart0_putint(PI_2_D(pitch));
			uart0_puts("\n\r");
			break;
		*/
/*
	uart0_putint(PI_2_D(pitch));
	uart0_putc(' ');
	uart0_putint(0);
	uart0_puts("\n\r");
*/
	if( ChangeFlag )
	{
		calc_lengths();

		GoFlag     = false;
		ChangeFlag = false;
		return true;
			
	}	
	if( GoFlag)
	{
		calc_lengths();

		GoFlag     = false;
		ChangeFlag = false;
		return true;
	}

	
	return false;
	
}





/*_______________________________________________________________________
void LengthCalculator::translation_matrix(float height)
{
	total_height=(438+height);
	Ti[0]=0;
	Ti[1]=0;
	Ti[2]=total_height;

}
__________________________________________________________________________
*/

/*_______________________________________________________________________

void LengthCalculator::rotation_matrix(float roll,float pitch,float yaw)
{
	cos_roll=cos(roll);
	cos_pitch=cos(pitch);
	cos_yaw=cos(yaw);
	sin_roll=sin(roll);
	sin_pitch=sin(pitch);
	sin_yaw=sin(yaw);
	
	pRb[1][1]=(cos_yaw*cos_pitch);
	pRb[1][2]=((-sin_yaw*cos_roll)+(cos_yaw*sin_roll*sin_pitch));
	pRb[1][3]=((sin_yaw*sin_roll)+(cos_yaw*sin_pitch*cos_roll));
	pRb[2][1]=(sin_yaw*cos_pitch);
	pRb[2][2]=((cos_yaw*cos_roll)+(sin_yaw*sin_roll*sin_pitch));
	pRb[2][3]=((-cos_yaw*sin_roll)+(sin_yaw*sin_pitch*cos_roll));
	pRb[3][1]=(-sin_pitch);
	pRb[3][2]=(cos_pitch*sin_roll);
	pRb[3][3]=(cos_pitch*cos_roll);
	
}_______________________________________________________________________
*/



/*_______________________________________________________________________
float LengthCalculator::leg1_length()
{
	length_1_square=pow((Ti[1]-leg1_Bi[1]+leg1_Pi[1]*pRb[1][1]+leg1_Pi[2]*pRb[1][2]),2);
	length_2_square=pow((Ti[2]-leg1_Bi[2]+leg1_Pi[1]*pRb[2][1]+leg1_Pi[2]*pRb[2][2]),2);
	length_3_square=pow((Ti[3]+leg1_Pi[1]*pRb[3][1]+leg1_Pi[2]*pRb[3][2]),2);
	
	length_square_1= length_1_square+length_2_square+length_3_square;
	length_leg1=sqrt( length_square_1);
	
	return length_leg1;
}

float LengthCalculator::leg2_length()
{
	length_11_square=pow((Ti[1]-leg2_Bi[1]+leg2_Pi[1]*pRb[1][1]+leg2_Pi[2]*pRb[1][2]),2);
	length_22_square=pow((Ti[2]-leg2_Bi[2]+leg2_Pi[1]*pRb[2][1]+leg2_Pi[2]*pRb[2][2]),2);
	length_33_square=pow((Ti[3]+leg2_Pi[1]*pRb[3][1]+leg2_Pi[2]*pRb[3][2]),2);
	
	length_square_2= length_11_square+length_22_square+length_33_square;
	length_leg2=sqrt(length_square_2);
	
	return length_leg2;
}


float LengthCalculator::leg3_length()
{
	length_111_square=pow((Ti[1]-leg3_Bi[1]+leg3_Pi[1]*pRb[1][1]+leg3_Pi[2]*pRb[1][2]),2);
	length_222_square=pow((Ti[2]-leg3_Bi[2]+leg3_Pi[1]*pRb[2][1]+leg3_Pi[2]*pRb[2][2]),2);
	length_333_square=pow((Ti[3]+leg3_Pi[1]*pRb[3][1]+leg3_Pi[2]*pRb[3][2]),2);
	
	length_square_3= length_111_square+length_222_square+length_333_square;
	length_leg3= sqrt(length_square_3);
	
	return length_leg3;
}
_______________________________________________________________________
*/



/*
int LengthCalculator::get_length1()
{
	return length[0];
}


int LengthCalculator::get_length2()
{
	return length[1];
}


int LengthCalculator::get_length3()
{
	return length[2];
}

*/