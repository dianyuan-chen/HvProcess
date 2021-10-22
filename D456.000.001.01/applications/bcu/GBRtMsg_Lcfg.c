#include <string.h>
#include "GBRtMsg.h"
#include "Hall.h"
#include "CellDataM.h"
#include "AppInfo.h"
#include "HardwareSn.h"
#include "RuntimeM.h"
#include "Soc.h"
#include "Soh.h"
#include "Insu.h"
#include "BalanceM.h"
#include "Statistic.h"
#include "PwmCapture_Lcfg.h"
#include "ChargeConnectM.h"
#include "ChargerComm.h"
#include "ChgSckTmpM.h"
#include "EL.h"
#include "DtuComm_M35.h"
#include "RelayM_Lcfg.h"
#include "SystemConnection_Lcfg.h"
#include "Diagnosis.h"
#include "Dio.h"
#include "ExternCanComm.h"
#include "ParameterM.h"
#include "AppInfo.h"
#include "HWDiagnosis.h"
#include "DigitalInput_Cfg.h"
#include "DigitalInput.h"
#include "ChargeM.h"
#include "DisChargeM.h"
#include "SocDiagCalib.h"

#define LOG_LEVEL LOG_LEVEL_OFF
#include "logger.h"


typedef struct {
    GB32960_RtMessageHeader GBRtHeader;
    union {
        struct {
            uint16 messageLength;
            uint8 releaseName[30];
            uint8 SCID[40];
            uint16 customMsgVersion;
            uint8 fwAddrSpace;
            uint32 runTime;
            uint8 runMode;
            uint16 chargeableCycles;
        } deviceInfo;
        struct {
            uint8 vinCode[17];
            uint8 deviceCnt;
        } deviceList;
        struct {
            uint16 messageLength;
            uint8 command;
        } ableCommand;
        struct {
            uint16 messageLength;
            uint8 heardbeat;
            uint16 supplyVoltage;
            uint8 resetSourse;
            uint16 dSoc;
            uint16 soc;
            uint16 integralRatio;
            uint16 soh;
            uint16 insuResSys;
            uint16 insuResPos;
            uint16 insuResNeg;
            uint8 runStatus;
            uint8 wakeSignal;
            uint16 bcuTotalVoltage;
            uint16 HVBPOS;
            uint16 HV1;
            uint16 HV2;
            uint16 HV3;
            uint16 HV4;
            uint16 HV5;
            uint8 DI1;
            uint8 DI2;
            uint8 SW1;
            uint8 SW2;
            uint8 chargeStartDiagFault;
            uint8 chargeDiagFaultFlag;
            uint8 chargeDiagFaultAction;
            uint8 ChargerGBReadyFault;
            uint8 chargeOtherFault;
            uint8 dischargeStartDiagFault;
            uint8 dischargeDiagFaultFlag;
            uint8 dischargeFaultDiagFaultAction;
            uint8 dischargeOtherFault;
            uint8 SOCEmptyReason;
            uint8 SOCFullReason;
            uint8 relayNum;
        } systemStatus;
        struct {
            uint8 totalSysNum;
            uint8 sysNumOfThisFrame;
            uint16 totalVoltage;
            sint16 current1;
            sint16 current2;
            uint16 totalCellNum;
            uint16 startCellOfThisFrame;
            uint8 cellNumOfThisFrame;
        } cellVoltages;
        struct {
            uint8 totalSysNum;
            uint8 sysNumOfThisFrame;
            uint16 totalCellNum;
        } cellTemperatures;
        struct {
            uint8 highVoltageSysNum;
            uint16 highVoltageCellNum;
            uint16 highVoltageValue;
            uint8 lowVoltageSysNum;
            uint16 lowVoltageCellNum;
            uint16 lowVoltageValue;
            uint8 highTemperatureSysNum;
            uint16 highTemperatureCellNum;
            uint8 highTemperatureValue;
            uint8 lowTemperatureSysNum;
            uint16 lowTemperatureCellNum;
            uint8 lowTemperatureValue;
        } cellPeakData;
        struct {
            uint16 supplyVoltage;
            uint8 ops;
            uint8 signalStrength;
            uint8 errorBitrate;
            uint16 lac;
            uint32 ci;
            sint32 longtitude;
            sint32 latitude;
        } dtuStatus;

        struct {
            uint16 messageLength;
            uint8 connection;
            uint16 chargedTime;
            uint16 requestChargeVoltMax;
            sint16 requestChargeCurrentMax;
            uint16 outputVoltage;
            uint16 outputCurrent;
            uint32 errorStatus;
            uint8 s2Status;
            uint16 ccResistor;
            uint16 cc2Resistor;
            uint16 cpFreq;
            uint16 cpDuty;
            uint8 elStatus;
            uint8 connectorTemp[4];
        } chargerStatus;

        struct {
            uint16 totalCellNum;
        } balanceStatus;

        struct {
            uint16 alarmNum;
        } alarmStatus;

        struct {
            uint8 chgType;
            uint16 chgResoltion;
            uint32 chgCumu;
            uint32 totalChgCumu;
            uint8 dchgType;
            uint16 dchgResoltion;
            uint32 dchgCumu;
            uint32 totalDchgCumu;
        } powerInfo;

        struct {
            uint16 num;
        } gb32960SupportCmdId;

        struct {
            uint16 messageLength;
            uint32 chargedTime;
            uint32 dischargedTime;
        } chargeDischargeTime;

    } dataHeader;
} GB32960_PACKED GBRt_MsgBuffer;


typedef struct {
    uint8 heardbeat;
    GBRt_MsgBuffer msgBuf;
} GB32960_PACKED GBRt_MsgBufferWithHeartbeat;

#define MSG_VERSION         0U

#define MEMBER_SIZEOF_MSG_HEADER(_member_) sizeof(((GBRt_MsgBuffer *)0)->dataHeader._member_)

#define MSG_LENGTH_DEVICE_INFO         (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(deviceInfo) + 16U/*FWID*/ + 16U/*BurnID*/)
#define MSG_LENGTH_DEVICE_LIST         (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(deviceList) + (uint16)(1U + SYSTEM_BMU_NUM) * sizeof(DeviceInfo_DeviceInfoType) /*HWIDs*/)
#define MSG_LENGTH_ABLE_COMMDEND       (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(ableCommand))
#define MSG_LENGTH_SYSTEM_STATUS       (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(systemStatus) + RELAYM_FN_NUM)
#if SYSTEM_BATTERY_CELL_NUM <= 255U
#define MSG_LENGTH_CELL_VOLTAGES       (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * SYSTEM_BATTERY_CELL_NUM))
#else
#define MSG_LENGTH_CELL_VOLTAGES       (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * 255U))
#define MSG_LENGTH_CELL_VOLTAGES2       (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * (SYSTEM_BATTERY_CELL_NUM - 255U)))
#endif
#define MSG_LENGTH_CELL_TEMPERATURES   (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(cellTemperatures) + (uint16)(1UL * SYSTEM_TEMP_CELL_NUM))
#define MSG_LENGTH_CELL_PEAK_DATA      (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(cellPeakData))
#define MSG_LENGTH_DTU_STATUS          (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(dtuStatus))
#define MSG_LENGTH_BALANCE_STATUS      (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(balanceStatus) + (uint16)(7UL + SYSTEM_BATTERY_CELL_NUM) / 8U)
#define MSG_LENGTH_ALARM_STATUS        (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(alarmStatus))
#define MSG_LENGTH_CHARGER_STATUS      (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(chargerStatus))
#define MSG_LENGTH_CUMU_INFO           (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(powerInfo))
#define MSG_LENGTH_GB32960_SUPPORT_CMDID  (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(gb32960SupportCmdId) + GB32960_SUPPORT_COMMAND_NUMBER)
#define MSG_LENGTH_DEVICE_CHADISCHATIME   (1U/*信息类型标识*/ + MEMBER_SIZEOF_MSG_HEADER(chargeDischargeTime))


