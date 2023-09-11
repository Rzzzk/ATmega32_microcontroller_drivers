/*
 * LCD_priv.h
 *
 *  Created on: Feb 18, 2023
 *      Author: REZK
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

#define EIGHT_BIT        8
#define FOUR_BIT         4



/*The most important commands*/
#define LCD_FOUR_BIT_DATA            	 0x02
#define LCD_FOUR_BIT_TWO_LINES       	 0x28
#define LCD_CLEAR_SCREEN                 0x01
#define LCD_CURSOR_OFF                   0x0c

#define LCD_EIGHT_BIT_TWO_LINES          0x38
#define LCD_INCREASE_DDRAM_ADRESS        0x06
#define LCD_SET_CURSOR_LOCATION          0x80
#define LCD_SET_CGRAM_LOCATION           0x40



static inline void LCD_invidSendCommand(u8 Copy_u8Command);
static inline void LCD_vidLatch(u8 Copy_u8Data);

#ifndef NULL
#define  NULL           (void*)0
#endif

#endif /* LCD_PRIV_H_ */
