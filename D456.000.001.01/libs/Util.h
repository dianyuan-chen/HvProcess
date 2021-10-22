#ifndef __UTIL_H__
#define __UTIL_H__


#include "Std_Types.h"



/**
 * \brief 计算uint16数组的算术平均值
 *
 * \param pdata 数组指针
 * \param size 数组大小
 *
 * \return 平均值
 */
uint16 calc_mean_value(const uint16 *pdata, uint8 size);

/**
 * \brief 测试uint16某bit位是否为1
 *
 * \param bits uint16位图
 * \param shift 偏移位置
 *
 * \return 返回结果
 */
boolean test_bit16(uint16 bits, uint8 shift);

/**
 * \brief 16bit置位
 */
uint16 set_bit16(uint16 bits, uint8 shift);

/**
 * \brief 16bit位清零
 */
uint16 clr_bit16(uint16 bits, uint8 shift);

/**
 * \brief 统计uint16中bit1的个数
 *
 * \param data 待统计的数
 * \param lsb_num 限定统计的位数
 *
 * \return 返回1的数量
 */
uint8 count_int16_bit_1(uint16 data, uint8 lsb_num);

/**
 * \brief 线性插值
 * \details 由已知的两个点确定一条直线，并计算直线上变量x点对应的y值
 *
 * \param para_x1 已知点x坐标1
 * \param para_y1 已知点y坐标1
 * \param para_x2 已知点x坐标2
 * \param para_y2 已知点y坐标2
 * \param para_x 变量x
 * \return 计算的y值
 */
float math_linear_differential_f(float para_x1, float para_y1, float para_x2, float para_y2, float para_x);

#endif
