 /** \addtogroup RingBuffer 循环Buffer
  * \{ */

/**
 * \file Ringbuffer.h
 * \brief 循环Buffer头文件
 */

#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#ifndef RingBuffer_SizeType
#include "Std_Types.h"
typedef uint8 RingBuffer_SizeType;
#endif

#ifndef RINGBUFFER_CHECK
#define RINGBUFFER_CHECK 0
#endif

#define RINGBUFFER_CHECK_MAGIC (0xfade7643UL)

/**
 * \brief 循环Buffer结构体.
 * \details 参考\link RINGBUFFER_DEFINE_STATIC \endlink和\link RINGBUFFER_DEFINE_STATIC \endlink
 */
typedef struct ring_buffer {
#if RINGBUFFER_CHECK != 0
    unsigned long magic; //!< 用于检查指针的有效性.
#endif
    RingBuffer_SizeType cap; //!< 缓冲大小.
    RingBuffer_SizeType len; //!< 已保存数据的长度.
    RingBuffer_SizeType in; //!< 写入数据的游标.
    RingBuffer_SizeType out; //!< 读取数据的游标.
    unsigned char *buf; //!< 缓冲指针.
} RingBuffer_Type;

/**
 * \brief 定义静态循环Buffer的宏.
 * \details 这样定义的循环Buffer可以直接使用, 不用使用\link RingBuffer_Init \endlink来初始化.
 *
 * \param name 需要定义的变量名.
 * \param size 循环Buffer的大小.
 */
#if RINGBUFFER_CHECK != 0
#define RINGBUFFER_DEFINE_STATIC(name, size)  \
static unsigned char __##name##_buffer[size]; \
static struct ring_buffer name = {            \
    (unsigned long)RINGBUFFER_CHECK_MAGIC,    \
    size,                                     \
    0U,                                        \
    0U,                                        \
    0U,                                        \
    __##name##_buffer,                        \
}
#else
#define RINGBUFFER_DEFINE_STATIC(name, size)  \
static unsigned char __##name##_buffer[size]; \
static struct ring_buffer name = {            \
    size,                                     \
    0U,                                        \
    0U,                                        \
    0U,                                        \
    __##name##_buffer,                        \
}
#endif

/**
 * \brief 定义全局循环Buffer的宏.
 * \details 这样定义的循环Buffer可以直接使用, 不用使用\link RingBuffer_Init \endlink来初始化.
 *
 * \param name 需要定义的变量名.
 * \param size 循环Buffer的大小.
 */
#if RINGBUFFER_CHECK != 0
#define RINGBUFFER_DEFINE(name, size)         \
static unsigned char __##name##_buffer[size]; \
RingBuffer_Type name = {                      \
    (unsigned long)RINGBUFFER_CHECK_MAGIC,    \
    size,                                     \
    0U,                                        \
    0U,                                        \
    0U,                                        \
    __##name##_buffer,                        \
}
#else
#define RINGBUFFER_DEFINE(name, size)         \
static unsigned char __##name##_buffer[size]; \
RingBuffer_Type name = {                      \
    size,                                     \
    0U,                                        \
    0U,                                        \
    0U,                                        \
    __##name##_buffer,                        \
}
#endif

/**
 * \brief 初始化循环Buffer.
 * \details 如果用\link RINGBUFFER_DEFINE \endlink或\link RINGBUFFER_DEFINE_STATIC \endlink定义的循环Buffer, 不需要使用该函数初始化.
 *
 * \param rb 需要初始化的循环Buffer.
 * \param buf 缓冲.
 * \param size 缓冲大小.
 */
void RingBuffer_Init(RingBuffer_Type *rb, unsigned char *buf, RingBuffer_SizeType size);

/**
 * \brief RingBuffer_Clear 清空循环Buffer
 *
 * \param rb 需要清空的循环Buffer.
 */
void RingBuffer_Clear(RingBuffer_Type *rb);

/**
 * \brief RingBuffer_PutData 向循环Buffer追加指定长度的相同数据.
 *
 * \param rb 需要追加的循环Buffer.
 * \param uch 追加的数据.
 * \param len 追加的长度.
 *
 * \return 追加的长度, 如果循环Buffer剩余的空间不足, 可能会 < 传入的长度.
 */
RingBuffer_SizeType RingBuffer_PutData(RingBuffer_Type *rb, unsigned char uch, RingBuffer_SizeType len);

/**
 * \brief RingBuffer_TryRead 尝试从循环Buffer读取指定长度的数据.
 *
 * \param rb 需要读取的循环Buffer.
 * \param buf 用于保存读取的数据指针.
 * \param len 尝试读取的长度.
 *
 * \return 返回已经读取的长度, 如果循环Buffer里保存的数据 < 尝试读取的长度, 该返回值会 < 尝试读取的长度.
 */
