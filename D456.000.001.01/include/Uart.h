/**
 * \addtogroup Uart 串口驱动
 * \{
 */

#ifndef UART_H
#define UART_H

#include "Std_Types.h"
#include "Uart_Cfg.h"

typedef void (*Uart_RxIndication)(void *UserData, uint8 dat);

#include "Uart_Types.h"

/**
 * \brief UART通道类型.
 */
typedef uint8 Uart_ChannelType;

/**
 * \brief 发送时从上层拷贝数据.
 * \link Uart_SendAsync \endlink, \link Uart_SetAsyncSendCompleteNotifier \endlink.
 *
 * \param[out] buf 用于保存拷贝的数据.
 * \size[in] 期望拷贝的大小.
 *
 * \return 拷贝数据的大小.
 * \note 如果返回值<传入的size, 那么数据发送完成, 则不会进一步发送数据.
 */
typedef uint8 (*Uart_CopyTxData)(void *UserData, uint8 *buf, uint8 size);

/**
 * \brief 初始化Uart
 *
 * \param channel Uart通道
 * \param baud 波特率
 *
 * \retval E_OK 初始化成功
 * \retval E_NOT_OK 初始化失败
 */
Std_ReturnType Uart_Init(Uart_ChannelType channel, uint32 baud, Uart_RxIndication RxIndication, void *UserData);


/**
 * \brief 设置串口波特率
 *
 * \param channel Uart通道
 * \param baud 波特率
 *
 * \retval E_OK 设置成功
 * \retval E_NOT_OK 设置失败
 */
Std_ReturnType Uart_SetBaudrate(Uart_ChannelType channel, uint32 baud);

/**
 * \brief 设置异步发送回调函数.
 * \details \link Uart_AsyncSendCompleteNotify \endlink, \link Uart_SendAsync \endlink.
 *
 * \param notifier [description]
 * \return [description]
 */
//Std_ReturnType Uart_SetAsyncSendCompleteNotifier(Uart_SendCompleteNotify notifier);

/**
 * \brief 异步发送
 * \details 把发送数据交给驱动去处理, 并立刻返回; 在发送完成之后调用设置好的回调函数;
 * 在所有数据发送完成之前, 调用者必须保证数据的有效性;
 * \link Uart_AsyncSendCompleteNotify \endlink, \link Uart_SetAsyncSendCompleteNotifier \endlink.
 *
 * \param channel UART通道.
 * \param copyTxData 数据拷贝函数.
 * \retval E_OK 数据已经发送驱动层
 * \retval E_NOT_OK 错误
 */
Std_ReturnType Uart_SendAsync(Uart_ChannelType channel, Uart_CopyTxData copyTxData);

/**
 * \brief 同步发送.
 * \details 同步发送数据, 在数据发送完成或发送错误的时候返回.
 *
 * \param channel UART通道.
 * \param dat 需要发送的数据的指针.
 * \param size 需要发送的数据的大小.
 * \retval E_OK 数据已经发送驱动层
 * \retval E_NOT_OK 错误
 */
Std_ReturnType Uart_SendSync(Uart_ChannelType channel, const uint8 *dat, uint8 size);


/**
 * \brief 同步发送.
 * \details 同步发送数据, 在数据发送完成或发送错误的时候返回.
 *
 * \param channel UART通道.
 * \param dat 需要发送的数据的指针.
 * \retval E_OK 数据已经发送驱动层
 * \retval E_NOT_OK 错误
 */
Std_ReturnType Uart_SendByteAsync(Uart_ChannelType channel, uint8 dat);

void Uart_Isr(Uart_ChannelType channel);

void SCI1_Isr(void);
void SCI2_Isr(void);

#endif
/** \} */
