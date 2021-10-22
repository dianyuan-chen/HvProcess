/** \addtogroup Async 异步事件框架
 * \{ */

/**
 * \file Async_Private.h
 * \brief 异步事件框架私有数据及函数声明.
 * \author U0005
 * \version 1.0
 * \date 2016-11-23
 */
#ifndef __ASYNC_PRIVATE_H__
#define __ASYNC_PRIVATE_H__

#include "Async_Event.h"

#define OS_TIME_FOREVER 0xFFFFFFFFUL

typedef enum {
    LOOPER_COMMAND_TYPE_CANCEL_EVENT, //<! 取消一个异步事件.
    LOOPER_COMMAND_TYPE_TRIGGER_CALL, //!< 触发一个异步事件.
    LOOPER_COMMAND_TYPE_ADD_EVENT, //!< 增加一个异步事件.
    LOOPER_COMMAND_TYPE_SET_TIMEOUT, //!< 设置异步事件的超时时间.
    LOOPER_COMMAND_TYPE_SET_CBK, //!< 设置异步事件的回掉函数.
    LOOPER_COMMAND_TYPE_EXIT, //!< 退出事件循环,
} async_LooperCommandType;


/**
 * 事件循环通知的命令数据.
 */
typedef struct {
    async_LooperCommandType cmd; //!< 命令类型.
    Async_EventType *event; //!< 关联的事件.
    union {
        void *pdat; //!< 指针格式的数据.
        uint32 dat32; //!< 32位宽的数据.
        uint16 dat16[2]; //!< 16位宽的数据.
        uint8  dat8[4]; //!< 8位宽的数据.
    } dat; //!< 附加的数据.
} async_LooperNotifyType;

/**
 * \brief 通知事件循环
 * \details 所有对于事件循环的真实操作都是在事件循环所在任务执行, 该函数只是把操作放在缓冲, 并设置一个信号量.
 *
 * \param looper 事件循环.
 * \param notify 要执行的操作.
 *
 * \return 通知成功(E_OK); 通知失败(E_NOT_OK).
 */
Std_ReturnType async_NotifyLoop(Async_LooperType *looper, const async_LooperNotifyType *notify);
uint32 async_EventExecTrigger(Async_EventType *event, uint8 trigger, const struct list_head *events);
uint32 async_EventExecTimeout(const struct list_head *events);
uint32 async_EventAddToLooper(Async_EventType *event, struct list_head *list);
uint32 async_EventSetTimeout(Async_EventType *event, uint32 timeout, const struct list_head *list);
void async_EventSetCbk(Async_EventType *event, Async_EventCbkType cbk, const struct list_head *list);
void async_EventDeleteFromLooper(Async_EventType *event, const struct list_head *list);

#endif

/** \} */