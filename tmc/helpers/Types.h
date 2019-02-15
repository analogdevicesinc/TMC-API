/*
 * Types.h
 *
 *  Created on: 29.09.2016
 *      Author: ed
 */

#ifndef TMC_TYPES_H_
#define TMC_TYPES_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// unsigned types
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef u8       uint8;
typedef u16      uint16;
typedef u32      uint32;
typedef u64      uint64;

#define u8_MAX   (u8)   255
#define u10_MAX  (u16)  1023
#define u12_MAX  (u16)  4095
#define u15_MAX  (u16)  32767
#define u16_MAX  (u16)  65535
#define u18_MAX  (u32)  262143uL
#define u20_MAX  (u32)  1048575uL
#define u22_MAX  (u32)  4194303uL
#define u24_MAX  (u32)  16777215uL
#define u32_MAX  (u32)  4294967295uL

// signed types
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef s8       int8;
typedef s16      int16;
typedef s32      int32;
typedef s64      int64;

typedef float f32;
typedef double f64;

#define s8_MAX   (s8)   127
#define s8_MIN   (s8)   -128
#define s16_MAX  (s16)  32767
#define s16_MIN  (s16)  -32768
#define s24_MAX  (s32)  8388607
#define s24_MIN  (s32)  -8388608
#define s32_MAX  (s32)  2147483647
#define s32_MIN  (s32)  -2147483648

// NULL pointer
#ifndef NULL
	#define NULL ((void *) 0)
#endif

#endif /* TMC_TYPES_H_ */
