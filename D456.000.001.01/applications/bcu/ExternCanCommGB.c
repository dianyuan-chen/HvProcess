/**
 * \file ExternCanCommGB.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 扩展CAN国标通信文件.
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
#include "ExternCanCommGB.h"
#include "ParameterM.h"
#include "Det.h"
#include "ChargeM.h"
#include "AppInfo.h"
#include "Statistic.h"
#include "PwmCapture_Lcfg.h"
#include "PowerM.h"
#include "UserStrategy.h"
#include "ExternCanComm_LCfg.h"
#include "TemperatureM.h"
#include "BridgeInsu.h"
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
#include "Modules.h"
#endif

#define EXTERNCANCOMMGB_E_PARAM_INVALID_PTR           0U
#define EXTERNCANCOMMGB_E_PARAM_INVALID_CHARGE_TYPE   1U

#define EXTERNCANCOMMGB_API_ID_Init                   0U

#define EXTERNCANCOMMGB_API_ID_GetBHMDataCbk          20U

#define EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk          100U

#define EXTERNCANCOMMGB_API_ID_StartRecStageTimeout   200U
#define EXTERNCANCOMMGB_API_ID_IsChargingReady        201U

#define EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN      0U

#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE_PTR(_ptr, _api) \
    if (_ptr == NULL) { \
        Det_ReportError(MODULE_ID_EXTERNCANCOMM_GB, 0U, _api, EXTERNCANCOMMGB_E_PARAM_INVALID_PTR); \
        goto cleanup; \
    }

#define VALIDATE_CHARGE_TYPE(_type, _api) \


#else

#define VALIDATE_PTR(_ptr, _api)
#endif

static ExternCanCommGB_InnerDataType ExternCanCommGB_innerData;

static void ExternCanCommGB_ReadConfigPara(void);
void ExternCanCommGB_CommStart(void);
void ExternCanCommGB_CommStop(void);
static void ExternCanCommGB_SetCommunication(uint8 flag);
static void ExternCanCommGB_SetCurrentChargeType(Charge_ChargeType type);
static void ExternCanCommGB_SetSelfDiagnosis(ExternCanComm_SelfDiagnosisType diagnosis);
static void ExternCanCommGB_ClrSelfDiagnosis(void);
static void ExternCanCommGB_UpdateSelfDiagnosis(ExternCanComm_SelfDiagnosisType diagnosis);
static void ExternCanCommGB_TimeoutCntUpdate(void);
static void ExternCanCommGB_ClearChargerStatusCarefully(void);
static void ExternCanCommGB_RestChargerStatus(void);
static Current_CurrentType ExternCanCommGB_CurrentToBmsCurrent(Current_CurrentType cur);
static Current_CurrentType ExternCanCommGB_CurrentFromBmsCurrent(Current_CurrentType cur);
static void ExternCanCommGB_GetDecreaseCurrent(Current_CurrentType new_current, Current_CurrentType *current);
static uint8 ExternCanCommGB_ChargeIsStop(void);
static uint8 ExternCanCommGB_IsChargingReady(void);
static void ExternCanCommGB_ChargingReadyCheck(void);

void ExternCanCommGB_Init(void)
{
    ExternCanCommGB_innerData.startFlag = FALSE;
    ExternCanCommGB_innerData.relayAdhesionCheckFlag = TRUE;
    ExternCanCommGB_innerData.protocolVersion = EXTERNCANCOMMGB_PROTOCOL_VERSION_2015;
    ExternCanCommGB_innerData.chargeTypeMask = 0U;
    ExternCanCommGB_innerData.currentChargeType = CHARGE_TYPE_NONE;
    if (EXTERNCANCOMM_PROTOCOL_IS_GB(ExternCanComm_ConfigInfo.Protocol))
    {
        ExternCanCommGB_ReadConfigPara();
        (void)ExternCanComm_SendIPduRegister(&ExternCanComm_IPduSendConfigInfo[12], EXTERNCANCOMM_GB_CHR_TX_PDUID_NUM);
        OSTimeDly(2U);
    }
}

static void ExternCanCommGB_ReadConfigPara(void)
{
    ExternCanComm_ProtocolType protocol;

    if (ChargeM_ConfigInfo.DC_Para.enable == STD_ON)
    {
        protocol = ExternCanComm_ConfigInfo.Protocol;
        if (EXTERNCANCOMM_PROTOCOL_IS_GB(protocol))
        {
            ExternCanCommGB_SetChargeType(CHARGE_TYPE_DC);
            ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
        }
    }
}

void ExternCanCommGB_SetChargeType(Charge_ChargeType type)
{
    imask_t mask;

    Irq_Save(mask);
    ExternCanCommGB_innerData.chargeTypeMask |= ((uint16)1U << type);
    Irq_Restore(mask);
}

static boolean ExternCanCommGB_ChargeTypeIsOn(Charge_ChargeType type)
{
    boolean flag = FALSE;
    uint16 typeMask;
    imask_t mask;

    if (type != CHARGE_TYPE_NONE)
    {
        Irq_Save(mask);
        typeMask = ExternCanCommGB_innerData.chargeTypeMask;
        Irq_Restore(mask);

        if (typeMask & ((uint16)1U << type))
        {
            flag = TRUE;
        }
    }
    return flag;
}
/*
static boolean ExternCanCommGB_ChargeTypeIsNone(void)
{
    boolean flag = FALSE;
    uint16 typeMask;
    imask_t mask;

    Irq_Save(mask);
    typeMask = ExternCanCommGB_innerData.chargeTypeMask;
    Irq_Restore(mask);

    if (typeMask == 0U)
    {
        flag = TRUE;
    }
    return flag;
}
*/
static void ExternCanCommGB_SetCurrentChargeType(Charge_ChargeType type)
{
    imask_t mask;

    Irq_Save(mask);
    ExternCanCommGB_innerData.currentChargeType = type;
    Irq_Restore(mask);
}

Charge_ChargeType ExternCanCommGB_GetCurrentChargeType(void)
{
    imask_t mask;
    Charge_ChargeType type;

    Irq_Save(mask);
    type = ExternCanCommGB_innerData.currentChargeType;
    Irq_Restore(mask);
    return type;
}

static void ExternCanCommGB_UpdateCurrentChargeType(void)
{
    boolean flag = FALSE;
    if (ExternCanCommGB_GetCurrentChargeType() == CHARGE_TYPE_NONE)
    {
        if (ExternCanCommGB_ChargeTypeIsOn(CHARGE_TYPE_DC) == TRUE)
        {
            if (ChargeConnectM_GetDC2ConnectStatus(CHARGE_TYPE_DC) == E_OK)
            {
                ExternCanCommGB_SetCurrentChargeType(CHARGE_TYPE_DC);
                flag = TRUE;
            }
        }
        if (!flag)
        {
            ExternCanCommGB_SetCurrentChargeType(CHARGE_TYPE_NONE);
        }
    }
}

void ExternCanCommGB_ChargerEnable(void)
{
    imask_t mask;

    Irq_Save(mask);
    ExternCanCommGB_innerData.startFlag = TRUE;
    ExternCanCommGB_innerData.stopFlag = FALSE;
    Irq_Restore(mask);
    ExternCanCommGB_CommStart();
}

void ExternCanCommGB_ChargerDisable(void)
{
    imask_t mask;
    ExternCanCommGB_ChargeStageType stage;

    Irq_Save(mask);
    ExternCanCommGB_innerData.stopFlag = TRUE;
    stage = ExternCanCommGB_innerData.stage;
    Irq_Restore(mask);

    if (stage <= EXTERNCANCOMMGB_STAGE_CONNECT_WAITING || //if GB is commnicated, then stop
        stage >= EXTERNCANCOMMGB_STAGE_FAULT)
    {
        ExternCanCommGB_CommStop();
    }
}

