/*
 * Seven_segment_prog.c
 *
 *  Created on: Feb 12, 2023
 *      Author: REZK
 */
#include"stdTypes.h"
#include"errorStates.h"

#include"Seven_segment_config.h"
#include"Seven_segment_priv.h"
#include"DIO_int.h"


ES_t Seven_Segment_enuInit(void)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	u32 Local_u32Check=0;

	/*Set the directions of all pins*/
	Local_u32Check  =  DIO_enuSetPinDirection(SEG_APORT,SEG_APIN,DIO_u8PIN_OUTPUT);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_BPORT,SEG_BPIN,DIO_u8PIN_OUTPUT)<<2);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_CPORT,SEG_CPIN,DIO_u8PIN_OUTPUT)<<4);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_DPORT,SEG_DPIN,DIO_u8PIN_OUTPUT)<<6);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_EPORT,SEG_EPIN,DIO_u8PIN_OUTPUT)<<8);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_FPORT,SEG_FPIN,DIO_u8PIN_OUTPUT)<<10);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_GPORT,SEG_GPIN,DIO_u8PIN_OUTPUT)<<12);


#if SEG_CMN_PIN<=DIO_u8PIN7 && SEG_CMN_PORT <=DIO_u8PORTD
	DIO_enuSetPinDirection(SEG_CMN_PORT,SEG_CMN_PIN,DIO_u8PIN_OUTPUT);
#elif SEG_CMN_PIN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED
#else
#error "the common has wrong selection !!! "
#endif

#if SEG_DOT_PIN<=DIO_u8PIN7 && SEG_DOT_PORT <=DIO_u8PORTD
	DIO_enuSetPinDirection(SEG_CMN_PORT,SEG_CMN_PIN,DIO_u8PIN_OUTPUT);
#elif SEG_DOT_PIN == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED
#else
#error "the dot led has wrong selection !!! "
#endif


	u8 Local_u8Iterator = 0;

	for(Local_u8Iterator=0 ;Local_u8Iterator<(sizeof(Local_u32Check)*8);Local_u8Iterator+=2)
	{
		if( ( ((Local_u32Check)>>Local_u8Iterator)&0x7)  != ES_OK )
		{
			return Local_enuErrorState;
		}

	}

	Local_enuErrorState = ES_OK;

	/*Then return error state variable*/
	return Local_enuErrorState;
}




ES_t Seven_Segment_enuDisplayNum(u8 Copy_u8Num)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Num < 10)
	{

#if SEG_TYPE == COMMON_CATHODE
		DIO_enuSetPinValue(SEG_APORT,SEG_APIN,((SEG_Au8Display[Copy_u8Num]>>0)&1));
		DIO_enuSetPinValue(SEG_BPORT,SEG_BPIN,((SEG_Au8Display[Copy_u8Num]>>1)&1));
		DIO_enuSetPinValue(SEG_CPORT,SEG_CPIN,((SEG_Au8Display[Copy_u8Num]>>2)&1));
		DIO_enuSetPinValue(SEG_DPORT,SEG_DPIN,((SEG_Au8Display[Copy_u8Num]>>3)&1));
		DIO_enuSetPinValue(SEG_EPORT,SEG_EPIN,((SEG_Au8Display[Copy_u8Num]>>4)&1));
		DIO_enuSetPinValue(SEG_FPORT,SEG_FPIN,((SEG_Au8Display[Copy_u8Num]>>5)&1));
		DIO_enuSetPinValue(SEG_GPORT,SEG_GPIN,((SEG_Au8Display[Copy_u8Num]>>6)&1));
#elif SEG_TYPE == COMMON_ANODE
		DIO_enuSetPinValue(SEG_APORT,SEG_APIN,!((SEG_Au8Display[Copy_u8Num]>>0)&1));
		DIO_enuSetPinValue(SEG_BPORT,SEG_BPIN,!((SEG_Au8Display[Copy_u8Num]>>1)&1));
		DIO_enuSetPinValue(SEG_CPORT,SEG_CPIN,!((SEG_Au8Display[Copy_u8Num]>>2)&1));
		DIO_enuSetPinValue(SEG_DPORT,SEG_DPIN,!((SEG_Au8Display[Copy_u8Num]>>3)&1));
		DIO_enuSetPinValue(SEG_EPORT,SEG_EPIN,!((SEG_Au8Display[Copy_u8Num]>>4)&1));
		DIO_enuSetPinValue(SEG_FPORT,SEG_FPIN,!((SEG_Au8Display[Copy_u8Num]>>5)&1));
		DIO_enuSetPinValue(SEG_GPORT,SEG_GPIN,!((SEG_Au8Display[Copy_u8Num]>>6)&1));
#else
#error "The seven segment type has a wrong selection !!"
#endif

	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t Seven_Segment_enuEnableCommon(void)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_CMN_PIN<=DIO_u8PIN7 && SEG_CMN_PORT <=DIO_u8PORTD

#if SEG_TYPE == COMMON_CATHODE
	DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN_PIN,DIO_u8PIN_LOW);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN_PIN,DIO_u8PIN_HIGH);
