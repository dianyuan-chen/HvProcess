/**
 * \file ChargeM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170221 |
 */

/**
 * \addtogroup ChargeM 充电管理
 * \{
 */

#ifndef CHARGEM_H_
#define CHARGEM_H_

#include "App_Types.h"
#include "Charge_Types.h"
#include "Diagnosis.h"

#define CHARGEM_CHARGERGB_CTL_BUFFER_SIZE           1U
#define CHARGEM_DIAGNOSIS_CTL_BUFFER_SIZE           ((DIAGNOSIS_ITEM_DEFAULT_NUM + 7U) / 8U)
#define CHARGEM_START_DIAG_CTL_BUFFER_SIZE          ((DIAGNOSIS_ITEM_DEFAULT_NUM + 3U) / 4U)
#define CHARGEM_OTHERS_FAULT_CTL_BUFFER_SIZE        10U

#define CHARGEM_START_DIAG_USE_BIT_NUM              2U
#define CHARGEM_START_DIAG_MASK_NUM                 3U
#define CHARGEM_START_DIAG_NUM_IN_BYTE              (8U/CHARGEM_START_DIAG_USE_BIT_NUM)
#define CHARGEM_START_DIAG_STATUS_DEFAULT           0xFFU


typedef uint8 ChargeM_OthersFaultIndexType;
#define CHARGEM_OTHERS_FAULT_INVALID    0xFFU

/**
 * \brief 国标准备就绪项
 *
 * \note 仅用于国标定义的充电准备就绪项定义，此定义不作为充电故障
 */
typedef enum{
    CHARGEM_CHARGERGB_READY_RELAY_INDEX, /**< 国标充电机充电BMS充电准备就绪 */
    CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX, /**< DC2国标充电机充电BMS充电准备就绪 */
}ChargeM_ChargerGBReadyIndexType;

/**
 * \brief 充电控制类型类型定义
 */
typedef enum{
    CHARGEM_CHARGE_ENABLE = 0, /**< 允许充电 */
    CHARGEM_CHARGE_DISABLE = 1, /**< 不允许充电 */
}ChargeM_CtlTypeType;

/**
 * \brief 充电控制配置参数类型定义
 */
typedef struct{
    uint8 enable; /**< 使能控制 */
    uint16 chargeTimeMax; /**< 最大允许充电时间 分辨率：1h/bit */
}ChargeM_ConfigParaType;

/**
 * \brief 充电管理链接配置参数类型定义
 */
typedef struct{
    ChargeM_ConfigParaType AC_Para; /**< 交流充电参数 */
    ChargeM_ConfigParaType DC_Para; /**< 直流充电参数 */
}ChargeM_ConfigInfoType;

typedef struct{
    uint8 flag; /**< 控制状态 */
    uint8 action; /**< 动作状态 */
}ChargeM_CtlInfoType;

typedef struct{
    Async_EventType event;
    uint8 chargerGBCtl[CHARGEM_CHARGERGB_CTL_BUFFER_SIZE]; /**< 国标充电机充电控制 */
    ChargeM_CtlInfoType diagnosisCtl[CHARGEM_DIAGNOSIS_CTL_BUFFER_SIZE]; /**< 故障诊断充电控制 */
    uint8 startDiagCtl[CHARGEM_START_DIAG_CTL_BUFFER_SIZE]; /**< 上电自检诊断充电控制 */
    uint8 othersFaultCtl[CHARGEM_OTHERS_FAULT_CTL_BUFFER_SIZE]; /**< 其他故障充电控制 */

    uint8 diagnosisCtlMask[CHARGEM_DIAGNOSIS_CTL_BUFFER_SIZE]; /**< 故障诊断充电控制掩码 */
    uint8 startDiagCtlMask[CHARGEM_START_DIAG_CTL_BUFFER_SIZE]; /**< 上电自检诊断充电控制掩码 */
}ChargeM_InnerDataType;

/**
 * \brief 配置参数变量声明
 */
extern const ChargeM_ConfigInfoType ChargeM_ConfigInfo;

/**
 * \brief 充电管理模块初始化
 */
void ChargeM_Init(Async_LooperType *looper);

/**
 * \brief 根据配置初始化当前充电模式下的最大允许充电电压和电流参数
 */
