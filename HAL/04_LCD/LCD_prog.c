/*
 * LCD_prog.c
 *
 *  Created on: Feb 18, 2023
 *      Author: REZK
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "util/delay.h"

#include "DIO_int.h"

#include "LCD_priv.h"
#include "LCD_config.h"


ES_t LCD_enuInit(void)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_OK;
	_delay_ms(50);
	/* We must set RS , RW and EN as output */
	DIO_enuSetPinDirection(RS_PORT, RS_PIN,DIO_u8PIN_OUTPUT);
	DIO_enuSetPinDirection(RW_PORT, RW_PIN,DIO_u8PIN_OUTPUT);
	DIO_enuSetPinDirection(EN_PORT, EN_PIN,DIO_u8PIN_OUTPUT);

	DIO_enuSetPinDirection(D4_PORT, D4_PIN,DIO_u8PIN_OUTPUT);
	DIO_enuSetPinDirection(D5_PORT, D5_PIN,DIO_u8PIN_OUTPUT);
	DIO_enuSetPinDirection(D6_PORT, D6_PIN,DIO_u8PIN_OUTPUT);
	DIO_enuSetPinDirection(D7_PORT, D7_PIN,DIO_u8PIN_OUTPUT);

#if LCD_MODE == EIGHT_BIT
	/*Set the direction for all pins*/
	DIO_enuSetPinDirection(D0_PORT, D0_PIN,DIO_u8PIN_OUTPUT);
	DIO_enuSetPinDirection(D1_PORT, D1_PIN,DIO_u8PIN_OUTPUT);
	DIO_enuSetPinDirection(D2_PORT, D2_PIN,DIO_u8PIN_OUTPUT);
	DIO_enuSetPinDirection(D3_PORT, D3_PIN,DIO_u8PIN_OUTPUT);
	_delay_ms(1);
	/*Function set*/
	/*8 Bit mode*/
	LCD_invidSendCommand(LCD_EIGHT_BIT_TWO_LINES);

#elif LCD_MODE == FOUR_BIT
	/*Function set*/
	/*4 Bit mode*/
	_delay_ms(1);
	LCD_invidSendCommand(LCD_FOUR_BIT_DATA);
	_delay_ms(1);
	LCD_invidSendCommand(LCD_FOUR_BIT_TWO_LINES);
#endif

	_delay_ms(1);
	LCD_invidSendCommand(0x0f);
	_delay_ms(2);
	LCD_invidSendCommand(LCD_INCREASE_DDRAM_ADRESS);
	_delay_ms(1);
	LCD_invidSendCommand(LCD_CLEAR_SCREEN);

	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuDisplayChar(u8 Copy_u8Char)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_u8PIN_HIGH);

	LCD_vidLatch(Copy_u8Char);

	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_u8PIN_LOW);

	LCD_vidLatch(Copy_u8Command);

	/*Then return error state variable*/
	return Local_enuErrorState;
}


static inline void LCD_invidSendCommand(u8 Copy_u8Command)
{
	/*To send command we have to clear RS and RW pins all time*/
	DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_u8PIN_LOW);
	DIO_enuSetPinValue(RW_PORT , RW_PIN , DIO_u8PIN_LOW);
	/*At first Disable LCD*/
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_LOW);

#if LCD_MODE == EIGHT_BIT
	/*Write the command on all pins*/
	DIO_enuSetPinValue(D0_PORT, D0_PIN, ((Copy_u8Command>>0)&1));
	DIO_enuSetPinValue(D1_PORT, D1_PIN, ((Copy_u8Command>>1)&1));
	DIO_enuSetPinValue(D2_PORT, D2_PIN, ((Copy_u8Command>>2)&1));
	DIO_enuSetPinValue(D3_PORT, D3_PIN, ((Copy_u8Command>>3)&1));
	DIO_enuSetPinValue(D4_PORT, D4_PIN, ((Copy_u8Command>>4)&1));
	DIO_enuSetPinValue(D5_PORT, D5_PIN, ((Copy_u8Command>>5)&1));
	DIO_enuSetPinValue(D6_PORT, D6_PIN, ((Copy_u8Command>>6)&1));
	DIO_enuSetPinValue(D7_PORT, D7_PIN, ((Copy_u8Command>>7)&1));
	_delay_ms(1);
	/*Latch the enable*/
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_LOW);
	_delay_ms(1);
