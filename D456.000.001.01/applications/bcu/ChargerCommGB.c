/**
 * \file ChargerCommGB.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 国标充电机通信文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */
#include <stdlib.h>
#include <string.h>
#include "App_Types.h"
#include "ucos_ii.h"
#include "ChargerCommGB.h"
#include "ParameterM.h"
#include "Det.h"
#include "ChargeM.h"
#include "AppInfo.h"
#include "Statistic.h"
#include "PwmCapture_Lcfg.h"
#include "PowerM.h"
#include "UserStrategy.h"
#include "ChargerComm_LCfg.h"
#include "TemperatureM.h"
#include "BridgeInsu.h"
#ifdef UPC6000
#include "SystemConnection_Lcfg.h"
#endif
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
#include "Modules.h"
#endif

#define CHARGERCOMMGB_E_PARAM_INVALID_PTR           0U
#define CHARGERCOMMGB_E_PARAM_INVALID_CHARGE_TYPE   1U

#define CHARGERCOMMGB_API_ID_Init                   0U

#define CHARGERCOMMGB_API_ID_GetBHMDataCbk          20U

#define CHARGERCOMMGB_API_ID_ReceiveCHMCbk          100U

#define CHARGERCOMMGB_API_ID_StartRecStageTimeout   200U
#define CHARGERCOMMGB_API_ID_IsChargingReady        201U

#define CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN      0U

#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE_PTR(_ptr, _api) \
    if (_ptr == NULL) { \
        Det_ReportError(MODULE_ID_CHARGERCOMM_GB, 0U, _api, CHARGERCOMMGB_E_PARAM_INVALID_PTR); \
        goto cleanup; \
    }

#define VALIDATE_CHARGE_TYPE(_type, _api) \


#else

#define VALIDATE_PTR(_ptr, _api)
#endif

static ChargerCommGB_InnerDataType ChargerCommGB_innerData;

static void ChargerCommGB_ReadConfigPara(void);
void ChargerCommGB_CommStart(void);
void ChargerCommGB_CommStop(void);
void ChargerCommGB_FullCharge(void);
static void ChargerCommGB_SetCommunication(uint8 flag);
static void ChargerCommGB_SetCurrentChargeType(Charge_ChargeType type);
static void ChargerCommGB_SetSelfDiagnosis(ChargerComm_SelfDiagnosisType diagnosis);
static void ChargerCommGB_ClrSelfDiagnosis(void);
static void ChargerCommGB_UpdateSelfDiagnosis(ChargerComm_SelfDiagnosisType diagnosis);
static void ChargerCommGB_TimeoutCntUpdate(void);
static void ChargerCommGB_ClearChargerStatusCarefully(void);
static void ChargerCommGB_RestChargerStatus(void);
static Current_CurrentType ChargerCommGB_CurrentToBmsCurrent(Current_CurrentType cur);
static Current_CurrentType ChargerCommGB_CurrentFromBmsCurrent(Current_CurrentType cur);
static void ChargerCommGB_GetDecreaseCurrent(Current_CurrentType new_current, Current_CurrentType *current);
static uint8 ChargerCommGB_ChargeIsStop(void);
static uint8 ChargerCommGB_IsChargingReady(void);
static void ChargerCommGB_ChargingReadyCheck(void);

void ChargerCommGB_Init(void)
{
    ChargerCommGB_innerData.startFlag = FALSE;
    ChargerCommGB_innerData.relayAdhesionCheckFlag = TRUE;
    ChargerCommGB_innerData.protocolVersion = CHARGERCOMMGB_PROTOCOL_VERSION_2015;
    ChargerCommGB_innerData.chargeTypeMask = 0U;
    ChargerCommGB_innerData.currentChargeType = CHARGE_TYPE_NONE;
    if (CHARGERCOMM_PROTOCOL_IS_GB(ChargerComm_ConfigInfo.AC_Protocol) ||
        CHARGERCOMM_PROTOCOL_IS_GB(ChargerComm_ConfigInfo.DC_Protocol))
    {
        ChargerCommGB_ReadConfigPara();
        (void)ChargerComm_SendIPduRegister(&ChargerComm_IPduSendConfigInfo[0], CHARGERCOMM_GB_CHR_TX_PDUID_NUM);
        OSTimeDly(2U);
    }
}

static void ChargerCommGB_ReadConfigPara(void)
{
    ChargerComm_ProtocolType protocol;

    if (ChargeM_ConfigInfo.AC_Para.enable == STD_ON)
    {
        protocol = ChargerComm_ConfigInfo.AC_Protocol;
        if (CHARGERCOMM_PROTOCOL_IS_GB(protocol))
        {
            ChargerCommGB_SetChargeType(CHARGE_TYPE_AC);
            ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
        }
    }
    if (ChargeM_ConfigInfo.DC_Para.enable == STD_ON)
    {
        protocol = ChargerComm_ConfigInfo.DC_Protocol;
        if (CHARGERCOMM_PROTOCOL_IS_GB(protocol))
        {
            ChargerCommGB_SetChargeType(CHARGE_TYPE_DC);
            ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
        }
    }
}

void ChargerCommGB_SetChargeType(Charge_ChargeType type)
{
    imask_t mask;

    Irq_Save(mask);
    ChargerCommGB_innerData.chargeTypeMask |= ((uint16)1U << type);
    Irq_Restore(mask);
}

static boolean ChargerCommGB_ChargeTypeIsOn(Charge_ChargeType type)
{
    boolean flag = FALSE;
    uint16 typeMask;
    imask_t mask;

    if (type != CHARGE_TYPE_NONE)
    {
        Irq_Save(mask);
        typeMask = ChargerCommGB_innerData.chargeTypeMask;
        Irq_Restore(mask);

        if (typeMask & ((uint16)1U << type))
        {
            flag = TRUE;
        }
    }
    return flag;
}
/*
static boolean ChargerCommGB_ChargeTypeIsNone(void)
{
    boolean flag = FALSE;
    uint16 typeMask;
    imask_t mask;

    Irq_Save(mask);
    typeMask = ChargerCommGB_innerData.chargeTypeMask;
    Irq_Restore(mask);

    if (typeMask == 0U)
    {
        flag = TRUE;
    }
    return flag;
}
*/
static void ChargerCommGB_SetCurrentChargeType(Charge_ChargeType type)
{
    imask_t mask;

    Irq_Save(mask);
    ChargerCommGB_innerData.currentChargeType = type;
    Irq_Restore(mask);
}

Charge_ChargeType ChargerCommGB_GetCurrentChargeType(void)
{
    imask_t mask;
    Charge_ChargeType type;

    Irq_Save(mask);
    type = ChargerCommGB_innerData.currentChargeType;
    Irq_Restore(mask);
    return type;
}

static void ChargerCommGB_UpdateCurrentChargeType(void)
{
    boolean flag = FALSE;
    if (ChargerCommGB_GetCurrentChargeType() == CHARGE_TYPE_NONE)
    {
        if (ChargerCommGB_ChargeTypeIsOn(CHARGE_TYPE_AC) == TRUE)
        {
            if (ChargeConnectM_GetConnectStatus(CHARGE_TYPE_AC) == E_OK)
            {
                ChargerCommGB_SetCurrentChargeType(CHARGE_TYPE_AC);
                flag = TRUE;
            }
        }
        if (!flag)
        {
            if (ChargerCommGB_ChargeTypeIsOn(CHARGE_TYPE_DC) == TRUE)
            {
                if (ChargeConnectM_GetConnectStatus(CHARGE_TYPE_DC) == E_OK)
                {
                    ChargerCommGB_SetCurrentChargeType(CHARGE_TYPE_DC);
                    flag = TRUE;
                }
            }
        }
        if (!flag)
        {
            ChargerCommGB_SetCurrentChargeType(CHARGE_TYPE_NONE);
        }
    }
}

void ChargerCommGB_ChargerEnable(void)
{
    imask_t mask;

    Irq_Save(mask);
    ChargerCommGB_innerData.startFlag = TRUE;
    ChargerCommGB_innerData.stopFlag = FALSE;
    Irq_Restore(mask);
    ChargerCommGB_CommStart();
}

void ChargerCommGB_ChargerDisable(void)
{
    imask_t mask;
    ChargerCommGB_ChargeStageType stage;

    Irq_Save(mask);
    ChargerCommGB_innerData.stopFlag = TRUE;
    stage = ChargerCommGB_innerData.stage;
    Irq_Restore(mask);

    if (stage <= CHARGERCOMMGB_STAGE_CONNECT_WAITING || //if GB is commnicated, then stop
        stage >= CHARGERCOMMGB_STAGE_FAULT)
    {
        ChargerCommGB_CommStop();
    }
}

void ChargerCommGB_CommStart(void)
{
    Charge_ChargeType currentType;
    ChargerComm_StageType stage = ChargerComm_GetCurrentRecStage();

    ChargerCommGB_UpdateCurrentChargeType();
    currentType = ChargerCommGB_GetCurrentChargeType();
    if (ChargerComm_GetChargeType() == CHARGE_TYPE_NONE &&
        currentType != CHARGE_TYPE_NONE &&
        ChargerCommGB_innerData.startFlag == TRUE &&
        stage == CHARGERCOMM_STAGE_IDLE)
    {
        if (currentType == CHARGE_TYPE_DC)
        {
            PowerM_Reset(POWERM_CUR_CHARGE_DC);
        }
        else
        {
            PowerM_Reset(POWERM_CUR_CHARGE_AC);
        }
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
        ChargerComm_SetChargeType(currentType);
        ChargerComm_InitChargeVoltAndCurrent();
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_COMM_WAITING);
    }
}

