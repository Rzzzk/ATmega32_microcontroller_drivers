/*
 * SPI_cofig.c
 *
 *  Created on: Apr 29, 2023
 *      Author: REZK
 */


#include "stdTypes.h"
#include "errorStates.h"
#include "commonMacros.h"

#include "SPI_int.h"


/*configuration structure for initial function*/

/*Frame configuration for master*/
SPI_Master_t SPI_strMasterConfig =
{
		LSB_SendFirst,
		SCK_IdleStateIsLow,
		CPHA_SampOnleadingSetOntrailing,
		SCALER_16

};

/*Frame configuration for slave*/
SPI_Slave_t SPI_strSlaveConfig =
{
		LSB_SendFirst,
		SCK_IdleStateIsLow,
		CPHA_SampOnleadingSetOntrailing,

};
