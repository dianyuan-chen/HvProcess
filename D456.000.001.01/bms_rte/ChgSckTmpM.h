/**
 * \file ChgSckTmpM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电插座温度管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161207 |
 */

/**
 * \addtogroup ChgSckTmpM 充电插座温度管理
 * \{
 */

#ifndef CHGSCKTMPM_H_
#define CHGSCKTMPM_H_

#include "Std_Types.h"
#include "Adc.h"
#include "Diagnosis.h"
#include "ChgSckTmpM_Cfg.h"

/**
 * \brief 充电插座温度个数
 */
#define CHGSCKTMPM_TEMPERATURE_MAX_NUM          5U

#define CHGSCKTMPM_TEMPERATURE_DC_POSITIVE      0U
#define CHGSCKTMPM_TEMPERATURE_DC_NEGATIVE      1U
#define CHGSCKTMPM_TEMPERATURE_AC_AL            2U
#define CHGSCKTMPM_TEMPERATURE_AC_BN            3U
#define CHGSCKTMPM_TEMPERATURE_AC_C             4U

#define CHGSCKTMPM_TEMPERATURE_CHANEL_NUM       5U

#define CHGSCKTMPM_ADC_FCH_T1 0U
#define CHGSCKTMPM_ADC_FCH_T2 1U
#define CHGSCKTMPM_ADC_SCH_T1 2U
#define CHGSCKTMPM_ADC_SCH_T2 3U
#define CHGSCKTMPM_ADC_SCH_T3 4U

#define CHGSCKTMPM_ADC_CHANNEL_NUM 5U


/**
 * \brief 充电插座温度值类型定义
 */
typedef uint8 ChgSckTmpM_TemperatureType;


/**
 * \brief 充电插座温度ADC采集通道类型定义
 */
typedef uint8 ChgSckTmpM_AdcChannelType;

/**
 * \brief 充电插座温度通道类型定义
 */
typedef uint8 ChgSckTmpM_TmpChannelType;

/**
 * \brief 充电插座温感配置类型定义
 */
typedef struct{
    uint8 enable; /**< 使能控制 */
}ChgSckTmpM_TmpConfigType;

/**
 * \brief 充电插座温度管理配置类型定义
 */
typedef struct{
    ChgSckTmpM_TmpConfigType temperature_config[CHGSCKTMPM_TEMPERATURE_MAX_NUM]; /**< 温感配置 */
}ChgSckTmpM_ConfigType;

/**
 * \brief 充电插座温度管理温度诊断类型定义
 */
typedef struct{
    Std_CircuitFaultType circuit_fault; /**< 电路故障状态 */
    Diagnosis_LevelType high_temp_alarm; /**< 高温报警状态 */
}ChgSckTmpM_TmpDiagnosisType;

/**
 * \brief 充电插座温度内部状态类型定义
 */
typedef struct{
    uint8 flag; /**< 更新标志 */
    uint16 adc; /**< adc电压值 */
    ChgSckTmpM_TemperatureType temperature; /**< 温度值 */
}ChgSckTmpM_InternalStatusType;

/**
 * \brief 充电插座管理模块配置参数
 */
extern ChgSckTmpM_InternalStatusType ChgSckTmpM_InternalStatusInfo[CHGSCKTMPM_TEMPERATURE_MAX_NUM];
extern const ChgSckTmpM_ConfigType ChgSckTmpM_ConfigInfo;
extern const Diagnosis_DiagInfoType ChgSckTmpM_HTDiagInfoConfig[CHGSCKTMPM_TEMPERATURE_MAX_NUM];
extern const Diagnosis_ParaType ChgSckTmpM_HTDiagConfig[CHGSCKTMPM_TEMPERATURE_MAX_NUM];
extern const uint8 ChgSckTmpM_AdcToTempChannelMap[];

/**
 * \brief 充电插座温度初始化
 * \note 使用配置初始化各路插座温度检测功能
 */
void ChgSckTmpM_Init(void);


/**
 * \brief 充电插座温度反初始化
 */
void ChgSckTmpM_Deinit(void);

/**
 * \brief 获取充电插座温度采样电压值
 *
 * \param ChannelId 充电插座温度采集通道
 * \return 采样电压值
 */
uint16 ChgSckTmpM_GetSampleVoltage(ChgSckTmpM_TmpChannelType ChannelId);

/**
 * \brief 获取充电插座温度
 * \note 通过输入通道类型获取对应通道的温度值
 *
 * \param ChannelId 充电插座温度通道
 * \return 充电插座温度值
 */
ChgSckTmpM_TemperatureType ChgSckTmpM_GetTemperature(ChgSckTmpM_TmpChannelType ChannelId);

/**
 * \brief 所有充电插座温度已经完成获取
 * \details 用于查询上电后所有充电插座温度是否已经更新
 * \return TRUE-完成 FALSE-未完成
 */
uint8 ChgSckTmpM_AllTemperatureIsGet(void);

/**
 * \brief 获取充电插座温感异常个数
 *
 * \return 异常温感个数
 */
uint16 ChgSckTmpM_GetAbnormalTemperatureNum(void);

/**
 * \brief 获取各充电插座温度值
 *
 * \return 对应充电插座温度值
 */
uint16 ChgSckTmpM_GetDCPositiveTemperature(void);
uint16 ChgSckTmpM_GetDCNegativeTemperature(void);
uint16 ChgSckTmpM_GetACALTemperature(void);
uint16 ChgSckTmpM_GetACBNTemperature(void);
uint16 ChgSckTmpM_GetACCTemperature(void);


#endif

/**
 * \}
 */
