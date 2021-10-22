/**
 * \file SoftwareTrigger.hx
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief XGate软件中断触发头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161228 |
 */


#include "Std_Types.h"
#include "App_Types.h"
#include "CellDataM.hx"

#ifndef SOFTWARETRIGGER_HX_
#define SOFTWARETRIGGER_HX_

#define XGATE_REC_DATA_INFO_BUFFER_SIZE     4

/**
 * \brief 协处理器电池数据类型
 */
 typedef uint8 XGateDataType;

/**
 * \brief 协处理器电池数据类型类型定义
 */
typedef enum{
    XGATE_CELL_DATA_TYPE_NONE, /**< 未知数据 */
    XGATE_CELL_DATA_TYPE_VOLTAGE, /**< 单体电压数据 */
    XGATE_CELL_DATA_TYPE_TEMPERATURE, /**< 电池温度数据 */
    XGATE_CELL_DATA_TYPE_COMMABORT, /**< 从机通信中断 */
}XGateDataTypeType;

/**
 * \brief 协处理器接收数据信息
 * \note 用于协处理器接收待处理电池数据缓存用
 */
#pragma push
#pragma align on

typedef struct{
    App_SlaveIdType Slave; /**< 从机号 */
    XGateDataTypeType Type; /**< 数据类型 */
    XGateDataType * near DataPtr; /**< 数据指针 */
    uint16 Length; /**< 数据长度 */
}XGateRecDataInfoType;

#pragma pop

extern XGateRecDataInfoType XGateRecDataInfoBuffer[XGATE_REC_DATA_INFO_BUFFER_SIZE];


extern void __X_XGateSoftTriggerHandler(uint16 dataptr);




#endif