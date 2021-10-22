/**
 * \file UserStrategy.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 用户策略定义文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170322 |
 */
#include <string.h>
#include <stdlib.h>
#include "UserStrategy.h"
#include "Statistic.h"
#include "Util.h"
#include "Hv.h"
#include "RelayM.h"
#include "PowerM.h"
#include "TemperatureM.h"
#include "ChargeConnectM.h"
#include "SocCalib_Cbk.h"
#include "ChargeM.h"
#include "RelayM_Lcfg.h"
#include "Diagnosis.h"

#if ( USERSTRATEGY_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE_PTR(_ptr, _api) \
    if(_ptr == NULL) { \
        Det_ReportError(MODULE_ID_USERSTRATEGY, 0U, _api, USERSTRATEGY_E_PARAM_INVALID_PTR); \
        goto cleanup; \
    }
#else
#define VALIDATE_RPTR(_ptr, _api)
#endif

UserStrategy_InnerDataType UserStrategy_innerData;


static Async_EvnetCbkReturnType UserStrategy_Poll(Async_EventType *event, uint8 byWhat);
static void safeCurrentCheck(void);
static void Buzzer_Alarm_Check(void);

void UserStrategy_Init(Async_LooperType *looper)
{
    // (void)RelayM_Control(RELAYM_FN_HMI, RELAYM_CONTROL_ON);
    UserStrategy_innerData.currentIsAllowToPowerOff = TRUE;
    if (looper != NULL)
    {
        UserCurrentSensor_Init(looper);
        if (E_OK == Async_EventInit(&UserStrategy_innerData.event, looper, UserStrategy_Poll, 100UL))
        {
            (void)Async_EventRegisterToLooper(&UserStrategy_innerData.event);
        }
    }
}

static void UserStrategy_AutoLostPower(void)
{
    Current_CurrentType current;
    RuntimeM_RunModeType mode;
    static uint32 lastTime = 0U;
    uint32 nowTime = OSTimeGet();
    uint32 delay = 12UL * 60UL * 60000UL;

    mode = RuntimeM_GetMode();
    if (mode == RUNTIMEM_RUNMODE_CALIBRATE || mode == RUNTIMEM_RUNMODE_NORMAL)
    {
        current = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);
        if (CurrentM_IsValidCurrent(current))
        {
            current = abs(current);
            if (current <= CURRENT_S_100MA_FROM_A(1))
            {
                if (MS_GET_INTERNAL(lastTime, nowTime) >= delay)
                {
                    lastTime = nowTime;
                    (void)RelayM_Control(RELAYM_FN_POSITIVE_MAIN, RELAYM_CONTROL_OFF);
                    (void)RelayM_Control(RELAYM_FN_CHARGE, RELAYM_CONTROL_OFF);
                    (void)RelayM_Control(RELAYM_FN_PRECHARGE, RELAYM_CONTROL_OFF);
                    // (void)RelayM_Control(RELAYM_FN_HMI, RELAYM_CONTROL_OFF);
                    (void)RelayM_Control(RELAYM_FN_BUZZER, RELAYM_CONTROL_OFF);
                    RuntimeM_RequestPowerDown();
                }
            }
            else
            {
                lastTime = nowTime;
            }
        }
        else
        {
            lastTime = nowTime;
        }
    }
    else
    {
        lastTime = nowTime;
    }
}

static void UserStrategy_ResetToOTA(void)
{
    Current_CurrentType current;

    if (RuntimeM_HasOtaRequest())
    {
        current = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);
        if (CurrentM_IsValidCurrent(current))
        {
            if (abs(current) < CURRENT_S_100MA_FROM_A(5))
            {
                (void)RuntimeM_RequestToDtuMode();
            }
        }
    }
}

static Async_EvnetCbkReturnType UserStrategy_Poll(Async_EventType *event, uint8 byWhat)
{
    (void)event;
    (void)byWhat;

    safeCurrentCheck();
    UserStrategy_AutoLostPower();
    Buzzer_Alarm_Check();
    UserStrategy_ResetToOTA();
    return ASYNC_EVENT_CBK_RETURN_OK;
}

