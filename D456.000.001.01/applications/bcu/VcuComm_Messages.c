/**
 * \file VcuComm_messages.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 整车通信报文文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170316 |
 */
#include "stdlib.h"
#include "App_Types.h"
#include "Cpu.h"
#include "Det.h"
#include "VcuComm_Types.h"
#include "VcuComm_Messages.h"
#include "CurrentM.h"
#include "Statistic.h"
#include "Soc.h"
#include "Soh.h"
#include "Insu.h"
#include "ChargeConnectM.h"
#include "ChargerComm.h"
#include "HWDiagnosis.h"
#include "AppInfo.h"
#include "ParameterM.h"
#include "CellDataM.h"
#include "RelayM.h"
#include "RelayM_Lcfg.h"
#include "SystemConnection_Lcfg.h"
#include "ChargeM.h"
#include "PrechargeM.h"
#include "BalanceM.h"
#include "TemperatureM.h"
#include "UserStrategy.h"
#include "HvProcess_Dchg.h"
#include "PowerM.h"
#include "Datetime.h"
#include "DatetimeM.h"
#include "DischargeM.h"
#include "HvProcess_Chg.h"
#include "RelayM_Lcfg.h"
#include "ChargeConnectM.h"
#include "Statistic.h"

#if ( VCUCOMM_DEV_ERROR_DETECT == STD_ON )
#include "Modules.h"
#endif

#define VCUCOMM_MESSAGES_E_PARAM_INVALID_PTR            0U

#define VCUCOMM_MESSAGES_API_ID_ReceiveCbk              0U


#if ( VCUCOMM_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE_PTR(_ptr, _api) \
    if (_ptr == NULL) { \
        Det_ReportError(MODULE_ID_VCUCOMM_MESSAGES, 0U, _api, VCUCOMM_MESSAGES_E_PARAM_INVALID_PTR); \
        goto cleanup; \
    }
#else
#define VALIDATE_PTR(_ptr, _api)
#endif

#define VCUCOMM_CURRENT_OFFSET      (32000)
#define VCUCOMM_VOLT_4_DISPLAY(volt)    (VOLT_4_DISPLAY(volt) < 10000U ? VOLT_4_DISPLAY(volt) : 10000U)

VcuComm_MsgDataType VcuComm_MsgData;

