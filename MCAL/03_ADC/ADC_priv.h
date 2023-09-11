/*
 * ADC_priv.h
 *
 *  Created on: Apr 24, 2023
 *      Author: REZK
 */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_


/*ADC Registers*/

#define  ADMUX         *((volatile unsigned char*)0x27)
#define  REFS1         7
#define  REFS0		   6
#define  ADLAR         5
#define  MUX4          4
#define  MUX3          3
#define  MUX2          2
#define  MUX1          1
#define  MUX0          0


#define  ADCSRA         *((volatile unsigned char*)0x26)
#define  ADEN           7
#define  ADSC           6
#define  ADATE          5
#define  ADIF           4
#define  ADIE           3
#define  ADPS2          2
#define  ADPS1          1
#define  ADPS0          0


#define  SFIOR          *((volatile unsigned char*)0x50)
#define  ADTS2          7
#define  ADTS1          6
#define  ADTS0          5
// bit                  4
#define  ACME           3
#define  PUD            2
#define  PSR2           1
#define  PSR10          0

/*
ADCH ADC Data Register High Byte 215
ADCL ADC Data Register Low Byte
 */
#define  ADCL          *((volatile unsigned char*)0x24)
#define  ADCH          *((volatile unsigned char*)0x25)
#define  ADC          *((volatile unsigned short*)0x24)

#endif /* ADC_PRIV_H_ */
