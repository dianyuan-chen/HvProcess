/**
 * \addtogroup Drivers
 * \{
 * \addtogroup ElectronicLock 电子锁驱动
 * \{
 */

#ifndef EL_H
#define EL_H

#include "EL_Cfg.h"

#include "Drv8872.h"
#include "Dio.h"
#include "Async_Looper.h"

/**
 * \brief 电子锁通道索引类型.
 */
typedef uint8 EL_ChannelType;

/**
 * \brief 电子锁配置
 */
typedef struct {
    uint8 driveChipId; /*< 驱动芯片ID */
    Dio_ChannelType LockFeedbackDio; /** 锁止时的反馈输入 */
    Dio_ChannelType UnlockFeedbackDio; /** 解锁时的反馈输入 */
    Dio_LevelType FeedbackDiStateWhenLock; /** 锁止时的反馈脚状态 */
    Dio_LevelType FeedbackDiStateWhenUnlock; /** 解锁时的反馈脚状态 */
    uint16 LockTimeDuration; /**< 驱动锁止的时间 */
    uint16 UnlockTimeDuration;  /**< 驱动解锁的时间 */
    uint16 CheckDelay;/**< 电子锁动作时间, 驱动完成之后检查反馈的延时时间 */
    uint8 ctlMax;
} EL_LockerConfigType;

#define EL_FORCE_OFF     0U
#define EL_FORCE_UNLOCK  1U
#define EL_FORCE_LOCK    2U

/**
 * \brief 电子锁状态
 */
typedef enum {
    EL_Diagnosis_UnlockOK, /**< 驱动正常并且解锁正常 */
    EL_Diagnosis_UnlockERR, /**< 驱动正常并且解锁异常 */
    EL_Diagnosis_LockOK, /**< 驱动正常并且锁止正常 */
    EL_Diagnosis_LockERR, /**< 驱动正常, 但是锁止异常 */
    EL_Diagnosis_Disabled /**< 电子锁被禁能 */
    //EL_Diagnosis_DriveERR, /**< 驱动异常 */
} EL_DiagnosisStatus;


typedef enum {
    EL_UNLOCK,
    EL_LOCK,
    EL_DISABLE,
} EL_State;

/**
 * \brief 电子锁初始化.
 * \details 初始化电子锁驱动, 如果支持异步操作, 则必须传入一个异步事件循环\link Async_LooperType \endlink.
 *
 * \param[in] looper 异步事件循环
 */
void EL_Init(Async_LooperType *looper);

/**
 * \brief 异步电子锁操作时状态回调函数.
 * \details 当电子锁状态发生变化是, 会调用状态回调函数. \link EL_SetNotifier \endlink.
 *
 * \param  channel 状态发生变化的电子锁通道索引.
 */
typedef void (*EL_StatusNotifyFuncionType)(EL_ChannelType channel);

/**
 * \brief 获取电子锁状态.
 *
 * \param channel 电子锁通道索引
 * \return 电子锁状态
 */
EL_DiagnosisStatus EL_GetDiagnosisStatus(EL_ChannelType channel);

/**
 * \brief 检查电子锁是否诊断完成.
 *
 * \param channel 电子锁通道索引
 * \retval TRUE 诊断完成
 * \retval FALSE 诊断未完成
 */
boolean EL_DiagnosisIsFinished(EL_ChannelType channel);
uint8 EL_DiagsisIsFinishedForDiag(void);

/**
 * \brief 获取电子锁的驱动状态.
 * \details 解锁电子锁, 并且在操作完成(可能失败)之后返回.
 *
 * \param channel 电子锁通道索引.
 */
EL_State EL_GetDriveState(EL_ChannelType channel);

/**
 * \brief 获取电子锁的实际状态.
 * \details 解锁电子锁, 并且在操作完成(可能失败)之后返回.
 *
 * \param channel 电子锁通道索引.
 */
EL_State EL_GetActualState(EL_ChannelType channel);


