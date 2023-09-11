/*
 * TWI_int.h
 *
 *  Created on: Jul 19, 2023
 *      Author: REZK
 */

#ifndef TWI_INT_H_
#define TWI_INT_H_

ES_t TWI_enuInitMaster(void);

ES_t TWI_enuInitSlave(void);

ES_t TWI_enuMasterSendStartCondition(void);

ES_t TWI_enuSendReapeatedStart(void);

ES_t TWI_enuSendSlaveAddressWithWriteReq(u8 Copy_u8SlaveAddress);

ES_t TWI_enuSendSlaveAddressWithReadReq(u8 Copy_u8SlaveAddress);

ES_t TWI_enuMasterWriteDataByte(u8 Copy_u8Data);

ES_t TWI_enuMasterReadDataByte(u8* Copy_pu8Data);

ES_t TWI_enuMasterSendStopCondition(void);

#endif /* TWI_INT_H_ */


