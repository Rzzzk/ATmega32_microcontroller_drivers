/*
 * EXTI_interface.h
 *
 *  Created on: Jul 27, 2023
 *      Author: REZK
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_


/* ID data type */
typedef enum
{
	EXTI_enuINT0,
	EXTI_enuINT1,
	EXTI_enuINT2
}EXI_ID_t;

/* State data type */
typedef enum
{
	EXTI_enuActive,
	EXTI_enuDeActive
}EXTI_State_t;

/* Since level  data type */
typedef enum
{
	EXTI_enuLowLevel,
	EXTI_enuAnyLogicalChange,
	EXTI_enuFallingEdge,
	EXTI_enuRisingEdge
}EXTI_SenceLevel_t;

/*EXTI data type*/
typedef struct
{
	EXI_ID_t EXTI_enuID;
	EXTI_State_t EXTI_enuState;
	EXTI_SenceLevel_t EXTI_enuSenceLevel;

}EXTI_t;


ES_t EXTI_enuInit(EXTI_t* Copy_pstrEXTIConfig);

ES_t EXTI_enuSetSenceMode(EXI_ID_t Copy_enuEXTI_ID , EXTI_SenceLevel_t Copy_enuSenceLevel);

ES_t EXTI_enuEnable(EXI_ID_t Copy_enuEXTI_ID);

ES_t EXTI_enuDisable(EXI_ID_t Copy_enuEXTI_ID);

ES_t EXTI_enuCallBack(EXI_ID_t Copy_enuEXTI_ID , void(*Copy_pfunEXTI_fun)(void));



#endif /* EXTI_INT_H_ */
