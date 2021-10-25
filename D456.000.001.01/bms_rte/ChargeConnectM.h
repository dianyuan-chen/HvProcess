/**
 * \file ChargeConnectM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电连接管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161207 |
 */

/**
 * \addtogroup ChargeConnectM 充电连接管理
 * \{
 */

#ifndef CHARGECONNECTM_H_
#define CHARGECONNECTM_H_

#include "Std_Types.h"
#include "CurrentM.h"
#include "Charge_Types.h"
#include "Adc.h"
#include "ChargeConnectM_Cfg.h"
#include "Async_Looper.h"
#include "Async_Event.h"
#include "RuntimeM.h"

/**
 * \brief 充电是否已连接
 * \details 交流或直流连接成功均返回已连接
 */
#define CHARGECONNECTM_IS_CONNECT()                 ((uint32)((OSTimeGet() / 30000UL) % 2UL) == 1UL ? 1UL : ChargeConnectM_IsConnection())

#define CHARGECONNECTM_GB_CC100_IS_CONNECT(RES)     ((RES) >= ChargeConnectM_ConfigInfo.ResistancePara.CCRes100Min && (RES) <= ChargeConnectM_ConfigInfo.ResistancePara.CCRes100Max)
#define CHARGECONNECTM_GB_CC220_IS_CONNECT(RES)     ((RES) >= ChargeConnectM_ConfigInfo.ResistancePara.CCRes220Min && (RES) <= ChargeConnectM_ConfigInfo.ResistancePara.CCRes220Max)
#define CHARGECONNECTM_GB_CC680_IS_CONNECT(RES)     ((RES) >= ChargeConnectM_ConfigInfo.ResistancePara.CCRes680Min && (RES) <= ChargeConnectM_ConfigInfo.ResistancePara.CCRes680Max)
#define CHARGECONNECTM_GB_CC1500_IS_CONNECT(RES)    ((RES) >= ChargeConnectM_ConfigInfo.ResistancePara.CCRes1500Min && (RES) <= ChargeConnectM_ConfigInfo.ResistancePara.CCRes1500Max)
#define CHARGECONNECTM_GB_CC_IS_CONNECT(RES)        (CHARGECONNECTM_GB_CC100_IS_CONNECT(RES) || \
                                                    CHARGECONNECTM_GB_CC220_IS_CONNECT(RES) || \
                                                    CHARGECONNECTM_GB_CC680_IS_CONNECT(RES) || \
                                                    CHARGECONNECTM_GB_CC1500_IS_CONNECT(RES))
#define CHARGECONNECTM_GB_CC2_IS_CONNECT(RES)       ((RES) >= ChargeConnectM_ConfigInfo.ResistancePara.CC2ResMin && (RES) <= ChargeConnectM_ConfigInfo.ResistancePara.CC2ResMax)
#define CHARGECONNECTM_GB_CP_DUTY_IS_VALID(DUTY)    (!(((DUTY) < PWM_DUTY_FROM_PERCENT(3U)) || ((DUTY) > PWM_DUTY_FROM_PERCENT(7U) && (DUTY) < PWM_DUTY_FROM_PERCENT(8U)) || ((DUTY) > PWM_DUTY_FROM_PERCENT(90U))))
#define CHARGECONNECTM_GB_CP_IS_CONNECT(DUTY)       CHARGECONNECTM_GB_CP_DUTY_IS_VALID(DUTY)
#define CHARGECONNECTM_GB_CP_FREQ_IS_VALID(FREQ)    ((FREQ) >= ChargeConnectM_ConfigInfo.CpPara.FreqMin && (FREQ) <= ChargeConnectM_ConfigInfo.CpPara.FreqMax)
#define CHARGECONNECTM_GB_CC_IS_ENABLE(MODE)        ((MODE) == CHARGECONNECTM_GB_AC_MODE1_CONNECT_B || \
                                                    (MODE) == CHARGECONNECTM_GB_AC_MODE2_CONNECT_B || \
                                                    (MODE) == CHARGECONNECTM_GB_AC_MODE3_CONNECT_B || \
                                                    (MODE) == CHARGECONNECTM_GB_AC_MODE3_CONNECT_C)

