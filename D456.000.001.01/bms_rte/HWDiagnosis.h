/**
 * \file HWDiagnosis.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 硬件自检头文件.
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


#ifndef HWDIAGNOSIS_H_
#define HWDIAGNOSIS_H_

#include "Std_Types.h"
#include "App_Types.h"
#include "Diagnosis.h"
#include "HWDiagnosis_Cfg.h"

/**
 * \brief 硬件诊断无效板载电压值
 */
#define HWDIAGNOSIS_INVALID_BOARD_VOLTAGE_VALUE         0xFFFF

/**
 * \brief 硬件诊断无效板载温度值
 */
#define HWDIAGNOSIS_INVALID_BOART_TEMPERATURE_VALUE     0xFF


/**
 * \brief 板载电压类型定义
 */
typedef uint16 HWDiagnosis_BoardVoltType;

/**
 * \板载温度类型定义
 */
typedef uint16 HWDiagnosis_BoardTempType;

/**
 * \brief 硬件诊断项类型定义
 */
typedef enum{
    HWDIAGNOSIS_ITEM_VOLT_HIGH, /**< 板载电压高 */
    HWDIAGNOSIS_ITEM_VOLT_LOW, /**< 板载电压低 */
    HWDIAGNOSIS_ITEM_TEMP_HIGH, /**< 板载温度高 */
    HWDIAGNOSIS_ITEM_TEMP_LOW, /**< 板载温度低 */
    HWDIAGNOSIS_ITEM_NUM, /**< 支持的板载诊断个数 */
}HWDiagnosis_DiagnosisItemType;



/**
 * \brief 单个板载电压报警项配置类型定义
 */
typedef struct{
    Diagnosis_LevelParaType HV_1stLevelCfg; /**< 高压一级报警配置 */
    Diagnosis_LevelParaType HV_SndLevelCfg; /**< 高压二级报警配置 */
    Diagnosis_LevelParaType LV_1stLevelCfg; /**< 低压一级报警配置 */
    Diagnosis_LevelParaType LV_SndLevelCfg; /**< 低压二级报警配置 */
}HWDiagnosis_VoltAlarmItemCfgType;

/**
 * \brief 单个板载温度报警项配置类型定义
 */
typedef struct{
    Diagnosis_LevelParaType HT_1stLevelCfg; /**< 高温一级报警配置 */
    Diagnosis_LevelParaType HT_SndLevelCfg; /**< 高温二级报警配置 */
    Diagnosis_LevelParaType LT_1stLevelCfg; /**< 低温一级报警配置 */
    Diagnosis_LevelParaType LT_SndLevelCfg; /**< 低温二级报警配置 */
}HWDiagnosis_TempAlarmItemCfgType;


/**
 * \brief 板载电压报警配置类型定义
 */
typedef struct{
    HWDiagnosis_VoltAlarmItemCfgType Bcu24VConfig; /**< 主机供电24V报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType BcuNandConfig; /**< 主机NAND供电电压报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType BcuMcuConfig; /**< 主机MCU供电电压报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType BcuPeripheralConfig; /**< 主机外设供电电压报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType BcuRtcConfig; /**< 主机RTC供电电压报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType BcuHall8VConfig; /**< 主机HALL_8V供电电压报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType BcuHall5VConfig; /**< 主机HALL_5V供电电压报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType BcuAds10xxVoltConfig; /**< 主机高压ADC2供电电压报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType Bmu24VConfig; /**< 从机24V供电电压报警配置 */
    HWDiagnosis_VoltAlarmItemCfgType BmuMcuConfig; /**< 从机MCU供电电压报警配置 */
}HWDiagnosis_VoltAlarmConfigType;

/**
 * \brief 板载温度报警配置类型定义
 */
