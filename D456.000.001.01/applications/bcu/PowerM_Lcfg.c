#include "PowerM.h"
#include "Soc.h"
#include "Statistic.h"

static Std_ReturnType thisSocGet(uint16 *v) {
    *v = ModelRealSoc_Get();
    return Soc_SocIsValid(*v) ? E_OK : E_NOT_OK;
}

// 快充充电电流表（无特殊说明，所有温度点必须有回滚）
static uint16 const dcchgsocxvalue[] = {PERCENT_TO_SOC(104)};
static sint16 const dcchgtempyvalue[] = {TEMPERATURE_FROM_C(-5), TEMPERATURE_FROM_C(60)};
static sint16 const dcchgtempaltyvalue[] = {TEMPERATURE_FROM_C(-3), TEMPERATURE_FROM_C(58)};
static uint16 const dcchgtableValue[] = {
    CURRENT_100MA_FROM_A(0U),// <= -5
    CURRENT_100MA_FROM_A(20U), // <= 60
};
static const PowerM_DiagnosisPercentMapType dcchgdiag[] = {
    {DIAGNOSIS_ITEM_VOLT_LINE, {100U, 50U, 0U, 0U}},
    {DIAGNOSIS_ITEM_TEMP_LINE, {100U, 50U, 0U, 0U}},
    // {DIAGNOSIS_ITEM_CHG_HT, {60U, 50U, 10U, 0U}},
    // {DIAGNOSIS_ITEM_CHG_LT, {60U, 50U, 10U, 0U}},
};


static const PowerM_ChargeEndConfigType dcDecreaseCurrent = {
    &dcDecreaseCurrent,
    3650U,
    5000U,
    POWERM_CHARGE_END_DEC_TO_CONSTVAL,
    CURRENT_100MA_FROM_A(0u),
    CURRENT_100MA_FROM_A(3U),
};

static Std_ReturnType thisHvGet(uint16 *v) {
    *v = Statistic_GetBcuHvMax();
    return CellDataM_VoltageIsValid(*v) ? E_OK : E_NOT_OK;
}

static const PowerM_ConfigParamType PowerMCurChgDcConfigTable = {
    ARRAY_SIZE(dcchgsocxvalue), /**< 功率控制表X轴分隔数量 */
    ARRAY_SIZE(dcchgtempyvalue), /**< 功率控制表Y轴分隔数量 */
    dcchgsocxvalue, /**< 功率控制表X轴分隔表 */
    dcchgtempyvalue, /**< 功率控制表Y轴分隔表 */
    dcchgtempaltyvalue, /**< 功率控制表Y轴回滚分隔表 */
    dcchgtableValue, /**< 各个分隔对应的值 */
    POWERM_YAXIS_USE_MIN, /**< 在yAxis和yAltAxis查询到的值取怎样取值，POWERM_YAXIS_USE_XX */
    0U, /**< 在y轴增加时使用Alt表 */
    POWERM_XAXIS_SUPPORT_L2R, /**< X轴支持变动方向 */
    0U, /**< X轴区间线性插值 */
    (uint8)ARRAY_SIZE(dcchgdiag), /**<  诊断故障功率百分比数量 */
    dcchgdiag, /**<  断故障功率百分比表 */
    thisSocGet, /**< 获取X轴值的函数 */
    1000U, /**< 功率输出时增加斜率时间参数 */
    CURRENT_100MA_FROM_A(20U), /**< 功率输出时增加斜率步进参数 */
    1000U, /**< 功率输出时减小斜率时间参数 */
    CURRENT_100MA_FROM_A(10U), /**< 功率输出时减小斜率步进参数 */
    3650U, /**< 充电末端X轴达到这个值时进入降流阶段 */
    &dcDecreaseCurrent /* &dcDecreaseCurrent */, /**< 降流链表 */
    thisHvGet /* thisHvGet */,  /**< 获取降流末端比较值函数 */
    NULL, /**< getChargeEndTable 获取降流链表，此函数配置后“chargeEndConfigs”和“getChargeEndCheckVal”将不起作用 */
    NULL, /**< 计算出目标值之后，使用改函数修改目标电流值，可用于复杂降流策略，包含故障降流 */
    NULL, /**< 在复位降流表时，只用该函数复位用户层数据，一般与hook函数配合使用 */
    0UL, /**< 温度改变引起查表区域变化时的确认时间，单位ms */
    NULL, /**< 计算出查表电流值之后，使用改函数修改查表电流值，可用于复杂降流策略，不包含故障降流 */
};

