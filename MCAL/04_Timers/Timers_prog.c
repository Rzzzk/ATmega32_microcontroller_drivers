/*
 * Timers_prog.c
 *
 *  Created on: Mar 24, 2023
 *      Author: REZK
 */

#include "stdTypes.h"
#include "errorStates.h"


#include "Timers_int.h"
#include "Timers_priv.h"


static void (*Timer0_pfuncTimer0OVFunc) (void) = NULL;
static void (*Timer0_pfuncTimer0CTCFunc) (void) = NULL;

/*call back overflow function*/
static void (*Timer1_pfuncTimer1_OVF_Func) (void) = NULL;

/*call back COMPA function*/
static void (*Timer1_pfuncTimer1_CTCA_Func) (void) = NULL;

/*call back COMPB function*/
static void (*Timer1_pfuncTimer1_CTCB_Func) (void) = NULL;
/***************************************************/
/*                     TIMER0                      */
/***************************************************/
ES_t Timer0_enuInit(Timer0_t *Copy_strTimer0)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*********************************************/
	/**              Set the mode               **/
	/*********************************************/

	switch(Copy_strTimer0->Timer0_enuMode)
	{
	case Timer0_enuOverflow :
		TCCR0 &=~(1<<WGM01);
		TCCR0 &=~(1<<WGM00);
		break;
	case Timer0_enuCTC :
		TCCR0 |=(1<<WGM01);
		TCCR0 &=~(1<<WGM00);
		break;
	case Timer0_enuPhaseCorrectPWM  :
		TCCR0 &=~(1<<WGM01);
		TCCR0 |=(1<<WGM00);
		break;
	case Timer0_enuFastPWM  :
		TCCR0 |=(1<<WGM01);
		TCCR0 |=(1<<WGM00);
		break;
	default :
		break;
	}


	/*********************************************/
	/**                  OC0                    **/
	/*********************************************/
	if(Copy_strTimer0->Timer0_enuMode == Timer0_enuOverflow)
	{
		TCCR0&=~(1<<COM00);
		TCCR0&=~(1<<COM01);
	}
	else
	{

		if(Copy_strTimer0->Timer0_enuOC0Action == Disconnect)
		{
			TCCR0&=~(1<<COM00);
			TCCR0&=~(1<<COM01);
		}
		else if(Copy_strTimer0->Timer0_enuOC0Action == ToggleOnCompare)
		{
			if(Copy_strTimer0->Timer0_enuMode == Timer0_enuCTC)
			{
				TCCR0|=(1<<COM00);
				TCCR0&=~(1<<COM01);
			}
		}
		else if((Copy_strTimer0->Timer0_enuOC0Action == ClearOnCompare) || (Copy_strTimer0->Timer0_enuOC0Action == PWM_NonInverted) )
		{
			TCCR0&=~(1<<COM00);
			TCCR0|=(1<<COM01);
		}
		else if((Copy_strTimer0->Timer0_enuOC0Action == SetOnCompare) || (Copy_strTimer0->Timer0_enuOC0Action == PWM_Inverted))
		{
			TCCR0|=(1<<COM00);
			TCCR0|=(1<<COM01);
		}

	}

	/*********************************************/
	/**              Pr-escaler                 **/
	/*********************************************/
	if((Copy_strTimer0->Timer0_enuPrescaler)>= TIMERS_enuNoClockSource && (Copy_strTimer0->Timer0_enuPrescaler) <= TIMERS_enuPrescalingBy1024 )
	{
		TCCR0 &=0xF8;
		TCCR0 |=(Copy_strTimer0->Timer0_enuPrescaler);
	}


	/*set compare match value*/
	OCR0  = Copy_strTimer0->Timer0_u8CompareMatchValue;

	/*set the initial counter value*/
    TCNT0 = Copy_strTimer0->Timer0_u8Counter;


	return Local_enuErrorState;
}

