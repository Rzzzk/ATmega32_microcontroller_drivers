/*
 * EEPROM_int.h
 *
 *  Created on: Sep 7, 2023
 *      Author: REZK
 */

#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_


ES_t EEPROM_enuWriteDataByte(u8 Copy_u8Data  , u16 Copy_u16Address);
ES_t EEPROM_enuReadDataByte(u8 *Copy_pu8Data , u16 Copy_u16Address);

#endif /* EEPROM_INT_H_ */
