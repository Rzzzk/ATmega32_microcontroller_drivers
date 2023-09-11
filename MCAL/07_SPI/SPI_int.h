/*
 * SPI_int.h
 *
 *  Created on: Apr 29, 2023
 *      Author: REZK
 */

#ifndef SPI_INT_H_
#define SPI_INT_H_
typedef enum
{
	LSB_SendFirst, //LSB of the data word is transmitted first
	MSB_SendFirst //LSB of the data word is transmitted first

}SPI_DataOrder_t;


typedef enum
{
	SCK_IdleStateIsLow,
	SCK_IdleStateIsHigh

}SPI_ClockPolarity_t;

typedef enum
{
	CPHA_SampOnleadingSetOntrailing,
	CPHA_SetOnleadingSampOntrailing

}SPI_ClockPhase_t;


typedef enum
{
	SCALER_4,
	SCALER_16,
	SCALER_64,
	SCALER_128,
	SCALER_2,
	SCALER_8,
	SCALER_32,

}SPI_Prescaler_t;


typedef struct
{
	SPI_DataOrder_t       SPI_enuDataOrder;
	SPI_ClockPolarity_t   SPI_enuClockPolarity;
	SPI_ClockPhase_t      SPI_enuClockPhase;
	SPI_Prescaler_t       SPI_enuPrescaler;
}SPI_Master_t;


typedef struct
{
	SPI_DataOrder_t       SPI_enuDataOrder;
	SPI_ClockPolarity_t   SPI_enuClockPolarity;
	SPI_ClockPhase_t      SPI_enuClockPhase;

}SPI_Slave_t;

ES_t SPI_enuInitMaster(SPI_Master_t* Copy_pstrMasterConfig);
ES_t SPI_enuInitSlave(SPI_Slave_t* Copy_pstrSlaveConfig);

ES_t SPI_enuTransceive(u8 Copy_u8TransmittedData , u8* Copy_pu8ReceivedData);

#endif /* SPI_INT_H_ */