// 慢充充电电流表（无特殊说明，所有温度点必须有回滚）
static uint16 const acchgsocxvalue[] = {PERCENT_TO_SOC(50), PERCENT_TO_SOC(80), PERCENT_TO_SOC(90), PERCENT_TO_SOC(104)};
static sint16 const acchgtempyvalue[] = {TEMPERATURE_FROM_C(-11), TEMPERATURE_FROM_C(0), TEMPERATURE_FROM_C(15), TEMPERATURE_FROM_C(40), TEMPERATURE_FROM_C(45), TEMPERATURE_FROM_C(50)};
static sint16 const acchgtempaltyvalue[] = {TEMPERATURE_FROM_C(-12), TEMPERATURE_FROM_C(-1), TEMPERATURE_FROM_C(14), TEMPERATURE_FROM_C(35), TEMPERATURE_FROM_C(40), TEMPERATURE_FROM_C(45)};
static uint16 const acchgtableValue[] = {
    CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), // <= -11
    CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), // <= 0
    CURRENT_100MA_FROM_A(30U), CURRENT_100MA_FROM_A(30U), CURRENT_100MA_FROM_A(30U), CURRENT_100MA_FROM_A(10U), // <= 15
    CURRENT_100MA_FROM_A(50U), CURRENT_100MA_FROM_A(30U), CURRENT_100MA_FROM_A(20U), CURRENT_100MA_FROM_A(10U), // <= 40
    CURRENT_100MA_FROM_A(20U), CURRENT_100MA_FROM_A(20U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), // <= 45
    CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), // <= 50
};
static const PowerM_DiagnosisPercentMapType acchgdiag[] = {
    {DIAGNOSIS_ITEM_CHG_HV, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_CHG_HT, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_CHG_LT, {60U, 50U, 10U, 0U}},
};

static const PowerM_ConfigParamType PowerMCurChgAcConfigTable = {
    ARRAY_SIZE(acchgsocxvalue), /**< 功率控制表X轴分隔数量 */
    ARRAY_SIZE(acchgtempyvalue), /**< 功率控制表Y轴分隔数量 */
    acchgsocxvalue, /**< 功率控制表X轴分隔表 */
    acchgtempyvalue, /**< 功率控制表Y轴分隔表 */
    acchgtempaltyvalue, /**< 功率控制表Y轴回滚分隔表 */
    acchgtableValue, /**< 各个分隔对应的值 */
    POWERM_YAXIS_USE_MIN, /**< 在yAxis和yAltAxis查询到的值取怎样取值，POWERM_YAXIS_USE_XX */
    0U, /**< 在y轴增加时使用Alt表 */
    POWERM_XAXIS_SUPPORT_L2R, /**< X轴支持变动方向 */
    0U, /**< X轴区间线性插值 */
    (uint8)ARRAY_SIZE(acchgdiag), /**<  诊断故障功率百分比数量 */
    acchgdiag, /**<  断故障功率百分比表 */
    thisSocGet, /**< 获取X轴值的函数 */
    500U, /**< 功率输出时增加斜率时间参数 */
    CURRENT_100MA_FROM_A(10U), /**< 功率输出时增加斜率步进参数 */
    500U, /**< 功率输出时减小斜率时间参数 */
    CURRENT_100MA_FROM_A(10U), /**< 功率输出时减小斜率步进参数 */
    0U, /**< 充电末端X轴达到这个值时进入降流阶段 */
    NULL, /**< 降流链表 */
    NULL,  /**< 获取降流末端比较值函数 */
    NULL, /**< getChargeEndTable 获取降流链表，此函数配置后“chargeEndConfigs”和“getChargeEndCheckVal”将不起作用 */
    NULL, /**< 计算出目标值之后，使用改函数修改目标电流值，可用于复杂降流策略，包含故障降流 */
    NULL, /**< 在复位降流表时，只用该函数复位用户层数据，一般与hook函数配合使用 */
    0UL, /**< 温度改变引起查表区域变化时的确认时间，单位ms */
    NULL, /**< 计算出查表电流值之后，使用改函数修改查表电流值，可用于复杂降流策略，不包含故障降流 */
};

