/*
 * commonMacros.h
 *
 *  Created on: Sep 22, 2022
 *      Author: REZK
 */

#ifndef COMMONMACROS_H_
#define COMMONMACROS_H_

#define SET_BIT(REG,BIT) (REG|=(1<<BIT)) // set a bit in the register
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT))) // clear a bit in the register
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT)) // toggle a bit in the register
#define GET_BIT(REG,BIT)         ((REG>>BIT)&1) // Output is 0 or 1
#define WRITE_BIT(REG,BIT,VALUE)  (REG&=(~(1<<BIT)))|(VALUE<<BIT)

#define ROT_R(REG,NUM) (REG = (REG>>NUM) | (REG<<(8-NUM)) ) // rotate register to right
#define ROT_L(REG,NUM) (REG = (REG<<NUM) | (REG>>(8-NUM)) ) // rotate register to lift

/* return  true , if the bit is set */
#define BIT_IS_SET(REG,BIT)  ( REG & (1<<BIT) )

/* return  true , if the bit is clear */
#define BIT_IS_CLEAR(REG,BIT)  ( !(REG & (1<<BIT)) )


#endif /* COMMONMACROS_H_ */
