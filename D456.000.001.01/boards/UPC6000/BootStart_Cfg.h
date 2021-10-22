#ifndef BOOTSTART_CFG_H
#define BOOTSTART_CFG_H

#include "derivative.h"

#define Boot_GetHwVersion() (((uint8)(~PORTB) >> 5) & (uint8)0x07)

#endif