void ChargerCommGB_CommStop(void)
{
    imask_t mask;
    Charge_ChargeType currentType;
    ChargerComm_StageType stage = ChargerComm_GetCurrentRecStage();

    Irq_Save(mask);
    ChargerCommGB_innerData.communication = FALSE;
    ChargerComm_ResetCommunicationStatus();
    ChargerCommGB_RestChargerStatus();
    currentType = ChargerCommGB_GetCurrentChargeType();
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
    ChargerCommGB_SetCurrentChargeType(CHARGE_TYPE_NONE);
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CONNECT_WAITING;
    if (ChargerCommGB_innerData.stopFlag == TRUE)
    {
        ChargerCommGB_innerData.startFlag = FALSE;
        ChargerCommGB_innerData.stopFlag = FALSE;
    }
    if (stage >= CHARGERCOMM_STAGE_GB_START && stage <= CHARGERCOMM_STAGE_GB_STOP)
    {
        ChargerComm_ClrChargeStatus();
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_IDLE);
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
    }
    Irq_Restore(mask);
}

static void ChargerCommGB_CommStopForRestart(void)
{
    imask_t mask;

    Irq_Save(mask);
    if (ChargerConnectM_GetConnectMode(ChargerCommGB_GetCurrentChargeType()) == CHARGECONNECTM_CONNECT_COMMUNICATION ||
        ChargerCommGB_innerData.stopFlag == TRUE)
    {
        // ChargerCommGB_CommStop();
    }
    else
    {
        ChargerCommGB_ClearChargerStatusCarefully();
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_RECOMM_CRM);
        ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CONNECT_WAITING;
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
    }
    Irq_Restore(mask);
}

void ChargerCommGB_FullCharge(void)
{
    imask_t mask;
    Charge_ChargeType currentType;
    ChargerComm_StageType stage = ChargerComm_GetCurrentRecStage();

    Irq_Save(mask);
    ChargerCommGB_innerData.communication = FALSE;
    ChargerComm_ResetCommunicationStatus();
    // ChargerCommGB_RestChargerStatus();
    currentType = ChargerCommGB_GetCurrentChargeType();
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
    // ChargerCommGB_SetCurrentChargeType(CHARGE_TYPE_NONE);
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CONNECT_WAITING;
    if (ChargerCommGB_innerData.stopFlag == TRUE)
    {
        ChargerCommGB_innerData.startFlag = FALSE;
        ChargerCommGB_innerData.stopFlag = FALSE;
    }
    if (stage >= CHARGERCOMM_STAGE_GB_START && stage <= CHARGERCOMM_STAGE_GB_STOP)
    {
        // ChargerComm_ClrChargeStatus();
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_FULLCHARGE);
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
    }
    Irq_Restore(mask);
}

uint8 ChargerCommGB_CommIsStart(void)
{
    return ChargerCommGB_innerData.startFlag;
}

static void ChargerCommGB_SetCommunication(uint8 flag)
{
    ChargerCommGB_innerData.communication = flag;
    ChargerComm_SetCommunicationStatus(flag);
}

uint8 ChargerCommGB_IsCommunication(void)
{
    return ChargerCommGB_innerData.communication;
}

