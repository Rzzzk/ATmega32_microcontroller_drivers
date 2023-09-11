/*
 * EXTI_priv.h
 *
 *  Created on: Mar 22, 2023
 *      Author: REZK
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_



#define MCUCR        (*(volatile unsigned char*)0x55)
#define SE            7
#define SM2           6
#define SM1           5
#define SM0           4
#define ISC11         3
#define ISC10         2
#define ISC01         1
#define ISC00         0

#define MCUCSR		 (*(volatile unsigned char*)0x54)
#define ISC2          6


#define GICR         (*(volatile unsigned char*)0x5B)
#define INT1		  7
#define INT0          6
#define INT2          5

#define GIFR         (*(volatile unsigned char*)0x5A)
#define INTF1		  7
#define INTF0         6
#define INTF2         5


#endif /* EXTI_PRIV_H_ */