#else
#error "The seven segment type has a wrong selection !!"
#endif

#elif SEG_CMN_PIN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED
#else
#error "the common has wrong selection !!! "
#endif


	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t Seven_Segment_enuDisableCommon(void)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_CMN_PIN<=DIO_u8PIN7 && SEG_CMN_PORT <=DIO_u8PORTD

#if SEG_TYPE == COMMON_CATHODE
	DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN_PIN,DIO_u8PIN_HIGH);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN_PIN,DIO_u8PIN_LOW);
#else
#error "The seven segment type has a wrong selection !!"
#endif

#elif SEG_CMN_PIN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED
#else
#error "the common has wrong selection !!! "
#endif


	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t Seven_Segment_enuEnableDot(void)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_DOT_PIN<=DIO_u8PIN7 && SEG_DOT_PORT <=DIO_u8PORTD

#if SEG_TYPE == COMMON_CATHODE
	DIO_enuSetPinValue(SEG_DOT_PORT,SEG_DOT_PIN,DIO_u8PIN_HIGH);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_DOT_PORT,SEG_DOT_PIN,DIO_u8PIN_LOW);
#else
#error "The seven segment type has a wrong selection !!"
#endif

#elif SEG_DOT_PIN == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED
#else
#error "the DOT led has wrong selection !!! "
#endif



	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t Seven_Segment_enuDisableDot(void)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_DOT_PIN<=DIO_u8PIN7 && SEG_DOT_PORT <=DIO_u8PORTD

#if SEG_TYPE == COMMON_CATHODE
	DIO_enuSetPinValue(SEG_DOT_PORT,SEG_DOT_PIN,DIO_u8PIN_LOW);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_DOT_PORT,SEG_DOT_PIN,DIO_u8PIN_HIGH);
#else
#error "The seven segment type has a wrong selection !!"
#endif

#elif SEG_DOT_PIN == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED
#else
#error "the DOT led has wrong selection !!! "
#endif


	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t Seven_Segment_enuClearDisplay(void)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_TYPE == COMMON_CATHODE
		DIO_enuSetPinValue(SEG_APORT,SEG_APIN,DIO_u8PIN_LOW);
		DIO_enuSetPinValue(SEG_BPORT,SEG_BPIN,DIO_u8PIN_LOW);
		DIO_enuSetPinValue(SEG_CPORT,SEG_CPIN,DIO_u8PIN_LOW);
		DIO_enuSetPinValue(SEG_DPORT,SEG_DPIN,DIO_u8PIN_LOW);
		DIO_enuSetPinValue(SEG_EPORT,SEG_EPIN,DIO_u8PIN_LOW);
		DIO_enuSetPinValue(SEG_FPORT,SEG_FPIN,DIO_u8PIN_LOW);
		DIO_enuSetPinValue(SEG_GPORT,SEG_GPIN,DIO_u8PIN_LOW);
#elif SEG_TYPE == COMMON_ANODE
		DIO_enuSetPinValue(SEG_APORT,SEG_APIN,DIO_u8PIN_HIGH);
		DIO_enuSetPinValue(SEG_BPORT,SEG_BPIN,DIO_u8PIN_HIGH);
		DIO_enuSetPinValue(SEG_CPORT,SEG_CPIN,DIO_u8PIN_HIGH);
		DIO_enuSetPinValue(SEG_DPORT,SEG_DPIN,DIO_u8PIN_HIGH);
		DIO_enuSetPinValue(SEG_EPORT,SEG_EPIN,DIO_u8PIN_HIGH);
		DIO_enuSetPinValue(SEG_FPORT,SEG_FPIN,DIO_u8PIN_HIGH);
		DIO_enuSetPinValue(SEG_GPORT,SEG_GPIN,DIO_u8PIN_HIGH);
#else
#error "The seven segment type has a wrong selection !!"
#endif


	/*Then return error state variable*/
	return Local_enuErrorState;
}









