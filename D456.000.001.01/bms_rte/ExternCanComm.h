/**
 * \file ExternCanComm.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 扩展CAN通信头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */

/**
 * \addtogroup ExternCanComm 扩展CAN通信
 * \{
 */


#ifndef EXTERNCANCOMM_H_
#define EXTERNCANCOMM_H_

#include "ExternCanComm_Internal.h"
#include "ChargeConnectM.h"
#include "HV.h"
#include "Current_Types.h"
#include "SystemConnection.h"


#define EXTERNCANCOMM_REC_TIMEOUT_DEFAULT         5000U
#define EXTERNCANCOMM_CHG_TIME_MAX                64800UL

/**
 * \brief 扩展CAN充电机状态类型定义
 */
typedef struct{
    Charge_ChargeType ChargeType; /**< 当前充电类型 */
    uint8 Protocol; /**< 通信协议 */
    uint8 ConnectStatus; /**< 充电机连接状态 */
    uint8 ChargingStatus; /**< 充电状态 */
    uint8 CommunicationStatus; /**< 充电机通信状态 */
    App_Tv100mvType ChargerOutputHV; /**< 当前输出总压 */
    Current_CurrentType ChargerOutputCurrent; /**< 当前输出电流 */
    uint16 ChargedTime; /**< 已充电时间 */
    uint16 RequireChargeTime; /**< 剩余充电时间 */
    App_Tv100mvType ChargerOutputHVMax; /**< 充电机最大输出总压 */
    App_Tv100mvType ChargerOutputHVMin; /**< 充电机最小输出总压 */
    Current_CurrentType ChargerOutputCurrentMax; /**< 充电机最大输出电流 */
    Current_CurrentType ChargerOutputCurrentMin; /**< 充电机最小输出电流 */
    uint8 CommAbortStatus; /**< 充电机通信中断状态 */
    uint16 ChargedPower; /**< 已充电能量 */
    uint8 ChargerFaultStatus[EXTERNCANCOMM_CHR_FAULT_STATUS_BUFF_NUM]; /**< 充电机异常状态 */
}ExternCanComm_ChargerStatusType;

/**
 * \brief 扩展CAN充电控制状态
 */
typedef struct{
    App_Tv100mvType ChargeVoltMax; /**< 最高允许充电总压 */
    Current_CurrentType ChargeCurrentMax; /**< 最高允许充电电流 */
}ExternCanComm_ChargeCtlType;

/**
 * \brief 充电机诊断状态类型定义
 */
typedef struct{
    Std_CommunicationFaultType Commfault; /**< 通信故障状态 */
}ExternCanComm_DiagnosisStatusType;


/**
 * \brief 扩展CAN通信模块初始化
 */
void ExternCanComm_Init(uint8 pri);

/**
 * \brief 扩展CAN通信是否已启动
 * \return FALSE-未启动 TRUE-已启动
 */
boolean ExternCanComm_IsStart(void);

/**
 * \brief 扩展CAN通信使能
 */
void ExternCanComm_ChargerEnable(void);

/**
 * \brief 扩展CAN通信禁能
 */
void ExternCanComm_ChargerDisable(void);

/**
 * \brief 设置当前扩展CAN充电类型
 */
void ExternCanComm_SetChargeType(Charge_ChargeType type);

/**
 * \brief 获取当前扩展CAN充电类型
 */
Charge_ChargeType ExternCanComm_GetChargeType(void);

/**
 * \brief 设置通信协议
 */
void ExternCanComm_SetProtocol(ExternCanComm_ProtocolType protocol);

/**
 * \brief 读取通信协议
 */
ExternCanComm_ProtocolType ExternCanComm_GetProtocol(void);

/**
 * \brief 设置当前扩展CAN充电状态
 */
void ExternCanComm_SetChargingStatus(uint8 status);

/**
 * \brief 获取当前扩展CAN充电状态
 * \return TRUE:充电中 FALSE:未充电
 */
uint8 ExternCanComm_GetChargingStatus(void);

/**
 * \brief 设置当前扩展CAN通信状态
 */
void ExternCanComm_SetCommunicationStatus(uint8 status);

/**
 * \brief 复位当前扩展CAN通信状态
 */
