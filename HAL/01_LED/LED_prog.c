/*
 * LED_prog.c
 *
 *  Created on: Feb 12, 2023
 *      Author: REZK
 */
#include"stdTypes.h"
#include"errorStates.h"

#include"DIO_int.h"

#include"LED_priv.h"
#include"LED_config.h"
#include"LED_int.h"



ES_t LED_enuInit(LED_t *Copy_pstrLedConfig)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pstrLedConfig!=NULL)
	{
		u8 Local_u8Iterator = 0;
		for(Local_u8Iterator=0 ; Local_u8Iterator < LED_NUM ; Local_u8Iterator++)
		{   /*at the first set the direction (output)*/
			Local_enuErrorState = DIO_enuSetPinDirection(Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
					Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID, DIO_u8PIN_OUTPUT);

			if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8Connection == LED_SINK)// sink connection
			{
				if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8InitState == LED_ON)
				{
					Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
							Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID, DIO_u8PIN_LOW);
				}
				else if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8InitState == LED_OFF)
				{
					Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
							Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID, DIO_u8PIN_HIGH);
				}
				else
				{
					Local_enuErrorState = ES_OUT_OF_RANGE;
				}
			}
			else if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8Connection == LED_SOURCE)// source connection
			{
				if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8InitState == LED_ON)
				{
					Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
							Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID, DIO_u8PIN_HIGH);
				}
				else if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8InitState == LED_OFF)
				{
					Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
							Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID, DIO_u8PIN_LOW);
				}
				else
				{
					Local_enuErrorState = ES_OUT_OF_RANGE;
				}
			}
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	/*Then return error state variable*/
	return Local_enuErrorState;
}


/*******************************************************************************/

ES_t LED_enuIurnON(LED_t *Copy_pstrLedConfig)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pstrLedConfig!=NULL)
	{
		if(Copy_pstrLedConfig->LED_u8Connection == LED_SINK)// sink connection
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedConfig->LED_u8PortID,
					Copy_pstrLedConfig->LED_u8PinID, DIO_u8PIN_LOW);
		}
		else if(Copy_pstrLedConfig->LED_u8Connection == LED_SOURCE)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedConfig->LED_u8PortID,
					Copy_pstrLedConfig->LED_u8PinID, DIO_u8PIN_HIGH);
		}

	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	/*Then return error state variable*/
	return Local_enuErrorState;
}
/*******************************************************************************/

ES_t LED_enuIurnOFF(LED_t *Copy_pstrLedConfig)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pstrLedConfig!=NULL)
	{
		if(Copy_pstrLedConfig->LED_u8Connection == LED_SINK)// sink connection
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedConfig->LED_u8PortID,
					Copy_pstrLedConfig->LED_u8PinID, DIO_u8PIN_HIGH);
		}
		else if(Copy_pstrLedConfig->LED_u8Connection == LED_SOURCE)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedConfig->LED_u8PortID,
					Copy_pstrLedConfig->LED_u8PinID, DIO_u8PIN_LOW);
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	/*Then return error state variable*/
	return Local_enuErrorState;
}

/*******************************************************************************/