#define CHARGECONNECTM_GB_CC2_IS_ENABLE(MODE)       ((MODE) == CHARGECONNECTM_GB_DC_MODE)

#define CHARGECONNECTM_GB_CP_IS_ENABLE(MODE)        ((MODE) == CHARGECONNECTM_GB_AC_MODE2_CONNECT_B || \
                                                    (MODE) == CHARGECONNECTM_GB_AC_MODE3_CONNECT_A || \
                                                    (MODE) == CHARGECONNECTM_GB_AC_MODE3_CONNECT_B || \
                                                    (MODE) == CHARGECONNECTM_GB_AC_MODE3_CONNECT_C)


#define CHARGECONNECTM_SINGLE_PHASE_VOLT            1821U // 单相电压值，计算公式：0.9*0.92*220 精度：0.1v/bit 注：参考QCT 895 6.5.5
#define CHARGECONNECTM_THREE_PHASE_VOLT             5449U // 三相电压值，计算公式：1.732*0.9*0.92*380 精度：0.1v/bit 注：参考QCT 895 6.5.5
#define CHARGECONNECTM_AC_VOLT_DEFAULT              CHARGECONNECTM_SINGLE_PHASE_VOLT // v/bit 交流充电供电电压端电压值，用于功率转换 可选 380v

#define CHARGECONNECTM_CC_1500OHM_CURRENT_MAX       CURRENT_S_100MA_FROM_A(10) //0.1A CC 1.5K欧电阻连接允许最大电流
#define CHARGECONNECTM_CC_680OHM_CURRENT_MAX        CURRENT_S_100MA_FROM_A(16) //0.1A CC 680欧电阻连接允许最大电流
#define CHARGECONNECTM_CC_220OHM_CURRENT_MAX        CURRENT_S_100MA_FROM_A(32) //0.1A CC 220欧电阻连接允许最大电流
#define CHARGECONNECTM_CC_100OHM_CURRENT_MAX        CURRENT_S_100MA_FROM_A(63) //0.1A CC 100欧电阻连接允许最大电流

/**
 * \brief 充电连接管理CCx电阻类型定义
 */
typedef uint16 ChargeConnectM_CCxResistanceType;

/**
 * \brief 充电连接管理ADC通道类型定义
 */
typedef uint16 ChargeConnectM_CCxChannelType;

/**
 * \brief 充电连接方式定义
 */
typedef enum{
    CHARGECONNECTM_CONNECT_NONE = 0, /**< 无充电连接 可使用充电机通信作为充电连接*/
    CHARGECONNECTM_CONNECT_COMMUNICATION = 1, /**< 通信连接 */
    CHARGECONNECTM_CONNECT_DIN = 2, /**< 开关输入连接 DIN */
    CHARGECONNECTM_CONNECT_WAKEUP_SIGNAL = 3, /**< 唤醒信号 */
    CHARGECONNECTM_CONNECT_CURRENT = 4, /**< 充电电流 */
    CHARGECONNECTM_GB_START = 5,
    CHARGECONNECTM_GB_DC_MODE = CHARGECONNECTM_GB_START, /**< 国标直流模式 CC2*/
    CHARGECONNECTM_GB_AC_MODE1_CONNECT_B = 6, /**< 国标交流模式1连接B CC */
    CHARGECONNECTM_GB_AC_MODE2_CONNECT_B = 7, /**< 国标交流模式2连接B CC+CP */
    CHARGECONNECTM_GB_AC_MODE3_CONNECT_A = 8, /**< 国标交流模式3连接A CP */
    CHARGECONNECTM_GB_AC_MODE3_CONNECT_B = 9, /**< 国标交流模式3连接B CC+CP */
    CHARGECONNECTM_GB_AC_MODE3_CONNECT_C = 10, /**< 国标交流模式3连接C CC+CP */
    CHARGECONNECTM_GB_STOP = CHARGECONNECTM_GB_AC_MODE3_CONNECT_C,
    CHARGECONNECTM_CONNECT_SELF_DEFINE = 11, /**< 自定义充电连接 */

    CHARGECONNECTM_GB_CONNECT_MAX = 12
}ChargeConnectM_ConnectType;

