/*
 * SPI_priv.h
 *
 *  Created on: Apr 29, 2023
 *      Author: REZK
 */

#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_

/*SPI registers*/


/*Control register*/
#define SPCR             (*(volatile unsigned char*) 0x2D)
#define SPIE             7
#define SPE              6
#define DORD             5
#define MSTR             4
#define CPOL             3
#define CPHA             2
#define SPR1             1
#define SPR0             0

/*Status register*/
#define SPSR             (*(volatile unsigned char*) 0x2E)
#define SPIF             7
#define WCOL             6
#define SPI2X            0

/*Data register*/
#define SPDR             (*(volatile unsigned char*) 0x2F)


#endif /* SPI_PRIV_H_ */