//Send functions define
Std_ReturnType ChargerCommGB_BHMSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargeConnectM_GetDCACConnectType() == ChargerCommGB_innerData.currentChargeType)
            {
                if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_SHAKEHAND_START)
                {
                    res = E_OK;
                }
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBHMDataCbk(uint8 *Buffer, uint16 *Length)
{
    App_Tv100mvType volt;
    uint16 index = 0U;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    volt = ChargeM_GetChargeDisableTriggerPara(DIAGNOSIS_ITEM_CHG_HTV, 0U);
    if (Statistic_TotalVoltageIsValid(volt))
    {
        volt += 100U;
    }
    WRITE_LT_UINT16(Buffer, index, volt);//最高允许充电电压
    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BRMSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargeConnectM_GetDCACConnectType() == ChargerCommGB_innerData.currentChargeType)
            {
                if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_SHAKEHAND_IDENTIFY)
                {
                    res = E_OK;
                }
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBRMDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 temp = 0U;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    WRITE_LT_UINT24(Buffer,
        index,
        ChargerComm_GetProtocol() == CHARGERCOMM_PROTOCOL_GB2015 ? CHARGERCOMMGB_PROTOCOL_VERSION_2015 : CHARGERCOMMGB_PROTOCOL_VERSION_2011);//协议版本号
    WRITE_LT_UINT8(Buffer, index, BatteryInfo_BaseConfigInfo.Type);//电池类型
    WRITE_LT_UINT16(Buffer, index, BatteryInfo_BaseConfigInfo.NominalCap);//额定容量
    WRITE_LT_UINT16(Buffer, index, BatteryInfo_BaseConfigInfo.NominalTotalVolt);//额定总压
    WRITE_LT_UINT8(Buffer, index, 'U');//厂商名称
    WRITE_LT_UINT8(Buffer, index, 'D');//厂商名称
    WRITE_LT_UINT8(Buffer, index, 'A');//厂商名称
    WRITE_LT_UINT8(Buffer, index, 'N');//厂商名称
    WRITE_LT_UINT32(Buffer, index, CHARGERCOMMGB_LONG_VALUE_DEFAULT);//电池组序号
    WRITE_LT_UINT24(Buffer, index, CHARGERCOMMGB_3_BYTES_VALUE_DEFAULT);//电池组生产日期
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_DISCHARGE_CNT_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//电池组充放电次数
    WRITE_LT_UINT8(Buffer, index, 0x00);//电池组充放电次数
    WRITE_LT_UINT8(Buffer, index, CHARGERCOMMGB_BYTE_VALUE_DEFAULT);//电池组产权标识
    WRITE_LT_UINT8(Buffer, index, CHARGERCOMMGB_BYTE_VALUE_DEFAULT);//保留
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN1_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//车辆识别码VIN
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN2_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//车辆识别码VIN
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN3_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//车辆识别码VIN
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN4_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//车辆识别码VIN
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN5_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//车辆识别码VIN
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN6_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//车辆识别码VIN
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN7_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//车辆识别码VIN
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN8_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//车辆识别码VIN
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_VIN9_INDEX, &temp);
    WRITE_LT_UINT8(Buffer, index, temp);//车辆识别码VIN
    if(ChargerComm_GetProtocol() == CHARGERCOMM_PROTOCOL_GB2015)
    {
        WRITE_LT_UINT8(Buffer, index, FWVERSION_BUILD); //软件版本流水号
        WRITE_LT_UINT8(Buffer, index, APP_INFO_BUILD_DATE_D); //BMS软件编译时间
        WRITE_LT_UINT8(Buffer, index, APP_INFO_BUILD_DATE_M);
        WRITE_BT_UINT16(Buffer, index, APP_INFO_BUILD_DATE_Y);
        WRITE_LT_UINT8(Buffer, index, FWVERSION_REVISION); //BMS软件版本号
        WRITE_LT_UINT8(Buffer, index, FWVERSION_MINOR);
        WRITE_LT_UINT8(Buffer, index, FWVERSION_MAJOR);
    }
    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BCPSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_PARA_CONFIG)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBCPDataCbk(uint8 *Buffer, uint16 *Length)
{
    App_Tv100mvType volt;
    uint16 index = 0U, temp;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    temp = ChargeM_GetChargeDisableTriggerPara(DIAGNOSIS_ITEM_CHG_HV, 0U);
    if (temp != 0xFFFFU)
    {
        temp += 20U;
    }
    WRITE_LT_UINT16(
            Buffer,
            index,
            MV_TO_10MV(temp));//最高允许充电单体电压
    if (ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
    {
        temp = BatteryInfo_BaseConfigInfo.NominalDCCurrent + 100U;
    }
    else
    {
        temp = BatteryInfo_BaseConfigInfo.NominalACCurrent + 100U;
    }
    WRITE_LT_UINT16(
        Buffer,
        index,
        ChargerCommGB_CurrentFromBmsCurrent((Current_CurrentType)temp));//最高允许充电电流
    temp = (uint16)DIVISION((uint32)BatteryInfo_BaseConfigInfo.NominalCap * BatteryInfo_BaseConfigInfo.NominalTotalVolt, 10000UL);
    WRITE_LT_UINT16(Buffer, index, temp);//额定能量
    volt = ChargeM_GetChargeDisableTriggerPara(DIAGNOSIS_ITEM_CHG_HTV, 0U);
    if (Statistic_TotalVoltageIsValid(volt))
    {
        volt += 100U;
    }
    WRITE_LT_UINT16(Buffer, index, volt);//最高允许充电电压
    temp = ChargeM_GetChargeDisableTriggerPara(DIAGNOSIS_ITEM_CHG_HT, 0U);
    if (temp < CELL_TEMPERATURE_SHORT_CIRCUIT_VALUE)
    {
        if (temp < CELL_TEMPERATURE_SHORT_CIRCUIT_VALUE - 5U)
        {
            temp += 5U;
        }
    }
    WRITE_LT_UINT8(Buffer, index, temp);//最高允许充电温度
    WRITE_LT_UINT16(Buffer, index, Soc_Get());//当前SOC
    WRITE_LT_UINT16(Buffer, index, Statistic_GetBcu100mvTotalVoltage());//当前总压

    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BROSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CHARGE_READY)
            {
               res = E_OK;
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBRODataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint8 flag;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    flag = ChargerCommGB_innerData.bmsChargeReady;
    WRITE_LT_UINT8(Buffer, index, flag);//充电准备就绪状态
    if(flag == CHARGERCOMMGB_BMS_CHARGE_READY)
    {
        ChargerCommGB_innerData.bmsChargeReadySendFlag = TRUE;
        if (ChargerComm_GetCurrentRecStage() < CHARGERCOMM_STAGE_GB_CRO)
        {
            if (ChargerCommGB_innerData.insuIsStop)
            {
#ifdef UPC6000

#if SYSTEM_BATTERY_CELL_NUM <= 48U
                BridgeInsu_Start(BRIDGEINSU_MOS_ALWAYS_ON);
#else
                BridgeInsu_Start(BRIDGEINSU_MOS_BY_VOL);
#endif

#endif
                ChargerCommGB_innerData.insuIsStop = FALSE;
            }
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CRO);
        }
    }
    ChargerCommGB_ChargingReadyCheck();
    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BCLSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CHARGING)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBCLDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 Volt, VoltMax, VoltMin;
    uint32 address;
    Current_CurrentType Current, CurrentMax/*, CurrentMin */;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    if (ChargerComm_GetCurrentRecStage() < CHARGERCOMM_STAGE_GB_CCS)
    {
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CCS);
    }
    Volt = UserStrategy_GetChargeVoltMax();
    ChargerComm_SetChargeVoltMax(Volt);
    VoltMax = ChargerComm_GetChargerOutputHVMax();
    VoltMin = ChargerComm_GetChargerOutputHVMin();
    if(VoltMax && Volt > VoltMax)
    {
        Volt = VoltMax;
    }
    else if(VoltMin && Volt < VoltMin)
    {
        Volt = VoltMin;
    }
    else
    {
    }
    WRITE_LT_UINT16(Buffer, index, Volt);//充电电压需求
    if (ChargerCommGB_ChargeIsStop())
    {
        if(ChargerCommGB_innerData.stopChargeDev == CHARGERCOMMGB_STOP_CHARGE_DEV_NONE)
        {
            ChargerCommGB_innerData.stopChargeDev = CHARGERCOMMGB_STOP_CHARGE_DEV_BMS;
        }
        if(ChargerCommGB_innerData.bclZeroCurSendFlag == TRUE && ChargerCommGB_innerData.bcsChargeStopSendFlag == TRUE)
        {
            ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CHARGE_STOP;
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CST_CSD);
        }
    }
    if(!(ChargerCommGB_innerData.bmsStopReason || ChargerCommGB_innerData.bmsFaultReason || ChargerCommGB_innerData.bmsErrorReason))
    {
        Current = UserStrategy_GetChargeCurrentMax();
        if (Current < 0)
        {
            Current = 0;
        }
        CurrentMax = ChargerComm_GetChargerOutputCurrentMax();
        // CurrentMin = ChargerComm_GetChargerOutputCurrentMin();
        if(CurrentM_IsValidCurrent(CurrentMax) && CurrentMax > 0 && Current > CurrentMax)
        {
            Current = CurrentMax;
        }
        /*else if(CurrentM_IsValidCurrent(CurrentMin) && CurrentMin > 0 && Current < CurrentMin)
        {
            Current = CurrentMin;
        }
        else
        {
        }*/
        CurrentMax = ChargeConnectM_GetChargeCurrentMax(ChargerCommGB_innerData.currentChargeType);
        if(Current > CurrentMax)
        {
            Current = CurrentMax;
            ChargerCommGB_innerData.chargeCurrentLast = Current;
        }
        else
        {
            ChargerCommGB_GetDecreaseCurrent(Current, &ChargerCommGB_innerData.chargeCurrentLast);
        }
    }
    else
    {
        ChargerCommGB_innerData.chargeCurrentLast = 0;
        ChargerCommGB_innerData.bclZeroCurSendFlag = TRUE;
    }
    ChargerComm_SetChargeCurrentMax(ChargerCommGB_innerData.chargeCurrentLast);
    Current = ChargerCommGB_CurrentFromBmsCurrent(ChargerCommGB_innerData.chargeCurrentLast);
    WRITE_LT_UINT16(Buffer, index, Current);//充电电流需求
    Volt = Statistic_GetBcu100mvTotalVoltage();
    if (ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
    {
        address = PARAMETERM_GET_CALIB_PARA_ADDR(ChargePara.DC_Para.chargeTotalVoltMax); /*lint !e507 !e413 */
    }
    else
    {
        address = PARAMETERM_GET_CALIB_PARA_ADDR(ChargePara.AC_Para.chargeTotalVoltMax); /*lint !e507 !e413 */
    }
    (void)ParameterM_CalibRead(address, (uint8*)(&VoltMax), sizeof(uint16));
    if (Volt >= VoltMax)
    {
        VoltMin = Volt - VoltMax;
    }
    else
    {
        VoltMin = VoltMax - Volt;
    }
    if(VoltMin < V_TO_100MV(2U) || Volt > VoltMax)
    {
        Volt = 0x01U; //恒压模式
    }
    else
    {
        Volt = 0x02U; //恒流模式
    }
    WRITE_LT_UINT8(Buffer, index, (uint8)Volt);

    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BCSSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CHARGING)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBCSDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 Volt, temp;
    uint32 Time;
    Current_CurrentType Current;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    Volt = Statistic_GetBcu100mvTotalVoltage();
    WRITE_LT_UINT16(Buffer, index, Volt);//检测总压

    Current = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);
    Current = ChargerCommGB_CurrentFromBmsCurrent(Current);
    WRITE_LT_UINT16(Buffer, index, Current);//检测电流
    Volt = (uint16)MV_TO_10MV(Statistic_GetBcuHv(0U));
    if (CellDataM_VoltageIsValid(Volt))
    {
        Volt &= 0xFFFU;
    }
    else
    {
        Volt = 0U;
    }
    temp = Statistic_GetBcuHvSlaveNum(0U);
    Volt |= (uint16)(temp + 1U) << 12;
    WRITE_LT_UINT16(Buffer, index, Volt);//最高单体电压及位置
    WRITE_LT_UINT8(Buffer, index, SOC_TO_PERCENT(Soc_Get()));//SOC
    Time = Statistic_GetRequireChargeTime();
    Time = S_TO_MIN(Time);
    if(Time > CHARGERCOMMGB_CHARGE_TIME_MAX)
    {
        Time = CHARGERCOMMGB_CHARGE_TIME_MAX;
    }
    WRITE_LT_UINT16(Buffer, index, Time);//剩余充电时间
    if (ChargerCommGB_innerData.bclZeroCurSendFlag == TRUE)
    {
        ChargerCommGB_innerData.bcsChargeStopSendFlag = TRUE;
    }
    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BSMSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CHARGING)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBSMDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 temp;
    uint8 temp8;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    temp = CellDataM_VoltageIndexToLogic(Statistic_GetBcuHvSlaveNum(0U), Statistic_GetBcuHvIndex(0U));
    WRITE_LT_UINT8(Buffer, index, temp + 1U);//最高单体电压编号
    temp8 = Statistic_GetBcuHt(0U);
    WRITE_LT_UINT8(Buffer, index, TEMP_4_DISPLAY(temp8));//最高温度
    temp = CellDataM_TemperatureIndexToLogic(Statistic_GetBcuHtSlaveNum(0U), Statistic_GetBcuHtIndex(0U));
    WRITE_LT_UINT8(Buffer, index, temp + 1U);//最高温度编号
    temp8 = Statistic_GetBcuLt(0U);
    WRITE_LT_UINT8(Buffer, index, TEMP_4_DISPLAY(temp8));//最低温度
    temp = CellDataM_TemperatureIndexToLogic(Statistic_GetBcuLtSlaveNum(0U), Statistic_GetBcuLtIndex(0U));
    WRITE_LT_UINT8(Buffer, index, temp + 1U);//最低温度编号
    temp = 0U;
    if(Diagnosis_GetLevel(DIAGNOSIS_ITEM_CHG_HV) >= DIAGNOSIS_LEVEL_THIRD) //过充
    {
        temp |= 0x01U;

    }
    else if (Diagnosis_GetLevel(DIAGNOSIS_ITEM_DCHG_HV) >= DIAGNOSIS_LEVEL_THIRD)
    {
        temp |= 0x01U;
    }
    else
    {
        if(Diagnosis_GetLevel(DIAGNOSIS_ITEM_CHG_LV) >= DIAGNOSIS_LEVEL_THIRD) //过放
        {
            temp |= 0x02U;
        }
        else if (Diagnosis_GetLevel(DIAGNOSIS_ITEM_DCHG_LV) >= DIAGNOSIS_LEVEL_THIRD)
        {
            temp |= 0x02U;
        }
        else
        {
        }
    }
    /*if(Diagnosis_GetLevel(DIAGNOSIS_ITEM_HSOC) >= DIAGNOSIS_LEVEL_THIRD) //HSOC
    {
        temp |= 0x04U;
    }
    else if(Diagnosis_GetLevel(DIAGNOSIS_ITEM_LSOC) >= DIAGNOSIS_LEVEL_THIRD)
    {
        temp |= 0x08U;
    }
    else
    {
    }*/
    if (ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_DC) //过流
    {
        if (Diagnosis_GetLevel(DIAGNOSIS_ITEM_DC_CHG_OC) >= DIAGNOSIS_LEVEL_THIRD)
        {
            temp |= 0x10U;
        }
    }
    else if (ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_AC)
    {
        if (Diagnosis_GetLevel(DIAGNOSIS_ITEM_AC_CHG_OC) >= DIAGNOSIS_LEVEL_THIRD)
        {
            temp |= 0x10U;
        }
    }
    else
    {
    }
    if(Diagnosis_GetLevel(DIAGNOSIS_ITEM_CHG_HT) >= DIAGNOSIS_LEVEL_THIRD) //过温
    {
        temp |= 0x40U;
    }
    else if (Diagnosis_GetLevel(DIAGNOSIS_ITEM_DCHG_HT) >= DIAGNOSIS_LEVEL_THIRD)
    {
        temp |= 0x40U;
    }
    else
    {
    }
    WRITE_LT_UINT8(Buffer, index, temp);
    temp = 0xC0U;
    if(Diagnosis_GetLevel(DIAGNOSIS_ITEM_LEAK) >= DIAGNOSIS_LEVEL_THIRD)  //漏电
    {
        temp |= 0x01U;
    }
    if(ChargerCommGB_CheckChargeReq(0U) == 1U) //其他
    {
        temp |= 0x10U;
    }
    WRITE_LT_UINT8(Buffer, index, temp);

    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BMVSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    // if (ChargerCommGB_innerData.startFlag == TRUE)
    // {
    //     if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
    //     {
    //         if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CHARGING)
    //         {
    //             res = E_OK;
    //         }
    //     }
    // }
    return res;
}

