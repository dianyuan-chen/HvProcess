#ifndef PRE_INCLUDE_H
#define PRE_INCLUDE_H

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define DIVISION(DIVIDEND, DIVISOR)     (((unsigned long)(DIVIDEND) + ((DIVISOR) / 2)) / (DIVISOR))
#define DIVISION_F(DIVIDEND, DIVISOR)   (((double)(DIVIDEND) + ((DIVISOR) / 2)) / (DIVISOR))

#define __far
#define __near
#define far
#define near

#endif
