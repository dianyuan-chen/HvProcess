#ifndef POWERM_CFG_H
#define POWERM_CFG_H

/**
 * \brief 功率控制电流类型
 */
typedef enum {
    POWERM_CUR_DCHARGE_CONTINUE, /**< 持续放电电流类型 */
    POWERM_CUR_DCHARGE_PEAK, /**< 峰值放电电流类型 */
    POWERM_CUR_DCHARGE_FEEDBACK, /**< 回馈电流类型 */
    POWERM_CUR_CHARGE_CONTINUE, /**< 充电最大电流类型 */
    POWERM_CUR_CHARGE_DC, /**< 直流快充充电电流 */
    POWERM_CUR_CHARGE_AC, /**< 交流慢充充电电流 */
    POWERM_CUR_CHARGE_HEATER, /**< 充电加热电流 */
    POWERM_CUR_EXTERN, /**< 扩展电流 */

    POWERM_CUR_TYPE_NUM,
} PowerM_CurrentTypeType;

#endif
