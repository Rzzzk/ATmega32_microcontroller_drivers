/*
 * ADC_int.h
 *
 *  Created on: Apr 24, 2023
 *      Author: REZK
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_

typedef enum
{
	VREF_AVCC,
	VREF_AREF,
	VREF_256

}ADC_VoltRef_t;

typedef enum
{
	SCALER_2=1,
	SCALER_4,
	SCALER_8,
	SCALER_16,
	SCALER_32,
	SCALER_64,
	SCALER_128,

}ADC_Prescaler_t;

typedef enum
{
	channel0=0,
	channel1,
	channel2,
	channel3,
	channel4,
	channel5,
	channel6,
	channel7
}ADC_Channel_t;

typedef struct
{
	ADC_VoltRef_t ADC_enuVoltRef;
	ADC_Prescaler_t ADC_enuPrescaler;

}ADC_t;

typedef struct
{
	ADC_Channel_t Chain_FirstChannel;
	ADC_Channel_t Chain_LastChannel;
	u16 *Chain_ResultArr;
	void (*Chain_CallBackNotification)(void);

}ADC_Chain_t;



ES_t ADC_enuInit(ADC_t *Copy_strADCConcfig);

/*******************************/
/* use it for critical ADC job */
/*******************************/
ES_t ADC_enuStartConversionSynch(ADC_Channel_t Copy_enuChannel , u16* Copy_pu16ADCReading , u16 Copy_u16Timeout);

/********************************/
/* use it for long time ADC job */
/********************************/
ES_t ADC_enuStartConversionAsynch(ADC_Channel_t Copy_enuChannel , u16* Copy_pu16ADCReading , void(*Copy_pfNotification)(void));


ES_t ADC_enuStartChainConversion(ADC_Chain_t *Copy_pstrChain );


#endif /* ADC_INT_H_ */
