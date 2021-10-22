/**
 * \file SocOcvCalib.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Soc静态校正头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170223 |
 */

/**
 * \addtogroup SocOcvCalib SOC静态校正
 * \{
 */
#ifndef SOC_OCV_CALIB_H_
#define SOC_OCV_CALIB_H_

#include "Std_Types.h"
#include "App_Types.h"

/**
 * \brief 温度上下限默认允许范围
 */
#define SOCOCVCALIB_RESERVE_TEMPERATURE     10U


/**
 * \brief 允许OCV校正条件函数接口类型
 */
typedef boolean (*isAllowCalibFuncPtr)(void);

/**
 * \brief 配置参数类型定义
 */
typedef struct{
    uint8 socBuffSize; /**< SOC缓存大小 */
    uint8 temperatureBuffSize; /**< 温度缓存大小 */
    uint16 allowedCurrent; /**< 允许校准最大电流 */
    uint16 powerOnDelay; /**< 上电检查延时时间 1mS/bit */
    uint16 calibCycle; /**< OCV-SOC校准周期 1min/bit */
    uint16 longCycle; /**< OCV-SOC长时间周期 1min/bit */
    uint16 checkCycle; /**< OCV-SOC查询周期 1s/bit */
    App_SocType diffSocMin; /**< 允许校准最小SOC差 */
    App_SocType calibStep; /**< SOC校准步长 */
    boolean linear_calib; /**< 线性校准使能 */
    isAllowCalibFuncPtr isAllowFuncPtr; /**< 是否允许校正函数指针 */
    boolean temperature_linear; /**< 温度是否线性查表 */
    App_VoltageType diffVoltMin; /**< 允许校正最小压差 */
    boolean chargeReset; /**< 是否充电模式重置 */
}SocOcvCalib_ConfigType;

/**
 * \brief 内部参数类型定义
 */
typedef struct{
    uint8 powerOnFlag; /**< 上电标志 */
    uint8 currentLargeFlag; /**< 大电流标志 */
    uint8 dateTime; /**< 时间 */
    boolean isAutoCalib; /**< 是否自动校正 */
    App_VoltageType voltage; /**< 校正电压 */
    App_TemperatureType temperature; /**< 校正温度 */
    App_VoltageType voltBuffer[30U]; /**< 温度线性插值后电压缓存 */
}SocOcvCalib_InnerDataType;

extern const SocOcvCalib_ConfigType SocOcvCalib_ConfigInfo;
extern const sint16 SocOcvCalib_TemperatureBuffer[];
extern const App_SocType SocOcvCalib_SocBuffer[];
extern const App_VoltageType SocOcvCalib_VoltageBuffer[];

/**
 * \brief 模块初始化
 */
void SocOcvCalib_Init(void);

/**
 * \brief 启动自动OCV校正
 */
void SocOcvCalib_AutoCalibStart(void);

/**
 * \brief OCV-SOC校准检查函数
 * \details 周期调用此函数来进行OCV-SOC校准检查及校准
 *
 * \return E_OK: 校准成功 E_NOT_OK: 未校准
 */
Std_ReturnType SocOcvCalib_Check(void);

/**
 * \brief OCV是否允许校正检查函数
 * \details 根据当前电压和温度状态，确定在当前状态下的相临电压之间差异是否满足校正的条件
 * \return TRUE-允许 FALSE-不允许
 */
boolean SocOcvCalib_IsAllowCalib(void);

#endif

/**
 * \}
 */