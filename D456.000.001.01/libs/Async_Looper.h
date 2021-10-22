/** \addtogroup Async 异步事件框架
 * \{ */

/**
 * \file Async_Looper.h
 * \brief 异步事件循环声明.
 * \author U0005
 * \version 1.0
 * \date 2016-11-23
 */

#ifndef __ASYNC_LOOPER_H__
#define __ASYNC_LOOPER_H__

#include "Std_Types.h"
#include "RingBuffer.h"
#include "ucos_ii.h"
#include "list.h"

/**
 * \brief 异步事件循环
 */
typedef struct {
    RingBuffer_Type rb; //!< 内部使用的用于控制的缓冲.
    struct list_head events; //!< 需要调度的异步事件链表头.
    OS_EVENT *sem; //!< 内部使用的用于控制的信号量.
} Async_LooperType;

/**
 * \brief 初始化事件循环.
 * \details 在事件循环使用之前先需要初始化.
 *
 * \param looper 需要初始化的事件循环.
 * \param cmdBuf 内部使用的缓冲, \link Async_LooperType \endlink
 * \param bufSize 内部使用的缓冲大小.
 * \retval E_OK 初始化成功.
 * \retval E_NOT_OK 初始化失败.
 */
Std_ReturnType Async_LooperInit(Async_LooperType *looper, unsigned char *cmdBuf, RingBuffer_SizeType bufSize);

/**
 * \brief 异步事件循环.
 * \details 该函数是一个死循环函数, 在没有明确调用\link Async_LooperExit \endlink之前不会退出.
 *
 * \param looper 事件循环
 */
void Async_LooperLoop(Async_LooperType *looper);

/**
 * \brief 退出一个正在执行的事件循环.
 * \details \link Async_LooperLoop \endlink
 *
 * \param looper 事件循环
 * \retval E_OK 退出成功.
 * \retval E_NOT_OK 退出失败.
 */
Std_ReturnType Async_LooperExit(Async_LooperType *looper);

#endif

 /** \} */