// 加热电流表
static uint16 const chgheatersocxvalue[] = {PERCENT_TO_SOC(104)};
static sint16 const chgheatertempyvalue[] = {TEMPERATURE_FROM_C(-10), TEMPERATURE_FROM_C(0), TEMPERATURE_FROM_C(15)};
static uint16 const chgheatertableValue[] = {
    CURRENT_100MA_FROM_A(20U), // < -10
    CURRENT_100MA_FROM_A(10U), // < 0
    CURRENT_100MA_FROM_A(5U), // < 15
};
static const PowerM_DiagnosisPercentMapType chgheatdiag[] = {
    {DIAGNOSIS_ITEM_CHG_HEAT_OC, {0U, 0U, 0U, 0U}},
};
static const PowerM_ConfigParamType PowerMCurChgHeaterConfigTable = {
    ARRAY_SIZE(chgheatersocxvalue), /**< 功率控制表X轴分隔数量 */
    ARRAY_SIZE(chgheatertempyvalue), /**< 功率控制表Y轴分隔数量 */
    chgheatersocxvalue, /**< 功率控制表X轴分隔表 */
    chgheatertempyvalue, /**< 功率控制表Y轴分隔表 */
    chgheatertempyvalue, /**< 功率控制表Y轴回滚分隔表 */
    chgheatertableValue, /**< 各个分隔对应的值 */
    POWERM_YAXIS_USE_LT, /**< 在yAxis和yAltAxis查询到的值取怎样取值，POWERM_YAXIS_USE_XX */
    0U, /**< 在y轴增加时使用Alt表 */
    POWERM_XAXIS_SUPPORT_BDIR, /**< X轴支持变动方向 */
    0U, /**< X轴区间线性插值 */
    (uint8)ARRAY_SIZE(chgheatdiag), /**<  诊断故障功率百分比数量 */
    chgheatdiag, /**<  断故障功率百分比表 */
    thisSocGet, /**< 获取X轴值的函数 */
    500U, /**< 功率输出时增加斜率时间参数 */
    CURRENT_100MA_FROM_A(10U), /**< 功率输出时增加斜率步进参数 */
    500U, /**< 功率输出时减小斜率时间参数 */
    CURRENT_100MA_FROM_A(10U), /**< 功率输出时减小斜率步进参数 */
    0U, /**< 充电末端X轴达到这个值时进入降流阶段 */
    NULL, /**< 降流链表 */
    NULL,  /**< 获取降流末端比较值函数 */
    NULL, /**< getChargeEndTable 获取降流链表，此函数配置后“chargeEndConfigs”和“getChargeEndCheckVal”将不起作用 */
    NULL, /**< 计算出目标值之后，使用改函数修改目标电流值，可用于复杂降流策略，包含故障降流 */
    NULL, /**< 在复位降流表时，只用该函数复位用户层数据，一般与hook函数配合使用 */
    0UL, /**< 温度改变引起查表区域变化时的确认时间，单位ms */
    NULL, /**< 计算出查表电流值之后，使用改函数修改查表电流值，可用于复杂降流策略，不包含故障降流 */
};