static GBRt_MsgBufferWithHeartbeat headerBufferWithHeartbeat;
static void fillDeviceInfo(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.deviceInfo.messageLength = sizeof(msgHeader->dataHeader.deviceInfo) - 2U;
    (void)memcpy(msgHeader->dataHeader.deviceInfo.releaseName, AppInfoTag.ReleaseName, sizeof(msgHeader->dataHeader.deviceInfo.releaseName));
    (void)memcpy(msgHeader->dataHeader.deviceInfo.SCID, AppInfoTag.SourceCommitId, sizeof(msgHeader->dataHeader.deviceInfo.SCID));
    msgHeader->dataHeader.deviceInfo.customMsgVersion = MSG_VERSION;
    msgHeader->dataHeader.deviceInfo.fwAddrSpace = AppInfoTag.FWAddrSpace;
    msgHeader->dataHeader.deviceInfo.runTime = OSTimeGet();
    msgHeader->dataHeader.deviceInfo.runMode = (uint8)RuntimeM_GetMode();
    msgHeader->dataHeader.deviceInfo.chargeableCycles = 0U;
}

static const GB32960_CopySegmentType copySegmentsDeviceInfo[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(deviceInfo), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(deviceInfo), 1U + MEMBER_SIZEOF_MSG_HEADER(deviceInfo) + 16U, PTR_TYPE_DATA, {AppInfoTag.FWID}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(deviceInfo) + 16U, 1U + MEMBER_SIZEOF_MSG_HEADER(deviceInfo) + 32U, PTR_TYPE_DATA, {AppInfoTag.BurnID}},
};

static const GB32960_CopySegmentType copyRecordSegmentsAbleCommand[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(ableCommand), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
};

static void fillDeviceList(GBRt_MsgBuffer *msgHeader) {
    (void)strcpy((sint8 *)msgHeader->dataHeader.deviceList.vinCode, "1234567890ABCDEF");
    msgHeader->dataHeader.deviceList.deviceCnt = SYSTEM_BMU_NUM + 1U;
}

static void fillAbleCommand(GBRt_MsgBuffer *msgHeader) {
    uint16 temp = 0xFFU;

    msgHeader->dataHeader.ableCommand.messageLength = sizeof(msgHeader->dataHeader.ableCommand) - 2U;
    (void)ParameterM_EeepRead(PARAMETERM_EEEP_REMOTEABLE_COMMAND_INDEX, &temp);
    msgHeader->dataHeader.ableCommand.command = (uint8)temp;
}

const GB32960_CopySegmentType copySegmentsDeviceList[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(deviceList), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(deviceList), 1U + MEMBER_SIZEOF_MSG_HEADER(deviceList) + 16U, PTR_TYPE_GET_DATA, {HardwareSn_GetPtr}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(deviceList) + 16U, 1U + MEMBER_SIZEOF_MSG_HEADER(deviceList) + 26U, PTR_TYPE_DATA, {AppInfoTag.FWVersion}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(deviceList) + 26U, 1U + MEMBER_SIZEOF_MSG_HEADER(deviceList) + 26U + SYSTEM_BMU_NUM * sizeof(DeviceInfo_DeviceInfoType), PTR_TYPE_GET_DATA, {DeviceInfo_GetPtr}},
};

static void fillCharDisTime(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.chargeDischargeTime.messageLength = sizeof(msgHeader->dataHeader.chargeDischargeTime) - 2U;
    msgHeader->dataHeader.chargeDischargeTime.chargedTime = Statistic_GetCumuChgTime();
    msgHeader->dataHeader.chargeDischargeTime.dischargedTime = Statistic_GetCumuDchgTime();
}

static void fillSystemStatus(GBRt_MsgBuffer *msgHeader) {
    uint32 validity_test;
    GBRt_MsgBufferWithHeartbeat *msgHeaderWithHeartbeat = container_of(msgHeader, GBRt_MsgBufferWithHeartbeat, msgBuf);/*lint !e586 !e507 !e413*/
    msgHeader->dataHeader.systemStatus.messageLength = sizeof(msgHeader->dataHeader.systemStatus) + RELAYM_FN_NUM - 2U;
    msgHeader->dataHeader.systemStatus.heardbeat = msgHeaderWithHeartbeat->heardbeat++;
    msgHeader->dataHeader.systemStatus.supplyVoltage = HWDiagnosis_GetBoardVoltage(HWDIAGNOSIS_BCU_VOLT_24V);
    msgHeader->dataHeader.systemStatus.resetSourse = (uint8)RuntimeM_GetResetSouce();
    validity_test = Statistic_GetBcuTotalVoltage();
    if ( validity_test < 6553500UL) {
        msgHeader->dataHeader.systemStatus.bcuTotalVoltage = (uint16)(validity_test / 100UL);
    } else {
        msgHeader->dataHeader.systemStatus.bcuTotalVoltage = 0U;
    }
    msgHeader->dataHeader.systemStatus.HVBPOS = HV_GetVoltage(HV_CHANNEL_BPOS);
    msgHeader->dataHeader.systemStatus.HV1 = HV_GetVoltage(HV_CHANNEL_HV1);
    msgHeader->dataHeader.systemStatus.HV2 = HV_GetVoltage(HV_CHANNEL_HV2);
    msgHeader->dataHeader.systemStatus.HV3 = HV_GetVoltage(HV_CHANNEL_HV3);
    msgHeader->dataHeader.systemStatus.HV4 = HV_GetVoltage(HV_CHANNEL_HV4);
    msgHeader->dataHeader.systemStatus.HV5 = HV_GetVoltage(HV_CHANNEL_HV5);
    msgHeader->dataHeader.systemStatus.DI1 = DigitalInput_GetDinLevel(DIGITALINPUT_BCU_DIN1);
    msgHeader->dataHeader.systemStatus.DI2 = DigitalInput_GetDinLevel(DIGITALINPUT_BCU_DIN2);
    msgHeader->dataHeader.systemStatus.SW1 = (uint8)DigitalInput_GetSwitchState(DIGITALINPUT_BCU_SW1);
    msgHeader->dataHeader.systemStatus.SW2 = (uint8)DigitalInput_GetSwitchState(DIGITALINPUT_BCU_SW2);
    msgHeader->dataHeader.systemStatus.chargeStartDiagFault = (uint8)ChargeM_GetStartDiagFault();
    msgHeader->dataHeader.systemStatus.chargeDiagFaultFlag = (uint8)ChargeM_GetDiagFaultFlag();
    msgHeader->dataHeader.systemStatus.chargeDiagFaultAction = (uint8)ChargeM_GetDiagFaultAction();
    msgHeader->dataHeader.systemStatus.ChargerGBReadyFault = (uint8)ChargeM_GetChargerGBReadyFault();
    msgHeader->dataHeader.systemStatus.chargeOtherFault = (uint8)ChargeM_GetOthersFault();
    msgHeader->dataHeader.systemStatus.dischargeStartDiagFault = (uint8)DischargeM_GetStartDiagFault();
    msgHeader->dataHeader.systemStatus.dischargeDiagFaultFlag = (uint8)DischargeM_GetDiagFaultFlag();
    msgHeader->dataHeader.systemStatus.dischargeFaultDiagFaultAction = (uint8)DischargeM_GetDiagFaultAction();
    msgHeader->dataHeader.systemStatus.dischargeOtherFault = (uint8)DischargeM_GetOthersFault();
    msgHeader->dataHeader.systemStatus.SOCEmptyReason = (uint8)SocDiagCalib_GetEmptyReason();
    msgHeader->dataHeader.systemStatus.SOCFullReason = (uint8)SocDiagCalib_GetFullReason();
    msgHeader->dataHeader.systemStatus.dSoc = Soc_Get();
    if (msgHeader->dataHeader.systemStatus.runStatus == 0X03U) {
        msgHeader->dataHeader.systemStatus.integralRatio = (uint16)(Soc_GetChgEfficiency() / 10U);
    } else {
        msgHeader->dataHeader.systemStatus.integralRatio = (uint16)(Soc_GetDchgEfficiency() / 10U);
    }
    msgHeader->dataHeader.systemStatus.soc = ModelRealSoc_Get();
    msgHeader->dataHeader.systemStatus.soh = Soh_Get();
    msgHeader->dataHeader.systemStatus.insuResSys = Insu_GetSystem();
    msgHeader->dataHeader.systemStatus.insuResPos = Insu_GetPositive();
    msgHeader->dataHeader.systemStatus.insuResNeg = Insu_GetNegative();
    msgHeader->dataHeader.systemStatus.runStatus = (ChargeConnectM_GetConnectType() != CHARGE_TYPE_NONE) ? 3U : 2U;
    msgHeader->dataHeader.systemStatus.wakeSignal = RuntimeM_GetWakeSignal();
    msgHeader->dataHeader.systemStatus.relayNum = RELAYM_FN_NUM;
    //for (i = 0; i < RELAYM_FN_NUM; ++i) {
    //    msgHeader->dataHeader.systemStatus.relayStatus[i] = RelayM_GetActualStatus(i) == RELAYM_ACTUAL_ON ? 1: 0;
    //}
}

