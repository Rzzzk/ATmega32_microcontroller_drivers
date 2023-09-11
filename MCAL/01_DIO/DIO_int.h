/*
 * DIO_int.h
 *
 *  Created on: Feb 11, 2023
 *      Author: REZK
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_



/*The Ports that you can use*/
#define  DIO_u8PORTA      0
#define  DIO_u8PORTB      1
#define  DIO_u8PORTC      2
#define  DIO_u8PORTD      3

/*The Pins that you can use*/
#define  DIO_u8PIN0       0
#define  DIO_u8PIN1       1
#define  DIO_u8PIN2       2
#define  DIO_u8PIN3       3
#define  DIO_u8PIN4       4
#define  DIO_u8PIN5       5
#define  DIO_u8PIN6       6
#define  DIO_u8PIN7       7

/*Port directions*/
#define DIO_u8PORT_OUTPUT          0xff
#define DIO_u8PORT_INPUT           0x00


/*Port values*/
/*Values for output pins*/
#define DIO_u8PORT_HIGH            0xff
#define DIO_u8PORT_LOW             0x00

/*Values for input pins*/
#define DIO_u8PORT_PULL_UP         0xff
#define DIO_u8PORT_FLOAT           0x00


/*Pin directions*/
#define DIO_u8PIN_OUTPUT          1
#define DIO_u8PIN_INPUT           0


/*Pin values*/
/*Values for output pins*/
#define DIO_u8PIN_HIGH            1
#define DIO_u8PIN_LOW             0

/*Values for input pins*/
#define DIO_u8PIN_PULL_UP         1
#define DIO_u8PIN_FLOAT           0

/****************************************************************************/
/***********              Prototypes of DIO APIs              ***************/
/****************************************************************************/
ES_t DIO_enuInit(void);

ES_t DIO_enuSetPortDirection(u8 Copy_u8PortID , u8 Copy_u8PortDir);

ES_t DIO_enuSetPortValue(u8 Copy_u8PortID , u8 Copy_u8Value);

ES_t DIO_enuTogPort(u8 Copy_u8PortID);

ES_t DIO_enuGetPortValue(u8 Copy_u8PortID , u8* Copy_pu8Value);


ES_t DIO_enuSetPinDirection(u8 Copy_u8PortID ,u8 Copy_u8PinID , u8 Copy_u8PinDir);

ES_t DIO_enuSetPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID , u8 Copy_u8Value);

ES_t DIO_enuTogPin(u8 Copy_u8PortID ,u8 Copy_u8PinID );

ES_t DIO_enuGetPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID , u8* Copy_pu8Value);

/****************************************************************************/
#endif /* DIO_INT_H_ */
