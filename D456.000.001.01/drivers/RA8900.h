#ifndef __RS8900_H__
#define __RS8900_H__

#include "Std_Types.h"
#include "Rtc.h"
#include "i2c.h"


#define RS8900_STATUS_NOT_INIT 0U
#define RS8900_STATUS_OK    1U
#define RS8900_STATUS_RESET 2U

typedef struct {
    const struct i2c_bus bus;
    uint8 status;
    uint8 isRamValid;
} RA8900_RtcChipType;

Std_ReturnType RA8900_Init(RA8900_RtcChipType *chip);
Std_ReturnType RA8900_ReadTime(const RA8900_RtcChipType *chip, Datetime_SecondType *seconds);
Std_ReturnType RA8900_WriteTime(const RA8900_RtcChipType *chip, Datetime_SecondType seconds);
uint8 RA8900_GetRamSizeBits (RA8900_RtcChipType *chip);
Std_ReturnType RS8900_WriteRamData(RA8900_RtcChipType *chip, const uint8 *dat, uint8 offset, uint8 len);
Std_ReturnType RA8900_ReadRamData(const RA8900_RtcChipType *chip, uint8 *dat, uint8 offset, uint8 len);
Std_ReturnType RA8900_ConfigInterrupt(const RA8900_RtcChipType *chip, Rtc_InterruptTypeType int_type, Rtc_InterruptSingleType int_type_single);
Std_ReturnType RA8900_ClearInterrupt(const RA8900_RtcChipType *chip);
Std_ReturnType RA8900_SetAlarmTime(const RA8900_RtcChipType *chip, Datetime_SecondType seconds);
Std_ReturnType RA8900_GetAlarmTime(const RA8900_RtcChipType *chip, Datetime_SecondType *seconds);
Std_ReturnType Ra8900_ReadTemperature(const RA8900_RtcChipType *chip, sint16 *pTemp);

extern const Rtc_OpsType RA8900RtcOps;

#endif
