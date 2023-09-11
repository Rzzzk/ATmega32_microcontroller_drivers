/*
 * WDT_priv.h
 *
 *  Created on: May 23, 2023
 *      Author: REZK
 */

#ifndef WDT_PRIV_H_
#define WDT_PRIV_H_

#define WDTCR (*(volatile unsigned char *)(0x41))


#define WDTOE  4
#define WDE    3
#define WDP2   2
#define WDP1   1
#define WDP0   0

#endif /* WDT_PRIV_H_ */
