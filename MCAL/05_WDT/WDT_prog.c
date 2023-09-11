/*
 * WDT_prog.c
 *
 *  Created on: May 23, 2023
 *      Author: REZK
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "commonMacros.h"

#include "WDT_int.h"
#include "WDT_priv.h"



ES_t WDT_enuEnable()
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Enable the watch dog timer*/
	SET_BIT(WDTCR,WDE);

	return Local_enuErrorState;
}

ES_t WDT_enuDisable()
{
	ES_t Local_enuErrorState = ES_NOK;

	/*At the same operation write one in  bits (WDE and WDTOE) */
	WDTCR |= 0b00011000 ;

	/*within the next 4 clocks write 0 in WDE bit*/
	/*write 0 in all register because i don't care about the other sittings while disabling*/
	WDTCR = 0;

	return Local_enuErrorState;
}

ES_t WDT_enuSleep(WDT_SleepTime_t Copy_enuWDTSleepTime)
{
	ES_t Local_enuErrorState = ES_NOK;

	if((Copy_enuWDTSleepTime >= WDT_enuSleepTime_16300us) && (Copy_enuWDTSleepTime <= WDT_enuSleepTime_2100ms))
	{
		WDTCR &= 0xf8; // 0b 1111 1000
		WDTCR |= Copy_enuWDTSleepTime;
		Local_enuErrorState =ES_OK;
	}

	return Local_enuErrorState;
}
