/**
 * \file ChargerCommUser.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 自定义充电机通信文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */

#include "Det.h"
#include "ChargeM.h"
#include "ChargerCommUser.h"
#include "ChargerComm.h"
#include "ChargerComm_LCfg.h"
#include "ChargerCommUser_Messages.h"
#include "PowerM.h"
#if ( CHARGERCOMMUSER_DEV_ERROR_DETECT == STD_ON )
#include "Modules.h"
#endif

#define CHARGERCOMMUSER_E_PARAM_INVALID_PTR         0U

#define CHARGERCOMMUSER_API_ID_Init                 0U
#define CHARGERCOMMUSER_API_ID_StartRecStageTimeout 1U


#if ( CHARGERCOMMUSER_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE_PTR(_ptr, _api) \
    if (_ptr == NULL) { \
        Det_ReportError(MODULE_ID_CHARGERCOMM_USER, 0U, _api, CHARGERCOMMUSER_E_PARAM_INVALID_PTR); \
        goto cleanup; \
    }
#else
#define VALIDATE_PTR(_ptr, _api)
#endif


ChargerCommUser_InnerDataType ChargerCommUser_innerData;


static void ChargerCommUser_ReadConfigPara(void);


void ChargerCommUser_Init(void)
{
    ChargerCommUser_innerData.startFlag = FALSE;
    ChargerCommUser_innerData.chargeTypeMask = 0U;
    if (ChargerComm_ConfigInfo.AC_Protocol == CHARGERCOMM_PROTOCOL_USER ||
        ChargerComm_ConfigInfo.DC_Protocol == CHARGERCOMM_PROTOCOL_USER)
    {
        ChargerCommUser_ReadConfigPara();
        ChargerCommUser_MessageInit();
    }
}

static void ChargerCommUser_ReadConfigPara(void)
{
    ChargerComm_ProtocolType protocol;

    if (ChargeM_ConfigInfo.AC_Para.enable == STD_ON)
    {
        protocol = ChargerComm_ConfigInfo.AC_Protocol;
        if (protocol == CHARGERCOMM_PROTOCOL_USER)
        {
            ChargerCommUser_SetChargeType(CHARGE_TYPE_AC);
        }
    }
    if (ChargeM_ConfigInfo.DC_Para.enable == STD_ON)
    {
        protocol = ChargerComm_ConfigInfo.DC_Protocol;
        if (protocol == CHARGERCOMM_PROTOCOL_USER)
        {
            ChargerCommUser_SetChargeType(CHARGE_TYPE_DC);
        }
    }
}

void ChargerCommUser_CommStart(void)
{
    Charge_ChargeType type;
    ChargerComm_StageType stage = ChargerComm_GetCurrentRecStage();

    ChargerCommUser_UpdateCurrentChargeType();
    type = ChargerCommUser_GetCurrentChargeType();
    if (ChargerCommUser_innerData.startFlag == TRUE &&
        stage == CHARGERCOMM_STAGE_IDLE &&
        type != CHARGE_TYPE_NONE)
    {
        if (type == CHARGE_TYPE_DC)
        {
            PowerM_Reset(POWERM_CUR_CHARGE_DC);
        }
        else
        {
            PowerM_Reset(POWERM_CUR_CHARGE_AC);
        }
        ChargerComm_SetChargeType(type);
        ChargerComm_InitChargeVoltAndCurrent();
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_USER_TC);
    }
}

void ChargerCommUser_CommStop(void)
{
    imask_t mask;
    Charge_ChargeType currentType;
    ChargerComm_StageType stage = ChargerComm_GetCurrentRecStage();

    if (stage >= CHARGERCOMM_STAGE_USER_START && stage <= CHARGERCOMM_STAGE_USER_STOP)
    {
        Irq_Save(mask);
        ChargerComm_ClrChargeStatus();
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_IDLE);
        Irq_Restore(mask);
        currentType = ChargerCommUser_GetCurrentChargeType();
        if (currentType == CHARGE_TYPE_DC)
        {
            PowerM_Reset(POWERM_CUR_CHARGE_DC);
        }
        else if (currentType == CHARGE_TYPE_AC)
        {
            PowerM_Reset(POWERM_CUR_CHARGE_AC);
        }
        else
        {
        }
        ChargerCommUser_SetCurrentChargeType(CHARGE_TYPE_NONE);
    }
}

void ChargerCommUser_SetCurrentChargeType(Charge_ChargeType type)
{
    imask_t mask;

    Irq_Save(mask);
    ChargerCommUser_innerData.currentChargeType = type;
    Irq_Restore(mask);
}

Charge_ChargeType ChargerCommUser_GetCurrentChargeType(void)
{
    imask_t mask;
    Charge_ChargeType type;

    Irq_Save(mask);
    type = ChargerCommUser_innerData.currentChargeType;
    Irq_Restore(mask);
    return type;
}

