/**
 * \file AnalogInput_Cbk.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 模拟输入头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170214 |
 */

#include "AnalogInput.h"

/**
 * \brief 模拟输入状态回调函数
 * \details 从主从CAN接收到从机模拟输入反馈的状态时可以使用该回调函数
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Length 数据长度
 */
void AnalogInput_FeedbackNewValueIndication(App_SlaveIdType SlaveId, const uint8* DataPtr, uint16 Length);