/**
 * \brief 获取电子锁的强制控制.
 * \details 解锁电子锁, 并且在操作完成(可能失败)之后返回.
 *
 * \param channel 电子锁通道索引.
 */
uint8 EL_GetForceControl(EL_ChannelType channel);

/**
 * \brief 电子锁诊断是否故障
 * \details 包含锁止故障和解锁故障
 * \return 0-正常 非0-故障
 */
uint16 EL_DiagnosisIsError(void);

/**
 * \brief 同步锁止.
 * \details 锁止电子锁, 并且在操作完成(可能失败)之后返回.
 *
 * \param channel 电子锁通道索引.
 * \retval E_OK 锁止操作完成;
 * \retval E_NOT_OK 锁止操作未完成;
 */
Std_ReturnType EL_LockSync(EL_ChannelType channel);


/**
 * \brief 同步解锁.
 * \details 解锁电子锁, 并且在操作完成(可能失败)之后返回.
 *
 * \param channel 电子锁通道索引.
 * \retval E_OK 解锁操作完成;
 * \retval E_NOT_OK 解锁操作未完成;
 */
Std_ReturnType EL_UnlockSync(EL_ChannelType channel);


/**
 * \brief 电子同步锁禁能.
 * \details 异步操作, 会关闭电子锁的锁止控制和解锁控制.
 *
 * \param channel 电子锁通道索引.
 * \retval E_OK 禁能操作完成;
 * \retval E_NOT_OK 禁能操作未完成;
 */
Std_ReturnType EL_DisableSync(EL_ChannelType channel);

/**
 * \brief 设置异步操作回调函数.
 * \details \link EL_LockAsync \endlink;\link EL_UnlockAsync \endlink.
 *
 * \param channel 电子锁通道索引
 * \param notifier 回调函数.
 */
void EL_SetNotifier(EL_ChannelType channel, EL_StatusNotifyFuncionType notifier);

/**
 * \brief 异步锁止.
 * \details 锁止电子锁, 立刻返回, 在操作完成之后会调用状态改变回调函数. \link EL_SetNotifier \endlink.
 *
 * \param channel 电子锁通道索引.
 * \retval E_OK 启动锁止流程正常.
 * \retval E_NOT_OK 启动锁止流程错误.
 */
Std_ReturnType EL_LockAsync(EL_ChannelType channel);

/**
 * \brief 异步解锁.
 * \details 解锁电子锁, 立刻返回, 在操作完成之后会调用状态改变回调函数. \link EL_SetNotifier \endlink.
 *
 * \param channel 电子锁通道索引.
 * \retval E_OK 启动解锁流程正常.
 * \retval E_NOT_OK 启动解锁流程错误.
 */
Std_ReturnType EL_UnlockAsync(EL_ChannelType channel);

/**
 * \brief 电子异步锁禁能.
 * \details 异步操作, 会关闭电子锁的锁止控制和解锁控制.
 *
 * \param channel 电子锁通道索引.
 * \retval E_OK 启动禁能流程正常.
 * \retval E_NOT_OK 启动禁能流程错误.
 */
Std_ReturnType EL_DisableAsync(EL_ChannelType channel);


/**
 * \brief 异步强制控制.
 *
 * \param channel 电子锁通道索引.
 * \retval E_OK 启动解锁流程正常.
 * \retval E_NOT_OK 启动解锁流程错误.
 */
Std_ReturnType EL_ForceAsync(EL_ChannelType channel, uint8 forceControl);
/**
 * \brief 判断电子锁功能是否开启.

 * \param channel 电子锁通道索引.
 * \retval TRUE 电子锁功能开启.
 * \retval TRUE 电子锁功能禁止.
 */
boolean EL_IsEnabled(EL_ChannelType channel);

extern const EL_LockerConfigType ELLockerConfig[EL_LOCKER_NUM];

#endif

/**
 * \}
 * \}
 */
