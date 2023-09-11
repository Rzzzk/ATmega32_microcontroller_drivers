/*
 * USART_int.h
 *
 *  Created on: Mar 28, 2023
 *      Author: REZK
 */

#ifndef USART_INT_H_
#define USART_INT_H_

typedef enum
{
	USART_enuTransmiter,
	USART_enuReciever,
	USART_enuTransmiterAndReciever
}USART_state_t;


typedef enum
{
	USART_enuSynchronous,
	USART_enuAsynchronous
}USART_ClockMode_t;

typedef enum
{
	USART_enuNormalSpeed,
	USART_enuDoubleSpeed

}USART_speed_t;

typedef enum
{
	USART_enuNoParity,
	USART_enuOddParity,
	USART_enuEvenParity

}USART_parityState_t;

typedef enum
{
	USART_enuOneStopBit,
	USART_enuTwoStopBit

}USART_stopState_t;

typedef enum
{
	USART_enuNoClockPolarity,
	USART_enuTransOnRisingRecOnFalling,
	USART_enuTransOnFallingRecOnRising,
}USART_ClockPolarity_t;

typedef enum
{
	USART_enuFiveBits,
	USART_enuSixBits,
	USART_enuSeveneBits,
	USART_enuEightBits,
	USART_enuNineBits
}USART_dataLenth_t;


typedef struct
{
	USART_ClockMode_t USART_enuClockMode;
	USART_state_t USART_enuState;
	USART_speed_t USART_enuSpeed;
	u32 USART_u16BaudRate;
	USART_parityState_t USART_enuParityBitState;
	USART_stopState_t USART_enuStopBitState;
	USART_dataLenth_t USART_enuNumOfDataBit;
	USART_ClockPolarity_t USART_enuClockPolarity;
}USART_t;


ES_t USART_enuInit(USART_t *Copy_strUSARTConfig);


/*Synchronous Functions*/
ES_t USART_enuSendCharSynch(u8 Copy_u8Char , u8 Copy_u16TimeOut);

ES_t USART_enuReceiveCharSynch(u8 *Copy_u8Char , u8 Copy_u16TimeOut);


/*Asynchronous Function*/
ES_t USART_enuSendCharAsynch(u8 *Copy_u8Char , void (*Copy_pfNotCallBack)(void));

ES_t USART_enuReceiveCharAsynch(u8 *Copy_u8Char , void (*Copy_pfNotCallBack)(void));



#endif /* USART_INT_H_ */
