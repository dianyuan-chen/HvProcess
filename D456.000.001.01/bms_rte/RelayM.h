/**
 * \file RelayM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 继电器管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD0005 | 20161201 |
 */


 /**
 * \addtogroup RelayM 继电器管理
 * \{
 */

#ifndef RELAYM_H_
#define RELAYM_H_

#include "Std_Types.h"
#include "RelayM_Cfg.h"
#include "Async_Event.h"
#include "HLSS.h"
#include "Hv.h"


/**
 * \brief 继电器的控制类型.
 */
typedef enum {
    RELAYM_CONTROL_ON, /**< 控制继电器打开. */
    RELAYM_CONTROL_OFF, /**< 控制继电器断开. */
    RELAYM_CONTROL_FORCE_OFF, /**< 控制继电器断开, 可以带负载切断. */
} RelayM_ControlType;

/**
 * \brief 继电器的实际状态.
 */
typedef enum {
    RELAYM_ACTUAL_ON, /**< 继电器实际已经闭合, 诊断为粘连之后, 也是该状态 */
    RELAYM_ACTUAL_OFF, /**< 继电器实际已经断开, 诊断为开路之后, 也是该状态 */
} RelayM_ActualStatusType;

typedef enum {
    RELAYM_FORCE_ON, /**< 继电器强控打开. */
    RELAYM_FORCE_OFF, /**< 继电器强控关闭. */
    RELAYM_FORCE_DISABLE,  /**< 继电器强控取消. */
} RelayM_ForceControlType;

/**
 * \brief 继电器的诊断状态.
 */

#define RELAYM_DIAGNOSIS_DRIVER_STATE_MASK      0x01U /**< 驱动端状态位, 0正常，1存在故障 */
#define RELAYM_DIAGNOSIS_ADHESIVE_STATE_MASK    0x02U /**< 粘连状态位， 0正常，1存在故障 */
#define RELAYM_DIAGNOSIS_ADHESIVE_CHECKING_MASK 0x04U /**< 正在进行黏连检测标记 */
#define RELAYM_DIAGNOSIS_OPEN_STATE_MASK        0x08U /**< 开路状态位， 0正常，1存在故障 */
#define RELAYM_DIAGNOSIS_OPEN_CHECKING_MASK     0x10U /**< 正在进行开路标记 */
#define RELAYM_DIAGNOSIS_AUX_CONTACT_MASK       0x20U /**< 辅助触点状态, 0正常, 1存在故障 */

#define RELAYM_DIAGNOSIS_IS_NORMAL(diag)                   (0U == (diag))
#define RELAYM_DIAGNOSIS_IS_NORMAL_IGNORE_CHECKING(diag)   (0U == ((diag) & (RELAYM_DIAGNOSIS_DRIVER_STATE_MASK | RELAYM_DIAGNOSIS_ADHESIVE_STATE_MASK | RELAYM_DIAGNOSIS_OPEN_STATE_MASK | RELAYM_DIAGNOSIS_AUX_CONTACT_MASK)))
#define RELAYM_DIAGNOSIS_IS_CHECKING(diag)                 ((diag) & (RELAYM_DIAGNOSIS_ADHESIVE_CHECKING_MASK | RELAYM_DIAGNOSIS_OPEN_CHECKING_MASK))

#define RELAYM_DIAGNOSIS_IS_ADHESIVE(diag)                 (((diag) & RELAYM_DIAGNOSIS_ADHESIVE_STATE_MASK) != 0U)
#define RELAYM_DIAGNOSIS_IS_OPEN(diag)                     (((diag) & RELAYM_DIAGNOSIS_OPEN_STATE_MASK) != 0U)
#define RELAYM_DIAGNOSIS_IS_AUX_CONTACT_ERR(diag)          (((diag) & RELAYM_DIAGNOSIS_AUX_CONTACT_MASK) != 0U)
#define RELAYM_DIAGNOSIS_IS_DRIVER_ERR(diag)               (((diag) & RELAYM_DIAGNOSIS_DRIVER_STATE_MASK) != 0U)

