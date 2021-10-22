/**
 * \file ChargerComm_LCfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电机通信链接配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */


#include "ChargerComm.h"
#include "ChargerCommGB.h"
#include "ChargerCommUser_Messages.h"
#include "PduR_Types.h"
#include "ChargerComm_LCfg.h"
#include "SystemConnection_Lcfg.h"

const uint8 ChargerComm_SendIPduNum = PDUR_CHARGERCOMM_TX_PDUID_NUM; //todo
const uint8 ChargerComm_RecIPduNum = PDUR_CHARGERCOMM_RX_PDUID_NUM; //todo
const ChargerComm_SendIPduCfgType ChargerComm_IPduSendConfigInfo[] = {
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BHM, /**< IPdu */
        2U, /**< Length */
        250U, /**< Cycle */
        ChargerCommGB_BHMSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBHMDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BRM, /**< IPdu */
        41U, /**< Length */
        250U, /**< Cycle */
        ChargerCommGB_BRMSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBRMDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BCP, /**< IPdu */
        13U, /**< Length */
        500U, /**< Cycle */
        ChargerCommGB_BCPSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBCPDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BRO, /**< IPdu */
        1U, /**< Length */
        250U, /**< Cycle */
        ChargerCommGB_BROSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBRODataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BCL, /**< IPdu */
        5U, /**< Length */
        50U, /**< Cycle */
        ChargerCommGB_BCLSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBCLDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BCS, /**< IPdu */
        9U, /**< Length */
        250U, /**< Cycle */
        ChargerCommGB_BCSSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBCSDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BSM, /**< IPdu */
        7U, /**< Length */
        250U, /**< Cycle */
        ChargerCommGB_BSMSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBSMDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BMV, /**< IPdu */
        CHARGERCOMM_DATA_LENGTH_NOT_FIX, /**< Length */
#if SYSTEM_BATTERY_CELL_NUM < 256U
        10000U, /**< Cycle */
#else
        10000U / ((SYSTEM_BATTERY_CELL_NUM + 255U) / 256U), /**< Cycle */
#endif
        ChargerCommGB_BMVSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBMVDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BMT, /**< IPdu */
        CHARGERCOMM_DATA_LENGTH_NOT_FIX, /**< Length */
        10000U, /**< Cycle */
        ChargerCommGB_BMTSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBMTDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BSP, /**< IPdu */
        CHARGERCOMM_DATA_LENGTH_NOT_FIX, /**< Length */
        10000U, /**< Cycle */
        NULL, /**< CondFunc */
        NULL, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BST, /**< IPdu */
        4U, /**< Length */
        10U, /**< Cycle */
        ChargerCommGB_BSTSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBSTDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BSD, /**< IPdu */
        7U, /**< Length */
        250U, /**< Cycle */
        ChargerCommGB_BSDSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBSDDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_GB_BEM, /**< IPdu */
        4U, /**< Length */
        250U, /**< Cycle */
        ChargerCommGB_BEMSendConditionCheck, /**< CondFunc */
        ChargerCommGB_GetBEMDataCbk, /**< Func */
    },

    {
        PDUR_CHARGERCOMM_TX_PDUID_USER_TC, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        ChargerCommUser_TCSendConditionCheck, /**< CondFunc */
        ChargerCommUser_GetTCDataCbk, /**< Func */
    },
    {
        PDUR_CHARGERCOMM_TX_PDUID_USER_TC1, /**< IPdu */
        8U, /**< Length */
        1000U, /**< Cycle */
        NULL, /**< CondFunc */
        ChargerCommUser_GetTC1DataCbk, /**< Func */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageIdleRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        CHARGERCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_USER_TC, /**< IPdu */
        8U,
        CHARGERCOMM_REC_TIMEOUT_USER, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommUser_ReceiveTCCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBCommWaitingRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        CHARGERCOMMGB_REC_TIMEOUT_CHM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCHMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBChmToCrmRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_CHM_TO_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        CHARGERCOMMGB_REC_TIMEOUT_CHM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBCrmRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        CHARGERCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBRecommCrmRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_RECOMM_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        CHARGERCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBCrmAARecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_CRM_AA, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_CRM_AA, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        NULL, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCRMTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBCtsCmlRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CTS, /**< IPdu */
        7U,
        CHARGERCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCTSCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CML, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCMLCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCMLTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBCroRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRO, /**< IPdu */
        1U,
        CHARGERCOMMGB_REC_TIMEOUT_CRO, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCROCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCROTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRO, /**< IPdu */
        1U,
        CHARGERCOMMGB_REC_TIMEOUT_CRO_AA, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        NULL, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCROAATimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBCcsRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CCS, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_CCS, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCCSCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCCSTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CST, /**< IPdu */
        4U,
        CHARGERCOMMGB_REC_TIMEOUT_CST, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCSTCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBCstCsdRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CST, /**< IPdu */
        4U,
        CHARGERCOMMGB_REC_TIMEOUT_CST, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCSTCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCSTTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CSD, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_CSD, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCSDCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommGB_RecCSDTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBCemRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CEM, /**< IPdu */
        4U,
        CHARGERCOMMGB_REC_TIMEOUT_CEM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCEMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageGBFullChargeItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CRM, /**< IPdu */
        8U,
        CHARGERCOMMGB_REC_TIMEOUT_RECOMM_CRM, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCRMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
    {
        PDUR_CHARGERCOMM_RX_PDUID_GB_CHM, /**< IPdu */
        3U,
        CHARGERCOMMGB_REC_TIMEOUT_DEFAULT, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommGB_ReceiveCHMCbk, /**< RecFunc: 数据接收回调函数 */
        NULL, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

static const ChargerComm_RecIPduInfoType ChargerComm_StageUserTCRecItem[] = {
    {
        PDUR_CHARGERCOMM_RX_PDUID_USER_TC, /**< IPdu */
        8U,
        CHARGERCOMM_REC_TIMEOUT_USER, /**< Timeout: 接收超时时间 */
        NULL, /**< TimeoutFunc: 获取IPdu接收超时时间回调函数 */
        ChargerCommUser_ReceiveTCCbk, /**< RecFunc: 数据接收回调函数 */
        ChargerCommUser_RecTCTimeoutCbk, /**< TimeoutEventFunc: 数据接收超时事件回调函数 */
    },
};

/**
 * \brief 充电机通信接收报文配置
 * \note 第一个为空，用于无充电机通信状态使用
 */
const ChargerComm_RecIPduCfgType ChargerComm_IPduRecConfigInfo[CHARGERCOMM_STAGE_MAX] = {
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageIdleRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageIdleRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBCommWaitingRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBCommWaitingRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBChmToCrmRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBChmToCrmRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBCrmRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBCrmRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBRecommCrmRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBRecommCrmRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBCrmAARecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBCrmAARecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBCtsCmlRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBCtsCmlRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBCroRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBCroRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBCcsRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBCcsRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBCstCsdRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBCstCsdRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBCemRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBCemRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageGBFullChargeItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageGBFullChargeItem, /**< IPduInfo: 各IPdu配置信息 */
    },
    {
        (uint8)ARRAY_SIZE(ChargerComm_StageUserTCRecItem), /**< IPduNum: 报文个数 */
        ChargerComm_StageUserTCRecItem, /**< IPduInfo: 各IPdu配置信息 */
    },
};
