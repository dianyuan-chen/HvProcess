/**
 * \addtogroup Statistic 统计信息
 *
 * \{
 */



/**
 * \file Statistic.h
 * \brief 统计信息文件.
 */

#ifndef STATISTIC_H_
#define STATISTIC_H_

#include "App_Types.h"
#include "CellDataM_Types.h"
#include "Statistic_Cfg.h"
#include "BalanceM_Cfg.h"
#include "SystemConnection.h"
#include "Async_Looper.h"
#include "Async_Event.h"
#include "RuntimeM.h"

#define STATISTIC_TIME_INVALID_VALUE		0xFFFFFFFFUL

#define STATISTIC_CUMU_AND_SAMPLE_TV_DIFF_MAX		V_TO_100MV(10U)

/**
 * \todo Need to include balance num allowed for sample board high voltage statistic
 */

#pragma push
#pragma align on

/**
 * \brief 单体电压统计数据项类型定义
 * \note 包含单体电压、从机号、从机内编号
 *
 * \remarks 统计数据存放地址需对XGATE可见
 */
typedef struct {
	App_VoltageType Voltage; /**< 电压值 */
	App_SlaveIdType Slave; /**< 从机号 */
	uint8 Index; /**< 从机内索引 */
}Statistic_VoltageItemType;

/**
 * \brief 单体温度统计数据项类型定义
 * \note 包含单体温度、从机号、从机内编号
 *
 * \remarks 统计数据存放地址需对XGATE可见
 */
typedef struct {
	App_TemperatureType Temperature; /**< 温度值 */
	App_SlaveIdType Slave; /**< 从机号 */
	uint8 Index; /**< 从机内索引 */
}Statistic_TemperatureItemType;

/**
 * \brief 电池电压数据统计数据类型定义
 *
 * \remarks 统计数据存放地址需对XGATE可见
 */
typedef struct{
	uint16 ValidVoltageNum; /**< 有效电压个数 */
	uint16 InvalidVoltageNum; /**< 无效电压个数，不包含通信中断从机 */
	App_Tv1mvType TotalVoltage; /**< 电池累加总压 */
	App_VoltageType AverageVoltage; /**< 平均电压值 */
	App_VoltageType DeltaVoltage; /**< 最大压差值 */
	uint8 HvNum; /**< 高压个数 */
	uint8 LvNum; /**< 低压个数 */
	Statistic_VoltageItemType HvItem[STATISTIC_VOLTAGE_NUM]; /**< 高压统计项 */
	Statistic_VoltageItemType LvItem[STATISTIC_VOLTAGE_NUM]; /**< 低压统计项 */
}Statistic_VoltageInfoType;

/**
 * \brief 电池温度数据统计数据类型定义
 *
 * \remarks 统计数据存放地址需对XGATE可见
 */
typedef struct {
	uint16 ValidTemperatureNum; /**< 有效温感个数 */
	uint16 InvalidTemperatureNum; /**< 无效温度个数， 不包含通信中断从机 */
	App_TemperatureType AverageTemperature; /**< 平均温度值 */
	App_TemperatureType DeltaTemperature; /**< 最大温差值 */
	uint8 HtNum; /**< 高温个数 */
	uint8 LtNum; /**< 低温个数 */
	Statistic_TemperatureItemType HtItem[STATISTIC_TEMPERATURE_NUM]; /**< 高温统计项 */
	Statistic_TemperatureItemType LtItem[STATISTIC_TEMPERATURE_NUM]; /**< 低温统计项 */
}Statistic_TemperatureInfoType;

/**
 * \brief bmu数据统计数据类型定义
 *
 * \remarks 统计数据存放地址需对XGATE可见
 */
typedef struct{
	Statistic_VoltageInfoType VoltageInfo; /**< 电池电压信息 */
	Statistic_TemperatureInfoType TemperatureInfo; /**< 电池温度信息 */
	Statistic_TemperatureInfoType HeatTemperatureInfo; /**< 加热温度信息 */
	Statistic_TemperatureInfoType PoleTemperatureInfo; /**< 极柱温度信息 */
}Statistic_BmuInfoType;

