/*
 * LED_config.c
 *
 *  Created on: Feb 12, 2023
 *      Author: REZK
 */

#include"stdTypes.h"
#include"errorStates.h"

#include"DIO_int.h"

#include"LED_int.h"
#include"LED_config.h"
#include"LED_priv.h"


/*

 Options :

    potrID : DIO_u8PORTA or DIO_u8PORTB or DIO_u8PORTC or DIO_u8PORTD
    pinID  : DIO_u8PINn (n = 1 : 7)
    state  : LED_ON or LED_OFF
	connection : LED_SINK or LED_SOURCE
 */

LED_t LED_AstrLedConfig[LED_NUM]=
{
		{DIO_u8PORTB,DIO_u8PIN1,LED_SINK  ,LED_ON},
		{DIO_u8PORTB,DIO_u8PIN2,LED_SINK  ,LED_ON},
		{DIO_u8PORTB,DIO_u8PIN4,LED_SOURCE,LED_ON}
};