static uint16 copyRelayData(uint16 offset, uint8 *buf, uint16 len) {
    uint16 i;
    uint8 dat;
    uint8 state;
    for (i = 0U; i < len; i++) {
        state = RelayM_GetDiagnosisStatus((uint8)(offset + i));
        if (RELAYM_DIAGNOSIS_IS_DRIVER_ERR(state)) {
            dat = 0x02U;
        } else if (RELAYM_DIAGNOSIS_IS_ADHESIVE(state)) {
            dat = 0x03U;
        } else if (RELAYM_DIAGNOSIS_IS_OPEN(state)) {
            dat = 0x04U;
        } else if (RELAYM_DIAGNOSIS_IS_AUX_CONTACT_ERR(state)) {
            dat = 0x05U;
        } else {
            dat = RelayM_GetActualStatus((uint8)(offset + i)) == RELAYM_ACTUAL_ON ? 1U : 0U;
        }
        *buf++ = dat;
    }

    return len;
}

static const GB32960_CopySegmentType copySegmentschargeDischargeTime[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(chargeDischargeTime), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
};


static const GB32960_CopySegmentType copySegmentsSystemStatus[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(systemStatus), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(systemStatus), 1U + MEMBER_SIZEOF_MSG_HEADER(systemStatus) + RELAYM_FN_NUM, PTR_TYPE_COPY_DATA, {copyRelayData}}
};


static void fillCellVoltage(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.cellVoltages.totalSysNum = 1U;
    msgHeader->dataHeader.cellVoltages.sysNumOfThisFrame = 1U;
    msgHeader->dataHeader.cellVoltages.totalVoltage = Statistic_GetBcu100mvTotalVoltage();
    msgHeader->dataHeader.cellVoltages.current1 = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);
    msgHeader->dataHeader.cellVoltages.current2 = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_HEATER);
    msgHeader->dataHeader.cellVoltages.totalCellNum = SYSTEM_BATTERY_CELL_NUM;
    msgHeader->dataHeader.cellVoltages.startCellOfThisFrame = 1U;
#if SYSTEM_BATTERY_CELL_NUM >= 256U
    msgHeader->dataHeader.cellVoltages.cellNumOfThisFrame = 255U;
#else
    msgHeader->dataHeader.cellVoltages.cellNumOfThisFrame = (uint8)(SYSTEM_BATTERY_CELL_NUM);
#endif
}


static const GB32960_CopySegmentType copySegmentsCellVoltage[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(cellVoltages), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
#if SYSTEM_BATTERY_CELL_NUM >= 256U
    {1U + MEMBER_SIZEOF_MSG_HEADER(cellVoltages), 1U + MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * 255UL), PTR_TYPE_GET_DATA, {CellDataM_GetVoltagePtr}}
#else
    {1U + MEMBER_SIZEOF_MSG_HEADER(cellVoltages), 1U + MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * SYSTEM_BATTERY_CELL_NUM), PTR_TYPE_GET_DATA, {CellDataM_GetVoltagePtr}}
#endif
};

#if SYSTEM_BATTERY_CELL_NUM >= 256U
const App_VoltageType *CellDataM_GetVoltagePtr2(void);
const App_VoltageType *CellDataM_GetVoltagePtr2(void) {
    const App_VoltageType *celldataPtr =  CellDataM_GetVoltagePtr();
    return &celldataPtr[255];
}

static void fillCellVoltage2(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.cellVoltages.totalSysNum = 1U;
    msgHeader->dataHeader.cellVoltages.sysNumOfThisFrame = 1U;
    msgHeader->dataHeader.cellVoltages.totalVoltage = Statistic_GetBcu100mvTotalVoltage();
    msgHeader->dataHeader.cellVoltages.current1 = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);
    msgHeader->dataHeader.cellVoltages.current2 = CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_HEATER);
    msgHeader->dataHeader.cellVoltages.totalCellNum = SYSTEM_BATTERY_CELL_NUM;
    msgHeader->dataHeader.cellVoltages.startCellOfThisFrame = 256U;
    msgHeader->dataHeader.cellVoltages.cellNumOfThisFrame = (uint8)(SYSTEM_BATTERY_CELL_NUM - 255U);
}

static const GB32960_CopySegmentType copySegmentsCellVoltage2[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(cellVoltages), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(cellVoltages), 1U + MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * (SYSTEM_BATTERY_CELL_NUM - 255U)), PTR_TYPE_GET_DATA, {CellDataM_GetVoltagePtr2}}
};
#endif

static void fillCellTemperatures(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.cellTemperatures.totalSysNum = 1U;
    msgHeader->dataHeader.cellTemperatures.sysNumOfThisFrame = 1U;
    msgHeader->dataHeader.cellTemperatures.totalCellNum = SYSTEM_TEMP_CELL_NUM;
}

