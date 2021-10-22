/**
 * \addtogroup SOC
 * \{
 */

#ifndef SOC_H_
#define SOC_H_

#include "Std_Types.h"
#include "App_Types.h"
#include "Soc_Cfg.h"
#include "CurrentM.h"
#include "Async_Looper.h"
#include "Async_Event.h"
#include "Diagnosis.h"
#include "BatteryInfo.h"
#include "RuntimeM.h"

/**
 * \brief 剩余容量溢出最大值
 * \details 剩余容量超过总容量最大值
 */
#define SOC_LEFT_CAP_MAX(TOTAL_CAP)             (DIVISION((uint32)(TOTAL_CAP) * SOC_MAX_VALUE, PERCENT_TO_SOC(100)))

/**
 * \brief 可修正总容量最小值
 */
#define SOC_VALID_TOTAL_CAP_MIN                 (DIVISION((uint32)BatteryInfo_BaseConfigInfo.NominalCap * SOH_VALID_MIN, PERCENT_TO_SOH(100)))


#define SOC_CHG_EFFICIENCY_IS_VALID(efficiency) (efficiency >= SOC_CHG_EFFICIENCY_MIN && efficiency <= SOC_CHG_EFFICIENCY_MAX)
#define SOC_DCHG_EFFICIENCY_IS_VALID(efficiency) (efficiency >= SOC_DCHG_EFFICIENCY_MIN && efficiency <= SOC_DCHG_EFFICIENCY_MAX)

#define SOC_JUMP_SOC_RESOLUTION                 PERCENT_TO_SOC(1)
#define SOC_JUMP_SOC_INVALID_INTERNAL           0xFFFFU
/**
 * \brief 电流积分类型定义
 */
typedef sint32 Soc_IntegralType;

typedef void *VoidPointer;
/**
 * \brief 获取空校准函数
 * \return 空校准值, 分辨率：0.1%/bit
 */
typedef uint16 (*SOC_EmptyCalib)(void);
/**
 * \brief SOC模块标定参数类型定义
 */
typedef struct {
    uint16 ChargeIntegralEfficiency; /**< 充电效率因子 精度：0.1% */
    uint16 DischargeIntegralEfficiency; /**< 放电效率因子 精度：0.1% */
} Soc_CalibConfigType;

typedef App_SocType (*Soc_GetJumpSocMaxFuncPtr)(void);

/**
 * \brief SOC跳变参数类型定义
 */
typedef struct{
    App_SocType socJumpMax; /**< SOC最大跳变值，注：此值需要不大于SOC跳变缓存大小SOC_JUMP_BUFF_SIZE（默认30） */
    Soc_GetJumpSocMaxFuncPtr func; /**< 获取最大跳变SOC值，包含释放值，此函数有效时 socJumpMax 不启作用 */
    uint16 socJumpTime; /**< SOC跳变时间 单位：S */
}Soc_JumpConfigType;

typedef enum {
    Soc_CumuTypeNone, /**< 不累计 */
    Soc_CumuTypeCap, /**< 累计容量类型AH */
    Soc_CumuTypePower, /**< 累计能量类型WH */
}Soc_CumuLativeTypeType;

typedef struct {
    Soc_CumuLativeTypeType type; /**< 累计类型 */
    uint16 resoltion; /**< 存储分辨率(仅用于能量累计类型) */
}Soc_DchgCumuInfoType;

typedef struct {
    Soc_CumuLativeTypeType type; /**< 累计类型 */
    uint16 resoltion; /**< 存储分辨率(仅用于能量累计类型) */
    boolean isContainFeedback; /**< 是否包含回馈电流 */
}Soc_ChgCumuInfoType;

/**
 * \brief SOC配置参数类型定义
 */
typedef struct{
    Soc_ChgCumuInfoType ChgCumuInfo; /**< 充电累计配置信息 */
    Soc_DchgCumuInfoType DchgCumuInfo; /**< 放电累计配置信息 */
    Soc_JumpConfigType jumpPara; /**< SOC跳变参数 */
    SOC_EmptyCalib func; /**< SOC空校准函数*/
    App_SocType socMaxForCharging; /**< 充电中最大SOC值 */
}Soc_ConfigInfoType;

/**
 * \brief SOC内部参数类型定义
 */
