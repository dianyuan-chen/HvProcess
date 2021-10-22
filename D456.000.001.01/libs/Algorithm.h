#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "Std_Types.h"

typedef int(*Algorithm_CmpFuncType)(const void *a, const void *b);
/**
 * 堆排序函数
 * @param base: 需要排序的数据指针
 * @param len: 需要排序的元素个数
 * @param size: 每个元素的数据长度
 * @param cmp: 回调函数,返回两个元素比较结果.返回(a - b)时升序,返回(b - a)时降序
 * @note:
    参数列表与标准库函数qsort一致,可以直接替换qsort.
    不仅可以对数字排序,还可以对字符串排序,关键在于回调函数的实现
    其中元素的比较结果并不一定要计算差,或者返回值为 [-1, 0, 1] 就足够了,当int类型
    为16位且排序的内容为32位时需要特别注意
 */
void HeapSort(void *base, size_t len, size_t size, Algorithm_CmpFuncType cmp);


#endif
