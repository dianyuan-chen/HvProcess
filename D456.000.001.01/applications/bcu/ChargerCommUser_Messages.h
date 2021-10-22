/**
 * \file ChargerCommUser_messages.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 自定义充电机通信报文头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170315 |
 */
#ifndef CHARGERCOMMUSER_MESSAGE_H_
#define CHARGERCOMMUSER_MESSAGE_H_

#include "ChargerCommUser.h"


typedef struct{
    boolean isNeedToSendStop; /**< 充电连接断开后，是否需要发送停止充电报文 */
}ChargerCommUser_MessageInnerDataType;

/**
 * \brief 用户自定义充电通信初始化
 */
void ChargerCommUser_MessageInit(void);

/**
 * \brief 用户自定义充电通信充电是否允许
 * \return E_OK: 允许 E_NOT_OK: 不允许
 */
Std_ReturnType ChargerCommUser_ChargeIsAllowed(void);

/**
 * \brief 发送TC报文条件检查
 *
 * \return E_OK: 允许发送 E_NOT_OK: 不允许发送
 */
Std_ReturnType ChargerCommUser_TCSendConditionCheck(void);

/**
 * \brief 获取TC发送的数据信息
 *
 * \param Buffer 数据缓存
 * \param Length 数据长度
 */
void ChargerCommUser_GetTCDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommUser_GetTC1DataCbk(uint8 *Buffer, uint16 *Length);

/**
 * \brief 用户自定义通信接收报文处理
 *
 * \param Buffer 数据缓存
 * \param Length 数据长度
 */
void ChargerCommUser_ReceiveTCCbk(const uint8 *Buffer, uint16 Length);

/**
 * \brief TC接收超时处理回调函数
 */
void ChargerCommUser_RecTCTimeoutCbk(void);



#endif