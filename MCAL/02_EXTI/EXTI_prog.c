/*
 * EXTI_prog.c
 *
 *  Created on: Mar 22, 2023
 *      Author: REZK
 */


#include "stdTypes.h"
#include "errorStates.h"


#include "EXTI_priv.h"
#include "EXTI_int.h"

static void (*EXTI_pfunINT0fun)(void)  = NULL;
static void (*EXTI_pfunINT1fun)(void)  = NULL;
static void (*EXTI_pfunINT2fun)(void)  = NULL;

ES_t EXTI_enuInit(EXTI_t *Copy_pstrEXTIConfig)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8Iterator=0;
	if (Copy_pstrEXTIConfig != NULL)
	{
		for(Local_u8Iterator=0 ; Local_u8Iterator < 3 ; Local_u8Iterator++)
		{
			if(Copy_pstrEXTIConfig[Local_u8Iterator].EXTI_enuState == EXTI_enuActive)
			{
				/*enable*/
				switch(Copy_pstrEXTIConfig[Local_u8Iterator].EXTI_enuID)
				{
				case EXTI_enuINT0 :
					GICR |=(1<<INT0);
					switch(Copy_pstrEXTIConfig[Local_u8Iterator].EXTI_enuSenceLevel)
					{
					case EXTI_enuLowLevel:
						MCUCR&=~(1<<ISC00);
						MCUCR&=~(1<<ISC01);
						break;
					case EXTI_enuAnyLogicalChange:
						MCUCR|=(1<<ISC00);
						MCUCR&=~(1<<ISC01);
						break;
					case EXTI_enuFallingEdge:
						MCUCR&=~(1<<ISC00);
						MCUCR|=(1<<ISC01);
						break;
					case EXTI_enuRisingEdge:
						MCUCR|=(1<<ISC00);
						MCUCR|=(1<<ISC01);
						break;
					}
					break;
					case EXTI_enuINT1 :
						GICR |=(1<<INT1);
						switch(Copy_pstrEXTIConfig[Local_u8Iterator].EXTI_enuSenceLevel)
						{
						case EXTI_enuLowLevel:
							MCUCR&=~(1<<ISC10);
							MCUCR&=~(1<<ISC11);
							break;
						case EXTI_enuAnyLogicalChange:
							MCUCR|=(1<<ISC10);
							MCUCR&=~(1<<ISC11);
							break;
						case EXTI_enuFallingEdge:
							MCUCR&=~(1<<ISC10);
							MCUCR|=(1<<ISC11);
							break;
						case EXTI_enuRisingEdge:
							MCUCR|=(1<<ISC10);
							MCUCR|=(1<<ISC11);
							break;
						}
						break;
						case EXTI_enuINT2 :
							GICR |=(1<<INT2);
							switch(Copy_pstrEXTIConfig[Local_u8Iterator].EXTI_enuSenceLevel)
							{
							case EXTI_enuLowLevel:
								MCUCSR&=~(1<<ISC2); //wrong
								break;
							case EXTI_enuAnyLogicalChange:
								MCUCSR&=~(1<<ISC2); //wrong
								break;
							case EXTI_enuFallingEdge:
								MCUCSR&=~(1<<ISC2);
								break;
							case EXTI_enuRisingEdge:
								MCUCSR|=(1<<ISC2);
								break;
							default:
								break;
							}
							break;
				}

			}
			else if(Copy_pstrEXTIConfig[Local_u8Iterator].EXTI_enuState == EXTI_enuDeActive)
			{
				/*Disable*/
				switch(Copy_pstrEXTIConfig[Local_u8Iterator].EXTI_enuID)
				{
				case EXTI_enuINT0 :
					GICR &=~(1<<INT0);
					break;
				case EXTI_enuINT1 :
					GICR &=~(1<<INT1);
					break;
				case EXTI_enuINT2 :
					GICR &=~(1<<INT2);
					break;
				}

			}
		}


	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t EXTI_enuSetSenceMode(EXI_ID_t Copy_enuEXTI_ID,EXTI_SenceLevel_t Copy_enuSenceLevel)
{
	ES_t Local_enuErrorState = ES_NOK;

	switch(Copy_enuEXTI_ID)
	{
	case EXTI_enuINT0 :
		switch(Copy_enuSenceLevel)
		{
		case EXTI_enuLowLevel:
			MCUCR&=~(1<<ISC00);
			MCUCR&=~(1<<ISC01);
			break;
		case EXTI_enuAnyLogicalChange:
			MCUCR|=(1<<ISC00);
			MCUCR&=~(1<<ISC01);
			break;
		case EXTI_enuFallingEdge:
			MCUCR&=~(1<<ISC00);
			MCUCR|=(1<<ISC01);
			break;
		case EXTI_enuRisingEdge:
			MCUCR|=(1<<ISC00);
			MCUCR|=(1<<ISC01);
			break;
		}
		break;
		case EXTI_enuINT1 :
			switch(Copy_enuSenceLevel)
			{
			case EXTI_enuLowLevel:
				MCUCR&=~(1<<ISC10);
				MCUCR&=~(1<<ISC11);
				break;
			case EXTI_enuAnyLogicalChange:
				MCUCR|=(1<<ISC10);
				MCUCR&=~(1<<ISC11);
				break;
			case EXTI_enuFallingEdge:
				MCUCR&=~(1<<ISC10);
				MCUCR|=(1<<ISC11);
				break;
			case EXTI_enuRisingEdge:
				MCUCR|=(1<<ISC10);
				MCUCR|=(1<<ISC11);
				break;
			}
			break;
			case EXTI_enuINT2 :
				switch(Copy_enuSenceLevel)
				{
				case EXTI_enuLowLevel:
					MCUCSR&=~(1<<ISC2); //wrong
					break;
				case EXTI_enuAnyLogicalChange:
					MCUCSR&=~(1<<ISC2); //wrong
					break;
				case EXTI_enuFallingEdge:
					MCUCSR&=~(1<<ISC2);
					break;
				case EXTI_enuRisingEdge:
					MCUCSR|=(1<<ISC2);
					break;
				}
				break;
	}

	return Local_enuErrorState;
}

ES_t EXTI_enuEnable(EXI_ID_t Copy_enuEXTI_ID)
{
	ES_t Local_enuErrorState = ES_NOK;
	switch(Copy_enuEXTI_ID)
	{
	case EXTI_enuINT0 :
		GICR |=(1<<INT0);
		Local_enuErrorState = ES_OK;
		break;
	case EXTI_enuINT1 :
		GICR |=(1<<INT1);
		Local_enuErrorState = ES_OK;
		break;
	case EXTI_enuINT2 :
		GICR |=(1<<INT2);
		Local_enuErrorState = ES_OK;
		break;
	}

	return Local_enuErrorState;
}

ES_t EXTI_enuDisable(EXI_ID_t Copy_enuEXTI_ID)
{
	ES_t Local_enuErrorState = ES_NOK;

	switch(Copy_enuEXTI_ID)
	{
	case EXTI_enuINT0 :
		GICR &=~(1<<INT0);
		Local_enuErrorState = ES_OK;
		break;
	case EXTI_enuINT1 :
		GICR &=~(1<<INT1);
		Local_enuErrorState = ES_OK;
		break;
	case EXTI_enuINT2 :
		GICR &=~(1<<INT2);
		Local_enuErrorState = ES_OK;
		break;
	}


	return Local_enuErrorState;
}

ES_t EXTI_enuCallBack(EXI_ID_t Copy_enuEXTI_ID , void(*Copy_pfunEXTI_fun)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	switch(Copy_enuEXTI_ID)
	{
	case EXTI_enuINT0 :
		EXTI_pfunINT0fun = Copy_pfunEXTI_fun;
		Local_enuErrorState = ES_OK;
		break;
	case EXTI_enuINT1 :
		EXTI_pfunINT1fun = Copy_pfunEXTI_fun;
		Local_enuErrorState = ES_OK;
		break;
	case EXTI_enuINT2 :
		EXTI_pfunINT2fun = Copy_pfunEXTI_fun;
		Local_enuErrorState = ES_OK;
		break;
	default :
		Local_enuErrorState = ES_NOK;
		break;
	}

	return Local_enuErrorState;
}


/*ISR FOR INT0*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if(EXTI_pfunINT0fun!=NULL)
	{
		EXTI_pfunINT0fun();
	}

}

/*ISR FOR INT1*/
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_pfunINT1fun!=NULL)
	{
		EXTI_pfunINT1fun();
	}
}

/* ISR FOR INT2*/
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if(EXTI_pfunINT2fun!=NULL)
	{
		EXTI_pfunINT2fun();
	}
}

void __vector_default(void) __attribute__((signal));
void __vector_default(void)
{
	// bad interrupt
	// write what you want to indicate that
}