ES_t Timer0_enuSetMode(TIMERS_Mode_t Copy_enuTimer0Mode)
{
	ES_t Local_enuErrorState=ES_NOK;
	/*Set the mode*/
	switch(Copy_enuTimer0Mode)
	{
	case Timer0_enuOverflow :
		TCCR0 &=~(1<<WGM01);
		TCCR0 &=~(1<<WGM00);
		break;
	case Timer0_enuCTC :
		TCCR0 |=(1<<WGM01);
		TCCR0 &=~(1<<WGM00);
		break;
	case Timer0_enuPhaseCorrectPWM  :
		TCCR0 &=~(1<<WGM01);
		TCCR0 |=(1<<WGM00);
		break;
	case Timer0_enuFastPWM  :
		TCCR0 |=(1<<WGM01);
		TCCR0 |=(1<<WGM00);
		break;
	default :
		break;
	}

	return Local_enuErrorState;
}

ES_t Timer0_enuSetPrescaler(TIMERS_prescaler_t Copy_enuTimer0Prescaler)
{
	ES_t Local_enuErrorState=ES_NOK;

	if((Copy_enuTimer0Prescaler)>= TIMERS_enuNoClockSource && (Copy_enuTimer0Prescaler) <= TIMERS_enuPrescalingBy1024 )
	{
		TCCR0 &=0xF8;
		TCCR0 |= Copy_enuTimer0Prescaler;
		Local_enuErrorState=ES_OK;
	}


	return Local_enuErrorState;
}


ES_t Timer0_enuSetCounter(u8 Copy_u8Counter)
{
	ES_t Local_enuErrorState=ES_NOK;

	/*set counter value*/
	TCNT0 = Copy_u8Counter;
	Local_enuErrorState=ES_OK;


	return Local_enuErrorState;

}

ES_t Timer0_enuGetCounter(u8 *Copy_u8Counter)
{
	ES_t Local_enuErrorState=ES_NOK;

	/*Get counter value*/
	*Copy_u8Counter = TCNT0;

	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t Timer0_enuSetCmpareMatch(u8 Copy_u8CompareMatchValue)
{
	ES_t Local_enuErrorState=ES_NOK;

	/*set compare match value*/
	OCR0 = Copy_u8CompareMatchValue;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;

}

ES_t Timer0_enuSetOC0Action(TIMERS_OutputPinAction_t Copy_enuTime0OC0Act)
{
	ES_t Local_enuErrorState=ES_NOK;

	/*********************************************/
	/**                  OC0                    **/
	/*********************************************/

	if(Copy_enuTime0OC0Act == Disconnect)
	{
		TCCR0&=~(1<<COM00);
		TCCR0&=~(1<<COM01);
	}
	else if(Copy_enuTime0OC0Act== ToggleOnCompare)
	{
		if(Copy_enuTime0OC0Act == Timer0_enuCTC)
		{
			TCCR0|=(1<<COM00);
			TCCR0&=~(1<<COM01);
		}
	}
	else if((Copy_enuTime0OC0Act == ClearOnCompare) || (Copy_enuTime0OC0Act == PWM_NonInverted) )
	{
		TCCR0&=~(1<<COM00);
		TCCR0|=(1<<COM01);
	}
	else if((Copy_enuTime0OC0Act == SetOnCompare) || (Copy_enuTime0OC0Act == PWM_Inverted))
	{
		TCCR0|=(1<<COM00);
		TCCR0|=(1<<COM01);
	}

	return Local_enuErrorState;
}


ES_t Timer0_enuOverFlowINT_Enable()
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK|=(1<<TOIE0);

	return Local_enuErrorState;

}

ES_t Timer0_enuOverFlowINT_Disable()
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK&=~(1<<TOIE0);

	return Local_enuErrorState;
}

ES_t Timer0_enuCTC_INT_Enable()
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK|=(1<<OCIE0);

	return Local_enuErrorState;
}

ES_t Timer0_enuCTC_INT_Disable()
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK&=~(1<<OCIE0);

	return Local_enuErrorState;
}


