#ifndef HARDWARESN_LCFG_H
#define HARDWARESN_LCFG_H

#include "Std_Types.h"
#include "AT24_Cfg.h"

void HardwareSn_Init(void);
void HardwareSn_Get(uint8 buf[AT24_HW_SERIAL_NUMBER_SIZE]);
const uint8 *HardwareSn_GetPtr(void);
int shell_func_at24(int argc, const char * const*argv);

#endif