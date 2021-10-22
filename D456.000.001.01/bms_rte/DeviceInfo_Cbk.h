/**
 * \file DeviceInfo_Cbk.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 设备信息类型回调函数头文件.
 *
 * 这里详细说明.
 *
 * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170214 |
 */

#ifndef DEVICE_INFO_CBK_H_
#define DEVICE_INFO_CBK_H_

#include "DeviceInfo.h"


/**
 * \brief HWID回调函数
 * \details 从主从CAN接收到从机反馈的HWID时可以使用该回调函数
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Length 数据长度
 */
void DeviceInfo_FeedbackNewHWIDIndication(App_SlaveIdType SlaveId, const uint8* DataPtr, uint16 Length);

/**
 * \brief FwVersion回调函数
 * \details 从主从CAN接收到从机反馈的FwVersion时可以使用该回调函数
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Length 数据长度
 */
void DeviceInfo_FeedbackNewFwVersionIndication(App_SlaveIdType SlaveId, const uint8* DataPtr, uint16 Length);




#endif