void ExternCanCommGB_CommStart(void)
{
    Charge_ChargeType currentType;
    ExternCanComm_StageType stage = ExternCanComm_GetCurrentRecStage();

    ExternCanCommGB_UpdateCurrentChargeType();
    currentType = ExternCanCommGB_GetCurrentChargeType();
    if (ExternCanComm_GetChargeType() == CHARGE_TYPE_NONE &&
        currentType != CHARGE_TYPE_NONE &&
        ExternCanCommGB_innerData.startFlag == TRUE &&
        stage == EXTERNCANCOMM_STAGE_IDLE)
    {
        if (currentType == CHARGE_TYPE_DC)
        {
            PowerM_Reset(POWERM_CUR_CHARGE_DC);
        }
        else
        {
            PowerM_Reset(POWERM_CUR_CHARGE_AC);
        }
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
        ExternCanComm_SetChargeType(currentType);
        ExternCanComm_InitChargeVoltAndCurrent();
        ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_COMM_WAITING);
    }
}

void ExternCanCommGB_CommStop(void)
{
    imask_t mask;
    Charge_ChargeType currentType;
    ExternCanComm_StageType stage = ExternCanComm_GetCurrentRecStage();

    Irq_Save(mask);
    ExternCanCommGB_innerData.communication = FALSE;
    ExternCanComm_ResetCommunicationStatus();
    ExternCanCommGB_RestChargerStatus();
    currentType = ExternCanCommGB_GetCurrentChargeType();
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
    ExternCanCommGB_SetCurrentChargeType(CHARGE_TYPE_NONE);
    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CONNECT_WAITING;
    if (ExternCanCommGB_innerData.stopFlag == TRUE)
    {
        ExternCanCommGB_innerData.startFlag = FALSE;
        ExternCanCommGB_innerData.stopFlag = FALSE;
    }
    if (stage >= EXTERNCANCOMM_STAGE_GB_START && stage <= EXTERNCANCOMM_STAGE_GB_STOP)
    {
        ExternCanComm_ClrChargeStatus();
        ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_IDLE);
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
    }
    Irq_Restore(mask);
}

static void ExternCanCommGB_CommStopForRestart(void)
{
    imask_t mask;

    Irq_Save(mask);
    if (ChargeConnectM_ConfigInfo.DC2_Para.type == CHARGECONNECTM_CONNECT_COMMUNICATION ||
        ExternCanCommGB_innerData.stopFlag == TRUE)
    {
        // ExternCanCommGB_CommStop();
    }
    else
    {
        ExternCanCommGB_ClearChargerStatusCarefully();
        ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_RECOMM_CRM);
        ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CONNECT_WAITING;
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
    }
    Irq_Restore(mask);
}

uint8 ExternCanCommGB_CommIsStart(void)
{
    return ExternCanCommGB_innerData.startFlag;
}

static void ExternCanCommGB_SetCommunication(uint8 flag)
{
    ExternCanCommGB_innerData.communication = flag;
    ExternCanComm_SetCommunicationStatus(flag);
}

uint8 ExternCanCommGB_IsCommunication(void)
{
    return ExternCanCommGB_innerData.communication;
}

//Send functions define
Std_ReturnType ExternCanCommGB_BHMSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargeConnectM_GetDC2ConnectType() == ExternCanCommGB_innerData.currentChargeType)
            {
                if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_SHAKEHAND_START)
                {
                    res = E_OK;
                }
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBHMDataCbk(uint8 *Buffer, uint16 *Length)
{
    App_Tv100mvType volt;
    uint16 index = 0U;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    volt = ChargeM_GetChargeDisableTriggerPara(DIAGNOSIS_ITEM_CHG_HTV, 0U);
    if (Statistic_TotalVoltageIsValid(volt))
    {
        volt += 100U;
    }
    WRITE_LT_UINT16(Buffer, index, volt);//最高允许充电电压
    *Length = index;
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BRMSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ChargeConnectM_GetDC2ConnectType() == ExternCanCommGB_innerData.currentChargeType)
            {
                if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_SHAKEHAND_IDENTIFY)
                {
                    res = E_OK;
                }
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBRMDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 temp = 0U;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    WRITE_LT_UINT24(Buffer,
        index,
        ExternCanComm_GetProtocol() == EXTERNCANCOMM_PROTOCOL_GB2015 ? EXTERNCANCOMMGB_PROTOCOL_VERSION_2015 : EXTERNCANCOMMGB_PROTOCOL_VERSION_2011);//协议版本号
    WRITE_LT_UINT8(Buffer, index, BatteryInfo_BaseConfigInfo.Type);//电池类型
    WRITE_LT_UINT16(Buffer, index, BatteryInfo_BaseConfigInfo.NominalCap);//额定容量
    WRITE_LT_UINT16(Buffer, index, BatteryInfo_BaseConfigInfo.NominalTotalVolt);//额定总压
    WRITE_LT_UINT8(Buffer, index, 'U');//厂商名称
    WRITE_LT_UINT8(Buffer, index, 'D');//厂商名称
    WRITE_LT_UINT8(Buffer, index, 'A');//厂商名称
    WRITE_LT_UINT8(Buffer, index, 'N');//厂商名称
    WRITE_LT_UINT32(Buffer, index, EXTERNCANCOMMGB_LONG_VALUE_DEFAULT);//电池组序号
    WRITE_LT_UINT24(Buffer, index, EXTERNCANCOMMGB_3_BYTES_VALUE_DEFAULT);//电池组生产日期
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_DISCHARGE_CNT_INDEX, &temp);
    WRITE_LT_UINT16(Buffer, index, temp);//电池组充放电次数
    WRITE_LT_UINT8(Buffer, index, 0x00);//电池组充放电次数
    WRITE_LT_UINT8(Buffer, index, EXTERNCANCOMMGB_BYTE_VALUE_DEFAULT);//电池组产权标识
    WRITE_LT_UINT8(Buffer, index, EXTERNCANCOMMGB_BYTE_VALUE_DEFAULT);//保留
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
    if(ExternCanComm_GetProtocol() == EXTERNCANCOMM_PROTOCOL_GB2015)
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
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BCPSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_PARA_CONFIG)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBCPDataCbk(uint8 *Buffer, uint16 *Length)
{
    App_Tv100mvType volt;
    uint16 index = 0U, temp;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    temp = ChargeM_GetChargeDisableTriggerPara(DIAGNOSIS_ITEM_CHG_HV, 0U);
    if (temp != 0xFFFFU)
    {
        temp += 20U;
    }
    WRITE_LT_UINT16(
            Buffer,
            index,
            MV_TO_10MV(temp));//最高允许充电单体电压
    if (ExternCanCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
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
        ExternCanCommGB_CurrentFromBmsCurrent((Current_CurrentType)temp));//最高允许充电电流
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
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BROSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CHARGE_READY)
            {
               res = E_OK;
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBRODataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint8 flag;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    flag = ExternCanCommGB_innerData.bmsChargeReady;
    WRITE_LT_UINT8(Buffer, index, flag);//充电准备就绪状态
    if(flag == EXTERNCANCOMMGB_BMS_CHARGE_READY)
    {
        ExternCanCommGB_innerData.bmsChargeReadySendFlag = TRUE;
        if (ExternCanComm_GetCurrentRecStage() < EXTERNCANCOMM_STAGE_GB_CRO)
        {
            if (ExternCanCommGB_innerData.insuIsStop)
            {
                BridgeInsu_Start(BRIDGEINSU_MOS_BY_VOL);
                ExternCanCommGB_innerData.insuIsStop = FALSE;
            }
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CRO);
        }
    }
    ExternCanCommGB_ChargingReadyCheck();
    *Length = index;
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BCLSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CHARGING)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBCLDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 Volt, VoltMax, VoltMin;
    uint32 address;
    Current_CurrentType Current, CurrentMax/*, CurrentMin */;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    if (ExternCanComm_GetCurrentRecStage() < EXTERNCANCOMM_STAGE_GB_CCS)
    {
        ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CCS);
    }
    Volt = UserStrategy_GetDC2ChargeVoltMax();
    ExternCanComm_SetChargeVoltMax(Volt);
    VoltMax = ExternCanComm_GetChargerOutputHVMax();
    VoltMin = ExternCanComm_GetChargerOutputHVMin();
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
    if (ExternCanCommGB_ChargeIsStop())
    {
        if(ExternCanCommGB_innerData.stopChargeDev == EXTERNCANCOMMGB_STOP_CHARGE_DEV_NONE)
        {
            ExternCanCommGB_innerData.stopChargeDev = EXTERNCANCOMMGB_STOP_CHARGE_DEV_BMS;
        }
        if(ExternCanCommGB_innerData.bclZeroCurSendFlag == TRUE && ExternCanCommGB_innerData.bcsChargeStopSendFlag == TRUE)
        {
            ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CHARGE_STOP;
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CST_CSD);
        }
    }
    if(!(ExternCanCommGB_innerData.bmsStopReason || ExternCanCommGB_innerData.bmsFaultReason || ExternCanCommGB_innerData.bmsErrorReason))
    {
        Current = UserStrategy_GetDC2ChargeCurrentMax();
        if (Current < 0)
        {
            Current = 0;
        }
        CurrentMax = ExternCanComm_GetChargerOutputCurrentMax();
        // CurrentMin = ExternCanComm_GetChargerOutputCurrentMin();
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
        CurrentMax = ChargeConnectM_GetChargeCurrentMax(ExternCanCommGB_innerData.currentChargeType);
        if(Current > CurrentMax)
        {
            Current = CurrentMax;
            ExternCanCommGB_innerData.chargeCurrentLast = Current;
        }
        else
        {
            ExternCanCommGB_GetDecreaseCurrent(Current, &ExternCanCommGB_innerData.chargeCurrentLast);
        }
    }
    else
    {
        ExternCanCommGB_innerData.chargeCurrentLast = 0;
        ExternCanCommGB_innerData.bclZeroCurSendFlag = TRUE;
    }
    ExternCanComm_SetChargeCurrentMax(ExternCanCommGB_innerData.chargeCurrentLast);
    Current = ExternCanCommGB_CurrentFromBmsCurrent(ExternCanCommGB_innerData.chargeCurrentLast);
    WRITE_LT_UINT16(Buffer, index, Current);//充电电流需求
    Volt = Statistic_GetBcu100mvTotalVoltage();
    if (ExternCanCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
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
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BCSSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CHARGING)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBCSDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 Volt, temp;
    uint32 Time;
    Current_CurrentType Current;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    Volt = Statistic_GetBcu100mvTotalVoltage();
    WRITE_LT_UINT16(Buffer, index, Volt);//检测总压

    Current = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);
    Current = ExternCanCommGB_CurrentFromBmsCurrent(Current);
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
    if(Time > EXTERNCANCOMMGB_CHARGE_TIME_MAX)
    {
        Time = EXTERNCANCOMMGB_CHARGE_TIME_MAX;
    }
    WRITE_LT_UINT16(Buffer, index, Time);//剩余充电时间
    if (ExternCanCommGB_innerData.bclZeroCurSendFlag == TRUE)
    {
        ExternCanCommGB_innerData.bcsChargeStopSendFlag = TRUE;
    }
    *Length = index;
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BSMSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CHARGING)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBSMDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 temp;
    uint8 temp8;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

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
    if (ExternCanCommGB_innerData.currentChargeType == CHARGE_TYPE_DC) //过流
    {
        if (Diagnosis_GetLevel(DIAGNOSIS_ITEM_DC_CHG_OC) >= DIAGNOSIS_LEVEL_THIRD)
        {
            temp |= 0x10U;
        }
    }
    else if (ExternCanCommGB_innerData.currentChargeType == CHARGE_TYPE_AC)
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
    if(ExternCanCommGB_CheckChargeReq(0U) == 1U) //其他
    {
        temp |= 0x10U;
    }
    WRITE_LT_UINT8(Buffer, index, temp);

    *Length = index;
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BMVSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    // if (ExternCanCommGB_innerData.startFlag == TRUE)
    // {
    //     if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
    //     {
    //         if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CHARGING)
    //         {
    //             res = E_OK;
    //         }
    //     }
    // }
    return res;
}

