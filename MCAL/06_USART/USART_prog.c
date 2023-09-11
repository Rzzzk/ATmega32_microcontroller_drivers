/*
 * USART_prog.c
 *
 *  Created on: Mar 28, 2023
 *      Author: REZK
 */

#include "errorStates.h"
#include "stdTypes.h"
#include "commonMacros.h"

#include "USART_int.h"
#include "USART_priv.h"


u8 *USART_pu8TransmittedData  = NULL;
u8 *USART_pu8ReceivedData = NULL;

void (*USART_pfReceiveNotification)(void) = NULL;
void (*USART_pfTransmitNotification)(void) = NULL;

ES_t USART_enuReceiveBusyState = ES_FUNC_IS_IDLE;
ES_t USART_enuTransmitBusyState = ES_FUNC_IS_IDLE;




ES_t USART_enuInit(USART_t *Copy_strUSARTConfig)
{
	ES_t Local_enuErrirState = ES_NOK;


	/* Baud rate settings*/
	u8 USART_u16BaudRate; //= (((F_CPU)/((Copy_strUSARTConfig->USART_u16BaudRate)* 16UL))-1);


	// Normal speed or double speed
	switch(Copy_strUSARTConfig->USART_enuSpeed)
	{
	case USART_enuNormalSpeed:
		UCSRA&=~(1<<U2X);
		USART_u16BaudRate = (((F_CPU)/((Copy_strUSARTConfig->USART_u16BaudRate)* 16UL))-1);
		break;
	case USART_enuDoubleSpeed:
		UCSRA|=(1<<U2X);
		USART_u16BaudRate = (((F_CPU)/((Copy_strUSARTConfig->USART_u16BaudRate)* 8UL))-1);
		break;
	}

	UBRRH =  USART_u16BaudRate>>8;
	UBRRL =  USART_u16BaudRate;

	// UCSRC buffer
	u8 Local_u8UCSRC_Buffer = 0;
	Local_u8UCSRC_Buffer|=(1<<URSEL);

	//Synchronous or Asynchronous
	switch(Copy_strUSARTConfig->USART_enuClockMode)
	{
	case USART_enuAsynchronous:
		Local_u8UCSRC_Buffer &=~(1<<UMSEL);
		break;
	case USART_enuSynchronous:
		Local_u8UCSRC_Buffer |=(1<<UMSEL);
		break;
	}

	//Parity bit mode
	switch(Copy_strUSARTConfig->USART_enuParityBitState)
	{
	case USART_enuNoParity :
		Local_u8UCSRC_Buffer &=~(1<<UPM0);
		Local_u8UCSRC_Buffer &=~(1<<UPM1);
		break;
	case USART_enuEvenParity :
		Local_u8UCSRC_Buffer &=~(1<<UPM0);
		Local_u8UCSRC_Buffer |=(1<<UPM1);
		break;
	case USART_enuOddParity :
		Local_u8UCSRC_Buffer |=(1<<UPM0);
		Local_u8UCSRC_Buffer |=(1<<UPM1);
		break;
	}

	//Stop Bit Select
	switch(Copy_strUSARTConfig->USART_enuStopBitState)
	{
	case USART_enuOneStopBit:
		Local_u8UCSRC_Buffer&=~(1<<USBS);
		break;
	case USART_enuTwoStopBit:
		Local_u8UCSRC_Buffer|=(1<<USBS);
		break;
	}

	//Data bits number
	switch(Copy_strUSARTConfig->USART_enuNumOfDataBit)
	{
	case USART_enuFiveBits:
		Local_u8UCSRC_Buffer&=~(1<<UCSZ0);
		Local_u8UCSRC_Buffer&=~(1<<UCSZ1);
		UCSRB&=~(1<<UCSZ2);
		break;
	case USART_enuSixBits:
		Local_u8UCSRC_Buffer|=(1<<UCSZ0);
		Local_u8UCSRC_Buffer&=~(1<<UCSZ1);
		UCSRB&=~(1<<UCSZ2);
		break;
	case USART_enuSeveneBits:
		Local_u8UCSRC_Buffer&=~(1<<UCSZ0);
		Local_u8UCSRC_Buffer|=(1<<UCSZ1);
		UCSRB&=~(1<<UCSZ2);
		break;
	case USART_enuEightBits:
		Local_u8UCSRC_Buffer|=(1<<UCSZ0);
		Local_u8UCSRC_Buffer|=(1<<UCSZ1);
		UCSRB&=~(1<<UCSZ2);
		break;
	case USART_enuNineBits:
		Local_u8UCSRC_Buffer|=(1<<UCSZ0);
		Local_u8UCSRC_Buffer|=(1<<UCSZ1);
		UCSRB|=(1<<UCSZ2);
		break;
	}


	//polarity with synchronous mode only
	switch(Copy_strUSARTConfig->USART_enuClockPolarity)
	{
	case USART_enuNoClockPolarity:

		break;
	case USART_enuTransOnRisingRecOnFalling:
		Local_u8UCSRC_Buffer&=~(1<<UCPOL);
		break;
	case USART_enuTransOnFallingRecOnRising:
		Local_u8UCSRC_Buffer|=(1<<UCPOL);
		break;
	}

	UCSRC = Local_u8UCSRC_Buffer;


	switch(Copy_strUSARTConfig->USART_enuState)
	{
	case USART_enuTransmiter:
		UCSRB|=(1<<TXEN);
		UCSRB&=~(1<<RXEN);
		break;
	case USART_enuReciever:
		UCSRB&=~(1<<TXEN);
		UCSRB|=(1<<RXEN);
		break;
	case USART_enuTransmiterAndReciever:
		UCSRB|=(1<<TXEN);
		UCSRB|=(1<<RXEN);
		break;
	}

	return Local_enuErrirState;
}