/**
 * \brief bcu数据统计数据类型定义
 *
 * \remarks 统计数据存放地址需对XGATE可见
 */
typedef struct{
	Statistic_VoltageInfoType VoltageInfo; /**< 电池电压信息 */
	Statistic_TemperatureInfoType TemperatureInfo; /**< 电池温度信息 */
	Statistic_TemperatureInfoType HeatTemperatureInfo; /**< 加热温度信息 */
	Statistic_TemperatureInfoType PoleTemperatureInfo; /**< 极柱温度信息 */
	uint16 BatteryChargeCount; /**< 电池充放电次数 */
	uint32 EclipseChargeTime; /**< 已充电时间 S/bit */
	uint32 RequireChargeTime; /**< 剩余充电时间 S/bit */
	uint32 EclipseDischargeTime; /**< 已放电时间 S/bit */
	uint32 RequireDischargeTime; /**< 剩余放电时间 S/bit */
}Statistic_BcuInfoType;

/**
 * \brief 总压类型类型定义
 * \note 定义有累加总压和高压采样总压
 */
typedef enum{
	STATISTIC_TV_TYPE_CUMULATE_PRIO, /**< 累加总压优先类型 */
	STATISTIC_TV_TYPE_SAMPLE_PRIO, /**< 采样总压优先类型 */
	STATISTIC_TV_TYPE_CUMULATE_ONLY, /**< 仅使用累加总压类型 */
	STATISTIC_TV_TYPE_SAMPLE_ONLY, /**< 仅使用采样总压类型 */
}Statistic_TvTypeType;

typedef struct{
	Statistic_TvTypeType prior_tv_type; /**< 优先使用总压类型 */
	uint8 cumuChgTimeEnable; /**< 累计充电时间使能 */
	uint8 cumuDchgTimeEnable; /**< 累计放电时间使能 */
}Statistic_ConfigInfoType;

#pragma pop

typedef struct{
	boolean start;
	Async_EventType asyncEvent;
	uint32 chargeTimeLast;
	uint32 dischargeTimeLast;
	App_Tv100mvType totalVoltage;
	boolean isTotalVoltageReady;
	uint32 totalVoltageTick;
	boolean isSimulationHtLt; /**< 是否使用模拟高温低温值 */
	App_TemperatureType simulationHt; /**< 模拟高温 */
	App_TemperatureType simulationLt; /**< 模拟低温 */
	uint32 cumuChgTime;
	uint32 cumuChgTimeCnt;
	uint32 cumuDchgTime;
	uint32 cumuDchgTimeCnt;
}Statistic_innerDataType;


#pragma push
#pragma DATA_SEG __GPAGE_SEG XGATE_DATA
#pragma CONST_SEG __GPAGE_SEG XGATE_CONST
/**
 * \brief 主机统计信息
 *
 * \remarks 止段内存需对XGATE可见
 */
extern Statistic_BcuInfoType Statistic_BcuInfo;

/**
 * \brief 从机单体电压统计缓存数组.
 *
 * \remarks 此段内存需对XGATE可见
 */

extern Statistic_BmuInfoType Statistic_SlaveInfo[BCU_SLAVE_NUM_MAX];

/**
 * \brief 从机单LTC6804采集板最高单体电压位置统计缓存
 * \note 每个LTC6804最高单体电压位置统计，注：每个从机的实际LTC6804个数以配置的从机型号为准。
 *
 * \remarks 此段内存需对XGATE可见
 */
extern uint8 Statistic_SampleBoardHighVoltage[BCU_SLAVE_NUM_MAX][BMU_LTC6804_NUM_MAX * BALANCEM_BMU_BOARD_BALANCE_NUM_MAX];

/**
 * \brief 从机单LTC6804采集板最低单体电压位置统计缓存
 * \note 每个LTC6804最低单体电压位置统计，注：每个从机的实际LTC6804个数以配置的从机型号为准。
 *
 * \remarks 此段内存需对XGATE可见
 */