void ExternCanCommGB_GetBMVDataCbk(uint8 *Buffer, uint16 *Length)
{
    imask_t mask;
    uint16 GroupNum, GroupMax;
    uint16 index = 0U;
    uint16 i, Num;
    App_VoltageType Volt;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    Irq_Save(mask);
    GroupNum = ExternCanCommGB_innerData.cellVoltGroupNum;
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
        if (Volt > EXTERNCANCOMMGB_CELL_VOLT_MAX)
        {
            Volt = EXTERNCANCOMMGB_CELL_VOLT_MAX;
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
    ExternCanCommGB_innerData.cellVoltGroupNum = (uint8)GroupNum;
    Irq_Restore(mask);

    *Length = index;
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BMTSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    // if (ExternCanCommGB_innerData.startFlag == TRUE)
    // {
    //     if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
    //     {
    //         if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CHARGING)
    //         {
    //             res = E_OK;
    //         }
    //     }
    // }
    return res;
}

void ExternCanCommGB_GetBMTDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 i, Num;
    App_TemperatureType Temperature;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    Num = CellDataM_BmuTemperatureLogicIdMax[SystemConnection_ConfigInfo.SlaveNum - 1U];
    for (i = 0U; i < Num; i++)
    {
        Temperature = CellDataM_GetTemperature(i);
        WRITE_LT_UINT8(Buffer, index, TEMP_4_DISPLAY(Temperature));
    }

    *Length = index;
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BSTSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CHARGE_STOP)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBSTDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint8 error;
    uint16 index = 0U;
    uint16 temp;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    temp = ExternCanCommGB_innerData.bmsStopReason;
    if(ExternCanComm_GetProtocol() == EXTERNCANCOMM_PROTOCOL_GB2015 &&
        ExternCanCommGB_innerData.stopChargeDev == EXTERNCANCOMMGB_STOP_CHARGE_DEV_CHARGER)
    {
        temp |= 0x40U;
    }
    WRITE_LT_UINT8(Buffer, index, temp);//BMS中止充电原因
    WRITE_LT_UINT16(Buffer, index, ExternCanCommGB_innerData.bmsFaultReason);//BMS中止充电故障原因
    error = ExternCanCommGB_innerData.bmsErrorReason | 0xF0U;
    WRITE_LT_UINT8(Buffer, index, error);//BMS中止充电错误原因
    ExternCanCommGB_innerData.bstSendCnt++;
    ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);

    *Length = index;
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BSDSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.currentChargeType != CHARGE_TYPE_NONE)
        {
            if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_STATISTIC)
            {
                res = E_OK;
            }
        }
    }
    return res;
}

void ExternCanCommGB_GetBSDDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint16 index = 0U;
    uint16 temp;
    uint8 temp8;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

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
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

Std_ReturnType ExternCanCommGB_BEMSendConditionCheck(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ExternCanCommGB_innerData.startFlag == TRUE)
    {
        if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_FAULT)
        {
            res = E_OK;
        }
    }
    return res;
}