void ChargeM_InitChargeVoltAndCurrent(void);

/**
 * \brief 当前是否允许充电
 * \details 除充电机未进行通信外是否有其他故障不允许充电，不区分充电类型;
 *          因国标快充要求进入充电就绪阶段后才闭合充电继电器（若为快充连接状态），结束充电时，
 *          断开充电继电器，所以此接口仅检查存在充电相关故障，不检查国标快充是否进入充电就绪阶段
 *
 * \return E_OK: 允许 E_NOT_OK:不允许
 */
Std_ReturnType ChargeM_ChargeIsAllowed(void);

/**
 * \brief 当前充电是否就绪
 * \details 检查是否有充电故障且国标快充是否进入就绪阶段（若为快充连接状态），
 *          与ChargeM_ChargeIsAllowed仅增加对国标快充就绪阶段的检查
 *
 * \return E_OK: 允许 E_NOT_OK:不允许
 */
Std_ReturnType ChargeM_ChargeIsReady(void);

/**
 * \brief 当前充电故障动作是否已经成立
 * \details 检查包含禁止充电的故障，也包含国标快充定义的结束充电时（若为快充连接状态），进入国标快充未就绪状态
 *
 * \return E_OK: 故障动作已成立 E_NOT_OK: 未成立
 */
Std_ReturnType ChargeM_ChargeIsFault(void);

/**
 * \brief 排除指定诊断项后当前充电故障动作是否已经成立
 * \details 检查包含禁止充电的故障，也包含国标快充定义的结束充电时（若为快充连接状态），进入国标快充未就绪状态
 *
 * \param item 指定要排除的诊断项
 * \return E_OK: 故障动作已成立 E_NOT_OK: 未成立
 */
Std_ReturnType ChargeM_ChargeIsFaultExcludeItem(Diagnosis_ItemType item);

/**
 * \brief 获取充电控制上电自检故障码
 * \details 未自检完成前返回无故障
 *
 * \return 上电自检诊断故障码 返回DIAGNOSIS_ITEM_INVALID_INDEX为无故障
 */
Diagnosis_ItemType ChargeM_GetStartDiagFault(void);

/**
 * \brief 充电上电自检是否正常允许充电
 * \return E_OK: 允许 E_NOT_OK: 不允许
 *
 * \note 此函数需要配置上电自检完成
 */
Std_ReturnType ChargeM_StartDiagIsNormal(void);

/**
 * \brief 充电上电自检排除指定诊断项序列后是否允许故障
 *
 * \param item 诊断项序列
 * \param length 序列长度
 *
 * \return E_OK: 故障 E_NOT_OK: 无故障
 */
Std_ReturnType ChargeM_StartDiagIsFaultExcludeItems(const Diagnosis_ItemType *item, uint8 length);

/**
 * \brief 获取充电控制诊断标志故障码
 * \details 此标志故障码是引起停止充电机充电的故障，不一定是断开继电器的故障
 *
 * \return 诊断故障 返回DIAGNOSIS_ITEM_INVALID_INDEX为无故障
 */
Diagnosis_ItemType ChargeM_GetDiagFaultFlag(void);

/**
 * \brief 获取充电控制诊断动作故障码
 * \details 此故障码是引起停止充电且充电继电器断开的故障
 *
 * \return 诊断故障 返回DIAGNOSIS_ITEM_INVALID_INDEX为无故障
 */
Diagnosis_ItemType ChargeM_GetDiagFaultAction(void);

/**
 * \brief 国标充电机充电控制是否允许充电
 *
 * \return E_OK:允许充电  E_NOT_OK:不允许充电
 */
Std_ReturnType ChargeM_ChargerGBIsReady(void);

/**
 * \brief 获取国标充电机充电控制故障码
 * \return 故障码 返回-1为无故障
 */
uint16 ChargeM_GetChargerGBReadyFault(void);

/**
 * \brief 故障诊断充电控制是否允许充电
 *
 * \return E_OK:允许充电  E_NOT_OK:不允许充电
 */
Std_ReturnType ChargeM_DiagnosisIsNormal(void);

/**
 * \brief 故障诊断充电故障动作是否已成立
 * \details 此函数用于确认是否有诊断故障需要断充电高压
 * \return E_OK:成立 E_NOT_OK:未成立
 */
