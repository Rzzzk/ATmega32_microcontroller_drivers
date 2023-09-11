/*
 * Timers_config.c
 *
 *  Created on: Mar 24, 2023
 *      Author: REZK
 */
#include "stdTypes.h"
#include "errorStates.h"
#include "Timers_int.h"


/*Timer0 initialize*/
 Timer0_t Timer0_strConfig =
 {
		 Timer0_enuFastPWM ,                    /* Timer 0 MODE          */
		 PWM_NonInverted ,                      /* Output signal OC0     */
		 TIMERS_enuPrescalingBy1024 ,           /* Prescaler             */
		 0,                                     /* Counter Initial Value */
		 250                                    /* Compare match value   */
 };


 /*Timer1 initialize*/
 Timer1_t Timer1_strConfig =
 {
		 Timer1_enuFastPWM_TopICR1 , /* Timer 1 Mode                  */
		 PWM_NonInverted ,           /* Output signal channel A       */
		 PWM_NonInverted ,           /* Output signal channel B       */
		 TIMERS_enuPrescalingBy8,    /* Prescaler                     */
		 0 , 						 /* Counter Initial Value         */
		 125 ,                       /* Compare match value channel A */
		 250 ,                       /* Compare match value channel B */
		 2500                        /* Input capture register value  */
 };
