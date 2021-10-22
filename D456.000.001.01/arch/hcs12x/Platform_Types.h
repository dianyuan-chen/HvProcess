/** @addtogroup General General
 *  @{ */

/** @file Platform_Types.h
 * General platform type definitions.
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#ifdef __HC12__
#include <stdtypes.h>
#include <stddef.h>
#endif

#define DIVISION_DIVIDEND_P(DIVIDEND, DIVISOR)   (((signed long)(DIVIDEND) + ((signed long)(DIVISOR) / 2L)) / ((signed long)(DIVISOR)))
#define DIVISION_DIVIDEND_N(DIVIDEND, DIVISOR)   (((signed long)(DIVIDEND) - (labs((signed long)(DIVISOR)) / 2L)) / ((signed long)(DIVISOR)))

#define DIVISION(DIVIDEND, DIVISOR)     (((unsigned long)(DIVIDEND) + ((DIVISOR) / 2UL)) / (DIVISOR))
#define DIVISION_S(DIVIDEND, DIVISOR)   ((signed long)(DIVIDEND) >= 0L ? DIVISION_DIVIDEND_P(DIVIDEND, DIVISOR) : DIVISION_DIVIDEND_N(DIVIDEND, DIVISOR))
#define DIVISION_F(DIVIDEND, DIVISOR)   (((double)(DIVIDEND) + ((double)(DIVISOR) / (double)2)) / (double)(DIVISOR))
#define GAIN(MULTIPLICAND, MULTIPLIER)  ((unsigned long)(MULTIPLICAND) * (unsigned long)(MULTIPLIER))

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define CPU_TYPE_8        8
#define CPU_TYPE_16       16
#define CPU_TYPE_32       32

#define MSB_FIRST         0
#define LSB_FIRST         1

#define HIGH_BYTE_FIRST   0
#define LOW_BYTE_FIRST    1

#define CPU_TYPE            CPU_TYPE_16
#define CPU_BIT_ORDER       LSB_FIRST
#define CPU_BYTE_ORDER      HIGH_BYTE_FIRST

#ifndef FALSE
#define FALSE       (boolean)false
#endif
#ifndef TRUE
#define TRUE        (boolean)true
#endif

typedef unsigned char       boolean;
typedef unsigned char       boollean;

typedef signed char         sint8;
typedef unsigned char       uint8;
typedef signed int          sint16;
typedef unsigned int        uint16;
typedef signed long         sint32;
typedef unsigned long       uint32;

typedef signed char         sint8_least;
typedef unsigned char       uint8_least;
typedef signed short        sint16_least;
typedef unsigned short      uint16_least;
typedef signed long         sint32_least;
typedef unsigned long       uint32_least;

typedef float               float32;
typedef double              float64;


typedef volatile sint8 vsint8;
typedef volatile uint8 vuint8;

typedef volatile sint16 vsint16;
typedef volatile uint16 vuint16;

typedef volatile sint32 vsint32;
typedef volatile uint32 vuint32;

#endif
/** @} */