static uint16 copyTempData(uint16 offset, uint8 *buf, uint16 len) {
    uint16 i;
    const uint8 *tmpPtr = CellDataM_GetTempraturePtr() + offset;

    for (i = 0U; i < len; i++) {
        if (*tmpPtr > 10U && *tmpPtr < 250U) {
            *buf++  = *tmpPtr++ - 10U;
        } else {
            *buf++ = *tmpPtr++;
        }
    }
    return i;
}

static const GB32960_CopySegmentType copySegmentsCellTemperatures[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(cellTemperatures), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(cellTemperatures), 1U + MEMBER_SIZEOF_MSG_HEADER(cellTemperatures) + (uint16)(1UL * SYSTEM_TEMP_CELL_NUM), PTR_TYPE_COPY_DATA, {copyTempData}}
};


static void fillCellPeakData(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.cellPeakData.highVoltageSysNum = 1U;
    msgHeader->dataHeader.cellPeakData.highVoltageCellNum = Statistic_GetBcuHvLogicIndex(0U) + 1U;
    msgHeader->dataHeader.cellPeakData.highVoltageValue = Statistic_GetBcuHv(0U);
    msgHeader->dataHeader.cellPeakData.lowVoltageSysNum = 1U;
    msgHeader->dataHeader.cellPeakData.lowVoltageCellNum = Statistic_GetBcuLvLogicIndex(0U) + 1U;
    msgHeader->dataHeader.cellPeakData.lowVoltageValue = Statistic_GetBcuLv(0U);
    msgHeader->dataHeader.cellPeakData.highTemperatureSysNum = 1U;
    msgHeader->dataHeader.cellPeakData.highTemperatureCellNum = Statistic_GetBcuHtLogicIndex(0U) + 1U;
    msgHeader->dataHeader.cellPeakData.highTemperatureValue = Statistic_GetBcuHt(0U) - 10U;
    msgHeader->dataHeader.cellPeakData.lowTemperatureSysNum = 1U;
    msgHeader->dataHeader.cellPeakData.lowTemperatureCellNum = Statistic_GetBcuLtLogicIndex(0U) + 1U;
    msgHeader->dataHeader.cellPeakData.lowTemperatureValue = Statistic_GetBcuLt(0U) - 10U;
}

static const GB32960_CopySegmentType copySegmentsCellPeakData[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(cellPeakData), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
};

static void fillDtuStatus(GBRt_MsgBuffer *msgHeader) {
    uint32 lacci[2];
    msgHeader->dataHeader.dtuStatus.supplyVoltage = DtuM35_GetSupplyVoltage();
    msgHeader->dataHeader.dtuStatus.ops = DtuM35_GetOPS();
    DtuM35_GetSingalQuality(&msgHeader->dataHeader.dtuStatus.signalStrength,
                            &msgHeader->dataHeader.dtuStatus.errorBitrate);
    DtuM35_GetLacCi(&lacci[0]);
    msgHeader->dataHeader.dtuStatus.lac = (uint16)lacci[0];
    msgHeader->dataHeader.dtuStatus.ci = lacci[1];
    DtuM35_GetLoc(&msgHeader->dataHeader.dtuStatus.longtitude);
}

static const GB32960_CopySegmentType copySegmentsDtuStatus[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(dtuStatus), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
};

static void fillChargerStatus(GBRt_MsgBuffer *msgHeader) {
    uint8 temp;
    uint32 temp32;
    Charge_ChargeType dcac_type, dc2_type;

    dcac_type = ChargeConnectM_GetDCACConnectType();
    dc2_type = ChargeConnectM_GetDC2ConnectType();

    msgHeader->dataHeader.chargerStatus.messageLength = sizeof(msgHeader->dataHeader.chargerStatus) - 2U;

    if (dcac_type != CHARGE_TYPE_NONE) {
        temp = dcac_type;
    } else if (dc2_type != CHARGE_TYPE_NONE) {
        temp = 3U;
    } else {
        temp = 0U;
    }
    msgHeader->dataHeader.chargerStatus.connection = temp;
    temp32 = Statistic_GetEclipseChargeTime();
    if (temp32 > 0xFFFFU) {
        temp32 = 0xFFFFU;
    }
    msgHeader->dataHeader.chargerStatus.chargedTime = (uint16)temp32;

    if ((dcac_type == CHARGE_TYPE_NONE) && (dc2_type != CHARGE_TYPE_NONE)) {
        msgHeader->dataHeader.chargerStatus.requestChargeVoltMax = ExternCanComm_GetChargeVoltMax();
        msgHeader->dataHeader.chargerStatus.requestChargeCurrentMax = ExternCanComm_GetChargeCurrentMax();
        msgHeader->dataHeader.chargerStatus.outputVoltage = ExternCanComm_GetChargerOutputHV();
        msgHeader->dataHeader.chargerStatus.outputCurrent = (uint16)ExternCanComm_GetChargerOutputCurrent();
        msgHeader->dataHeader.chargerStatus.errorStatus = ExternCanComm_GetChargerFaultBitmap();
    } else {
        msgHeader->dataHeader.chargerStatus.requestChargeVoltMax = ChargerComm_GetChargeVoltMax();
        msgHeader->dataHeader.chargerStatus.requestChargeCurrentMax = ChargerComm_GetChargeCurrentMax();
        msgHeader->dataHeader.chargerStatus.outputVoltage = ChargerComm_GetChargerOutputHV();
        msgHeader->dataHeader.chargerStatus.outputCurrent = (uint16)ChargerComm_GetChargerOutputCurrent();
        msgHeader->dataHeader.chargerStatus.errorStatus = ChargerComm_GetChargerFaultBitmap();
    }
    msgHeader->dataHeader.chargerStatus.s2Status =  ChargeConnectM_GetS2();
    msgHeader->dataHeader.chargerStatus.ccResistor = ChargerConnectM_GetCCxResistanceStatus(CHARGECONNECTM_ADC_CC_CHANNEL);
    msgHeader->dataHeader.chargerStatus.cc2Resistor = ChargerConnectM_GetCCxResistanceStatus(CHARGECONNECTM_ADC_CC2_CHANNEL);
    msgHeader->dataHeader.chargerStatus.cpFreq = CP_GetFrequence();
    msgHeader->dataHeader.chargerStatus.cpDuty = CP_GetDuty();
    msgHeader->dataHeader.chargerStatus.elStatus = (uint8)EL_GetDiagnosisStatus(0U);
    if (msgHeader->dataHeader.chargerStatus.connection == CHARGE_TYPE_AC) {
        temp = ChgSckTmpM_GetTemperature(CHGSCKTMPM_TEMPERATURE_AC_AL);
        if (temp >= 10U && temp <= 250U) {
            temp -= 10U;
        }
        msgHeader->dataHeader.chargerStatus.connectorTemp[0U] = temp;
        temp = ChgSckTmpM_GetTemperature(CHGSCKTMPM_TEMPERATURE_AC_BN);
        if (temp >= 10U && temp <= 250U) {
            temp -= 10U;
        }
        msgHeader->dataHeader.chargerStatus.connectorTemp[1U] = temp;
        temp = ChgSckTmpM_GetTemperature(CHGSCKTMPM_TEMPERATURE_AC_C);
        if (temp >= 10U && temp <= 250U) {
            temp -= 10U;
        }
        msgHeader->dataHeader.chargerStatus.connectorTemp[2U] = temp;
        msgHeader->dataHeader.chargerStatus.connectorTemp[3U] = 0xFFU;
    } else if (msgHeader->dataHeader.chargerStatus.connection == CHARGE_TYPE_DC) {
        temp = ChgSckTmpM_GetTemperature(CHGSCKTMPM_TEMPERATURE_DC_POSITIVE);
        if (temp >= 10U && temp <= 250U) {
            temp -= 10U;
        }
        msgHeader->dataHeader.chargerStatus.connectorTemp[0U] = temp;
        temp = ChgSckTmpM_GetTemperature(CHGSCKTMPM_TEMPERATURE_DC_NEGATIVE);
        if (temp >= 10U && temp <= 250U) {
            temp -= 10U;
        }
        msgHeader->dataHeader.chargerStatus.connectorTemp[1U] = temp;
        msgHeader->dataHeader.chargerStatus.connectorTemp[2U] = 0xFFU;
        msgHeader->dataHeader.chargerStatus.connectorTemp[3U] = 0xFFU;
    } else {
        msgHeader->dataHeader.chargerStatus.connectorTemp[0U] = 0xFFU;
        msgHeader->dataHeader.chargerStatus.connectorTemp[1U] = 0xFFU;
        msgHeader->dataHeader.chargerStatus.connectorTemp[2U] = 0xFFU;
        msgHeader->dataHeader.chargerStatus.connectorTemp[3U] = 0xFFU;
    }
}

