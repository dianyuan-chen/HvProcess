#ifndef WINTIME_H__
#define WINTIME_H__

#include <time.h>
#include "Std_Types.h"
#include "Rtc.h"

typedef struct {
    time_t offset;
} WinTime_RtcChipType;

Std_ReturnType WinTime_Init(WinTime_RtcChipType *chip);
Std_ReturnType WinTime_ReadTime(WinTime_RtcChipType *chip, Datetime_SecondType *seconds);
Std_ReturnType WinTime_WriteTime(WinTime_RtcChipType *chip, Datetime_SecondType seconds);
uint8 WinTime_GetRamSizeBits (WinTime_RtcChipType *chip);
Std_ReturnType RS8900_WriteRamData(WinTime_RtcChipType *chip, const uint8 *dat, uint8 offset, uint8 len);
Std_ReturnType WinTime_ReadRamData(WinTime_RtcChipType *chip, uint8 *dat, uint8 offset, uint8 len);
Std_ReturnType WinTime_ConfigInterrupt(WinTime_RtcChipType *chip, Rtc_InterruptTypeType int_type, Rtc_InterruptSingleType int_type_single);
Std_ReturnType WinTime_ClearInterrupt(WinTime_RtcChipType *chip);
Std_ReturnType WinTime_SetAlarmTime(WinTime_RtcChipType *chip, Datetime_SecondType seconds);
Std_ReturnType WinTime_GetAlarmTime(WinTime_RtcChipType *chip, Datetime_SecondType *seconds);

extern const Rtc_OpsType WinTimeRtcOps;

#endif