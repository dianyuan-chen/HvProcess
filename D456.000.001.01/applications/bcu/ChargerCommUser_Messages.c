/**
 * \file ChargerCommUser_messages.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 自定义充电机通信报文文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170315 |
 */
#include "App_Types.h"
#include "Cpu.h"
#include "Det.h"
#include "ChargerCommUser_Messages.h"
#include "ChargerComm.h"
#include "ChargeM.h"
#include "PowerM.h"
#include "TemperatureM.h"
#include "ChargerComm_LCfg.h"
#include "UserStrategy.h"
#include "EL.h"
#include "Statistic.h"
#include "Soc.h"
// #include "HvProcess_Chg.h"

#define CHARGERCOMMUSER_MESSAGES_E_PARAM_INVALID_PTR         0U

#define CHARGERCOMMUSER_MESSAGES_API_ID_ReceiveTCCbk         0U
#define CHARGERCOMMUSER_MESSAGES_API_ID_GetTCDataCbk         1U


#if ( CHARGERCOMMUSER_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE_PTR(_ptr, _api) \
    if (_ptr == NULL) { \
        Det_ReportError(MODULE_ID_CHARGERCOMM_USER_MESSAGES, 0U, _api, CHARGERCOMMUSER_MESSAGES_E_PARAM_INVALID_PTR); \
        goto cleanup; \
    }
#else
#define VALIDATE_PTR(_ptr, _api)
#endif

static void getTCChgCtlData(uint8 *Buffer, uint16 *Length);
static void getTCChgStopData(uint8 *Buffer, uint16 *Length);

extern ChargerCommUser_InnerDataType ChargerCommUser_innerData;
ChargerCommUser_MessageInnerDataType ChargerCommUser_MsgInnerData;

void ChargerCommUser_MessageInit(void)
{
    (void)ChargerComm_SendIPduRegister(&ChargerComm_IPduSendConfigInfo[CHARGERCOMM_GB_CHR_TX_PDUID_NUM], CHARGERCOMM_USER_CHR_TX_PDUID_NUM);
}

Std_ReturnType ChargerCommUser_ChargeIsAllowed(void)
{
    return ChargeM_ChargeIsAllowed();
}

Std_ReturnType ChargerCommUser_TCSendConditionCheck(void)
{
    Std_ReturnType res = E_OK;
    Charge_ChargeType type;

    type = ChargerCommUser_GetCurrentChargeType();
    if (ChargerCommUser_innerData.startFlag == TRUE)
    {
        if (type != CHARGE_TYPE_NONE)
        {
            if (ChargeConnectM_GetConnectType() == type)
            {
                if (ChargerComm_GetCurrentRecStage() == CHARGERCOMM_STAGE_USER_TC)
                {
                    // res = E_OK;
                }
            }
        }
    }
    else
    {
        if (ChargerCommUser_MsgInnerData.isNeedToSendStop)
        {
            // res = E_OK;
        }
    }
    return res;
}

