/**
 * \file ExternCanComm_LCfg.h
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
 * \addtogroup ExternCanComm 充电机通信
 * \{
 */


#ifndef EXTERNCANCOMM_LCFG_H_
#define EXTERNCANCOMM_LCFG_H_

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "ExternCanComm_Types.h"
#include "RelayM.h"

/**
 * \brief 数据长度可变
 */
#define EXTERNCANCOMM_DATA_LENGTH_NOT_FIX     0xFFFFU

#define EXTERNCANCOMM_IS_GB_TX_IPDU(IPDU)     ((IPDU) >= EXTERNCANCOMM_TX_IPDU_GB_START && (IPDU) <= EXTERNCANCOMM_TX_IPDU_GB_STOP)

/**
 * \brief 接收超时定义 ms
 */
#define EXTERNCANCOMMGB_REC_TIMEOUT_DEFAULT           5000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CHM               5000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CRM               55000U // + EXTERNCANCOMMGB_REC_TIMEOUT_CHM = 60000
#define EXTERNCANCOMMGB_REC_TIMEOUT_RECOMM_CRM        30000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CRM_AA            5000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CHM_TO_CRM        30000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CRO               5000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CRO_AA            60000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CCS               1000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CST               5000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CSD               10000U
#define EXTERNCANCOMMGB_REC_TIMEOUT_CEM               30000U


extern const ExternCanComm_ConfigType ExternCanComm_ConfigInfo;
extern const ExternCanComm_SendIPduCfgType ExternCanComm_IPduSendConfigInfo[];
extern const ExternCanComm_RecIPduCfgType ExternCanComm_IPduRecConfigInfo[EXTERNCANCOMM_STAGE_MAX];

#endif

/**
 * \}
 */
