/**
 * \file RuntimeM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 运行时管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161212 |
 */

/**
 * \addtogroup RuntimeM 运行时管理
 * \{
 */


#ifndef RUNTIMEM_H_
#define RUNTIMEM_H_

#include "Std_Types.h"
#include "Async_Looper.h"
#include "Diagnosis.h"
#include "ComStack_Types.h"

#define RUNTIMEM_WAKEUP_SIGNAL_BIT_NONE             0x00U
#define RUNTIMEM_WAKEUP_SIGNAL_BIT_KEY_ON           0x01U
#define RUNTIMEM_WAKEUP_SIGNAL_BIT_OBC_POWER        0x02U
#define RUNTIMEM_WAKEUP_SIGNAL_BIT_CHARGER_READY    0x04U
#define RUNTIMEM_WAKEUP_SIGNAL_BIT_RTC_INT          0x08U
#define RUNTIMEM_WAKEUP_SIGNAL_BIT_CP_HIGH          0x10U
#define RUNTIMEM_WAKEUP_SIGNAL_BIT_CAN2_INH         0x20U

/**
 * \brief 系统复位源类型定义
 */
typedef enum{
    RUNTIMEM_RESET_SOURCE_UNKNOWN, /**< 未知 */
    RUNTIMEM_RESET_SOURCE_VOLTAGE, /**< 供电电压异常复位 */
    RUNTIMEM_RESET_SOURCE_CLOCK, /**< 时钟源异常复位 */
    RUNTIMEM_RESET_SOURCE_WATCHDOG, /**< 看门狗复位 */
}RuntimeM_ResetSourceType;

/**
 * \brief 运行模式类型定义
 */
typedef enum{
    RUNTIMEM_RUNMODE_STANDBY, /**< 待机模式 */
    RUNTIMEM_RUNMODE_NORMAL, /**< 正常运行模式 */
    RUNTIMEM_RUNMODE_DTU, /**< 后台模式 */
    RUNTIMEM_RUNMODE_DATA, /**< 数据模式 */
    RUNTIMEM_RUNMODE_TEST, /**< 工程模式 */
    RUNTIMEM_RUNMODE_FBL, /**< 刷机模式 */
    RUNTIMEM_RUNMODE_CALIBRATE, /**< 标定模式 */
}RuntimeM_RunModeType;

/**
 * \brief 运行时复位状态类型定义
 */
typedef enum{
    RUNTIMEM_RESET_STATE_NONE, /**< 无复位命令 */
    RUNTIMEM_RESET_STATE_DATASAVE, /**< 数据存储状态 */
    RUNTIMEM_RESET_STATE_PROCESS_WAITING, /**< 进程等待状态 */
    RUNTIMEM_RESET_STATE_RESETING, /**< 进行复位 */
}RuntimeM_ResetStateType;

/**
 * \brief 运行时延时下电状态类型定义
 */
typedef enum{
    RUNTIMEM_PWD_STATE_NONE, /**< 无延时下电命令 */
    RUNTIMEM_PWD_STATE_DATASAVE, /**< 数据存储状态 */
    RUNTIMEM_PWD_STATE_PROCESS_WAITING, /**< 进程等待状态 */
    RUNTIMEM_PWD_STATE_POWER_DOWN, /**< 下电状态 */
}RuntimeM_PowerDownStateType;

typedef enum {
    RUNTIMEM_SIGNAL_POWERDOWN,
    RUNTIMEM_SIGNAL_RESET,
    RUNTIMEM_SIANGL_POWERDOWN_FORCE,
    RUNTIMEM_SIGNAL_RESET_FORCE,
} RuntimeM_SignalType;

/** 低压下电需要处理的任务 */
typedef struct {
    uint32 bit; /**< 位标识 */
    boolean (*kill)(RuntimeM_SignalType signal); /**< 低压下电处理函数, 返回TRUE时, 表示该任务已经关闭, 可以下电. */
} RuntimeM_TaskNotifyType;

#define RUNTIMEM_WAKEUP_OFF               0U /**< 关闭唤醒 */
#define RUNTIMEM_WAKEUP_PARAM_IS_DELAY    1U /**< 唤醒参数是延时 */
#define RUNTIMEM_WAKEUP_PARAM_IS_TIME     2U /**< 唤醒参数是时刻, 每天的秒偏移 */