// 最大允许放电功率表（无特殊说明，所有温度点必须有回滚）
static uint16 const dchgsocxvalue[] = {PERCENT_TO_SOC(9.9), PERCENT_TO_SOC(29.9), PERCENT_TO_SOC(59.9), PERCENT_TO_SOC(104)};
static sint16 const dchgtempyvalue[] = {TEMPERATURE_FROM_C(-21), TEMPERATURE_FROM_C(-10), TEMPERATURE_FROM_C(0), TEMPERATURE_FROM_C(10), TEMPERATURE_FROM_C(60)};
static sint16 const dchgtempaltyvalue[] = {TEMPERATURE_FROM_C(-22), TEMPERATURE_FROM_C(-11), TEMPERATURE_FROM_C(-1), TEMPERATURE_FROM_C(9), TEMPERATURE_FROM_C(55)};
static uint16 const dchgtableValue[] = {
    CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), // <= -21
    CURRENT_100MA_FROM_A(20U), CURRENT_100MA_FROM_A(50U), CURRENT_100MA_FROM_A(80U), CURRENT_100MA_FROM_A(80U), // <= -10
    CURRENT_100MA_FROM_A(40U), CURRENT_100MA_FROM_A(80U), CURRENT_100MA_FROM_A(100U), CURRENT_100MA_FROM_A(100U), // <= 0
    CURRENT_100MA_FROM_A(80U), CURRENT_100MA_FROM_A(100U), CURRENT_100MA_FROM_A(100U), CURRENT_100MA_FROM_A(100U), // <= 10
    CURRENT_100MA_FROM_A(100U), CURRENT_100MA_FROM_A(100U), CURRENT_100MA_FROM_A(100U), CURRENT_100MA_FROM_A(100U), // <= 60
};
static const PowerM_DiagnosisPercentMapType dchgdiag[] = {
    {DIAGNOSIS_ITEM_DCHG_LV, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_DCHG_HT, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_DCHG_LT, {60U, 50U, 10U, 0U}},
};
static const PowerM_ConfigParamType PowerMCurDchgContinueConfigTable = {
    ARRAY_SIZE(dchgsocxvalue), /**< 功率控制表X轴分隔数量 */
    ARRAY_SIZE(dchgtempyvalue), /**< 功率控制表Y轴分隔数量 */
    dchgsocxvalue, /**< 功率控制表X轴分隔表 */
    dchgtempyvalue, /**< 功率控制表Y轴分隔表 */
    dchgtempaltyvalue, /**< 功率控制表Y轴回滚分隔表 */
    dchgtableValue, /**< 各个分隔对应的值 */
    POWERM_YAXIS_USE_MIN, /**< 在yAxis和yAltAxis查询到的值取怎样取值，POWERM_YAXIS_USE_XX */
    0U, /**< 在y轴增加时使用Alt表 */
    POWERM_XAXIS_SUPPORT_BDIR, /**< X轴支持变动方向 */
    0U, /**< X轴区间线性插值 */
    (uint8)ARRAY_SIZE(dchgdiag), /**<  诊断故障功率百分比数量 */
    dchgdiag, /**<  断故障功率百分比表 */
    thisSocGet, /**< 获取X轴值的函数 */
    500U, /**< 功率输出时增加斜率时间参数 */
    CURRENT_100MA_FROM_A(100U), /**< 功率输出时增加斜率步进参数 */
    500U, /**< 功率输出时减小斜率时间参数 */
    CURRENT_100MA_FROM_A(20U), /**< 功率输出时减小斜率步进参数 */
    0U, /**< 充电末端X轴达到这个值时进入降流阶段 */
    NULL, /**< 降流链表 */
    NULL,  /**< 获取降流末端比较值函数 */
    NULL, /**< getChargeEndTable 获取降流链表，此函数配置后“chargeEndConfigs”和“getChargeEndCheckVal”将不起作用 */
    NULL, /**< 计算出目标值之后，使用改函数修改目标电流值，可用于复杂降流策略，包含故障降流 */
    NULL, /**< 在复位降流表时，只用该函数复位用户层数据，一般与hook函数配合使用 */
    0UL, /**< 温度改变引起查表区域变化时的确认时间，单位ms */
    NULL, /**< 计算出查表电流值之后，使用改函数修改查表电流值，可用于复杂降流策略，不包含故障降流 */
};



