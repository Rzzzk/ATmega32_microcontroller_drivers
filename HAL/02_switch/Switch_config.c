/*
 * Switch_config.c
 *
 *  Created on: Feb 12, 2023
 *      Author: REZK
 */

#include"errorStates.h"
#include"stdTypes.h"

#include"DIO_int.h"

#include"Switch_int.h"
#include"Switch_config.h"

/*

 Options :

    potrID : DIO_u8PORTA or DIO_u8PORTB or DIO_u8PORTC or DIO_u8PORTD
    pinID  : DIO_u8PINn (n = 1 : 7)
    state  : DIO_u8PIN_PULL_UP or DIO_u8PIN_FLOAT

 */

SW_t Switch_AstrSwitchstate[SW_NUM]={
		{DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_PULL_UP},
		{DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_PULL_UP},
		{DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_PULL_UP}
};

