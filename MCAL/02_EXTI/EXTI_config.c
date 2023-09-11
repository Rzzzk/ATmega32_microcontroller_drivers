/*
 * EXTI_config.c
 *
 *  Created on: Mar 22, 2023
 *      Author: REZK
 */

#include "errorStates.h"
#include "stdTypes.h"
#include "EXTI_int.h"


EXTI_t EXTI_AstrEXTIConfig[3]=
{
		{EXTI_enuINT0,EXTI_enuActive ,EXTI_enuRisingEdge },
		{EXTI_enuINT1,EXTI_enuActive ,EXTI_enuRisingEdge },
		{EXTI_enuINT2,EXTI_enuActive ,EXTI_enuRisingEdge }
};
