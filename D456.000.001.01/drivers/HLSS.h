/**
 * \addtogroup Drivers
 * \{
 * \addtogroup HLSSDriver 高底边驱动
 * \{
 */
#ifndef HLSS_H
#define HLSS_H

#include "Std_Types.h"
#include "Dio.h"
#include "Adc.h"
#include "HLSS_Types.h"
#include "HLSS_Cfg.h"
#include "Async_Looper.h"

/**
 * \brief HLSS反馈电压无效值定义
 */
#define HLSS_INVALID_VOLTAGE_VALUE      0x0FFFFU

/**
 * \biref HLSS反馈电流无效值定义
 */
#define HLSS_INVALID_CURRENT_VALUE      0U

/**
 * \从机HLSS状态控制DID
 */
#define HLSS_SLAVE_CONTROL_DID          0x900U

/**
 * \brief 高低边开关的驱动电平的定义.
 */
typedef uint8 HLSS_DriveType;
#define HLSS_DRIVE_OFF     0U/**< 驱动开关断开 */
#define HLSS_DRIVE_ON      1U/**< 驱动开关导通 */

/**
 * \brief 高低边开关的强制驱动电平的定义
 */
typedef uint8 HLSS_ForceDriveType;
#define HLSS_FORCE_NONE    0U /**< 未强控制 */
#define HLSS_FORCE_OFF     1U /**< 强制断开 */
#define HLSS_FORCE_ON      2U /**< 强制闭合 */
#define HLSS_FORCE_MAX     3U

/**
 * \brief 高低边开关的诊断状态.
 */

typedef uint8 HLSS_DiagnosisStatusType;
#define HLSS_DIAGNOSIS_OK   0U /**< 开关状态正常 */
#define HLSS_DIAGNOSIS_ERR  1U /**< 开关状态异常 */

/**
 * \brief 高低边开关的诊断依据数据.
 */
typedef struct {
    HLSS_VoltageType VolMax; /**< 电压上限 */
    HLSS_VoltageType VolMin; /**< 电压下限 */
    HLSS_CurrentType CurrentMax; /**< 电流上限 */
    HLSS_CurrentType CurrentMin; /**< 电流下限 */
} HLSS_DiagnosisValueType;

/**
 * \brief ADC值到物理值得公式参数.
 * \details PhyValue = (AdcValue - Offset) * MulFactor / DivFactor;
 */
typedef struct {
    Adc_ValueType Offset;
    Adc_ValueType MulFactor;
    Adc_ValueType DivFactor;
} HLSS_ValueAdcToPhyCalculateParamType;

/**
 * \brief 高低边开关初始化
 * \details 复位所有高低边开关状态为断开，反馈电压和反馈电流为无效值
 */
void HLSS_Init(Async_LooperType *looper);

/**
 * \brief 设置高低边开关的驱动状态.
 * \details 只是设置驱动状态, 返回结果没有诊断状态.
 *
 * \param ChannelId 开关通道.
 * \param Drive 驱动状态. *
 */
void HLSS_Drive(HLSS_ChannelType ChannelId, HLSS_DriveType Drive);

/**
 * \brief 强制设置高低边开关的驱动状态
 * \details 不返回诊断状态，强制驱动类型为无时，自动转换为正常控制状态
 *
 * \param ChannelId 开关通道
 * \param Force 强制驱动状态
 */
void HLSS_Force(HLSS_ChannelType ChannelId, HLSS_ForceDriveType Force);

/**
 * \brief 获取高低边开关的驱动状态.
 *
 * \param ChannelId 开关通道.
 *
 * \return 驱动状态
 */
HLSS_DriveType HLSS_GetDrive(HLSS_ChannelType ChannelId);

/**
 * \brief 获取高低边开关的强制驱动状态
 *
 * \param ChannelId 开关通道
 * \return 强制驱动状态
 */
HLSS_ForceDriveType HLSS_GetForce(HLSS_ChannelType ChannelId);

/**
 * \brief 获取高低边开关的实际状态.
 *
 * \param ChannelId 开关通道.
 *
 * \return 实际状态
 */
HLSS_DriveType HLSS_GetActual(HLSS_ChannelType ChannelId);

/**
 * \brief 获取高低边开关的诊断状态.
 *
 * \param ChannelId 开关通道.
 * \return 开关的诊断状态.
 */
HLSS_DiagnosisStatusType HLSS_GetDiagnosisStatus(HLSS_ChannelType ChannelId);

/**
 * \brief 获取高低边开关的诊断电压.
 *
 * \param ChannelId 开关通道.
 * \return 诊断电压.
 */
HLSS_VoltageType HLSS_GetDiagnosisVoltage(HLSS_ChannelType ChannelId);
/**
 * \brief 获取高低边开关的诊断电流.
 *
 * \param ChannelId 开关通道.
 * \return 诊断电流.
 */
HLSS_CurrentType HLSS_GetDiagnosisCurrent(HLSS_ChannelType ChannelId);

/**
 * \brief 使用DIO控制高低边开关的配置参数.
 */
typedef struct {
    Dio_ChannelType ControlDio; /**< 使用的DIO通道 */
    Dio_LevelType DioLevelWhenDriveOn; /**< 驱动开关导通时使用的DIO的电平 */
    HLSS_ValueAdcToPhyCalculateParamType VoltageCalculateParam; /**< 电压ADC值到电压值得计算参数 */
    HLSS_ValueAdcToPhyCalculateParamType CurrentCalculateParam; /**< 电流ADC值到电流值得计算参数 */
    uint16 MaxCurrentValue; /**< 计算到的最大电流 */
    Std_ReturnType (*GetDiagnosisValue)(HLSS_DriveType DriveType, HLSS_DiagnosisValueType *DiagnosisValuePtr); /**< 获取当前时刻的电流电压诊断上下限 */
} HLSS_DioConfigType;

/**
 * \brief 从机高低边开关的配置参数.
 */
typedef struct {
    uint8 BmuId; /**< 从机ID号 */
    uint8 HSSIdInBMU; /**< 从机内部的高低边开关号 */
} HLSS_BMUConfigType;

/**
 * \brief 高低边开关的几种类型.
 */
typedef enum {
    HLSS_DIO_HSS_TYPE, /**< 只用DIO控制的高边开关 */
    HLSS_DIO_LSS_TYPE, /**< 只用DIO控制的低边开关 */
    HLSS_BMU_HSS_TYPE, /**< 从机控制的高边开关 */
    HLSS_BMU_LSS_TYPE, /**< 从机控制的低边开关 */
} HLSS_TypeType;

/**
 * \brief 高低边开关的配置参数.
 */
typedef struct {
    HLSS_TypeType type; /**< 类型 */
    void *hwCfg; /**< 对应类型的配置, 不同的类型该指针可以转换成\link HLSS_DioConfigType \endlink指针或\link HLSS_BMUConfigType \endlink指针 */
} HLSS_ConfigType;

/**
 * \brief 所有高低边开关的配置.
 */
extern const HLSS_ConfigType HLSSBcuConfig[];

int shell_func_hlss(int argc, const char * const*argv);

#endif

/**
 * \}
 * \}
 */
