/**
 * \addtogroup CURRENT
 * \{
 */

#ifndef CURRENTM_H
#define CURRENTM_H

#include "Std_Types.h"
#include "Current_Types.h"
#include "Hall.h"
#include "Shunt.h"
#include "UserCurrentSensor.h"

#define CURRENTM_DEV_ERROR_DETECT           STD_OFF
#define CURRENTM_HALL_REVERSE_EN            STD_OFF //需要同时修改HALL配置通道反向

#if CURRENTM_HALL_REVERSE_EN == STD_ON
#define CURRENTM_DUAL_LOW_RANGE_CHANNEL     CURRENTM_SAMPLE_CHANNEL_HALL1
#define CURRENTM_DUAL_HIGH_RANGE_CHANNEL    CURRENTM_SAMPLE_CHANNEL_HALL2
#else
#define CURRENTM_DUAL_LOW_RANGE_CHANNEL     CURRENTM_SAMPLE_CHANNEL_HALL2
#define CURRENTM_DUAL_HIGH_RANGE_CHANNEL    CURRENTM_SAMPLE_CHANNEL_HALL1
#endif

/**
 * 采集通道定义.
 * \note 主要是在配置文件中使用.
 */
typedef enum {
    CURRENTM_SAMPLE_CHANNEL_HALL = 0, /**< 霍尔电流传感器, 当HALL是双量程的时候使用. */
    CURRENTM_SAMPLE_CHANNEL_HALL1 = CURRENTM_SAMPLE_CHANNEL_HALL, /**< 第一路HALL传感器采集通道 */
    CURRENTM_SAMPLE_CHANNEL_HALL2 = 1, /**< 第二路HALL传感器采集通道 */
    CURRENTM_SAMPLE_CHANNEL_SHUNT = 2, /**< 分流器采集通道 */
    CURRENTM_SAMPLE_CHANNEL_USERDEF1 = 3,
    CURRENTM_SAMPLE_CHANNEL_USERDEF2 = 4,
    CURRENTM_SAMPLE_CHANNEL_MAX = 5,
    CURRENTM_SAMPLE_CHANNEL_INVALID = 0xFF /**< 无效通道 */
} CurrentM_SampleChannelType;

/**
 * \brief 电流采集回路.
 */
typedef enum {
    CURRENTM_CHANNEL_MAIN, /**< 主回路电流 */
    CURRENTM_CHANNEL_HEATER, /**< 加热回路电流 */
    CURRENTM_CHANNEL_MAX
} CurrentM_ChannelType;

/**
 * \brief 采集回路配置数据定义.
 */
typedef struct {
    boolean enable; /**< 是否开启该回路采集 */
    CurrentM_SampleChannelType channel; /**< 该采集回路使用的通道 */
    boolean redundancyEnable; /**< 该采集回路是否开启冗余采集. */
    CurrentM_SampleChannelType redundancySample; /**< 冗余采集使用的通道 */
} CurrentM_SampleLoopConfigType;

/**
 * \brief 电流管理配置数据.
 */
typedef struct {
    boolean hallIsDualRange; /**< 2路HALL传感器是否为双量程传感器. */
    Current_CurrentType LowHallCurrentMax; /**< 小量程HALL最大电流值，超过此值启用大量程 */
    CurrentM_SampleLoopConfigType main; /**< 主回路的采集配置 */
    CurrentM_SampleLoopConfigType heater; /**< 加热回路采集配置 */
    Current_CurrentType autoCalibLimit[CURRENTM_SAMPLE_CHANNEL_MAX]; /**< 自动校准电流限制值 */
    Current_CurrentType zeroFilter[CURRENTM_SAMPLE_CHANNEL_MAX]; /**< 电流零点滤波电流 */
} CurrentM_ConfigType;

/**
 * \brief 电流数据
 */
typedef struct {
    uint32 timestamp;
    Current_CurrentType currentCalibrated;
    Current_CurrentType current;
} CurrentM_TimedCurrentType;

/**
 * \brief 电流管理配置参数声明
 */
extern const CurrentM_ConfigType CurrentM_ConfigInfo;

/**
 * \brief 初始化电流管理.
 *
 * \param cfg 初始化参数
 */
void CurrentM_Init(const CurrentM_ConfigType *cfg, uint8 pri, OS_STK *stack, uint16 stackLen);
void CurrentM_HeatInit(const CurrentM_ConfigType *cfg, uint8 pri, OS_STK *stack, uint16 stackLen);

/**
 * \brief 读取某一路的电流值.
 *
 * \param channel 读取哪一路采集回路的电流.
 * \return 该采集回路的电流.
 */
Current_CurrentType CurrentM_GetCurrent(CurrentM_ChannelType channel);

/**
 * \brief 读取某一路的校正电流值.
 *
 * \param channel 读取哪一路采集回路的校正电流.
 * \return 该采集回路的校正电流.
 */
Current_CurrentType CurrentM_GetCurrentCalibrated(CurrentM_ChannelType channel);

/**
 * \brief 自动校准某一路电流采集回路.
 * \note 自动校准的前提是由应用层确保该回路没有采集电流.
 *
 * \param channel 需要校准的电流采集回路.
 */
Std_ReturnType CurrentM_AutoCalibrated(CurrentM_SampleChannelType channel);

/**
 * \brief 获取主回路充电电流值
 */
uint16 CurrentM_GetMainDiagChgCurrent(void);

/**
 * \brief 获取主回路放电电流值
 */
uint16 CurrentM_GetMainDiagDchgCurrent(void);

/**
 * \brief 电流有效性检查
 *
 * \param current 检测电流值
 * \return TRUE-有效 FALSE-无效
 */
boolean CurrentM_IsValidCurrent(Current_CurrentType current);

/**
 * \brief 电流有效性检查
 * \note 用于故障诊断
 *
 * \param current 检测电流值
 * \return TRUE-有效 FALSE-无效
 */
boolean CurrentM_DiagIsValidCurrent(uint16 current);

/**
 * \brief 电流是否异常
 * \details 包含电流无效、短路、开路、通信异常等
 * \return 1-无效 0-有效
 */
uint16 CurrentM_CurrentIsAbnormal(void);

#endif

/** \} */
