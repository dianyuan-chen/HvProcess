/**
 * \addtogroup CURRENT
 * \{
 */
#ifndef HALL_H_
#define HALL_H_

#include "Current_Types.h"
#include "Hall_Cfg.h"
#include "Adc.h"

typedef uint8 Hall_ChannelType;

typedef struct {
    sint16 offset;
    sint16 mul;
    sint16 div;
    uint8 filterNum;
    uint8 dropNum;
    uint16 voltMin; /**< 电流电压最小值 */
    uint16 voltMax; /**< 电流电压最大值 */
    uint16 (*getSupplyVol)(void); /**< 获取霍尔供电电压的函数, 用于增益校准 */
    boolean supplyVolAjd; /**< 是否需要去除供电影响 */
    boolean isReverse; /**< 是否反向 */
} Hall_ConfigType;

typedef enum {
    HALL_DIAGNOSIS_OK,
    HALL_DIAGNOSIS_SENSOR_OPEN_CIRCUIT,
    HALL_DIAGNOSIS_SENSOR_SHORT_CIRCUIT,
    HALL_DIAGNOSIS_SUPPLY_VOLTAGE_ERR,
} Hall_StatusType;

void Hall_Init(const Hall_ConfigType *cfg);

Current_CurrentType Hall_GetCurrent(Hall_ChannelType channel);
Current_CurrentType Hall_GetCurrentCalibrated(Hall_ChannelType channel);
Std_ReturnType Hall_WaitCurrent(Hall_ChannelType channel, Current_TimedCurrentType *current, uint16 timeout);
Std_ReturnType Hall_WaitCurrentCalibrated(Hall_ChannelType channel, Current_TimedCurrentType *current, uint16 timeout);

sint16 Hall_GetSampleVoltage(Hall_ChannelType channel);

void Hall_SetCalibrateParam(Hall_ChannelType channel, const Current_SensorCalibrateParam *param);
void Hall_GetCalibrateParam(Hall_ChannelType channel, Current_SensorCalibrateParam *param);
void Hall_SyncCalibrate(Hall_ChannelType channel);

Hall_StatusType Hall_GetDiagnosisStatus(Hall_ChannelType channel);

#endif

/** \} */