Std_ReturnType ChargeM_DiagnosisIsFaultAction(void);

/**
 * \brief 排除某一故障后故障诊断充电故障动作是否已成立
 * \details 此函数用于确认排除某一故障后是否有诊断故障需要断充电高压
 * \return E_OK:成立 E_NOT_OK:未成立
 */
Std_ReturnType ChargeM_DiagnosisIsFaultActionExcludeItem(Diagnosis_ItemType item);

/**
 * \brief 排除指定诊断项序列后当前充电故障标志是否成立
 * \details 此函数用于确认排除多个故障后是否有诊断故障需要禁止充电
 *
 * \param item 诊断项序列
 * \param length 诊断项个数
 *
 * \return E_OK:成立 E_NOT_OK:未成立
 */
Std_ReturnType ChargeM_DiagnosisIsFaultFlagExcludeItems(const Diagnosis_ItemType *item, uint8 length);

/**
 * \brief 设置国标充电控制状态
 * \details 通过此函数可设置国标充电时进行充电启停的控制状态
 *
 * \param item 诊断项
 * \param ctl 控制方式 CHARGEM_CHARGE_ENABLE：允许充电 CHARGEM_CHARGE_DISABLE：不允许充电
 */
void ChargeM_SetChargerGBReadyStatus(ChargeM_ChargerGBReadyIndexType item, ChargeM_CtlTypeType ctl);

/**
 * \brief 获取国标充电对充电的控制状态
 *
 * \param item 国标充电控制项
 * \return CHARGEM_CHARGE_ENABLE：允许充电 CHARGEM_CHARGE_DISABLE：不允许充电
 */
ChargeM_CtlTypeType ChargeM_GetChargerGBReadyStatus(ChargeM_ChargerGBReadyIndexType item);

/**
 * \brief 同时设置故障诊断充电控制标志及动作
 * \details 通过此函数可设置发生诊断故障时进行充电启停的控制标志及动作，同时会影响由ChargeM_ChargeIsFault为E_OK，
 *          且ChargeM_ChargeIsAllowed为E_NOT_OK
 *
 * \param item 诊断项
 * \param ctl 控制方式 CHARGEM_CHARGE_ENABLE：允许充电 CHARGEM_CHARGE_DISABLE：不允许充电
 */
void ChargeM_SetDiagnosisChargeCtl(Diagnosis_ItemType item, ChargeM_CtlTypeType ctl);

/**
 * \brief 设置故障诊断充电控制状态
 * \details 通过此函数可设置发生诊断故障时进行充电启停的控制状态，会影响ChargeM_ChargeIsAllowed为E_NOT_OK，
 *          但不会影响由ChargeM_ChargeIsFault为E_OK
 *
 * \param item 诊断项
 * \param ctl 控制方式 CHARGEM_CHARGE_ENABLE：允许充电 CHARGEM_CHARGE_DISABLE：不允许充电
 */
void ChargeM_SetDiagnosisChargeCtlFlag(Diagnosis_ItemType item, ChargeM_CtlTypeType ctl);

/**
 * \brief 获取诊断故障当前对充电的控制状态
 *
 * \param item 故障诊断项
 * \return CHARGEM_CHARGE_ENABLE：允许充电 CHARGEM_CHARGE_DISABLE：不允许充电
 */
ChargeM_CtlTypeType ChargeM_GetDiagnosisChargeCtlFlag(Diagnosis_ItemType item);

/**
 * \brief 设置故障诊断充电动作控制动作
 * \details 通过此函数可设置发生诊断故障时进行充电启停的控制动作，同时会影响由ChargeM_ChargeIsFault为E_OK和
 *          ChargeM_ChargeIsAllowed为E_NOT_OK
 *
 * \param item 诊断项
 * \param ctl 控制方式 CHARGEM_CHARGE_ENABLE：允许充电 CHARGEM_CHARGE_DISABLE：不允许充电
 */
void ChargeM_SetDiagnosisChargeCtlAction(Diagnosis_ItemType item, ChargeM_CtlTypeType ctl);

/**
 * \brief 获取诊断故障当前对充电的动作控制
 *
 * \param item 故障诊断项
 * \return CHARGEM_CHARGE_ENABLE：允许充电 CHARGEM_CHARGE_DISABLE：不允许充电
 */
