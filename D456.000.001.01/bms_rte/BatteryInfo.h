/**
 * \file BatteryInfo.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 电池信息头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170614 |
 */

#ifndef BATTERY_INFO_H_
#define BATTERY_INFO_H_


#include "Std_Types.h"
#include "App_Types.h"

/**
 * \brief 应用层配置参数类型定义
 */
typedef struct{
    uint8 Type; /**< 电池类型 */
    App_CapType NominalCap; /**< 额定容量 */
    App_CurrentType NominalDischargeCurrent; /**< 额定放电电流 */
    App_Tv100mvType NominalTotalVolt; /**< 额定总压 */
    App_CurrentType NominalDCCurrent; /**< 快充额定电流 */
    App_CurrentType NominalACCurrent; /**< 慢充额定电流 */
    uint16 SeriesNum; /**< 电池串数 */
    uint16 ParallelNum; /**< 电池并数 */
    uint16 CellTemperatureNum; /**< 单体温感数 */
    uint16 InitialSOC; /**< 初始SOC */
    uint16 InitialSOH; /**< 初始SOH */
    uint16 PoleTemperatureNum; /**< 极柱温感数*/
    uint16 HeatTemperatureNum; /**< 加热温感数*/
    App_VoltageType HighVoltLimit; /**< 单体电压高极限保护 */
    App_VoltageType LowVoltLimit; /**< 单体电压低极限保护 */
    App_VoltageType HighTempLimit; /**< 单体温度高极限保护 */
    uint32 LimitProtectDelay; /**< 极限保护延时 */
}BatteryInfo_BaseConfigType;

/**
 * \brief 应用层配置参数
 */
extern const BatteryInfo_BaseConfigType BatteryInfo_BaseConfigInfo;




#endif