/**
 * \brief ADC值到物理值得公式参数.
 * \details PhyValue = adcValue / (power * gain - adcValue) * pullup_resistance;
 */
typedef struct {
    uint16 power; /**< 供电电压 mv */
    uint16 adc_max; /**< ADC采集电压最大值 */
    ChargeConnectM_CCxResistanceType pullup_resistance; /**< 上拉电阻 ohm */
    float32 gain; /**< 增益 */
} ChargeConnectM_ValueAdcToPhyCalculateParamType;

/**
 * \brief 国标电阻参数类型定义
 */
typedef struct{
    ChargeConnectM_CCxResistanceType CCRes100Max; /**< CC100电阻最大值 */
    ChargeConnectM_CCxResistanceType CCRes100Min; /**< CC100电阻最小值 */
    ChargeConnectM_CCxResistanceType CCRes220Max; /**< CC220电阻最大值 */
    ChargeConnectM_CCxResistanceType CCRes220Min; /**< CC220电阻最小值 */
    ChargeConnectM_CCxResistanceType CCRes680Max; /**< CC680电阻最大值 */
    ChargeConnectM_CCxResistanceType CCRes680Min; /**< CC680电阻最小值 */
    ChargeConnectM_CCxResistanceType CCRes1500Max; /**< CC1500电阻最大值 */
    ChargeConnectM_CCxResistanceType CCRes1500Min; /**< CC1500电阻最小值 */
    ChargeConnectM_CCxResistanceType CC2ResMax; /**< CC2电阻最大值 */
    ChargeConnectM_CCxResistanceType CC2ResMin; /**< CC2电阻最小值 */
}ChargeConnectM_GBResParaType;

typedef struct{
    uint16 FreqMin; /**< 频率最小值 */
    uint16 FreqMax; /**< 频率最大值 */
}ChargeConnectM_GBCpParaType;

/**
 * \brief 充电连接DIN类型连接参数定义
 */
typedef struct{
    uint8 type; /**< 数字输入类型 */
    uint8 channel; /**< 数字输入通道 */
    uint16 on_delay; /**< 连接延时 */
    uint16 off_delay; /**< 断开延时 */
}ChargeConnectM_DinParaType;

typedef Std_ReturnType (*ChargeConnectM_ConnectFunPtr)(void);

/**
 * \brief 快充/慢充充电连接优先级配置类型
 */
typedef enum {
    CHARGECONNECTM_PRIO_TYPE_AC_EQ_DC = 0, //相同优先级，同时连接时，认为不连接，可报多连接故障
    CHARGECONNECTM_PRIO_TYPE_AC_GT_DC = 1, //慢充连接优先级高于快充连接
    CHARGECONNECTM_PRIO_TYPE_AC_LT_DC = 2, //快充连接优先级高于慢充连接
}ChargeConnectM_ConnectionPrioType;

/**
 * \brief 充电连接通用配置类型
 */
typedef struct{
    uint8 Wakeup; /**< 唤醒信号 */
    ChargeConnectM_ConnectType type;
    ChargeConnectM_DinParaType DinPara;
    ChargeConnectM_ConnectFunPtr FuncPtr;
}ChargeConnectM_CommonConfigType;

typedef struct{
    Current_CurrentType cur_min; /**< 最小充电连接电流 */
    Current_CurrentType rel_cur_min; /**< 最小充电连接释放电流 */
    uint32 connect_delay; /**< 连接延时 */
    uint32 unconnect_delay; /**< 连接释放延时 */
}ChargeConnectM_CurrentConnectParaType;

typedef struct{
    uint32 timeout; /**< 上电充电连接超时时间 */
}ChargeConnectM_StartConnectParaType;

/**
 * \brief 充电连接配置类型定义
 */