// static uint16 VcuComm_bms2VcuCurrent(Current_CurrentType current);
static VcuComm_FaultCodeTableType VcuFaultCodeTabel[] = {
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_HV,                    {255U,0U,0U,0U,0U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_HV,                   {255U,1U,1U,1U,1U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_LV,                    {255U,2U,2U,2U,2U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_LV,                   {255U,3U,3U,3U,3U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_HTV,                   {255U,4U,4U,4U,4U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_HTV,                  {255U,5U,5U,5U,5U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_LTV,                   {255U,6U,6U,6U,6U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_LTV,                  {255U,7U,7U,7U,7U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_DV,                    {255U,10U,10U,10U,10U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_DV,                   {255U,11U,11U,11U,11U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_HT,                    {255U,12U,12U,12U,12U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_HT,                   {255U,13U,13U,13U,13U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_LT,                    {255U,14U,14U,14U,14U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_LT,                   {255U,15U,15U,15U,15U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_DT,                    {255U,16U,16U,16U,16U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_DT,                   {255U,17U,17U,17U,17U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DC_CHG_OC,                 {255U,18U,18U,18U,18U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_AC_CHG_OC,                 {255U,19U,19U,19U,19U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_FB_OC,                     {255U,20U,20U,20U,20U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_OC,                   {255U,21U,21U,21U,21U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_SP_OC,                     {255U,22U,22U,22U,22U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_HSOC,                      {255U,23U,23U,23U,23U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_LSOC,                      {255U,24U,24U,24U,24U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_LEAK,                      {255U,25U,25U,25U,25U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_HEAT_DT,               {255U,28U,28U,28U,28U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_HEAT_DT,              {255U,29U,29U,29U,29U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHG_HEAT_TIMEOUT,          {255U,30U,30U,30U,30U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DCHG_HEAT_TIMEOUT,         {255U,31U,31U,31U,31U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_VOLT_LINE,                 {255U,128U,128U,128U,128U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_TEMP_LINE,                 {255U,129U,129U,129U,129U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_INTER_COMM,                {255U,130U,130U,130U,130U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHGSCKTMP_DC_POSITIVE,     {255U,131U,131U,131U,131U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHGSCKTMP_DC_NEGATIVE,     {255U,132U,132U,132U,132U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHGSCKTMP_AC_AL,           {255U,133U,133U,133U,133U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHGSCKTMP_AC_BN,           {255U,134U,134U,134U,134U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHARGER_COMM,              {255U,136U,136U,136U,136U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_VCU_COMM,                  {255U,137U,137U,137U,137U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_FULL_CHARGE,               {255U,138U,138U,138U,138U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CHGSCKTMP_ABNORMAL,        {255U,139U,139U,139U,139U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_PRECHARGE_FAILURE,         {255U,140U,140U,140U,140U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_CURRENT_ABNORMAL,          {255U,141U,141U,141U,141U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_BMS_INIT_FAILURE,          {255U,142U,142U,142U,142U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_HVIL_ABNORMAL,             {255U,143U,143U,143U,143U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_RELAY_ABNORMAL,            {255U,144U,144U,144U,144U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_HEAT_FAULT,                {255U,145U,145U,145U,145U}},
    {(VcuComm_GetAlarmFuncPtr)Diagnosis_GetLevel, DIAGNOSIS_LEVEL_NONE, DIAGNOSIS_ITEM_DOUBLE_CHG_CONNECT_FAULT,  {255U,152U,152U,152U,152U}},
};

static uint8 VcuComm_GetFaultCode(void)
{

}


void VcuComm_MessageInit(Async_LooperType *looper)
{
    (void)looper;
    (void)VcuComm_SendIPduRegister(&VcuComm_IPduSendConfigInfo[0], VcuComm_SendIPduNum);
}

void VcuComm_GetStatusMsg_0x1E1(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x1E4(uint8 *buf, uint16 *Length) {

}
void VcuComm_GetStatusMsg_0x1F5_Excomm(uint8 *buf, uint16 *Length) {

}
void VcuComm_GetStatusMsg_0x1F5(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x1F3(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x211(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x352(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x353(uint8 *buf, uint16 *Length) {

}


void VcuComm_GetStatusMsg_0x354(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x355(uint8 *buf, uint16 *Length) {

}


void VcuComm_GetStatusMsg_0x356(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x357(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x3F3(uint8 *buf, uint16 *Length) {

}
/*
void VcuComm_GetStatusMsg_0x3F4(uint8 *buf, uint16 *Length) {
    static uint16 start_num = 0U;
    uint8 val8;
    uint16 index = 0U;

    WRITE_BT_UINT16(buf, index, start_num);
    for (; index < 8U && start_num < SYSTEM_POLE_TEMP_NUM; start_num++) {
        val8 = CellDataM_GetPoleTemperature(start_num);
        WRITE_BT_UINT8(buf, index, val8);
    }
    for (; index < 8U;) {
        WRITE_BT_UINT8(buf, index, 0xFFU);
    }
    if (start_num >= SYSTEM_POLE_TEMP_NUM) {
        start_num = 0U;
    }
    *Length = index;
}
*/


void VcuComm_GetStatusMsg_0x3F5(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x3F6(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x3FF(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x1F4(uint8 *buf, uint16 *Length)
{

}

//新增报文
void VcuComm_GetStatusMsg_0x201(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x360(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x361(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x358(uint8 *buf, uint16 *Length) {

}

void VcuComm_GetStatusMsg_0x202(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x203(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x204(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x205(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x206(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x207(uint8 *buf, uint16 *Length)
{

}

void VcuComm_GetStatusMsg_0x208(uint8 *buf, uint16 *Length) {

}


void VcuComm_GetMsgData0x1E1Cbk(uint8 *buf, uint16 *Length)
{
    sint16 sval;
    sint16 index = 0U, uval;
    //总压
    uval = Statistic_GetBcu100mvTotalVoltage();
    WRITE_LT_UINT16(buf, index, uval);
    //总电流
    sval = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);
    if (CurrentM_IsValidCurrent(sval))
    {
        uval = (uint16)(-sval);
    }
    else
    {
        uval = 0xFFFFU;
    }
    WRITE_LT_UINT16(buf, index, uval);
    //SOC
    WRITE_LT_UINT16(buf, index, Soc_Get());
    //报警码
    uval = VcuComm_GetFaultCode();
    WRITE_LT_UINT16(buf, index, uval);

    *Length = index;
}

void VcuComm_GetMsgData0x1E2Cbk(uint8 *buf, uint16 *Length)
{
    uint16 temp, index = 0U;
    //报警等级
    temp = Diagnosis_GetDiagLevelMax();
    WRITE_LT_UINT16(buf, index, temp);
    //最高单体电压
    temp = Statistic_GetBcuHv(0U);
    WRITE_LT_UINT16(buf, index, temp);
    //最高单体电压串号
    temp = (uint16)Statistic_GetBcuHvLogicIndex(0U) + 1U;
    WRITE_LT_UINT16(buf, index, temp);
    //最低单体电压
    temp = Statistic_GetBcuLv(0U);
    WRITE_LT_UINT16(buf, index, temp);

    *Length = index;
}

void VcuComm_GetMsgData0x1E3Cbk(uint8 *buf, uint16 *Length)
{
    uint16 temp, index = 0U;
    //最低单体电压电压串号
    temp = Statistic_GetBcuLvLogicIndex(0U) + 1;
    WRITE_LT_UINT16(buf, index, temp);
    //最高温度
    temp = Statistic_GetBcuHt(0U);
    WRITE_LT_UINT16(buf, index, temp);
    //最高温度编号
    temp = Statistic_GetBcuHtLogicIndex(0U) + 1;
    WRITE_LT_UINT16(buf, index, temp);
    //最低温度
    temp = Statistic_GetBcuLt(0U);
    WRITE_LT_UINT16(buf, index, temp);

    *Length = index;
}

void VcuComm_GetMsgData0x1E4Cbk(uint8 *buf, uint16 *Length)
{
    uint16 temp, index = 0U;
    //最低温度编号
    temp = Statistic_GetBcuLtLogicIndex(0U) + 1;
    WRITE_LT_UINT16(buf, index, temp);
    //正极绝缘阻值
    temp = Insu_GetPositive();
    WRITE_LT_UINT16(buf, index, temp);
    //负极绝缘阻值
    temp = Insu_GetNegative();
    WRITE_LT_UINT16(buf, index, temp);
    //系统状态
    if (CHARGECONNECTM_ISCONNECT())
    {
        temp = 1;
    }
    else
    {
        temp = 0;
    }
    WRITE_LT_UINT16(buf, index, temp);

    *Length = index;
}

void VcuComm_GetMsgData0x1E5Cbk(uint8 *buf, uint16 *Length)
{
    Charge_ChargeType type = ChargeConnectM_GetConnectType();
    uint16 val16 = 0U, uval = 0U, volt, index = 0U;
    sint16 current = PowerM_GetCurrent(POWERM_CUR_CHARGE_DC);
    volt = Power_GetChargeVoltage(type);
    if (CHARGECONNECTM_IS_CONNECT())
    {
        if (ChargeM_ChargeIsAllowed())
        {
            uval = (uint16)current;
            val16 = volt;
        }
    }
    //充电请求电压
    WRITE_LT_UINT16(buf, index, val16);
    //充电请求电流
    WRITE_LT_UINT16(buf, index, uval);
    //充电机输出电压
    uval = ChargerComm_GetChargerOutputHV();
    WRITE_LT_UINT16(buf, index, uval);
    //充电机输出电流
    current = ChargerComm_GetChargerOutputCurrent();
    uval = (uint16)current;
    WRITE_LT_UINT16(buf, index, uval);

    *Length = index;
}

void VcuComm_GetMsgData0x1E6Cbk(uint8 *buf, uint16 *Length)
{
    uint32 time;
    uint16 temp, index = 0;
    uint8 i;
    Diagnosis_ItemType item = DIAGNOSIS_ITEM_CHG_HV;
    //已充电时间
    time = Statistic_GetEclipseChargeTime();
    temp = (uint16)S_TO_MIN(time);
    WRITE_LT_UINT16(buf, index, temp);
    //故障标志1
    temp = 0U;
    for (i = 0U; i <= 15U; i++)
    {
        if (Diagnosis_GetLevel(item) >= 1U)//若有警报发生
        {
            temp |= (uint16)0x1U << i;
        }
        item = (Diagnosis_ItemType)((uint16)item + 1U);//下一item
    }
    WRITE_LT_UINT16(buf, index, temp);
    //故障标志2
    temp = 0U;
    for (i = 0; i <= 15U; i++)
    {
        if (Diagnosis_GetLevel(item) >= 1U)
        {
            temp |= (uint16)0x1U << i;
        }
        item = (Diagnosis_ItemType)((uint16)item + 1U);
    }
    WRITE_LT_UINT16(buf, index, temp);
    //故障标志3
    temp = 0U;
    for (i = 0; i <= 15U; i++)
    {
        if (Diagnosis_GetLevel(item) >= 1U)
        {
            temp |= (uint16)0x1U << i;
        }
        item = (Diagnosis_ItemType)((uint16)item + 1U);
        if (item > DIAGNOSIS_ITEM_SUPPLY_VOL_HIGH && item < DIAGNOSIS_ITEM_VOLT_LINE)
        {
            item = DIAGNOSIS_ITEM_VOLT_LINE;
        }
    }
    WRITE_LT_UINT16(buf, index, temp);

    *Length = index;
}

void VcuComm_GetMsgData0x1E7Cbk(uint8 *buf, uint16 *Length)
{
    uint16 temp = 0U, index = 0U;
    sint16 current;
    uint8 i;
    Diagnosis_ItemType item = DIAGNOSIS_ITEM_CHGSCKTMP_AC_BN;
    //故障标志4
    for (i = 0; i <= 15U; i++)
    {
        if (Diagnosis_GetLevel(item) >= 1U)
        {
            temp = (uint16)0x1U << i;
        }
        item = (Diagnosis_ItemType)((uint16)item + 1U);
    }
    WRITE_LT_UINT16(buf, index, temp);
    //故障标志5
    temp = 0U;
    for (i = 0; i <= 15U; i++)
    {
        if (Diagnosis_GetLevel(item) >= 1U)
        {
            temp |= (uint16)0x1U << i;
        }
        item = (Diagnosis_ItemType)((uint16)item + 1U);
        if (item > DIAGNOSIS_ITEM_CRASH_FAULT)
        {
            break;
        }
    }
    WRITE_LT_UINT16(buf, index, temp);
    //电池组总电流（无符号）
    current = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);
    temp = (uint16)abs(current);
    WRITE_LT_UINT16(buf, index, temp);
    //预留
    WRITE_LT_UINT16(buf, index, 0xFFFFU);

    *Length = index;
}



void VcuComm_ReceiveCbk(uint8 *Buffer, uint16 Length)
{
    VALIDATE_PTR(Buffer, VCUCOMM_MESSAGES_API_ID_ReceiveCbk);

    VcuComm_SetCommunicationStatus(TRUE);
    VcuComm_ClrCommAbortMessageFlag((uint16)VCUCOMM_RX_IPDU_MSG_0x12345678);
    (void)Buffer;
    (void)Length;

#if ( VCUCOMM_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void VcuComm_RecTimeoutCbk(void)
{
    VcuComm_MsgData.PowerCommand = VCUCOMM_POWER_OFF;
    VcuComm_SetCommunicationStatus(FALSE);
    VcuComm_SetCommAbortMessageFlag((uint16)VCUCOMM_RX_IPDU_MSG_0x12345678);
}



// Condition Check function define
Std_ReturnType VcuComm_SendConditionCheck(uint16 IPdu)
{
    Std_ReturnType res = E_NOT_OK;

    (void)IPdu;
    if (VcuComm_GetCurrentRecStage() == (uint16)VCUCOMM_STAGE_STAGE1)
    {
        res = E_OK;
    }
    return res;
}

Std_ReturnType VcuComm_RecConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;
    uint16 stage;

    stage = VcuComm_GetCurrentRecStage();
    if (stage == (uint16)VCUCOMM_STAGE_STAGE1)
    {
        res = E_OK;
    }
    return res;
}

// static uint16 VcuComm_bms2VcuCurrent(Current_CurrentType current)
// {
//     uint16 vcu_current;
//     Current_CurrentType cur_offset = VCUCOMM_CURRENT_OFFSET;

//     if (!CurrentM_IsValidCurrent(current))
//     {
//         current = 0;
//     }
//     if (current < (-1) * cur_offset)
//     {
//         vcu_current = 0U;
//     }
//     else if (current > cur_offset)
//     {
//         vcu_current = (uint16)cur_offset * 2U;
//     }
//     else
//     {
//         vcu_current = (uint16)current + (uint16)cur_offset;
//     }
//     return vcu_current;
// }

