#ifndef _TOOLS_LINUX_BITOPS_H_
#define _TOOLS_LINUX_BITOPS_H_


#ifndef __BYTESIZE
#define __BYTESIZE          8
#endif

#ifndef BITS_PER_BYTE
# define BITS_PER_BYTE      __BYTESIZE
#endif

#define DIV_ROUND_UP(n,d)   (((n) + (d) - 1U) / (d))

#define BIT_MASK(nr)        ((unsigned char)((unsigned char)1U << ((nr) % (unsigned char)BITS_PER_BYTE)))
#define BIT_BYTE(nr)        ((nr) >> 3)


#endif