
/**
 * \addtogroup SOC
 * \{
 */

#ifndef SOC_CFG_H_
#define SOC_CFG_H_

#define SOC_DEV_ERROR_DETECT        STD_OFF

#define SOC_MAX_VALUE               PERCENT_TO_SOC(100U)

#define SOC_MAX_VALID_VALUE         PERCENT_TO_SOC(120U) //用于配置参数

/**
 * \brief 电流时间积分最大时间间隔
 */
#define SOC_INTEGRAL_INTERNAL_MAX   S_TO_MS(1UL)

/**
 * \brief 单次电流积分最大值
 */
#define SOC_100UAS_INTEGRAL_MAX     ((Soc_IntegralType)AH_TO_100UAS(1UL))

/**
 * \brief SOC满充前达到的最大值
 */
#define SOC_MAX_FOR_FULL_CHARGE     PERCENT_TO_SOC(99U)

/**
 * \brief 充放电因子参数
 */
#define SOC_CHG_EFFICIENCY_MAX      PERCENT_TO_THOUSAND(200U)
#define SOC_CHG_EFFICIENCY_MIN      PERCENT_TO_THOUSAND(50U)
#define SOC_DCHG_EFFICIENCY_MAX     PERCENT_TO_THOUSAND(200U)
#define SOC_DCHG_EFFICIENCY_MIN     PERCENT_TO_THOUSAND(50U)

/**
 * \brief SOC跳变缓存大小
 */
#define SOC_JUMP_BUFF_SIZE          30U

#endif

/**
 * \}
 */