// 最大允许充电电功率表（无特殊说明，所有温度点必须有回滚）
static uint16 const chgcontinuesocxvalue[] = {PERCENT_TO_SOC(9.9), PERCENT_TO_SOC(29.9), PERCENT_TO_SOC(59.9), PERCENT_TO_SOC(104)};
static sint16 const chgcontinuetempyvalue[] = {TEMPERATURE_FROM_C(-10), TEMPERATURE_FROM_C(0), TEMPERATURE_FROM_C(10), TEMPERATURE_FROM_C(20), TEMPERATURE_FROM_C(50)};
static sint16 const chgcontinuetempaltyvalue[] = {TEMPERATURE_FROM_C(-11), TEMPERATURE_FROM_C(-1), TEMPERATURE_FROM_C(9), TEMPERATURE_FROM_C(19), TEMPERATURE_FROM_C(45)};
static uint16 const chgcontinuetableValue[] = {
    CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), // < -10
    CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), // < 0
    CURRENT_100MA_FROM_A(20U), CURRENT_100MA_FROM_A(20U), CURRENT_100MA_FROM_A(20U), CURRENT_100MA_FROM_A(20U), // < 10
    CURRENT_100MA_FROM_A(30U), CURRENT_100MA_FROM_A(30U), CURRENT_100MA_FROM_A(30U), CURRENT_100MA_FROM_A(30U), // < 20
    CURRENT_100MA_FROM_A(50U), CURRENT_100MA_FROM_A(50U), CURRENT_100MA_FROM_A(50U), CURRENT_100MA_FROM_A(50U), // < 50
};
static const PowerM_DiagnosisPercentMapType chgcontinuediag[] = {
    {DIAGNOSIS_ITEM_CHG_HV, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_CHG_HT, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_CHG_LT, {60U, 50U, 10U, 0U}},
};
static const PowerM_ConfigParamType PowerMCurChgContinueConfigTable = {
    ARRAY_SIZE(chgcontinuesocxvalue), /**< 功率控制表X轴分隔数量 */
    ARRAY_SIZE(chgcontinuetempyvalue), /**< 功率控制表Y轴分隔数量 */
    chgcontinuesocxvalue, /**< 功率控制表X轴分隔表 */
    chgcontinuetempyvalue, /**< 功率控制表Y轴分隔表 */
    chgcontinuetempaltyvalue, /**< 功率控制表Y轴回滚分隔表 */
    chgcontinuetableValue, /**< 各个分隔对应的值 */
    POWERM_YAXIS_USE_MIN, /**< 在yAxis和yAltAxis查询到的值取怎样取值，POWERM_YAXIS_USE_XX */
    0U, /**< 在y轴增加时使用Alt表 */
    POWERM_XAXIS_SUPPORT_BDIR, /**< X轴支持变动方向 */
    0U, /**< X轴区间线性插值 */
    (uint8)ARRAY_SIZE(chgcontinuediag), /**<  诊断故障功率百分比数量 */
    chgcontinuediag, /**<  断故障功率百分比表 */
    thisSocGet, /**< 获取X轴值的函数 */
    500U, /**< 功率输出时增加斜率时间参数 */
    CURRENT_100MA_FROM_A(200U), /**< 功率输出时增加斜率步进参数 */
    500U, /**< 功率输出时减小斜率时间参数 */
    CURRENT_100MA_FROM_A(20U), /**< 功率输出时减小斜率步进参数 */
    0U, /**< 充电末端X轴达到这个值时进入降流阶段 */
    NULL, /**< 降流链表 */
    NULL,  /**< 获取降流末端比较值函数 */
    NULL, /**< getChargeEndTable 获取降流链表，此函数配置后“chargeEndConfigs”和“getChargeEndCheckVal”将不起作用 */
    NULL, /**< 计算出目标值之后，使用改函数修改目标电流值，可用于复杂降流策略，包含故障降流 */
    NULL, /**< 在复位降流表时，只用该函数复位用户层数据，一般与hook函数配合使用 */
    0UL, /**< 温度改变引起查表区域变化时的确认时间，单位ms */
    NULL, /**< 计算出查表电流值之后，使用改函数修改查表电流值，可用于复杂降流策略，不包含故障降流 */
};

