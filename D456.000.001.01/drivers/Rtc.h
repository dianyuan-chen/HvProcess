#ifndef RTC_H__
#define RTC_H__

#include "Std_Types.h"
#include "Datetime.h"

typedef enum {
    RTC_INTERRUPT_DISABLE,
    RTC_INTERRUPT_ALARM,
    RTC_INTERRUPT_FREQUENCY,
    RTC_INTERRUPT_COUNTDOWN,
} Rtc_InterruptTypeType;

typedef enum {
    RTC_INTERRUPT_SINGLE_LOWLEVEL,
    RTC_INTERRUPT_SINGLE_PAUSE,
} Rtc_InterruptSingleType;

typedef Std_ReturnType (*Rtc_InitFuncType)(void *chip);
typedef Std_ReturnType (*Rtc_WriteTimeFuncType)(void *chip, Datetime_SecondType time);
typedef Std_ReturnType (*Rtc_ReadTimeFuncType)(void *chip, Datetime_SecondType *second);
typedef uint8 (*Rtc_GetRamSizeFuncType)(void *chip);
typedef Std_ReturnType (*Rtc_WriteRamDataFuncType)(void *chip, const uint8 *dat, uint8 offset, uint8 len);
typedef Std_ReturnType (*Rtc_ReadRamDataFuncType)(void *chip, uint8 *dat, uint8 offset, uint8 len);
typedef Std_ReturnType (*Rtc_ConfigInterruptFuncType)(void *chip, Rtc_InterruptTypeType int_type, Rtc_InterruptSingleType int_type_single);
typedef Std_ReturnType (*Rtc_ClearInterruptFuncType)(void *chip);
typedef Std_ReturnType (*Rtc_SetAlarmTimeFuncType)(void *chip, Datetime_SecondType seconds);
typedef Std_ReturnType (*Rtc_GetAlarmTimeFuncType)(void *chip, Datetime_SecondType *seconds);
typedef Std_ReturnType (*Rtc_ReadTemperatureFuncType)(void *chip, sint16 *temp);

typedef struct {
    Rtc_InitFuncType Init;
    Rtc_WriteTimeFuncType WriteTime;
    Rtc_ReadTimeFuncType ReadTime;
    Rtc_GetRamSizeFuncType GetRamSize;
    Rtc_WriteRamDataFuncType WriteRamData;
    Rtc_ReadRamDataFuncType ReadRamData;
    Rtc_ConfigInterruptFuncType ConfigInterrupt;
    Rtc_ClearInterruptFuncType ClearInterrupt;
    Rtc_SetAlarmTimeFuncType SetAlarmTime;
    Rtc_GetAlarmTimeFuncType GetAlarmTime;
    Rtc_ReadTemperatureFuncType ReadTemperature;
} Rtc_OpsType;

typedef struct {
    void *chip;
    const Rtc_OpsType *ops;
} Rtc_DevicesType;


#define Rtc_ReadTime(rtc, sec)                  ((rtc)->ops->ReadTime((rtc)->chip, sec))
#define Rtc_WriteTime(rtc, sec)                 ((rtc)->ops->WriteTime((rtc)->chip, sec))
#define Rtc_Init(rtc)                           ((rtc)->ops->Init((rtc)->chip))
#define Rtc_ReadTemperature(rtc, pTemp)         ((rtc)->ops->ReadTemperature((rtc)->chip, pTemp))
#define Rtc_ClearInterrupt(rtc)                 ((rtc)->ops->ClearInterrupt((rtc)->chip))
#define Rtc_SetAlarmTime(rtc, sec)              ((rtc)->ops->SetAlarmTime((rtc)->chip, sec))
#define Rtc_GetAlarmTime(rtc, sec)              ((rtc)->ops->GetAlarmTime((rtc)->chip, sec))
#define Rtc_WriteRamData(rtc, dat, offset, len) ((rtc)->ops->WriteRamData((rtc)->chip, dat, offset, len))
#define Rtc_ReadRamData(rtc, dat, offset, len)  ((rtc)->ops->ReadRamData((rtc)->chip, dat, offset, len))


#endif