static void safeCurrentCheck(void)
{
    boolean flag = FALSE;
    uint32 nowTick;
    Current_CurrentType current = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);

    if (!CURRENT_IS_VALID(current)) {
        flag = TRUE;
    }
    else if ((uint16)abs(current) < CURRENT_100MA_FROM_A(3U)) {
        flag = TRUE;
    }
    else {
    }

    nowTick = OSTimeGet();
    if (flag) {
        if (UserStrategy_innerData.powerOffTick == 0UL) {
            UserStrategy_innerData.powerOffTick = nowTick;
        }
        else {
            if (MS_GET_INTERNAL(UserStrategy_innerData.powerOffTick, nowTick) >= 1000UL) {
                UserStrategy_innerData.currentIsAllowToPowerOff = TRUE;
            }
        }
    }
    else {
        UserStrategy_innerData.powerOffTick = 0UL;
        UserStrategy_innerData.currentIsAllowToPowerOff = FALSE;
    }
}

//此函数底层仅调用一次，需要循环调用请在UserStrategy_SaftyOff函数中实现
boolean UserStrategy_IsSafeToOff(void) {
    boolean res = FALSE;

    if (UserStrategy_innerData.currentIsAllowToPowerOff) {
        res = TRUE;
    }
    return res;
}

boolean UserStartegy_ChargeIsAllow(void)
{
    boolean res = FALSE;

    if (Diagnosis_StartDiagIsFinish())
    {
        res = TRUE;
    }
    return res;
}

App_Tv100mvType UserStrategy_GetChargeVoltMax(void)
{
    App_Tv100mvType volt;
    Charge_ChargeType type = ChargeConnectM_GetConnectType();

    volt = PowerM_GetChargeVoltage(type);

    return volt;
}

Current_CurrentType UserStrategy_GetChargeCurrentMax(void)
{
    Current_CurrentType current;
    Charge_ChargeType type = ChargeConnectM_GetConnectType();

    if (TemperatureM_GetHeatState() != TEMPERATUREM_HEAT_STATE_NONE)
    {
        current = PowerM_GetCurrent(POWERM_CUR_CHARGE_HEATER);
    }
    else if (type == CHARGE_TYPE_DC)
    {
        current = PowerM_GetCurrent(POWERM_CUR_CHARGE_DC);
    }
    else
    {
        current = PowerM_GetCurrent(POWERM_CUR_CHARGE_AC);
    }
    return current;
}

App_Tv100mvType UserStrategy_GetDC2ChargeVoltMax(void)
{
    App_Tv100mvType volt;

    volt = PowerM_GetChargeVoltage(CHARGE_TYPE_DC);

    return volt;
}

Current_CurrentType UserStrategy_GetDC2ChargeCurrentMax(void)
{
    Current_CurrentType current;

    if (TemperatureM_GetHeatState() != TEMPERATUREM_HEAT_STATE_NONE)
    {
        current = PowerM_GetCurrent(POWERM_CUR_CHARGE_HEATER);
    }
    else
    {
        current = PowerM_GetCurrent(POWERM_CUR_CHARGE_DC);
    }
    return current;
}

boolean UserStartegy_GBChargeRelayIsReady(RelayM_FunctionType relayType)
{
    boolean res = FALSE;

    if (relayType == RELAYM_FN_NONE)
    {
        res = TRUE;
    }
    else if (RelayM_FunctionRelayIsEnable(relayType) == E_NOT_OK)
    {
        res = TRUE;
    }
    else if (RelayM_GetActualStatus(relayType) == RELAYM_ACTUAL_ON)
    {
        res = TRUE;
    }
    else
    {
    }
    return res;
}

App_Tv100mvType UserStrategy_GetMcuVoltage(void)
{
    return HV_GetVoltage(HV_CHANNEL_HV1);
}

uint16 UserStrategy_IsDiagHvilAbnormal(void)
{
    return 0U;
}

void UserStrategy_CheckSRS(const PwmCapture_DataType *dat)
{
    (void)dat;
    // uint8 i;
    // uint32 lowtime = PwmCapture_GetLowTime(dat);
    // if (lowtime >= 1800 && lowtime <= 2200) {
    //     ChargeM_SetOthersFaultDchargeCtl(, DIS);
    //     DischargeM_SetOthersFaultDchargeCtl();
    //     RelayM_ForceControl(RELAYM_FN_NEGTIVE_MAIN, RELAYM_FORCE_OFF); //优化断开主负
    //     for (i = 0; i < RELAYM_FN_NUM; ++i) {
    //         RelayM_ForceControl(i, RELAYM_FORCE_OFF);
    //     }
    // }
}