ChargeM_CtlTypeType ChargeM_GetDiagnosisChargeCtlAction(Diagnosis_ItemType item);

/**
 * \brief 其他故障充电控制是否允许充电
 *
 * \return E_OK:允许充电  E_NOT_OK:不允许充电
 */
Std_ReturnType ChargeM_OthersFaultIsNormal(void);

/**
 * \brief 获取充电控制其他故障故障码
 * \return 其他故障码 返回CHARGEM_OTHERS_FAULT_INVALID为无故障
 */
ChargeM_OthersFaultIndexType ChargeM_GetOthersFault(void);

/**
 * \brief 设置上电自检诊断状态
 *
 * \param num 诊断号
 * \param flag 控制状态
 */
void ChargeM_SetStartDiagCtl(Diagnosis_ItemType num, Diagnosis_StartDiagStateType flag);

/**
 * \brief 获取上电自检诊断状态
 *
 * \param num 诊断号
 * \return 控制状态
 */
Diagnosis_StartDiagStateType ChargeM_GetStartDiagCtl(Diagnosis_ItemType num);

/**
 * \brief 电池是否充电完成
 * \return TRUE-完成 FALSE- 未完成
 */
boolean ChargeM_BatteryChargeIsFinish(void);

/**
 * \brief 设置充电其他故障控制状态
 *
 * \param num 其他故障号
 * \param flag 控制状态
 */
ChargeM_CtlTypeType ChargeM_GetOthersFaultChargeCtl(ChargeM_OthersFaultIndexType item);

/**
 * \brief 获取充电其他故障控制状态
 *
 * \param num 其他故障号
 * \return 控制状态
 */
void ChargeM_SetOthersFaultChargeCtl(ChargeM_OthersFaultIndexType item, ChargeM_CtlTypeType ctl);

/**
 * \brief 诊断故障事件产生及释放对充电控制回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制标志及动作，此函数可用于同一级别的使能和禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件充电控制使能回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制标志及动作使能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlEnableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件充电控制禁能回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制标志及动作禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlDisableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件产生及释放对充电控制回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制状态，此函数可用于同一级别的使能和禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlFlagEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件充电控制使能回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制标志使能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlFlagEnableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件充电控制禁能回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制标志禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlFlagDisableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件产生及释放对充电控制动作回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制动作，此函数可用于同一级别的使能和禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlActionEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件充电控制动作使能回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制动作使能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlActionEnableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件充电控制动作禁能回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对充电的控制动作禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_DiagnosisCtlActionDisableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 上电自检诊断故障事件对充电控制使能回调函数
 * \details 当产生故障事件时，可通过此函数更新上电自检诊断故障对充电的控制状态
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_StartDiagCtlEnableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 上电自检诊断故障事件对充电控制禁能回调函数
 * \details 当产生故障事件时，可通过此函数更新上电自检诊断故障对充电的控制状态
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void ChargeM_StartDiagCtlDisableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 国标充电电子锁是否准备就绪
 * \details 当前充电模式不需要电子锁时，直接返回就绪；否则，只有驱动状态和实际状态均为锁止时才认为准备就绪。
 * \return TRUE-就绪 FALSE-未就绪
 */
boolean ChargeM_ELIsChargeReady(void);

/**
 * \brief 获取禁止充电故障等级
 * \details 获取对应诊断项禁止充电的故障等级
 *
 * \param item 诊断项
 * \param is_descend 等级是否从高到低等级降序检查 TRUE-降序检查 FALSE-升序检查
 * \return 禁止充电故障等级 返回DIAGNOSIS_LEVEL_NONE表示无禁止充电故障
 */
Diagnosis_LevelType ChargeM_GetChargeDisableLevel(Diagnosis_ItemType item, boolean is_descend);

/**
 * \brief 获取禁止充电故障触发配置参数值
 *
 * \param item 诊断项
 * \param offset 0-触发阈值 1-释放阈值 2-触发延时 3-释放延时
 * \return 禁止充电故障触发配置参数值 0xFFFF表示无效值
 */
uint16 ChargeM_GetChargeDisableTriggerPara(Diagnosis_ItemType item, uint8 offset);



#endif


/**
 * \}
 */
