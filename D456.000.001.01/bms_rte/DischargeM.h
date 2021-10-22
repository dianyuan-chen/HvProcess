/**
 * \file DischargeM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 放电管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170311 |
 */

/**
 * \addtogroup DischargeM 放电管理
 * \{
 */

#ifndef DISCHARGEM_H_
#define DISCHARGEM_H_

#include "App_Types.h"
#include "Diagnosis.h"

#define DISCHARGEM_DIAGNOSIS_CTL_BUFFER_SIZE           ((DIAGNOSIS_ITEM_DEFAULT_NUM + 7U) / 8U)
#define DISCHARGEM_START_DIAG_CTL_BUFFER_SIZE          ((DIAGNOSIS_ITEM_DEFAULT_NUM + 3U) / 4U)
#define DISCHARGEM_OTHERS_FAULT_CTL_BUFFER_SIZE        10U

#define DISCHARGEM_START_DIAG_USE_BIT_NUM              2U
#define DISCHARGEM_START_DIAG_MASK_NUM                 3U
#define DISCHARGEM_START_DIAG_NUM_IN_BYTE              (8U/DISCHARGEM_START_DIAG_USE_BIT_NUM)
#define DISCHARGEM_START_DIAG_STATUS_DEFAULT           0xFFU

typedef uint8 DischargeM_OthersFaultIndexType;
#define DISCHARGEM_OTHERS_FAULT_INVALID    0xFFU


/**
 * \brief 放电控制类型类型定义
 */
typedef enum{
    DISCHARGEM_DISCHARGE_ENABLE = 0, /**< 允许放电 */
    DISCHARGEM_DISCHARGE_DISABLE = 1, /**< 不允许放电 */
}DischargeM_CtlTypeType;


typedef struct{
    uint8 flag; /**< 控制状态 */
    uint8 action; /**< 动作状态 */
}DischargeM_CtlInfoType;

typedef struct{
    Async_EventType event;
    DischargeM_CtlInfoType diagnosisCtl[DISCHARGEM_DIAGNOSIS_CTL_BUFFER_SIZE]; /**< 故障诊断放电控制 */
    uint8 startDiagCtl[DISCHARGEM_START_DIAG_CTL_BUFFER_SIZE]; /**< 上电自检诊断放电控制 */
    uint8 othersFaultCtl[DISCHARGEM_OTHERS_FAULT_CTL_BUFFER_SIZE]; /**< 其他故障放电控制 */

    uint8 diagnosisCtlMask[DISCHARGEM_DIAGNOSIS_CTL_BUFFER_SIZE]; /**< 故障诊断充电控制掩码 */
    uint8 startDiagCtlMask[DISCHARGEM_START_DIAG_CTL_BUFFER_SIZE]; /**< 上电自检诊断充电控制掩码 */
}DischargeM_InnerDataType;

/**
 * \brief 放电管理模块初始化
 */
void DischargeM_Init(Async_LooperType *looper);

/**
 * \brief 当前是否允许放电
 * \details 是否有故障不允许放电
 *
 * \return E_OK: 允许 E_NOT_OK:不允许
 */
Std_ReturnType DischargeM_DischargeIsAllowed(void);

/**
 * \brief 当前放电故障是否已经成立
 * \details
 * \return E_OK: 故障动作已成立 E_NOT_OK: 未成立
 */
Std_ReturnType DischargeM_DischargeIsFault(void);

/**
 * \brief 当前放电故障动作是否已经成立
 * \details 例：当某一故障延时断继电器等成立后，此函数返回E_OK，此时需断放电继电器,此函数用于确认是否需要断放电高压
 * \return E_OK: 故障动作已成立 E_NOT_OK: 未成立
 */
Std_ReturnType DischargeM_DischargeIsFaultAction(void);

/**
 * \brief 放电上电自检是否正常允许放电
 * \return E_OK: 允许 E_NOT_OK: 不允许
 *
 * \note 此函数需要配置上电自检完成
 */
