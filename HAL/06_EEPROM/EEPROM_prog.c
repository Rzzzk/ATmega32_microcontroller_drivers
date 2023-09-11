/*
 * EEPROM_prog.c
 *
 *  Created on: Sep 7, 2023
 *      Author: REZK
 */


#include "stdTypes.h"
#include "commonMacros.h"
#include "errorStates.h"

#include "TWI_int.h"

#include "EEPROM_int.h"
#include "EEPROM_config.h"
#include "EEPROM_priv.h"


ES_t EEPROM_enuWriteDataByte(u8 Copy_u8Data  , u16 Copy_u16Address)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 SalveAddr;

#if EEPROM_TYPE == EEPROM_24C08_
	SalveAddr=(((0b01010<<3) |EEPROM_PIN_A2_CON | (Copy_u16Address & 0x0300)>>8)) ;

#elif EEPROM_TYPE == EEPROM_24C16_
	SalveAddr= (u8)((0b01010000)|(Copy_u16Address & 0x0700)>>8) ;
#endif

	TWI_enuMasterSendStartCondition();

	TWI_enuSendSlaveAddressWithWriteReq(SalveAddr);

	TWI_enuMasterWriteDataByte((u8)Copy_u16Address);

	TWI_enuMasterWriteDataByte(Copy_u8Data);

	TWI_enuMasterSendStopCondition();

	return Local_enuErrorState;
}


ES_t EEPROM_enuReadDataByte(u8 *Copy_pu8Data , u16 Copy_u16Address)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 SalveAddr;

#if EEPROM_TYPE == EEPROM_24C08_
	SalveAddr=(((0b01010<<3) |EEPROM_PIN_A2_CON | (Copy_u16Address & 0x0300)>>8)) ;

#elif EEPROM_TYPE == EEPROM_24C16_
	SalveAddr= (u8)((0b01010000)|(Copy_u16Address & 0x0700)>>8) ;
#endif

	TWI_enuMasterSendStartCondition();

	TWI_enuSendSlaveAddressWithWriteReq(SalveAddr);

	TWI_enuMasterWriteDataByte((u8)Copy_u16Address);

	TWI_enuSendReapeatedStart();

	TWI_enuSendSlaveAddressWithReadReq(SalveAddr);

	TWI_enuMasterReadDataByte(Copy_pu8Data);

	TWI_enuMasterSendStopCondition();

	return Local_enuErrorState;
}