ES_t Timer0_enuCallBack(TIMERS_Mode_t Copy_enuTimer0Mode , void(*Copy_pfunTimer0func)(void))
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_pfunTimer0func == NULL)
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	else
	{
		switch(Copy_enuTimer0Mode)
		{
		case Timer0_enuOverflow:
			Timer0_pfuncTimer0OVFunc = Copy_pfunTimer0func;
			Local_enuErrorState=ES_OK;
			break;
		case Timer0_enuCTC:
			Timer0_pfuncTimer0CTCFunc = Copy_pfunTimer0func;
			Local_enuErrorState=ES_OK;
			break;
		default :
			break;
		}
	}

	return Local_enuErrorState;
}

// compare match ISR
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(Timer0_pfuncTimer0CTCFunc!=NULL)
	{
		Timer0_pfuncTimer0CTCFunc();
	}

}

// overflow ISR
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if(Timer0_pfuncTimer0OVFunc!=NULL)
	{
		Timer0_pfuncTimer0OVFunc();
	}

}


/***************************************************/
/*                     TIMER1                      */
/***************************************************/

ES_t Timer1_enuInit(Timer1_t *Copy_strTimer1Config)
{
	ES_t Local_enuErrorState = ES_NOK;


	/*set the mode of timer1*/

	switch(Copy_strTimer1Config->Timer1_enuMode)
	{
	case Timer1_enuOverflow:
		TCCR1A&=~(1<<WGM10);
		TCCR1A&=~(1<<WGM11);
		TCCR1B&=~(1<<WGM12);
		TCCR1B&=~(1<<WGM13);
		Local_enuErrorState = ES_OK;
		break;
	case Timer1_enuCTC:
		TCCR1A&=~(1<<WGM10);
		TCCR1A&=~(1<<WGM11);
		TCCR1B|=(1<<WGM12);
		TCCR1B&=~(1<<WGM13);
		Local_enuErrorState = ES_OK;
		break;
	case Timer1_enuFastPWM_TopICR1:
		TCCR1A&=~(1<<WGM10);
		TCCR1A|=(1<<WGM11);
		TCCR1B|=(1<<WGM12);
		TCCR1B|=(1<<WGM13);
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}

	/*set the compare match values*/
	OCR1A = Copy_strTimer1Config->Timer1_u16Comparematch_A_Value ;
	OCR1B = Copy_strTimer1Config->Timer1_u16Comparematch_B_Value ;
	/*set input capture register value*/
	ICR1  = Copy_strTimer1Config->Timer1_u16InputCapRegValue ;

	TCNT1 = Copy_strTimer1Config->Timer1_u16Counter;

	/*OC1A Action*/

	switch(Copy_strTimer1Config->Timer1_enuOC1A_Action)
	{
	case Disconnect:
		TCCR1A&=~(1<<COM1A0);
		TCCR1A&=~(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case ToggleOnCompare:
		TCCR1A|=(1<<COM1A0);
		TCCR1A&=~(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case ClearOnCompare:
		TCCR1A&=~(1<<COM1A0);
		TCCR1A|=(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case PWM_NonInverted:
		TCCR1A&=~(1<<COM1A0);
		TCCR1A|=(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case SetOnCompare:
		TCCR1A|=(1<<COM1A0);
		TCCR1A|=(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case PWM_Inverted:
		TCCR1A|=(1<<COM1A0);
		TCCR1A|=(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}

	/*OC1B Action*/

	switch(Copy_strTimer1Config->Timer1_enuOC1B_Action)
	{
	case Disconnect:
		TCCR1A&=~(1<<COM1B0);
		TCCR1A&=~(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case ToggleOnCompare:
		TCCR1A|=(1<<COM1B0);
		TCCR1A&=~(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case ClearOnCompare:
		TCCR1A&=~(1<<COM1B0);
		TCCR1A|=(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case PWM_NonInverted:
		TCCR1A&=~(1<<COM1B0);
		TCCR1A|=(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case SetOnCompare:
		TCCR1A|=(1<<COM1B0);
		TCCR1A|=(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case PWM_Inverted:
		TCCR1A|=(1<<COM1B0);
		TCCR1A|=(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}

	/*Set the Prescaler */

	if((Copy_strTimer1Config->Timer1_enuPrescaler)>=TIMERS_enuNoClockSource && (Copy_strTimer1Config->Timer1_enuPrescaler) <= TIMERS_enuPrescalingBy1024)
	{
		TCCR1B&=0xf8;
		TCCR1B|=(Copy_strTimer1Config->Timer1_enuPrescaler);
	}

	return Local_enuErrorState;
}



ES_t Timer1_enuSetMode(TIMERS_Mode_t Copy_enuTimer1Mode)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*set the mode of timer1*/

	switch(Copy_enuTimer1Mode)
	{
	case Timer1_enuOverflow:
		TCCR1A&=~(1<<WGM10);
		TCCR1A&=~(1<<WGM11);
		TCCR1B&=~(1<<WGM12);
		TCCR1B&=~(1<<WGM13);
		Local_enuErrorState = ES_OK;
		break;
	case Timer1_enuCTC:
		TCCR1A&=~(1<<WGM10);
		TCCR1A&=~(1<<WGM11);
		TCCR1B|=(1<<WGM12);
		TCCR1B&=~(1<<WGM13);
		Local_enuErrorState = ES_OK;
		break;
	case Timer1_enuFastPWM_TopICR1:
		TCCR1A&=~(1<<WGM10);
		TCCR1A|=(1<<WGM11);
		TCCR1B|=(1<<WGM12);
		TCCR1B|=(1<<WGM13);
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}

	return Local_enuErrorState;
}

ES_t Timer1_enuSetPrescaler(TIMERS_prescaler_t Copy_enuTimer1Prescaler)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set the Prescaler */

	if(Copy_enuTimer1Prescaler>=TIMERS_enuNoClockSource && Copy_enuTimer1Prescaler <= TIMERS_enuPrescalingBy1024)
	{
		TCCR1B&=0xf8;
		TCCR1B|=Copy_enuTimer1Prescaler;
	}

	return Local_enuErrorState;
}


ES_t Timer1_enuSetCounter(u16 Copy_u16Counter)
{
	ES_t Local_enuErrorState = ES_NOK;

	TCNT1 = Copy_u16Counter;
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t Timer1_enuGetCounter(u16 *Copy_u16Counter)
{
	ES_t Local_enuErrorState = ES_NOK;

	*Copy_u16Counter = TCNT1 ;
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}


ES_t Timer1_enuSetCmpareMatchRegA(u16 Copy_u16CompareMatchValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	OCR1A = Copy_u16CompareMatchValue;
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t Timer1_enuSetCmpareMatchRegB(u16 Copy_u16CompareMatchValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	OCR1B = Copy_u16CompareMatchValue;
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}


ES_t Timer1_enuSetInputCapReg(u16 Copy_u16InputCapRegValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	ICR1  = Copy_u16InputCapRegValue;
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t Timer1_enuSet_OC1A_Action(TIMERS_OutputPinAction_t Copy_enuTime1OC1AAct)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*OC1A Action*/

	switch(Copy_enuTime1OC1AAct)
	{
	case Disconnect:
		TCCR1A&=~(1<<COM1A0);
		TCCR1A&=~(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case ToggleOnCompare:
		TCCR1A|=(1<<COM1A0);
		TCCR1A&=~(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case ClearOnCompare:
		TCCR1A&=~(1<<COM1A0);
		TCCR1A|=(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case PWM_NonInverted:
		TCCR1A&=~(1<<COM1A0);
		TCCR1A|=(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case SetOnCompare:
		TCCR1A|=(1<<COM1A0);
		TCCR1A|=(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	case PWM_Inverted:
		TCCR1A|=(1<<COM1A0);
		TCCR1A|=(1<<COM1A1);
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}


	return Local_enuErrorState;
}


ES_t Timer1_enuSet_OC1B_Action(TIMERS_OutputPinAction_t Copy_enuTime1OC1BAct)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*OC1B Action*/

	switch(Copy_enuTime1OC1BAct)
	{
	case Disconnect:
		TCCR1A&=~(1<<COM1B0);
		TCCR1A&=~(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case ToggleOnCompare:
		TCCR1A|=(1<<COM1B0);
		TCCR1A&=~(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case ClearOnCompare:
		TCCR1A&=~(1<<COM1B0);
		TCCR1A|=(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case PWM_NonInverted:
		TCCR1A&=~(1<<COM1B0);
		TCCR1A|=(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case SetOnCompare:
		TCCR1A|=(1<<COM1B0);
		TCCR1A|=(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	case PWM_Inverted:
		TCCR1A|=(1<<COM1B0);
		TCCR1A|=(1<<COM1B1);
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}

	return Local_enuErrorState;
}


ES_t Timer1_enuOverFlowINT_Enable()
{
	ES_t Local_enuErrorState = ES_NOK;

	//Overflow Interrupt Enable
	TIMSK|=(1<<TOIE1);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t Timer1_enuOverFlowINT_Disable()
{
	ES_t Local_enuErrorState = ES_NOK;

	//Overflow Interrupt Disable
	TIMSK&=~(1<<TOIE1);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t Timer1_enuCTCA_INT_Enable()
{
	ES_t Local_enuErrorState = ES_NOK;
	TIMSK|=(1<<OCIE1A);

	return Local_enuErrorState;
}

ES_t Timer1_enuCTCB_INT_Enable()
{
	ES_t Local_enuErrorState = ES_NOK;

	TIMSK|=(1<<OCIE1B);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}


ES_t Timer1_enuCTCA_INT_Disable()
{
	ES_t Local_enuErrorState = ES_NOK;

	TIMSK&=~(1<<OCIE1A);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t Timer1_enuCTCB_INT_Disable()
{
	ES_t Local_enuErrorState = ES_NOK;

	TIMSK&=~(1<<OCIE1B);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t Timer1_enuCallBackOVF(void(*Copy_pfunTimer1func)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pfunTimer1func == NULL)
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	else
	{

		Timer1_pfuncTimer1_OVF_Func = Copy_pfunTimer1func;
		Local_enuErrorState=ES_OK;

	}

	return Local_enuErrorState;
}


ES_t Timer1_enuCallBackCTCA(void(*Copy_pfunTimer1func)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pfunTimer1func == NULL)
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfuncTimer1_CTCA_Func = Copy_pfunTimer1func;
		Local_enuErrorState=ES_OK;
	}

	return Local_enuErrorState;
}

ES_t Timer1_enuCallBackCTCB(void(*Copy_pfunTimer1func)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pfunTimer1func == NULL)
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfuncTimer1_CTCB_Func = Copy_pfunTimer1func;
		Local_enuErrorState=ES_OK;
	}

	return Local_enuErrorState;
}

//Timer/Counter1 Compare Match A
void __vector_7(void) __attribute__((signal));
void __vector_7 (void)
{
	if(Timer1_pfuncTimer1_CTCA_Func != NULL)
	{
		Timer1_pfuncTimer1_CTCA_Func();
	}


}

//Timer/Counter1 Compare Match B
void __vector_8(void) __attribute__((signal));
void __vector_8 (void)
{
	if(Timer1_pfuncTimer1_CTCB_Func != NULL)
	{
		Timer1_pfuncTimer1_CTCB_Func();
	}


}
//Timer/Counter1 Overflow
void __vector_9(void) __attribute__((signal));
void __vector_9 (void)
{
	if(Timer1_pfuncTimer1_OVF_Func != NULL)
	{
		Timer1_pfuncTimer1_OVF_Func();
	}
}