static const GB32960_CopySegmentType copySegmentsChargerStatus[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(chargerStatus), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
};

static void fillBalanceStatus(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.balanceStatus.totalCellNum = SYSTEM_BATTERY_CELL_NUM;
}

static const GB32960_CopySegmentType copySegmentsBalanceStatus[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(balanceStatus), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(balanceStatus), 1U + MEMBER_SIZEOF_MSG_HEADER(balanceStatus) + (uint16)(7UL + SYSTEM_BATTERY_CELL_NUM) / 8U, PTR_TYPE_GET_DATA, {BalanceM_GetBalanceStatusPtr}},
};


static Diagnosis_LevelType alarms[DIAGNOSIS_ITEM_DEFAULT_NUM];
static uint8 alaramLengthCaculated = 0U;
static uint8 alaramNum = 0U;
static uint8 alarmCopyOffset = 0U;
static void fillAlarmStatus(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.alarmStatus.alarmNum = alaramNum;
}

static uint16 copyAlarmData(uint16 offset, uint8 *buf, uint16 len) {
    uint16 copyed = 0U;

    (void)offset;

    if (alarmCopyOffset >= (uint8)DIAGNOSIS_ITEM_MAX_NUM) {
        (void)memset(buf, (int)DIAGNOSIS_LEVEL_NONE, len);
        copyed = len;
    } else {
        while (len >= 2U && alarmCopyOffset < ARRAY_SIZE(alarms)) {
            if (alarms[alarmCopyOffset] != DIAGNOSIS_LEVEL_NONE) {
                len -= 2U;
                copyed += 2U;
                *buf++ = (uint8)Diagnosis_IndexToItem(alarmCopyOffset);
                *buf++ = alarms[alarmCopyOffset];
            }
            ++alarmCopyOffset;
        }
    }
    return copyed;
}

static uint16 getAlarmLength(void) {
    if (alaramLengthCaculated == 0U) {
        uint8 i;
        alarmCopyOffset = 0U;
        alaramNum = 0U;
        Diagnosis_GetAllLevelByIndex(alarms, ARRAY_SIZE(alarms));
        for (i = 0U; i < ARRAY_SIZE(alarms); ++i) {
            if (alarms[i] != DIAGNOSIS_LEVEL_NONE) {
                alaramNum++;
            }
        }
        alaramLengthCaculated = 1U;
    }
    return 1U + MEMBER_SIZEOF_MSG_HEADER(alarmStatus) + 2U * (uint16)alaramNum;
}

static void clearAlarmLength(void) {
    alaramLengthCaculated = 0U;
}

static const GB32960_CopySegmentType copySegmentsAlarmStatus[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(alarmStatus), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(alarmStatus), 0xFFFEU, PTR_TYPE_COPY_DATA, {copyAlarmData}},
};


static void fillGB32960CommandListNum(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.gb32960SupportCmdId.num = GB32960_SUPPORT_COMMAND_NUMBER;
}

static const GB32960_CopySegmentType copySupportCommandIDs[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(gb32960SupportCmdId), PTR_TYPE_DATA, {&headerBufferWithHeartbeat.msgBuf}},
    {1U + MEMBER_SIZEOF_MSG_HEADER(gb32960SupportCmdId), MSG_LENGTH_GB32960_SUPPORT_CMDID, PTR_TYPE_DATA, {GB32960_SupportCommandId}},
};

const GB32960_RTMessageItemType loginOnceData[] = {
    {0x92U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_DEVICE_INFO, NULL, (GB32960_FillMessageFuncType)fillDeviceInfo, copySegmentsDeviceInfo, (uint8)ARRAY_SIZE(copySegmentsDeviceInfo)},
    {0x97U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_ABLE_COMMDEND, NULL, (GB32960_FillMessageFuncType)fillAbleCommand, copyRecordSegmentsAbleCommand, (uint8)ARRAY_SIZE(copyRecordSegmentsAbleCommand)},
    {0x82U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_DEVICE_LIST, NULL, (GB32960_FillMessageFuncType)fillDeviceList, copySegmentsDeviceList, (uint8)ARRAY_SIZE(copySegmentsDeviceList)},
    {0x91U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_GB32960_SUPPORT_CMDID, NULL, (GB32960_FillMessageFuncType)fillGB32960CommandListNum, copySupportCommandIDs, (uint8)ARRAY_SIZE(copySupportCommandIDs)},
    {0xFFU, TRUE, LEN_TYPE_LENGTH, 0x00U, NULL, NULL, NULL, 0U}
};

const GB32960_RTMessageItemType intervalData[] = {
    {0x95U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_DEVICE_CHADISCHATIME, NULL, (GB32960_FillMessageFuncType)fillCharDisTime, copySegmentschargeDischargeTime, (uint8)ARRAY_SIZE(copySegmentschargeDischargeTime)},
    {0x93U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_SYSTEM_STATUS, NULL, (GB32960_FillMessageFuncType)fillSystemStatus, copySegmentsSystemStatus, (uint8)ARRAY_SIZE(copySegmentsSystemStatus)},
    {0x9AU, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_CELL_VOLTAGES, NULL, (GB32960_FillMessageFuncType)fillCellVoltage, copySegmentsCellVoltage, (uint8)ARRAY_SIZE(copySegmentsCellVoltage)},
#if SYSTEM_BATTERY_CELL_NUM >= 256U
    {0x9AU, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_CELL_VOLTAGES2, NULL, (GB32960_FillMessageFuncType)fillCellVoltage2, copySegmentsCellVoltage2, (uint8)ARRAY_SIZE(copySegmentsCellVoltage2)},
#endif
    {0x09U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_CELL_TEMPERATURES, NULL, (GB32960_FillMessageFuncType)fillCellTemperatures, copySegmentsCellTemperatures, (uint8)ARRAY_SIZE(copySegmentsCellTemperatures)},
    {0x9BU, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_CELL_PEAK_DATA, NULL, (GB32960_FillMessageFuncType)fillCellPeakData, copySegmentsCellPeakData, (uint8)ARRAY_SIZE(copySegmentsCellPeakData)},
    {0x96U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_DTU_STATUS, NULL, (GB32960_FillMessageFuncType)fillDtuStatus, copySegmentsDtuStatus, (uint8)ARRAY_SIZE(copySegmentsDtuStatus)},
    {0x86U, TRUE, LEN_TYPE_LENGTH, MSG_LENGTH_BALANCE_STATUS, NULL, (GB32960_FillMessageFuncType)fillBalanceStatus, copySegmentsBalanceStatus, (uint8)ARRAY_SIZE(copySegmentsBalanceStatus)},
    {0x99U, FALSE, LEN_TYPE_LENGTH, MSG_LENGTH_CHARGER_STATUS, NULL, (GB32960_FillMessageFuncType)fillChargerStatus, copySegmentsChargerStatus, (uint8)ARRAY_SIZE(copySegmentsChargerStatus)},
    {0x87U, TRUE, LEN_TYPE_GET_LENGTH, 0U, getAlarmLength, (GB32960_FillMessageFuncType)fillAlarmStatus, copySegmentsAlarmStatus, (uint8)ARRAY_SIZE(copySegmentsAlarmStatus)},
    {0xFFU, TRUE, LEN_TYPE_LENGTH, 0x00U, NULL, NULL, NULL, 0U}
};


