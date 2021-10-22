#ifndef DCM_PROGRAM_H
#define DCM_PROGRAM_H

#include "Std_Types.h"

typedef uint8 DcmProgram_AppTagType;

#define DCM_PROGRAM_APP_TAG_A 0x01
#define DCM_PROGRAM_APP_TAG_B 0x02

Std_ReturnType DcmProgram_RequestDownload(uint32 addr, uint16 length);
Std_ReturnType DcmProgram_ProgramData(uint8 seq, uint8 *data, uint16 length);
Std_ReturnType DcmProgram_ExitTransfer(void);
Std_ReturnType DcmProgram_ClearAppTag(DcmProgram_AppTagType which);

#endif