RingBuffer_SizeType RingBuffer_TryRead(RingBuffer_Type *rb, unsigned char *buf, RingBuffer_SizeType len);

/**
 * \brief RingBuffer_Read 从循环Buffer读取指定长度的数据.
 *
 * \param rb 需要读取的循环Buffer.
 * \param buf 用于保存读取的数据指针.
 * \param len 读取的长度.
 *
 * \return 返回读取的长度, 如果循环Buffer里面存数的数据 < 读取的长度, 将返回0, 循环Buffer里面的数据不会被读取.
 */
RingBuffer_SizeType RingBuffer_Read(RingBuffer_Type *rb, unsigned char *buf, RingBuffer_SizeType len);

/**
 * \brief RingBuffer_TryWrite 尝试向循环Buffer读取指定长度的数据.
 *
 * \param rb 需要写入的循环Buffer.
 * \param dat 需要写入数据的指针.
 * \param len 尝试写入的长度.
 *
 * \return 返回已写入的长度, 如果循环Buffer的空闲空间 < 尝试读取的长度, 该返回值 < 尝试写入的长度.
 */
RingBuffer_SizeType RingBuffer_TryWrite(RingBuffer_Type *rb, const unsigned char *dat, RingBuffer_SizeType len);

/**
 * \brief RingBuffer_Write 向循环Buffer写入指定长度的数据.
 *
 * \param rb 需要写入的循环Buffer.
 * \param dat 需要写入的数据指针.
 * \param len 写入的长度.
 *
 * \return 返回已写入的长度, 如果循环Buffer的空闲空间 < 尝试读取的长度, 将返回0, 循环Buffer不会写入数据.
 */
RingBuffer_SizeType RingBuffer_Write(RingBuffer_Type *rb, const unsigned char *dat, RingBuffer_SizeType len);

/**
 * \brief RingBuffer_LeftSpace 查询循环Buffer空闲的空间.
 *
 * \param rb 需要查询的循环Buffer
 *
 * \return 返回空闲的大小.
 */
RingBuffer_SizeType RingBuffer_LeftSpace(const RingBuffer_Type *rb);

/**
 * \brief RingBuffer_IsEmpty 查询循环Buffer是否为空
 *
 * \param rb 需要查询的循环Buffer
 * \return 0-非空 非0-空
 */
RingBuffer_SizeType RingBuffer_IsEmpty(const RingBuffer_Type *rb);

/**
 * \brief RingBuffer_PopString 从循环Buffer里面读取一个字符串.
 *
 * \param rb 需要读取的循环Buffer
 * \param buf 保存读取的字符串的指针, 如果该指针为空, 将丢弃读取到的数据.
 * \param bufSize 保存字符串的执行内存的大小, 如果读取的数据长度 > bufSize, 多余的数据将被丢弃.
 *
 * \return 保存到buf中的数据长度.
 */
RingBuffer_SizeType RingBuffer_PopString(RingBuffer_Type *rb, char *buf, RingBuffer_SizeType bufSize);

/**
 * \brief RingBuffer_PopStringIsStartWith 从循环Buffer里面读取一个字符串, 并判断该字符串是否以prefix开头.
 *
 * \param rb 需要读取的循环Buffer
 * \param prefix 需要判断的开头的字符串.
 * \param buf 保存读取的字符串的指针, 如果该指针为空, 将丢弃读取到的数据.
 * \param size (*bufSize)保存字符串的指向内存的大小, 如果读取的数据长度 > bufSize, 多余的数据将被丢弃. 同时该值还返回保存到buf中的数据的长度.
 *
 * \return 1 读取到的字符串是以prefix开头; 0 读取到的字符串不以prefix开头.
 */
char RingBuffer_PopStringIsStartWith(RingBuffer_Type *rb, const char *prefix, char *buf, RingBuffer_SizeType *size);

/**
 * \brief 从尾部丢弃一部分数据.
 *
 * \param rb 操作的循环Buffer
 * \param size 丢弃的数据的长度.
 *
 * \return 丢弃的数据的长度, 如果原有数据长度<size, 返回原有数据的长度.
 */
RingBuffer_SizeType RingBuffer_DropDataFromTail(RingBuffer_Type *rb, RingBuffer_SizeType size);

/**
 * \brief 从头部丢弃一部分数据.
 *
 * \param rb 操作的循环Buffer
 * \param size 丢弃的数据的长度.
 *
 * \return 丢弃的数据的长度, 如果原有数据长度<size, 返回原有数据的长度.
 */
RingBuffer_SizeType RingBuffer_DropDataFromHead(RingBuffer_Type *rb, RingBuffer_SizeType size);

#endif

/** \} */