extern uint8 Statistic_SampleBoardLowVoltage[BCU_SLAVE_NUM_MAX][BMU_LTC6804_NUM_MAX];

#pragma pop

/**
 * \brief 统计配置信息声明
 * \details 包含与统计相关的配置项
 */
extern const Statistic_ConfigInfoType Statistic_ConfigInfo;

/**
 * \brief 统计模块初始化函数
 */
void Statistic_Init(Async_LooperType *looper);

/**
 * \brief 获取已充电时间
 * \note  单位：S
 */
uint32 Statistic_GetEclipseChargeTime(void);

/**
 * \brief 获取剩余充电时间
 * \note  单位：S
 */
uint32 Statistic_GetRequireChargeTime(void);

/**
 * \brief 获取已放电时间
 * \note  单位：S
 */
uint32 Statistic_GetEclipseDischargeTime(void);

/**
 * \brief 获取剩余放电时间
 * \note  单位：S
 */
uint32 Statistic_GetRequireDischargeTime(void);

/**
 * \brief 获取有效电压个数
 *
 * \return 有效电压个数
 */
uint16 Statistic_GetBcuValidVoltageNum(void);

/**
 * \brief 获取异常电压个数
 */
uint16 Statistic_GetBcuInvalidVoltageNum(void);

/**
 * \brief 获取有效温感个数
 */
uint16 Statistic_GetBcuValidTemperatureNum(void);

/**
 * \brief 获取异常温感个数
 */
uint16 Statistic_GetBcuInvalidTemperatureNum(void);

/**
 * \brief 获取BCU统计累加总压值
 *
 * \return 累加总压值 1mv/bit
 */
App_Tv1mvType Statistic_GetBcuTotalVoltage(void);

/**
 * \brief 获取平均电压值
 */
App_VoltageType Statistic_GetBcuAverageVoltage(void);

/**
 * \brief 获取最大压差值
 */
App_VoltageType Statistic_GetBcuDeltaVoltage(void);

/**
 * \brief 获取平均温度值
 */
App_TemperatureType Statistic_GetBcuAverageTemperature(void);

/**
 * \brief 获取最大温差值
 * \note  与温度偏移量一致，返回值有TEMPERATURE_OFFSET偏移量
 */
App_TemperatureType Statistic_GetBcuDeltaTemperature(void);

/**
 * \brief 获取单体高压个数
 * \note  返回值不超过STATISTIC_VOLTAGE_NUM
 */
uint8 Statistic_GetBcuHvNum(void);

/**
 * \brief 获取单体低压个数
 * \note  返回值不超过STATISTIC_VOLTAGE_NUM
 */
uint8 Statistic_GetBcuLvNum(void);

/**
 * \brief 获取单体高温个数
 * \note  返回值不超过STATISTIC_TEMPERATURE_NUM
 */
uint8 Statistic_GetBcuHtNum(void);

/**
 * \brief 获取单体低温个数
 * \note  返回值不超过STATISTIC_TEMPERATURE_NUM
 */
uint8 Statistic_GetBcuLtNum(void);

/**
 * \brief 获取最高单体电压
 * \note  输入编号0对应电压最高，其次是编号1，以此类推
 *
 * \param index 最高电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 返回对应编号的电压值，可能返回无效值
 */
App_VoltageType Statistic_GetBcuHv(uint8 index);

/**
 * \brief 获取最高单体电压从机号
 * \note  输入编号0对应电压最高，其次是编号1，以此类推
 *
 * \param index 最高电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 从机ID，从0开始
 */
App_SlaveIdType Statistic_GetBcuHvSlaveNum(uint8 index);

/**
 * \brief 获取最高单体电压从机内串号
 * \note  输入编号0对应电压最高，其次是编号1，以此类推
 *
 * \param index 最高电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 从机内串号，从0开始
 */
uint8 Statistic_GetBcuHvIndex(uint8 index);

/**
 * \brief 获取最高单体电压逻辑编号
 * \note  输入编号0对应电压最高，其次是编号1，以此类推
 *
 * \param index 最高电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 电池全局逻辑串号，从0开始
 */