const GB32960_RtMessageConfigDataType GB32960RtMessageConfigData = {
    &headerBufferWithHeartbeat.msgBuf.GBRtHeader,
    loginOnceData,
    intervalData,
    clearAlarmLength,
};


#include "SaveM.h"

static GBRt_MsgBufferWithHeartbeat recordHeaderWithHeartbeat;

/**
 * \brief      20170315: 经讨论决定,使用国标协议版本号低字节作为数据存储记录类型的版本标识
 */
#if MSG_VERSION > 0U
#define GB_TYPE_TO_RECORD_TYPE(type)    ((((uint16)MSG_VERSION << 8) & 0xFF00U) | type)
#else
#define GB_TYPE_TO_RECORD_TYPE(type)    (type)
#endif

static const GB32960_CopySegmentType copyRecordSegmentschargeDischargeTime[] = {
    {0U, 1U + MEMBER_SIZEOF_MSG_HEADER(chargeDischargeTime), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
};

static const GB32960_CopySegmentType copyRecordSegmentsDeviceInfo[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(deviceInfo), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(deviceInfo), MEMBER_SIZEOF_MSG_HEADER(deviceInfo) + 16U, PTR_TYPE_DATA, {AppInfoTag.FWID}},
    {MEMBER_SIZEOF_MSG_HEADER(deviceInfo) + 16U, MEMBER_SIZEOF_MSG_HEADER(deviceInfo) + 32U, PTR_TYPE_DATA, {AppInfoTag.BurnID}},
};

const GB32960_CopySegmentType copyRecordSegmentsDeviceList[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(deviceList), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(deviceList), MEMBER_SIZEOF_MSG_HEADER(deviceList) + 16U, PTR_TYPE_GET_DATA, {HardwareSn_GetPtr}},
    {MEMBER_SIZEOF_MSG_HEADER(deviceList) + 16U, MEMBER_SIZEOF_MSG_HEADER(deviceList) + 26U, PTR_TYPE_DATA, {AppInfoTag.FWVersion}},
    {MEMBER_SIZEOF_MSG_HEADER(deviceList) + 26U, MEMBER_SIZEOF_MSG_HEADER(deviceList) + 26U + SYSTEM_BMU_NUM * sizeof(DeviceInfo_DeviceInfoType), PTR_TYPE_GET_DATA, {DeviceInfo_GetPtr}},
};

static const GB32960_CopySegmentType copyRecordSegmentsSystemStatus[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(systemStatus), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(systemStatus), MEMBER_SIZEOF_MSG_HEADER(systemStatus) + RELAYM_FN_NUM, PTR_TYPE_COPY_DATA, {copyRelayData}}
};

#if SYSTEM_BATTERY_CELL_NUM < 256U
static const GB32960_CopySegmentType copyRecordSegmentsCellVoltage[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(cellVoltages), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(cellVoltages), MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * SYSTEM_BATTERY_CELL_NUM), PTR_TYPE_GET_DATA, {CellDataM_GetVoltagePtr}}
};
#else
static const GB32960_CopySegmentType copyRecordSegmentsCellVoltage[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(cellVoltages), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(cellVoltages), MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * 255U), PTR_TYPE_GET_DATA, {CellDataM_GetVoltagePtr}}
};
static const GB32960_CopySegmentType copyRecordSegmentsCellVoltage2[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(cellVoltages), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(cellVoltages), MEMBER_SIZEOF_MSG_HEADER(cellVoltages) + (uint16)(2UL * (SYSTEM_BATTERY_CELL_NUM - 255U)), PTR_TYPE_GET_DATA, {CellDataM_GetVoltagePtr2}}
};
#endif

static const GB32960_CopySegmentType copyRecordSegmentsCellTemperatures[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(cellTemperatures), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(cellTemperatures), MEMBER_SIZEOF_MSG_HEADER(cellTemperatures) + (uint16)(1UL * SYSTEM_TEMP_CELL_NUM), PTR_TYPE_COPY_DATA, {copyTempData}}
};

static const GB32960_CopySegmentType copyRecordSegmentsCellPeakData[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(cellPeakData), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
};

static const GB32960_CopySegmentType copyRecordSegmentsDtuStatus[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(dtuStatus), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
};

static const GB32960_CopySegmentType copyRecordSegmentsChargerStatus[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(chargerStatus), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
};

static const GB32960_CopySegmentType copyRecordSegmentsBalanceStatus[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(balanceStatus), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(balanceStatus), MEMBER_SIZEOF_MSG_HEADER(balanceStatus) + (uint16)(7UL + SYSTEM_BATTERY_CELL_NUM) / 8U, PTR_TYPE_GET_DATA, {BalanceM_GetBalanceStatusPtr}},
};

static void fillPowerInfoRecord(GBRt_MsgBuffer *msgHeader) {
    msgHeader->dataHeader.powerInfo.chgType = (uint8)Soc_ConfigInfo.ChgCumuInfo.type;
    msgHeader->dataHeader.powerInfo.chgResoltion = Soc_ConfigInfo.ChgCumuInfo.resoltion;
    msgHeader->dataHeader.powerInfo.chgCumu = Soc_GetChgPower();
    msgHeader->dataHeader.powerInfo.totalChgCumu = Soc_GetCumuChgPower();
    msgHeader->dataHeader.powerInfo.dchgType = (uint8)Soc_ConfigInfo.DchgCumuInfo.type;
    msgHeader->dataHeader.powerInfo.dchgResoltion = Soc_ConfigInfo.DchgCumuInfo.resoltion;
    msgHeader->dataHeader.powerInfo.dchgCumu = Soc_GetDchgPower();
    msgHeader->dataHeader.powerInfo.totalDchgCumu = Soc_GetCumuDchgPower();
}

static const GB32960_CopySegmentType copyRecordSegmentsPowerInfo[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(powerInfo), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
};

