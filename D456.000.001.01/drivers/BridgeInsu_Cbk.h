#ifndef BRIDGE_INSU_CBK_H
#define BRIDGE_INSU_CBK_H

#include "Adc.h"

typedef enum {
    BRIDGEINSU_POS_ADC_CHANNEL,
    BRIDGEINSU_NEG_ADC_CHANNEL,
} BridgeInsu_AdcChannelType;

void BridgeInsu_NewAdcValueIndication(Adc_ValueGroupType posValue, Adc_ValueGroupType negValue);

#endif