boolean UserStrategy_SaftyOff(RuntimeM_SignalType signal) {
    (void) signal;
    return UserStrategy_IsSafeToOff();
}

/**< 建议由连接到未连接变化时增加适当延时，保证连接状态不会突变而导致异常 */
Std_ReturnType UserStrategy_ACConnected(void)
{
    return E_NOT_OK;
}

/**< 建议由连接到未连接变化时增加适当延时，保证连接状态不会突变而导致异常 */
Std_ReturnType UserStrategy_DCConnected(void)
{
    return E_NOT_OK;
}

Std_ReturnType UserStrategy_DC2Connected(void)
{
    return E_NOT_OK;
}

uint16 UserStrategy_GetCrashFault(void)
{
    return 0U;
}

void UserStrategy_FullChargeHook(void)
{
    SocDiagCalib_FullCalibCbk(DIAGNOSIS_ITEM_FULL_CHARGE, DIAGNOSIS_LEVEL_FIRST, DIAGNOSIS_EVENT_ASSERT);
    ChargeM_DiagnosisCtlDisableEventCbk(DIAGNOSIS_ITEM_FULL_CHARGE, DIAGNOSIS_LEVEL_FIRST, DIAGNOSIS_EVENT_ASSERT);
}

void UserStrategy_FullChargeReleaseHook(void)
{
    SocDiagCalib_FullCalibRelCbk(DIAGNOSIS_ITEM_FULL_CHARGE, DIAGNOSIS_LEVEL_FIRST, DIAGNOSIS_EVENT_DEASSERT);
    ChargeM_DiagnosisCtlEnableEventCbk(DIAGNOSIS_ITEM_FULL_CHARGE, DIAGNOSIS_LEVEL_FIRST, DIAGNOSIS_EVENT_DEASSERT);
}
boolean UserStrategy_RemoteBalanceConditionCheck(void){
    uint8 ret = TRUE;
    return ret;
}

static void Buzzer_Alarm_Check(void)
{
    uint8 AlarmLevel;
    uint32 nowTime = OSTimeGet();
    static uint32 onTime = 0U, offTime = 0U;
    static uint32 lastTime = 0U;
    static boolean is_on = FALSE;
    // uint8 i;

    // for (i = 0U; i < (uint8)ARRAY_SIZE(Alarm_type_Lever2); i ++)
    // {
    //     if (Diagnosis_GetLevel(Alarm_type_Lever2[i].diagItemType) >= Alarm_type_Lever2[i].level)
    //     {
    //         AlarmLevel = 2U;
    //         break;
    //     }
    // }
    // if (!AlarmLevel)
    // {
    //     for (i = 0U; i < (uint8)ARRAY_SIZE(Alarm_type_Lever1); i ++)
    //     {
    //         if (Diagnosis_GetLevel(Alarm_type_Lever1[i].diagItemType) >= Alarm_type_Lever1[i].level)
    //         {
    //             AlarmLevel = 1U;
    //             break;
    //         }
    //     }
    // }
    AlarmLevel = Diagnosis_GetDiagLevelMax();
    if (AlarmLevel >= 3U)
    {
        if (is_on)
        {
            if (MS_GET_INTERNAL(lastTime, nowTime) >= onTime)
            {
                is_on = FALSE;
                lastTime = nowTime;
                (void)RelayM_Control(RELAYM_FN_BUZZER, RELAYM_CONTROL_OFF);
            }
        }
        else
        {
            if (MS_GET_INTERNAL(lastTime, nowTime) >= offTime)
            {
                is_on = TRUE;
                lastTime = nowTime;
                (void)RelayM_Control(RELAYM_FN_BUZZER, RELAYM_CONTROL_ON);
            }
        }
        if (AlarmLevel >= 3U)
        {
            onTime = USERSTRATEGY_BUZZER_LEVEL2_ON_TIME;
            offTime = USERSTRATEGY_BUZZER_LEVEL2_OFF_TIME;
        }
    }
    else
    {
        is_on = FALSE;
        lastTime = nowTime;
        onTime = 0U;
        offTime = 0U;
        (void)RelayM_Control(RELAYM_FN_BUZZER, RELAYM_CONTROL_OFF);
    }
}