void ExternCanCommGB_GetBEMDataCbk(uint8 *Buffer, uint16 *Length)
{
    uint8 flag = 0U;
    uint16 temp;
    uint32 now;

    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);
    VALIDATE_PTR(Length, EXTERNCANCOMMGB_API_ID_GetBHMDataCbk);

    Buffer[0] = ExternCanCommGB_innerData.bmsTimeoutReason[0] | 0xF0U;
    Buffer[1] = ExternCanCommGB_innerData.bmsTimeoutReason[1] | 0xF0U;
    Buffer[2] = ExternCanCommGB_innerData.bmsTimeoutReason[2] | 0xF0U;
    Buffer[3] = ExternCanCommGB_innerData.bmsTimeoutReason[3] | 0xFCU;

    now = OSTimeGet();
    if (ExternCanCommGB_innerData.bemCurDecreaseLastTick == 0U)
    {
        ExternCanCommGB_innerData.bemCurDecreaseLastTick = now;
    }
    temp = (uint16)abs(CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN));
    if (temp <= CURRENT_100MA_FROM_A(5U))
    {
        flag = 1U;
    }
    else if (MS_GET_INTERNAL(ExternCanCommGB_innerData.bemCurDecreaseLastTick, now) >= 10000U)
    {
        flag = 1U;
    }
    else
    {
    }
    if (flag != 0U)
    {
        ExternCanCommGB_CommStopForRestart();
        ExternCanCommGB_innerData.bemCurDecreaseLastTick = 0U;
    }
    *Length = EXTERNCANCOMMGB_BMS_TIMEOUT_BYTE_NUM;
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}
//用于超时重启充电
static void ExternCanCommGB_ClearChargerStatusCarefully(void)
{
    ExternCanCommGB_innerData.communication = FALSE;
    ExternCanCommGB_innerData.timeoutCntSwitch = FALSE;
    ExternCanCommGB_innerData.bmsChargeReady = FALSE;
    ExternCanCommGB_innerData.bmsChargeReadyLastTick = 0U;
    ExternCanCommGB_innerData.bmsChargeReadySendFlag = FALSE;
    ExternCanCommGB_innerData.chargeCurrentLast = 0;
    ExternCanCommGB_innerData.chargeCurrentLastTick = 0U;
    ExternCanCommGB_innerData.bmsStopReason = 0U;
    ExternCanCommGB_innerData.bmsFaultReason = 0U;
    ExternCanCommGB_innerData.bmsErrorReason = 0U;
    ExternCanCommGB_innerData.chargerStopReason = 0U;
    ExternCanCommGB_innerData.chargerFaultReason = 0U;
    ExternCanCommGB_innerData.chargerErrorReason = 0U;
    ExternCanCommGB_innerData.chargeStopLastTick = 0U;
    ExternCanCommGB_innerData.relayAdhesionCheckFlag = TRUE;
    ExternCanCommGB_innerData.bclZeroCurSendFlag = FALSE;
    ExternCanCommGB_innerData.ccsRecFlag = FALSE;
    ExternCanCommGB_innerData.stopChargeDev = EXTERNCANCOMMGB_STOP_CHARGE_DEV_NONE;
    ExternCanCommGB_innerData.bcsChargeStopSendFlag = FALSE;
    ExternCanCommGB_innerData.bstSendCnt = 0U;
    ExternCanCommGB_innerData.bemCurDecreaseLastTick = 0U;
    ExternCanCommGB_innerData.cellVoltGroupNum = 0U;
    (void)memset(ExternCanCommGB_innerData.chargerTimeoutReason, 0, EXTERNCANCOMMGB_CHG_TIMEOUT_BYTE_NUM);
    ExternCanComm_SetChargingStatus(FALSE);
    ExternCanComm_SetChargerOutputHV(0U);
    ExternCanComm_SetChargerOutputHVMax(0U);
    ExternCanComm_SetChargerOutputHVMin(0U);
    ExternCanComm_SetChargerOutputCurrent(0);
    ExternCanComm_SetChargerOutputCurrentMax(0);
    ExternCanComm_SetChargerOutputCurrentMin(0);
    if (ExternCanCommGB_innerData.insuIsStop)
    {
        BridgeInsu_Start(BRIDGEINSU_MOS_BY_VOL);
        ExternCanCommGB_innerData.insuIsStop = FALSE;
    }
}

// 用于重新启动充电
static void ExternCanCommGB_RestChargerStatus(void)
{
    ExternCanCommGB_ClearChargerStatusCarefully();
    ExternCanCommGB_innerData.protocolVersion = EXTERNCANCOMMGB_PROTOCOL_VERSION_2015;
    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CONNECT_WAITING;
    ExternCanCommGB_innerData.timeoutCnt = 0U;
}

// Receive functions define
void ExternCanCommGB_ReceiveCHMCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U;
    uint32 version = 0U;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    ExternCanCommGB_innerData.communication = TRUE;
    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        ExternCanCommGB_UpdateCurrentChargeType();
        if (ChargeConnectM_ConfigInfo.DC2_Para.type == CHARGECONNECTM_CONNECT_COMMUNICATION)
        {
            // ExternCanCommGB_ChargerEnable();
            ExternCanCommGB_SetCommunication(TRUE);
        }
        else
        {
            if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
            {
                flag = 0U;
                ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
            }
        }
    }
    if (flag != 0U)
    {
        Charge_ChargeType type = ExternCanComm_GetChargeType();
        if (type != CHARGE_TYPE_NONE &&
            type != ExternCanCommGB_innerData.currentChargeType)
        {
            flag = 0U;
        }
        else if (ExternCanCommGB_innerData.stage > EXTERNCANCOMMGB_STAGE_SHAKEHAND_IDENTIFY)
        {
            flag = 0U;
        }
        else
        {
        }
    }
    if (flag != 0U)
    {
        //ExternCanCommGB_CommStart();
        ExternCanCommGB_SetCommunication(TRUE);
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_NORMAL);
        ExternCanComm_ClrAllFaultStatus();
        if (ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_SHAKEHAND_START)
        {
            if (Length >= 3U)
            {
                version = READ_LT_UINT24(Buffer, index);
            }
            if (version == (uint32)EXTERNCANCOMMGB_PROTOCOL_VERSION_2015)
            {
                BridgeInsu_Stop();
                ExternCanCommGB_innerData.insuIsStop = TRUE;
                (void)memset(ExternCanCommGB_innerData.bmsTimeoutReason, 0, EXTERNCANCOMMGB_BMS_TIMEOUT_BYTE_NUM);
                ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CHM_TO_CRM);
                ExternCanComm_SetProtocol(EXTERNCANCOMM_PROTOCOL_GB2015);
                ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_SHAKEHAND_START;
            }
        }
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ExternCanCommGB_ReceiveCRMCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U, identify = 0U;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    ExternCanCommGB_innerData.communication = TRUE;
    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        ExternCanCommGB_UpdateCurrentChargeType();
        if (ChargeConnectM_ConfigInfo.DC2_Para.type == CHARGECONNECTM_CONNECT_COMMUNICATION)
        {
            // ExternCanCommGB_ChargerEnable();
            ExternCanCommGB_SetCommunication(TRUE);
        }
        else
        {
            if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
            {
                flag = 0U;
                ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
            }
        }
    }
    if (flag != 0U)
    {
        Charge_ChargeType type = ExternCanComm_GetChargeType();
        if (type != CHARGE_TYPE_NONE &&
            type != ExternCanCommGB_innerData.currentChargeType)
        {
            flag = 0U;
        }
        else if (ExternCanCommGB_innerData.stage > EXTERNCANCOMMGB_STAGE_PARA_CONFIG)
        {
            flag = 0U;
        }
        else
        {
        }
    }
    if (flag != 0U)
    {
        //if (ExternCanCommGB_innerData.timeoutCnt > 3) break;
        //ExternCanCommGB_CommStart();
        ExternCanCommGB_SetCommunication(TRUE);
        ExternCanComm_ClrAllFaultStatus();
        if(ExternCanComm_GetCurrentRecStage() == EXTERNCANCOMM_STAGE_IDLE)
        {
            ExternCanCommGB_ClrSelfDiagnosis();
        }
        if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CONNECT_WAITING && ExternCanCommGB_innerData.timeoutCnt == 0U)
        {
            ExternCanComm_SetProtocol(EXTERNCANCOMM_PROTOCOL_GB2011);
        }

        for(index = 0U; index < EXTERNCANCOMMGB_BMS_TIMEOUT_BYTE_NUM; index++)
        {
            ExternCanCommGB_innerData.bmsTimeoutReason[index] = 0U;
        }
        index = 0U;
        if (Length > 0U)
        {
            identify = READ_LT_UINT8(Buffer, index);
        }
        if (identify == EXTERNCANCOMMGB_CHG_IDENTI_NUM)
        {
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CTS_CML);
            ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_PARA_CONFIG;
        }
        else if (identify == EXTERNCANCOMMGB_CHG_UN_IDENT_NUM)
        {
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CRM_AA);
            ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_SHAKEHAND_IDENTIFY;
        }
        else
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            ExternCanComm_ClrChargerStatus();
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
            ExternCanCommGB_innerData.bmsTimeoutReason[0] &= 0xFCU;
            ExternCanCommGB_innerData.bmsTimeoutReason[0] |= EXTERNCANCOMMGB_REC_SPN2560_00_UNKNOWN_VALUE;
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3901);
            ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
