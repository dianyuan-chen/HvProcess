/**
 * \file ChargerComm_LCfg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电机通信链接配置头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */

/**
 * \addtogroup ChargerComm 充电机通信
 * \{
 */


#ifndef CHARGERCOMM_LCFG_H_
#define CHARGERCOMM_LCFG_H_

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "ChargerComm_Types.h"
#include "RelayM.h"

/**
 * \brief 数据长度可变
 */
#define CHARGERCOMM_DATA_LENGTH_NOT_FIX     0xFFFFU

#define CHARGERCOMM_IS_GB_TX_IPDU(IPDU)     ((IPDU) >= CHARGERCOMM_TX_IPDU_GB_START && (IPDU) <= CHARGERCOMM_TX_IPDU_GB_STOP)
#define CHARGERCOMM_IS_USER_TX_IPDU(IPDU)   ((IPDU) >= CHARGERCOMM_TX_IPDU_USER_START && (IPDU) <= CHARGERCOMM_TX_IPDU_USER_STOP)

/**
 * \brief 接收超时定义 ms
 */
#define CHARGERCOMMGB_REC_TIMEOUT_DEFAULT           5000U
#define CHARGERCOMMGB_REC_TIMEOUT_CHM               5000U
#define CHARGERCOMMGB_REC_TIMEOUT_CRM               55000U // + CHARGERCOMMGB_REC_TIMEOUT_CHM = 60000
#define CHARGERCOMMGB_REC_TIMEOUT_RECOMM_CRM        30000U
#define CHARGERCOMMGB_REC_TIMEOUT_CRM_AA            5000U
#define CHARGERCOMMGB_REC_TIMEOUT_CHM_TO_CRM        30000U
#define CHARGERCOMMGB_REC_TIMEOUT_CRO               5000U
#define CHARGERCOMMGB_REC_TIMEOUT_CRO_AA            60000U
#define CHARGERCOMMGB_REC_TIMEOUT_CCS               1000U
#define CHARGERCOMMGB_REC_TIMEOUT_CST               5000U
#define CHARGERCOMMGB_REC_TIMEOUT_CSD               10000U
#define CHARGERCOMMGB_REC_TIMEOUT_CEM               30000U

#define CHARGERCOMM_REC_TIMEOUT_USER                5000U

extern const ChargerComm_ConfigType ChargerComm_ConfigInfo;
extern const ChargerComm_SendIPduCfgType ChargerComm_IPduSendConfigInfo[];
extern const ChargerComm_RecIPduCfgType ChargerComm_IPduRecConfigInfo[CHARGERCOMM_STAGE_MAX];

#endif

/**
 * \}
 */