void ChargerCommGB_GetBMVDataCbk(uint8 *Buffer, uint16 *Length)
{
    imask_t mask;
    uint16 GroupNum, GroupMax;
    uint16 index = 0U;
    uint16 i, Num;
    App_VoltageType Volt;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    Irq_Save(mask);
    GroupNum = ChargerCommGB_innerData.cellVoltGroupNum;
    Irq_Restore(mask);
    GroupMax = (SystemConnection_ConfigInfo.voltageNum + 255U) / 256U;
    if (GroupMax > 0x0FU)
    {
        GroupMax = 0x0FU;
    }
    if (GroupNum >= GroupMax)
    {
        GroupNum = 0U;
    }
    Num = CellDataM_BmuVoltageLogicIdMax[SystemConnection_ConfigInfo.SlaveNum - 1U];
    if (Num >= (GroupNum + 1U) * 256U)
    {
        Num = (GroupNum + 1U) * 256U;
    }

    for (i = GroupNum * 256U; i < Num; i++)
    {
        Volt = CellDataM_GetVoltage(i);
        Volt = VOLT_4_DISPLAY(Volt);
        Volt = (uint16)MV_TO_10MV(Volt);
        if (Volt > CHARGERCOMMGB_CELL_VOLT_MAX)
        {
            Volt = CHARGERCOMMGB_CELL_VOLT_MAX;
        }
        Volt |= (uint16)((uint16)GroupNum << 12);
        WRITE_LT_UINT16(Buffer, index, Volt);
    }
    GroupNum++;
    if (GroupNum >= GroupMax)
    {
        GroupNum = 0U;
    }
    Irq_Save(mask);
    ChargerCommGB_innerData.cellVoltGroupNum = (uint8)GroupNum;
    Irq_Restore(mask);

    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BMTSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    // if (ChargerCommGB_innerData.startFlag == TRUE)
    // {
    //     if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
    //     {
    //         if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CHARGING)
    //         {
    //             res = E_OK;
    //         }
    //     }
    // }
    return res;
}

void ChargerCommGB_GetBMTDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 i, Num;
    App_TemperatureType Temperature;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    Num = CellDataM_BmuTemperatureLogicIdMax[SystemConnection_ConfigInfo.SlaveNum - 1U];
    for (i = 0U; i < Num; i++)
    {
        Temperature = CellDataM_GetTemperature(i);
        WRITE_LT_UINT8(Buffer, index, TEMP_4_DISPLAY(Temperature));
    }

    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BSTSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CHARGE_STOP)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBSTDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint8 error;
    uint16 index = 0U;
    uint16 temp;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    temp = ChargerCommGB_innerData.bmsStopReason;
    if(ChargerComm_GetProtocol() == CHARGERCOMM_PROTOCOL_GB2015 &&
        ChargerCommGB_innerData.stopChargeDev == CHARGERCOMMGB_STOP_CHARGE_DEV_CHARGER)
    {
        temp |= 0x40U;
    }
    WRITE_LT_UINT8(Buffer, index, temp);//BMS中止充电原因
    WRITE_LT_UINT16(Buffer, index, ChargerCommGB_innerData.bmsFaultReason);//BMS中止充电故障原因
    error = ChargerCommGB_innerData.bmsErrorReason | 0xF0U;
    WRITE_LT_UINT8(Buffer, index, error);//BMS中止充电错误原因
    ChargerCommGB_innerData.bstSendCnt++;
    ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);

    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BSDSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_STATISTIC)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ChargerCommGB_GetBSDDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 temp;
    uint8 temp8;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    WRITE_LT_UINT8(Buffer, index, SOC_TO_PERCENT(Soc_Get()));//中止SOC
    temp = Statistic_GetBcuLv(0U);
    temp = VOLT_4_DISPLAY(temp);
    temp = (uint16)MV_TO_10MV(temp);
    WRITE_LT_UINT16(Buffer, index, temp);//最低电压
    temp = Statistic_GetBcuHv(0U);
    temp = VOLT_4_DISPLAY(temp);
    temp = (uint16)MV_TO_10MV(temp);
    WRITE_LT_UINT16(Buffer, index, temp);//最高电压
    temp8 = Statistic_GetBcuLt(0U);
    WRITE_LT_UINT8(Buffer, index, TEMP_4_DISPLAY(temp8));//最低温度
    temp8 = Statistic_GetBcuHt(0U);
    WRITE_LT_UINT8(Buffer, index, TEMP_4_DISPLAY(temp8));//最高温度

    *Length = index;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ChargerCommGB_BEMSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargerCommGB_innerData.startFlag == TRUE)
    {
        if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_FAULT)
        {
            res = E_OK;
        }
    }
    return res;
}

void ChargerCommGB_GetBEMDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint8 flag = 0U;
    uint16 temp;
    uint32 now;

    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, CHARGERCOMMGB_API_ID_GetBHMDataCbk);

    Buffer[0] = ChargerCommGB_innerData.bmsTimeoutReason[0] | 0xF0U;
    Buffer[1] = ChargerCommGB_innerData.bmsTimeoutReason[1] | 0xF0U;
    Buffer[2] = ChargerCommGB_innerData.bmsTimeoutReason[2] | 0xF0U;
    Buffer[3] = ChargerCommGB_innerData.bmsTimeoutReason[3] | 0xFCU;

    now = OSTimeGet();
    if (ChargerCommGB_innerData.bemCurDecreaseLastTick == 0U)
    {
        ChargerCommGB_innerData.bemCurDecreaseLastTick = now;
    }
    temp = (uint16)abs(CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN));
    if (temp <= CURRENT_100MA_FROM_A(5U))
    {
        flag = 1U;
    }
    else if (MS_GET_INTERNAL(ChargerCommGB_innerData.bemCurDecreaseLastTick, now) >= 10000U)
    {
        flag = 1U;
    }
    else
    {
    }
    if (flag != 0U)
    {
        ChargerCommGB_CommStopForRestart();
        ChargerCommGB_innerData.bemCurDecreaseLastTick = 0U;
    }
    *Length = CHARGERCOMMGB_BMS_TIMEOUT_BYTE_NUM;
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}
//用于超时重启充电
static void ChargerCommGB_ClearChargerStatusCarefully(void)
{
    ChargerCommGB_innerData.communication = FALSE;
    ChargerCommGB_innerData.timeoutCntSwitch = FALSE;
    ChargerCommGB_innerData.bmsChargeReady = FALSE;
    ChargerCommGB_innerData.bmsChargeReadyLastTick = 0U;
    ChargerCommGB_innerData.bmsChargeReadySendFlag = FALSE;
    ChargerCommGB_innerData.chargeCurrentLast = 0;
    ChargerCommGB_innerData.chargeCurrentLastTick = 0U;
    ChargerCommGB_innerData.bmsStopReason = 0U;
    ChargerCommGB_innerData.bmsFaultReason = 0U;
    ChargerCommGB_innerData.bmsErrorReason = 0U;
    ChargerCommGB_innerData.chargerStopReason = 0U;
    ChargerCommGB_innerData.chargerFaultReason = 0U;
    ChargerCommGB_innerData.chargerErrorReason = 0U;
    ChargerCommGB_innerData.chargeStopLastTick = 0U;
    ChargerCommGB_innerData.relayAdhesionCheckFlag = TRUE;
    ChargerCommGB_innerData.bclZeroCurSendFlag = FALSE;
    ChargerCommGB_innerData.ccsRecFlag = FALSE;
    ChargerCommGB_innerData.stopChargeDev = CHARGERCOMMGB_STOP_CHARGE_DEV_NONE;
    ChargerCommGB_innerData.bcsChargeStopSendFlag = FALSE;
    ChargerCommGB_innerData.bstSendCnt = 0U;
    ChargerCommGB_innerData.bemCurDecreaseLastTick = 0U;
    ChargerCommGB_innerData.cellVoltGroupNum = 0U;
    (void)memset(ChargerCommGB_innerData.chargerTimeoutReason, 0, CHARGERCOMMGB_CHG_TIMEOUT_BYTE_NUM);
    ChargerComm_SetChargingStatus(FALSE);
    ChargerComm_SetChargerOutputHV(0U);
    ChargerComm_SetChargerOutputHVMax(0U);
    ChargerComm_SetChargerOutputHVMin(0U);
    ChargerComm_SetChargerOutputCurrent(0);
    ChargerComm_SetChargerOutputCurrentMax(0);
    ChargerComm_SetChargerOutputCurrentMin(0);
    if (ChargerCommGB_innerData.insuIsStop)
    {
#ifdef UPC6000

#if SYSTEM_BATTERY_CELL_NUM <= 48U
        BridgeInsu_Start(BRIDGEINSU_MOS_ALWAYS_ON);
#else
        BridgeInsu_Start(BRIDGEINSU_MOS_BY_VOL);
#endif

#endif
        ChargerCommGB_innerData.insuIsStop = FALSE;
    }
}