Std_ReturnType DischargeM_StartDiagIsNormal(void);

/**
 * \brief 获取放电控制上电自检故障码
 * \details 未自检完成前返回无故障
 *
 * \return 上电自检诊断故障码 返回DIAGNOSIS_ITEM_INVALID_INDEX为无故障
 */
Diagnosis_ItemType DischargeM_GetStartDiagFault(void);

/**
 * \brief 放电上电自检排除指定诊断项序列后是否允许故障
 *
 * \param item 诊断项序列
 * \param length 序列长度
 *
 * \return E_OK: 故障 E_NOT_OK: 无故障
 */
Std_ReturnType DischargeM_StartDiagIsFaultExcludeItems(const Diagnosis_ItemType *item, uint8 length);

/**
 * \brief 故障诊断放电控制是否允许放电
 *
 * \return E_OK:允许放电  E_NOT_OK:不允许放电
 */
Std_ReturnType DischargeM_DiagnosisIsNormal(void);

/**
 * \brief 故障诊断放电控制故障已经动作
 * \details 用于确认诊断故障后延时完成需要故障动作,此函数用于确认是否有诊断故障需要断放电高压
 * \return E_OK: 未成立  E_NOT_OK: 故障动作成立
 */
Std_ReturnType DischargeM_DiagnosisIsFaultAction(void);

/**
 * \brief 获取放电控制诊断标志故障码
 * \return 诊断故障 返回DIAGNOSIS_ITEM_INVALID_INDEX为无故障
 */
Diagnosis_ItemType DischargeM_GetDiagFaultFlag(void);

/**
 * \brief 获取放电控制诊断动作故障码
 * \return 诊断故障 返回DIAGNOSIS_ITEM_INVALID_INDEX为无故障
 */
Diagnosis_ItemType DischargeM_GetDiagFaultAction(void);

/**
 * \brief 排除指定诊断项序列后当前放电故障标志是否成立
 * \details 此函数用于确认排除多个故障后是否有诊断故障需要禁止放电
 *
 * \param item 诊断项序列
 * \param length 诊断项个数
 *
 * \return E_OK:成立 E_NOT_OK:未成立
 */
Std_ReturnType DischargeM_DiagnosisIsFaultFlagExcludeItems(const Diagnosis_ItemType *item, uint8 length);

/**
 * \brief 同时设置故障诊断放电控制标志及动作
 * \details 通过此函数可设置发生诊断故障时进行放电启停的控制标志及动作
 *
 * \param item 诊断项
 * \param ctl 控制方式 DISCHARGEM_DISCHARGE_ENABLE：允许放电 DISCHARGEM_DISCHARGE_DISABLE：不允许放电
 */
void DischargeM_SetDiagnosisDchargeCtl(Diagnosis_ItemType item, DischargeM_CtlTypeType ctl);

/**
 * \brief 设置故障诊断放电控制标志
 * \details 通过此函数可设置发生诊断故障时进行放电启停的控制标志及动作
 *
 * \param item 诊断项
 * \param ctl 控制方式 DISCHARGEM_DISCHARGE_ENABLE：允许放电 DISCHARGEM_DISCHARGE_DISABLE：不允许放电
 */
void DischargeM_SetDiagnosisDchargeCtlFlag(Diagnosis_ItemType item, DischargeM_CtlTypeType ctl);

/**
 * \brief 其他故障放电控制是否允许放电
 *
 * \return E_OK:允许放电  E_NOT_OK:不允许放电
 */
Std_ReturnType DischargeM_OthersFaultIsNormal(void);

/**
 * \brief 获取放电控制其他故障故障码
 * \return 其他故障码 返回DISCHARGEM_OTHERS_FAULT_INVALID为无故障
 */
DischargeM_OthersFaultIndexType DischargeM_GetOthersFault(void);

/**
 * \brief 获取诊断故障当前对放电的控制标志
 *
 * \param item 故障诊断项
 * \return DISCHARGEM_DISCHARGE_ENABLE：允许放电 DISCHARGEM_DISCHARGE_DISABLE：不允许放电
 */