typedef struct{
    boolean ConnectionIsDynamic; /**< 充电连接是否动态更新 */
    boolean DoS2MonitorsEL; /**< S2监控电子锁状态开关 */
    boolean DoS2MonitorCPEnable; /**< S2监控CP使能开关 */
    uint16 S2OffDelayMin; /**< S2最小断开延时 */
    ChargeConnectM_ConnectionPrioType ConnectionPrio; /**< 快慢充连接优先级 */
    ChargeConnectM_CommonConfigType AC_Para;
    ChargeConnectM_CommonConfigType DC_Para;
    ChargeConnectM_CommonConfigType DC2_Para;
    ChargeConnectM_ValueAdcToPhyCalculateParamType AdcPara[CHARGECONNECTM_ADC_CHANNEL_MAX];
    ChargeConnectM_GBResParaType ResistancePara; /**< 国标电阻参数 */
    ChargeConnectM_GBCpParaType CpPara; /**< 国标CP参数 */
    ChargeConnectM_CurrentConnectParaType CurConnectPara; /**< 充电电流连接参数 */
    ChargeConnectM_StartConnectParaType StartConnectPara; /**< 上电充电连接参数 */
}ChargeConnectM_ConfigType;


/**
 * \brief CC故障诊断类型定义
 */
typedef struct{
    Std_CircuitFaultType CircuitFault; /**< CC电路诊断状态 */
}ChargeConnectM_CCDiagnosisStatusType;


/**
 * \brief CC2故障诊断类型定义
 */
typedef struct{
    Std_CircuitFaultType CircuitFault; /**< CC2电路诊断状态 */
}ChargeConnectM_CC2DiagnosisStatusType;


/**
 * \brief 充电连接管理故障诊断类型定义
 */
typedef struct{
    ChargeConnectM_CCDiagnosisStatusType CC_Diagnosis; /**< CC诊断状态 */
    ChargeConnectM_CC2DiagnosisStatusType CC2_Diagnosis; /**< CC2诊断状态 */
}ChargeConnectM_DiagnosisStatusType;

/**
 * \brief CC CC2状态类型定义
 */
typedef struct{
    uint16 voltage; /**< 电压值 */
    ChargeConnectM_CCxResistanceType resistance; /**< 电阻值 */
}ChargeConnectM_CCxStatusType;

typedef struct{
    Async_EventType event; /**< 异步事件 */
    Charge_ChargeType start_type; /**< 上电连接类型 */
    Charge_ChargeType current_type; /**< 当前充电连接类型 */
    Charge_ChargeType last_type; /**< 上一次充电连接类型 */
    uint8 double_connect; /**< 双重连接标志 */
    Charge_ChargeType dc2_start_type; /**< 上电连接类型 */
    Charge_ChargeType dc2_current_type; /**< 当前充电连接类型 */
    Charge_ChargeType dc2_last_type; /**< 上一次充电连接类型 */
    uint8 CpConnectFlag; /**< CP连接标志 */
    uint32 CpConnectLastTick; /**< CP连接计时 */
    uint8 ChargeCurrentConnectionFlag; /**< 充电电流连接标志 */
    uint32 acDinOnLastTime; /**< 慢充DIN连接计时 */
    uint32 acDinOffLastTime; /**< 慢充DIN断开计时 */
    uint32 dcDinOnLastTime; /**< 快充DIN连接计时 */
    uint32 dcDinOffLastTime; /**< 快充DIN断开计时 */
}ChargeConnectM_InnerDataType;


/**
 * \brief 声明外部充电连接配置参数
 */
extern const ChargeConnectM_ConfigType ChargeConnectM_ConfigInfo;


/**
 * /brief 充电连接管理初始化
 * /note 配置充电连接管理模块，包括AC DC充电的使能、连接方式等进行配置
 *
 * /param looper 异步事件循环
 */
void ChargeConnectM_Init(Async_LooperType *looper);

void ChargeConnectM_CCxStopSampleTemporary(uint32 time);

/**
 * \brief 充电连接管理反初始化
 */
void ChargeConnectM_Deinit(void);

/**
 * \brief 获取CCx信号状态的电压值
 *
 * \param ChannelId 通道号
 * \return 电压值
 */
uint16 ChargerConnectM_GetCCxVoltageStatus(ChargeConnectM_CCxChannelType ChannelId);

/**
 * \brief 获取CCx信号状态的电阻值
 *
 * \param ChannelId 通道号
 * \return 电阻值
 */
ChargeConnectM_CCxResistanceType ChargerConnectM_GetCCxResistanceStatus(ChargeConnectM_CCxChannelType ChannelId);