typedef struct{
    HWDiagnosis_TempAlarmItemCfgType BcuNtcConfig; /**< 主机板载温度报警配置 */
    HWDiagnosis_TempAlarmItemCfgType BcuRtcConfig; /**< 主机RTC片内温度报警配置 */
    HWDiagnosis_TempAlarmItemCfgType BcuAds10xxTemp1Config; /**< 主机ADC1片内温度报警配置 */
    HWDiagnosis_TempAlarmItemCfgType BcuAds10xxTemp2Config; /**< 主机ADC2片内温度报警配置 */
    HWDiagnosis_TempAlarmItemCfgType BcuMcuConfig; /**< 主机MCU片内温度报警配置 */
    HWDiagnosis_TempAlarmItemCfgType BcuShuntConfig; /**< 主机分流器片内温度报警配置 */
    HWDiagnosis_TempAlarmItemCfgType BmuNtcConfig; /**< 从机板载温度报警配置 */
}HWDiagnosis_TempAlarmConfigType;

/**
 * \brief 主机板载电压AD转换参数
 */
typedef struct {
    sint16 offset;
    sint16 mul;
    sint16 div;
} HWDiagnosis_VolAdcToValueParamType;

void HWDiagnosis_Init(void);

/**
 * \brief 获取板载电压值
 * \note 根据板载电压类型获取电压值
 *
 * \param VoltType 板载电压类型
 *
 * \return 板载电压值
 */
App_VoltageType HWDiagnosis_GetBoardVoltage(HWDiagnosis_BoardVoltType VoltType);

/**
 * \brief 获取板系统供电电压
 *
 * \return 系统供电电压
 */
App_VoltageType HWDiagnosis_GetSupplyVoltage(void);

/**
 * \brief 获取全部板载电压信息
 * \note 板载电压的顺序与HWDiagnosis_BoardVoltType顺序相同
 *
 * \param VoltageBuffPtr 全部板载电压值
 * \param VoltageBuffCnt 能存放电压值的个数, 实际Buffer的大小为sizeof(App_VoltageType) * VoltageBuffSize
 *
 * \return 获取到的电压的个数.
 */
uint8 HWDiagnosis_GetBoardVoltageAll(App_VoltageType *VoltageBuffPtr, uint8 VoltageBuffCnt);

/**
 * \brief 获取板载温度值
 * \note 根据板载温度类型获取温度值
 *
 * \param TempType 板载温度类型
 *
 * \return 板载温度值
 */
App_TemperatureType HWDiagnosis_GetBoardTemperature(HWDiagnosis_BoardTempType TempType);

/**
 * \brief 获取全部板载温度信息
 * \note 板载温度的顺序与HWDiagnosis_BoardTempType顺序相同
 *
 * \param TemperatureBuffPtr 全部板载温度值
 * \param TemperatureBuffCnt 能存放温度值的个数, 实际Buffer的大小为sizeof(App_TemperatureType) * VoltageBuffSize
 *
 * \return 获取到的温度的个数.
 */
uint8 HWDiagnosis_GetBoardTemperatureAll(App_TemperatureType *TemperatureBuffPtr, uint8 TemperatureBuffCnt);


/**
 * \brief 获取诊断状态（此函数未实现）
 * \note 根据ECU ID确定是获取主机还是从机的诊断，然后根据诊断项获取诊断状态
 *
 * \param EcuId 设备编号 0:BCU 1~16:BMU1~16
 * \param Diag_Item 诊断项
 *
 * \return 诊断状态
 */
Diagnosis_LevelType HWDiagnosis_GetDiagnosisStatus(App_SlaveIdType SlaveId, HWDiagnosis_DiagnosisItemType Diag_Item);

/**
 * \brief 获取全部诊断状态信息（此函数未实现）
 * \note 板载状态的顺序与HWDiagnosis_DiagnosisItemType顺序相同
 *
 * \param DiagnosisBuffPtr 全部诊断状态
 */
void HWDiagnosis_GetDiagnosisStatusAll(Diagnosis_LevelType *DiagnosisBuffPtr);

/**
 * \brief BMS硬件是否存在硬件故障（此函数未实现）
 * \return TRUE: 有故障 FALSE: 无故障
 */
uint8 HWDiagnosis_IsHwFault(void);

/**
 * \brief 供电电压是否采集异常
 * \details 采集供电电压无效
 * \return 0-正常 1-异常
 */
uint16 HWDiagnosis_SupplyVoltageIsAbnomal(void);

#endif

/**
 * \}
 */
