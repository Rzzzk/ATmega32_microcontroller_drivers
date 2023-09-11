/*
 * ADC_config.c
 *
 *  Created on: Jul 27, 2023
 *      Author: REZK
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "commonMacros.h"


#include "ADC_int.h"

ADC_t ADC_strConfig =
{
		VREF_AVCC,
		SCALER_64
};
