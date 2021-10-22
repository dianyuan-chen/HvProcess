/**
 * \file ExternCanComm_LCfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 扩展CAN通信链接配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */


#include "ExternCanComm.h"
#include "ExternCanCommGB.h"
#include "PduR_Types.h"
#include "ExternCanComm_LCfg.h"
#include "SystemConnection_Lcfg.h"
#include "VcuComm_Messages.h"

const uint8 ExternCanComm_SendIPduNum = PDUR_EXTERNCANCOMM_TX_PDUID_NUM; //todo
const uint8 ExternCanComm_RecIPduNum = PDUR_EXTERNCANCOMM_RX_PDUID_NUM; //todo
const ExternCanComm_SendIPduCfgType ExternCanComm_IPduSendConfigInfo[] = {
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BHM, /**< IPdu */
        2U, /**< Length */
        250U, /**< Cycle */
        ExternCanCommGB_BHMSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBHMDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BRM, /**< IPdu */
        41U, /**< Length */
        250U, /**< Cycle */
        ExternCanCommGB_BRMSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBRMDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BCP, /**< IPdu */
        13U, /**< Length */
        500U, /**< Cycle */
        ExternCanCommGB_BCPSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBCPDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BRO, /**< IPdu */
        1U, /**< Length */
        250U, /**< Cycle */
        ExternCanCommGB_BROSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBRODataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BCL, /**< IPdu */
        5U, /**< Length */
        50U, /**< Cycle */
        ExternCanCommGB_BCLSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBCLDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BCS, /**< IPdu */
        9U, /**< Length */
        250U, /**< Cycle */
        ExternCanCommGB_BCSSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBCSDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BSM, /**< IPdu */
        7U, /**< Length */
        250U, /**< Cycle */
        ExternCanCommGB_BSMSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBSMDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BMV, /**< IPdu */
        EXTERNCANCOMM_DATA_LENGTH_NOT_FIX, /**< Length */
#if SYSTEM_BATTERY_CELL_NUM < 256U
        10000U, /**< Cycle */
#else
        10000U / ((SYSTEM_BATTERY_CELL_NUM + 255U) / 256U), /**< Cycle */
#endif
        ExternCanCommGB_BMVSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBMVDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BMT, /**< IPdu */
        EXTERNCANCOMM_DATA_LENGTH_NOT_FIX, /**< Length */
        10000U, /**< Cycle */
        ExternCanCommGB_BMTSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBMTDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BSP, /**< IPdu */
        EXTERNCANCOMM_DATA_LENGTH_NOT_FIX, /**< Length */
        10000U, /**< Cycle */
        NULL, /**< CondFunc */
        NULL, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BST, /**< IPdu */
        4U, /**< Length */
        10U, /**< Cycle */
        ExternCanCommGB_BSTSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBSTDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BSD, /**< IPdu */
        7U, /**< Length */
        250U, /**< Cycle */
        ExternCanCommGB_BSDSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBSDDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_GB_BEM, /**< IPdu */
        4U, /**< Length */
        250U, /**< Cycle */
        ExternCanCommGB_BEMSendConditionCheck, /**< CondFunc */
        ExternCanCommGB_GetBEMDataCbk, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_1E1, /**< IPdu */
        8U, /**< Length */
        100U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x1E1, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_1E4, /**< IPdu */
        8U, /**< Length */
        100U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x1E4, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_1F3, /**< IPdu */
        8U, /**< Length */
        100U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x1F3, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_1F5, /**< IPdu */
        8U, /**< Length */
        100U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x1F5_Excomm, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_360, /**< IPdu */
        8U, /**< Length */
        100U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x360, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_361, /**< IPdu */
        8U, /**< Length */
        100U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x361, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_208, /**< IPdu */
        8U, /**< Length */
        100U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x208, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_351, /**< IPdu */
        8U, /**< Length */
        100U, /**< Cycle */
        NULL, /**< CondFunc */
        NULL, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_358, /**< IPdu */
        8U, /**< Length */
        200U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x358, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_352, /**< IPdu */
        8U, /**< Length */
        200U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x352, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_353, /**< IPdu */
        8U, /**< Length */
        200U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x353, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_354, /**< IPdu */
        8U, /**< Length */
        200U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x354, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_355, /**< IPdu */
        8U, /**< Length */
        200U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x355, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_3F6, /**< IPdu */
        8U, /**< Length */
        200U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x3F6, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_211, /**< IPdu */
        8U, /**< Length */
        500U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x211, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_1F4, /**< IPdu */
        8U, /**< Length */
        500U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x1F4, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_356, /**< IPdu */
        8U, /**< Length */
// #if 3000U/SYSTEM_BATTERY_CELL_NUM > 1000UL
        1000U, /**< Cycle */
// #else
//         3000U/SYSTEM_BATTERY_CELL_NUM, /**< Cycle */
// #endif
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x356, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_357, /**< IPdu */
        8U, /**< Length */
// #if 6000U/SYSTEM_TEMP_CELL_NUM > 1000UL
        1000U, /**< Cycle */
// #else
//         6000U/SYSTEM_TEMP_CELL_NUM, /**< Cycle */
// #endif
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x357, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_3F3, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x3F3, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_3F4, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        NULL, //VcuComm_GetStatusMsg_0x3F4, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_3F5, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x3F5, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_3FF, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x3FF, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_201, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x201, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_202, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x202, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_205, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x205, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_206, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x206, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_207, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x207, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_203, /**< IPdu */
        8U, /**< Length */
        2000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x203, /**< Func */
    },
    {
        PDUR_EXTERNCANCOMM_TX_PDUID_204, /**< IPdu */
        8U, /**< Length */
        2000U, /**< Cycle */
        NULL, /**< CondFunc */
        VcuComm_GetStatusMsg_0x204, /**< Func */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageIdleRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        EXTERNCANCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBCommWaitingRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CHM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCHMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBChmToCrmRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CHM_TO_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CHM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBCrmRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        EXTERNCANCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBRecommCrmRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_RECOMM_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        EXTERNCANCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBCrmAARecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CRM_AA, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CRM_AA, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        NULL, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBCtsCmlRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CTS, /**< IPdu */
        7U,
        EXTERNCANCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCTSCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CML, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCMLCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCMLTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBCroRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRO, /**< IPdu */
        1U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CRO, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCROCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCROTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CRO, /**< IPdu */
        1U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CRO_AA, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        NULL, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCROAATimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBCcsRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CCS, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CCS, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCCSCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCCSTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CST, /**< IPdu */
        4U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CST, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCSTCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBCstCsdRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CST, /**< IPdu */
        4U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CST, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCSTCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCSTTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CSD, /**< IPdu */
        8U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CSD, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCSDCbk, /**< RecFunc: 数据接收回调函数 */
        ExternCanCommGB_RecCSDTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ExternCanComm_RecIPduInfoType ExternCanComm_StageGBCemRecItem[] = {
    {
        PDUR_EXTERNCANCOMM_RX_PDUID_GB_CEM, /**< IPdu */
        4U,
        EXTERNCANCOMMGB_REC_TIMEOUT_CEM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ExternCanCommGB_ReceiveCEMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

/**
 * \brief 扩展CAN通信接收报文配置
 * \note 第一个为空，用于无扩展CAN通信状态使用
 */
const ExternCanComm_RecIPduCfgType ExternCanComm_IPduRecConfigInfo[EXTERNCANCOMM_STAGE_MAX] = {
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageIdleRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageIdleRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBCommWaitingRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBCommWaitingRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBChmToCrmRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBChmToCrmRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBCrmRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBCrmRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBRecommCrmRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBRecommCrmRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBCrmAARecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBCrmAARecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBCtsCmlRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBCtsCmlRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBCroRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBCroRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBCcsRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBCcsRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBCstCsdRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBCstCsdRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ExternCanComm_StageGBCemRecItem), /**< IPduNum: 报文个数 */
        ExternCanComm_StageGBCemRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
};
