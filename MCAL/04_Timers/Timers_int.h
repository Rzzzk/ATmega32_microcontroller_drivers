/*
 * Timers_int.h
 *
 *  Created on: Mar 24, 2023
 *      Author: REZK
 */

#ifndef TIMERS_INT_H_
#define TIMERS_INT_H_


typedef enum
{
	Timer0_enuOverflow,
	Timer0_enuCTC,
	Timer0_enuFastPWM,
	Timer0_enuPhaseCorrectPWM,
	Timer1_enuOverflow,
	Timer1_enuCTC,
	Timer1_enuFastPWM_TopICR1,

}TIMERS_Mode_t;


typedef enum
{
	Disconnect,
	ToggleOnCompare,
	ClearOnCompare,
	SetOnCompare,
	PWM_NonInverted, //OC0_Clear on CTC set at top //Fast PWM  // phase correct OC0_clear on CTC when count up set on CTC when count down
	PWM_Inverted,    //OC0_set on CTC clear at top //Fast PWM //phase correct OC0_set on CTC when count up clear on CTC when count down

}TIMERS_OutputPinAction_t;


typedef enum
{
	TIMERS_enuNoClockSource,
	TIMERS_enuNoPrescaling,
	TIMERS_enuPrescalingBy8,
	TIMERS_enuPrescalingBy64,
	TIMERS_enuPrescalingBy256,
	TIMERS_enuPrescalingBy1024,

}TIMERS_prescaler_t;


/***************************************************/
/*                     TIMER0                      */
/***************************************************/


typedef struct
{
	TIMERS_Mode_t Timer0_enuMode;
	TIMERS_OutputPinAction_t Timer0_enuOC0Action;
	TIMERS_prescaler_t Timer0_enuPrescaler;
	unsigned char Timer0_u8Counter;
	unsigned char Timer0_u8CompareMatchValue;

}Timer0_t;



ES_t Timer0_enuInit(Timer0_t *Copy_strTimer0);

ES_t Timer0_enuSetMode(TIMERS_Mode_t Copy_enuTimer0Mode);

ES_t Timer0_enuSetPrescaler(TIMERS_prescaler_t Copy_enuTimer0Prescaler);

ES_t Timer0_enuSetCounter(u8 Copy_u8Counter);

ES_t Timer0_enuGetCounter(u8 *Copy_u8Counter);

ES_t Timer0_enuSetCmpareMatch(u8 Copy_u8CompareMatchValue);

ES_t Timer0_enuSetOC0Action(TIMERS_OutputPinAction_t Copy_enuTime0OC0Act);

ES_t Timer0_enuOverFlowINT_Enable();

ES_t Timer0_enuOverFlowINT_Disable();

ES_t Timer0_enuCTC_INT_Enable();

ES_t Timer0_enuCTC_INT_Disable();

ES_t Timer0_enuCallBack(TIMERS_Mode_t Copy_enuTimer0Mode , void(*Copy_pfunTimer0func)(void));

/***************************************************/
/*                     TIMER1                      */
/***************************************************/


typedef struct
{
	TIMERS_Mode_t Timer1_enuMode;
	TIMERS_OutputPinAction_t Timer1_enuOC1A_Action;
	TIMERS_OutputPinAction_t Timer1_enuOC1B_Action;
	TIMERS_prescaler_t Timer1_enuPrescaler;
	unsigned short Timer1_u16Counter;
	unsigned short Timer1_u16Comparematch_A_Value;
	unsigned short Timer1_u16Comparematch_B_Value;
	unsigned short Timer1_u16InputCapRegValue;

}Timer1_t;


ES_t Timer1_enuInit(Timer1_t *Copy_strTimer1Config);

ES_t Timer1_enuSetMode(TIMERS_Mode_t Copy_enuTimer1Mode);

ES_t Timer1_enuSetPrescaler(TIMERS_prescaler_t Copy_enuTimer1Prescaler);



/*the action of output pin*/
ES_t Timer1_enuSet_OC1A_Action(TIMERS_OutputPinAction_t Copy_enuTime1OC1AAct);

ES_t Timer1_enuSet_OC1B_Action(TIMERS_OutputPinAction_t Copy_enuTime1OC1BAct);


/*Set/Get counter values*/
ES_t Timer1_enuSetCounter(u16 Copy_u16Counter);

ES_t Timer1_enuGetCounter(u16 *Copy_u16Counter);

/*Set compare match values*/
ES_t Timer1_enuSetCmpareMatchRegA(u16 Copy_u16CompareMatchValue);

ES_t Timer1_enuSetCmpareMatchRegB(u16 Copy_u16CompareMatchValue);

ES_t Timer1_enuSetInputCapReg(u16 Copy_u16InputCapRegValue);


/*Peripheral interrupt enable/disable*/
ES_t Timer1_enuOverFlowINT_Enable();

ES_t Timer1_enuOverFlowINT_Disable();

ES_t Timer1_enuCTCA_INT_Enable();

ES_t Timer1_enuCTCA_INT_Disable();

ES_t Timer1_enuCTCB_INT_Enable();

ES_t Timer1_enuCTCB_INT_Disable();


/*callback functions*/

ES_t Timer1_enuCallBackOVF(void(*Copy_pfunTimer1func)(void));

ES_t Timer1_enuCallBackCTCA(void(*Copy_pfunTimer1func)(void));

ES_t Timer1_enuCallBackCTCB(void(*Copy_pfunTimer1func)(void));

#endif /* TIMERS_INT_H_ */
