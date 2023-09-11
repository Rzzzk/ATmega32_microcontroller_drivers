/*
 * LED_int.h
 *
 *  Created on: Feb 12, 2023
 *      Author: REZK
 */

#ifndef LED_INT_H_
#define LED_INT_H_

typedef struct
{
	u8 LED_u8PortID;
	u8 LED_u8PinID;
	u8 LED_u8Connection;
	u8 LED_u8InitState;

}LED_t;

ES_t LED_enuInit(LED_t *Copy_pstrLedConfig);

ES_t LED_enuIurnON(LED_t *Copy_pstrLedConfig);

ES_t LED_enuIurnOFF(LED_t *Copy_pstrLedConfig);


#endif /* LED_INT_H_ */
