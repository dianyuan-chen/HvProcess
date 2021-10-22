/**
 * \file VcuComm_Types.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 整车通信类型定义头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170316 |
 */

/**
 * \addtogroup VcuComm 整车通信
 * \{
 */


#ifndef VCUCOMM_TYPES_H_
#define VCUCOMM_TYPES_H_

/**
 * \brief 整车通信IPdu类型定义
 * \notes 发送报文优先
 */
typedef enum _VcuComm_IPduType{
    //TX IPDU
    VCUCOMM_TX_IPDU_START = 0,
    VCUCOMM_TX_IPDU_MSG_0x1E1 = VCUCOMM_TX_IPDU_START, /**< 整车通信发送0x1801FFF4报文IPdu */
    VCUCOMM_TX_IPDU_MSG_0x1E2 = 1, /**< 整车通信发送0x1802FFF4报文IPdu */
    VCUCOMM_TX_IPDU_MSG_0x1E3 = 2, /**< 整车通信发送0x1803FFF4报文IPdu */
    VCUCOMM_TX_IPDU_MSG_0x1E4 = 3, /**< 整车通信发送0x1804FFF4报文IPdu */
    VCUCOMM_TX_IPDU_MSG_0x1E5 = 4, /**< 整车通信发送0x1807FFF4报文IPdu */
    VCUCOMM_TX_IPDU_MSG_0x1E6 = 5, /**< 整车通信发送0x1801D2F4报文IPdu*/
    VCUCOMM_TX_IPDU_MSG_0x1E7 = 6, /**< 整车通信发送0x1802D2F4报文IPdu*/
    VCUCOMM_TX_IPDU_STOP = VCUCOMM_TX_IPDU_MSG_0x1E7,

    //RX IPDU
    VCUCOMM_RX_IPDU_START = 7,
    VCUCOMM_RX_IPDU_MSG_0x12345678 = VCUCOMM_RX_IPDU_START, /**< 整车通信接收0x12345678报文IPdu */
    VCUCOMM_RX_IPDU_STOP = VCUCOMM_RX_IPDU_MSG_0x12345678,

    VCUCOMM_IPDU_INVALID = 0xFF, /**< 无效IPDU */
}VcuComm_IPduType;


typedef enum _VcuComm_StageType{
    VCUCOMM_STAGE_IDLE = 0, /**< 空闲状态 */

    VCUCOMM_STAGE_START = 1,
    VCUCOMM_STAGE_STAGE1 = VCUCOMM_STAGE_START, /**< 整车通信 */
    VCUCOMM_STAGE_STOP = VCUCOMM_STAGE_STAGE1,

    VCUCOMM_STAGE_MAX = 2
}VcuComm_StageType;


#endif



/**
 * \}
 */