// 用于重新启动充电
static void ChargerCommGB_RestChargerStatus(void)
{
    ChargerCommGB_ClearChargerStatusCarefully();
    ChargerCommGB_innerData.protocolVersion = CHARGERCOMMGB_PROTOCOL_VERSION_2015;
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CONNECT_WAITING;
    ChargerCommGB_innerData.timeoutCnt = 0U;
}

// Receive functions define
void ChargerCommGB_ReceiveCHMCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U;
    uint32 version = 0U;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    ChargerCommGB_innerData.communication = TRUE;
    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        ChargerCommGB_UpdateCurrentChargeType();
        if (ChargerConnectM_GetConnectMode(ChargerCommGB_innerData.currentChargeType) == CHARGECONNECTM_CONNECT_COMMUNICATION)
        {
            // ChargerCommGB_ChargerEnable();
            ChargerCommGB_SetCommunication(TRUE);
        }
        else
        {
            if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
            {
                flag = 0U;
                ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
            }
        }
    }
    if (flag != 0U)
    {
        Charge_ChargeType type = ChargerComm_GetChargeType();
        if (type != CHARGE_TYPE_NONE &&
            type != ChargerCommGB_innerData.currentChargeType)
        {
            flag = 0U;
        }
        else if (ChargerCommGB_innerData.stage > CHARGERCOMMGB_STAGE_SHAKEHAND_IDENTIFY)
        {
            flag = 0U;
        }
        else
        {
        }
    }
    if (flag != 0U)
    {
        //ChargerCommGB_CommStart();
        ChargerCommGB_SetCommunication(TRUE);
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_NORMAL);
        ChargerComm_ClrAllFaultStatus();
        if (ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_SHAKEHAND_START)
        {
            if (Length >= 3U)
            {
                version = READ_LT_UINT24(Buffer, index);
            }
            if (version == (uint32)CHARGERCOMMGB_PROTOCOL_VERSION_2015)
            {
                BridgeInsu_Stop();
                ChargerCommGB_innerData.insuIsStop = TRUE;
                (void)memset(ChargerCommGB_innerData.bmsTimeoutReason, 0, CHARGERCOMMGB_BMS_TIMEOUT_BYTE_NUM);
                ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CHM_TO_CRM);
                ChargerComm_SetProtocol(CHARGERCOMM_PROTOCOL_GB2015);
                ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_SHAKEHAND_START;
            }
        }
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommGB_ReceiveCRMCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U, identify = 0U;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    ChargerCommGB_innerData.communication = TRUE;
    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        ChargerCommGB_UpdateCurrentChargeType();
        if (ChargerConnectM_GetConnectMode(ChargerCommGB_innerData.currentChargeType) == CHARGECONNECTM_CONNECT_COMMUNICATION)
        {
            // ChargerCommGB_ChargerEnable();
            ChargerCommGB_SetCommunication(TRUE);
        }
        else
        {
            if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
            {
                flag = 0U;
                ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
            }
        }
    }
    if (flag != 0U)
    {
        Charge_ChargeType type = ChargerComm_GetChargeType();
        if (type != CHARGE_TYPE_NONE &&
            type != ChargerCommGB_innerData.currentChargeType)
        {
            flag = 0U;
        }
        else if (ChargerCommGB_innerData.stage > CHARGERCOMMGB_STAGE_PARA_CONFIG)
        {
            flag = 0U;
        }
        else
        {
        }
    }
    if (flag != 0U)
    {
        //if (ChargerCommGB_innerData.timeoutCnt > 3) break;
        //ChargerCommGB_CommStart();
        ChargerCommGB_SetCommunication(TRUE);
        ChargerComm_ClrAllFaultStatus();
        if(ChargerComm_GetCurrentRecStage() == CHARGERCOMM_STAGE_IDLE)
        {
            ChargerCommGB_ClrSelfDiagnosis();
        }
        if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CONNECT_WAITING && ChargerCommGB_innerData.timeoutCnt == 0U)
        {
            ChargerComm_SetProtocol(CHARGERCOMM_PROTOCOL_GB2011);
        }

        for(index = 0U; index < CHARGERCOMMGB_BMS_TIMEOUT_BYTE_NUM; index++)
        {
            ChargerCommGB_innerData.bmsTimeoutReason[index] = 0U;
        }
        index = 0U;
        if (Length > 0U)
        {
            identify = READ_LT_UINT8(Buffer, index);
        }
        if (identify == CHARGERCOMMGB_CHG_IDENTI_NUM)
        {
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CTS_CML);
            ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_PARA_CONFIG;
        }
        else if (identify == CHARGERCOMMGB_CHG_UN_IDENT_NUM)
        {
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CRM_AA);
            ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_SHAKEHAND_IDENTIFY;
        }
        else
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            ChargerComm_ClrChargerStatus();
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
            ChargerCommGB_innerData.bmsTimeoutReason[0] &= 0xFCU;
            ChargerCommGB_innerData.bmsTimeoutReason[0] |= CHARGERCOMMGB_REC_SPN2560_00_UNKNOWN_VALUE;
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3901);
            ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
#endif
        }
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommGB_ReceiveCTSCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
        {
            ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_PARA_CONFIG &&
            ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_CHARGE_READY)
        {
            flag = 0U;
        }
    }
    if (flag != 0U)
    {
        (void)Buffer;
        (void)Length;
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommGB_ReceiveCMLCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U;
    uint16 volt, volt_max;
    Current_CurrentType current, current_max;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
        {
            ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_PARA_CONFIG &&
            ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_CHARGE_READY)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length >= 6U)
    {
        volt_max = READ_LT_UINT16(Buffer, index);
        ChargerComm_SetChargerOutputHVMax(volt_max);
        volt = READ_LT_UINT16(Buffer, index);
        if (volt > volt_max)
        {
            volt = 0U;
        }
        ChargerComm_SetChargerOutputHVMin(volt);
        current_max = (Current_CurrentType)READ_LT_UINT16(Buffer, index);
        current_max = ChargerCommGB_CurrentToBmsCurrent(current_max);
        ChargerComm_SetChargerOutputCurrentMax(current_max);
        if (ChargerComm_GetProtocol() == CHARGERCOMM_PROTOCOL_GB2015 &&
            Length >= 8U)
        {
            current = (Current_CurrentType)READ_LT_UINT16(Buffer, index);
            current = ChargerCommGB_CurrentToBmsCurrent(current);
            if (current > current_max)
            {
                current = (Current_CurrentType)CURRENT_INVALID_VALUE;
            }
            ChargerComm_SetChargerOutputCurrentMin(current);
        }
        ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CHARGE_READY;
        ChargerCommGB_innerData.bmsChargeReadyLastTick = OSTimeGet();
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommGB_ReceiveCROCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag =1U;
    uint16 index = 0U, readyFlag;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
        {
            ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_CHARGE_READY)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length > 0U)
    {
        readyFlag = READ_LT_UINT8(Buffer, index);
        if (readyFlag == CHARGERCOMMGB_CHG_IDENTI_NUM)
        {
            if (ChargerCommGB_innerData.bmsChargeReadySendFlag == TRUE)
            {
                ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CHARGING;
            }
        }
        else if (readyFlag == CHARGERCOMMGB_CHG_UN_IDENT_NUM)
        {
            ChargerComm_RecAsyncEventType *recEvent = ChargerComm_GetRecAsyncEventPtr();
            Async_EventSetTimeout(&recEvent[1].event, CHARGERCOMMGB_REC_TIMEOUT_CRO_AA);
        }
        else
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            ChargerComm_ClrChargerStatus();
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
            ChargerCommGB_innerData.bmsTimeoutReason[1] &= 0xF3U;
            ChargerCommGB_innerData.bmsTimeoutReason[1] |= CHARGERCOMMGB_REC_CHARGER_READY_UNKNOWN_VALUE;
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3923);
            ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