CellDataM_CellLogicIndexType Statistic_GetBcuHvLogicIndex(uint8 index);

/**
 * \brief 获取最低单体电压
 * \note  输入编号0对应电压最低，其次是编号1，以此类推
 *
 * \param index 最低电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 返回对应编号的电压值，可能返回无效值
 */
App_VoltageType Statistic_GetBcuLv(uint8 index);

/**
 * \brief 获取最低单体电压从机号
 * \note  输入编号0对应电压最低，其次是编号1，以此类推
 *
 * \param index 最低电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 从机ID，从0开始
 */
App_SlaveIdType Statistic_GetBcuLvSlaveNum(uint8 index);

/**
 * \brief 获取最低单体电压从机内索引号
 * \note  输入编号0对应电压最低，其次是编号1，以此类推
 *
 * \param index 最低电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 从机内串号，从0开始
 */
uint8 Statistic_GetBcuLvIndex(uint8 index);

/**
 * \brief 获取最低单体电压逻辑编号
 * \note  输入编号0对应电压最低，其次是编号1，以此类推
 *
 * \param index 最低电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 电池全局逻辑串号，从0开始
 */
CellDataM_CellLogicIndexType Statistic_GetBcuLvLogicIndex(uint8 index);

/**
 * \brief 获取最高温度
 * \note  输入编号0对应温度最高，其次是编号1，以此类推
 *
 * \param index 最高温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 返回对应编号的温度值，可能返回无效值
 */
App_TemperatureType Statistic_GetBcuHt(uint8 index);

/**
 * \brief 获取最高温度从机号
 * \note  输入编号0对应温度最高，其次是编号1，以此类推
 *
 * \param index 最高温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 从机ID，从0开始
 */
App_SlaveIdType Statistic_GetBcuHtSlaveNum(uint8 index);

/**
 * \brief 获取最高温度从机内索引号
 * \note  输入编号0对应温度最高，其次是编号1，以此类推
 *
 * \param index 最高温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 从机内温度编号，从0开始
 */
uint8 Statistic_GetBcuHtIndex(uint8 index);

/**
 * \brief 获取最高温度逻辑引号
 * \note  输入编号0对应温度最高，其次是编号1，以此类推
 *
 * \param index 最高温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 温度全局逻辑编号，从0开始
 */
CellDataM_CellLogicIndexType Statistic_GetBcuHtLogicIndex(uint8 index);

/**
 * \brief 获取最低温度
 * \note  输入编号0对应温度最低，其次是编号1，以此类推
 *
 * \param index 最低温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 返回对应编号的温度值，可能返回无效值
 */
App_TemperatureType Statistic_GetBcuLt(uint8 index);

/**
 * \brief 获取最低温度从机号
 * \note  输入编号0对应温度最低，其次是编号1，以此类推
 *
 * \param index 最低温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 从机ID，从0开始
 */
App_SlaveIdType Statistic_GetBcuLtSlaveNum(uint8 index);

/**
 * \brief 获取最低温度从机内索引号
 * \note  输入编号0对应温度最低，其次是编号1，以此类推
 *
 * \param index 最低温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 从机内温度编号，从0开始
 */
uint8 Statistic_GetBcuLtIndex(uint8 index);

/**
 * \brief 获取最低温度逻辑引号
 * \note  输入编号0对应温度最低，其次是编号1，以此类推
 *
 * \param index 最低温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 温度全局逻辑编号，从0开始
 */
CellDataM_CellLogicIndexType Statistic_GetBcuLtLogicIndex(uint8 index);

/**
 * \brief 获取电池充放电次数
 */
uint16 Statistic_GetBcuBatteryDischargeCount(void);

/**
 * \brief 获取单体最高电压
 * \note  此函数用于故障诊断，功能同Statistic_GetBcuHv(0U)
 *
 * \return 最高电压，分辨率：1mv/bit
 */