#elif LCD_MODE == FOUR_BIT
	/*Send the uper command*/
	DIO_enuSetPinValue(D4_PORT, D4_PIN, ((Copy_u8Command>>4)&1));
	DIO_enuSetPinValue(D5_PORT, D5_PIN, ((Copy_u8Command>>5)&1));
	DIO_enuSetPinValue(D6_PORT, D6_PIN, ((Copy_u8Command>>6)&1));
	DIO_enuSetPinValue(D7_PORT, D7_PIN, ((Copy_u8Command>>7)&1));
	/*Latch the enable*/
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_LOW);
	_delay_ms(1);
	/*Then send the lower command*/
	DIO_enuSetPinValue(D4_PORT, D4_PIN, ((Copy_u8Command>>0)&1));
	DIO_enuSetPinValue(D5_PORT, D5_PIN, ((Copy_u8Command>>1)&1));
	DIO_enuSetPinValue(D6_PORT, D6_PIN, ((Copy_u8Command>>2)&1));
	DIO_enuSetPinValue(D7_PORT, D7_PIN, ((Copy_u8Command>>3)&1));
	/*Latch the enable*/
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_LOW);
	_delay_ms(1);
#endif

}

static inline void LCD_vidLatch(u8 Copy_u8Data)
{
	DIO_enuSetPinValue(RW_PORT , RW_PIN , DIO_u8PIN_LOW);
	/*At first Disable LCD*/
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_LOW);

#if LCD_MODE == EIGHT_BIT
	/*Write the command on all pins*/
	DIO_enuSetPinValue(D0_PORT, D0_PIN, ((Copy_u8Data>>0)&1));
	DIO_enuSetPinValue(D1_PORT, D1_PIN, ((Copy_u8Data>>1)&1));
	DIO_enuSetPinValue(D2_PORT, D2_PIN, ((Copy_u8Data>>2)&1));
	DIO_enuSetPinValue(D3_PORT, D3_PIN, ((Copy_u8Data>>3)&1));
	DIO_enuSetPinValue(D4_PORT, D4_PIN, ((Copy_u8Data>>4)&1));
	DIO_enuSetPinValue(D5_PORT, D5_PIN, ((Copy_u8Data>>5)&1));
	DIO_enuSetPinValue(D6_PORT, D6_PIN, ((Copy_u8Data>>6)&1));
	DIO_enuSetPinValue(D7_PORT, D7_PIN, ((Copy_u8Data>>7)&1));
	_delay_ms(1);
	/*Latch the enable*/
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_LOW);
	_delay_ms(1);

#elif LCD_MODE == FOUR_BIT
	/*Send the uper command*/
	DIO_enuSetPinValue(D4_PORT, D4_PIN, ((Copy_u8Data>>4)&1));
	DIO_enuSetPinValue(D5_PORT, D5_PIN, ((Copy_u8Data>>5)&1));
	DIO_enuSetPinValue(D6_PORT, D6_PIN, ((Copy_u8Data>>6)&1));
	DIO_enuSetPinValue(D7_PORT, D7_PIN, ((Copy_u8Data>>7)&1));
	/*Latch the enable*/
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_LOW);
	_delay_ms(1);
	/*Then send the lower command*/
	DIO_enuSetPinValue(D4_PORT, D4_PIN, ((Copy_u8Data>>0)&1));
	DIO_enuSetPinValue(D5_PORT, D5_PIN, ((Copy_u8Data>>1)&1));
	DIO_enuSetPinValue(D6_PORT, D6_PIN, ((Copy_u8Data>>2)&1));
	DIO_enuSetPinValue(D7_PORT, D7_PIN, ((Copy_u8Data>>3)&1));
	/*Latch the enable*/
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8PIN_LOW);
	_delay_ms(1);
#endif

}



