/**
 * \file HvProcess_Chg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压充电流程控制文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170320 |
 */
#include "LimitProtect.h"
#include "CellDataM.h"
#include "Statistic.h"
#include "RelayM.h"
#include "RelayM_Lcfg.h"
#include "BatteryInfo.h"


static LimitProtect_InnerDataType LimitProtect_innerData;

static Async_EvnetCbkReturnType LimitProtect_Poll(Async_EventType *event, uint8 byWhat);
static void limitProtectCheck(void);

void LimitProtect_Init(Async_LooperType *looper)
{
    LimitProtect_innerData.is_protect = FALSE;
    if (looper != NULL)
    {
        if (E_OK == Async_EventInit(&LimitProtect_innerData.event, looper, LimitProtect_Poll, 100UL))
        {
            (void)Async_EventRegisterToLooper(&LimitProtect_innerData.event);
        }
    }
}

static Async_EvnetCbkReturnType LimitProtect_Poll(Async_EventType *event, uint8 byWhat)
{
    (void)byWhat;
    (void)event;

    limitProtectCheck();

    return ASYNC_EVENT_CBK_RETURN_OK;
}

static void limitProtectCheck(void)
{
    uint8 i, para_is_valid;
    boolean is_on = FALSE;
    App_VoltageType volt;
    App_TemperatureType temperature;
    static uint32 lastTick = 0UL;
    uint32 nowTick = OSTimeGet();

    volt = Statistic_GetBcuHv(0U);
    para_is_valid = CellDataM_VoltageIsValid(BatteryInfo_BaseConfigInfo.HighVoltLimit);
    if (CellDataM_VoltageIsValid(volt) && para_is_valid && volt >= BatteryInfo_BaseConfigInfo.HighVoltLimit)
    {
        is_on = TRUE;
    }
    else
    {
        volt = Statistic_GetBcuLv(0U);
        para_is_valid = CellDataM_VoltageIsValid(BatteryInfo_BaseConfigInfo.LowVoltLimit);
        if (CellDataM_VoltageIsValid(volt) && para_is_valid && volt <= BatteryInfo_BaseConfigInfo.LowVoltLimit)
        {
            is_on = TRUE;
        }
        else
        {
            temperature = Statistic_GetBcuHt(0U);
            para_is_valid = CellDataM_TemperatureIsValid((uint16)BatteryInfo_BaseConfigInfo.HighTempLimit);
            if (CellDataM_TemperatureIsValid((uint16)temperature) && para_is_valid && temperature >= (uint8)BatteryInfo_BaseConfigInfo.HighTempLimit)
            {
                is_on = TRUE;
            }
        }
    }
    if (is_on)
    {
        if (MS_GET_INTERNAL(lastTick, nowTick) >= BatteryInfo_BaseConfigInfo.LimitProtectDelay)
        {
            LimitProtect_innerData.is_protect = TRUE;
            for (i = 0U; i < RELAYM_FN_NUM; ++i)
            {
                HLSS_Force(RelayM_GetDriveHSSChannel(i), HLSS_FORCE_OFF);
            }
            lastTick = nowTick;
        }
    }
    else
    {
        lastTick = nowTick;
    }
}

boolean LimitProtect_IsProtected(void)
{
    return LimitProtect_innerData.is_protect;
}