uint16 Statistic_GetBcuHvMax(void);
/**
 * \brief 获取单体最低电压
 * \note  此函数用于故障诊断，功能同Statistic_GetBcuLv(0U)
 *
 * \return 最低电压，分辨率：1mv/bit
 */
uint16 Statistic_GetBcuLvMax(void);

/**
 * \brief 获取总压值(100mv分辨率)
 *
 * \return 总压值
 */
App_Tv100mvType Statistic_GetBcu100mvTotalVoltage(void);

/**
 * \brief BCU总压是否已经准备就绪
 * \details 需要累加总压和采样总压同时准备就绪
 * \return TRUE-就绪 FALSE-未就绪
 */
uint8 Statistic_Bcu100MvTotalVoltageIsReady(void);

/**
 * \brief 获取总压差值
 * \note  此函数返回总压为通过特定总压计算策略获取，计算策略包含累加总压和采样总压的比较
 *
 * \return 总压值，分辨率：100mv/bit
 */
App_Tv100mvType Statistic_GetBcuDeltaTotalVoltage(void);

/**
 * \brief 判断累加总压值是否有效定义
 *
 * \param voltage  累加总压，精度：1mv/bit
 * \return 0:无效 1：有效
 */
uint8 Statistic_AccTotalVoltageIsValid(uint32 voltage);

/**
 * \brief 判断总压值是否有效定义
 *
 * \param voltage  总压值，精度：0.1v/bit
 * \return 0:无效 1：有效
 */
uint8 Statistic_TotalVoltageIsValid(uint16 voltage);

/**
 * \brief 获取单体最大压差值
 *
 * \return 最大压差值，分辨率：1mv/bit
 */
uint16 Statistic_GetBcuDvMax(void);

/**
 * \brief 获取最高温度
 * \note  此函数用于故障诊断，功能同Statistic_GetBcuHt(0U)
 *
 * \return 最高温度值
 */
uint16 Statistic_GetBcuHtMax(void);

/**
 * \brief 获取最低温度
 * \note  此函数用于故障诊断，功能同Statistic_GetBcuLt(0U)
 *
 * \return 最低温度值
 */
uint16 Statistic_GetBcuLtMax(void);

/**
 * \brief 获取最大温差
 *
 * \return 最大温差值
 */
uint16 Statistic_GetBcuDtMax(void);

/**
 * \brief 获取有效加热温感个数
 *
 * \return 有效加热温感个数，若配置为无加热温感，则返回0
 */
uint16 Statistic_GetBcuValidHeatTemperatureNum(void);

/**
 * \brief 获取异常加热温感个数
 *
 * \return 无效加热温感个数，若配置为无加热温感，则返回0
 */
uint16 Statistic_GetBcuInvalidHeatTemperatureNum(void);

/**
 * \brief 获取有效极柱温感个数
 *
 * \return 有效极柱温感个数，若配置为无极柱温感，则返回0
 */
uint16 Statistic_GetBcuValidPoleTemperatureNum(void);

/**
 * \brief 获取异常极柱温感个数
 *
 * \return 有效极柱温感个数，若配置为无极柱温感，则返回0
 */
uint16 Statistic_GetBcuInvalidPoleTemperatureNum(void);

/**
 * \brief 获取最高加热温度
 * \note  此函数用于故障诊断
 *
 * \return 最高加热温度值
 */
uint16 Statistic_GetBcuHeatHtMax(void);

/**
 * \brief 获取最低加热温度
 * \note  此函数用于故障诊断
 *
 * \return 最低加热温度值
 */
uint16 Statistic_GetBcuHeatLtMax(void);

/**
 * \brief 获取最大加热温差
 * \note  此函数用于故障诊断
 *
 * \return 最大加热温差值
 */
uint16 Statistic_GetBcuHeatDtMax(void);

/**
 * \brief 获取最高极柱温度
 * \note  此函数用于故障诊断
 *
 * \return 最高极柱温度值
 */
uint16 Statistic_GetBcuPoleHtMax(void);

/**
 * \brief 获取最低极柱温度
 * \note  此函数用于故障诊断
 *
 * \return 最低极柱温度值
 */