static Diagnosis_LevelType alarmsRecord[DIAGNOSIS_ITEM_MAX_NUM];
static uint8 alaramNumRecord = 0U;
static uint8 alarmCopyOffsetRecord = 0U;
static void fillAlarmStatusRecord(GBRt_MsgBuffer *msgHeader) {
    uint8 i;
    alarmCopyOffsetRecord = 0U;
    alaramNumRecord = 0U;
    Diagnosis_GetAllLevelByIndex(alarmsRecord, ARRAY_SIZE(alarmsRecord));
    for (i = 0U; i < ARRAY_SIZE(alarmsRecord); ++i) {
        if (alarmsRecord[i] != DIAGNOSIS_LEVEL_NONE) {
            alaramNumRecord++;
        }
    }
    msgHeader->dataHeader.alarmStatus.alarmNum = alaramNumRecord;
}

static uint16 copyAlarmDataRecord(uint16 offset, uint8 *buf, uint16 len) {
    uint16 copyed = 0U;

    (void)offset;

    if (alarmCopyOffsetRecord >= (uint8)DIAGNOSIS_ITEM_MAX_NUM) {
        (void)memset(buf, (int)DIAGNOSIS_LEVEL_NONE, len);
        copyed = len;
    } else {
        while (len >= 2U && alarmCopyOffsetRecord < ARRAY_SIZE(alarmsRecord)) {
            if (alarmsRecord[alarmCopyOffsetRecord] != DIAGNOSIS_LEVEL_NONE) {
                len -= 2U;
                copyed += 2U;
                *buf++ = (uint8)Diagnosis_IndexToItem(alarmCopyOffsetRecord);
                *buf++ = alarmsRecord[alarmCopyOffsetRecord];
            }
            ++alarmCopyOffsetRecord;
        }
    }
    return copyed;
}

static uint16 getAlarmLengthRecord(void) {
    return 1U + MEMBER_SIZEOF_MSG_HEADER(alarmStatus) + 2U * (uint16)alaramNumRecord;
}

static const GB32960_CopySegmentType copyRecordSegmentsAlarmStatus[] = {
    {0U, MEMBER_SIZEOF_MSG_HEADER(alarmStatus), PTR_TYPE_DATA, {&recordHeaderWithHeartbeat.msgBuf.dataHeader}},
    {MEMBER_SIZEOF_MSG_HEADER(alarmStatus), 0xFFFEU, PTR_TYPE_COPY_DATA,  {copyAlarmDataRecord}},
};

static boolean has_dtu_module(void) {
    return DIO_CHANNEL_DTU_IS_PRESENT() ? TRUE : FALSE;
}

static boolean is_valid_in_charging_mode(void) {
    return CHARGECONNECTM_IS_CONNECT() ? TRUE : FALSE;
}

static const GB32960_RecordItemType onceDataList[] = {
    {GB_TYPE_TO_RECORD_TYPE(0x92U), MSG_LENGTH_DEVICE_INFO, NULL, (GB32960_FillMessageFuncType)fillDeviceInfo, copyRecordSegmentsDeviceInfo, (uint8)ARRAY_SIZE(copyRecordSegmentsDeviceInfo), NULL},
    {GB_TYPE_TO_RECORD_TYPE(0x97U), MSG_LENGTH_ABLE_COMMDEND, NULL, (GB32960_FillMessageFuncType)fillAbleCommand, copyRecordSegmentsAbleCommand, (uint8)ARRAY_SIZE(copyRecordSegmentsAbleCommand), NULL},
    {GB_TYPE_TO_RECORD_TYPE(0x82U), MSG_LENGTH_DEVICE_LIST, NULL, (GB32960_FillMessageFuncType)fillDeviceList, copyRecordSegmentsDeviceList, (uint8)ARRAY_SIZE(copyRecordSegmentsDeviceList), NULL},
    {0xFFFFU, 0x00U, NULL, NULL, NULL, 0U, NULL}
};

static const GB32960_RecordItemType fixedCycleDataList[] = {
    {GB_TYPE_TO_RECORD_TYPE(0x96U), MSG_LENGTH_DTU_STATUS, NULL, (GB32960_FillMessageFuncType)fillDtuStatus, copyRecordSegmentsDtuStatus, (uint8)ARRAY_SIZE(copyRecordSegmentsDtuStatus), has_dtu_module},
    {0xFFFFU, 0x00U, NULL, NULL, NULL, 0U, NULL}
};



static const GB32960_RecordItemType unfixedCycleDataList[] = {
    {GB_TYPE_TO_RECORD_TYPE(0x95U), MSG_LENGTH_DEVICE_CHADISCHATIME, NULL, (GB32960_FillMessageFuncType)fillCharDisTime, copyRecordSegmentschargeDischargeTime, (uint8)ARRAY_SIZE(copyRecordSegmentschargeDischargeTime), NULL},
    {GB_TYPE_TO_RECORD_TYPE(0x93U), MSG_LENGTH_SYSTEM_STATUS, NULL, (GB32960_FillMessageFuncType)fillSystemStatus, copyRecordSegmentsSystemStatus, (uint8)ARRAY_SIZE(copyRecordSegmentsSystemStatus), NULL},
    {GB_TYPE_TO_RECORD_TYPE(0x9AU), MSG_LENGTH_CELL_VOLTAGES, NULL, (GB32960_FillMessageFuncType)fillCellVoltage, copyRecordSegmentsCellVoltage, (uint8)ARRAY_SIZE(copyRecordSegmentsCellVoltage), NULL},
#if SYSTEM_BATTERY_CELL_NUM >= 256U
    {GB_TYPE_TO_RECORD_TYPE(0x9AU), MSG_LENGTH_CELL_VOLTAGES2, NULL, (GB32960_FillMessageFuncType)fillCellVoltage2, copyRecordSegmentsCellVoltage2, (uint8)ARRAY_SIZE(copyRecordSegmentsCellVoltage2), NULL},
#endif
    {GB_TYPE_TO_RECORD_TYPE(0x09U), MSG_LENGTH_CELL_TEMPERATURES, NULL, (GB32960_FillMessageFuncType)fillCellTemperatures, copyRecordSegmentsCellTemperatures, (uint8)ARRAY_SIZE(copyRecordSegmentsCellTemperatures), NULL},
    {GB_TYPE_TO_RECORD_TYPE(0x9BU), MSG_LENGTH_CELL_PEAK_DATA, NULL, (GB32960_FillMessageFuncType)fillCellPeakData, copyRecordSegmentsCellPeakData, (uint8)ARRAY_SIZE(copyRecordSegmentsCellPeakData), NULL},
    {GB_TYPE_TO_RECORD_TYPE(0x86U), MSG_LENGTH_BALANCE_STATUS, NULL, (GB32960_FillMessageFuncType)fillBalanceStatus, copyRecordSegmentsBalanceStatus, (uint8)ARRAY_SIZE(copyRecordSegmentsBalanceStatus), BalanceM_IsBalance},
    {GB_TYPE_TO_RECORD_TYPE(0x99U), MSG_LENGTH_CHARGER_STATUS, NULL, (GB32960_FillMessageFuncType)fillChargerStatus, copyRecordSegmentsChargerStatus, (uint8)ARRAY_SIZE(copyRecordSegmentsChargerStatus), is_valid_in_charging_mode},
    {GB_TYPE_TO_RECORD_TYPE(0x87U), 0U, getAlarmLengthRecord, (GB32960_FillMessageFuncType)fillAlarmStatusRecord, copyRecordSegmentsAlarmStatus, (uint8)ARRAY_SIZE(copyRecordSegmentsAlarmStatus), NULL},
    {GB_TYPE_TO_RECORD_TYPE(0x89U), MSG_LENGTH_CUMU_INFO, NULL, (GB32960_FillMessageFuncType)fillPowerInfoRecord, copyRecordSegmentsPowerInfo, (uint8)ARRAY_SIZE(copyRecordSegmentsPowerInfo), NULL},
    {0xFFFFU, 0x00U, NULL, NULL, NULL, 0U, NULL}
};