#endif
        }
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommGB_ReceiveCCSCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U, chargeState;
    Current_CurrentType current;
    ChargerComm_ProtocolType type;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
        {
            ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_CHARGING)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length >= 6U)
    {
        ChargerComm_SetChargerOutputHV(READ_LT_UINT16(Buffer, index));
        current = (Current_CurrentType)READ_LT_UINT16(Buffer, index);
        current = ChargerCommGB_CurrentToBmsCurrent(current);
        ChargerComm_SetChargerOutputCurrent(current);
        ChargerComm_SetChargerChargedTime(READ_LT_UINT16(Buffer, index));
        chargeState = READ_LT_UINT8(Buffer, index);
        chargeState &= 0x03U;
        type = ChargerComm_GetProtocol();

        flag = 0U;
        if (ChargerComm_GetChargerOutputHV() && current != 0)
        {
            flag = 1U;
        }
        if (type != CHARGERCOMM_PROTOCOL_GB2015)
        {
            if (flag != 0U)
            {
                ChargerComm_SetChargingStatus(TRUE);
            }
            else
            {
                ChargerComm_SetChargingStatus(FALSE);
            }
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CCS);
            ChargerCommGB_innerData.ccsRecFlag = TRUE;
        }
        else
        {
            if (chargeState > 1U) //异常状态
            {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
                ChargerComm_SetChargingStatus(FALSE);
                ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
                ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
                ChargerCommGB_innerData.bmsTimeoutReason[2] &= 0xFCU;
                ChargerCommGB_innerData.bmsTimeoutReason[2] |= CHARGERCOMMGB_REC_CHARGER_STATUS_UNKNOWN_VALUE;
                ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3905);
#endif
            }
            else
            {
                if (flag != 0U && chargeState) //0:暂停 1:允许
                {
                    ChargerComm_SetChargingStatus(TRUE);
                }
                else
                {
                    ChargerComm_SetChargingStatus(FALSE);
                }
                ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CCS);
                ChargerCommGB_innerData.ccsRecFlag = TRUE;
            }
        }
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommGB_ReceiveCSTCbk(const uint8 *Buffer, uint16 Length)
{
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
    uint8 unkonw_state = 0U
#endif
    uint8 flag = 1U;
    uint16 index = 0U;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
        {
            ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_CHARGING &&
            ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_CHARGE_STOP)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length >= 4U)
    {
        ChargerCommGB_innerData.chargerStopReason = READ_LT_UINT8(Buffer, index);
        ChargerCommGB_innerData.chargerFaultReason = READ_LT_UINT16(Buffer, index);
        ChargerCommGB_innerData.chargerErrorReason = READ_LT_UINT8(Buffer, index);

        flag = ChargerCommGB_innerData.chargerStopReason & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_STOP_CHG_WITH_FINISH, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_STOP_CHG_WITH_FINISH);
        }
        flag = (ChargerCommGB_innerData.chargerStopReason >> 2) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_MANUAL_STOP_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_MANUAL_STOP_INDEX);
        }
        flag = (ChargerCommGB_innerData.chargerStopReason >> 4) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_FAULT_FAULT_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_FAULT_FAULT_INDEX);
        }
        flag = (ChargerCommGB_innerData.chargerStopReason >> 6) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_BMS_STOP_CHARGE_FAULT_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_BMS_STOP_CHARGE_FAULT_INDEX);
        }
        flag = (uint8)ChargerCommGB_innerData.chargerFaultReason & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_OVER_TEMPERATURE_FAULT_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_OVER_TEMPERATURE_FAULT_INDEX);
        }
        flag = (uint8)(ChargerCommGB_innerData.chargerFaultReason >> 2) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_CHAGER_CONNECTOR_FAULT_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_CHAGER_CONNECTOR_FAULT_INDEX);
        }
        flag = (uint8)(ChargerCommGB_innerData.chargerFaultReason >> 4) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_INNER_OVER_TEMPERATURE_FAULT_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_INNER_OVER_TEMPERATURE_FAULT_INDEX);
        }
        flag = (uint8)(ChargerCommGB_innerData.chargerFaultReason >> 6) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_ENERGY_TRANSIMIT_FAULT_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_ENERGY_TRANSIMIT_FAULT_INDEX);
        }
        flag = (uint8)(ChargerCommGB_innerData.chargerFaultReason >> 8) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_EMERGENCY_STOP_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_EMERGENCY_STOP_INDEX);
        }
        flag = (uint8)(ChargerCommGB_innerData.chargerFaultReason >> 10) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void) ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_FAULT_FAULT_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_FAULT_FAULT_INDEX);
        }
        flag = ChargerCommGB_innerData.chargerErrorReason & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_CURRENT_NOT_MATCH_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_CURRENT_NOT_MATCH_INDEX);
        }
        flag = (ChargerCommGB_innerData.chargerErrorReason >> 2) & 0x03U;
        if(flag != 0U)
        {
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ChargerComm_SetChargeFaultWithIndex(CHARGERCOMM_CHR_OUTPUT_VOLT_FAULT_INDEX, flag);
        }
        else
        {
            (void)ChargerComm_ClearChargerFaultWithIndex(CHARGERCOMM_CHR_OUTPUT_VOLT_FAULT_INDEX);
        }
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
        if (unkonw_state == 0U)
#endif
        {
            ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CHARGE_STOP;
            if(ChargerCommGB_innerData.stopChargeDev == CHARGERCOMMGB_STOP_CHARGE_DEV_NONE)
            {
                ChargerCommGB_innerData.stopChargeDev = CHARGERCOMMGB_STOP_CHARGE_DEV_CHARGER; //正常充电完成
            }
            else if(ChargerCommGB_innerData.stopChargeDev == CHARGERCOMMGB_STOP_CHARGE_DEV_CHARGER ||
                    ChargerCommGB_innerData.stopChargeDev == CHARGERCOMMGB_STOP_CHARGE_DEV_BMS)
            {
                if(ChargerCommGB_innerData.bstSendCnt >= 3U)
                {
                    ChargerCommGB_innerData.bstSendCnt = 0U;
                    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_STATISTIC;
                    ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CST_CSD);
                }
            }
            else
            {
            }
        }
#if CHARGERCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
        else
        {
            ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
            ChargerCommGB_innerData.bmsTimeoutReason[2] &= 0xF3U;
            ChargerCommGB_innerData.bmsTimeoutReason[2] |= CHARGERCOMMGB_REC_CHARGER_STOP_UNKNOWN_VALUE;
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3906);
        }
#endif
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommGB_ReceiveCSDCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U, temp;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
        {
            ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ChargerCommGB_innerData.stage != CHARGERCOMMGB_STAGE_STATISTIC)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length >= 4U)
    {
        temp = READ_LT_UINT16(Buffer, index);
        ChargerComm_SetChargerChargedTime(temp);
        temp = READ_LT_UINT16(Buffer, index);
        ChargerComm_SetChargerChargedPower(temp);
        ChargerCommGB_RestChargerStatus();
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
        ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CONNECT_WAITING;
        if (ChargerCommGB_innerData.stopFlag == TRUE)
        {
            ChargerCommGB_innerData.startFlag = FALSE;
        }
        if (ChargeM_BatteryChargeIsFinish() == TRUE)
        {
            ChargerCommGB_FullCharge();
        }
        else
        {
            ChargerCommGB_CommStopForRestart();
        }
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ChargerCommGB_ReceiveCEMCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    VALIDATE_PTR(Buffer, CHARGERCOMMGB_API_ID_ReceiveCHMCbk);

    if (ChargerCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType)
        {
            ChargerCommGB_SetSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
    }
    if (flag != 0U && Length >= 4U)
    {
        (void)memcpy(ChargerCommGB_innerData.chargerTimeoutReason, Buffer, 4U);
        if(0x01U == (ChargerCommGB_innerData.chargerTimeoutReason[0] & 3U))
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3921);
        }
        if(0x01U == (ChargerCommGB_innerData.chargerTimeoutReason[1] & 3U))
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3922);
        }
        if(0x01U == ((ChargerCommGB_innerData.chargerTimeoutReason[1] >> 2) & 3U))
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3923);
        }
        if(0x01U == ((ChargerCommGB_innerData.chargerTimeoutReason[2]) & 3U))
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3924);
        }
        if(0x01U == ((ChargerCommGB_innerData.chargerTimeoutReason[2] >> 2) & 3U))
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3925);
        }
        if(0x01U == ((ChargerCommGB_innerData.chargerTimeoutReason[2] >> 4) & 3U))
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3926);
        }
        if(0x01U == ((ChargerCommGB_innerData.chargerTimeoutReason[3]) & 3U))
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3927);
        }
        ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
    return;
#endif
}

void ChargerCommGB_RecCHMTimeoutCbk(void)
{
    ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CRM);
}

void ChargerCommGB_RecCRMTimeoutCbk(void)
{
    ChargerComm_StageType RecStage;
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
    RecStage = ChargerComm_GetCurrentRecStage();
    if (RecStage == CHARGERCOMM_STAGE_GB_CRM ||
        RecStage == CHARGERCOMM_STAGE_GB_CHM_TO_CRM ||
        RecStage == CHARGERCOMM_STAGE_GB_RECOMM_CRM)
    {
        ChargerComm_ClrChargerStatus();
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
        ChargerCommGB_innerData.bmsTimeoutReason[0] &= 0xFCU;
        ChargerCommGB_innerData.bmsTimeoutReason[0] |= CHARGERCOMMGB_REC_SPN2560_00_TIMEOUT_VALUE;
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3901);
    }
    else if (RecStage == CHARGERCOMM_STAGE_GB_CRM_AA)
    {
        ChargerComm_ClrChargerStatus();
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
        ChargerCommGB_innerData.bmsTimeoutReason[0] &= 0xF3U;
        ChargerCommGB_innerData.bmsTimeoutReason[0] |= CHARGERCOMMGB_REC_SPN2560_AA_TIMEOUT_VALUE;
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3902);
    }
    else
    {
    }
    ChargerCommGB_SetCommunication(FALSE);
}

void ChargerCommGB_RecCMLTimeoutCbk(void)
{
    ChargerCommGB_SetCommunication(FALSE);
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
    ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
    ChargerCommGB_innerData.bmsTimeoutReason[1] &= 0xFCU;
    ChargerCommGB_innerData.bmsTimeoutReason[1] |= CHARGERCOMMGB_REC_CAPABILITY_TIMEOUT_VALUE;
    ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3903);
}

void ChargerCommGB_RecCROTimeoutCbk(void)
{
    ChargerCommGB_SetCommunication(FALSE);
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
    ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
    ChargerCommGB_innerData.bmsTimeoutReason[1] &= 0xF3U;
    ChargerCommGB_innerData.bmsTimeoutReason[1] |= CHARGERCOMMGB_REC_CHARGER_READY_TIMEOUT_VALUE;
    ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3904);
}