/**
 * \brief 获取DIN作为充电连接的连接状态
 *
 * \param type 连接类型 DIGITALINPUT_TYPE_SWITCH / DIGITALINPUT_TYPE_LEVEL / DIGITALINPUT_TYPE_WAKEUP_SIGNAL
 * \param channel 通道
 *
 * \return E_OK：连接 E_NOT_OK:未连接
 */
Std_ReturnType ChargeConnectM_DinIsConnect(uint8 type, uint8 channel);

/**
 * \brief 获取充电连接状态
 * \note 根据充电类型返回对应连接的连接状态
 *
 * \param ChargeType 充电类型 直流充电or交流充电
 * \return 充电连接状态 E-OK:连接 其他-未连接
 */
Std_ReturnType ChargeConnectM_GetConnectStatus(Charge_ChargeType ChargeType);
Std_ReturnType ChargeConnectM_GetDC2ConnectStatus(Charge_ChargeType ChargeType);

/**
 * \brief 获取实际连接充电类型
 * \note 根据充电类型返回当前实际连接的充电类型
 *
 * \return 充电连接类型 0-无 1-DC 2-AC 0xFF-无效值
 */
Charge_ChargeType ChargeConnectM_GetActualConnectType(void);

/**
 * \brief 获取当前连接充电类型
 * \note 根据充电类型返回当前连接的充电类型，此接口受ConnectionIsDynamic配置参数的影响，当连接为静态时，获取到的仅为上电时的连接状态
 *       当充电机通信快慢充无连接时，会同时检查快充2是否有连接,快慢充上电连接优先
 *
 * \return 充电连接类型 0-无 1-DC 2-AC 0xFF-无效值
 */
Charge_ChargeType ChargeConnectM_GetConnectType(void);

/**
 * \brief 获取充电机通信快慢充连接状态
 * \return 充电连接类型 0-无 1-DC 2-AC 0xFF-无效值
 */
Charge_ChargeType ChargeConnectM_GetDCACConnectType(void);

/**
 * \brief 获取扩展通信快充2连接状态
 * \return 充电连接类型 0-无 1-DC 2-AC 0xFF-无效值
 */
Charge_ChargeType ChargeConnectM_GetDC2ConnectType(void);

/**
 * \brief 获取上电后初次连接类型
 * \note 此值会在充电连接配置中上电连接超时配置参数内确定是否有充电连接，超时后则认为无充电连接，且后续不再更新
 *       包含充电机通信快慢充上电连接和快充2上电连接,快慢充上电连接优先
 *
 * \return 充电连接类型 0-无 1-DC 2-AC 0xFF-无效值
 */
Charge_ChargeType ChargeConnectM_GetStartConnectType(void);

/**
 * \brief 获取充电机通信快慢充上电连接状态
 * \return 充电连接类型 0-无 1-DC 2-AC 0xFF-无效值
 */
Charge_ChargeType ChargeConnectM_GetDCACStartConnectType(void);

/**
 * \brief 获取扩展通信快充2上电连接状态
 * \return 充电连接类型 0-无 1-DC 2-AC 0xFF-无效值
 */
Charge_ChargeType ChargeConnectM_GetDC2StartConnectType(void);

/**
 * \brief 充电是否连接
 * \return FALSE-未连接 TRUE-已连接
 */
boolean ChargeConnectM_IsConnection(void);

/**
 * \brief 获取充电类型对应的连接模式
 *
 * \param ChargeType 充电类型
 * \return 连接模式
 */
inline ChargeConnectM_ConnectType ChargerConnectM_GetConnectMode(Charge_ChargeType ChargeType);

/**
 * \brief 获取CP连接状态
 * \return TRUE：连接 FALSE: 未连接
 */
uint8 ChargeConnectM_GetCpConnectStatus(void);

/**
 * \brief 获取CC连接状态
 * \return TRUE：连接 FALSE: 未连接
 */
uint8 ChargeConnectM_GetCcConnectStatus(void);
uint8 ChargeConnectM_GetCc100ConnectStatus(void);
uint8 ChargeConnectM_GetCc220ConnectStatus(void);
uint8 ChargeConnectM_GetCc680ConnectStatus(void);
uint8 ChargeConnectM_GetCc1500ConnectStatus(void);

