/*
 * ADC_prog.c
 *
 *  Created on: Apr 24, 2023
 *      Author: REZK
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "commonMacros.h"


#include "ADC_int.h"
#include "ADC_priv.h"

static u16* ADC_pu16ADCReading = NULL;
static void(*ADC_pfCallBackNotification)(void) = NULL;

ES_t ADC_enuBusyState = ES_FUNC_IS_IDLE;



ES_t ADC_enuInit(ADC_t *Copy_strADCConcfig)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set the volt reference*/
	switch(Copy_strADCConcfig->ADC_enuVoltRef)
	{
	case VREF_AVCC:
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
	case VREF_AREF:
		SET_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
	case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}

	/*Set the prescaler*/
	ADCSRA &=0xf8;
	Copy_strADCConcfig->ADC_enuPrescaler &=0x07;
	ADCSRA|=Copy_strADCConcfig->ADC_enuPrescaler;


	/*Enable the ADC peripheral*/
	SET_BIT(ADCSRA,ADEN);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;

}





ES_t ADC_enuStartConversionSynch(ADC_Channel_t Copy_enuChannel , u16* Copy_pu16ADCReading , u16 Copy_u16Timeout)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pu16ADCReading == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else if(ADC_enuBusyState == ES_FUNC_IS_BUSY)
	{
		Local_enuErrorState = ES_FUNC_IS_BUSY;
	}
	else
	{

		/*at first make the ADC function busy*/
		ADC_enuBusyState = ES_FUNC_IS_BUSY;

		u16 Local_u16Timeout = Copy_u16Timeout;

		ADMUX&=0xE0;
		ADMUX|=Copy_enuChannel;

		// start conversion
		SET_BIT(ADCSRA,ADSC);

		// wait until the conversion completed (polling)
		while((READ_BIT(ADCSRA,ADSC)) || Local_u16Timeout < Copy_u16Timeout )
		{
			Local_u16Timeout++;
		}

		if(Local_u16Timeout == Copy_u16Timeout)
		{
			Local_enuErrorState = ES_NOK;
		}
		else
		{
			*Copy_pu16ADCReading = ADC;
			Local_enuErrorState = ES_OK;
		}

		/*at last make the ADC function idle*/
		ADC_enuBusyState = ES_FUNC_IS_IDLE;

	}

	return Local_enuErrorState;
}





ES_t ADC_enuStartConversionAsynch(ADC_Channel_t Copy_enuChannel , u16* Copy_pu16ADCReading , void(*Copy_pfCallBackNotification)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if((Copy_pu16ADCReading==NULL) || (Copy_pfCallBackNotification==NULL) )
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else if(ADC_enuBusyState == ES_FUNC_IS_BUSY)
	{
		Local_enuErrorState = ES_FUNC_IS_BUSY;
	}
	else
	{

		/*at first make the ADC function busy*/
		ADC_enuBusyState = ES_FUNC_IS_BUSY;

		/* ************************************************
		 * Make a global pointer to have the same addresses
		 * to be able to access these addresses
		 * ************************************************ */
		ADC_pu16ADCReading = Copy_pu16ADCReading;
		ADC_pfCallBackNotification = Copy_pfCallBackNotification;

		/*Set the channel*/
		ADMUX&=0xE0;
		ADMUX|=Copy_enuChannel;

		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);

		/*ADC interrupt enable*/
		SET_BIT(ADCSRA,ADIE);

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

/*

typedef struct
{
	ADC_Channel_t Chain_FirstChannel;
	ADC_Channel_t Chain_LastChannel;
	u16 Chain_ResultArr[NUM_OF_CHANNELS];
	void (*Chain_CallBackNotification)(void);

}ADC_Chain_t;

 */


ADC_Channel_t ADC_u8ChainIndex;
ADC_Channel_t ADC_pu8LastChianChannel;
u8 ADC_u8ChainArrIndex = 100 ;



ES_t ADC_enuStartChainConversion(ADC_Chain_t *Copy_pstrChain )
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pstrChain == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else if(ADC_enuBusyState == ES_FUNC_IS_BUSY)
	{
		Local_enuErrorState = ES_FUNC_IS_BUSY;
	}
	else
	{
		/* At the first make the ADC busy state flag > " Busy " */
		ADC_enuBusyState = ES_FUNC_IS_BUSY;

		/*Bass the copy_chain to global_chain to use in ISR */

		// Bass the first channel
		ADC_u8ChainIndex = Copy_pstrChain->Chain_FirstChannel;

		// Initiate the array index
		ADC_u8ChainArrIndex = 0;

		// Bass the last channel
		ADC_pu8LastChianChannel = Copy_pstrChain->Chain_LastChannel;

		//Bass the array address
		ADC_pu16ADCReading = Copy_pstrChain->Chain_ResultArr;

		// Initiate the callback function
		ADC_pfCallBackNotification = Copy_pstrChain->Chain_CallBackNotification;


		/*Set the first channel*/
		ADMUX&=0xE0;
		ADMUX|=ADC_u8ChainIndex;

		/*Start conversion*/
		SET_BIT(ADCSRA,ADSC);

		/*ADC interrupt enable*/
		SET_BIT(ADCSRA,ADIE);

	}



	return Local_enuErrorState;
}



void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if((ADC_pu16ADCReading==NULL) || (ADC_pfCallBackNotification==NULL))
	{
		/*Don't do any thing*/
	}
	else if( ADC_u8ChainArrIndex != 100)
	{
		if(ADC_u8ChainIndex == ADC_pu8LastChianChannel)
		{
			/*Read the ADC and but it in the array at the LAST index*/
			ADC_pu16ADCReading[ADC_u8ChainArrIndex] = ADC;

			/*make the ADC function idle*/
			ADC_enuBusyState = ES_FUNC_IS_IDLE;

			ADC_u8ChainArrIndex = 100;

			/*Call notification function*/
			ADC_pfCallBackNotification();

			/*Disable Interrupt*/
			CLEAR_BIT(ADCSRA,ADIE);
		}
		else
		{
			/*Read the ADC and but it in the array at the current index*/
			ADC_pu16ADCReading[ADC_u8ChainArrIndex] = ADC;

			/*Move to the next Index in result array*/
			ADC_u8ChainArrIndex+=1;

			/*Move to the next channel*/
			ADC_u8ChainIndex+=1;

			/*Set the next Channel*/
			ADMUX&=0xE0;
			ADMUX|=ADC_u8ChainIndex;

			/*Start conversion*/
			SET_BIT(ADCSRA,ADSC);

		}

	}
	else
	{
		/*read the ADC value*/
		*ADC_pu16ADCReading = ADC;

		/*make the ADC function idle*/
		ADC_enuBusyState = ES_FUNC_IS_IDLE;

		/*call the notification function*/
		ADC_pfCallBackNotification();

		/*Make the global pointers NULL pointers*/
		ADC_pu16ADCReading=NULL;
		ADC_pfCallBackNotification=NULL;

		/*ADC interrupt disable*/
		CLEAR_BIT(ADCSRA,ADIE);

	}

}










