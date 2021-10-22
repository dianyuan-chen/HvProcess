#ifndef SEARCH_H
#define SEARCH_H

#include <Std_Types.h>


/**
 * \brief 获取数值在数组范围的左索引.
 * \details 传入的数组必须是从小到大排列.
 *
 * \param buf 数组
 * \param maxIndex 数组最大索引.
 * \param value 查找的值
 * \return 数值所在范围的左索引.
 */
uint8 OrderedBuffer_GetUint8AscendBufLeftIndex(const uint8 *buf, uint8 right, uint8 value);

/**
 * \brief 获取数值在数组范围的左索引.
 * \details 传入的数组必须是从小到大排列.
 *
 * \param buf 数组
 * \param maxIndex 数组最大索引.
 * \param value 查找的值
 * \return 数值所在范围的左索引.
 */
uint8 OrderedBuffer_GetUint8DescendBufLeftIndex(const uint8 *buf, uint8 right, uint8 value);

/**
 * \brief 获取数值在数组范围的左索引.
 * \details 传入的数组必须是从小到大排列.
 *
 * \param buf 数组
 * \param maxIndex 数组最大索引.
 * \param value 查找的值
 * \return 数值所在范围的左索引.
 */
uint8 OrderedBuffer_GetUint16AscendBufLeftIndex(const uint16 *buf, uint8 right, uint16 value);

/**
 * \brief 获取数值在数组范围的左索引.
 * \details 传入的数组必须是从小到大排列.
 *
 * \param buf 数组
 * \param maxIndex 数组最大索引.
 * \param value 查找的值
 * \return 数值所在范围的左索引.
 */
uint8 OrderedBuffer_GetUint16DescendBufLeftIndex(const uint16 *buf, uint8 right, uint16 value);


/**
 * \brief 获取数值在数组最接近的值的索引, 如果与2个差值相同, 返回左边的数字索引.
 * \details 传入的数组必须是从小到大排列.
 *
 * \param buf 数组
 * \param maxIndex 数组最大索引.
 * \param value 查找的值
 * \return 最接近的数值的索引.
 */
uint8 OrderedBuffer_GetUint8AscendBufIndex(const uint8 *buf, uint8 maxIndex, uint8 value);


/**
 * \brief 获取数值在数组最接近的值的索引, 如果与2个差值相同, 返回左边的数字索引.
 * \details 传入的数组必须是从大到小排列.
 *
 * \param[in] buf 数组
 * \param[in] maxIndex 数组最大索引.
 * \param[in] value 查找的值
 * \return 最接近的数值的索引.
 */
uint8 OrderedBuffer_GetUint8DescendBufIndex(const uint8 *buf, uint8 maxIndex, uint8 value);

/**
 * \brief 获取数值在数组最接近的值的索引, 如果与2个差值相同, 返回左边的数字索引.
 * \details 传入的数组必须是从小到大排列.
 *
 * \param buf 数组
 * \param maxIndex 数组最大索引.
 * \param value 查找的值
 * \return 最接近的数值的索引.
 */
uint8 OrderedBuffer_GetUint16AscendBufIndex(const uint16 *buf, uint8 maxIndex, uint16 value);


/**
 * \brief 获取数值在数组最接近的值的索引, 如果与2个差值相同, 返回左边的数字索引.
 * \details 传入的数组必须是从大到小排列.
 *
 * \param[in] buf 数组
 * \param[in] maxIndex 数组最大索引.
 * \param[in] value 查找的值
 * \return 最接近的数值的索引.
 */
uint8 OrderedBuffer_GetUint16DescendBufIndex(const uint16 *buf, uint8 maxIndex, uint16 value);


/**
 * \brief 把一个数据放入一个已经由小到大排列的Buffer中, 并保持所有数据是由小到大排列的.
 *
 * \param[inout] buf Buffer
 * \param[in] len 原有数据的长度(非Buffer的大小)
 * \param[in] value 需要放入的数据.
 */
void OrderedBuffer_PutUint16Ascend(uint16 *buf, uint8 len, uint16 value);


/**
 * \brief 把一个数据放入一个已经由大到小排列的Buffer中, 并保持所有数据是由大到小排列的.
 *
 * \param[inout] buf Buffer
 * \param[in] len 原有数据的长度(非Buffer的大小)
 * \param[in] value 需要放入的数据.
 */
void OrderedBuffer_PutUint16Descend(uint16 *buf, uint8 len, uint16 value);


/**
 * \brief 计算一个已经排序的Buffer的中间数据的平均值.
 * \details [long description]
 *
 * \param[in] buf Buffer
 * \param[in] len Buffer中数据的长度.
 * \param[in] drop 需要丢弃最大值的长度和最小值的长度,
 * \note 丢弃的值是drop个最大值, drop个最小值.
 */
uint16 OrderedBuffer_AverageUint16CenterValue(const uint16 *buf, uint8 len, uint8 drop);

#endif