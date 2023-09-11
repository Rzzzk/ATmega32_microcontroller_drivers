/*
 * GIE_priv.h
 *
 *  Created on: May 10, 2023
 *      Author: REZK
 */

#ifndef GIE_PRIV_H_
#define GIE_PRIV_H_

#define sei()             __asm__ __volatile__ ("sei" ::)
#define cli()             __asm__ __volatile__ ("cli" ::)

#define SREG               (*(volatile u8*)0x5F)
#define I                  7
#define T                  6
#define H                  5
#define S                  4
#define V                  3
#define N                  2
#define Z                  1
#define C                  0



#endif /* GIE_PRIV_H_ */
