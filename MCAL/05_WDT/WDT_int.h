/*
 * WDT_int.h
 *
 *  Created on: May 23, 2023
 *      Author: REZK
 */

#ifndef WDT_INT_H_
#define WDT_INT_H_


typedef enum
{
	WDT_enuSleepTime_16300us,
	WDT_enuSleepTime_32500us,
	WDT_enuSleepTime_65ms,
	WDT_enuSleepTime_130ms,
	WDT_enuSleepTime_260ms,
	WDT_enuSleepTime_520ms,
	WDT_enuSleepTime_1000ms,
	WDT_enuSleepTime_2100ms,

}WDT_SleepTime_t;

ES_t WDT_enuEnable();

ES_t WDT_enuDisable();

ES_t WDT_enuSleep(WDT_SleepTime_t Copy_enuWDTSleepTime);




#endif /* WDT_INT_H_ */
