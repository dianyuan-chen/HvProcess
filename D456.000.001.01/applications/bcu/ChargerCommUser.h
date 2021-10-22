/**
 * \file ChargerCommUser.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 用户自定义充电机通信头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */

/**
 * \addtogroup ChargerCommUser 自定义充电机通信
 * \{
 */


#ifndef CHARGERCOMMUSER_H_
#define CHARGERCOMMUSER_H_

#include "App_Types.h"
#include "ChargerComm_Types.h"
#include "ChargeConnectM.h"
#include "ChargerCommGB.h"
#include "PduR_Lcfg.h"

#define CHARGERCOMMUSER_DEV_ERROR_DETECT        STD_OFF

#define CHARGERCOMMUSER_REC_TIMEOUT_DEFAULT     5000U

#if PDUR_CFG_CHARGERCOMM_PDUID_NUM > CHARGERCOMM_GB_CHR_TX_PDUID_NUM
#define CHARGERCOMM_USER_CHR_TX_PDUID_NUM       (PDUR_CFG_CHARGERCOMM_PDUID_NUM - CHARGERCOMM_GB_CHR_TX_PDUID_NUM)
#else
#define CHARGERCOMM_USER_CHR_TX_PDUID_NUM       0U
#endif

typedef struct{
    uint8 startFlag; /**< 启动标志 */
    uint8 communication; /**< 通信标志 */
    uint16 chargeTypeMask; /**< 充电类型位掩码 */
    Charge_ChargeType currentChargeType; /**< 当前连接充电类型 */
}ChargerCommUser_InnerDataType;


/**
 * \brief 用户自定义充电机模块初始化
 */
void ChargerCommUser_Init(void);

/**
 * \brief 设置当前用户自定义通信协议的充电类型
 *
 * \param type 充电类型 请参考 \link Charge_ChargeType \endlink
 */
void ChargerCommUser_SetChargeType(Charge_ChargeType type);

/**
 * \brief 用户自定义充电通信连接类型是否开启
 *
 * \return 详见请参考 \link Charge_ChargeType \endlink
 */
boolean ChargerCommUser_ChargeTypeIsOn(Charge_ChargeType type);

/**
 * \brief 用户自定义充电通信连接类型是否为空
 */
boolean ChargerCommUser_ChargeTypeIsNone(void);

/**
 * \brief 设置当前连接充电类型
 *
 * \param type 当前连接类型
 */
void ChargerCommUser_SetCurrentChargeType(Charge_ChargeType type);

/**
 * \brief 获取当前连接的充电类型
 */
Charge_ChargeType ChargerCommUser_GetCurrentChargeType(void);

/**
 * \brief 更新当前充电连接类型
 */
void ChargerCommUser_UpdateCurrentChargeType(void);

/**
 * \brief 启动用户自定义充电机通信
 * \note 开启充电机通信，未开启之前不会进行通信数据收发
 */
void ChargerCommUser_CommStart(void);

/**
 * \brief 停止用户自定义充电机通信
 * \note 停止用户自定义充电机通信，停止通信后不会进行通信数据收发
 */
void ChargerCommUser_CommStop(void);

/**
 * \brief 使能用户自定义充电机通信
 */
void ChargerCommUser_ChargerEnable(void);

/**
 * \brief 禁能用户自定义充电机通信
 */
void ChargerCommUser_ChargerDisable(void);

/**
 * \brief 用户自定义充电机通信是否启动
 */
uint8 ChargerCommUser_CommIsEnable(void);

/**
 * \brief 用户自定义充电通信状态设置
 *
 * \param flag 通信状态
 */
void ChargerCommUser_SetCommunication(uint8 flag);

/**
 * \brief 用户自定义充电通信状态获取
 *
 * \return 非0:正在通信 0:未通信
 */
uint8 ChargerCommUser_IsCommunication(void);

/**
 * \brief 启动新的接收阶段超时计时
 * \details 根据传入的接收阶段stage启动对应的所有接收报文的超时计时
 *
 * \param channel 通道号
 * \param currentStage 接收阶段
 */
void ChargerCommUser_StartRecStageTimeout(uint8 channel, ChargerComm_StageType currentStage);

/**
 * \brief 获取国标定义充电信号限制最大电流
 * \return 最大允许充电电流
 */
Current_CurrentType ChargerCommUser_GetGBSignalCurrentMax(void);

/**
 * \brief 自定义充电机通信启动
 */
void ChargerCommUser_ReceiveStageStart(void);

/**
 * \brief 自定义通信停止
 */
void ChargerCommUser_ReceiveStageStop(void);


#endif


/**
 * \}
 */