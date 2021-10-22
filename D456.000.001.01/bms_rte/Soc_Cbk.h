/**
 * \addtogroup SOC
 * \{
 */

#ifndef SOC_CBK_H
#define SOC_CBK_H

#include "Soc.h"
#include "Current_Types.h"

/**
 * \brief 采集到新的电流值后的回调函数.
 * \note 在电流管理的模块中已经实现了电流的滤波.
 *
 * \param current 之前一段时间内的平均电流.
 * \param current_time 平均电流计算的时间
 * \note 电流积分有2中实现方式: 1,把当前电流值与时间戳存放到缓冲, 由单独的电流积分任务进行计算; 2,直接在这个函数中进行积分运算.
 */
void Soc_NewAverageCurrentIndication(Current_CurrentType current, uint32 current_time);



#endif

/** \} */