typedef struct {
    uint8 maxTimeForWaitTaskPowerdown; /**< 等待低压下电的最大时间, 单位:毫秒 */
    const RuntimeM_TaskNotifyType *notifies; /**< 需要等待的任务列表, */
    uint8 TimeOrDelayToWakeupForData; /**< 唤醒进行数据传输的时间参数是时刻还是延时, RUNTIMEM_WAKEUP_PARAM_IS_XX*/
    uint8 TimeOrDelayToWakeupForOTA; /**< 唤醒进行OTA的时间参数是时刻还是延时, RUNTIMEM_WAKEUP_PARAM_IS_XX */
    uint32 wakeupTimeForData; /**< 下电多少秒之后(或什么时刻)唤醒进行数据传输 */
    uint32 wakeupTimeForOTA; /**< 有OTA请求时, 下电多少秒之后(或什么时刻)唤醒进行程序OTA */
    uint32 cpInvalidTimeFilter; /**< CP无效的过滤时间， 单位ms */
    uint16 maxOnTimeForData; /**< DTU模式下, 数据传输最长的工作时间, 单位: 秒 */
    uint16 maxOnTimeForOTA;  /**< DTU模式下, OTA最长的工作时间, 单位: 秒 */
    uint16 minBatteryVolForWakeup; /**< 运行唤醒进入DTU模块的最低低压供电电压, 单位:毫伏 */
    boolean chargeEndOtaSupport; /**< 充电末端的OTA支持 */
    boolean (*userIsWakeup)(void); /**< 用户唤醒信号函数 */
    PduIdType dongleRxPduId;
    PduIdType dongleTxPduId;
} RuntimeM_ConfigType;

extern const RuntimeM_ConfigType RuntimeM_ConfigData;

void RuntimeM_Init(Async_LooperType *looper);


/**
 * \brief 获取当前运行模式
 *
 * \return 返回当前运行模式
 */
RuntimeM_RunModeType RuntimeM_GetMode(void);

/**
 * \brief 启动系统复位

 * \return E_OK:启动成功 E_NOT_OK:启动失败
 */
Std_ReturnType RuntimeM_StartReset(RuntimeM_RunModeType mode);

/**
 * \brief 获取系统复位或下电需要等待的标记.

 * \return 复位或下电需要等待的标记
 */
uint32 RuntimeM_GetWaitFlags(void);

/**
 * \brief 获取系统复位源

 * \return 返回复位源
 */
RuntimeM_ResetSourceType RuntimeM_GetResetSouce(void);

/**
 * \brief 设置OTA请求, 试系统会在下电后尽快唤醒.
 */
void RuntimeM_RequestOta(void);

/**
 * \brief 判断是否有OTA请求.
 *
 * \retval TRUE 有OTA请求
 * \retval FALSE 无OTA请求
 */
boolean RuntimeM_HasOtaRequest(void);

/**
 * \brief 获取当前时刻的唤醒信号源.
 * \return 当前唤醒信号的位标识.
 */
uint8 RuntimeM_GetWakeSignal(void);

/**
 * \brief 请求下电, 只能在DTU模式下使用.
 */
void RuntimeM_RequestPowerDown(void);


/**
 * \brief 通知运行管理模块, 直接进入DTU模式，可用于手动升级.
 */
Std_ReturnType RuntimeM_RequestToDtuMode(void);

/**
 * \brief 通知运行管理模块, 进入编程模式(复位到Bootloader或,延长DTU的运行时限).
 */
Std_ReturnType RuntimeM_RequestToProgram(void);

/**
 * \brief 运行管理模块是否已经进入下电休眠流程
 *
 * \return FALSE:未进入 TRUE:已进入
 */
boolean RuntimeM_IsInPowerDownFlow(void);

/**
 * \brief 供电电压低事件
 * \details 通知运行管理模块供电电压低，请求休眠
 *
 * \param item 故障诊断项
 * \param level 故障等级
 * \param event 事件类型
 */
void RuntimeM_LowPowerSupply(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

#endif

/**
 * \}
 */