void ChargerCommGB_RecCROAATimeoutCbk(void)
{
    ChargerCommGB_SetCommunication(FALSE);
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
    ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
    ChargerCommGB_innerData.bmsTimeoutReason[1] &= 0xF3U;
    ChargerCommGB_innerData.bmsTimeoutReason[1] |= CHARGERCOMMGB_REC_CHARGER_READY_TIMEOUT_VALUE;
    ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3904);
}

void ChargerCommGB_RecCCSTimeoutCbk(void)
{
    ChargerCommGB_SetCommunication(FALSE);
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
    ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
    ChargerCommGB_innerData.bmsTimeoutReason[2] &= 0xFCU;
    ChargerCommGB_innerData.bmsTimeoutReason[2] |= CHARGERCOMMGB_REC_CHARGER_STATUS_TIMEOUT_VALUE;
    ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3905);
}

void ChargerCommGB_RecCSTTimeoutCbk(void)
{
    if (ChargerCommGB_innerData.stage == CHARGERCOMMGB_STAGE_CHARGE_STOP)
    {
        ChargerCommGB_SetCommunication(FALSE);
        ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
        ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
        ChargerCommGB_innerData.bmsTimeoutReason[2] &= 0xF3U;
        ChargerCommGB_innerData.bmsTimeoutReason[2] |= CHARGERCOMMGB_REC_CHARGER_STOP_TIMEOUT_VALUE;
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3906);
    }
}

void ChargerCommGB_RecCSDTimeoutCbk(void)
{
    ChargerCommGB_SetCommunication(FALSE);
    ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_FAULT;
    ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CEM);
    ChargerCommGB_innerData.bmsTimeoutReason[3] &= 0xFCU;
    ChargerCommGB_innerData.bmsTimeoutReason[3] |= CHARGERCOMMGB_REC_CHARGER_STATIS_TIMEOUT_VALUE;
    ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_GB_SPN3907);
}

//GB策略实现
ChargerComm_SelfDiagnosisType ChargerCommGB_GetSelfDiagnosis(void)
{
    ChargerComm_SelfDiagnosisType current_num;
    imask_t mask;

    Irq_Save(mask);
    current_num = ChargerCommGB_innerData.selfDiag;
    Irq_Restore(mask);

    return current_num;
}

static void ChargerCommGB_SetSelfDiagnosis(ChargerComm_SelfDiagnosisType diagnosis)
{
    imask_t mask;

    Irq_Save(mask);
    if (ChargerCommGB_innerData.selfDiag != diagnosis)
    {
        ChargerCommGB_innerData.selfDiag = diagnosis;
    }
    Irq_Restore(mask);
}

static void ChargerCommGB_ClrSelfDiagnosis(void)
{
    imask_t mask;

    Irq_Save(mask);
    ChargerCommGB_innerData.selfDiag = CHARGERCOMM_SELFDIAG_NORMAL;
    Irq_Restore(mask);
}

static void ChargerCommGB_UpdateSelfDiagnosis(ChargerComm_SelfDiagnosisType diagnosis)
{
    if(diagnosis >= CHARGERCOMM_SELFDIAG_CHR_GB_SPN3902 && diagnosis <= CHARGERCOMM_SELFDIAG_CHR_GB_SPN3927)
    {
        ChargerCommGB_TimeoutCntUpdate();
    }
    if(ChargerCommGB_GetSelfDiagnosis() == CHARGERCOMM_SELFDIAG_NORMAL)
    {
        ChargerCommGB_SetSelfDiagnosis(diagnosis);
    }
}


static void ChargerCommGB_UpdateSelfDiagnosisWithOthers(void)
{
    if(ChargeM_DiagnosisIsNormal() != E_OK)
    {
        if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_HV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HV); //单体高压
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HV); //单体高压
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_LV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LV); //单体低压
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_LV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LV); //单体低压
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_HT) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HT); //单体高温
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HT) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HT); //单体高温
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_LT) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LT); //单体低温
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_LT) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LT); //单体低温
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_DT) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_DT); //单体温差
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_DT) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_DT); //单体温差
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_DV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_DV); //单体压差
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_DV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_DV); //单体压差
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_INTER_COMM) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_SLAVE_COMM); //内网通信
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_LSOC) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LSOC); //SOC低
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_HSOC) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HSOC); //SOC高
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_LEAK) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LEAK); //系统漏电
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_HTV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HTV); //总压高
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HTV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HTV); //总压高
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_LTV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LTV); //总压低
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_LTV) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LTV); //总压低
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_VOLT_LINE) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_VOLT_LINE); //电压排线脱落
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_TEMP_LINE) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_TEMP_LINE); //温感排线脱落
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DC_CHG_OC) == CHARGEM_CHARGE_DISABLE &&
            ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_OCC); //充电过流
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_AC_CHG_OC) == CHARGEM_CHARGE_DISABLE &&
            ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_AC)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_OCC); //充电过流
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_OC) == CHARGEM_CHARGE_DISABLE)
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_ODC); //放电过流
        }
        else
        {
            ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_OTHERS); //其他故障
        }
    }
}

static void ChargerCommGB_TimeoutCntUpdate(void)
{
    if(ChargerCommGB_innerData.timeoutCntSwitch == FALSE)
    {
        ChargerCommGB_innerData.timeoutCntSwitch = TRUE;
        ChargerCommGB_innerData.timeoutCnt++;
    }
}

void ChargerCommGB_StartRecStageTimeout(uint8 channel, ChargerComm_StageType currentStage)
{
    uint16 timeout;
    const ChargerComm_RecIPduCfgType* cfg;
    ChargerComm_RecAsyncEventType *recEvent;

    if (channel < CHARGERCOMM_MONITOR_REC_MSG_NUM_PER_STAGE &&
        currentStage >= CHARGERCOMM_STAGE_GB_START &&
        currentStage <= CHARGERCOMM_STAGE_GB_STOP)
    {
        cfg = ChargerComm_GetRecStageCfg(currentStage);
        recEvent = ChargerComm_GetRecAsyncEventPtr();
        VALIDATE_PTR(cfg, CHARGERCOMMGB_API_ID_StartRecStageTimeout);
        VALIDATE_PTR(recEvent, CHARGERCOMMGB_API_ID_StartRecStageTimeout);

        switch(currentStage)
        {
            case CHARGERCOMM_STAGE_IDLE:
                break;
            case CHARGERCOMM_STAGE_GB_START:
            case CHARGERCOMM_STAGE_GB_CHM_TO_CRM:
            case CHARGERCOMM_STAGE_GB_RECOMM_CRM:
            case CHARGERCOMM_STAGE_GB_CRM_AA:
            case CHARGERCOMM_STAGE_GB_CTS_CML:
            case CHARGERCOMM_STAGE_GB_CRO:
            case CHARGERCOMM_STAGE_GB_CCS:
            case CHARGERCOMM_STAGE_GB_CST_CSD:
            case CHARGERCOMM_STAGE_GB_CEM:
            case CHARGERCOMM_STAGE_GB_CRM:
            case CHARGERCOMM_STAGE_GB_FULLCHARGE:
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
                    timeout = CHARGERCOMMGB_REC_TIMEOUT_DEFAULT;
                }
                Async_EventSetTimeout(&recEvent[channel].event, timeout);
                break;
            case CHARGERCOMM_STAGE_USER_START:
            case CHARGERCOMM_STAGE_MAX:
            default:
                // do nothing
                break;
        }
    }
#if ( CHARGERCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

static Current_CurrentType ChargerCommGB_CurrentToBmsCurrent(Current_CurrentType cur)
{
    if(cur >= 0)
    {
        cur = -1*(cur - (sint16)CHARGERCOMMGB_CURRENT_OFFSET);
        if (cur < 0)
        {
            cur = (Current_CurrentType)CURRENT_INVALID_VALUE;
        }
    }
    else
    {
        cur = (Current_CurrentType)CURRENT_INVALID_VALUE;
    }
    return cur;
}

static Current_CurrentType ChargerCommGB_CurrentFromBmsCurrent(Current_CurrentType cur)
{
    if(cur > (Current_CurrentType)CHARGERCOMMGB_CURRENT_OFFSET)
    {
        cur = (Current_CurrentType)CHARGERCOMMGB_CURRENT_OFFSET;
    }
    cur = -1*cur + (Current_CurrentType)CHARGERCOMMGB_CURRENT_OFFSET;
    if (cur < 0)
    {
        cur = 0;
    }
    return cur;
}


static void ChargerCommGB_GetDecreaseCurrent(Current_CurrentType new_current, Current_CurrentType *current)
{
    Current_CurrentType value;
    INT32U now_tick;

    if (current != NULL)
    {
        value = *current;
        now_tick = OSTimeGet();
        if (new_current >= value)
        {
            *current = new_current;
        }
        else
        {
            if (MS_GET_INTERNAL(ChargerCommGB_innerData.chargeCurrentLastTick, now_tick) >= 1000U)
            {
                Current_CurrentType diff = value - new_current;
                ChargerCommGB_innerData.chargeCurrentLastTick = now_tick;
                if(diff > CHARGERCOMMGB_CURRENT_DECREASE_MAX_PER_S)
                {
                    value -= CHARGERCOMMGB_CURRENT_DECREASE_MAX_PER_S;
                }
                else
                {
                    value = new_current;
                }
                *current = value;
            }
        }
    }
}

