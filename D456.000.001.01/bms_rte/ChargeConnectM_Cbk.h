/**
 * \file ChargeConnectM_Cbk.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电连接管理回调函数头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161207 |
 */

/**
 * \addtogroup ChargeConnectM 充电连接管理
 * \{
 */

#ifndef CHARGECONNECTM_CBK_H_
#define CHARGECONNECTM_CBK_H_

#include "ChargeConnectM.h"

/**
 * \brief ADC电压采集回调函数.
 * \details 当ADC采集到新的反馈电压值时, 可以调用该函数更新adc对应通道的状态.
 *
 * \param ChannelId 充电连接ADC通道.
 * \param adcValue ADC采集值.
 */
void ChargeConnectM_FeedbackNewAdcValueIndication(ChargeConnectM_CCxChannelType ChannelId, Adc_ValueType adcValue);


#endif


/**
 * \}
 */