#endif
        }
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ExternCanCommGB_ReceiveCTSCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
        {
            ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_PARA_CONFIG &&
            ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_CHARGE_READY)
        {
            flag = 0U;
        }
    }
    if (flag != 0U)
    {
        (void)Buffer;
        (void)Length;
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ExternCanCommGB_ReceiveCMLCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U;
    uint16 volt, volt_max;
    Current_CurrentType current, current_max;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
        {
            ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_PARA_CONFIG &&
            ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_CHARGE_READY)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length >= 6U)
    {
        volt_max = READ_LT_UINT16(Buffer, index);
        ExternCanComm_SetChargerOutputHVMax(volt_max);
        volt = READ_LT_UINT16(Buffer, index);
        if (volt > volt_max)
        {
            volt = 0U;
        }
        ExternCanComm_SetChargerOutputHVMin(volt);
        current_max = (Current_CurrentType)READ_LT_UINT16(Buffer, index);
        current_max = ExternCanCommGB_CurrentToBmsCurrent(current_max);
        ExternCanComm_SetChargerOutputCurrentMax(current_max);
        if (ExternCanComm_GetProtocol() == EXTERNCANCOMM_PROTOCOL_GB2015 &&
            Length >= 8U)
        {
            current = (Current_CurrentType)READ_LT_UINT16(Buffer, index);
            current = ExternCanCommGB_CurrentToBmsCurrent(current);
            if (current > current_max)
            {
                current = (Current_CurrentType)CURRENT_INVALID_VALUE;
            }
            ExternCanComm_SetChargerOutputCurrentMin(current);
        }
        ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CHARGE_READY;
        ExternCanCommGB_innerData.bmsChargeReadyLastTick = OSTimeGet();
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ExternCanCommGB_ReceiveCROCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag =1U;
    uint16 index = 0U, readyFlag;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
        {
            ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_CHARGE_READY)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length > 0U)
    {
        readyFlag = READ_LT_UINT8(Buffer, index);
        if (readyFlag == EXTERNCANCOMMGB_CHG_IDENTI_NUM)
        {
            if (ExternCanCommGB_innerData.bmsChargeReadySendFlag == TRUE)
            {
                ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CHARGING;
            }
        }
        else if (readyFlag == EXTERNCANCOMMGB_CHG_UN_IDENT_NUM)
        {
            ExternCanComm_RecAsyncEventType *recEvent = ExternCanComm_GetRecAsyncEventPtr();
            Async_EventSetTimeout(&recEvent[1].event, EXTERNCANCOMMGB_REC_TIMEOUT_CRO_AA);
        }
        else
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            ExternCanComm_ClrChargerStatus();
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
            ExternCanCommGB_innerData.bmsTimeoutReason[1] &= 0xF3U;
            ExternCanCommGB_innerData.bmsTimeoutReason[1] |= EXTERNCANCOMMGB_REC_CHARGER_READY_UNKNOWN_VALUE;
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3923);
            ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
#endif
        }
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ExternCanCommGB_ReceiveCCSCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U, chargeState;
    Current_CurrentType current;
    ExternCanComm_ProtocolType type;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
        {
            ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_CHARGING)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length >= 6U)
    {
        ExternCanComm_SetChargerOutputHV(READ_LT_UINT16(Buffer, index));
        current = (Current_CurrentType)READ_LT_UINT16(Buffer, index);
        current = ExternCanCommGB_CurrentToBmsCurrent(current);
        ExternCanComm_SetChargerOutputCurrent(current);
        ExternCanComm_SetChargerChargedTime(READ_LT_UINT16(Buffer, index));
        chargeState = READ_LT_UINT8(Buffer, index);
        chargeState &= 0x03U;
        type = ExternCanComm_GetProtocol();

        flag = 0U;
        if (ExternCanComm_GetChargerOutputHV() && current != 0)
        {
            flag = 1U;
        }
        if (type != EXTERNCANCOMM_PROTOCOL_GB2015)
        {
            if (flag != 0U)
            {
                ExternCanComm_SetChargingStatus(TRUE);
            }
            else
            {
                ExternCanComm_SetChargingStatus(FALSE);
            }
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CCS);
            ExternCanCommGB_innerData.ccsRecFlag = TRUE;
        }
        else
        {
            if (chargeState > 1U) //异常状态
            {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
                ExternCanComm_SetChargingStatus(FALSE);
                ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
                ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
                ExternCanCommGB_innerData.bmsTimeoutReason[2] &= 0xFCU;
                ExternCanCommGB_innerData.bmsTimeoutReason[2] |= EXTERNCANCOMMGB_REC_CHARGER_STATUS_UNKNOWN_VALUE;
                ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3905);
#endif
            }
            else
            {
                if (flag != 0U && chargeState) //0:暂停 1:允许
                {
                    ExternCanComm_SetChargingStatus(TRUE);
                }
                else
                {
                    ExternCanComm_SetChargingStatus(FALSE);
                }
                ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CCS);
                ExternCanCommGB_innerData.ccsRecFlag = TRUE;
            }
        }
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ExternCanCommGB_ReceiveCSTCbk(const uint8 *Buffer, uint16 Length)
{
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
    uint8 unkonw_state = 0U
#endif
    uint8 flag = 1U;
    uint16 index = 0U;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
        {
            ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_CHARGING &&
            ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_CHARGE_STOP)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length >= 4U)
    {
        ExternCanCommGB_innerData.chargerStopReason = READ_LT_UINT8(Buffer, index);
        ExternCanCommGB_innerData.chargerFaultReason = READ_LT_UINT16(Buffer, index);
        ExternCanCommGB_innerData.chargerErrorReason = READ_LT_UINT8(Buffer, index);

        flag = ExternCanCommGB_innerData.chargerStopReason & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_STOP_CHG_WITH_FINISH, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_STOP_CHG_WITH_FINISH);
        }
        flag = (ExternCanCommGB_innerData.chargerStopReason >> 2) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_MANUAL_STOP_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_MANUAL_STOP_INDEX);
        }
        flag = (ExternCanCommGB_innerData.chargerStopReason >> 4) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_FAULT_FAULT_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_FAULT_FAULT_INDEX);
        }
        flag = (ExternCanCommGB_innerData.chargerStopReason >> 6) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_BMS_STOP_CHARGE_FAULT_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_BMS_STOP_CHARGE_FAULT_INDEX);
        }
        flag = (uint8)ExternCanCommGB_innerData.chargerFaultReason & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_OVER_TEMPERATURE_FAULT_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_OVER_TEMPERATURE_FAULT_INDEX);
        }
        flag = (uint8)(ExternCanCommGB_innerData.chargerFaultReason >> 2) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_CHAGER_CONNECTOR_FAULT_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_CHAGER_CONNECTOR_FAULT_INDEX);
        }
        flag = (uint8)(ExternCanCommGB_innerData.chargerFaultReason >> 4) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_INNER_OVER_TEMPERATURE_FAULT_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_INNER_OVER_TEMPERATURE_FAULT_INDEX);
        }
        flag = (uint8)(ExternCanCommGB_innerData.chargerFaultReason >> 6) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_ENERGY_TRANSIMIT_FAULT_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_ENERGY_TRANSIMIT_FAULT_INDEX);
        }
        flag = (uint8)(ExternCanCommGB_innerData.chargerFaultReason >> 8) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_EMERGENCY_STOP_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_EMERGENCY_STOP_INDEX);
        }
        flag = (uint8)(ExternCanCommGB_innerData.chargerFaultReason >> 10) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void) ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_FAULT_FAULT_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_FAULT_FAULT_INDEX);
        }
        flag = ExternCanCommGB_innerData.chargerErrorReason & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_CURRENT_NOT_MATCH_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_CURRENT_NOT_MATCH_INDEX);
        }
        flag = (ExternCanCommGB_innerData.chargerErrorReason >> 2) & 0x03U;
        if(flag != 0U)
        {
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
            if (flag == 3U)
            {
                unkonw_state = 1U;
            }
#endif
            (void)ExternCanComm_SetChargeFaultWithIndex(EXTERNCANCOMM_CHR_OUTPUT_VOLT_FAULT_INDEX, flag);
        }
        else
        {
            (void)ExternCanComm_ClearChargerFaultWithIndex(EXTERNCANCOMM_CHR_OUTPUT_VOLT_FAULT_INDEX);
        }
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
        if (unkonw_state == 0U)