uint16 Statistic_GetBcuPoleLtMax(void);

/**
 * \brief 获取最大极柱温差
 * \note  此函数用于故障诊断
 *
 * \return 最大极柱温差值
 */
uint16 Statistic_GetBcuPoleDtMax(void);


//Slave

/**
 * \brief 获取从机有效电压个数
 *
 * \param SlaveId 从机ID，从0开始
 * \return 有效电压个数
 */
uint16 Statistic_GetSlaveValidVoltageNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机异常电压个数
 *
 * \param SlaveId 从机ID，从0开始
 * \return 异常电压个数
 */
uint16 Statistic_GetSlaveInvalidVoltageNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机有效温感个数
 *
 * \param SlaveId 从机ID，从0开始
 * \return 有效温感个数
 */
uint16 Statistic_GetSlaveValidTemperatureNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机异常温感个数
 *
 * \param SlaveId 从机ID，从0开始
 * \return 异常温感个数
 */
uint16 Statistic_GetSlaveInvalidTemperatureNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机统计累加总压值
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机内累加总压值，分辨率：1mv/bit
 */
App_Tv1mvType Statistic_GetSlaveTotalVoltage(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机平均电压值
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机内平均电压值
 */
App_VoltageType Statistic_GetSlaveAverageVoltage(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机最大压差值
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机内最大压差值
 */
App_VoltageType Statistic_GetSlaveDeltaVoltage(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机平均温度值
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机内平均温度值
 */
App_TemperatureType Statistic_GetSlaveAverageTemperature(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机最大温差值
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机内最大温差值
 */
App_TemperatureType Statistic_GetSlaveDeltaTemperature(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机单体高压个数
 * \note  返回值不超过STATISTIC_VOLTAGE_NUM
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机单体高压个数
 */
uint8 Statistic_GetSlaveHvNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机单体低压个数
 * \note  返回值不超过STATISTIC_VOLTAGE_NUM
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机单体低压个数
 */
uint8 Statistic_GetSlaveLvNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机单体高温个数
 * \note  返回值不超过STATISTIC_TEMPERATURE_NUM
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机单体高温个数
 */
uint8 Statistic_GetSlaveHtNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机单体低温个数
 * \note  返回值不超过STATISTIC_TEMPERATURE_NUM
 *
 * \param SlaveId 从机ID，从0开始
 * \return 从机单体低温个数
 */
uint8 Statistic_GetSlaveLtNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取指定从机指定编号的最高单体电压
 *
 * \param SlaveId 从机ID，从0开始
 * \param index 最高单体电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 最高单体电压值
 */
App_VoltageType Statistic_GetSlaveHv(App_SlaveIdType SlaveId, uint8 index);

/**
 * \brief 获取从机最高单体电压从机内索引号
 *
 * \param SlaveId 从机ID，从0开始
 * \param index 最高单体电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 最高单体电压串号
 */
uint8 Statistic_GetSlaveHvIndex(App_SlaveIdType SlaveId, uint8 index);

/**
 * \brief 获取指定从机指定编号的最低单体电压
 *
 * \param SlaveId 从机ID，从0开始
 * \param index 最低单体电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 最低单体电压值
 */
App_VoltageType Statistic_GetSlaveLv(App_SlaveIdType SlaveId, uint8 index);

/**
 * \brief 获取从机最低单体电压从机内索引号
 *
 * \param SlaveId 从机ID，从0开始
 * \param index 最低单体电压编号，范围：[0, STATISTIC_VOLTAGE_NUM)
 * \return 最低单体电压串号
 */
uint8 Statistic_GetSlaveLvIndex(App_SlaveIdType SlaveId, uint8 index);

/**
 * \brief 获取指定从机指定编号的最高温度
 *
 * \param SlaveId 从机ID，从0开始
 * \param index 最高温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 最高温度值
 */
App_TemperatureType Statistic_GetSlaveHt(App_SlaveIdType SlaveId, uint8 index);

/**
 * \brief 获取从机最高温度从机内索引号 编号从0开始
 */
uint8 Statistic_GetSlaveHtIndex(App_SlaveIdType SlaveId, uint8 index);

/**
 * \brief 获取指定从机指定位置的最低温度
 *
 * \param SlaveId 从机ID，从0开始
 * \param index 最低温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 最低温度值
 */
App_TemperatureType Statistic_GetSlaveLt(App_SlaveIdType SlaveId, uint8 index);

/**
 * \brief 获取从机最低温度从机内索引号
 *
 * \param SlaveId 从机ID，从0开始
 * \param index 最低温度编号，范围：[0, STATISTIC_TEMPERATURE_NUM)
 * \return 最低温度串号
 */
uint8 Statistic_GetSlaveLtIndex(App_SlaveIdType SlaveId, uint8 index);

/**
 * \brief 实际采集电池串数是否与配置串数不匹配
 * \details 若有从机未通信，则返回0
 *
 * \return 0-匹配 1-不匹配
 */
uint16 Statistic_ActureBatNumIsNotMatch(void);

/**
 * \brief 实际采集电池温感个数是否与配置个数不匹配
 * \details 若有从机未通信，则返回0
 *
 * \return 0-匹配 1-不匹配
 */
uint16 Statistic_ActureTemperatureNumIsNotMatch(void);

/**
 * \brief 开启最高最低温度模拟
 */
void Statistic_SimulationHtLtEnable(void);

/**
 * \brief 关闭最高最低温度模拟
 */
void Statistic_SimulationHtLtDisable(void);

/**
 * \brief 设置模拟最高温度值
 * \details 仅设置模拟最高温度值，但不会开启模拟功能
 *
 * \param ht 模拟最高温度值
 */
void Statistic_SetSimulationHt(App_TemperatureType ht);

/**
 * \brief 获取模拟最高温度值
 */
App_TemperatureType Statistic_GetSimulationHt(void);

/**
 * \brief 设置模拟最低温度值
 * \details 仅设置模拟最低温度值，但不会开启模拟功能
 *
 * \param ht 模拟最低温度值
 */
void Statistic_SetSimulationLt(App_TemperatureType lt);

/**
 * \brief 获取模拟最低温度值
 */
App_TemperatureType Statistic_GetSimulationLt(void);

/**
 * \brief 获取累计充电时间 单位:S
 * \details 时间溢出后自动清零
 *
 * \return 累计充电时间
 */
uint32 Statistic_GetCumuChgTime(void);

/**
 * \brief 设置累计充电时间
 * \details 时间溢出后自动清零
 *
 * \param time 充电时间
 */
void Statistic_SetCumuChgTime(uint32 time);

/**
 * \brief 保存累计充电时间
 * \details 将当前累计充电时间存储在NVM中,时间溢出后自动清零
 *
 * \param time 充电时间
 * \return E_OK: 成功 E_NOT_OK: 失败
 */
Std_ReturnType Statistic_SaveCumuChgTime(uint32 time);

/**
 * \brief 获取累计放电时间 单位:S
 * \details 时间溢出后自动清零
 *
 * \return 累计放电时间
 */
uint32 Statistic_GetCumuDchgTime(void);

/**
 * \brief 设置累计放电时间
 * \details 时间溢出后自动清零
 *
 * \param time 放电时间
 */
void Statistic_SetCumuDchgTime(uint32 time);

/**
 * \brief 保存累计放电时间
 * \details 将当前累计放电时间存储在NVM中,时间溢出后自动清零
 *
 * \param time 放电时间
 * \return E_OK: 成功 E_NOT_OK: 失败
 */
Std_ReturnType Statistic_SaveCumuDchgTime(uint32 time);

/**
 * \brief 获取累计运行时间 单位:S
 * \details 时间溢出后自动清零
 *
 * \return 累计放电时间
 */
uint32 Statistic_GetCumuTime(void);

/**
 * \brief 延时下电保存当前统计信息回调函数
 *
 * \param signal 触发信号
 */
boolean Statistic_PowerDownSaveCbk(RuntimeM_SignalType signal);



#endif

/**
 * \}
 */
