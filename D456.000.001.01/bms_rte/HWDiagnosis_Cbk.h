/**
 * \file HWDiagnosis_Cbk.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 硬件自检回调函数头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */

/**
 * \addtogroup HWDiagnosis 硬件自检
 * \{
 */


#ifndef HWDIAGNOSIS_CBK_H_
#define HWDIAGNOSIS_CBK_H_

#include "Std_Types.h"
#include "HWDiagnosis.h"

/**
 * \brief 板载电压新ADC转换完成回调函数
 * \note 由硬件确定支持的ADC转换，不支持获取ADC值的板载电压使用 \link HWDiagnosis_VoltNewIndication \endlink
 *
 * \param VoltType 板载电压类型
 * \param AdcValue ADC值
 */
void HWDiagnosis_VoltAdcNewIndication(HWDiagnosis_BoardVoltType VoltType, uint16 AdcValue);

/**
 * \brief 新板载电压回调函数
 * \note 用于直接获取到电压值的板载电压类型，由硬件决定
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Voltage 数据长度
 */
void HWDiagnosis_VoltNewIndication(HWDiagnosis_BoardVoltType Offset, const uint8* DataPtr, HWDiagnosis_BoardVoltType Length);

/**
 * \brief 板载温度新ADC转换完成回调函数
 * \note 由硬件确定支持的ADC转换，不支持获取ADC值的板载温度使用 \link HWDiagnosis_TempNewIndication \endlink
 *
 * \param TempType 板载温度类型
 * \param AdcValue ADC值
 */
void HWDiagnosis_TempAdcNewIndication(HWDiagnosis_BoardTempType TempType, uint16 AdcValue);

/**
 * \brief 新板载温度回调函数
 * \note 用于直接获取到温度值的板载温度类型，由硬件决定
 *
 * \param SlaveId 从机号
 * \param DataPtr 数据缓存
 * \param Voltage 数据长度
 */
void HWDiagnosis_TempNewIndication(HWDiagnosis_BoardTempType Offset, const uint8* DataPtr, uint16 Length);

/**
 * \brief 清除从机板载电压回调函数
 * \details 当从机出现通信中断时，调用此函数来清除对应从机的相关板载电压信息
 *
 * \param SlaveId 从机号
 */
void HWDiagnosis_VoltClrIndication(HWDiagnosis_BoardVoltType Offset, HWDiagnosis_BoardVoltType Length);

/**
 * \brief 清除从机板载温度回调函数
 * \details 当从机出现通信中断时，调用此函数来清除对应从机的相关板载温度信息
 *
 * \param SlaveId 从机号
 */
void HWDiagnosis_TempClrIndication(HWDiagnosis_BoardTempType Offset, HWDiagnosis_BoardTempType Length);



#endif

/**
 * \}
 */
