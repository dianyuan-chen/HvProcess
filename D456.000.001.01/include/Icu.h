/**
 * \addtogroup autosar
 * \{
 * \addtogroup ICU Input Capture Unit 驱动
 * \{
 */

#ifndef ICU_H
#define ICU_H

#include "Std_Types.h"
#include "Icu_Types.h"

typedef enum {
    ICU_MODE_NORMAL,
    ICU_MODE_SLEEP,
} Icu_ModeType;

typedef enum {
    ICU_ACTIVE,
    ICU_IDLE,
} Icu_InputStateType;

typedef enum {
    ICU_RISING_EDGE,
    ICU_FALLING_EDGE,
    ICU_BOTH_EDGES,
} Icu_ActivationType;

typedef uint Icu_ValueType;

typedef struct {
    Icu_ValueType ActiveTime;
    Icu_ValueType PeriodTime;
} Icu_DutyCycleType;


typedef enum {
    ICU_MODE_SIGNAL_EDGE_DETECT,
    ICU_MODE_SIGNAL_MEASUREMENT,
    ICU_MODE_TIMESTAMP,
    ICU_MODE_EDGE_COUNTER,
} Icu_MeasurementModeType;

typedef enum {
    ICU_LOW_TIME,
    ICU_HIGH_TIME,
    ICU_PERIOD_TIME,
    ICU_DUTY_CYCLE,
} Icu_SignalMeasurementPropertyType;

typedef enum {
    ICU_LINEAR_BUFFER,
    ICU_CIRCULAR_BUFFER,
} Icu_TimestampBufferType;

void Icu_Init(const Icu_ConfigType *ConfigPtr);
void Icu_DeInit(void);
void Icu_SetMode(Icu_ModeType Mode);
void Icu_DisableWakeup(Icu_ChannelType Channel);
void Icu_EnableWakeup(Icu_ChannelType Channel);

//todo: "How this impl"
//void Icu_CheckWakeup(EcuM_WakeupSourceType WakeupSource);

void Icu_SetActivationCondition(Icu_ChannelType Channel, Icu_ActivationType Activation);
void Icu_DisableNotification(Icu_ChannelType Channel);
void Icu_EnableNotification(Icu_ChannelType Channel);
Icu_InputStateType Icu_GetInputState(Icu_ChannelType Channel);
void Icu_StartTimestamp(Icu_ChannelType Channel, Icu_ValueType *BufferPtr, uint16 BufferSize, uint16 NotifyInterval);
void Icu_StopTimestamp(Icu_ChannelType Channel);
Icu_IndexType Icu_GetTimestampIndex(Icu_ChannelType Channel);
void Icu_ResetEdgeCount(Icu_ChannelType Channel);
void Icu_EnableEdgeCount(Icu_ChannelType Channel);
void Icu_DisableEdgeCount(Icu_ChannelType Channel);
Icu_EdgeNumberType Icu_GetEdgeNumbers(Icu_ChannelType Channel);
void Icu_EnableEdgeDetection(Icu_ChannelType Channel);
void Icu_DisableEdgeDetection(Icu_ChannelType Channel);
void Icu_StartSignalMeasurement(Icu_ChannelType Channel);
void Icu_StopSignalMeasurement(Icu_ChannelType Channel);
void Icu_GetDutyCycleValues(Icu_ChannelType Channel, Icu_DutyCycleType* DutyCycleValues);
Icu_ValueType Icu_GetTimeEscaped(Icu_ChannelType Channel);

#endif

/**
 * \}
 * \}
 */
