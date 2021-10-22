/**
 * \file ChargerCommGB.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 国标充电机通信头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */

/**
 * \addtogroup ChargerCommGB 国标充电机通信
 * \{
 */


#ifndef CHARGERCOMMGB_H_
#define CHARGERCOMMGB_H_

#include "ChargerComm_Types.h"
#include "ChargeConnectM.h"
#include "ChargerComm.h"

#define CHARGERCOMMGB_DEV_ERROR_DETECT          STD_OFF

#define CHARGERCOMMGB_RELAY_ADHESION_CHECK_EN   STD_OFF

/**
 * \brief 报文优先级定义
 */
#define CHARGERCOMMGB_MESSAGE_PRI_DEFAULT       6U
#define CHARGERCOMMGB_BRO_PGN_2304_PRI          4U
#define CHARGERCOMMGB_BST_PGN_6400_PRI          4U
#define CHARGERCOMMGB_BEM_PGN_7680_PRI          2U

#define CHARGERCOMMGB_2015_BRM_PGN_PRI          7U
#define CHARGERCOMMGB_2015_BCP_PGN_PRI          7U
#define CHARGERCOMMGB_2015_BCS_PGN_PRI          7U
#define CHARGERCOMMGB_2015_BMV_PGN_PRI          7U
#define CHARGERCOMMGB_2015_BMT_PGN_PRI          7U
#define CHARGERCOMMGB_2015_BSP_PGN_PRI          7U

#define CHARGERCOMMGB_YEAR_OFFSET               1985U


#define CHARGERCOMM_GB_CHR_TX_PDUID_NUM         13U

/**
 * \brief 国标默认值定义
 */
#define CHARGERCOMMGB_BYTE_VALUE_DEFAULT        0xFFU
#define CHARGERCOMMGB_WORD_VALUE_DEFAULT        0xFFFFU
#define CHARGERCOMMGB_3_BYTES_VALUE_DEFAULT     0xFFFFFFU
#define CHARGERCOMMGB_LONG_VALUE_DEFAULT        0xFFFFFFFFU

#define CHARGERCOMMGB_CHG_UN_IDENT_NUM          0x00U
#define CHARGERCOMMGB_CHG_IDENTI_NUM            0xAAU

#define CHARGERCOMMGB_BMS_CHARGE_READY          0xAAU
#define CHARGERCOMMGB_BMS_CHARGE_NOT_READY      0x00U

#define CHARGERCOMMGB_REC_SPN2560_00_TIMEOUT_VALUE          0x01U
#define CHARGERCOMMGB_REC_SPN2560_00_UNKNOWN_VALUE          0x02U
#define CHARGERCOMMGB_REC_SPN2560_AA_TIMEOUT_VALUE          0x04U
#define CHARGERCOMMGB_REC_CAPABILITY_TIMEOUT_VALUE          0x01U
#define CHARGERCOMMGB_REC_CHARGER_READY_TIMEOUT_VALUE       0x04U
#define CHARGERCOMMGB_REC_CHARGER_READY_UNKNOWN_VALUE       0x08U
#define CHARGERCOMMGB_REC_CHARGER_STATUS_TIMEOUT_VALUE      0x01U
#define CHARGERCOMMGB_REC_CHARGER_STATUS_UNKNOWN_VALUE      0x02U
#define CHARGERCOMMGB_REC_CHARGER_STOP_TIMEOUT_VALUE        0x04U
#define CHARGERCOMMGB_REC_CHARGER_STOP_UNKNOWN_VALUE        0x08U
#define CHARGERCOMMGB_REC_CHARGER_STATIS_TIMEOUT_VALUE      0x01U

#define CHARGERCOMMGB_CURRENT_DECREASE_MAX_PER_S    200 // 0.1A/bit 电流降流步长

#define CHARGERCOMMGB_COMM_ABORT_TIMEOUT_TIMES      3U //认为是通信中断的超时次数
#define CHARGERCOMMGB_RELAY_ADHESION_CHECK_TIMEOUT  3000U //ms/bit 充电继电器粘连检测超时时间

#define CHARGERCOMMGB_CURRENT_OFFSET                CURRENT_100MA_FROM_A(400U) // 0.1A/bit国标电流偏移量
#define CHARGERCOMMGB_CELL_VOLT_MAX                 2400U //0.01V/bit 单体电压最大值

#define CHARGERCOMMGB_CHG_TIMEOUT_BYTE_NUM      4U
#define CHARGERCOMMGB_BMS_TIMEOUT_BYTE_NUM      4U

#define CHARGERCOMMGB_RECEIVE_TIMEOUT_EVENT_NUM 3U

#define CHARGERCOMMGB_CHARGE_TIME_MAX           600U //国标充电最大充电时间 min

/**
 * \brief 接收异步事件-充电阶段切换，启动计时
 */
#define CHARGERCOMMGB_REC_EVENT_TYPE_STAGE      0U
/**
 * \brief 接收异步事件-接到成功，更新计时
 */
#define CHARGERCOMMGB_REC_EVENT_TYPE_RECEIVE    1U