#endif
        {
            ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CHARGE_STOP;
            if(ExternCanCommGB_innerData.stopChargeDev == EXTERNCANCOMMGB_STOP_CHARGE_DEV_BMS)
            {
                ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_STATISTIC;
                ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CST_CSD);
            }
            else if(ExternCanCommGB_innerData.stopChargeDev == EXTERNCANCOMMGB_STOP_CHARGE_DEV_NONE)
            {
                ExternCanCommGB_innerData.stopChargeDev = EXTERNCANCOMMGB_STOP_CHARGE_DEV_CHARGER; //正常充电完成
            }
            else if(ExternCanCommGB_innerData.stopChargeDev == EXTERNCANCOMMGB_STOP_CHARGE_DEV_CHARGER)
            {
                if(ExternCanCommGB_innerData.bstSendCnt >= 3U)
                {
                    ExternCanCommGB_innerData.bstSendCnt = 0U;
                    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_STATISTIC;
                    ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CST_CSD);
                }
            }
            else
            {
            }
        }
#if EXTERNCANCOMMGB_UNKNOWN_STATE_PROCESS_EN != 0U
        else
        {
            ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
            ExternCanCommGB_innerData.bmsTimeoutReason[2] &= 0xF3U;
            ExternCanCommGB_innerData.bmsTimeoutReason[2] |= EXTERNCANCOMMGB_REC_CHARGER_STOP_UNKNOWN_VALUE;
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3906);
        }
#endif
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ExternCanCommGB_ReceiveCSDCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    uint16 index = 0U, temp;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
        {
            ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
        if (ExternCanCommGB_innerData.stage != EXTERNCANCOMMGB_STAGE_STATISTIC)
        {
            flag = 0U;
        }
    }
    if (flag != 0U && Length >= 4U)
    {
        temp = READ_LT_UINT16(Buffer, index);
        ExternCanComm_SetChargerChargedTime(temp);
        temp = READ_LT_UINT16(Buffer, index);
        ExternCanComm_SetChargerChargedPower(temp);
        ExternCanCommGB_RestChargerStatus();
        ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX, CHARGEM_CHARGE_DISABLE);
        ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CONNECT_WAITING;
        if (ExternCanCommGB_innerData.stopFlag == TRUE)
        {
            ExternCanCommGB_innerData.startFlag = FALSE;
        }
        if (ChargeM_BatteryChargeIsFinish() == TRUE)
        {
            ExternCanCommGB_CommStop();
        }
        else
        {
            ExternCanCommGB_CommStopForRestart();
        }
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

void ExternCanCommGB_ReceiveCEMCbk(const uint8 *Buffer, uint16 Length)
{
    uint8 flag = 1U;
    VALIDATE_PTR(Buffer, EXTERNCANCOMMGB_API_ID_ReceiveCHMCbk);

    if (ExternCanCommGB_innerData.startFlag == FALSE)
    {
        flag = 0U;
        ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE);
    }
    else
    {
        if (ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType)
        {
            ExternCanCommGB_SetSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
        }
    }
    if (flag != 0U && Length >= 4U)
    {
        (void)memcpy(ExternCanCommGB_innerData.chargerTimeoutReason, Buffer, 4U);
        if(0x01U == (ExternCanCommGB_innerData.chargerTimeoutReason[0] & 3U))
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3921);
        }
        if(0x01U == (ExternCanCommGB_innerData.chargerTimeoutReason[1] & 3U))
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3922);
        }
        if(0x01U == ((ExternCanCommGB_innerData.chargerTimeoutReason[1] >> 2) & 3U))
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3923);
        }
        if(0x01U == ((ExternCanCommGB_innerData.chargerTimeoutReason[2]) & 3U))
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3924);
        }
        if(0x01U == ((ExternCanCommGB_innerData.chargerTimeoutReason[2] >> 2) & 3U))
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3925);
        }
        if(0x01U == ((ExternCanCommGB_innerData.chargerTimeoutReason[2] >> 4) & 3U))
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3926);
        }
        if(0x01U == ((ExternCanCommGB_innerData.chargerTimeoutReason[3]) & 3U))
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3927);
        }
        ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
    return;
#endif
}

void ExternCanCommGB_RecCHMTimeoutCbk(void)
{
    ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CRM);
}

void ExternCanCommGB_RecCRMTimeoutCbk(void)
{
    ExternCanComm_StageType RecStage;
    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
    RecStage = ExternCanComm_GetCurrentRecStage();
    if (RecStage == EXTERNCANCOMM_STAGE_GB_CRM ||
        RecStage == EXTERNCANCOMM_STAGE_GB_CHM_TO_CRM ||
        RecStage == EXTERNCANCOMM_STAGE_GB_RECOMM_CRM)
    {
        ExternCanComm_ClrChargerStatus();
        ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
        ExternCanCommGB_innerData.bmsTimeoutReason[0] &= 0xFCU;
        ExternCanCommGB_innerData.bmsTimeoutReason[0] |= EXTERNCANCOMMGB_REC_SPN2560_00_TIMEOUT_VALUE;
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3901);
    }
    else if (RecStage == EXTERNCANCOMM_STAGE_GB_CRM_AA)
    {
        ExternCanComm_ClrChargerStatus();
        ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
        ExternCanCommGB_innerData.bmsTimeoutReason[0] &= 0xF3U;
        ExternCanCommGB_innerData.bmsTimeoutReason[0] |= EXTERNCANCOMMGB_REC_SPN2560_AA_TIMEOUT_VALUE;
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3902);
    }
    else
    {
    }
    ExternCanCommGB_SetCommunication(FALSE);
}

void ExternCanCommGB_RecCMLTimeoutCbk(void)
{
    ExternCanCommGB_SetCommunication(FALSE);
    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
    ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
    ExternCanCommGB_innerData.bmsTimeoutReason[1] &= 0xFCU;
    ExternCanCommGB_innerData.bmsTimeoutReason[1] |= EXTERNCANCOMMGB_REC_CAPABILITY_TIMEOUT_VALUE;
    ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3903);
}

void ExternCanCommGB_RecCROTimeoutCbk(void)
{
    ExternCanCommGB_SetCommunication(FALSE);
    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
    ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
    ExternCanCommGB_innerData.bmsTimeoutReason[1] &= 0xF3U;
    ExternCanCommGB_innerData.bmsTimeoutReason[1] |= EXTERNCANCOMMGB_REC_CHARGER_READY_TIMEOUT_VALUE;
    ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3904);
}

void ExternCanCommGB_RecCROAATimeoutCbk(void)
{
    ExternCanCommGB_SetCommunication(FALSE);
    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
    ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
    ExternCanCommGB_innerData.bmsTimeoutReason[1] &= 0xF3U;
    ExternCanCommGB_innerData.bmsTimeoutReason[1] |= EXTERNCANCOMMGB_REC_CHARGER_READY_TIMEOUT_VALUE;
    ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3904);
}

void ExternCanCommGB_RecCCSTimeoutCbk(void)
{
    ExternCanCommGB_SetCommunication(FALSE);
    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
    ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
    ExternCanCommGB_innerData.bmsTimeoutReason[2] &= 0xFCU;
    ExternCanCommGB_innerData.bmsTimeoutReason[2] |= EXTERNCANCOMMGB_REC_CHARGER_STATUS_TIMEOUT_VALUE;
    ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3905);
}