void ChargerCommUser_UpdateCurrentChargeType(void)
{
    uint8 flag = 1U;
    if (ChargerCommUser_GetCurrentChargeType() == CHARGE_TYPE_NONE)
    {
        if (ChargerCommUser_ChargeTypeIsOn(CHARGE_TYPE_AC) == TRUE)
        {
            if (ChargeConnectM_GetConnectStatus(CHARGE_TYPE_AC) == E_OK)
            {
                ChargerCommUser_SetCurrentChargeType(CHARGE_TYPE_AC);
                flag = 0U;
            }
        }
        if (ChargerCommUser_ChargeTypeIsOn(CHARGE_TYPE_DC) == TRUE)
        {
            if (ChargeConnectM_GetConnectStatus(CHARGE_TYPE_DC) == E_OK)
            {
                ChargerCommUser_SetCurrentChargeType(CHARGE_TYPE_DC);
                flag = 0U;
            }
        }
        if (flag != 0U)
        {
            ChargerCommUser_SetCurrentChargeType(CHARGE_TYPE_NONE);
        }
    }
}

void ChargerCommUser_ChargerEnable(void)
{
    imask_t mask;

    Irq_Save(mask);
    ChargerCommUser_innerData.startFlag = TRUE;
    Irq_Restore(mask);

    ChargerCommUser_CommStart();
}

void ChargerCommUser_ChargerDisable(void)
{
    imask_t mask;

    Irq_Save(mask);
    ChargerCommUser_innerData.startFlag = FALSE;
    Irq_Restore(mask);

    ChargerCommUser_CommStop();
}

uint8 ChargerCommUser_CommIsEnable(void)
{
    return ChargerCommUser_innerData.startFlag;
}

void ChargerCommUser_SetCommunication(uint8 flag)
{
    ChargerCommUser_innerData.communication = flag;
}

uint8 ChargerCommUser_IsCommunication(void)
{
    return ChargerCommUser_innerData.communication;
}

void ChargerCommUser_SetChargeType(Charge_ChargeType type)
{
    imask_t mask;

    Irq_Save(mask);
    ChargerCommUser_innerData.chargeTypeMask |= ((uint16)1U << type);
    Irq_Restore(mask);
}

boolean ChargerCommUser_ChargeTypeIsOn(Charge_ChargeType type)
{
    boolean flag = FALSE;
    uint16 typeMask;
    imask_t mask;

    if (type != CHARGE_TYPE_NONE)
    {
        Irq_Save(mask);
        typeMask = ChargerCommUser_innerData.chargeTypeMask;
        Irq_Restore(mask);

        if (typeMask & ((uint16)1U << type))
        {
            flag = TRUE;
        }
    }
    return flag;
}

boolean ChargerCommUser_ChargeTypeIsNone(void)
{
    boolean flag = FALSE;
    uint16 typeMask;
    imask_t mask;

    Irq_Save(mask);
    typeMask = ChargerCommUser_innerData.chargeTypeMask;
    Irq_Restore(mask);

    if (typeMask == 0U)
    {
        flag = TRUE;
    }
    return flag;
}

void ChargerCommUser_StartRecStageTimeout(uint8 channel, ChargerComm_StageType currentStage)
{
    uint16 timeout;
    const ChargerComm_RecIPduCfgType* cfg;
    ChargerComm_RecAsyncEventType *recEvent;

    if (channel < CHARGERCOMM_MONITOR_REC_MSG_NUM_PER_STAGE &&
        currentStage >= CHARGERCOMM_STAGE_USER_START &&
        currentStage <= CHARGERCOMM_STAGE_USER_STOP)
    {
        cfg = ChargerComm_GetRecStageCfg(currentStage);
        recEvent = ChargerComm_GetRecAsyncEventPtr();
        VALIDATE_PTR(cfg, CHARGERCOMMUSER_API_ID_StartRecStageTimeout);
        VALIDATE_PTR(recEvent, CHARGERCOMMUSER_API_ID_StartRecStageTimeout);

        switch(currentStage)
        {
            case CHARGERCOMM_STAGE_IDLE:
            case CHARGERCOMM_STAGE_GB_START:
            case CHARGERCOMM_STAGE_GB_CHM_TO_CRM:
            case CHARGERCOMM_STAGE_GB_CRM:
            case CHARGERCOMM_STAGE_GB_RECOMM_CRM:
            case CHARGERCOMM_STAGE_GB_CRM_AA:
            case CHARGERCOMM_STAGE_GB_CTS_CML:
            case CHARGERCOMM_STAGE_GB_CRO:
            case CHARGERCOMM_STAGE_GB_CCS:
            case CHARGERCOMM_STAGE_GB_CST_CSD:
            case CHARGERCOMM_STAGE_GB_CEM:
            case CHARGERCOMM_STAGE_GB_FULLCHARGE:
                break;
            case CHARGERCOMM_STAGE_USER_START:
                if (channel < cfg->IPduNum)
                {
                    if (cfg->IPduInfo[channel].TimeoutFunc)
                    {
                        timeout = cfg->IPduInfo[channel].TimeoutFunc();
                    }
                    else
                    {
                        timeout = cfg->IPduInfo[channel].Timeout;
                    }
                }
                else
                {
                    timeout = CHARGERCOMMUSER_REC_TIMEOUT_DEFAULT;
                }
                Async_EventSetTimeout(&recEvent[channel].event, timeout);
                break;
            case CHARGERCOMM_STAGE_MAX:
                break;
            default:
                break;
        }
    }
#if ( CHARGERCOMMUSER_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Current_CurrentType ChargerCommUser_GetGBSignalCurrentMax(void)
{
    Current_CurrentType currentMax;
    uint8 type = ChargerCommUser_innerData.currentChargeType;

    currentMax = ChargeConnectM_GetChargeCurrentMax(type);
    if (currentMax < 0)
    {
        currentMax = 0x7FFF;
    }

    return currentMax;
}