DischargeM_CtlTypeType DischargeM_GetDiagnosisDchargeCtlFlag(Diagnosis_ItemType item);

/**
 * \brief 设置故障诊断放电控制动作
 * \details 通过此函数可设置发生诊断故障时进行放电启停的控制动作
 *
 * \param item 诊断项
 * \param ctl 控制方式 DISCHARGEM_DISCHARGE_ENABLE：允许放电 DISCHARGEM_DISCHARGE_DISABLE：不允许放电
 */
void DischargeM_SetDiagnosisDchargeCtlAction(Diagnosis_ItemType item, DischargeM_CtlTypeType ctl);

/**
 * \brief 获取诊断故障当前对放电的控制动作
 *
 * \param item 故障诊断项
 * \return DISCHARGEM_DISCHARGE_ENABLE：允许放电 DISCHARGEM_DISCHARGE_DISABLE：不允许放电
 */
DischargeM_CtlTypeType DischargeM_GetDiagnosisDchargeCtlAction(Diagnosis_ItemType item);

/**
 * \brief 设置放电启动诊断控制状态
 *
 * \param num 诊断号
 * \param flag 控制状态
 */
void DischargeM_SetStartDiagCtl(Diagnosis_ItemType num, Diagnosis_StartDiagStateType flag);

/**
 * \brief 获取放电启动诊断控制状态
 *
 * \param num 诊断号
 * \return 控制状态
 */
Diagnosis_StartDiagStateType DischargeM_GetStartDiagCtl(Diagnosis_ItemType num);

/**
 * \brief 设置放电其他故障控制状态
 *
 * \param num 其他故障号
 * \param flag 控制状态
 */
DischargeM_CtlTypeType DischargeM_GetOthersFaultDchargeCtl(DischargeM_OthersFaultIndexType item);

/**
 * \brief 获取放电其他故障控制状态
 *
 * \param num 其他故障号
 * \return 控制状态
 */
void DischargeM_SetOthersFaultDchargeCtl(DischargeM_OthersFaultIndexType item, DischargeM_CtlTypeType ctl);

/**
 * \brief 诊断故障事件产生及释放回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对放电的控制标志及动作，可用于同一级别的使能和禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void DischargeM_DiagnosisCtlEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件控制使能放电回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对放电的控制标志及动作使能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void DischargeM_DiagnosisCtlEnableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件控制禁能放电回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对放电的控制标志及动作禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void DischargeM_DiagnosisCtlDisableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件产生及释放回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对放电的控制状态，可用于同一级别的使能和禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void DischargeM_DiagnosisCtlFlagEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件控制使能放电回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对放电的控制标志使能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void DischargeM_DiagnosisCtlFlagEnableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断故障事件控制禁能放电回调函数
 * \details 当产生故障事件时，可通过此函数更新诊断故障对放电的控制标志禁能
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void DischargeM_DiagnosisCtlFlagDisableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 上电自检诊断故障事件对放电控制使能回调函数
 * \details 当产生故障事件时，可通过此函数更新上电自检诊断故障对放电的控制状态
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void DischargeM_StartDiagCtlEnableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 上电自检诊断故障事件对放电控制禁能回调函数
 * \details 当产生故障事件时，可通过此函数更新上电自检诊断故障对放电的控制状态
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void DischargeM_StartDiagCtlDisableEventCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 获取禁止放电故障等级
 * \details 获取对应诊断项禁止放电的故障等级
 *
 * \param item 诊断项
 * \param is_descend 等级是否从高到低等级降序检查 TRUE-降序检查 FALSE-升序检查
 * \return 禁止放电故障等级 返回DIAGNOSIS_LEVEL_NONE表示无禁止放电故障
 */
Diagnosis_LevelType DischargeM_GetDischargeDisableLevel(Diagnosis_ItemType item, boolean is_descend);





#endif

/**
 * \}
 */
