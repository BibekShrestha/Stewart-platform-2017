/*
 * communication.h
 *
 * Created: 5/8/2017 5:03:08 PM
 *  Author: Rajesh
 */ 


#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_



#define INCREASE_HEIGHT_BIT		0
#define DECREASE_HEIGHT_BIT		1
#define INCREASE_ROLL_BIT		2
#define DECREASE_ROLL_BIT		3
#define	INCREASE_PITCH		 	4
#define	DECREASE_PITCH	 		5
#define STROBE					6
#define ACKNOWLEDGE				7



#define STATUS_DE_ACKNOWLEDGE( Rx_Buffer )						((Rx_Buffer & ( 1 << ACKNOWLEDGE			))	>>ACKNOWLEDGE		 )
#define STATUS_DE_STROBE( Rx_Buffer )							((Rx_Buffer & ( 1 << STROBE					))	>>STROBE			 )
#define STATUS_DE_DECREASE_PITCH( Rx_Buffer ) 					((Rx_Buffer & ( 1 << DECREASE_PITCH			))	>>DECREASE_PITCH	 )
#define STATUS_DE_INCREASE_PITCH( Rx_Buffer )				 	((Rx_Buffer & ( 1 << INCREASE_PITCH			))	>>INCREASE_PITCH	 )
#define STATUS_DE_DECREASE_ROLL_BIT( Rx_Buffer )				((Rx_Buffer & ( 1 << DECREASE_ROLL_BIT		))	>>DECREASE_ROLL_BIT	 )
#define STATUS_DE_INCREASE_ROLL_BIT( Rx_Buffer )				((Rx_Buffer & ( 1 << INCREASE_ROLL_BIT		))	>>INCREASE_ROLL_BIT	 )
#define STATUS_DE_DECREASE_HEIGHT_BIT( Rx_Buffer )				((Rx_Buffer & ( 1 << DECREASE_HEIGHT_BIT	))	>>DECREASE_HEIGHT_BIT)
#define STATUS_DE_INCREASE_HEIGHT_BIT( Rx_Buffer )				((Rx_Buffer & ( 1 << INCREASE_HEIGHT_BIT	))	>>INCREASE_HEIGHT_BIT)


#define RESET_ACKNOWLEDGE( Rx_Buffer )							(Rx_Buffer &= ~( 1 << ACKNOWLEDGE			) )
#define RESET_STROBE( Rx_Buffer )								(Rx_Buffer &= ~( 1 << STROBE				) )
#define RESET_DECREASE_PITCH( Rx_Buffer ) 						(Rx_Buffer &= ~( 1 << DECREASE_PITCH		) )
#define RESET_INCREASE_PITCH( Rx_Buffer )				 		(Rx_Buffer &= ~( 1 << INCREASE_PITCH		) )
#define RESET_DECREASE_ROLL_BIT( Rx_Buffer )					(Rx_Buffer &= ~( 1 << DECREASE_ROLL_BIT		) )
#define RESET_INCREASE_ROLL_BIT( Rx_Buffer )					(Rx_Buffer &= ~( 1 << INCREASE_ROLL_BIT		) )
#define RESET_DECREASE_HEIGHT_BIT( Rx_Buffer )					(Rx_Buffer &= ~( 1 << DECREASE_HEIGHT_BIT	) )
#define RESET_INCREASE_HEIGHT_BIT( Rx_Buffer )					(Rx_Buffer &= ~( 1 << INCREASE_HEIGHT_BIT	) )
																
																
																
																
#define SET_ACKNOWLEDGE( Rx_Buffer )							(Rx_Buffer |= (1	<<	ACKNOWLEDGE				))
#define SET_STROBE( Rx_Buffer )									(Rx_Buffer |= (1	<<	STROBE					))
#define SET_DECREASE_PITCH( Rx_Buffer )	 						(Rx_Buffer |= (1	<<	DECREASE_PITCH			));\
																(					RESET_INCREASE_PITCH(Rx_Buffer);\
																(					SET_ACKNOWLEDGE(Rx_Buffer)
#define SET_INCREASE_PITCH( Rx_Buffer )					 		(Rx_Buffer |= (1	<<	INCREASE_PITCH		 	));\
																(					RESET_DECREASE_PITCH	;\
																(					SET_ACKNOWLEDGE(Rx_Buffer))
#define SET_DECREASE_ROLL_BIT( Rx_Buffer )						(Rx_Buffer |= (1	<<	DECREASE_ROLL_BIT	));\
																(					SET_ACKNOWLEDGE(Rx_Buffer)
#define SET_INCREASE_ROLL_BIT( Rx_Buffer )						(Rx_Buffer |= (1	<<	INCREASE_ROLL_BIT	));\
																(					SET_ACKNOWLEDGE(Rx_Buffer)
#define SET_DECREASE_HEIGHT_BIT( Rx_Buffer )					(Rx_Buffer |= (1	<<	DECREASE_HEIGHT_BIT	));\
																(					SET_ACKNOWLEDGE(Rx_Buffer)
#define SET_INCREASE_HEIGHT_BIT( Rx_Buffer )					(Rx_Buffer |= (1	<<	INCREASE_HEIGHT_BIT	));\
																					SET_ACKNOWLEDGE(Rx_Buffer)





#endif /* COMMUNICATION_H_ */