ES_t USART_enuSendCharSynch(u8 Copy_u8Char , u8 Copy_u16TimeOut)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8TimeOut = 0 ;


	if(USART_enuTransmitBusyState == ES_FUNC_IS_BUSY)
	{
		Local_enuErrorState = ES_FUNC_IS_BUSY;
	}
	else
	{
		USART_enuTransmitBusyState = ES_FUNC_IS_BUSY; // <>

		// wait until the TX empty flag & Time out
		while((READ_BIT(UCSRA,UDRE))==0 && Local_u8TimeOut < Copy_u16TimeOut) // 10000 6000
		{
			Local_u8TimeOut++;
		}
		if(Local_u8TimeOut == Copy_u16TimeOut)
		{
			Local_enuErrorState = ES_NOK;
		}
		else
		{
			//Send the data
			UDR = Copy_u8Char;
			Local_enuErrorState = ES_OK;
		}

		USART_enuTransmitBusyState = ES_FUNC_IS_IDLE;// </>
	}

	return Local_enuErrorState;
}


ES_t USART_enuReceiveCharSynch(u8 *Copy_u8Char , u8 Copy_u16TimeOut)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8TimeOut = 0 ;

	if(USART_enuReceiveBusyState == ES_FUNC_IS_BUSY)
	{
		Local_enuErrorState = ES_FUNC_IS_BUSY;
	}
	else
	{
		USART_enuReceiveBusyState = ES_FUNC_IS_BUSY; // <>

		while(READ_BIT(UCSRA,RXC)==0 && Local_u8TimeOut<Copy_u16TimeOut)
		{
			Local_u8TimeOut++;
		}
		if(Local_u8TimeOut == Copy_u16TimeOut)
		{
			Local_enuErrorState = ES_NOK;
		}
		else
		{
			/*receive the data*/
			*Copy_u8Char = UDR;
			Local_enuErrorState = ES_OK;
		}

		USART_enuReceiveBusyState = ES_FUNC_IS_IDLE; // </>
	}


	return Local_enuErrorState;
}


ES_t USART_enuSendCharAsynch(u8 *Copy_u8Char , void (*Copy_pfNotCallBack)(void))
{
	ES_t Local_enuErrorState = ES_NOK;


	if(Copy_u8Char==NULL || Copy_pfNotCallBack == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else if (USART_enuTransmitBusyState == ES_FUNC_IS_BUSY)
	{
		Local_enuErrorState = ES_FUNC_IS_BUSY;
	}
	else
	{
		USART_enuTransmitBusyState = ES_FUNC_IS_BUSY; // <>

		/*at the first, pass the local variables to the global*/
		USART_pu8TransmittedData = Copy_u8Char;
		USART_pfTransmitNotification = Copy_pfNotCallBack;


		/*enable the interrupt*/
		/*the interrupt will occur when the transmit buffer (UDR) is ready to receive new data.
		  If UDRE flag is one*/
		SET_BIT(UCSRB,UDRIE);

	}

	return Local_enuErrorState;
}


ES_t USART_enuReceiveCharAsynch(u8 *Copy_u8Char , void (*Copy_pfNotCallBack)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u8Char==NULL || Copy_pfNotCallBack == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else if (USART_enuReceiveBusyState == ES_FUNC_IS_BUSY)
	{
		Local_enuErrorState = ES_FUNC_IS_BUSY;
	}
	else
	{
		USART_enuReceiveBusyState = ES_FUNC_IS_BUSY;

		/*at the first bass the local variables to the global*/
		USART_pu8ReceivedData = Copy_u8Char;
		USART_pfReceiveNotification = Copy_pfNotCallBack;

		/*enable the interrupt*/
		SET_BIT(UCSRB,RXCIE);

	}


	return Local_enuErrorState;
}




void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{
	if(USART_pu8ReceivedData == NULL || USART_pfReceiveNotification == NULL)
	{
		/*Don't do any thing */
	}
	else
	{
		/*Read the data*/
		*USART_pu8ReceivedData = UDR;

		/*call the notification function*/
		USART_pfReceiveNotification();

		/*the USART now is available to use*/
		USART_enuReceiveBusyState = ES_FUNC_IS_IDLE; // </>

		/*Disable the interrupt*/
		CLEAR_BIT(UCSRB,RXCIE);

	}
}

/*UDR buffer is empty*/
void __vector_14 (void) __attribute__((signal));
void __vector_14 (void)
{

	if(USART_pu8TransmittedData == NULL || USART_pfTransmitNotification == NULL)
	{
		/*Don't do any thing */
	}
	else
	{
		/*write the data in the buffer */
		UDR = *USART_pu8TransmittedData;

		/*call the notification function*/
		USART_pfTransmitNotification();

		/*Disable the interrupt*/
		CLEAR_BIT(UCSRB,UDRIE);

		USART_pfTransmitNotification = NULL;
		USART_pu8TransmittedData = NULL;

		/*the USART now is available to use*/
		USART_enuTransmitBusyState = ES_FUNC_IS_IDLE; // </>
	}
}