/**
 * \brief 获取CC2连接状态
 * \return TRUE：连接 FALSE: 未连接
 */
uint8 ChargeConnectM_GetCc2ConnectStatus(void);

/**
 * \brief 检查CC检测是否使能
 *
 * \param ChargeType 充电类型
 * \return E_NOT_OK:未使能 E_OK:使能
 */
Std_ReturnType ChargeConnectM_CCIsEnable(Charge_ChargeType ChargeType);

/**
 * \brief 检查CC2检测是否使能
 *
 * \param ChargeType 充电类型
 * \return E_NOT_OK:未使能 E_OK:使能
 */
Std_ReturnType ChargeConnectM_CC2IsEnable(Charge_ChargeType ChargeType);

/**
 * \brief 检查CP检测是否使能
 *
 * \param ChargeType 充电类型
 * \return E_NOT_OK:未使能 E_OK:使能
 */
Std_ReturnType ChargeConnectM_CPIsEnable(Charge_ChargeType ChargeType);

/**
 * \brief CC2连接是否故障
 * \details 阻值有效且不在有效范围
 * \return 0-正常 非0-故障
 */
uint16 ChargeConnectM_CC2ConnectIsFault(void);

/**
 * \brief CC连接是否故障
 * \details 阻值有效且不在有效范围
 * \return 0-正常 非0-故障
 */
uint16 ChargeConnectM_CCConnectIsFault(void);

/**
 * \brief CP连接是否故障
 * \details 频率有效且不在有效范围
 * \return 0-正常 非0-故障
 */
uint16 ChargeConnectM_CPConnectIsFault(void);

/**
 * \brief 获取连接模式预连接状态是否正常
 * \details 用于上电后一段时间内未达到国标完全连接状态时的预连接状态，主要为CP 12V电平到PWM切换之前的状态
 *
 * \param mode 国标连接模式
 * \return E_OK: 连接正常 E_NOT_OK: 连接异常
 */
Std_ReturnType ChargeConnectM_GBModeIsPreConnect(ChargeConnectM_ConnectType mode);

/**
 * \brief 判断当前充电类型状态下是否已经完成预连接
 * \details 用于上电后一段时间内未达到国标完全连接状态时的预连接状态，主要为CP 12V电平到PWM切换之前的状态；
 *
 * \return E_OK: 连接正常 E_NOT_OK: 连接异常
 */
Std_ReturnType ChargeConnectM_IsPreConnect(Charge_ChargeType type);
Std_ReturnType ChargeConnectM_DC2IsPreConnect(void);

/**
 * \brief 控制国标S2开启关闭
 *
 * \param Control 开启/关闭 STD_ON:开启 STD_OFF:关闭
 */
void ChargeConnectM_SetS2(uint8 Control);

/**
 * \brief 获取国标S2的当前控制状态
 *
 * \retval STD_ON 开启
 * \retval STD_OFF 关闭
 */
uint8 ChargeConnectM_GetS2(void);

/**
 * \brief 当前连接状态下是否需要电子锁控制
 *
 * \return TRUE-需要 FALSE-不需要
 */
boolean ChargeConnectM_ELIsNeeding(void);

/**
 * \brief 获取充电连接当前硬件连接状态下的最大允许充电电流
 *
 * \return 最大允许充电电流
 */
Current_CurrentType ChargeConnectM_GetChargeCurrentMax(Charge_ChargeType type);
Current_CurrentType ChargeConnectM_GetCcChargeCurrentMax(void);
Current_CurrentType ChargeConnectM_GetCpChargeCurrentMax(void);

/**
 * \brief 是否为充电连接双重连接故障
 * \details 当出现快充和慢充同时连接时，认为充电双重连接故障
 * \return 0-正常 1-故障
 */
uint16 ChargeConnectM_IsDoubleConnectFault(void);

/**
 * \brief 是否可以安全下电
 *
 * \return 返回TRUE时, 表示该任务已经关闭, 可以下电.
 */
boolean ChargeConnectM_SaftyOff(RuntimeM_SignalType signal);


#endif

/**
 * \}
 */
