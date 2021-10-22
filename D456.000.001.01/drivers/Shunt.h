/**
 * \addtogroup CURRENT
 * \{
 */
#ifndef SHUNT_H
#define SHUNT_H

#include "Current_Types.h"
#include "Async_Looper.h"
#include "CS5490.h"
#include "Shunt_Cfg.h"

#define VOLTAGE_CONST  5000000UL

typedef struct {
    uint16 resistor; // 0.1微欧姆
    uint16 tempDrift;
    uint32 maxVol; // 最大电压
    boolean isReverse; // 是否反向
} Shunt_SensorConfigType;

typedef struct {
    CS5490_DeviceType *cs5490;
    Dio_ChannelType interruptPin;
    void (*newChipTemperatureIndication)(uint8 temp);
    // uint16 averageCurrentSampleTimes; // 采集多少次读取一次平均电流
} Shunt_ConfigType;

#define SHUNT_DIAGNOSIS_OK                0x00U
#define SHUNT_DIAGNOSIS_NO_INIT           0x01U
#define SHUNT_DIAGNOSIS_COMMULICATION_ERR 0x02U
#define SHUNT_DIAGNOSIS_OVER_TEMPERATURE  0x04U
#define SHUNT_DIAGNOSIS_NTC_OFFLINE       0x08U
#define SHUNT_DIAGNOSIS_STOPED            0x10U
#define SHUNT_DIAGNOSIS_OVER_CURRENT      0x20U

void Shunt_Init(Async_LooperType *looper, uint16 gainErr);
void Shunt_Irq(void);

Current_CurrentType Shunt_GetCurrent(void);
Std_ReturnType Shunt_WaitCurrent(Current_TimedCurrentType *current, uint16 timeout);
Current_CurrentType Shunt_GetCurrentCalibrated(void);
Std_ReturnType Shunt_WaitCurrentCalibrated(Current_TimedCurrentType *current, uint16 timeout);

uint8 Shunt_GetTemperature(void);

void Shunt_SetCalibrateParam(const Current_SensorCalibrateParam *param);
void Shunt_GetCalibrateParam(Current_SensorCalibrateParam *param);
void Shunt_SyncCalibrate(void);
uint8 Shunt_GetDiagnosisStatus(void);
Std_ReturnType Shunt_SetGainErr(uint16 gainErr);
uint16 Shunt_GetGainErr(void);
void CS5490_LcfgIrqEnable(boolean isEnable);
void Shunt_DumpVoltageuV(void);
void shunt_dump(void);

extern const Shunt_ConfigType ShuntConfigData;
extern const Shunt_SensorConfigType ShuntSensorConfig;

#endif

/** \} */
