/*
 * GIE_prog.c
 *
 *  Created on: May 10, 2023
 *      Author: REZK
 */
#include "stdTypes.h"
#include "errorStates.h"
#include "commonMacros.h"
#include "GIE_int.h"
#include "GIE_priv.h"


ES_t GIE_enuEnable()
{
	ES_t Local_enuErrorstate = ES_NOK;

	SET_BIT(SREG,I);
	Local_enuErrorstate = ES_OK;

	return Local_enuErrorstate;
}

ES_t GIE_enuDisable()
{
	ES_t Local_enuErrorstate = ES_NOK;

	CLEAR_BIT(SREG,I);
	Local_enuErrorstate = ES_OK;

	return Local_enuErrorstate;
}
