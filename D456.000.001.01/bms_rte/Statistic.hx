/**
 * \file Statistic.hx
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief XGate电池统计头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170116 |
 */

/**
 * \addtogroup Statistic 统计信息
 \{
 */

#ifndef STATISTIC_HX_
#define STATISTIC_HX_

#include "Std_Types.h"
#include "Statistic.h"

typedef union{
    struct{
        uint8 HvNum;
        uint8 LvNum;
        Statistic_VoltageItemType HvItemBuffer[STATISTIC_VOLTAGE_NUM];
        Statistic_VoltageItemType LvItemBuffer[STATISTIC_VOLTAGE_NUM];
    }VoltageInfo;
    struct{
        uint8 HtNum;
        uint8 LtNum;
        Statistic_TemperatureItemType HtItemBuffer[STATISTIC_TEMPERATURE_NUM];
        Statistic_TemperatureItemType LtItemBuffer[STATISTIC_TEMPERATURE_NUM];
    }TemperatureInfo;
}XStatistic_InternalType;


/**
 * \brief 从机统计信息电压统计更新
 * \details 从机统计信息内容参见\link Statistic_BmuInfoType \endlink
 *
 * \param SlaveNum 从机号
 */
void XStatistic_SlaveVoltStatistic(App_SlaveIdType SlaveNum);

/**
 * \brief 从机统计信息温度统计更新
 * \details 从机统计信息内容参见\link Statistic_BmuInfoType \endlink
 *
 * \param SlaveNum 从机号
 */
void XStatistic_SlaveTemperatureStatistic(App_SlaveIdType SlaveNum);

/**
 * \brief 清除从机统计信息
 * \details 清除包含电压统计、温度统计相关信息，请参考\link Statistic_BmuInfoType \endlink
 *
 * \param SlaveNum 从机号
 */
void XStatistic_ClrSlaveStatistic(App_SlaveIdType SlaveNum);

/**
 * \brief 从机采集板统计信息统计更新
 * \details 从机采集板统计信息仅统计每个采集板最高单体电压，个数由每采集板均衡路数确定
 *
 * \param SlaveNum 从机号
 */
void XStatistic_SlaveBoardHvStatistic(App_SlaveIdType SlaveNum);

/**
 * \brief 从机采集板统计信息统计更新
 * \details 从机采集板统计信息仅统计每个采集板最低单体电压，个数由每采集板均衡路数确定
 *
 * \param SlaveNum 从机号
 */
void XStatistic_SlaveBoardLvStatistic(App_SlaveIdType SlaveNum);

/**
 * \brief 更新BCU电池电压统计信息
 * \details 统计包含单体最高、最低电压、平均电压、累加总压及编号信息等
 */
void XStatistic_BcuVoltageStatistic(void);

/**
 * \brief 更新BCU电池温度统计信息
 * \details 统计包含单体最高、最低温度、平均温度及编号信息等
 */
void XStatistic_BcuTemperatureStatistic(void);


#endif

/**
 * \}
 */