void ExternCanCommGB_RecCSTTimeoutCbk(void)
{
    if (ExternCanCommGB_innerData.stage == EXTERNCANCOMMGB_STAGE_CHARGE_STOP)
    {
        ExternCanCommGB_SetCommunication(FALSE);
        ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
        ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
        ExternCanCommGB_innerData.bmsTimeoutReason[2] &= 0xF3U;
        ExternCanCommGB_innerData.bmsTimeoutReason[2] |= EXTERNCANCOMMGB_REC_CHARGER_STOP_TIMEOUT_VALUE;
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3906);
    }
}

void ExternCanCommGB_RecCSDTimeoutCbk(void)
{
    ExternCanCommGB_SetCommunication(FALSE);
    ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_FAULT;
    ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CEM);
    ExternCanCommGB_innerData.bmsTimeoutReason[3] &= 0xFCU;
    ExternCanCommGB_innerData.bmsTimeoutReason[3] |= EXTERNCANCOMMGB_REC_CHARGER_STATIS_TIMEOUT_VALUE;
    ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3907);
}

//GB策略实现
ExternCanComm_SelfDiagnosisType ExternCanCommGB_GetSelfDiagnosis(void)
{
    ExternCanComm_SelfDiagnosisType current_num;
    imask_t mask;

    Irq_Save(mask);
    current_num = ExternCanCommGB_innerData.selfDiag;
    Irq_Restore(mask);

    return current_num;
}

static void ExternCanCommGB_SetSelfDiagnosis(ExternCanComm_SelfDiagnosisType diagnosis)
{
    imask_t mask;

    Irq_Save(mask);
    if (ExternCanCommGB_innerData.selfDiag != diagnosis)
    {
        ExternCanCommGB_innerData.selfDiag = diagnosis;
    }
    Irq_Restore(mask);
}

static void ExternCanCommGB_ClrSelfDiagnosis(void)
{
    imask_t mask;

    Irq_Save(mask);
    ExternCanCommGB_innerData.selfDiag = EXTERNCANCOMM_SELFDIAG_NORMAL;
    Irq_Restore(mask);
}

static void ExternCanCommGB_UpdateSelfDiagnosis(ExternCanComm_SelfDiagnosisType diagnosis)
{
    if(diagnosis >= EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3902 && diagnosis <= EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3927)
    {
        ExternCanCommGB_TimeoutCntUpdate();
    }
    if(ExternCanCommGB_GetSelfDiagnosis() == EXTERNCANCOMM_SELFDIAG_NORMAL)
    {
        ExternCanCommGB_SetSelfDiagnosis(diagnosis);
    }
}


static void ExternCanCommGB_UpdateSelfDiagnosisWithOthers(void)
{
    if(ChargeM_DiagnosisIsNormal() != E_OK)
    {
        if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_HV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HV); //单体高压
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HV); //单体高压
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_LV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LV); //单体低压
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_LV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LV); //单体低压
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_HT) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HT); //单体高温
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HT) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HT); //单体高温
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_LT) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LT); //单体低温
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_LT) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LT); //单体低温
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_DT) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_DT); //单体温差
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_DT) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_DT); //单体温差
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_DV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_DV); //单体压差
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_DV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_DV); //单体压差
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_INTER_COMM) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_SLAVE_COMM); //内网通信
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_LSOC) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LSOC); //SOC低
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_HSOC) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HSOC); //SOC高
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_LEAK) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LEAK); //系统漏电
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_HTV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HTV); //总压高
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HTV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HTV); //总压高
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_LTV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LTV); //总压低
        }
        else if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_LTV) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LTV); //总压低
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_VOLT_LINE) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_VOLT_LINE); //电压排线脱落
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_TEMP_LINE) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_TEMP_LINE); //温感排线脱落
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DC_CHG_OC) == CHARGEM_CHARGE_DISABLE &&
            ExternCanCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_OCC); //充电过流
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_AC_CHG_OC) == CHARGEM_CHARGE_DISABLE &&
            ExternCanCommGB_innerData.currentChargeType == CHARGE_TYPE_AC)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_OCC); //充电过流
        }
        else if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_DCHG_OC) == CHARGEM_CHARGE_DISABLE)
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_ODC); //放电过流
        }
        else
        {
            ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_OTHERS); //其他故障
        }
    }
}

static void ExternCanCommGB_TimeoutCntUpdate(void)
{
    if(ExternCanCommGB_innerData.timeoutCntSwitch == FALSE)
    {
        ExternCanCommGB_innerData.timeoutCntSwitch = TRUE;
        ExternCanCommGB_innerData.timeoutCnt++;
    }
}

void ExternCanCommGB_StartRecStageTimeout(uint8 channel, ExternCanComm_StageType currentStage)
{
    uint16 timeout;
    const ExternCanComm_RecIPduCfgType* cfg;
    ExternCanComm_RecAsyncEventType *recEvent;

    if (channel < EXTERNCANCOMM_MONITOR_REC_MSG_NUM_PER_STAGE &&
        currentStage >= EXTERNCANCOMM_STAGE_GB_START &&
        currentStage <= EXTERNCANCOMM_STAGE_GB_STOP)
    {
        cfg = ExternCanComm_GetRecStageCfg(currentStage);
        recEvent = ExternCanComm_GetRecAsyncEventPtr();
        VALIDATE_PTR(cfg, EXTERNCANCOMMGB_API_ID_StartRecStageTimeout);
        VALIDATE_PTR(recEvent, EXTERNCANCOMMGB_API_ID_StartRecStageTimeout);

        switch(currentStage)
        {
            case EXTERNCANCOMM_STAGE_IDLE:
                break;
            case EXTERNCANCOMM_STAGE_GB_START:
            case EXTERNCANCOMM_STAGE_GB_CHM_TO_CRM:
            case EXTERNCANCOMM_STAGE_GB_RECOMM_CRM:
            case EXTERNCANCOMM_STAGE_GB_CRM_AA:
            case EXTERNCANCOMM_STAGE_GB_CTS_CML:
            case EXTERNCANCOMM_STAGE_GB_CRO:
            case EXTERNCANCOMM_STAGE_GB_CCS:
            case EXTERNCANCOMM_STAGE_GB_CST_CSD:
            case EXTERNCANCOMM_STAGE_GB_CEM:
            case EXTERNCANCOMM_STAGE_GB_CRM:
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
                    timeout = EXTERNCANCOMMGB_REC_TIMEOUT_DEFAULT;
                }
                Async_EventSetTimeout(&recEvent[channel].event, timeout);
                break;
            case EXTERNCANCOMM_STAGE_MAX:
            default:
                // do nothing
                break;
        }
    }
#if ( EXTERNCANCOMMGB_DEV_ERROR_DETECT == STD_ON )
cleanup:
#endif
    return;
}