#define CHARGERCOMMGB_STOP_CHARGE_DEV_NONE      0U
#define CHARGERCOMMGB_STOP_CHARGE_DEV_CHARGER   1U
#define CHARGERCOMMGB_STOP_CHARGE_DEV_BMS       2U


/**
 * \brief 国标通信协议版本类型定义
 */
typedef enum{
    CHARGERCOMMGB_PROTOCOL_VERSION_2011 = 0x100,
    CHARGERCOMMGB_PROTOCOL_VERSION_2015 = 0x101
}ChargerCommGB_PortocolVersionType;

typedef enum{
    CHARGERCOMMGB_COMM_STATE_IDLE,
    CHARGERCOMMGB_COMM_STATE_SENDING,
    CHARGERCOMMGB_COMM_STATE_RECEIVING,
    CHARGERCOMMGB_COMM_STATE_INDICATION,
    CHARGERCOMMGB_COMM_STATE_PROCESSING,
}ChargerCommGB_CommStateType;

typedef enum{
    CHARGERCOMMGB_STAGE_CONNECT_WAITING, /**< 等待硬件连接阶段 */
    CHARGERCOMMGB_STAGE_SHAKEHAND_START, /**< 握手启动阶段 */
    CHARGERCOMMGB_STAGE_SHAKEHAND_IDENTIFY, /**< 握手辨识阶段 */
    CHARGERCOMMGB_STAGE_PARA_CONFIG, /**< 参数配置阶段 */
    CHARGERCOMMGB_STAGE_CHARGE_READY, /**< 充电准备就绪阶段 */
    CHARGERCOMMGB_STAGE_CHARGING, /**< 充电阶段 */
    CHARGERCOMMGB_STAGE_CHARGE_STOP, /**< 中止充电阶段 */
    CHARGERCOMMGB_STAGE_STATISTIC, /**< 充电统计阶段 */
    CHARGERCOMMGB_STAGE_FAULT, /**< 故障阶段 */
    CHARGERCOMMGB_STAGE_END, /**< 充电结束阶段 */
    CHARGERCOMMGB_STAGE_MAX
}ChargerCommGB_ChargeStageType;

/**
 * \brief 国标通信消息数据信息类型定义
 */
typedef struct{
    uint8 *dataBufferPtr;
    uint16 availableSize;
}ChargerCommGB_MsgDataInfoType;

typedef struct{
    uint8 startFlag; /**< 启动标志 */
    uint8 stopFlag; /**< 启动是否需要停止标志 */
    boolean insuIsStop; /**< 绝缘检测是否控制关闭 */
    uint8 communication; /**< 通信状态 */
    uint16 chargeTypeMask; /**< 充电类型位掩码 */
    Charge_ChargeType currentChargeType; /**< 当前连接的充电类型 */
    ChargerCommGB_PortocolVersionType protocolVersion; /**< 通信版本 */
    ChargerCommGB_ChargeStageType stage; /**< 充电阶段 */
    ChargerComm_SelfDiagnosisType selfDiag; /**< 自检状态 */
    uint8 timeoutCntSwitch; /**< 通信超时计数开关 */
    uint8 timeoutCnt; /**< 通信超时计数 */
    uint8 bmsChargeReady; /**< BMS充电准备就绪 */
    uint32 bmsChargeReadyLastTick; /**< BMS充电准备就绪计时 */
    uint8 bmsChargeReadySendFlag; /**< BMS充电准备就绪发送标志 */
    Current_CurrentType chargeCurrentLast; /**< 上次充电电流 */
    uint32 chargeCurrentLastTick; /**< 充电电流更新计时 */
    uint8 bmsTimeoutReason[CHARGERCOMMGB_BMS_TIMEOUT_BYTE_NUM]; /**< BMS通信中断原因 */
    uint8 bmsStopReason; /**< bms停止充电原因 */
    uint16 bmsFaultReason; /**< bms中止充电故障原因 */
    uint8 bmsErrorReason; /**< bms中止充电错误原因 */
    uint8 chargerStopReason; /**< charger停止充电原因 */
    uint16 chargerFaultReason; /**< charger中止充电故障原因 */
    uint8 chargerErrorReason; /**< charger中止充电错误原因 */
    uint32 chargeStopLastTick; /**< 停止充电计时 */
    uint8 relayAdhesionCheckFlag; /**< 充电继电器粘连检测标志 */
    uint8 bclZeroCurSendFlag; /**< BCL报文0电流发送标志 */
    uint8 ccsRecFlag; /**< 充电机CCS报文接收标志 */
    uint8 stopChargeDev; /**< 停止充电设备 0-无 1-充电机 2-BMS */
    uint8 bcsChargeStopSendFlag; /**< 停止充电前BCS报文发送标志 */
    uint8 bstSendCnt; /**< BST报文发送计数 */
    uint32 bemCurDecreaseLastTick; /**< 通信超时阶段电流下降计时 */
    uint8 chargerTimeoutReason[CHARGERCOMMGB_CHG_TIMEOUT_BYTE_NUM]; /**< 充电机通信中断原因 */
    Async_EventType recTimeoutEvent[CHARGERCOMMGB_RECEIVE_TIMEOUT_EVENT_NUM]; /**< 接收超时事件个数 */
    uint8 cellVoltGroupNum; /**< 单体电压组号 */
}ChargerCommGB_InnerDataType;

