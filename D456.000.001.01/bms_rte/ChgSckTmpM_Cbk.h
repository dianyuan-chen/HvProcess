/**
 * \file ChgSckTmpM_Cbk.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电插座温度管理回调函数头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161207 |
 */

/**
 * \addtogroup ChgSckTmpM 充电插座温度管理
 * \{
 */

#ifndef CHGSCKTMPM_CBK_H_
#define CHGSCKTMPM_CBK_H_

#include "ChgSckTmpM.h"

/**
 * \brief 充电插座温度采集回调函数
 * \note 完成新ADC温度采集后通过此回调函数更新对应充电插座温度值
 *
 * \param ChannelId 充电插座温度通道
 * \param adcValue ADC采样值
 */
void ChgSckTmpM_FeedbackTemperatureNewIndication(ChgSckTmpM_AdcChannelType ChannelId, Adc_ValueType adcValue);


#endif

/**
 * \}
 */
