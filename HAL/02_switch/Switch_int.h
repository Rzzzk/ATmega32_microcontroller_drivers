/*
 * Switch_int.h
 *
 *  Created on: Feb 12, 2023
 *      Author: REZK
 */

#ifndef SWITCH_INT_H_
#define SWITCH_INT_H_

typedef struct
{
	u8 SW_PortID;
	u8 SW_PinID;
	u8 SW_Status;

}SW_t;

ES_t Switch_enuInit(SW_t* Copy_AstrSwitchs);


ES_t Switch_enuGetState(SW_t* Copy_AstrSwitchs,u8* Copy_pu8SwchState);



#endif /* SWITCH_INT_H_ */
