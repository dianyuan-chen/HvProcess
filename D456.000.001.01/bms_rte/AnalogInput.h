#ifndef ANALAGINPUT_H
#define ANALAGINPUT_H

#include "Std_Types.h"
#include "App_Types.h"
#include "AnalogInput_Cfg.h"

typedef struct {
    sint16 offset;
    sint16 mul;
    sint16 div;
} AnalogInput_ChannelConfigType;

void AnalogInput_NewAdcIndication(uint8 channel, uint16 adcv);
uint16 AnalogInput_Get(uint8 channel);

extern const AnalogInput_ChannelConfigType AnalogInput_ChannelConfigData[ANALOGINPUT_CHANNEL_NUM];


#endif