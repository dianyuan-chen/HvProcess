/**
 * \addtogroup TermIO 终端IO
 * \{
 */

#ifndef TERMIO_H
#define TERMIO_H

#include "Std_Types.h"
#include "ComStack_Types.h"

#define TERMIO_VIA_CAN 0
#define TERMIO_VIA_STDIO 1

#include "Termio_Cfg.h"

void TERMIO_Init(void);
/**
 * \brief 通过TERMIO发送一个字符.
 *
 * \param c 需要发送的字符.
 */
void TERMIO_PutChar(char c);


/**
 * \brief 通过TERMIO读取一个字符.
 *
 * \return 读取到的字符.
 */
char TERMIO_GetChar(void);

/**
 * \brief 当用CAN实现TERMIO时, 这个函数用于CanIf层接收回调.
 *
 * \param RxPduId CanIf接收的PDU ID.
 * \param PduInfoPtr CanIf接收到的数据.
 */
void TERMIO_CanRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);

/**
 * \brief 当用CAN实现TERMIO时, 这个函数用于CanIf层发送确认回调.
 *
 * \param RxPduId CanIf接收的PDU ID.
 */
void TERMIO_TxConfirmation(PduIdType TxPduId);

/**
 * \brief 从TERMIO读取一行数据.
 * \details 需要在Termio_Cfg.h中定义\link TERMIO_END_OF_LINE \endlink为'\\r'或'\\n', 该字符知道行数据的结束符.
 *
 * \param buf 数据存放的缓冲.
 * \param buf_size 缓冲区大小.
 *
 * \return 接收到的数据的长度.
 */
uint8 TERMIO_Readline(char *buf, uint8 buf_size);

/**
 * \brief 清空发送缓冲.
 * \details 会导致发送缓冲中的数据立刻发送出去.
 */
void TERMIO_Flush(void);

#endif

/** \} */