uint8 ChargerCommGB_CheckChargeReq(uint16 delay) //return 0-waitting 1-ready 2-fault
{
    uint8 flag;
    uint16 data, hvMax;
    uint16 reason = 0U;
    Diagnosis_ItemType item;
    uint8 version2015 = FALSE;

    //充电停止原因
    //if(SOC_TO_PERCENT(bcu_get_SOC()) >= 100)//SOC过大
    //    temp |= 0x01;
    if (ChargerComm_GetProtocol() == CHARGERCOMM_PROTOCOL_GB2015)
    {
        version2015 = TRUE;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HTV) == CHARGEM_CHARGE_DISABLE)//达到总压设定值
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HTV);
        reason |= 0x04U;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HV) == CHARGEM_CHARGE_DISABLE) //达到单体电压设定值
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HV);
        reason |= 0x10U;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_FULL_CHARGE) == CHARGEM_CHARGE_DISABLE) //满充
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_FULL_CHARGE);
        reason |= 0x10U;
    }
    ChargerCommGB_innerData.bmsStopReason = (uint8)reason;
    //充电故障原因
    reason = 0U;
    if (ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
    {
        item = DIAGNOSIS_ITEM_DC_CHG_OC;
    }
    else
    {
        item = DIAGNOSIS_ITEM_AC_CHG_OC;
    }
    if(ChargeM_GetDiagnosisChargeCtlFlag(item) == CHARGEM_CHARGE_DISABLE) //充电过流
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_OCC);
        reason |= 0x01U;
    }
    data = Statistic_GetBcu100mvTotalVoltage();
    hvMax = ChargerComm_GetChargerOutputHVMax();
    flag = 0U;
    if (hvMax > 0U && data > hvMax)
    {
        flag = 1U;
    }
    if(data < ChargerComm_GetChargerOutputHVMin() || flag != 0U)
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_TV_EXCEPTION);
        reason |= 0x04U;
    }
    ChargerCommGB_innerData.bmsErrorReason = (uint8)reason;
    //充电错误原因
    reason = 0U;
    if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_LEAK) == CHARGEM_CHARGE_DISABLE)  //漏电
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_LEAK);
        reason |= 0x01U;
    }
    // 输出连接器过温故障
    flag = FALSE;
    if (ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
    {
        if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHGSCKTMP_DC_POSITIVE) == CHARGEM_CHARGE_DISABLE)
        {
            flag = TRUE;
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHGSCKTMP_DC_NEGATIVE) == CHARGEM_CHARGE_DISABLE)
        {
            flag = TRUE;
        }
        else
        {
        }
    }
    else
    {
        if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHGSCKTMP_AC_AL) == CHARGEM_CHARGE_DISABLE)
        {
            flag = TRUE;
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHGSCKTMP_AC_BN) == CHARGEM_CHARGE_DISABLE)
        {
            flag = TRUE;
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHGSCKTMP_AC_C) == CHARGEM_CHARGE_DISABLE)
        {
            flag = TRUE;
        }
        else
        {
        }
    }
    if(flag != FALSE)
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_OTHERS);
        reason |= 0x04U;
    }
    if(ChargeConnectM_GetDCACConnectType() != ChargerCommGB_innerData.currentChargeType) // 充电连接器故障
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_CHR_NOT_CONNECT);
        reason |= 0x40U;
    }
    if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HT) == CHARGEM_CHARGE_DISABLE) //过温
    {
        ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_HT);
        reason |= 0x100U;
    }
    if(version2015 == TRUE)
    {
        RelayM_FunctionType type;
        if (ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
        {
            type = ChargerComm_ConfigInfo.DC_RelayType;
        }
        else
        {
            type = ChargerComm_ConfigInfo.AC_RelayType;
        }
        if(type != RELAYM_FN_NONE)
        {
            if (!RELAYM_DIAGNOSIS_IS_NORMAL_IGNORE_CHECKING(RelayM_GetDiagnosisStatus(type))) //继电器异常
            {
                ChargerCommGB_UpdateSelfDiagnosis(CHARGERCOMM_SELFDIAG_BMS_RELAY_FAULT);
                reason |= 0x400U;
            }
        }
        //检测点2电压检测故障
    }
    if(//g_guobiao_comm_timeout_cnt >= GUOBIAO_COMM_ABORT_TIMEOUT_TIMES ||
        (ChargeM_ChargeIsAllowed() != E_OK &&
        reason==0U &&
        ChargerCommGB_innerData.bmsStopReason==0U &&
        ChargerCommGB_innerData.bmsErrorReason==0U)) //其他故障
    {
        //if(g_guobiao_comm_timeout_cnt >= GUOBIAO_COMM_ABORT_TIMEOUT_TIMES)
        //    ChargerCommGB_UpdateSelfDiagnosis(kGBChgFaultOverTimeoutTimes);
        //else
            ChargerCommGB_UpdateSelfDiagnosisWithOthers();
        if(version2015 == TRUE)
        {
            reason |= 0x4000U;
        }
        else
        {
            reason |= 0x400U;
        }
    }
    ChargerCommGB_innerData.bmsFaultReason = reason;
    flag = 1U;
    if(ChargerCommGB_innerData.bmsStopReason || ChargerCommGB_innerData.bmsFaultReason || ChargerCommGB_innerData.bmsErrorReason)
    {
        if (delay)
        {
            uint32 now = OSTimeGet();
            if(ChargerCommGB_innerData.chargeStopLastTick == 0U)
            {
                ChargerCommGB_innerData.chargeStopLastTick = now;
            }
            if(MS_GET_INTERNAL(ChargerCommGB_innerData.chargeStopLastTick, now) >= delay)
            {
                flag = 2U;
            }
            else
            {
                flag = 0U;
            }
        }
        else
        {
            flag = 2U;
        }
    }
    else
    {
        ChargerCommGB_innerData.chargeStopLastTick = 0U;
    }
    return flag;
}

uint8 ChargerCommGB_ChargeIsFaultStop(void)
{
    uint8 flag = FALSE;

    if (ChargerCommGB_innerData.bmsErrorReason ||
        ChargerCommGB_innerData.bmsFaultReason)
    {
        flag = TRUE;
    }
    return flag;
}

static uint8 ChargerCommGB_ChargeIsStop(void)
{
    uint8 flag = FALSE;
    if(ChargerCommGB_CheckChargeReq(100U) == 2U)
    {
        flag = TRUE;
    }
    return flag;
}

static uint8 ChargerCommGB_IsChargingReady(void) // return 0-waitting 1-ready 2-fault
{
    uint8 flag = 0U, ret = 0xFFU;
    RelayM_FunctionType relayType;

    if (ChargerCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
    {
        relayType = ChargerComm_ConfigInfo.DC_RelayType;
    }
    else
    {
        relayType = ChargerComm_ConfigInfo.AC_RelayType;
    }

#if CHARGERCOMMGB_RELAY_ADHESION_CHECK_EN == STD_ON
    if (relayType != RELAYM_FN_NONE)
    {
        if (RelayM_RelayHvIsMonitor(relayType) == E_OK)
        {
            if (RelayM_GetActualStatus(RELAYM_FN_POSITIVE_DISCHRGE) != RELAYM_ACTUAL_ON)
            {
                if (RelayM_GetActualStatus(RELAYM_FN_PRECHARGE) != RELAYM_ACTUAL_ON)
                {
                    RelayM_DiagnosisStatusType status;
                    if(ChargerCommGB_innerData.relayAdhesionCheckFlag == TRUE/* &&
                        bcu_get_insulation_work_state()!=kInsulationWorkStateNotConnected &&
                        bcu_get_insulation_work_state()!=kInsulationWorkStateVoltExcept*/)
                    {
                        ChargerCommGB_innerData.relayAdhesionCheckFlag = FALSE;
                        (void)RelayM_StartAdhesiveDetect(relayType, NULL); //TODO 未完成粘连检测功能
                    }
                    status = RelayM_GetDiagnosisStatus(relayType);
                    if (RELAYM_DIAGNOSIS_IS_CHECKING(status))
                    {
                        ret = 0U;
                    }
                }
            }
        }
    }
    if (ret == 0xFFU)
#endif
    {
        if (UserStartegy_ChargeIsAllow() == TRUE)
        {
            flag = ChargerCommGB_CheckChargeReq(500U);
        }
        if (flag == 1U)
        {
            ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERGB_READY_RELAY_INDEX, CHARGEM_CHARGE_ENABLE);
            if (relayType == RELAYM_FN_NONE)
            {
                ret = 1U;
            }
            else if (UserStartegy_GBChargeRelayIsReady(relayType) == TRUE)
            {
                ret = 1U;
            }
            else
            {
            }
        }
        else if (flag == 2U)
        {
            ret = 2U;
        }
        else
        {
        }
    }
    if (ret == 0xFFU)
    {
        ret = 0U;
    }
    return ret;
}

static void ChargerCommGB_ChargingReadyCheck(void)
{
    uint8 flag = ChargerCommGB_IsChargingReady();
    uint32 now = OSTimeGet();

    if(flag == 1U)
    {
        ChargerCommGB_innerData.bmsChargeReady = CHARGERCOMMGB_BMS_CHARGE_READY;
    }
    else
    {
        if(MS_GET_INTERNAL(ChargerCommGB_innerData.bmsChargeReadyLastTick, now) >= 15000U || //准备就绪超时进入中止充电阶段
            flag == 2U) //故障
        {
            ChargerCommGB_innerData.stage = CHARGERCOMMGB_STAGE_CHARGE_STOP;
            ChargerComm_TriggerNewRecStage(CHARGERCOMM_STAGE_GB_CST_CSD);
        }
        else
        {
            ChargerCommGB_innerData.bmsChargeReady = CHARGERCOMMGB_BMS_CHARGE_NOT_READY;
        }
    }
}