// 最大运行瞬时回馈功率表（无特殊说明，所有温度点必须有回滚）
static uint16 const dchgfbsocxvalue[] = {PERCENT_TO_SOC(9.9), PERCENT_TO_SOC(29.9), PERCENT_TO_SOC(59.9), PERCENT_TO_SOC(104)};
static sint16 const dchgfbtempyvalue[] = {TEMPERATURE_FROM_C(-10), TEMPERATURE_FROM_C(0), TEMPERATURE_FROM_C(10), TEMPERATURE_FROM_C(20), TEMPERATURE_FROM_C(30), TEMPERATURE_FROM_C(50)};
static sint16 const dchgfbtempaltyvalue[] = {TEMPERATURE_FROM_C(-11), TEMPERATURE_FROM_C(-1), TEMPERATURE_FROM_C(9), TEMPERATURE_FROM_C(19), TEMPERATURE_FROM_C(29), TEMPERATURE_FROM_C(45)};
static uint16 const dchgfbtableValue[] = {
    CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), // <= -10
    CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), CURRENT_100MA_FROM_A(10U), // <= 0
    CURRENT_100MA_FROM_A(150U), CURRENT_100MA_FROM_A(150U), CURRENT_100MA_FROM_A(100U), CURRENT_100MA_FROM_A(30U), // <= 10
    CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(150U), CURRENT_100MA_FROM_A(50U), // <= 20
    CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(80U), // <= 30
    CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(300U), CURRENT_100MA_FROM_A(100U), // <= 50
};
static const PowerM_DiagnosisPercentMapType dchgfbdiag[] = {
    {DIAGNOSIS_ITEM_DCHG_HV, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_DCHG_HT, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_DCHG_LT, {60U, 50U, 10U, 0U}},
};
static const PowerM_ConfigParamType PowerMCurDchgFeedbackConfigTable = {
    ARRAY_SIZE(dchgfbsocxvalue), /**< 功率控制表X轴分隔数量 */
    ARRAY_SIZE(dchgfbtempyvalue), /**< 功率控制表Y轴分隔数量 */
    dchgfbsocxvalue, /**< 功率控制表X轴分隔表 */
    dchgfbtempyvalue, /**< 功率控制表Y轴分隔表 */
    dchgfbtempaltyvalue, /**< 功率控制表Y轴回滚分隔表 */
    dchgfbtableValue, /**< 各个分隔对应的值 */
    POWERM_YAXIS_USE_MIN, /**< 在yAxis和yAltAxis查询到的值取怎样取值，POWERM_YAXIS_USE_XX */
    0U, /**< 在y轴增加时使用Alt表 */
    POWERM_XAXIS_SUPPORT_BDIR, /**< X轴支持变动方向 */
    0U, /**< X轴区间线性插值 */
    (uint8)ARRAY_SIZE(dchgfbdiag), /**<  诊断故障功率百分比数量 */
    dchgfbdiag, /**<  断故障功率百分比表 */
    thisSocGet, /**< 获取X轴值的函数 */
    500U, /**< 功率输出时增加斜率时间参数 */
    CURRENT_100MA_FROM_A(20U), /**< 功率输出时增加斜率步进参数 */
    500U, /**< 功率输出时减小斜率时间参数 */
    CURRENT_100MA_FROM_A(20U), /**< 功率输出时减小斜率步进参数 */
    0U, /**< 充电末端X轴达到这个值时进入降流阶段 */
    NULL, /**< 降流链表 */
    NULL,  /**< 获取降流末端比较值函数 */
    NULL, /**< getChargeEndTable 获取降流链表，此函数配置后“chargeEndConfigs”和“getChargeEndCheckVal”将不起作用 */
    NULL, /**< 计算出目标值之后，使用改函数修改目标电流值，可用于复杂降流策略，包含故障降流 */
    NULL, /**< 在复位降流表时，只用该函数复位用户层数据，一般与hook函数配合使用 */
    0UL, /**< 温度改变引起查表区域变化时的确认时间，单位ms */
    NULL, /**< 计算出查表电流值之后，使用改函数修改查表电流值，可用于复杂降流策略，不包含故障降流 */
};

