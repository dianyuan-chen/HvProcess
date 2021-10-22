/**
 * \file BalanceM_Cbk.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 均衡管理回调函数头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161207 |
 */

/**
 * \addtogroup BalanceM 均衡管理
 * \{
 */

#ifndef BALANCEM_CBK_H_
#define BALANCEM_CBK_H_

#include "BalanceM.h"
#include "InternalComm.h"

/**
 * \brief 从机均衡状态接收
 * \note 接收到的为从机当前实时的均衡状态，因从机均衡存在超时关闭功能，需要实时请求从机的均衡状态
 *
 * \param SlaveNum 从机号
 * \param DataPtr 数据缓存
 * \param Length 数据长度
 */
void BalanceM_RxBalanceNewStatusIndication(App_SlaveIdType SlaveNum, const uint8* DataPtr, uint16 Length);

/**
 * \brief 获取控制从机均衡状态控制数据回调函数
 * \details 通过从机号及DID将控制从机均衡状态的数据组包到DataBufferPtr中，并将组包的长度通过Length返回
 *
 * \param SlaveNum 从机号
 * \param Did 控制DID
 * \param DataBufferPtr 组包数据存放缓存
 * \param Length 返回实际组包长度
 */
void BalanceM_GetSlaveBalanceControlSendData_Cbk(App_SlaveIdType SlaveNum, InternalComm_DidTypes Did, InternalComm_MsgType DataBufferPtr, InternalComm_MsgLenType *Length);

/**
 * \brief 清除对应从机的均衡状态
 * \details 用于通信中断时清除从机的均衡状态
 *
 * \param SlaveNum 从机号
 */
void BalanceM_BalanceStatusClrIndication(App_SlaveIdType SlaveNum);

/**
 * \brief  均衡参数条件回调函数
 * \param[in]  type  均衡参数类型
 * \return     返回条件逻辑结果
 * \note       根据返回结果值决定使用哪一组均衡参数,其中充电均衡参数优先级较高
 */
boolean BalanceM_FirstCondition_Cbk(BalanceM_BalanceTypeType type);

/**
 * \brief      均衡故障条件回调函数
 * \param[in]  type  均衡参数类型
 * \return     根据返回结果值决定是否允许开启均衡
 * \note       根据相关设计文档,检查相应的故障状态,决定是否允许开启均衡
 */
boolean BalanceM_SecondCondition_Cbk(BalanceM_BalanceTypeType type);

#endif


/**
 * \}
 */