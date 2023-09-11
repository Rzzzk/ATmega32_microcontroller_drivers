/*
 * LCD_config.h
 *
 *  Created on: Feb 18, 2023
 *      Author: REZK
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
/****************************/
/*       LCD Mode           */
/****************************/

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *   FOUR_BIT Mode connect D4 , D5 , D6 and D7   *
 *    EIGHT_BIT mode connect all pins D0 : D7    *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#define LCD_MODE    FOUR_BIT

/************************************/
/*      Control Pins connection     */
/************************************/
#define RS_PIN      DIO_u8PIN4
#define RS_PORT     DIO_u8PORTC

#define RW_PIN      DIO_u8PIN5
#define RW_PORT     DIO_u8PORTC

#define EN_PIN      DIO_u8PIN6
#define EN_PORT     DIO_u8PORTC

/************************************/
/*       Data Pins connection       */
/************************************/

/*Don't worry about or from not connected pins*/

#define D0_PIN      DIO_u8PIN0
#define D0_PORT     DIO_u8PORTD

#define D1_PIN      DIO_u8PIN1
#define D1_PORT     DIO_u8PORTD

#define D2_PIN      DIO_u8PIN2
#define D2_PORT     DIO_u8PORTD

#define D3_PIN      DIO_u8PIN3
#define D3_PORT     DIO_u8PORTD

#define D4_PIN      DIO_u8PIN4
#define D4_PORT     DIO_u8PORTD

#define D5_PIN      DIO_u8PIN5
#define D5_PORT     DIO_u8PORTD

#define D6_PIN      DIO_u8PIN6
#define D6_PORT     DIO_u8PORTD

#define D7_PIN      DIO_u8PIN7
#define D7_PORT     DIO_u8PORTD

#endif /* LCD_CONFIG_H_ */