static Std_ReturnType ChargerCommUser_TCRecConditionCheck(void)
{
    uint8 flag = 1U;
    Std_ReturnType res = E_NOT_OK;
    Charge_ChargeType type, userType;

    ChargerCommUser_SetCommunication(TRUE);
    ChargerComm_SetProtocol(CHARGERCOMM_PROTOCOL_USER);
    ChargerCommUser_UpdateCurrentChargeType();
    userType = ChargerCommUser_GetCurrentChargeType();
    if (ChargerConnectM_GetConnectMode(userType) == CHARGECONNECTM_CONNECT_COMMUNICATION)
    {
        // ChargerCommUser_ChargerEnable();
        ChargerComm_SetCommunicationStatus(TRUE);
    }
    else
    {
        if (ChargeConnectM_GetConnectType() != userType)
        {
            flag = 0U;
        }
    }
    if (flag != 0U)
    {
        if (ChargerCommUser_innerData.startFlag == TRUE)
        {
            type = ChargerComm_GetChargeType();
            if (type == CHARGE_TYPE_NONE || type == userType)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ChargerCommUser_GetTCDataCbk(uint8 *Buffer, uint16 *Length)
{
    VALIDATE_PTR(Buffer, CHARGERCOMMUSER_MESSAGES_API_ID_GetTCDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMUSER_MESSAGES_API_ID_GetTCDataCbk);

    if (ChargerCommUser_innerData.startFlag == TRUE)
    {
        getTCChgCtlData(Buffer, Length);
    }
    else
    {
        getTCChgStopData(Buffer, Length);
    }
}

void ChargerCommUser_ReceiveTCCbk(const uint8 *Buffer, uint16 Length)
{
    uint16 index = 0U;
    uint16 temp;
    ChargerComm_StageType stage;
    VALIDATE_PTR(Buffer, CHARGERCOMMUSER_MESSAGES_API_ID_ReceiveTCCbk);

    if (ChargerCommUser_TCRecConditionCheck() == E_OK)
    {
        // condition check
        stage = ChargerComm_GetCurrentRecStage();
        if(stage == CHARGERCOMM_STAGE_USER_TC)
        {
            //ChargerCommUser_CommStart();
            ChargerComm_SetCommunicationStatus(TRUE);
            if(Length >= 5U)
            {
                // ???????
                ChargerComm_SetChargerOutputHV(READ_BT_UINT16(Buffer, index));
                // ???????
                temp = READ_BT_UINT16(Buffer, index);
                ChargerComm_SetChargerOutputCurrent((Current_CurrentType)temp);
                // ???????
                if(temp > 0U)
                {
                    ChargerComm_SetChargingStatus(TRUE);
                }
                else
                {
                    ChargerComm_SetChargingStatus(FALSE);
                }
                // ???????
                temp = READ_BT_UINT8(Buffer, index);
                if (temp & 0x01U)
                {
                    (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_HARDWARE_FAULT_INDEX, 0x01U);
                }
                else
                {
                    (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_HARDWARE_FAULT_INDEX);
                }
                // ???????
                if (temp & 0x02U)
                {
                    (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_OVER_TEMPERATURE_FAULT_INDEX, 0x01U);
                }
                else
                {
                    (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_OVER_TEMPERATURE_FAULT_INDEX);
                }
                // ?????????
                if (temp & 0x04U)
                {
                    (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_INPUT_VOLT_FAULT_INDEX, 0x01U);
                }
                else
                {
                    (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_INPUT_VOLT_FAULT_INDEX);
                }
                // ?????(??)??
                if ((temp & 0x08U))
                {
                    (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_RUN_STATUS_INDEX, 0x01U);
                }
                else
                {
                    (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_RUN_STATUS_INDEX);
                }
                // BMS????
                if ((temp & 0x10U))
                {
                    (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_COMM_ABORT_WITH_BMS_INDEX, 0x01U);
                }
                else
                {
                    (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_COMM_ABORT_WITH_BMS_INDEX);
                }
            }
        }
    }
#if ( CHARGERCOMMUSER_DEV_ERROR_DETECT == STD_ON )
cleanup:
    return;
#endif
}

void ChargerCommUser_GetTC1DataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U, temp;
    // ??????
    temp = Statistic_GetBcuHv(0U);
    temp = VOLT_4_DISPLAY(temp);
    WRITE_BT_UINT16(Buffer, index, temp);
    // ??????
    temp = Statistic_GetBcuLv(0U);
    temp = VOLT_4_DISPLAY(temp);
    WRITE_BT_UINT16(Buffer, index, temp);
    // soc
    temp = Soc_Get();
    temp = (uint16)SOC_TO_UINT8(temp);
    WRITE_BT_UINT8(Buffer, index, temp);
    // ????
    temp = Statistic_GetBcuHt(0U);
    temp = TEMP_4_DISPLAY(temp);
    temp = TEMP_TO_40_OFFSET(temp);
    WRITE_BT_UINT8(Buffer, index, temp);
    // ?????
    temp = Statistic_GetBcu100mvTotalVoltage();
    if (!Statistic_TotalVoltageIsValid(temp))
    {
        temp = 0xFFFFU;
    }
    WRITE_BT_UINT16(Buffer, index, temp);
    *Length = index;
}


static void getTCChgCtlData(uint8 *Buffer, uint16 *Length)
{
    Std_ReturnType flag;
    uint16 temp;
    uint16 index = 0U;
    App_Tv100mvType Volt;
    Current_CurrentType current, current_max;
    RelayM_FunctionType relayType;
    Charge_ChargeType type = ChargeConnectM_GetConnectType();

    if (type == CHARGE_TYPE_DC)
    {
        relayType = ChargerComm_ConfigInfo.DC_RelayType;
    }
    else
    {
        relayType = ChargerComm_ConfigInfo.AC_RelayType;
    }
    flag = ChargerCommUser_ChargeIsAllowed();
    if (flag == E_OK)
    {
        if (ChargeConnectM_ELIsNeeding())
        {
            if (EL_GetDriveState(0U) != EL_LOCK)
            {
                flag = E_NOT_OK;
            }
            else if (EL_GetActualState(0U) != EL_LOCK)
            {
                flag = E_NOT_OK;
            }
            else
            {
            }
        }
    }
    // ??????
    Volt = UserStrategy_GetChargeVoltMax();
    // ??????
    // if (HvProcess_GetChgState() == HVPROCESS_CHG_RELAY_OFF_CURRENT_JUDGE)
    // {
    //     flag = E_NOT_OK;
    // }
    if (flag == E_NOT_OK)
    {
        current = 0;
        Volt = 0U;
    }
    else
    {
        current = UserStrategy_GetChargeCurrentMax();
    }
    if (current < 0)
    {
        current = 0;
    }
    current_max = ChargerCommUser_GetGBSignalCurrentMax();
    if(current > current_max)
    {
        current = current_max;
    }
    if (!UserStartegy_GBChargeRelayIsReady(relayType))
    {
        current = 0;
        Volt = 0U;
    }
    ChargerComm_SetChargeVoltMax(Volt);
    WRITE_BT_UINT16(Buffer, index, Volt);
    ChargerComm_SetChargeCurrentMax(current);
    WRITE_BT_UINT16(Buffer, index, current);
    // ????
    if (flag == E_NOT_OK)
    {
        flag = 1U;
        ChargerCommUser_MsgInnerData.isNeedToSendStop = FALSE;
    }
    else
    {
        flag = 0U;
        ChargerCommUser_MsgInnerData.isNeedToSendStop = TRUE;
    }
    WRITE_BT_UINT8(Buffer, index,  flag);
    // ????
    temp = 0U;
    flag = Diagnosis_StartDiagIsFinish();
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HT) == CHARGEM_CHARGE_DISABLE)
    {
        temp |= (uint16)1U << 1;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_LT) == CHARGEM_CHARGE_DISABLE)
    {
        temp |= (uint16)1U << 2;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_AC_CHG_OC) == CHARGEM_CHARGE_DISABLE)
    {
        temp |= (uint16)1U << 3;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_LEAK) == CHARGEM_CHARGE_DISABLE)
    {
        temp |= (uint16)1U << 4;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHARGER_COMM) == CHARGEM_CHARGE_DISABLE)
    {
        temp |= (uint16)1U << 5;
    }
    if (ChargeM_DiagnosisIsFaultActionExcludeItem(DIAGNOSIS_ITEM_FULL_CHARGE) == E_OK)
    {
        temp |= (uint16)1U << 6;
    }
    else if (ChargeM_StartDiagIsNormal() == E_NOT_OK && flag == TRUE)
    {
        temp |= (uint16)1U << 6;
    }
    else if (ChargeM_OthersFaultIsNormal() == E_NOT_OK)
    {
        temp |= (uint16)1U << 6;
    }
    else
    {
    }
    WRITE_BT_UINT8(Buffer, index,  temp);
    // ??
    WRITE_BT_UINT16(Buffer, index, 0U);
    *Length = index;
