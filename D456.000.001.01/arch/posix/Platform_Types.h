/** @addtogroup General General
 *  @{ */
/** @file Platform_Types.h
 * General platform type definitions.
 */
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define CPU_TYPE            CPU_TYPE_32
#define CPU_BIT_ORDER       MSB_FIRST
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST
#ifndef FALSE
#define FALSE       (boolean)false
#endif
#ifndef TRUE
#define TRUE        (boolean)true
#endif
typedef bool                boolean;
typedef bool                boollean;
typedef signed char         sint8;
typedef unsigned char       uint8;
typedef signed short        sint16;
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