// 最大允许瞬时放电功率表（无特殊说明，所有温度点必须有回滚）
static uint16 const dchgpeaksocxvalue[] = {PERCENT_TO_SOC(9.9), PERCENT_TO_SOC(29.9), PERCENT_TO_SOC(59.9), PERCENT_TO_SOC(104)};
static sint16 const dchgpeaktempyvalue[] = {TEMPERATURE_FROM_C(-21), TEMPERATURE_FROM_C(-10), TEMPERATURE_FROM_C(0), TEMPERATURE_FROM_C(10), TEMPERATURE_FROM_C(60)};
static sint16 const dchgpeaktempaltyvalue[] = {TEMPERATURE_FROM_C(-22), TEMPERATURE_FROM_C(-11), TEMPERATURE_FROM_C(-1), TEMPERATURE_FROM_C(9), TEMPERATURE_FROM_C(55)};
static uint16 const dchgpeaktableValue[] = {
    CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), // <= -21
    CURRENT_100MA_FROM_A(30U), CURRENT_100MA_FROM_A(60U), CURRENT_100MA_FROM_A(90U), CURRENT_100MA_FROM_A(100U), // <= -10
    CURRENT_100MA_FROM_A(50U), CURRENT_100MA_FROM_A(90U), CURRENT_100MA_FROM_A(120U), CURRENT_100MA_FROM_A(150U), // <= 0
    CURRENT_100MA_FROM_A(100U), CURRENT_100MA_FROM_A(150U), CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(250U), // <= 10
    CURRENT_100MA_FROM_A(150U), CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(300U), CURRENT_100MA_FROM_A(300U), // <= 20
    CURRENT_100MA_FROM_A(200U), CURRENT_100MA_FROM_A(300U), CURRENT_100MA_FROM_A(300U), CURRENT_100MA_FROM_A(300U), // <= 30
    CURRENT_100MA_FROM_A(300U), CURRENT_100MA_FROM_A(300U), CURRENT_100MA_FROM_A(300U), CURRENT_100MA_FROM_A(300U), // <= 60
};
static const PowerM_DiagnosisPercentMapType dchgpeakdiag[] = {
    {DIAGNOSIS_ITEM_DCHG_LV, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_DCHG_HT, {60U, 50U, 10U, 0U}},
    {DIAGNOSIS_ITEM_DCHG_LT, {60U, 50U, 10U, 0U}},
};
static const PowerM_ConfigParamType PowerMCurDchgPeakConfigTable = {
    ARRAY_SIZE(dchgpeaksocxvalue), /**< 功率控制表X轴分隔数量 */
    ARRAY_SIZE(dchgpeaktempyvalue), /**< 功率控制表Y轴分隔数量 */
    dchgpeaksocxvalue, /**< 功率控制表X轴分隔表 */
    dchgpeaktempyvalue, /**< 功率控制表Y轴分隔表 */
    dchgpeaktempaltyvalue, /**< 功率控制表Y轴回滚分隔表 */
    dchgpeaktableValue, /**< 各个分隔对应的值 */
    POWERM_YAXIS_USE_MIN, /**< 在yAxis和yAltAxis查询到的值取怎样取值，POWERM_YAXIS_USE_XX */
    0U, /**< 在y轴增加时使用Alt表 */
    POWERM_XAXIS_SUPPORT_BDIR, /**< X轴支持变动方向 */
    0U, /**< X轴区间线性插值 */
    (uint8)ARRAY_SIZE(dchgpeakdiag), /**<  诊断故障功率百分比数量 */
    dchgpeakdiag, /**<  断故障功率百分比表 */
    thisSocGet, /**< 获取X轴值的函数 */
    500U, /**< 功率输出时增加斜率时间参数 */
    CURRENT_100MA_FROM_A(200U), /**< 功率输出时增加斜率步进参数 */
    500U, /**< 功率输出时减小斜率时间参数 */
    CURRENT_100MA_FROM_A(20U), /**< 功率输出时减小斜率步进参数 */
    0U, /**< 充电末端X轴达到这个值时进入降流阶段 */
    NULL, /**< 降流链表 */
    NULL,  /**< 获取降流末端比较值函数 */
    NULL, /**< getChargeEndTable 获取降流链表，此函数配置后“chargeEndConfigs”和“getChargeEndCheckVal”将不起作用 */
    NULL, /**< 计算出目标值之后，使用改函数修改目标电流值，可用于复杂降流策略，包含故障降流 */
    NULL, /**< 在复位降流表时，只用该函数复位用户层数据，一般与hook函数配合使用 */
    0UL, /**< 温度改变引起查表区域变化时的确认时间，单位ms */
    NULL, /**< 计算出查表电流值之后，使用改函数修改查表电流值，可用于复杂降流策略，不包含故障降流 */
};

static Std_ReturnType thisExtCurXGet(uint16 *v) {
    (void)v;
    return E_NOT_OK;
}