typedef uint8 RelayM_DiagnosisStatusType;

// typedef enum {
//     RELAYM_DIAGNOSIS_ADHESIVE_NOT_DETECTED, /**< 粘连还没有检查. */
//     RELAYM_DIAGNOSIS_ADHESIVE_DETECTING, /**< 正在检查粘连. */
//     RELAYM_DIAGNOSIS_ADHESIVE, /**< 继电器粘连. */
//     RELAYM_DIAGNOSIS_OPEN_CIRCUIT, /**< 继电器开路. */
//     RELAYM_DIAGNOSIS_DRIVER_ERR, /**< 继电器驱动故障. */
//     RELAYM_DIAGNOSIS_OK, /**< 继电器状态正常. */
//     RELAYM_DIAGNOSIS_UNKNOWN, /**< 未知状态 */
// } RelayM_DiagnosisStatusType;

#define RELAYM_RELAY_ON_POS         0U /**< 继电器在正端 */
#define RELAYM_RELAY_ON_NEG         1U /**< 继电器在负端 */

#define RELAYM_INVALID_RESISTOR     (0xFFFFU)

/**
 * \brief 继电器配置的数据结构.
 * \note 运行时配置.
 */
typedef struct {
    const char *name; /**<继电器名称*/
    uint16 OnTimeDelay; /**< 闭合机械延时 */
    uint16 OffTimeDelay; /**< 断开机械延时 */
    uint16 Resistor; /**< 线圈电阻 */
    HLSS_ChannelType DriveHSS; /**< 驱动的高边开关通道 */
    boolean (*IsSafeToOff)(void); /**< 判断是否可以安全切断 */
    sint16 (*GetInstantVoltage)(void);  /**< 获取后端电压的用户函数 */
    uint16 HvChannelCheckInterval; /**< 开路或黏连检测高压检测周期, ms */
    uint8 OnWhere; /**< 继电器所在位置, RELAYM_RELAY_ON_POS RELAYM_RELAY_ON_NEG */
    uint8 continuePercent; /**< 连续下降(上升)百分比 */
    uint8 totalPercent; /**< 直接百分比 */
    uint16 detectTimeout; /**< 开路或黏连检测超时时间 */
    Dio_ChannelType AuxContact; /**< 辅助触点IO */
    Dio_LevelType IoLevelOfAuxContactWhenOn; /**< 闭合是辅助触点的状态 */
} RelayM_ConfigType;

/**
 * \brief 继电器通用配置的数据结构
 */
typedef struct {
    uint32 MinTimeSapce; /**< 继电器最小闭合间隔 */
} RelayM_CommonConfigType;

/**
 * \brief 继电器粘连检测回调函数.
 * \note 请参考\link RelayM_StartAdhesiveDetect \endlink, \link RelayM_StartOpenCircuitDetect \endlink.
 *
 * \param fn 继电器
 * \param digStatus 继电器的诊断状态
 */
typedef void (*RelayM_DetectCbk)(RelayM_FunctionType fn, RelayM_DiagnosisStatusType digStatus);

typedef struct {
    Async_EventType event;
    RelayM_FunctionType fn;
    RelayM_DetectCbk cbk;
    RelayM_DiagnosisStatusType diagStatus;
    RelayM_ControlType control;
    RelayM_ForceControlType forceControl;
    RelayM_ActualStatusType actualStatus;
    uint32 opsTime; // 动作时间点
    uint32 onOpsCnt; // 闭合计数
    uint32 forceOffOpsCnt; // 强制切断操作计数
    sint16 volBuf[5];
    uint32 detectStartTime;
    uint8 volBufIndex;
} RelayM_InnerDataType;

extern const RelayM_FunctionType RelayMFnNum;
extern const RelayM_CommonConfigType RelayMCommonConfigData;
extern const RelayM_ConfigType RelayMConfigData[];
extern RelayM_InnerDataType RelayMInnerData[];


void RelayM_Init(Async_LooperType *looper);