/**
 * \brief 国标充电机模块初始化
 */
void ChargerCommGB_Init(void);

/**
 * \brief 国标充电机通信当前充电类型
 * \details 详见请参考 \link Charge_ChargeType \endlink
 *
 * \param type 充电类型
 */
void ChargerCommGB_SetChargeType(Charge_ChargeType type);

/**
 * \brief 使能国标充电机通信
 */
void ChargerCommGB_ChargerEnable(void);

/**
 * \brief 获取当前连接的充电类型
 */
Charge_ChargeType ChargerCommGB_GetCurrentChargeType(void);

/**
 * \brief 禁能国标充电机通信
 */
void ChargerCommGB_ChargerDisable(void);

/**
 * \brief 国标充电机通信是否启动
 */
uint8 ChargerCommGB_CommIsStart(void);

/**
 * \brief 获取国标充电机自诊断状态
 *
 * \return 参考\link ChargerComm_SelfDiagnosisType \endlink
 */
ChargerComm_SelfDiagnosisType ChargerCommGB_GetSelfDiagnosis(void);

/**
 * \brief 国标充电通信状态获取
 *
 * \return 非0:正在通信 0:未通信
 */
uint8 ChargerCommGB_IsCommunication(void);

/**
 * \brief 报文发送条件检查
 *
 * \return E_OK: 允许发送 E_NOT_OK: 不允许发送
 */
Std_ReturnType ChargerCommGB_BHMSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BRMSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BCPSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BROSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BCLSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BCSSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BSMSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BMVSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BMTSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BSTSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BSDSendConditionCheck(void);
Std_ReturnType ChargerCommGB_BEMSendConditionCheck(void);

/**
 * \brief 获取发送报文的数据信息
 *
 * \param Buffer 数据缓存
 * \param Length 数据长度
 */
void ChargerCommGB_GetBHMDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBRMDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBCPDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBRODataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBCLDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBCSDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBSMDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBMVDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBMTDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBSTDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBSDDataCbk(uint8 *Buffer, uint16 *Length);
void ChargerCommGB_GetBEMDataCbk(uint8 *Buffer, uint16 *Length);

/**
 * \brief 国标通信CHM接收报文处理
 *
 * \param Buffer 数据缓存
 * \param Length 数据长度
 */
void ChargerCommGB_ReceiveCHMCbk(const uint8 *Buffer, uint16 Length);
void ChargerCommGB_ReceiveCRMCbk(const uint8 *Buffer, uint16 Length);
void ChargerCommGB_ReceiveCTSCbk(const uint8 *Buffer, uint16 Length);
void ChargerCommGB_ReceiveCMLCbk(const uint8 *Buffer, uint16 Length);
void ChargerCommGB_ReceiveCROCbk(const uint8 *Buffer, uint16 Length);
void ChargerCommGB_ReceiveCCSCbk(const uint8 *Buffer, uint16 Length);
void ChargerCommGB_ReceiveCSTCbk(const uint8 *Buffer, uint16 Length);
void ChargerCommGB_ReceiveCSDCbk(const uint8 *Buffer, uint16 Length);
void ChargerCommGB_ReceiveCEMCbk(const uint8 *Buffer, uint16 Length);

/**
 * \brief 接收超时处理回调函数
 */
void ChargerCommGB_RecCHMTimeoutCbk(void);
void ChargerCommGB_RecCRMTimeoutCbk(void);
void ChargerCommGB_RecCMLTimeoutCbk(void);
void ChargerCommGB_RecCROTimeoutCbk(void);
void ChargerCommGB_RecCROAATimeoutCbk(void);
void ChargerCommGB_RecCCSTimeoutCbk(void);
void ChargerCommGB_RecCSTTimeoutCbk(void);
void ChargerCommGB_RecCSDTimeoutCbk(void);


/**
 * \brief 启动新的接收阶段超时计时
 * \details 根据传入的接收阶段stage启动对应的所有接收报文的超时计时
 *
 * \param channel 通道号
 * \param currentStage 接收阶段
 */
void ChargerCommGB_StartRecStageTimeout(uint8 channel, ChargerComm_StageType currentStage);

/**
 * \brief 检查是否当前允许充电
 *
 * \param delay 不允许充电延时时间
 * \return 0-waitting 1-ready 2-fault
 */
uint8 ChargerCommGB_CheckChargeReq(uint16 delay);

/**
 * \brief 是否为故障停止充电
 * \details 非正常充电结束均为故障停止充电，正常充电结束如单体高压、总压高、满充等
 * \return TRUE-是 FALSE-否
 */
uint8 ChargerCommGB_ChargeIsFaultStop(void);

#endif


/**
 * \}
 */