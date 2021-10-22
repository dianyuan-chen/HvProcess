#ifndef ADC_TYPES_H_
#define ADC_TYPES_H_

#include "derivative.h"


/** ID of group */
typedef uint8 Adc_GroupType;

#define ADC_GROUP_ADT0    0U
#define ADC_GROUP_ADT1    1U
#define ADC_NBR_OF_GROUPS 2U

typedef enum {
    ADC_CH0,
    ADC_CH1,
    ADC_CH2,
    ADC_CH3,
    ADC_CH4,
    ADC_CH5,
    ADC_CH6,
    ADC_CH7,
    ADC_CH8,
    ADC_CH9,
    ADC_CH10,
    ADC_CH11,
    ADC_CH12,
    ADC_CH13,
    ADC_CH14,
    ADC_CH15,
    ADC_NBR_OF_CHANNELS,
} Adc_ChannelType;

/* Std-type, supplier defined */
typedef enum {
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_2,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_4,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_6,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_8,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_10,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_12,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_14,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_16,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_18,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_20,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_22,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_24,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_26,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_28,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_30,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_32,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_34,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_36,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_38,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_40,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_42,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_44,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_46,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_48,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_50,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_52,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_54,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_56,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_58,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_60,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_62,
    ADC_SYSTEM_CLOCK_DIVIDE_FACTOR_64,
} Adc_PrescaleType;

/* Std-type, supplier defined */
typedef enum {
    ADC_SAMPLE_TIME_4_CLOCKS,
    ADC_SAMPLE_TIME_6_CLOCKS,
    ADC_SAMPLE_TIME_8_CLOCKS,
    ADC_SAMPLE_TIME_10_CLOCKS,
    ADC_SAMPLE_TIME_12_CLOCKS,
    ADC_SAMPLE_TIME_16_CLOCKS,
    ADC_SAMPLE_TIME_20_CLOCKS,
    ADC_SAMPLE_TIME_24_CLOCKS
} Adc_SampleTimeType;

typedef enum {
    ADC_RESOLUTION_8_BIT = 0,
    ADC_RESOLUTION_10_BIT = 1,
    ADC_RESOLUTION_12_BIT = 2,
} Adc_ResolutionType;


/* Channel definitions, std container */
typedef struct {
    Adc_PrescaleType prescale;
    Adc_ResolutionType resolution;
    // NOT SUPPORTED Adc_VoltageSourceType  adcChannelRefVoltSrcLow;
    // NOT SUPPORTED Adc_VoltageSourceType  adcChannelRefVoltSrcHigh;
    // NOT SUPPORTED Adc_ResolutionType     adcChannelResolution;
    // NOT SUPPORTED Adc_CalibrationType    adcChannelCalibrationEnable;
} Adc_ChannelConfigurationType;


/* Std-type, supplier defined */
typedef enum {
    ADC_CONV_MODE_DISABLED,
    ADC_CONV_MODE_ONESHOT,
    ADC_CONV_MODE_CONTINUOUS,
} Adc_GroupConvModeType;

typedef struct {
    uint8 CTL0;
    uint8 CTL1;
    uint8 CTL2;
    uint8 CTL3;
    uint8 CTL4;
    uint8 CTL5;
    uint8 STAT0;
    uint8 Reserved;
    uint16 CMPE;
    uint16 STAT1;
    uint16 DIEN;
    uint16 CMPHT;
    uint16 DR[16];
} Adc_HwRegisterType;

typedef struct {
    Adc_HwRegisterType *near hwreg;
    uint8 CTL0;
    uint8 CTL1;
    uint8 CTL2;
    uint8 CTL3;
    uint8 CTL4;
    uint8 CTL5;
    void (*hwTrggerControl)(uint8 isEnable);
    void (*groupCallback)(void);
} Adc_GroupConfigType;

typedef struct {
    const Adc_GroupConfigType *cfg;
    Adc_ValueGroupType *resultBuffer;
    uint16 numberOfChannels;
} Adc_GroupDefType;


typedef struct {
    uint8 groupNum;
    Adc_GroupDefType *groupDefPtr;
} Adc_ConfigType;

extern const Adc_ConfigType AdcConfig;
extern const Adc_ConfigType AdcConfig_0b101;
#endif /* ADC_CONFIGTYPES_H_ */