ES_t LCD_enuDisplayString(const char* Copy_pu8String)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu8String != NULL)
	{
		u8 Local_u8Index = 0;
		while(Copy_pu8String[Local_u8Index]!='\0')
		{
			Local_enuErrorState = LCD_enuDisplayChar(Copy_pu8String[Local_u8Index]);
			Local_u8Index++;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}


	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuGoToRowCol(u8 Copy_u8Row , u8 Copy_u8Col)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

		u8 Local_u8ADDRAM_Address;

		switch(Copy_u8Row)
		{
		case 0: Local_u8ADDRAM_Address = Copy_u8Col;           break;
		case 1: Local_u8ADDRAM_Address = (Copy_u8Col+(0x40));      break;
		case 2: Local_u8ADDRAM_Address = (Copy_u8Col+0x10);      break;
		case 3: Local_u8ADDRAM_Address = (Copy_u8Col+0x50);      break;
		}

		LCD_invidSendCommand(Local_u8ADDRAM_Address|LCD_SET_CURSOR_LOCATION);
		Local_enuErrorState = ES_OK;



	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuDisplayNumber(s16 Copy_s16Number)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_s16Number == 0)
	{
		LCD_enuDisplayChar('0');
	}
	else
	{
		if(Copy_s16Number<0)
		{
			Copy_s16Number*=-1;
			LCD_enuDisplayChar('-');

		}

		s16 temp = 0;
		while(Copy_s16Number!=0)
		{
			// number = 53613

			temp = Copy_s16Number%10 + temp*10 ;
			Copy_s16Number/=10;

		}

		while(temp!=0)
		{
			LCD_enuDisplayChar((temp%10)+'0');
			temp/=10;
		}
	}

	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuClear()
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	LCD_invidSendCommand(LCD_CLEAR_SCREEN);
	Local_enuErrorState = ES_OK;

	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuDisplayStringRowCol(u8 Copy_u8Row , u8 Copy_u8Col , const char* Copy_pu8String )
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	LCD_enuGoToRowCol(Copy_u8Row , Copy_u8Col);

	LCD_enuDisplayString(Copy_pu8String);

	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuCreateCharacter(u8 *Copy_pu8Pattern , u8 Copy_u8Address)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8Iterator = 0 ;

	LCD_invidSendCommand(LCD_SET_CGRAM_LOCATION|(Copy_u8Address*8));

	for(Local_u8Iterator=0 ; Local_u8Iterator<8 ;Local_u8Iterator++)
	{
		LCD_enuDisplayChar(Copy_pu8Pattern[Local_u8Iterator]);
	}


	//0x40 --> 0b 0100 0000
	//            0111 1111

	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuDisplayBinary(u16 Copy_u16Number)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;

	// 00010 1011

	if(Copy_u16Number == 0 || Copy_u16Number == 1)
	{
		LCD_enuDisplayNumber(Copy_u16Number);
	}
	else
	{
		s8 Local_u8Iterator = 0;
		u8 Local_u8Flag = 0;
		for(Local_u8Iterator=7 ; Local_u8Iterator>=0 ; Local_u8Iterator--)
		{
			if(((Copy_u16Number>>Local_u8Iterator)&1)==1)
			{
				Local_u8Flag=1;
			}

			if(Local_u8Flag==1)
			{
				LCD_enuDisplayNumber((Copy_u16Number>>Local_u8Iterator)&1);
			}

		}
	}


	/*Then return error state variable*/
	return Local_enuErrorState;
}

ES_t LCD_enuDisplayNumber_4Digit(u16 Copy_u16Number)
{
	/*At first set the error state variable by "NOT OK" state*/
	ES_t Local_enuErrorState = ES_NOK;
	// 2514

	LCD_enuDisplayNumber(Copy_u16Number/10000);

	LCD_enuDisplayNumber((Copy_u16Number%1000)/100);

	LCD_enuDisplayNumber((Copy_u16Number%100)/10);

	LCD_enuDisplayNumber((Copy_u16Number%10));


	/*Then return error state variable*/
	return Local_enuErrorState;
}






