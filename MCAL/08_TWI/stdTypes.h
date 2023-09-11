/*
 * stdTypes.h
 *
 *  Created on: Sep 22, 2022
 *      Author: REZK
 */

#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char             u8  ;   //0:255
typedef signed char               s8  ;   //-128:+127
typedef unsigned short            u16 ;   //0:65535
typedef signed short              s16 ;   //-32768:+32767
typedef unsigned long             u32 ;
typedef signed long               s32 ;
typedef unsigned long long        u64 ;
typedef signed long long          s64 ;

typedef float                     f32 ;
typedef double                    f64 ;

#ifndef NULL
#define NULL ((void*)0)
#endif

#endif /* STDTYPES_H_ */
