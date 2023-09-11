/*
 * Keypad_prog.c
 *
 *  Created on: Feb 19, 2023
 *      Author: REZK
 */

#include "stdTypes.h"
#include "errorStates.h"

#include "Keypad_config.h"
#include "Keypad_priv.h"
#include "DIO_int.h"

extern const u8 KEYPAD_Au8KeysConfig[KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM];

ES_t KEYPAD_enuInit()
{
	ES_t Local_enuErrorState =ES_NOK;

	DIO_enuSetPinDirection(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN,DIO_u8PIN_INPUT);
	DIO_enuSetPinValue(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN,DIO_u8PIN_FLOAT);

	DIO_enuSetPinDirection(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN,DIO_u8PIN_INPUT);
	DIO_enuSetPinValue(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN,DIO_u8PIN_FLOAT);

	DIO_enuSetPinDirection(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN,DIO_u8PIN_INPUT);
	DIO_enuSetPinValue(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN,DIO_u8PIN_FLOAT);

#if KEYPAD_ROWS_NUM == FOUR_ROWS
	DIO_enuSetPinDirection(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN,DIO_u8PIN_INPUT);
	DIO_enuSetPinValue(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN,DIO_u8PIN_FLOAT);
#endif

	DIO_enuSetPinDirection(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN,DIO_u8PIN_INPUT);
	DIO_enuSetPinValue(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN,DIO_u8PIN_PULL_UP);

	DIO_enuSetPinDirection(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN,DIO_u8PIN_INPUT);
	DIO_enuSetPinValue(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN,DIO_u8PIN_PULL_UP);

	DIO_enuSetPinDirection(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN,DIO_u8PIN_INPUT);
	DIO_enuSetPinValue(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN,DIO_u8PIN_PULL_UP);

#if KEYPAD_COLS_NUM == FOUR_COLS
	DIO_enuSetPinDirection(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN,DIO_u8PIN_INPUT);
	DIO_enuSetPinValue(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN,DIO_u8PIN_PULL_UP);
#endif

	return Local_enuErrorState;
}

ES_t KEYPAD_enuGetPressadKey(u8 * Copy_pu8PressedKey)
{
	ES_t Local_enuErrorState =ES_NOK;


	u8 Local_u8Row = 0 , Local_u8Col = 0 , Local_u8State ;
	*Copy_pu8PressedKey = KEYPAD_KEY_DEFAULT_VAL;

	for(Local_u8Row=0 ; Local_u8Row < KEYPAD_ROWS_NUM ; Local_u8Row++)
	{
		switch(Local_u8Row)
		{
		case 0:
			DIO_enuSetPinDirection(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN,DIO_u8PIN_OUTPUT);
			DIO_enuSetPinValue(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN,DIO_u8PIN_LOW);
			break;
		case 1:
			DIO_enuSetPinDirection(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN,DIO_u8PIN_OUTPUT);
			DIO_enuSetPinValue(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN,DIO_u8PIN_LOW);
			break;
		case 2:
			DIO_enuSetPinDirection(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN,DIO_u8PIN_OUTPUT);
			DIO_enuSetPinValue(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN,DIO_u8PIN_LOW);
			break;
		case 3:
			DIO_enuSetPinDirection(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN,DIO_u8PIN_OUTPUT);
			DIO_enuSetPinValue(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN,DIO_u8PIN_LOW);
			break;
		}

		for(Local_u8Col=0 ; Local_u8Col < KEYPAD_COLS_NUM ; Local_u8Col++)
		{
			switch(Local_u8Col)
			{
			case 0:
				DIO_enuGetPinValue(KEYPAD_COL0_PORT,KEYPAD_COL0_PIN,&Local_u8State);
				if(Local_u8State==0)
				{
					*Copy_pu8PressedKey = KEYPAD_Au8KeysConfig[Local_u8Row][Local_u8Col];
					while(Local_u8State==0)
					{
						DIO_enuGetPinValue(KEYPAD_COL0_PORT,KEYPAD_COL0_PIN,&Local_u8State);
					}
				}
				break;
			case 1:
				DIO_enuGetPinValue(KEYPAD_COL1_PORT,KEYPAD_COL1_PIN,&Local_u8State);
				if(Local_u8State==0)
				{
					*Copy_pu8PressedKey = KEYPAD_Au8KeysConfig[Local_u8Row][Local_u8Col];
					while(Local_u8State==0)
					{
						DIO_enuGetPinValue(KEYPAD_COL1_PORT,KEYPAD_COL1_PIN,&Local_u8State);
					}
				}
				break;
			case 2:
				DIO_enuGetPinValue(KEYPAD_COL2_PORT,KEYPAD_COL2_PIN,&Local_u8State);
				if(Local_u8State==0)
				{
					*Copy_pu8PressedKey = KEYPAD_Au8KeysConfig[Local_u8Row][Local_u8Col];
					while(Local_u8State==0)
					{
						DIO_enuGetPinValue(KEYPAD_COL2_PORT,KEYPAD_COL2_PIN,&Local_u8State);
					}
				}
				break;
			case 3:
				DIO_enuGetPinValue(KEYPAD_COL3_PORT,KEYPAD_COL3_PIN,&Local_u8State);
				if(Local_u8State==0)
				{
					*Copy_pu8PressedKey = KEYPAD_Au8KeysConfig[Local_u8Row][Local_u8Col];
					while(Local_u8State==0)
					{
						DIO_enuGetPinValue(KEYPAD_COL3_PORT,KEYPAD_COL3_PIN,&Local_u8State);
					}
				}
				break;
			}


		}//end of for(col)


		switch(Local_u8Row)
		{
		case 0:
			DIO_enuSetPinDirection(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN,DIO_u8PIN_INPUT);
			DIO_enuSetPinValue(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN,DIO_u8PIN_FLOAT);
			break;
		case 1:
			DIO_enuSetPinDirection(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN,DIO_u8PIN_INPUT);
			DIO_enuSetPinValue(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN,DIO_u8PIN_FLOAT);
			break;
		case 2:
			DIO_enuSetPinDirection(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN,DIO_u8PIN_INPUT);
			DIO_enuSetPinValue(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN,DIO_u8PIN_FLOAT);
			break;
		case 3:
			DIO_enuSetPinDirection(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN,DIO_u8PIN_INPUT);
			DIO_enuSetPinValue(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN,DIO_u8PIN_FLOAT);
			break;
		}

	}//end of for(row)




	return Local_enuErrorState;
}