#if ( CHARGERCOMMUSER_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

static void getTCChgStopData(uint8 *Buffer, uint16 *Length)
{
    uint16 flag;
    uint16 index = 0U;

    ChargerCommUser_MsgInnerData.isNeedToSendStop = FALSE;

    // ??????
    ChargerComm_SetChargeVoltMax(0U);
    WRITE_BT_UINT16(Buffer, index, 0U);
    // ??????
    ChargerComm_SetChargeCurrentMax(0);
    WRITE_BT_UINT16(Buffer, index, 0U);
    // ????
    WRITE_BT_UINT8(Buffer, index,  1U);
    // ????
    flag = 0U;
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HT) == CHARGEM_CHARGE_DISABLE)
    {
        flag |= (uint16)1U << 1;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_LT) == CHARGEM_CHARGE_DISABLE)
    {
        flag |= (uint16)1U << 2;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_AC_CHG_OC) == CHARGEM_CHARGE_DISABLE)
    {
        flag |= (uint16)1U << 3;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_LEAK) == CHARGEM_CHARGE_DISABLE)
    {
        flag |= (uint16)1U << 4;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHARGER_COMM) == CHARGEM_CHARGE_DISABLE)
    {
        flag |= (uint16)1U << 5;
    }
    if (ChargeM_DiagnosisIsFaultActionExcludeItem(DIAGNOSIS_ITEM_FULL_CHARGE) == E_OK)
    {
        flag |= (uint16)1U << 6;
    }
    else if (ChargeM_StartDiagIsNormal() == E_NOT_OK && ChargerCommUser_MsgInnerData.isNeedToSendStop == TRUE)
    {
        flag |= (uint16)1U << 6;
    }
    else if (ChargeM_OthersFaultIsNormal() == E_NOT_OK)
    {
        flag |= (uint16)1U << 6;
    }
    else
    {
    }
    WRITE_BT_UINT8(Buffer, index,  flag);
    // ??
    WRITE_BT_UINT16(Buffer, index, 0U);
    *Length = index;
#if ( CHARGERCOMMUSER_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommUser_RecTCTimeoutCbk(void)
{
    ChargerCommUser_SetCommunication(FALSE);
    ChargerComm_ClrChargerStatus();
    if (ChargerConnectM_GetConnectMode(ChargerCommUser_GetCurrentChargeType()) == CHARGECONNECTM_CONNECT_COMMUNICATION)
    {
        // ChargerCommUser_CommStop();
    }
    ChargerComm_SetCommunicationStatus(FALSE);
}
