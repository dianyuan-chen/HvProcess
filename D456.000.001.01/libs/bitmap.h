#ifndef __LINUX_BITMAP_H
#define __LINUX_BITMAP_H


#include "bitops.h"

#define BITS_NUM_TO_MASK(NUM)   ((NUM) < 32U ? Bitmap_BitsMask[NUM] : 0xFFFFFFFF)

extern const unsigned long Bitmap_BitsMask[32];

/**
 * \brief 置位位图中的bits
 * \details 置位指定起始及长度的位图中的位
 *
 * \param char 位图指针
 * \param int 全局起始位
 * \param len 位长度
 */
extern void bitmap_set(unsigned char *map, unsigned int start, int len);

/**
 * \brief 清零位图中的bits
 * \details 清零指定起始及长度的位图中的位
 *
 * \param char 位图指针
 * \param int 全局起始位
 * \param len 位长度
 */
extern void bitmap_clear(unsigned char *map, unsigned int start, int len);

/**
 * \brief 获取位状态
 * \details 获取位图中指定位的状态
 *
 * \param char 位图指针
 * \param int 查询位
 *
 * \return 1:已置位 0:未置位
 */
extern unsigned char bitmap_get(const unsigned char *map, unsigned int bit);





#endif /* __LINUX_BITMAP_H */