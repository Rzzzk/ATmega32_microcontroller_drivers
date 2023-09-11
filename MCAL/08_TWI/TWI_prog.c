/*
 * TWI_prog.c
 *
 *  Created on: Jul 19, 2023
 *      Author: REZK
 */
#include "stdTypes.h"
#include "commonMacros.h"
#include "errorStates.h"

#include "TWI_int.h"
#include "TWI_config.h"
#include "TWI_priv.h"

ES_t TWI_enuInitMaster(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	TWBR = 0x02;
	TWSR = 0x00;

	TWAR = TWI_MC_ADDRESS<<1;
	TWCR = (1<<TWEN);

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t TWI_enuInitSlave(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	TWAR = TWI_MC_ADDRESS<<1;
	/*Enable TWI peripheral*/
	TWCR = (1<<TWEN);

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}



ES_t TWI_enuMasterSendStartCondition(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Send start condition*/
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/*wait until the flag set again*/
	while((GET_BIT(TWCR,TWINT))==0);

	/*Read the status register*/
	if((TWSR&0xf8) == TWI_SATRT_COND_TRANSMIT)
	{
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_TWI_START_COND_ERROR;
		//CLEAR_BIT(TWCR,TWSTA); //clear start condition bit
	}

	return Local_enuErrorState;
}

ES_t TWI_enuSendReapeatedStart(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Send start condition*/
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/*wait until the flag set again*/
	while((GET_BIT(TWCR,TWINT))==0);

	/*Read the status register*/
	if((TWSR&0xf8) == TWI_REP_START_TRANSMIT)
	{
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_TWI_REP_START_COND_ERROR;
		//CLEAR_BIT(TWCR,TWSTA);//clear start condition bit
	}

	return Local_enuErrorState;
}

ES_t TWI_enuSendSlaveAddressWithWriteReq(u8 Copy_u8SlaveAddress)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*set the slave address in msb in the data register and clear the bit0*/
	TWDR = (u8)(Copy_u8SlaveAddress<<1) ;


	/*Clear the TWI flag to do the operation*/
	TWCR = (1 << TWINT) | (1 << TWEN);

	/*wait until the flag set again*/
	while((GET_BIT(TWCR,TWINT))==0);

	/*Read the status register*/
	if((TWSR&0xf8) == SLAVE_ADDR_AND_WRITE)
	{
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_TWI_SLAVE_ADD_WRITE_ERROR;
	}

	return Local_enuErrorState;
}

ES_t TWI_enuSendSlaveAddressWithReadReq(u8 Copy_u8SlaveAddress)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*set the slave address in msb in the data register and set the bit0*/
	TWDR = (u8)((Copy_u8SlaveAddress<<1) |1);


	/*Clear the TWI flag to do the operation*/
	TWCR = (1 << TWINT) | (1 << TWEN);

	/*wait until the flag set again*/
	while((GET_BIT(TWCR,TWINT))==0);

	/*Read the status register*/
	if(( TWSR&0xf8) == SLAVE_ADDR_AND_READ)
	{
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_TWI_SLAVE_ADD_READ_ERROR;
	}

	return Local_enuErrorState;
}

ES_t TWI_enuMasterWriteDataByte(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Write the data in data register*/
	TWDR = Copy_u8Data;

	/*Clear the TWI flag to do the operation*/
	TWCR = (1 << TWINT) | (1 << TWEN);

	/*wait until the flag set again*/
	while((GET_BIT(TWCR,TWINT))==0);

	/*Read the status register*/
	if((TWSR&0xf8) == MASTER_TRANSMIT_DATA)
	{
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_TWI_MASTER_WRITE_DATA_BYTE_ERROR;
	}


	return Local_enuErrorState;
}

ES_t TWI_enuMasterReadDataByte(u8* Copy_pu8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Clear the TWI flag to let the slave sending the data*/
	TWCR = (1 << TWINT) | (1 << TWEN);

	/*wait until the flag set again*/
	while((GET_BIT(TWCR,TWINT))==0);

	*Copy_pu8Data = TWDR;

	/*Read the status register*/
	if((TWSR&0xf8) == MASTER_RECEIVED_DATA_WITH_ACK)
	{
		/*Read received data*/
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_TWI_MASTER_READ_DATA_BYTE_ERROR;
	}


	return Local_enuErrorState;
}

ES_t TWI_enuMasterSendStopCondition(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set stop condition bit*/
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

	/*Clear the TWI flag to send the stop condition*/
	SET_BIT(TWCR,TWINT);

	return Local_enuErrorState;
}









