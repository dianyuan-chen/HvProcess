#ifndef __LINUX_BITMAP_H
#define __LINUX_BITMAP_H


#include "bitops.h"

#define BITS_NUM_TO_MASK(NUM)   ((NUM) < 32U ? Bitmap_BitsMask[NUM] : 0xFFFFFFFF)

extern const unsigned long Bitmap_BitsMask[32];

/**
 * \brief ��λλͼ�е�bits
 * \details ��λָ����ʼ�����ȵ�λͼ�е�λ
 *
 * \param char λͼָ��
 * \param int ȫ����ʼλ
 * \param len λ����
 */
extern void bitmap_set(unsigned char *map, unsigned int start, int len);

/**
 * \brief ����λͼ�е�bits
 * \details ����ָ����ʼ�����ȵ�λͼ�е�λ
 *
 * \param char λͼָ��
 * \param int ȫ����ʼλ
 * \param len λ����
 */
extern void bitmap_clear(unsigned char *map, unsigned int start, int len);

/**
 * \brief ��ȡλ״̬
 * \details ��ȡλͼ��ָ��λ��״̬
 *
 * \param char λͼָ��
 * \param int ��ѯλ
 *
 * \return 1:����λ 0:δ��λ
 */
extern unsigned char bitmap_get(const unsigned char *map, unsigned int bit);





#endif /* __LINUX_BITMAP_H */