typedef struct{
    uint8 start; /**< 启动标志 */
    uint8 clrEeepIntegralFlag; /**< 增强EEPROM积分值清零标志 */
    App_SocType soc; /**< 当前SOC */
    App_CapType leftCap; /**< 剩余容量 */
    Soc_IntegralType integral; /**< 积分值 精度：100UAs/bit */
    Soc_IntegralType rtcRamIntegralLast; /**< 上次记录RTC RAM中存储的积分值 */
    uint32 lastTime; /**< 上次积分时间 */
    uint8 socOverLimitFlag; /**< Soc超时限制值标志，用于充电SOC保持 */
    Async_EventType event; /**< 周期更新事件 */
    uint16 chgEfficiency; /**< 充电因子 */
    uint16 dchgEfficiency; /**< 放电因子 */
    uint8 jumpSocWriteIndex; /**< SOC变化值写入索引 */
    App_SocType jumpSocLast; /**< 上一次SOC跳变值 */
    App_SocType jumpSocBuff[SOC_JUMP_BUFF_SIZE]; /**< 跳变SOC缓存 */
    uint32 jumpTimeBuff[SOC_JUMP_BUFF_SIZE]; /**< 跳变时间缓存 */
    uint32 ChgPowerIntegral; /**< 充电能量积分值 精度：1wh/bit */
    uint32 DchgPowerIntegral; /**< 放电能量积分值 精度：1wh/bit */
    uint32 thisCumuChgPower; /**< 本次上电充电能量累计 精度：与配置精度一致 */
    uint32 thisCumuDchgPower; /**< 本次上电放电能量累计 精度：与配置精度一致 */
    App_CapType chgHoldSocLeftCap; /**< 充电保持SOC值对应的剩余容量值 */
    Soc_IntegralType chgHoldSocIntegral; /**< 充电保持SOC值对应的剩余容量小数值 */
}Soc_InnerDataType;

extern const boolean SoxUseModel;

extern const Soc_ConfigInfoType Soc_ConfigInfo;

/**
 * \brief Soc初始化
 * \note 需要从EEEPROM中恢复SOC值.
 */
void Soc_Init(Async_LooperType *looper);


/**
 * \brief 获取当前计算的SOC.
 *
 * \return SOC值, 分辨率：0.1%/bit
 */
App_SocType Soc_Get(void);

App_SocType ModelRealSoc_Get(void);

/**
 * \brief 设置充电因子
 * \details 要求充电因子介于SOC_CHG_EFFICIENCY_MIN和SOC_CHG_EFFICIENCY_MAX之间，超出此范围使用最大或最小值
 *
 * \param efficiency 充电因子, 分辨率：0.1%/bit
 */
Std_ReturnType Soc_SetChgEfficiency(uint16 efficiency);

/**
 * \brief 获取充电因子
 * \return 充电因子, 分辨率：0.1%/bit
 */
uint16 Soc_GetChgEfficiency(void);

/**
 * \brief 设置放电因子
 * \details 要求放电因子介于SOC_DCHG_EFFICIENCY_MIN和SOC_DCHG_EFFICIENCY_MAX之间，超出此范围时使用最大或最小值
 *
 * \param efficiency 放电因子, 分辨率：0.1%/bit
 */
Std_ReturnType Soc_SetDchgEfficiency(uint16 efficiency);

/**
 * \brief 获取放电因子
 * \return 放电因子, 分辨率：0.1%/bit
 */
uint16 Soc_GetDchgEfficiency(void);

/**
 * \brief 重新校准SOC值.
 * \note 该函数主要是给上层在充电或放电末端实施SOC校准时调用.
 *
 * \param val 新的SOC值, 分辨率：0.1%/bit
 */
void Soc_Set(App_SocType val);

/**
 * \brief 更新电流积分小数部分值
 * \details 用于恢复保存下来的电流积分小数部分的值，以保证积分精度
 *
 * \param value SOC电流积分值,分辨率：0.1mAS
 */
void Soc_SetCurrentIntegralValue(Soc_IntegralType value);

/**
 * \brief 获取当前SOC电流积分小数部分的值
 *
 * \return SOC电流积分值,分辨率：0.1mAS
 */
Soc_IntegralType Soc_GetCurrentIntegralValue(void);

/**
 * \brief 配置总容量
 * \details 如果总容量不大于额定容量，则更新并保存总容量，否则返回失败，同时检查如果剩余容量大于当前总容量，更新并保存剩余容量
 *
 * \param totalCap 总容量,分辨率：0.1AH/bit
 * \return E_OK: 配置成功 E_NOT_OK:配置失败
 */
Std_ReturnType Soc_ConfigTotalCap(App_CapType totalCap);

/**
 * \brief 配置剩余容量
 * \details 如果剩余容量不大于当前总容量，则更新并保存剩余容量，否则返回失败
 *
 * \param leftCap 剩余容量,分辨率：0.1AH/bit
 * \return E_OK: 配置成功 E_NOT_OK:配置失败
 */
Std_ReturnType Soc_ConfigLeftCap(App_CapType leftCap);

/**
 * \brief 获取精确剩余容量值
 * \details 包含剩余容量整数部分与正在积分的小数部分,分辨率：0.1AH/bit
 *
 * \return 剩余容量值 返回0xFFFF为无效值
 */
App_CapType Soc_GetHighPrecisionLeftCap(void);

/**
 * \brief 根据剩余容量和总容量计算SOC值,分辨率：0.1%/bit
 *
 * \param totalCap 总容量,分辨率：0.1AH/bit
 * \param leftCap 剩余容量,分辨率：0.1AH/bit
 *
 * \return SOC值
 */
App_SocType Soc_SocFromCap(uint32 totalCap, uint32 leftCap);

