#ifndef __PWMCAPURE_H__
#define __PWMCAPURE_H__

#include "Std_Types.h"
#include "XGate.hx"

#pragma push
#pragma align on
typedef struct {
    uint16 *near ect2_tc;
    uint8 port_t_bit;
    uint8 revertflag;
    uint8 edgesToTriggerHcs12;
    uint8 overflowIgnore;
    uint32 highLevelCounter;
    uint32 lowLevelCounter;
    uint32 counter;
    uint16 last_capture;
    uint8 bitlevel;
} PwmCapture_DataType;

#define PWM_TRIGGER_HCS12_RAISING 0x01U
#define PWM_TRIGGER_HCS12_FALLING 0x02U
#define PWM_TRIGGER_HCS12_ALL     0x03U
#define PWM_TRIGGER_HCS12_NONE    0x00U

#define PWM_RAISING_EDGE_TRIGGERED  0x04U

#pragma pop

extern uint32 PwmCapture_Clock;

/**
 * \brief PWM捕获模块的初始化
 */
void PwmCapture_Init(void);

/**
 * \brief 获取PWM波形占空比
 *
 * \param pwm_data 对应通道的PWM数据
 * \return PWM波形占空比（单位：0.1%）
 */
uint16 PwmCapture_GetDuty(const PwmCapture_DataType *pwm_data);

/**
 * \brief 获取PWM波形周期
 * \detail 与底层PWM捕获模块的时钟相关，不建议使用，建议使用\ref PwmCapture_GetCycleTime。
 *
 * \param pwm_data 对应通道的PWM数据
 * \return 获取PWM波形周期（底层PWM捕获模块的时钟的周期）
 */
uint32 PwmCapture_GetCycle(const PwmCapture_DataType *pwm_data);

/**
 * \brief 获取PWM波形频率
 *
 * \param pwm_data 对应通道的PWM数据
 * \return PWM波形频率（单位：Hz）；
 */
uint32 PwmCapture_GetFrequence(const PwmCapture_DataType *pwm_data);

/**
 * \brief 判断最近一次的沿跳变是否为上升沿跳变
 *
 * \param pwm_data pwm_data 对应通道的PWM数据
 * \retval TRUE 最近一次的沿跳变为上升沿跳变
 * \retval FALSE 最近一次的沿跳变为下降沿跳变
 */
boolean PwmCapture_IsTriggerRising(const PwmCapture_DataType *pwm_data);

/**
 * \brief 获取PWM波形的低电平时间
 *
 * \param pwm_data 对应通道的PWM数据
 * \return 低电平的时间（单位：100uS），比如返回10表示1mS；
 */
uint32 PwmCapture_GetLowTime(const PwmCapture_DataType *pwm_data);

/**
 * \brief 获取PWM波形的高电平时间
 *
 * \param pwm_data 对应通道的PWM数据
 * \return 高电平的时间（单位：100uS），比如返回10表示1mS；
 */
uint32 PwmCapture_GetHighTime(const PwmCapture_DataType *pwm_data);

/**
 * \brief 获取PWM波形周期
 *
 * \param pwm_data 对应通道的PWM数据
 * \return PWM波形周期（单位：100uS），比如返回10表示1mS；
 */
uint32 PwmCapture_GetCycleTime(const PwmCapture_DataType *pwm_data);


uint16 CP_GetFrequence(void);
uint16 CP_GetDuty(void);
uint32 CP_GetLowTime(void);
uint32 CP_GetHighTime(void);


#endif
