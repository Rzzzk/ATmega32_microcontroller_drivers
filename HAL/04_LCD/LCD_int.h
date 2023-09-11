/*
 * LCD_int.h
 *
 *  Created on: Feb 18, 2023
 *      Author: REZK
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_


ES_t LCD_enuInit(void);

ES_t LCD_enuDisplayChar(u8 Copy_u8Char);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);

ES_t LCD_enuDisplayString(const char* string);

ES_t LCD_enuGoToRowCol(u8 row , u8 col);

ES_t LCD_enuDisplayNumber(s16 number);

ES_t LCD_enuClear();

ES_t LCD_enuDisplayStringRowCol(u8 row , u8 col , const char* string );

ES_t LCD_enuCreateCharacter(u8 *pattern , u8 address);

ES_t LCD_enuDisplayBinary(u16 number);

ES_t LCD_enuDisplayNumber_4Digit(u16 number);


#endif /* LCD_INT_H_ */
