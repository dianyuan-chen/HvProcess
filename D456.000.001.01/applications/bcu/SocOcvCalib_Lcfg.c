/**
 * \file SocOcvCalib_Lcfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Soc静态校正配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170223 |
 */
#include "SocOcvCalib.h"
#include "Std_Types.h"

/**
 * \brief OCV-SOC温度表
 *
 * \note 两个温度点代表一个温度范围，[0]:代表最低有效温度 [MAX]:代表最高有效温度，超时最低和最高时不进行SOC校准，此Buffer必须大于1
 *       此Buffer查询采用就近原则取索引号
 */
const sint16 SocOcvCalib_TemperatureBuffer[] = {
    TEMPERATURE_FROM_C(-40), TEMPERATURE_FROM_C(125),
};

/**
 * \brief OCV-SOC soc表
 *
 * \note 一个SOC值对应一个OCV电压，[0]:代表<=最小电压对应的SOC值，[MAX]:代表>=最大电压对应的SOC值
 *       此Buffer查询采用就近原则取索引号
 */
const App_SocType SocOcvCalib_SocBuffer[] = {
    PERCENT_TO_SOC(5U), PERCENT_TO_SOC(10U), PERCENT_TO_SOC(15U), PERCENT_TO_SOC(20U), PERCENT_TO_SOC(25U),
    PERCENT_TO_SOC(30U), PERCENT_TO_SOC(50U), PERCENT_TO_SOC(70U), PERCENT_TO_SOC(75U), PERCENT_TO_SOC(80U),
    PERCENT_TO_SOC(85U), PERCENT_TO_SOC(90U), PERCENT_TO_SOC(95U), PERCENT_TO_SOC(100U)
};

/**
 * \brief OCV-SOC 电压表
 * \note 与SocOcvCalib_TemperatureBuffer数组对应，一个温度对应一组电压数据，必须一一对应
 */
const App_VoltageType SocOcvCalib_VoltageBuffer[] = {
    3020U, 3130U, 3180U, 3205U, 3213U, 3222U, 3255U, 3288U, 3296U, 3310U, 3320U, 3330U, 3346U, 3410U,
    3025U, 3135U, 3185U, 3210U, 3218U, 3227U, 3260U, 3293U, 3301U, 3315U, 3325U, 3335U, 3350U, 3415U,
};

const SocOcvCalib_ConfigType SocOcvCalib_ConfigInfo = {
    (uint8)ARRAY_SIZE(SocOcvCalib_SocBuffer), /**< socBuffSize: SOC缓存大小 */
    (uint8)ARRAY_SIZE(SocOcvCalib_TemperatureBuffer), /**< temperatureBuffSize: 温度缓存大小 */
    CURRENT_100MA_FROM_A(3U), /**< allowedCurrent：校准允许最大电流 */
    S_TO_MS(2U), /**< powerOnDelay：上电检查延时时间 1mS/bit */
    HOUR_TO_MIN(12U), /**< calibCycle:OCV-SOC校准周期 1min/bit */
    HOUR_TO_MIN(5U*24U), /**< longCycle:OCV-SOC校准周期 1min/bit */
    1800U, /**< checkCycle:OCV-SOC查询周期 1s/bit */
    PERCENT_TO_SOC(0U), /**< diffSocMin:允许校准最小SOC差 */
    PERCENT_TO_SOC(100U), /**< calibStep:SOC校准步长 */
    TRUE, /**< linear_calib: 线性校准使能 */
    NULL, /**< isAllowFuncPtr:是否允许校正函数指针 */
    TRUE, /**< temperature_linear: 温度是否线性查表 */
    5U, /**< diffVoltMin: 允许校正最小压差 */
    TRUE, /**< chargeReset: 是否充电模式重置 */
};