void ExternCanComm_ResetCommunicationStatus(void);

/**
 * \brief 获取当前扩展CAN通信状态
 * \return TRUE:通信中 FALSE:未通信
 */
uint8 ExternCanComm_GetCommunicationStatus(void);

/**
 * \brief 设置当前扩展CAN最高允许充电总压
 */
void ExternCanComm_SetChargeVoltMax(App_Tv100mvType voltage);

/**
 * \brief 获取当前扩展CAN最高允许充电总压
 */
App_Tv100mvType ExternCanComm_GetChargeVoltMax(void);

/**
 * \brief 设置当前扩展CAN最高允许充电电流
 */
void ExternCanComm_SetChargeCurrentMax(Current_CurrentType current);

/**
 * \brief 获取当前扩展CAN最高允许充电电流
 */
Current_CurrentType ExternCanComm_GetChargeCurrentMax(void);

/**
 * \brief 设置当前扩展CAN充电机输出总压
 */
void ExternCanComm_SetChargerOutputHV(App_Tv100mvType voltage);

/**
 * \brief 获取当前扩展CAN充电机输出总压
 */
App_Tv100mvType ExternCanComm_GetChargerOutputHV(void);

/**
 * \brief 设置当前扩展CAN充电机输出电流
 */
void ExternCanComm_SetChargerOutputCurrent(Current_CurrentType current);

/**
 * \brief 获取当前扩展CAN充电机输出电流
 */
Current_CurrentType ExternCanComm_GetChargerOutputCurrent(void);

/**
 * \brief 设置扩展CAN充电机最大输出总压
 */
void ExternCanComm_SetChargerOutputHVMax(App_Tv100mvType voltage);

/**
 * \brief 获取扩展CAN充电机最大输出总压
 */
App_Tv100mvType ExternCanComm_GetChargerOutputHVMax(void);

/**
 * \brief 设置扩展CAN充电机最小输出总压
 */
void ExternCanComm_SetChargerOutputHVMin(App_Tv100mvType voltage);

/**
 * \brief 获取扩展CAN充电机最小输出总压
 */
App_Tv100mvType ExternCanComm_GetChargerOutputHVMin(void);

/**
 * \brief 设置扩展CAN充电机最大输出电流
 */
void ExternCanComm_SetChargerOutputCurrentMax(Current_CurrentType current);

/**
 * \brief 获取扩展CAN充电机最大输出电流
 */
Current_CurrentType ExternCanComm_GetChargerOutputCurrentMax(void);

/**
 * \brief 设置扩展CAN充电机最小输出电流
 */
void ExternCanComm_SetChargerOutputCurrentMin(Current_CurrentType current);

/**
 * \brief 获取扩展CAN充电机最小输出电流
 */
Current_CurrentType ExternCanComm_GetChargerOutputCurrentMin(void);

/**
 * \brief 设置扩展CAN充电机已充电时间
 */
void ExternCanComm_SetChargerChargedTime(uint16 time);

/**
 * \brief 获取扩展CAN充电机已充电时间
 */
uint16 ExternCanComm_GetChargerChargedTime(void);

/**
 * \brief 设置扩展CAN充电机已充电能量
 */
void ExternCanComm_SetChargerChargedPower(uint16 power);

/**
 * \brief 获取扩展CAN充电机已充电能量
 */
uint16 ExternCanComm_GetChargerChargedPower(void);

/**
 * \brief 获取扩展CAN充电机状态信息
 * \note 包含充电机类型、连接状态、充电状态等信息 详见\link ExternCanComm_ChargerStatusType \endlink
 *
 * \param status 充电机状态信息
 */
void ExternCanComm_GetChargerStatus(ExternCanComm_ChargerStatusType *status);

/**
 * \brief 清除扩展CAN充电机状态信息
 */
void ExternCanComm_ClrChargerStatus(void);

/**
 * \brief 清除充电状态信息
 */
void ExternCanComm_ClrChargeStatus(void);

/**
 * \brief 故障诊断用扩展CAN通信中断
 * \return TRUE-中断 FALSE-正常
 */
uint16 ExternCanComm_DiagIsCommAbort(void);

