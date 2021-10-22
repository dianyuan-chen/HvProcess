#ifndef __SECOND_DATE_H__
#define __SECOND_DATE_H__

#include "Std_Types.h"

typedef struct  {
    /// 年, 从1表示 2001年.
    unsigned char year;
    /// 月, 1-12.
    unsigned char month;
    /// 日, 1-31.
    unsigned char day;
    /// 星期, 0-6.
    unsigned char weekday;
    /// 时, 0-23.
    unsigned char hour;
    /// 分, 0-59.
    unsigned char minute;
    /// 秒, 0-59.
    unsigned char second;
} Datetime_DatetimeType;

typedef unsigned long Datetime_SecondType;

Std_ReturnType Datetime_FromSecond(Datetime_DatetimeType *datetime, Datetime_SecondType second);
Std_ReturnType Datetime_ToSecond(const Datetime_DatetimeType *datetime, Datetime_SecondType *seconds);
boolean Datetime_IsValid(const Datetime_DatetimeType *datetime, boolean need_check_weekday);

#endif