/**
 * \brief 获取SOC过限制值标志
 * \details 此限制值为充电时未充满前SOC保持的最大值，超时此值时需要置位此标志
 *
 * \return 过限制值标志
 */
uint8 Soc_GetOverLimitFlag(void);

/**
 * \brief 设置SOC过限制值标志
 * \details 当出现SOC满校正时需要调用此函数取消限制，以便SOC可达到100%，此限制仅在充电未充电时有效
 *
 * \param flag 限制值标志
 */
void Soc_SetOverLimitFlag(uint8 flag);

/**
 * \brief 保存剩余容量小数部分电流积分值到eeeprom
 * \details 仅保存小于1AH的小数部分剩余容量的电流积分值，分辨率：0.1mAS
 *
 * \param integral 电流积分值
 */
void Soc_SaveHighPrecision(Soc_IntegralType integral);

/**
 * \brief 延时下电保存当前剩余容量回调函数
 * \details 高精度SOC保存，主要作用是将当前SOC保存到eeeprom和rtc ram中
 *
 * \param signal 触发信号
 */
boolean Soc_PowerDownSaveCbk(RuntimeM_SignalType signal);

/**
 * \brief soc是否有效
 *
 * \param soc SOC值
 * \return 0-无效 1-有效
 */
uint8 Soc_SocIsValid(App_SocType soc);

/**
 * \brief SOC达到跳变值的时间间隔
 *
 * \return 时间间隔，单位：S
 */
uint16 Soc_GetJumpSocInternal(void);

/**
 * \brief SOC跳变时间间隔是否有效
 *
 * \param internal 时间间隔，单位：S
 * \return 0-无效 1-有效
 */
uint8 Soc_JumpSocInternalIsValid(uint16 internal);

/**
 * \brief 获取本次上电充电能量值
 * \details 根据配置信息，充电能量有两类：容量or电量，容量分辨率为1AH，电量分辨率由配置决定
 * \return 能量值
 */
uint32 Soc_GetChgPower(void);

/**
 * \brief 获取本次上电放电能量值
 * \details 根据配置信息，能量有两类：容量or电量，容量分辨率为1AH，电量分辨率由配置决定
 * \return 能量值
 */
uint32 Soc_GetDchgPower(void);

/**
 * \brief 获取累计充电能量值
 * \details 根据配置信息，充电能量有两类：容量or电量，容量分辨率为1AH，电量分辨率由配置决定
 * \return 能量值
 */
uint32 Soc_GetCumuChgPower(void);

/**
 * \brief 获取累计放电能量值
 * \details 根据配置信息，能量有两类：容量or电量，容量分辨率为1AH，电量分辨率由配置决定
 * \return 能量值
 */
uint32 Soc_GetCumuDchgPower(void);

/**
 * \brief 配置模型总容量
 * \details 如果总容量不大于额定容量，则更新并保存总容量，否则返回失败，同时检查如果剩余容量大于当前总容量，更新并保存剩余容量
 *
 * \param totalCap 总容量,分辨率：0.1AH/bit
 * \return E_OK: 配置成功 E_NOT_OK:配置失败
 */
Std_ReturnType Soc_ModelConfigTotalCap(App_CapType totalCap);

/**
 * \brief 配置模型剩余容量
 * \details 如果总容量不大于额定容量，则更新并保存总容量，否则返回失败，同时检查如果剩余容量大于当前总容量，更新并保存剩余容量
 *
 * \param leftCap 总容量,分辨率：0.1AH/bit
 * \return E_OK: 配置成功 E_NOT_OK:配置失败
 */
Std_ReturnType Soc_ModelConfigLeftCap(App_CapType leftCap);

App_SocType ModelSoc_Get(void);

/**
 * \brief 配置模型真实剩余容量
 * \details 如果总容量不大于额定容量，则更新并保存总容量，否则返回失败，同时检查如果剩余容量大于当前总容量，更新并保存剩余容量
 *
 * \param leftCap 总容量,分辨率：0.1AH/bit
 * \return E_OK: 配置成功 E_NOT_OK:配置失败
 */
Std_ReturnType Soc_ModelConfigRealLeftCap(App_CapType leftCap);

/**
 * \brief 配置模型显示剩余容量
 * \details 如果总容量不大于额定容量，则更新并保存总容量，否则返回失败，同时检查如果剩余容量大于当前总容量，更新并保存剩余容量
 *
 * \param leftCap 总容量,分辨率：0.1AH/bit
 * \return E_OK: 配置成功 E_NOT_OK:配置失败
 */
Std_ReturnType Soc_ModelConfigDispLeftCap(App_CapType leftCap);

/**
 * @brief 外部依赖函数声明
 */
extern Std_ReturnType Soc_IsChargeFinish(void);
extern Current_CurrentType Soc_CurrentHook(Current_CurrentType current);
extern boolean Soc_IsBatteryCurrent(void);
uint16 SOC_EmptyCalibFunc(VoidPointer func);
uint16 SOC_DefaultEmptyCalib(void);
extern uint16 Model_SOH;
extern uint32 Model_LeftChargeTime;

#endif

/** \} */