/**
 * \brief 设置继电器的控制状态.
 *
 * \param fn 需要控制的继电器.
 * \param control 控制状态.
 */
Std_ReturnType RelayM_Control(RelayM_FunctionType fn, RelayM_ControlType control);

/**
 * \brief 获取继电器的控制状态.
 *
 * \param fn 需要查询的继电器.
 * \return 继电器的控制状态.
 */
RelayM_ControlType RelayM_GetControlStatus(RelayM_FunctionType fn);


/**
 * \brief 获取继电器的实际状态.
 *
 * \param fn 需要查询的继电器.
 * \return 继电器的实际状态.
 */
RelayM_ActualStatusType RelayM_GetActualStatus(RelayM_FunctionType fn);


/**
 * \brief 继电器强制控制.
 *
 * \param fn 需要查询的继电器.
 * \param forceControl 继电器的强制控制.
 */
void RelayM_ForceControl(RelayM_FunctionType fn, RelayM_ForceControlType forceControl);


/**
 * \brief 获取继电器强制控制.
 *
 * \param fn 需要查询的继电器.
 * \return 继电器的强制控制状态.
 */
RelayM_ForceControlType RelayM_GetForceControlStatus(RelayM_FunctionType fn);

/**
 * \brief 获取继电器的诊断状态.
 *
 * \param fn 需要查询的继电器.
 * \return 继电器的诊断状态.
 */
RelayM_DiagnosisStatusType RelayM_GetDiagnosisStatus(RelayM_FunctionType fn);

/**
 * \brief 启动继电器的粘连检测.
 * \note 该调用为异步调用, 请参考\link RelayM_DetectCbk \endlink.
 *
 * \param fn 要检测的继电器.
 * \param cbk 检测完成之后的回调函数.
 * \retval E_OK 成功启动检测流程.
 * \retval E_NOT_OK 启动检测流程失败.
 */
Std_ReturnType RelayM_StartAdhesiveDetect(RelayM_FunctionType fn, RelayM_DetectCbk cbk);

/**
 * \brief 启动继电器的开路检测（此功能暂未实现）.
 * \note 该调用为异步调用, 请参考\link RelayM_DetectCbk \endlink.
 *
 * \param fn 要检测的继电器.
 * \param cbk 检测完成之后的回调函数.
 * \retval E_OK 成功启动检测流程.
 * \retval E_NOT_OK 启动检测流程失败.
 */
Std_ReturnType RelayM_StartOpenCircuitDetect(RelayM_FunctionType fn, RelayM_DetectCbk cbk);

/**
 * \brief 获取继电器控制高边开关的通道.
 *
 * \param fn 需要查询的继电器.
 * \return 继电器控制高边开关的通道.
 */
HLSS_ChannelType RelayM_GetDriveHSSChannel(RelayM_FunctionType fn);

/**
 * \brief 继电器后端高压是否配置监控
 * \details 启动继电器后端电压才能进行继电器故障检测
 *
 * \param fn 需要查询的继电器
 * \return E_NOT_OK：未配置监控 E_OK：已配置监控
 */
Std_ReturnType RelayM_RelayHvIsMonitor(RelayM_FunctionType fn);

/**
 * \brief 检查对应功能的继电器是否使能
 *
 * \param fn 需要查询的继电器功能
 * \return E_NOT_OK:未使能 E_OK:使能
 */
Std_ReturnType RelayM_FunctionRelayIsEnable(RelayM_FunctionType fn);


/**
 * \brief 判断当前是否有继电器正在吸合.
 * \details 吸合的时候会影响到外部供电电压, 导致部分采集不准确.
 * \retval TRUE 有继电器正在进行吸合动作.
 * \retval FALSE 无继电器正在进行吸合动作.
 */
boolean RelayM_IsInOpProcess(void);

/**
 * \brief 继电器是否异常
 * \details 继电器开路、粘连、驱动电路异常等无属于继电器异常，任一继电器异常返回非0
 * \return 0-正常 非0-异常
 */
uint16 RelayM_IsDiagAbnormal(void);



#endif

/** \} */
