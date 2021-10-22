/**
 * \addtogroup CURRENT
 * \{
 */

#ifndef HALL_CBK_H
#define HALL_CBK_H

#include "Adc.h"
#include "Hall.h"

/**
 * \brief ADC层采集到HALL1传感器的电流值的回调函数.
 *
 * \param channel HALL通道.
 * \param v ADC采集值.
 */
void Hall_NewChannelSampleValue(Hall_ChannelType channel, Adc_ValueType v);

/**
 * \brief ADC层采集到HALL1传感器供电电压回调函数.
 *
 * \param channel HALL通道.
 * \param v ADC采集值.
 */
void Hall_NewChannelVolSupplyValue(Hall_ChannelType channel, Adc_ValueType v);

#endif

/** \} */