/*
 * Switch_prog.c
 *
 *  Created on: Feb 12, 2023
 *      Author: REZK
 */

#include"stdTypes.h"
#include"errorStates.h"

#include"DIO_int.h"
#include"Switch_config.h"
#include"Switch_priv.h"



ES_t Switch_enuInit(SW_t* Copy_AstrSwitchs)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8Iterator=0;

	if(Copy_AstrSwitchs != NULL)
	{

		for(Local_u8Iterator=0 ; Local_u8Iterator < SW_NUM ; Local_u8Iterator++ )
		{
			Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSwitchs[Local_u8Iterator].SW_PortID,
					Copy_AstrSwitchs[Local_u8Iterator].SW_PinID,
					DIO_u8PIN_INPUT);

			Local_enuErrorState = DIO_enuSetPinValue(Copy_AstrSwitchs[Local_u8Iterator].SW_PortID,
					Copy_AstrSwitchs[Local_u8Iterator].SW_PinID,
					Copy_AstrSwitchs[Local_u8Iterator].SW_Status);
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	/*Then return error state variable*/
	return Local_enuErrorState;
}


ES_t Switch_enuGetState(SW_t* Copy_AstrSwitchs,u8* Copy_pu8SwchState)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_AstrSwitchs!=NULL && Copy_pu8SwchState != NULL)
	{
		Local_enuErrorState = DIO_enuGetPinValue(Copy_AstrSwitchs->SW_PortID,
				Copy_AstrSwitchs->SW_PinID,
				Copy_pu8SwchState);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

/*Then return error state variable*/
     return Local_enuErrorState;
}





















