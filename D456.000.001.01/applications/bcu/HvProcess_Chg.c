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
#include "stdlib.h"
#include "Cpu.h"
#include "HvProcess_Dchg.h"
#include "HvProcess_Chg.h"
#include "ChargeConnectM.h"
#include "ChargeM.h"
#include "Statistic.h"
#include "DischargeM.h"
#include "RelayM.h"
#include "RelayM_Lcfg.h"
#include "ChargerComm.h"
#include "RuntimeM.h"
#include "ChargerCommUser_Messages.h"
#include "UserStrategy.h"
// #include "ChargeM_Cfg.h"
// #include "DischargeM_Cfg.h"

static HvProcess_ChgInnerDataType HvProcess_ChgInnerData;


void HvProcess_ChgInit(Async_LooperType *looper)
{
    (void)looper;
    HvProcess_ChgInnerData.State = HVPROCESS_CHG_START;
}

HvProcess_ChgStateType HvProcess_GetChgState(void)
{
    HvProcess_ChgStateType state;
    imask_t mask;

    Irq_Save(mask);
    state = HvProcess_ChgInnerData.State;
    Irq_Restore(mask);

    return state;
}

void HvProcess_SetChgState(HvProcess_ChgStateType state)
{
    imask_t mask;

    Irq_Save(mask);
    HvProcess_ChgInnerData.State = state;
    Irq_Restore(mask);
}

void HvProcess_ChgPoll(void)
{

}

static boolean HvProcess_ChgRelayIsNormal(void)
{

}

boolean HvProcess_ChgStateStartCond(void)
{
    /*
    >判断充电是否已连接；是否唤醒
        >判断放电是否在启动状态
            >判断继电器错误检查标志是否为FALSE；nowTime大于500ms>
                >继电器错误检查标志置TRUE
                >启动继电器粘连检测
            >判断继电器错误检查标志是否置TRUE
                >继电器诊断
                    >充电是否允许
    */
}

void HvProcess_ChgStateStartAction(void)
{
    //闭合充电继电器
}

boolean HvProcess_ChgIsFinishCond(void)
{
    //判断充电是否完成
}

void HvProcess_ChgFinishAction(void)
{
    //置继电器断开计时为系统时间；置充电完成标志为1
}

boolean HvProcess_ChgChargeConnectionCond(void)
{
    //判断充电是否连接
}

void HvProcess_ChgChargeConnectionAction(void)
{
    //继电器断开计时置为系统时间
}
static const Diagnosis_ItemType items[4U] = {
    DIAGNOSIS_ITEM_CHG_HTV,
    DIAGNOSIS_ITEM_CHG_HV,
    DIAGNOSIS_ITEM_VOLT_LINE,
    DIAGNOSIS_ITEM_TEMP_LINE
};

boolean HvProcess_ChgFaultCond(void)
{
    /*
    >判断时间是否大于300ms
        >赋值监测时间
    >判断是否有充电故障
        >排除指定诊断项序列后当前充电故障标志是否成立
        >判断充电是否结束
            >充电完成动作
        >判断延时是否大于delay
    >无充电故障
    */
}

void HvProcess_ChgFaultAction(void)
{
    //继电器断开计时置为系统时间
}

boolean HvProcess_ChgRelayOffDelayCond(void)
{
    /*
    >判断电流是否有效
    >判断是否延时结束
    >
    */
}

void HvProcess_ChgRelayOffDelayAction(void)
{
    //断开充电；继电器故障检查标志置FALSE
}

boolean HvProcess_ChgRestartAllowedCond(void)
{
    /*
    >总压置是否有效定义
        >判断后端电压是否高于前端电压90%（若高于90%会报粘连故障）,若低于90%，延时0ms
    >置lastTime
    >判断是都延时结束
    */
}
