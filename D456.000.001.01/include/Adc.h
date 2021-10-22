/**
 * \addtogroup autosar AUTOSAR兼容
 * \{
 * \addtogroup ADC ADC驱动
 * \{
 */
#ifndef ADC_H_
#define ADC_H_

#include "Std_Types.h"


typedef uint16 Adc_ValueType;
typedef uint16 Adc_ValueGroupType;

/** Group status. */
typedef enum {
    ADC_IDLE,
    ADC_BUSY,
    ADC_COMPLETED,
    ADC_STREAM_COMPLETED,
} Adc_StatusType;

/*
 * Std-types
 *
 */
/** Access mode to group conversion results. */
typedef enum {
    ADC_ACCESS_MODE_SINGLE,
    ADC_ACCESS_MODE_STREAMING
} Adc_GroupAccessModeType;

/** Group trigger source. */
typedef enum {
    ADC_TRIGG_SRC_HW,
    ADC_TRIGG_SRC_SW,
} Adc_TriggerSourceType;

/** HW trigger edge. */
typedef enum {
    ADC_NO_HW_TRIG,
    ADC_HW_TRIG_BOTH_EDGES,
    ADC_HW_TRIG_FALLING_EDGE,
    ADC_HW_TRIG_RISING_EDGE,
} Adc_HwTriggerSignalType;

/** Stream buffer type. */
typedef enum {
    ADC_NO_STREAMING,
    ADC_STREAM_BUFFER_CIRCULAR,
    ADC_STREAM_BUFFER_LINEAR,
} Adc_StreamBufferModeType;

typedef struct {
    uint8               notifictionEnable;
    Adc_ValueGroupType  *resultBufferPtr;
    Adc_StatusType      groupStatus;
} Adc_GroupStatus;

#include "Adc_Cfg.h"
#include "Adc_Types.h"


/* Function interface. */
/** Initializes the ADC hardware units and driver. */
void Adc_Init (const Adc_ConfigType *ConfigPtr);
/** Returns all ADC HW Units to a state comparable to their power on reset state. */
void Adc_DeInit (void);

/** Sets up the result buffer for a group. */
Std_ReturnType Adc_SetupResultBuffer (Adc_GroupType group, Adc_ValueGroupType *bufferPtr);
/** Starts the conversion of all channels of the requested ADC Channel group. */
void Adc_StartGroupConversion (Adc_GroupType group);
void Adc_StopGroupConversion (Adc_GroupType group);

void Adc_GroupConversionComplete (uint8 group);

/** Reads results from last conversion into buffer */
Std_ReturnType Adc_ReadGroup (Adc_GroupType group, Adc_ValueGroupType *dataBufferPtr);

/** Enables the notification mechanism for the requested ADC Channel group. */
void Adc_EnableGroupNotification (Adc_GroupType group);
/** Disables the notification mechanism for the requested ADC Channel group. */
void Adc_DisableGroupNotification (Adc_GroupType group);

/** Returns the conversion status of the requested ADC Channel group. */
Adc_StatusType Adc_GetGroupStatus (Adc_GroupType group);

void ADT0_Isr(void);
void ADT1_Isr(void);
void dump_adt(void);

#endif /*ADC_H_*/

/**
 * \}
 * \}
 */
