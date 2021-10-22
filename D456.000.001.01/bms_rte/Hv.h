/**
 * \addtogroup HV 高压检测
 * \{
 */
#ifndef HV_H_
#define HV_H_

#include "Std_Types.h"
#include "Hv_Cfg.h"
#include "Adc.h"
#include "App_Types.h"

/**
 * \brief 无效电压值.
 */
#define HV_VOTAGE_INVALID (0xFFFFu)
#define HV_INSTANCE_VOLTAGE_INVALID (0x7FFF)

typedef struct {
    sint16 offset;
    sint16 mul;
    sint16 div;
} HV_ConfigType;


/**
 * \brief 高压采集通道.
 */
typedef enum {
    HV_CHANNEL_BPOS = 0, /**< 采集通道B+ */
    HV_CHANNEL_HV1 = 1, /**< 高压采集通道1 */
    HV_CHANNEL_HV2 = 2, /**< 高压采集通道2 */
    HV_CHANNEL_HV3 = 3, /**< 高压采集通道3 */
    HV_CHANNEL_HV4 = 4, /**< 高压采集通道4 */
    HV_CHANNEL_HVE1 = HV_CHANNEL_HV4,
    HV_CHANNEL_HV5 = 5, /**< 高压采集通道5 */
    HV_CHANNEL_HVE2 = HV_CHANNEL_HV5,
    HV_CHANNEL_MAX = 6,
} HV_ChannelType;

#define HV_CHANNEL_NONE   (HV_ChannelType)0xFF

/**
 * \brief 启动采集.
 * \note 该函数只是设置启动标记以及相关滤波参数立即返回,
 * 其采集结果可以通过\link HV_GetVoltage \endlink来读取.
 *
 * \param channel 需要采集的通道.
 * \param filterNum 一次滤波的采集电压数.
 * \param dropNum 前后需要丢弃的最大最小值个数.
 * \return 启动成功(E_OK); 忙(E_NOT_OK).
 */
Std_ReturnType HV_StartSample(HV_ChannelType channel, uint8 filterNum, uint8 dropNum, uint16 gainErr);

/**
 * \brief 设置电路的线性无擦.
 *
 * \param channel 需要设置的通道.
 * \param gaiErr 线性误差, 900-1100
 * \return 设置成功(E_OK); 设置失败(E_NOT_OK).
 */
Std_ReturnType HV_SetGainErr(HV_ChannelType channel, uint16 gainErr);

/**
 * \brief 获取电路的线性无擦.
 *
 * \param channel 需要设置的通道.
 * \return 线性误差.
 */
uint16 HV_GetGainErr(HV_ChannelType channel);

/**
 * \brief 停止采集.
 * \note 与\link HV_StartSample \endlink成对使用.
 *
 * \param channel 需要停止采集的通道.
 * \return 停止成功(E_OK); 该通道之前没有启动(E_NOT_OK).
 */
Std_ReturnType HV_StopSample(HV_ChannelType channel);

/**
 * \brief 清除滤波缓冲.
 * \note 清除滤波缓冲后, 滤波采集值会重新采集filterNum个之后才能得到一个新的滤波过后的值.
 *
 * \param channel 需要清除滤波缓冲的通道.
 * \return 清除滤波缓冲(E_OK); 清除滤波失败(E_NOT_OK).
 */
Std_ReturnType HV_ClearFilterBuffer(HV_ChannelType channel);

/**
 * \brief 读取滤波过后的采集电压.
 *
 * \param channel 读取的通道.
 * \return 滤波过后的采集电压.
 */
App_Tv100mvType HV_GetVoltage(HV_ChannelType channel);


/**
 * \brief 读取当前的采集电压.
 *
 * \param channel 读取的通道.
 * \return 当前的采集电压.
 */
sint16 HV_GetInstantVoltage(HV_ChannelType channel);

/**
 * \brief 同步采集.
 * \note 对一个通道进行同步采集, 内部实现:
 * ```c
 * HV_StartSample(channel, filterNum, dropNum);
 * for (;;) {
 *   v = HV_GetVoltage();
 *   if (v != HV_VOTAGE_INVALID) {
 *     *vol = v;
 *     HV_StopSample(channel);
 *     return STD_OK;
 *   }
 * }
 * ```
 *
 * \param channel 需要采集的通道.
 * \param filterNum 一次滤波的采集电压数.
 * \param dropNum 前后需要丢弃的最大最小值个数.
 * \param vol [out] 用于保存采集结果.
 *
 * \return 启动成功(E_OK); 忙(E_NOT_OK).
 */
Std_ReturnType HV_SyncSample(HV_ChannelType channel, uint8 filterNum, uint8 dropNum, App_Tv100mvType *vol);



void HV_NewAdcValueIndication(HV_ChannelType channel, sint16 advValue);

#endif
/** \} */
