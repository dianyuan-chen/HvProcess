/**
 * \file VcuComm_messages.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 整车通信报文头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170316 |
 */
#ifndef VCUCOMM_MESSAGE_H_
#define VCUCOMM_MESSAGE_H_

#include "VcuComm.h"
#include "Diagnosis.h"


typedef Diagnosis_LevelType (*VcuComm_GetAlarmFuncPtr)(Diagnosis_ItemType index);

typedef struct {
    VcuComm_GetAlarmFuncPtr func;
    uint8 level;
    Diagnosis_ItemType item;
    uint8 code[5];
}VcuComm_FaultCodeTableType;

typedef struct {
    uint8 num;
    uint8 maxLevel;
    uint8 list[10];
}VcuComm_CodeDataType;
/**
 * \brief 整车通信高压上下电命令类型定义
 */
typedef enum{
    VCUCOMM_POWER_OFF, /**< 高压下电命令 */
    VCUCOMM_POWER_ON /**< 高压上电命令 */
}VcuComm_PowerCmdType;

/**
 * \整车通信报文数据
 */
typedef struct{
    VcuComm_PowerCmdType PowerCommand; /**< 高压上下电命令 */
    VcuComm_CodeDataType FaultCode;
    uint32 CmuTotalTime; /**< 累计使用时间 */
}VcuComm_MsgDataType;


extern VcuComm_MsgDataType VcuComm_MsgData;

/**
 * \brief 整车通信报文初始化
 */
void VcuComm_MessageInit(Async_LooperType *looper);

/**
 * \brief 获取整车通信发送报文的数据信息
 *
 * \param Buffer 数据缓存
 * \param Length 数据长度
 */
void VcuComm_GetMsgData0x1E1Cbk(uint8 *buf, uint16 *Length);
void VcuComm_GetMsgData0x1E2Cbk(uint8 *buf, uint16 *Length);
void VcuComm_GetMsgData0x1E3Cbk(uint8 *buf, uint16 *Length);
void VcuComm_GetMsgData0x1E4Cbk(uint8 *buf, uint16 *Length);
void VcuComm_GetMsgData0x1E5Cbk(uint8 *buf, uint16 *Length);
void VcuComm_GetMsgData0x1E6Cbk(uint8 *buf, uint16 *Length);
void VcuComm_GetMsgData0x1E7Cbk(uint8 *buf, uint16 *Length);


/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x1E1(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x1E4(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x1F5(uint8 *buf, uint16 *Length);
void VcuComm_GetStatusMsg_0x1F5_Excomm(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x1F3(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x211(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x352(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x353(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x354(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x355(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x356(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x357(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x3F3(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x3F4(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x3F5(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x3F6(uint8 *buf, uint16 *Length);
/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x3FF(uint8 *buf, uint16 *Length);

void VcuComm_GetStatusMsg_0x1F4(uint8 *buf, uint16 *Length);

//新增报文

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x201(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x360(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x361(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x358(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x202(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x203(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x204(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x205(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x206(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x207(uint8 *buf, uint16 *Length);

/**
 * \brief 参考UDAN.BMS整车协议
 */
void VcuComm_GetStatusMsg_0x208(uint8 *buf, uint16 *Length);

/**
 * \brief 接收超时处理回调函数
 */
void VcuComm_RecTimeoutCbk(void);


/**
 * \brief 发送整车报文1条件检查
 *
 * \return E_OK: 允许发送 E_NOT_OK: 不允许发送
 */
Std_ReturnType VcuComm_SendConditionCheck(uint16 IPdu);

/**
 * \brief 接收整车报文条件检查
 *
 * \return E_OK: 允许接收 E_NOT_OK: 不允许接收
 */
Std_ReturnType VcuComm_RecConditionCheck(void);

/**
 * \brief 整车接收报文处理
 *
 * \param Buffer 数据缓存
 * \param Length 数据长度
 */
void VcuComm_ReceiveCbk(uint8 *Buffer, uint16 Length);



#endif