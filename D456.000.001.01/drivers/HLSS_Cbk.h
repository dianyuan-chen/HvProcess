/**
 * \addtogroup HLSSDriver
 * \{ */

#ifndef HLSS_CBK_H
#define HLSS_CBK_H

#include "HLSS.h"
#include "InternalComm.h"

/**
 * \brief 电流采集回调函数.
 * \details 当ADC采集到新的反馈电流值时, 可以调用该函数更新高低边驱动的内部诊断状态.
 *
 * \param ChannelId 高低边驱动通道.
 * \param adcValue ADC采集值.
 *
 * \note 主机板内高低边开关使用该回调函数.
 */
void HLSS_FeedbackNewCurrentAdcValueIndication(HLSS_ChannelType ChannelId, Adc_ValueType adcValue);

/**
 * \brief 电压采集回调函数.
 * \details 当ADC采集到新的反馈电压值时, 可以调用该函数更新高低边驱动的内部诊断状态.
 *
 * \param ChannelId 高低边驱动通道.
 * \param adcValue ADC采集值.
 *
 * \note 主机板内高低边开关使用该回调函数.
 */
void HLSS_FeedbackNewVoltageAdcValueIndication(HLSS_ChannelType ChannelId, Adc_ValueType adcValue);


/**
 * \brief 电流采集回调函数.
 * \details 从主从CAN接收到从机高边开关反馈电流时可以使用该回调函数.
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Voltage 数据长度
 *
 * \note 主机板内高低边开关使用该回调函数.
 */
void HLSS_FeedbackNewCurrentValueIndication(App_SlaveIdType SlaveId, const uint8* DataPtr, uint16 Length);

/**
 * \brief 电压采集回调函数.
 * \details 从主从CAN接收到从机高边开关反馈电压时可以使用该回调函数.
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Voltage 数据长度
 *
 * \note 主机板内高低边开关使用该回调函数.
 */
void HLSS_FeedbackNewVoltageValueIndication(App_SlaveIdType SlaveId, const uint8* DataPtr, uint16 Length);

/**
 * \brief 开关驱动状态回调函数
 * \details 从主从CAN接收到从机高边开关反馈的驱动状态时可以使用该回调函数
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Length 数据长度
 */
void HLSS_FeedbackNewDriveStatusIndication(App_SlaveIdType SlaveId, const uint8* DataPtr, uint16 Length);

/**
 * \brief 清除对应从机的HLSS反馈电流值
 * \details 用于通信中断时清除从机HLSS的反馈电流值
 *
 * \param SlaveId 从机号
 */
void HLSS_CurrentValueClrIndication(App_SlaveIdType SlaveId);

/**
 * \brief 清除对应从机的HLSS反馈电压值
 * \details 用于通信中断时清除从机HLSS的反馈电压值
 *
 * \param SlaveId 从机号
 */
void HLSS_VoltageValueClrIndication(App_SlaveIdType SlaveId);

/**
 * \brief 清除对应从机的HLSS的开关驱动状态
 * \details 用于通信中断时清除从机HLSS的开关状态
 *
 * \param SlaveId 从机号
 */
void HLSS_DriveStatusClrIndication(App_SlaveIdType SlaveId);

/**
 * \brief 获取控制从机HLSS驱动状态控制数据回调函数
 * \details 通过从机号及DID将控制从机HLSS驱动状态的数据组包到DataBufferPtr中，并将组包的长度通过Length返回
 *
 * \param SlaveNum 从机号
 * \param Did 控制DID
 * \param DataBufferPtr 组包数据存放缓存
 * \param Length 返回实际组包长度
 */
void HLSS_GetDriveSlaveHlssSendData_Cbk(App_SlaveIdType SlaveNum, InternalComm_DidTypes Did, InternalComm_MsgType DataBufferPtr, InternalComm_MsgLenType *Length);

#endif

/** \} */