// 扩展电流最大允许功率表（无特殊说明，所有温度点必须有回滚）
static uint16 const extcursocxvalue[] = {PERCENT_TO_SOC(104)};
static sint16 const extcurtempyvalue[] = {TEMPERATURE_FROM_C(-20), TEMPERATURE_FROM_C(60)};
static sint16 const extcurtempaltyvalue[] = {TEMPERATURE_FROM_C(-21), TEMPERATURE_FROM_C(55)};
static uint16 const extcurtableValue[] = {
    CURRENT_100MA_FROM_A(0U), CURRENT_100MA_FROM_A(0U), // <= -20
    CURRENT_100MA_FROM_A(300U), CURRENT_100MA_FROM_A(300U), // <= 60
};
static const PowerM_DiagnosisPercentMapType extcurdiag[] = {
    {DIAGNOSIS_ITEM_DCHG_LV, {60U, 50U, 10U, 0U}},
};
static const PowerM_ConfigParamType PowerMCurExtCurConfigTable = {
    ARRAY_SIZE(extcursocxvalue), /**< 功率控制表X轴分隔数量 */
    ARRAY_SIZE(extcurtempyvalue), /**< 功率控制表Y轴分隔数量 */
    extcursocxvalue, /**< 功率控制表X轴分隔表 */
    extcurtempyvalue, /**< 功率控制表Y轴分隔表 */
    extcurtempaltyvalue, /**< 功率控制表Y轴回滚分隔表 */
    extcurtableValue, /**< 各个分隔对应的值 */
    POWERM_YAXIS_USE_MIN, /**< 在yAxis和yAltAxis查询到的值取怎样取值，POWERM_YAXIS_USE_XX */
    0U, /**< 在y轴增加时使用Alt表 */
    POWERM_XAXIS_SUPPORT_BDIR, /**< X轴支持变动方向 */
    0U, /**< X轴区间线性插值 */
    (uint8)ARRAY_SIZE(extcurdiag), /**<  诊断故障功率百分比数量 */
    extcurdiag, /**<  断故障功率百分比表 */
    thisExtCurXGet, /**< 获取X轴值的函数 */
    500U, /**< 功率输出时增加斜率时间参数 */
    CURRENT_100MA_FROM_A(200U), /**< 功率输出时增加斜率步进参数 */
    500U, /**< 功率输出时减小斜率时间参数 */
    CURRENT_100MA_FROM_A(20U), /**< 功率输出时减小斜率步进参数 */
    0U, /**< 充电末端X轴达到这个值时进入降流阶段 */
    NULL, /**< 降流链表 */
    NULL,  /**< 获取降流末端比较值函数 */
    NULL, /**< getChargeEndTable 获取降流链表，此函数配置后“chargeEndConfigs”和“getChargeEndCheckVal”将不起作用 */
    NULL, /**< 计算出目标值之后，使用改函数修改目标电流值，可用于复杂降流策略，包含故障降流 */
    NULL, /**< 在复位降流表时，只用该函数复位用户层数据，一般与hook函数配合使用 */
    0UL, /**< 温度改变引起查表区域变化时的确认时间，单位ms */
    NULL, /**< 计算出查表电流值之后，使用改函数修改查表电流值，可用于复杂降流策略，不包含故障降流 */
};



const PowerM_CurrentTypeType PowerMChannelNum = POWERM_CUR_TYPE_NUM;
const PowerM_CurrentTypeType PowerMChannelCurrentDC = POWERM_CUR_CHARGE_DC;
const PowerM_CurrentTypeType PowerMChannelCurrentAC = POWERM_CUR_CHARGE_AC;
const PowerM_CurrentTypeType PowerMChannelCurrentHeater = POWERM_CUR_CHARGE_HEATER;
const PowerM_ConfigParamType *const PowerMConfigParamMaps[POWERM_CUR_TYPE_NUM] = {
    &PowerMCurDchgContinueConfigTable,
    &PowerMCurDchgPeakConfigTable,
    &PowerMCurDchgFeedbackConfigTable,
    &PowerMCurChgContinueConfigTable,
    &PowerMCurChgDcConfigTable,
    &PowerMCurChgAcConfigTable,
    &PowerMCurChgHeaterConfigTable,
    &PowerMCurExtCurConfigTable,
};

PowerM_InnerChannelDataType PowerMInnerChannelData[POWERM_CUR_TYPE_NUM];
