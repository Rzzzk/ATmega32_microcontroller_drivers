/*
 * USART_config.c
 *
 *  Created on: Mar 28, 2023
 *      Author: REZK
 */
#include "stdTypes.h"
#include "errorStates.h"
#include "USART_int.h"

USART_t USART_strUSARTConfig=
{
		USART_enuAsynchronous,           //Synchronous(Clock) or Asynchronous
		USART_enuTransmiterAndReciever,  //Transmitter or Receiver or both
		USART_enuNormalSpeed,            //Normal speed or double speed
		4800,                            //Choose the baud rate
		USART_enuNoParity,               //Parity bit state
		USART_enuOneStopBit,             //Stop bit count
		USART_enuEightBits,              //Count of Data bits
		USART_enuNoClockPolarity         //Clock polarity for Synchronous clock mode
};
