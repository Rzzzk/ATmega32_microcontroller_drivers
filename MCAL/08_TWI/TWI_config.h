/*
 * TWI_config.h
 *
 *  Created on: Jul 19, 2023
 *      Author: REZK
 */

#ifndef TWI_CONFIG_H_
#define TWI_CONFIG_H_

#ifndef F_CPU
#define F_CPU                  1000000UL
#endif

/* Slave / Receiver(Master) address*/
#define TWI_MC_ADDRESS          0b01000001

/*Clock configuration*/
#define TWI_SCL_FREQUENCY        100000UL

/*
 	 Options :
 	   TWI_PRESCALER_1
 	   TWI_PRESCALER_4
 	   TWI_PRESCALER_16
 	   TWI_PRESCALER_64
 */
#define TWI_PRESCALER                 TWI_PRESCALER_16

/*
 	 Options :

 	 ENABLE_GENERAL_CALL
 	 DISABLE_GENERAL_CALL

 */
#define TWI_GENERAL_CALL_ENABLE  DISABLE_GENERAL_CALL



#endif /* TWI_CONFIG_H_ */