static Current_CurrentType ExternCanCommGB_CurrentToBmsCurrent(Current_CurrentType cur)
{
    if(cur >= 0)
    {
        cur = -1*(cur - (sint16)EXTERNCANCOMMGB_CURRENT_OFFSET);
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

static Current_CurrentType ExternCanCommGB_CurrentFromBmsCurrent(Current_CurrentType cur)
{
    if(cur > (Current_CurrentType)EXTERNCANCOMMGB_CURRENT_OFFSET)
    {
        cur = (Current_CurrentType)EXTERNCANCOMMGB_CURRENT_OFFSET;
    }
    cur = -1*cur + (Current_CurrentType)EXTERNCANCOMMGB_CURRENT_OFFSET;
    if (cur < 0)
    {
        cur = 0;
    }
    return cur;
}


static void ExternCanCommGB_GetDecreaseCurrent(Current_CurrentType new_current, Current_CurrentType *current)
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
            if (MS_GET_INTERNAL(ExternCanCommGB_innerData.chargeCurrentLastTick, now_tick) >= 1000U)
            {
                Current_CurrentType diff = value - new_current;
                ExternCanCommGB_innerData.chargeCurrentLastTick = now_tick;
                if(diff > EXTERNCANCOMMGB_CURRENT_DECREASE_MAX_PER_S)
                {
                    value -= EXTERNCANCOMMGB_CURRENT_DECREASE_MAX_PER_S;
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

uint8 ExternCanCommGB_CheckChargeReq(uint16 delay) //return 0-waitting 1-ready 2-fault
{
    uint8 flag;
    uint16 data, hvMax;
    uint16 reason = 0U;
    Diagnosis_ItemType item;
    uint8 version2015 = FALSE;

    //充电停止原因
    //if(SOC_TO_PERCENT(bcu_get_SOC()) >= 100)//SOC过大
    //    temp |= 0x01;
    if (ExternCanComm_GetProtocol() == EXTERNCANCOMM_PROTOCOL_GB2015)
    {
        version2015 = TRUE;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HTV) == CHARGEM_CHARGE_DISABLE)//达到总压设定值
    {
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HTV);
        reason |= 0x04U;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HV) == CHARGEM_CHARGE_DISABLE) //达到单体电压设定值
    {
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HV);
        reason |= 0x10U;
    }
    if (ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_FULL_CHARGE) == CHARGEM_CHARGE_DISABLE) //满充
    {
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_FULL_CHARGE);
        reason |= 0x10U;
    }
    ExternCanCommGB_innerData.bmsStopReason = (uint8)reason;
    //充电故障原因
    reason = 0U;
    if (ExternCanCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
    {
        item = DIAGNOSIS_ITEM_DC_CHG_OC;
    }
    else
    {
        item = DIAGNOSIS_ITEM_AC_CHG_OC;
    }
    if(ChargeM_GetDiagnosisChargeCtlFlag(item) == CHARGEM_CHARGE_DISABLE) //充电过流
    {
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_OCC);
        reason |= 0x01U;
    }
    data = Statistic_GetBcu100mvTotalVoltage();
    hvMax = ExternCanComm_GetChargerOutputHVMax();
    flag = 0U;
    if (hvMax > 0U && data > hvMax)
    {
        flag = 1U;
    }
    if(data < ExternCanComm_GetChargerOutputHVMin() || flag != 0U)
    {
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_TV_EXCEPTION);
        reason |= 0x04U;
    }
    ExternCanCommGB_innerData.bmsErrorReason = (uint8)reason;
    //充电错误原因
    reason = 0U;
    if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_LEAK) == CHARGEM_CHARGE_DISABLE)  //漏电
    {
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_LEAK);
        reason |= 0x01U;
    }
    // 输出连接器过温故障
    flag = FALSE;
    if (ExternCanCommGB_innerData.currentChargeType == CHARGE_TYPE_DC)
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
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_OTHERS);
        reason |= 0x04U;
    }
    if(ChargeConnectM_GetDC2ConnectType() != ExternCanCommGB_innerData.currentChargeType) // 充电连接器故障
    {
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT);
        reason |= 0x40U;
    }
    if(ChargeM_GetDiagnosisChargeCtlFlag(DIAGNOSIS_ITEM_CHG_HT) == CHARGEM_CHARGE_DISABLE) //过温
    {
        ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_HT);
        reason |= 0x100U;
    }
    if(version2015 == TRUE)
    {
        RelayM_FunctionType type;

        type = ExternCanComm_ConfigInfo.RelayType;
        if(type != RELAYM_FN_NONE)
        {
            if (!RELAYM_DIAGNOSIS_IS_NORMAL_IGNORE_CHECKING(RelayM_GetDiagnosisStatus(type))) //继电器异常
            {
                ExternCanCommGB_UpdateSelfDiagnosis(EXTERNCANCOMM_SELFDIAG_BMS_RELAY_FAULT);
                reason |= 0x400U;
            }
        }
        //检测点2电压检测故障
    }
    if(//g_guobiao_comm_timeout_cnt >= GUOBIAO_COMM_ABORT_TIMEOUT_TIMES ||
        (ChargeM_ChargeIsAllowed() != E_OK &&
        reason==0U &&
        ExternCanCommGB_innerData.bmsStopReason==0U &&
        ExternCanCommGB_innerData.bmsErrorReason==0U)) //其他故障
    {
        //if(g_guobiao_comm_timeout_cnt >= GUOBIAO_COMM_ABORT_TIMEOUT_TIMES)
        //    ExternCanCommGB_UpdateSelfDiagnosis(kGBChgFaultOverTimeoutTimes);
        //else
            ExternCanCommGB_UpdateSelfDiagnosisWithOthers();
        if(version2015 == TRUE)
        {
            reason |= 0x4000U;
        }
        else
        {
            reason |= 0x400U;
        }
    }
    ExternCanCommGB_innerData.bmsFaultReason = reason;
    flag = 1U;
    if(ExternCanCommGB_innerData.bmsStopReason || ExternCanCommGB_innerData.bmsFaultReason || ExternCanCommGB_innerData.bmsErrorReason)
    {
        if (delay)
        {
            uint32 now = OSTimeGet();
            if(ExternCanCommGB_innerData.chargeStopLastTick == 0U)
            {
                ExternCanCommGB_innerData.chargeStopLastTick = now;
            }
            if(MS_GET_INTERNAL(ExternCanCommGB_innerData.chargeStopLastTick, now) >= delay)
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
        ExternCanCommGB_innerData.chargeStopLastTick = 0U;
    }
    return flag;
}

uint8 ExternCanCommGB_ChargeIsFaultStop(void)
{
    uint8 flag = FALSE;

    if (ExternCanCommGB_innerData.bmsErrorReason ||
        ExternCanCommGB_innerData.bmsFaultReason)
    {
        flag = TRUE;
    }
    return flag;
}

static uint8 ExternCanCommGB_ChargeIsStop(void)
{
    uint8 flag = FALSE;
    if(ExternCanCommGB_CheckChargeReq(100U) == 2U)
    {
        flag = TRUE;
    }
    return flag;
}

static uint8 ExternCanCommGB_IsChargingReady(void) // return 0-waitting 1-ready 2-fault
{
    uint8 flag = 0U, ret = 0xFFU;
    RelayM_FunctionType relayType;

    relayType = ExternCanComm_ConfigInfo.RelayType;

#if EXTERNCANCOMMGB_RELAY_ADHESION_CHECK_EN == STD_ON
    if (relayType != RELAYM_FN_NONE)
    {
        if (RelayM_RelayHvIsMonitor(relayType) == E_OK)
        {
            if (RelayM_GetActualStatus(RELAYM_FN_POSITIVE_DISCHRGE) != RELAYM_ACTUAL_ON)
            {
                if (RelayM_GetActualStatus(RELAYM_FN_PRECHARGE) != RELAYM_ACTUAL_ON)
                {
                    RelayM_DiagnosisStatusType status;
                    if(ExternCanCommGB_innerData.relayAdhesionCheckFlag == TRUE/* &&
                        bcu_get_insulation_work_state()!=kInsulationWorkStateNotConnected &&
                        bcu_get_insulation_work_state()!=kInsulationWorkStateVoltExcept*/)
                    {
                        ExternCanCommGB_innerData.relayAdhesionCheckFlag = FALSE;
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
            flag = ExternCanCommGB_CheckChargeReq(500U);
        }
        if (flag == 1U)
        {
            ChargeM_SetChargerGBReadyStatus(CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX, CHARGEM_CHARGE_ENABLE);
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

static void ExternCanCommGB_ChargingReadyCheck(void)
{
    uint8 flag = ExternCanCommGB_IsChargingReady();
    uint32 now = OSTimeGet();

    if(flag == 1U)
    {
        ExternCanCommGB_innerData.bmsChargeReady = EXTERNCANCOMMGB_BMS_CHARGE_READY;
    }
    else
    {
        if(MS_GET_INTERNAL(ExternCanCommGB_innerData.bmsChargeReadyLastTick, now) >= 15000U || //准备就绪超时进入中止充电阶段
            flag == 2U) //故障
        {
            ExternCanCommGB_innerData.stage = EXTERNCANCOMMGB_STAGE_CHARGE_STOP;
            ExternCanComm_TriggerNewRecStage(EXTERNCANCOMM_STAGE_GB_CST_CSD);
        }
        else
        {
            ExternCanCommGB_innerData.bmsChargeReady = EXTERNCANCOMMGB_BMS_CHARGE_NOT_READY;
        }
    }
}
