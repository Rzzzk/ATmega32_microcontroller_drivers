/*
 * TWI_priv.h
 *
 *  Created on: Jul 19, 2023
 *      Author: REZK
 */

#ifndef TWI_PRIV_H_
#define TWI_PRIV_H_



#define TWI_TWBR_VAL

#define TWI_PRESCALER_1         1
#define TWI_PRESCALER_4         4
#define TWI_PRESCALER_16        16
#define TWI_PRESCALER_64        64


#define ENABLE_GENERAL_CALL     1
#define DISABLE_GENERAL_CALL    0



/*******************/
/*  Master status  */
/*******************/

/*Start condition and repeated start state*/
#define TWI_SATRT_COND_TRANSMIT                               0x08
#define TWI_REP_START_TRANSMIT                                0x10

/*Address package*/
#define SLAVE_ADDR_AND_WRITE                                  0x18
#define SLAVE_ADDR_AND_READ                                   0x40

/*Master transmit data*/
#define MASTER_TRANSMIT_DATA                                  0x28
/*Master received data with ACK*/
#define MASTER_RECEIVED_DATA_WITH_ACK                         0x50
/*Master received data without ACK*/
#define MASTER_RECEIVED_DATA_WITH_NACK                        0x58

/******************/
/*  Slave status  */
/******************/
/*Slave address received with 'read' request*/
#define SLAVE_ADDR_RECEIVED_WITH_R_REQ                        0xA8
/*Slave address received with 'write' request*/
#define SLAVE_ADDR_RECEIVED_WITH_W_REQ                        0x60

/*Slave received the data*/
#define SLAVE_DATA_RECEIVED                                   0x80
/*Slave transmitted the data*/
#define SLAVE_DATA_TRANSMITTED                                0xB8

/*Data Register*/
#define TWDR          *((volatile u8*)0x23)
#define TWD0          0
/*Address register*/
#define TWAR          *((volatile u8*)0x22)
#define TWA6          7
#define TWA5          6
#define TWA4          5
#define TWA3          4
#define TWA2          3
#define TWA1          2
#define TWA0          1
#define TWGCE         0

/*Status register*/
#define TWSR          *((volatile u8*)0x21)
#define TWS7          7
#define TWS6          6
#define TWS5          5
#define TWS4          4
#define TWS3          3
#define TWPS1         1
#define TWPS0         0

/*Bit rate register*/
#define TWBR          *((volatile u8*)0x20)

/*Control register*/
#define TWCR          *((volatile u8*)0x56)
#define TWINT         7
#define TWEA          6
#define TWSTA         5
#define TWSTO         4
#define TWWC          3
#define TWEN          2
#define TWIE          0


#endif /* TWI_PRIV_H_ */
