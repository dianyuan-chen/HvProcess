/**
 * \file SocCalib_Cbk.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Soc校正回调函数头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170223 |
 */
#ifndef SOC_CALIB_CBK_H_
#define SOC_CALIB_CBK_H_

#include "SocDiagCalib.h"

/**
 * \brief SOC过充等诊断满校正回调函数
 *
 * \param item 诊断项
 * \param level 报警等级
 * \param event 报警类型
 */
void SocDiagCalib_FullCalibCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief SOC过充等诊断满校正释放回调函数
 *
 * \param item 诊断项
 * \param level 报警等级
 * \param event 报警类型
 */
void SocDiagCalib_FullCalibRelCbk(Diagnosis_ItemType item , Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief SOC过放等诊断空校正回调函数
 *
 * \param item 诊断项
 * \param level 报警等级
 * \param event 报警类型
 */
void SocDiagCalib_EmptyCalibCbk(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief SOC过放等诊断空校正释放回调函数
 *
 * \param item 诊断项
 * \param level 报警等级
 * \param event 报警类型
 */
void SocDiagCalib_EmptyCalibRelCbk(Diagnosis_ItemType item , Diagnosis_LevelType level, Diagnosis_EventType event);




#endif