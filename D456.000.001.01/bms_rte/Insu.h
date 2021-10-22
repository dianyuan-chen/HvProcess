/**
 * \addtogroup INSULATION 绝缘检测
 * \{
 */

#ifndef INSU_H_
#define INSU_H_

#include "Std_Types.h"
#include "Insu_Cfg.h"

/**
 * \brief 绝缘模块状态类型.
 */
typedef enum {
    INSU_STATUS_OK, /**< 绝缘检测正常 */
    INSU_STATUS_BUSBAR_ERR, /**< 绝缘母线异常 */
    INSU_STATUS_POLAR_RES_LOW, /**< 正极或负极绝缘阻值太低, 导致不能计算 */
    INSU_STATUS_COMMULICATION_ERR, /**< 独立绝缘模块通信异常 */
} Insu_StatusType;

/**
 * \brief 绝缘电阻值类型.
 */
typedef uint16 Insu_ResistorType;

/**
 * \brief 绝缘电阻无效值.
 */
#define INSU_RES_INVALID (0xffffu)

/**
 * \brief 绝缘检测初始化.
 * \note 初始化之后, 将会自动按照配置的参数进行绝缘检测.
 *
 * \param cfg 配置参数.
 */
void Insu_Init(const Insu_ConfigType *cfg);

/**
 * \brief 读取正端绝缘电阻.
 * \note 对于如果不能检测到正端绝缘电阻的硬件, 返回\link INSU_RES_INVALID \endlink.
 *
 * \return 绝缘电阻值.
 */
Insu_ResistorType Insu_GetPositive(void);


/**
 * \brief 读取负端绝缘电阻.
 * \note 对于如果不能检测到负端绝缘电阻的硬件, 返回\link INSU_RES_INVALID \endlink.
 *
 * \return 绝缘电阻值.
 */
Insu_ResistorType Insu_GetNegative(void);


/**
 * \brief 读取系统绝缘电阻.
 * \details 分别读取正极绝缘阻值和负极绝缘阻值，两者取小作为系统绝缘阻值
 *
 * \return 绝缘电阻值.
 */
Insu_ResistorType Insu_GetSystem(void);

/**
 * \brief 读取绝缘模块的工作状态.（此函数未实现）
 *
 * \return 绝缘模块的工作状态.
 */
Insu_StatusType Insu_GetStatus(void);

/**
 * \brief 反初始化.
 * \note 该函数执行之后, 绝缘检测将停止.
 */
void Insu_Deinit(void);

/**
 * \brief 获取漏电率 单位ohm/v
 * \details 根据当前B+总压和系统绝缘阻值计算漏电率
 */
uint16 Insu_GetLeak(void);

/**
 * \brief 绝缘阻值是否有效
 *
 * \param resistor 绝缘阻值
 * \return TRUE:无效 FALSE:有效
 */
uint8 Insu_ResIsValid(Insu_ResistorType resistor);

/**
 * \brief 绝缘阻值是否已经完成计算
 * \details 系统上电后完成一次绝缘阻值计算即返回TRUE
 * \return FALSE:未计算 TRUE:已计算
 */
boolean Insu_IsCalculated(void);

/**
 * \brief 绝缘漏电值是否有效
 * \details 0xFFFFU代表无效值
 *
 * \param leak 漏电值 单位ohm/V
 * \return 0-无效 1-有效
 */
uint8 Insu_LeakIsValid(uint16 leak);

#endif

/** \} */