static uint32 UnfixedAlarmListCycle[] = {
    5000U,  /*!< 正常 */
    3000U,  /*!< 一级报警 */
    2000U,  /*!< 二级报警 */
    1000U,   /*!< 三级报警 */
    1000U,   /*!< 四级报警 */
};
static const Diagnosis_ItemType UnfixedAlarmList[] = {
    DIAGNOSIS_ITEM_CHG_HV, /**< 充电单体高压 */
    DIAGNOSIS_ITEM_DCHG_HV, /**< 放电单体高压 */
    DIAGNOSIS_ITEM_CHG_LV, /**< 充电单体低压 */
    DIAGNOSIS_ITEM_DCHG_LV, /**< 放电单体低压 */
    DIAGNOSIS_ITEM_CHG_HTV, /**< 充电总压高 */
    DIAGNOSIS_ITEM_DCHG_HTV, /**< 放电总压高 */
    DIAGNOSIS_ITEM_CHG_LTV, /**< 充电总压低 */
    DIAGNOSIS_ITEM_DCHG_LTV, /**< 放电总压低 */
    DIAGNOSIS_ITEM_CHG_DTV, /**< 充电总压差 */
    DIAGNOSIS_ITEM_DCHG_DTV, /**< 放电总压差 */
    DIAGNOSIS_ITEM_CHG_DV, /**< 充电压差 */
    DIAGNOSIS_ITEM_DCHG_DV, /**< 放电压差 */

    DIAGNOSIS_ITEM_CHG_HT, /**< 充电高温 */
    DIAGNOSIS_ITEM_DCHG_HT, /**< 放电高温 */
    DIAGNOSIS_ITEM_CHG_LT, /**< 充电低温 */
    DIAGNOSIS_ITEM_DCHG_LT, /**< 放电低温 */
    DIAGNOSIS_ITEM_CHG_DT, /**< 充电温差 */
    DIAGNOSIS_ITEM_DCHG_DT, /**< 放电温差 */

    DIAGNOSIS_ITEM_DC_CHG_OC, /**< 快充过流 */
    DIAGNOSIS_ITEM_AC_CHG_OC, /**< 慢充过流 */
    DIAGNOSIS_ITEM_FB_OC, /**< 回馈过流 */
    DIAGNOSIS_ITEM_DCHG_OC, /**< 持续放电过流 */
    DIAGNOSIS_ITEM_SP_OC, /**< 加速过流/瞬时放电过流 */

    DIAGNOSIS_ITEM_HSOC, /**< SOC高 */
    DIAGNOSIS_ITEM_LSOC, /**< SOC低 */

    DIAGNOSIS_ITEM_LEAK, /**< 漏电 */

    DIAGNOSIS_ITEM_CHG_HEAT_HT, /**< 充电加热高温 */
    DIAGNOSIS_ITEM_CHG_HEAT_TIMEOUT, /**< 充电加热超时 */
    DIAGNOSIS_ITEM_CHG_HEAT_OC, /**< 充电加热过流 */
    DIAGNOSIS_ITEM_SUPPLY_VOL_LOW, /**< 供电电压过低 */

    DIAGNOSIS_ITEM_VOLT_LINE, /**< 电压排线 */
    DIAGNOSIS_ITEM_TEMP_LINE, /**< 温感排线 */
    DIAGNOSIS_ITEM_INTER_COMM, /**< 内网通信 */

    DIAGNOSIS_ITEM_CHGSCKTMP_DC_POSITIVE, /**< 快充正极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_DC_NEGATIVE, /**< 快充负极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_AC_AL, /**< 慢充AL极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_AC_BN, /**< 慢充BN极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_AC_C, /**< 慢充C极高温 */

    DIAGNOSIS_ITEM_CHARGER_COMM, /**< 充电机通信 */
    DIAGNOSIS_ITEM_VCU_COMM, /**< 整车通信 */
    DIAGNOSIS_ITEM_FULL_CHARGE, /**< 满充 */
    DIAGNOSIS_ITEM_CHGSCKTMP_ABNORMAL, /**< 充电插座温感异常 */
    DIAGNOSIS_ITEM_PRECHARGE_FAILURE, /**< 预充失败 */
    DIAGNOSIS_ITEM_CURRENT_ABNORMAL, /**< 电流异常 */
    DIAGNOSIS_ITEM_BMS_INIT_FAILURE, /**< BMS初始化故障 */
    DIAGNOSIS_ITEM_HVIL_ABNORMAL, /**< HVIL故障 */
    DIAGNOSIS_ITEM_RELAY_ABNORMAL, /**< 继电器故障 */
    DIAGNOSIS_ITEM_HEAT_FAULT, /**< 加热故障 */
    DIAGNOSIS_ITEM_CC2_CONNECT_FAULT, /**< CC2连接故障 */
    DIAGNOSIS_ITEM_CC_CONNECT_FAULT, /**< CC连接故障 */
    DIAGNOSIS_ITEM_CP_CONNECT_FAULT, /**< CP连接故障 */
    DIAGNOSIS_ITEM_HEAT_TEMP_LINE_FAULT, /**< 加热温感异常 */
    DIAGNOSIS_ITEM_EL_FAULT, /**< 电子锁故障 */

    DIAGNOSIS_ITEM_SUPPLY_VOL_ABNOMAL, /**< 供电电压异常 */
    DIAGNOSIS_ITEM_CRASH_FAULT, /**< 碰撞故障 */
};

static uint32 unfixed_get_cycle(void) {
    uint8 i;

    Diagnosis_LevelType lv = DIAGNOSIS_LEVEL_NONE;
    Diagnosis_LevelType tmp;
    uint32 res;

    for (i = 0U; i < ARRAY_SIZE(UnfixedAlarmList); i++) {
        tmp = Diagnosis_GetLevel(UnfixedAlarmList[i]);
        if (tmp > lv) {
            lv = tmp;
        }
    }

    if (lv < ARRAY_SIZE(UnfixedAlarmListCycle)) {
        res = UnfixedAlarmListCycle[lv];
    } else {
        res = UnfixedAlarmListCycle[0];
    }

    return res;
}


uint16 GBRtMsg_GetRecordLength(const GB32960_RecordItemType *item) {
    uint16 length = 0U;
    if (item->getLength) {
        length = item->getLength();
    } else {
        length = item->length;
    }
    /**
     * 数据长度不包含信息类型标识,所以此处需要减去该大小
     */
    return length - sizeof(((GBRt_MsgBuffer *)0)->GBRtHeader);
}

const SaveM_RecordConfigDataType SaveMRecordConfigData = {
    /* GBRt_MsgBuffer *headerData; */ &recordHeaderWithHeartbeat.msgBuf.GBRtHeader,
    /* onPowerUpOnceData = */ {
        0U,
        NULL,
        onceDataList
    },
    /* fixedCycleData = */ {
        5000U,
        NULL,
        fixedCycleDataList
    },
    /* unfixedCycleData = */ {
        5000U,
        unfixed_get_cycle,
        unfixedCycleDataList
    }
};
