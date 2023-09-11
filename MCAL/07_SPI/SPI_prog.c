/*
 * SPI_prog.c
 *
 *  Created on: Apr 29, 2023
 *      Author: REZK
 */


#include "stdTypes.h"
#include "errorStates.h"
#include "commonMacros.h"


#include "SPI_int.h"
#include "SPI_priv.h"

ES_t SPI_enuBusyState = ES_FUNC_IS_IDLE;

ES_t SPI_enuInitMaster(SPI_Master_t* Copy_pstrMasterConfig)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Master selection*/
	SET_BIT(SPCR,MSTR);

	/*set data order*/
	switch(Copy_pstrMasterConfig->SPI_enuDataOrder)
	{
	case LSB_SendFirst:
		SET_BIT(SPCR,DORD);
		break;
	case MSB_SendFirst:
		CLEAR_BIT(SPCR,DORD);
		break;
	}

	/*set clock polarity*/
	switch(Copy_pstrMasterConfig->SPI_enuClockPolarity)
	{
	case SCK_IdleStateIsLow:
		CLEAR_BIT(SPCR,CPOL);
		break;
	case SCK_IdleStateIsHigh:
		SET_BIT(SPCR,CPOL);
		break;
	}

	/*set clock phase*/
	switch(Copy_pstrMasterConfig->SPI_enuClockPhase)
	{
	case CPHA_SampOnleadingSetOntrailing:
		CLEAR_BIT(SPCR,CPHA);
		break;
	case CPHA_SetOnleadingSampOntrailing:
		SET_BIT(SPCR,CPHA);
		break;
	}

	/*set prescaler*/
	switch(Copy_pstrMasterConfig->SPI_enuPrescaler)
	{
	case SCALER_4:
		CLEAR_BIT(SPCR,SPR0);
		CLEAR_BIT(SPCR,SPR1);
		CLEAR_BIT(SPSR,SPI2X);
		break;
	case SCALER_16:
		SET_BIT(SPCR,SPR0);
		CLEAR_BIT(SPCR,SPR1);
		CLEAR_BIT(SPSR,SPI2X);
		break;
	case SCALER_64:
		CLEAR_BIT(SPCR,SPR0);
		SET_BIT(SPCR,SPR1);
		CLEAR_BIT(SPSR,SPI2X);
		break;
	case SCALER_128:
		SET_BIT(SPCR,SPR0);
		SET_BIT(SPCR,SPR1);
		CLEAR_BIT(SPSR,SPI2X);
		break;
	case SCALER_2:
		CLEAR_BIT(SPCR,SPR0);
		CLEAR_BIT(SPCR,SPR1);
		SET_BIT(SPSR,SPI2X);
		break;
	case SCALER_8:
		SET_BIT(SPCR,SPR0);
		CLEAR_BIT(SPCR,SPR1);
		SET_BIT(SPSR,SPI2X);
		break;
	case SCALER_32:
		CLEAR_BIT(SPCR,SPR0);
		SET_BIT(SPCR,SPR1);
		SET_BIT(SPSR,SPI2X);
		break;
	}


	/*PSI enable*/
	SET_BIT(SPCR,SPE);

	return Local_enuErrorState;

}


ES_t SPI_enuInitSlave(SPI_Slave_t* Copy_pstrSlaveConfig)
{

	ES_t Local_enuErrorState = ES_NOK;

	/*Slave selection*/
	CLEAR_BIT(SPCR,MSTR);

	/*set data order*/
	switch(Copy_pstrSlaveConfig->SPI_enuDataOrder)
	{
	case LSB_SendFirst:
		SET_BIT(SPCR,DORD);
		break;
	case MSB_SendFirst:
		CLEAR_BIT(SPCR,DORD);
		break;
	}

	/*set clock polarity*/
	switch(Copy_pstrSlaveConfig->SPI_enuClockPolarity)
	{
	case SCK_IdleStateIsLow:
		CLEAR_BIT(SPCR,CPOL);
		break;
	case SCK_IdleStateIsHigh:
		SET_BIT(SPCR,CPOL);
		break;
	}

	/*set clock phase*/
	switch(Copy_pstrSlaveConfig->SPI_enuClockPhase)
	{
	case CPHA_SampOnleadingSetOntrailing:
		CLEAR_BIT(SPCR,CPHA);
		break;
	case CPHA_SetOnleadingSampOntrailing:
		SET_BIT(SPCR,CPHA);
		break;
	}


	/*PSI enable*/
	SET_BIT(SPCR,SPE);
	return Local_enuErrorState;

}




/*Synchronous function*/
ES_t SPI_enuTransceive(u8 Copy_u8TransmittedData , u8* Copy_pu8ReceivedData)
{

	ES_t Local_enuErrorState = ES_NOK;

	if(SPI_enuBusyState == ES_FUNC_IS_BUSY)
	{
		Local_enuErrorState = ES_FUNC_IS_BUSY;
	}
	else if(Copy_pu8ReceivedData ==NULL)
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}
	else
	{
		SPI_enuBusyState = ES_FUNC_IS_BUSY;

		/*write data on data register*/
		SPDR = Copy_u8TransmittedData;

		/*wait until communication complete*/
		while(READ_BIT(SPSR,SPIF)==0);

		/*read the received data*/
		*Copy_pu8ReceivedData = SPDR;
		
		Local_enuErrorState = ES_OK;

		SPI_enuBusyState = ES_FUNC_IS_IDLE;
	}

	return Local_enuErrorState;

}
