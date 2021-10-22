/** \addtogroup Async
 * \{ */

/**
 * \file Async_Event.h
 * \brief 异步事件相关声明.
 * \author U0005
 * \version 1.0
 * \date 2016-11-23
 */


#ifndef __ASYNC_EVENT_H__
#define __ASYNC_EVENT_H__

#include "list.h"
#include "Std_Types.h"
#include "Async_Looper.h"

#define ASYNC_TRIGGER_BY_TIMEOUT 0xFFU

/**
 * \brief 异步事件返回值类型定义.
 */
typedef enum {
    ASYNC_EVENT_CBK_RETURN_CANCEL = 0, /*!< 返回这个值该异步事件会从Looper中移除. */
    ASYNC_EVENT_CBK_RETURN_OK = 1, //!< 返回这个值该异步事件不会从Looper中移除, 并且会重新计算超时.
    ASYNC_EVENT_CBK_RETURN_CONTINUE_LAST_TIMEOUT = 2, //!< 返回这个值该异步事件不会从Looper中移除, bywhat!=ASYNC_TRIGGER_BY_TIMEOUT时不会重新计算超时.
} Async_EvnetCbkReturnType;

/**
 * \ \link Async_Event \endlink
 */
typedef struct Async_Event Async_EventType;

/**
 * \brief 异步事件回调函数类型.
 *
 * \param event 异步事件.
 * \param byWhat 触发该次调用的源.
 *
 * \return \see Async_EvnetCbkReturnType
 */
typedef Async_EvnetCbkReturnType (*Async_EventCbkType)(Async_EventType *event, uint8 byWhat);

/**
 * \brief 异步事件.
 */
struct Async_Event {
    struct list_head head; //!< 双向链表表头.
    Async_EventCbkType cbk; //!< 回调函数.
    uint32 timeout; //!< 超时事件.
    uint32 next_timestamp; //!< 下次的超时时刻.
    Async_LooperType *looper; //!< 所在Looper.
};

/**
 * \brief 初始化一个异步事件.
 * \details  在对异步事件操作之前必须对异步事件进行初始化.
 *
 * \param[in] event 需要初始化的异步事件.
 * \param[in] looper 注册到Looper, 该事件的回调函数会运行在Looper所在任务.
 * \param[in] cbk 异步事件的回调函数.
 * \param[in] timeout 异步事件的超时.
 *
 * \retval E_OK 初始化成功.
 * \retval E_NO_OK 初始化失败.
 */
Std_ReturnType Async_EventInit(Async_EventType *event, Async_LooperType *looper, Async_EventCbkType cbk, uint32 timeout);

/**
 * \brief 异步事件注册.
 * \details 异步事件需要注册到一个Looper才能被调度.
 *
 * \param[in] event 需要初始化的异步事件.
 *
 * \retval E_OK 注册成功.
 * \retval E_NO_OK 注册失败.
 */
Std_ReturnType Async_EventRegisterToLooper(Async_EventType *event);

/**
 * \brief 触发一个异步事件.
 * \details 可以在超时之前主动触发一个事件的回调函数运行.
 *
 * \param[in] event 需要触发的异步事件.
 * \param[in] trigger 这个值会传递到回调函数, \link Async_EventCbkType \endlink
 *
 * \note trigger用户自定义的值应该在[0x00, ... 0xBF], 其他值为库使用或保留, 目前使用\link ASYNC_TRIGGER_BY_TIMEOUT \endlink (0xFF)表示超时触发.
 *
 * \retval E_OK 触发成功.
 * \retval E_NOT_OK 触发失败.
 */
Std_ReturnType Async_EventTrigger(Async_EventType *event, uint8 trigger);

/**
 * \brief 取消异步事件.
 * \details 把事件从Looper中移除, 这之后这个异步事件将不会被调度.
 *
 * \param[in] event 需要取消的异步事件.
 * \retval E_OK 取消成功.
 * \retval E_NO_OK 取消失败.
 */
Std_ReturnType Async_EventCancel(Async_EventType *event);

/**
 * \brief 重新设置超时时间.
 * \details 重新设置超时时间, 下一次的超时调度时刻将在当前时刻+超时时间.
 *
 * \note 必须在回调函数中才能调用
 *
 * \param[in] event 需要设置的异步事件.
 * \param[in] _timeout 需要设置的超时.
 */
#define Async_EventSetTimeout(event, _timeout) ((event)->timeout = (_timeout))

/**
 * \brief 获取当前设置的超时时间
 * \note 必须在回调函数中才能调用
 *
 * \param      event  需要设置的异步事件
 * \return 返回时间
 */
#define Async_EventGetTimeout(event)    ((event)->timeout)

/**
 * \brief 重新设置回调函数.
 * \details 下次事件发生时, 会调用该函数.
 *
 * \note 必须在回调函数中才能调用
 *
 * \param[in] event 需要设置的异步事件.
 * \param[in] _cbk 需要设置的回调函数.
 */
#define Async_EventSetCallback(event, _cbk) ((event)->cbk = _cbk)

/**
 * \brief 获取异步事件所在Looper.
 *
 * \param[in] event 异步事件指针.
 * \return 该异步事件所在的Looper.
 */
#define Async_EventGetLooper(event)     ((event)->looper)

/**
 * \brief 重新设置超时时间.
 * \details 重新设置超时时间, 下一次的超时调度时刻将在当前时刻+超时时间.
 *
 * \note 可以在任何地方调用, 与\link Async_EventSetTimeout \endlink比较,效率较低;
 *
 * \param[in] event 需要设置的异步事件.
 * \param[in] _timeout 需要设置的超时.
 *
 * \retval E_OK 设置成功.
 * \retval E_NO_OK 设置失败.
 */
Std_ReturnType Async_EventSetTimeoutAsync(Async_EventType *event, uint32 timeout);

/**
 * \brief 重新设置回调函数.
 * \details 下次事件发生时, 会调用该函数.
 * \note 可以在任何地方调用, 与\link Async_EventSetCallback \endlink比较,效率较低;
 *
 * \param[in] event 需要设置的异步事件.
 * \param[in] _cbk 需要设置的回调函数.
 *
 * \retval E_OK 设置成功.
 * \retval E_NO_OK 设置失败.
 */
Std_ReturnType Async_EventSetCbkAsync(Async_EventType *event, Async_EventCbkType cbk);

#endif

 /** \} */
