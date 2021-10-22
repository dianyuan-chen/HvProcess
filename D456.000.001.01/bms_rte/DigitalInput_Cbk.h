/**
 * \addtogroup DigitalInput
 * \{
 */
#ifndef DIGITALINPUT_CBK_H
#define DIGITALINPUT_CBK_H

#include "DigitalInput.h"

/**
 * \brief 数字开关输入状态回调函数
 * \details 从主从CAN接收到从机数字判刑输入反馈的状态时可以使用该回调函数
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Length 数据长度
 */
void DigitalInput_FeedbackNewSWValueIndication(App_SlaveIdType SlaveId, const uint8* DataPtr, uint16 Length);

/**
 * \brief 数字电平输入状态回调函数
 * \details 从主从CAN接收到从机数字电平输入反馈的状态时可以使用该回调函数
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Length 数据长度
 */
void DigitalInput_FeedbackNewDINValueIndication(App_SlaveIdType SlaveId, const uint8* DataPtr, uint16 Length);


#endif

/** \} */