/**
 * \brief 获取扩展CAN诊断状态信息
 *
 * \param status 获取到的诊断状态信息
 */
void ExternCanComm_GetDiagnosisStatus(ExternCanComm_DiagnosisStatusType *status);

/**
 * \brief 获取扩展CAN充电机通信状态
 * \note 根据不同的充电类型获取充电机通信状态，当类型为ALL时表示任一充电机通信时返回通信中
 *
 * \param ChargeType 充电机充电类型
 * \return E_NOT_OK:未通信 E_OK:正在通信
 */
Std_ReturnType ExternCanComm_ChargerIsCommunication(Charge_ChargeType ChargeType);

/**
 * \brief 初始化扩展CAN充电总压和电流
 */
void ExternCanComm_InitChargeVoltAndCurrent(void);

/**
 * \brief 通过索引设置扩展CAN充电故障状态
 *
 * \param num 充电机故障索引
 * \param flag 故障值
 *
 * \return 设置结果，成功返回E_OK
 */
Std_ReturnType ExternCanComm_SetChargeFaultWithIndex(ExternCanComm_ChargerFaultType num, uint8 flag);

/**
 * \brief 通过索引清除扩展CAN充电机故障状态
 *
 * \param num 充电机故障索引
 * \return 清除结果，成功返回E_OK
 */
Std_ReturnType ExternCanComm_ClearChargerFaultWithIndex(ExternCanComm_ChargerFaultType num);

/**
 * \brief 获取指定索引的扩展CAN充电机故障状态
 *
 * \param num 充电机故障索引
 * \return 故障状态 0-正常 1/2-故障 0xFF-复位状态（无故障）
 */
uint8 ExternCanComm_GetChargerFaultWithIndex(ExternCanComm_ChargerFaultType num);

/**
 * \brief 获取扩展CAN充电机所有故障状态位图
 *
 * \return 故障状态位图
 */
uint32 ExternCanComm_GetChargerFaultBitmap(void);

/**
 * \brief 清除扩展CAN充电机所有故障状态
 */
void ExternCanComm_ClrAllFaultStatus(void);

/**
 * \brief 获取扩展CAN充电机故障缓存大小
 */
uint8 ExternCanComm_GetChargerFaultBuffNum(void);

/**
 * \brief 通过扩展CAN充电机故障缓存编号获取充电机故障状态
 * \details 可以获取此缓存编号中保存的所有故障状态
 *
 * \param num 充电机故障缓存编号
 * \return 故障状态
 */
uint8 ExternCanComm_GetChargerFaultWithBuffNum(uint8 num);

/**
 * \brief 扩展CAN充电机是否故障（不包含充电机输入交流电压故障）
 * \return 故障返回TRUE,否则返回FALSE
 */
uint8 ExternCanComm_ChargerIsFaultWithNoInputVolt(void);

/**
 * \brief 扩展CAN充电机是否故障
 * \note 不包含正常充电结束相关状态，仅指充电机相关故障信息
 *
 * \return 故障返回TRUE,否则返回FALSE
 */
uint8 ExternCanComm_ChargerIsFault(void);

/**
 * \brief 根据充电类型获取当前类型的充电协议
 *
 * \param connectType 充电类型
 * \return 充电协议
 */
ExternCanComm_ProtocolType ExternCanComm_GetProtocolFromConnect(Charge_ChargeType connectType);

/**
 * \brief 获取充电电流差值
 * \details 在恒流充电模式下，计算充电控制电流和采样电流差；在恒压充电模式下，计算充电机实际输出电流和采样电流差。
 * \return 电流差
 */
uint16 ExternCanComm_DiagGetDeltaCurWithChr(void);

/**
 * \brief 是否为恒压充电状态
 * \details 根据最大允许充电总压和当前实际总压比较，确定当前是否应该进入恒压充电
 *
 * \return FALSE-是 TRUE-否
 */
boolean ExternCanComm_IsCVCharge(void);

/**
 * \brief 扩展CAN充电机通信状态是否为空闲状态
 * \details 即无快充通信也无慢充通信时为空闲状态
 *
 * \return FALSE-是 TRUE-否
 */
boolean ExternCanComm_IsIdle(void);


#endif


/**
 * \}
 */
