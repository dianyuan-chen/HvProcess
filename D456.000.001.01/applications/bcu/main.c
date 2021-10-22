#ifdef __HC12__

#include "Std_Types.h"
#include "ucos_ii.h"
#include "Mcu.h"
#include "Irq.h"
#include "CanEcho.h"
#include "Dcm.h"
#include "Can.h"
#include "CanIf.h"
#include "CanTp.h"
#include "Shell.h"
#include "Async_Looper.h"
#include "Async_Event.h"
#include "Port.h"
#include "Dio.h"
#include "Det.h"
#include "Adc.h"
#include "Hall.h"
#include "EL.h"
#include "Ads1018_Lcfg.h"
#include "InternalComm.h"
#include "Shunt.h"
#include "Hv.h"
#include "InnerTp_Lcfg.h"
#include "BridgeInsu_Lcfg.h"
#include "DatetimeM.h"
#include "DtuComm_M35.h"
#include "GB32960.h"
#include "XGate.h"
#include "HLSS.h"
#include "BalanceM.h"
#include "Statistic.h"
#include "DtuComm_M35_Lcfg.h"
#include "HardwareSn.h"
#include "DigitalInput.h"
#include "HWDiagnosis.h"
#include "AllInOneComm.h"
#include "RuntimeM.h"
#include "PwmCapture_Lcfg.h"
#include "CurrentM.h"
#include "Eeeprom.h"
#include "ParameterM.h"
#include "ChargeConnectM.h"
#include "ChgSckTmpM.h"
#include "SocCalib.h"
#include "Soh.h"
#include "J1939Tp.h"
#include "ChargerCommUser.h"
#include "ChargerCommGB.h"
#include "SaveM.h"
#include "GBRtMsg.h"
#include "VcuComm.h"
#include "VcuComm_Messages.h"
#include "HvProcess.h"
#include "PowerM.h"
#include "FullCharge.h"
#include "WatchDogM.h"
#include "PrechargeM.h"
#include "UserStrategy.h"
#include "ChargeM.h"
#include "DischargeM.h"
#include "Async_Test.h"
#include "HardwareIO.h"
#include "Hmi.h"
#include "App_Cfg.h"
#include "BridgeInsu.h"
#include "LimitProtect.h"
#include "ExternCanCommGB.h"
#ifdef UPC6000
#include "SystemConnection_Lcfg.h"
#endif
#if defined(A650) || defined(A651) || defined(A652) || defined(A653) || defined(A660) || defined(A661) || defined(A655)|| defined(A657)|| defined(A665)
#include "Rs485Shell.h"
#endif

#define LOG_LEVEL LOG_LEVEL_OFF
#include "logger.h"


static boolean DcmOnCanTp_RxPduIdIsValid(PduIdType RxPduId) {
    boolean ret;
    if (RxPduId == 0U || RxPduId == 1U) {
        ret = TRUE;
    } else {
        ret = FALSE;
    }
    return ret;
}

static const Dcm_ConfigType DcmConfigCanTp = {
    DCM_UDS_ON_CAN, /* Dcm_ProtocolType protocolType; */
    DcmOnCanTp_RxPduIdIsValid, /* boolean (*RxPduIdIsValid)(PduIdType RxPduId); */
    5000U, /* Dcm_DspNonDefaultSessionS3ServerType DcmDspNonDefaultSessionS3Server; */
};

static boolean DcmOnDtuTp_RxPduIdIsValid(PduIdType RxPduId) {
    boolean ret;
    if (RxPduId == 2U) {
        ret = TRUE;
    } else {
        ret = FALSE;
    }
    return ret;
}

static const Dcm_ConfigType DcmConfigDtuTp = {
    DCM_UDS_ON_CAN, /* Dcm_ProtocolType protocolType; */
    DcmOnDtuTp_RxPduIdIsValid, /* boolean (*RxPduIdIsValid)(PduIdType RxPduId); */
    120000U, /* Dcm_DspNonDefaultSessionS3ServerType DcmDspNonDefaultSessionS3Server; */
};

static OS_STK currentm_task_stack[800];
static OS_STK heat_current_task_stack[300];
static OS_STK start_task_stack[500];
static OS_STK hvadc_task_stack[300];
// static OS_STK shunt_task_stack[400];


static void start_dtu_task(void) {

    static OS_STK dtu_task_stack[400];

    (void)OSTaskCreateExt(
        (void(*)(void *p_arg))DtuM35_MainLoop,
#if defined(A651) || defined(A653) || defined(A661)
        (void *)&DtuCommM35ConfigGB32960MC20,
#elif defined(A655)|| defined(A657)|| defined(A665)
        (void *)&DtuCommM35ConfigGB32960EC20,
#elif defined(A601) || defined(A603) || defined(C601) || defined(C603)
        (void *)&C600DtuCommM35ConfigGB32960MC20,
#else
        (void *)NULL,
#endif
        &dtu_task_stack[ARRAY_SIZE(dtu_task_stack) - 1U],
        DTU_TASK_PRI,
        DTU_TASK_PRI,
        &dtu_task_stack[0],
        (uint32)ARRAY_SIZE(dtu_task_stack),
        NULL,
        OS_TASK_OPT_NONE);
}
void start_dtu_task_testmode(void) ;

void start_dtu_task_testmode(void) {
    start_dtu_task();
}

static OS_STK driver_looper_stack[400];
static uint8 driverLooperCmdBuffer[100];
static Async_LooperType driverLooper;
static OS_STK ext_looper_stack[400];
static uint8 extLooperCmdBuffer[200];
static Async_LooperType extLooper;
static OS_STK shunt_looper_stack[400];
static uint8 shuntLooperCmdBuffer[64];
static Async_LooperType shuntLooper;

static void start_looper_tasks(void) {
    if (E_OK == Async_LooperInit(&driverLooper, driverLooperCmdBuffer, (RingBuffer_SizeType)sizeof(driverLooperCmdBuffer))) {
        (void)OSTaskCreateExt(
            (void(*)(void *p_arg))Async_LooperLoop,
            (void *)&driverLooper,
            &driver_looper_stack[ARRAY_SIZE(driver_looper_stack) - 1U],
            DRIVER_LOOPER_TASK_PRI,
            DRIVER_LOOPER_TASK_PRI,
            &driver_looper_stack[0],
            (uint32)ARRAY_SIZE(driver_looper_stack),
            NULL,
            OS_TASK_OPT_NONE);
    }

    if (E_OK == Async_LooperInit(&extLooper, extLooperCmdBuffer, (RingBuffer_SizeType)sizeof(extLooperCmdBuffer))) {
        (void)OSTaskCreateExt(
            (void(*)(void *p_arg))Async_LooperLoop,
            (void *)&extLooper,
            &ext_looper_stack[ARRAY_SIZE(ext_looper_stack) - 1U],
            EXT_LOOPER_TASK_PRI,
            EXT_LOOPER_TASK_PRI,
            &ext_looper_stack[0],
            (uint32)ARRAY_SIZE(ext_looper_stack),
            NULL,
            OS_TASK_OPT_NONE);
    }



    if (E_OK == Async_LooperInit(&shuntLooper, shuntLooperCmdBuffer, (RingBuffer_SizeType)sizeof(shuntLooperCmdBuffer))) {
        (void)OSTaskCreateExt(
            (void(*)(void *p_arg))Async_LooperLoop,
            (void *)&shuntLooper,
            &shunt_looper_stack[ARRAY_SIZE(shunt_looper_stack) - 1U],
            SHUNT_LOOPER_TASK_PRI,
            SHUNT_LOOPER_TASK_PRI,
            &shunt_looper_stack[0],
            (uint32)ARRAY_SIZE(shunt_looper_stack),
            NULL,
            OS_TASK_OPT_NONE);
    }
}


static void start_hvadc_task(void(*task_func)(void *param)) {
    (void)OSTaskCreateExt(
        (void(*)(void *param))task_func,
        (void *)0,
        &hvadc_task_stack[ARRAY_SIZE(hvadc_task_stack) - 1U],
        HVADC_TEST_TASK_PRI,
        HVADC_TEST_TASK_PRI,
        &hvadc_task_stack[0],
        (uint32)ARRAY_SIZE(hvadc_task_stack),
        NULL,
        OS_TASK_OPT_NONE);
}

#if 0
extern void shunt_test_task(void *pdata);
static void start_shunt_task(void) {
    (void)OSTaskCreateExt(
        (void(*)(void *p_arg))shunt_test_task,
        (void *)0,
        &shunt_task_stack[ARRAY_SIZE(shunt_task_stack) - 1],
        SHUNT_TEST_TASK_PRI,
        SHUNT_TEST_TASK_PRI,
        &shunt_task_stack[0],
        ARRAY_SIZE(shunt_task_stack),
        NULL,
        OS_TASK_OPT_NONE);
}
#endif


extern void nand_init(void);

extern const Hall_ConfigType HallConfigData[HALL_CHANNEL_NUM];

static boolean isNeedStartSampleTask(void) {
    boolean ret = FALSE;
    RuntimeM_RunModeType mode = RuntimeM_GetMode();

    if (mode == RUNTIMEM_RUNMODE_CALIBRATE) {
        ret = TRUE;
    } else if (mode == RUNTIMEM_RUNMODE_NORMAL) {
        ret = TRUE;
    } else if (mode == RUNTIMEM_RUNMODE_DTU) {
        ret = TRUE;
    } else {
    }
    return ret;
}


static void startHvSample(void) {
    uint16 gainErr;

    if (ParameterM_EeepRead(PARAMETERM_EEEP_HVBPOS_GAIN_ERROR_INDEX, &gainErr) != E_OK) {
        gainErr = 1000U;
    }
    (void)HV_StartSample(HV_CHANNEL_BPOS, 4U, 1U, gainErr);

    if (ParameterM_EeepRead(PARAMETERM_EEEP_HV1_GAIN_ERROR_INDEX, &gainErr) != E_OK) {
        gainErr = 1000U;
    }
    (void)HV_StartSample(HV_CHANNEL_HV1, 4U, 1U, gainErr);
    if (ParameterM_EeepRead(PARAMETERM_EEEP_HV2_GAIN_ERROR_INDEX, &gainErr) != E_OK) {
        gainErr = 1000U;
    }
    (void)HV_StartSample(HV_CHANNEL_HV2, 4U, 1U, gainErr);
    if (ParameterM_EeepRead(PARAMETERM_EEEP_HV3_GAIN_ERROR_INDEX, &gainErr) != E_OK) {
        gainErr = 1000U;
    }
    (void)HV_StartSample(HV_CHANNEL_HV3, 4U, 1U, gainErr);
    if (ParameterM_EeepRead(PARAMETERM_EEEP_HV4_GAIN_ERROR_INDEX, &gainErr) != E_OK) {
        gainErr = 1000U;
    }
    (void)HV_StartSample(HV_CHANNEL_HV4, 4U, 1U, gainErr);
    if (ParameterM_EeepRead(PARAMETERM_EEEP_HV5_GAIN_ERROR_INDEX, &gainErr) != E_OK) {
        gainErr = 1000U;
    }
    (void)HV_StartSample(HV_CHANNEL_HV5, 4U, 1U, gainErr);

}

extern const Adc_ConfigType AdcConfigTestMode;

static void run_test_mode(void) {
    Can_DeInit();
    Can_Init(&CanConfig_TestMode);
    (void)Can_SetControllerMode(0U, CAN_T_START);
    if (HardWareIO_GetVersion() != 5U /*0b101*/) {
        (void)Can_SetControllerMode(1U, CAN_T_START);
    }
    (void)Can_SetControllerMode(2U, CAN_T_START);
    (void)Can_SetControllerMode(3U, CAN_T_START);

    HardwareSn_Init();
    Adc_Init(&AdcConfigTestMode);
    HC12XIrq_InstallVector(IRQ_ATD1, ADT1_Isr, 0U);
    Adc_StartGroupConversion(ADC_GROUP_ADT1);
    OSTimeDly(2U);
    HC12XIrq_InstallVector(IRQ_ATD0, ADT0_Isr, 0U);
    Adc_StartGroupConversion(ADC_GROUP_ADT0);
    start_hvadc_task(hvadc_test_task_testmode);
    nand_init();
    CanEcho_Init(&extLooper);
    PwmCapture_Init();
    PwmCapture_Start();
    Shunt_Init(&shuntLooper, 1000U);
    (void)AllInOneComm_Init(LTC6804COMM_SAMPLE_TASK_PRI, TRUE);
    Dio_WriteChannel(DIO_CHANNEL_SYSTEM_POWER_LATCH, STD_HIGH);
#if defined(A650) || defined(A651) || defined(A652) || defined(A653) || defined(A660) || defined(A661) || defined(A655)|| defined(A657)|| defined(A665)
    (void)UartShell_Init((const UartShell_ConfigType *)UartShellConfigType, 0U);
#endif
    for (;;) {
        Shell_Loop();
    }
}

static void start_task(void *pdata) {
    RuntimeM_RunModeType mode;
    (void) pdata;

#if OS_TASK_STAT_EN > 0
    OSStatInit();
#endif

    Can_Init(&CanConfig);
    CanIf_Init();
    PduR_Init(&PduR_ConfigInfo);
    CanTp_Init(&CanTp_Cfg);
    J1939Tp_Init(&J1939Tp_Config);
    (void)Can_SetControllerMode(0U, CAN_T_START);
#ifdef UPC6000
    if (HardWareIO_GetVersion() != 5U /*0b101*/) {
#endif
        (void)Can_SetControllerMode(1U, CAN_T_START);
#ifdef UPC6000
    }
#endif
    (void)Can_SetControllerMode(2U, CAN_T_START);
    (void)Can_SetControllerMode(3U, CAN_T_START);

    HC12XIrq_InstallVector(IRQ_IIC1, IIC1_Isr, 0U);
    HC12XIrq_InstallVector(IRQ_SCI1, SCI1_Isr, 0U);
    HC12XIrq_InstallVector(IRQ_SCI2, SCI2_Isr, 0U);

    start_looper_tasks();

    RuntimeM_Init(&extLooper);
    TERMIO_Init();

    if (RuntimeM_GetMode() == RUNTIMEM_RUNMODE_TEST) {
        run_test_mode();
    }

    WatchdogM_Init();

    DigitalInput_Init();

    HLSS_Init(&driverLooper);
    if (isNeedStartSampleTask()) {
        HLSS_Drive(HLSS_BCU_BMU_ENABLE, HLSS_DRIVE_ON);
    } else {
        HLSS_Drive(HLSS_BCU_BMU_ENABLE, HLSS_DRIVE_OFF);
    }
    DischargeM_Init(&extLooper);
    ChargeM_Init(&extLooper);
    RelayM_Init(&extLooper);

    Drv8872_Init(&extLooper);
    Hall_Init(&HallConfigData[0]);
    SaveM_Init(SAVE_M_TASK_PRI);

    ParameterM_Init();
    if (isNeedStartSampleTask()) {
        uint16 gainErr;
        PwmCapture_Init();
        PwmCapture_Start();
#ifdef UPC6000
        if (HardWareIO_GetVersion() != 5U /*0b101*/) {
#endif
            if (ParameterM_EeepRead(PARAMETERM_EEEP_SHUNT_GAIN_ERROR_INDEX, &gainErr) != E_OK) {
                gainErr = 1000U;
            }
            Shunt_Init(&shuntLooper, gainErr);
#ifdef UPC6000
        }
#endif
        CurrentM_Init(&CurrentM_ConfigInfo, CURRENTM_TASK_PRI, currentm_task_stack, ARRAY_SIZE(currentm_task_stack));
        CurrentM_HeatInit(&CurrentM_ConfigInfo, HEAT_CURRENT_TASK_PRI, heat_current_task_stack, ARRAY_SIZE(heat_current_task_stack));
        PowerM_Init(&extLooper);
    }
    if (HardWareIO_GetVersion() != 5U /*0b101*/) {
        Adc_Init(&AdcConfig);
    } else {
        Adc_Init(&AdcConfig_0b101);
    }
    HC12XIrq_InstallVector(IRQ_ATD1, ADT1_Isr,  0U);
    Adc_StartGroupConversion(ADC_GROUP_ADT1);
    OSTimeDly(2U);
    HC12XIrq_InstallVector(IRQ_ATD0, ADT0_Isr, 0U);
    Adc_StartGroupConversion(ADC_GROUP_ADT0);
    mode = RuntimeM_GetMode();
    Dcm_Init(mode == RUNTIMEM_RUNMODE_DTU ? &DcmConfigDtuTp : &DcmConfigCanTp);
    Det_Start();
    if (mode == RUNTIMEM_RUNMODE_NORMAL ||
            mode == RUNTIMEM_RUNMODE_CALIBRATE ||
            mode == RUNTIMEM_RUNMODE_DTU) {
        Statistic_Init(&extLooper);
    } else {
        Statistic_Init(NULL);
    }
    CellDataM_Init();
    if (isNeedStartSampleTask()) {
        InternalComm_Init(INTERNALCOMM_TX_TASK_PRI);
        (void)AllInOneComm_Init(LTC6804COMM_SAMPLE_TASK_PRI, FALSE);
    }

    async_test(&extLooper);
    DatetimeM_Init(&extLooper);
    if (HardWareIO_GetVersion() != 5U /*0b101*/) {
        EL_Init(&extLooper);
    }
    Soc_Init(&extLooper);
    Soh_Init();
#if defined(A650) || defined(A651) || defined(A655)
    BridgeInsu_Init(&driverLooper, &BridgeInsuConfigData_A650);
#elif defined(A652) || defined(A653) || defined(A660) || defined(A661) || defined(A657) || defined(A665)
    BridgeInsu_Init(&driverLooper, &BridgeInsuConfigData_A652);
#else
    BridgeInsu_Init(&driverLooper, &BridgeInsuConfigData);
#endif

#ifdef UPC6000
    if (isNeedStartSampleTask()) {
#if SYSTEM_BATTERY_CELL_NUM <= 48U
        BridgeInsu_Start(BRIDGEINSU_MOS_ALWAYS_ON);
#else
        BridgeInsu_Start(BRIDGEINSU_MOS_BY_VOL);
#endif
    }
#endif

    if (isNeedStartSampleTask()) {
        startHvSample();
        start_hvadc_task(hvadc_test_task);
    }

    BalanceM_Init(&BalanceM_ConfigInfo);
    if (isNeedStartSampleTask()) {
        BalanceM_RegisterLooper(&extLooper);
    }
    CanEcho_Init(&extLooper);
    Diagnosis_Init(&ParameterM_CurrentCalibParaPtr->diagnosisPara, DIAGNOSIS_TASK_PRI);

    ChgSckTmpM_Init();
    if (mode == RUNTIMEM_RUNMODE_CALIBRATE ||
            mode == RUNTIMEM_RUNMODE_NORMAL) {
        SocCalib_Init(&extLooper);
        HvProcess_Init(HVPROCESS_TASK_PRI);
        ChargerComm_Init(CHARGERCOMM_TASK_PRI);
        ChargerCommGB_Init();
        ChargerCommUser_Init();
        if (ExternCanComm_ConfigInfo.Protocol != EXTERNCANCOMM_PROTOCOL_NONE) {
            ExternCanComm_Init(EXTERNCANCOMM_TASK_PRI);
            ExternCanCommGB_Init();
        }
        VcuComm_Init(VCUCOMM_TASK_PRI);
        ChargeConnectM_Init(&extLooper);
        FullCharge_Init(&extLooper);
        PrechargeM_Init(&extLooper);
        (void)Hmi_Init(&extLooper, 9600UL);
    }
    UserStrategy_Init(&extLooper);
    LimitProtect_Init(&extLooper);

    HardwareSn_Init();

#if defined(A601) || defined(A603) || defined(A651) || defined(A653) || defined(A661) || defined(A655)|| defined(A657)|| defined(A665) || defined(C601) || defined(C603)
    if (isNeedStartSampleTask()) {
        GBRtMsg_Init(&driverLooper);
        GB32960_Init(&driverLooper, RuntimeM_GetMode() == RUNTIMEM_RUNMODE_DTU ? 1U : 0U);
        start_dtu_task();
    }
#endif

    WatchdogM_Enable();

    if (mode == RUNTIMEM_RUNMODE_DATA) {
        for (;;) {
            CanTp_MainFunction();
            Dcm_MainFunction();
            WatchdogM_Run();
            OSTimeDly(1U);
        }
    } else {
        for (;;) {
            Det_MainFunction();
            CanTp_MainFunction();
            Dcm_MainFunction();
            J1939Tp_MainFunction();
            WatchdogM_Run();
            OSTimeDly(OS_TICKS_PER_SEC / 500U);
        }
    }
}

void main(void) {
    Irq_Init();
    Mcu_Init(&MCU_DEFAULT_CONFIG);
    (void)Mcu_InitClock(MCU_DEFAULT_CONFIG.McuDefaultClockSettings);
    Port_Init(&PortConfigData);
    Dio_WriteChannel(DIO_CHANNEL_SUSPEND, STD_HIGH);
    Dio_WriteChannel(DIO_CHANNEL_SYSTEM_POWER_LATCH, STD_LOW);
    Dio_WriteChannel(DIO_CHANNEL_8V_HALL_EN, STD_LOW);
    Dio_WriteChannel(DIO_CHANNEL_CAN2_EN, STD_HIGH);

    OSInit();

    (void)OSTaskCreateExt(
        start_task,
        (void *)0x123456U,
        &start_task_stack[ARRAY_SIZE(start_task_stack) - 1U],
        START_TASK_PRI,
        START_TASK_PRI,
        &start_task_stack[0],
        (uint32)ARRAY_SIZE(start_task_stack),
        NULL,
        OS_TASK_OPT_NONE);

    OSStart();
}

void App_TaskIdleHook(void);
void App_TaskIdleHook(void) {
    Can_MainFunction_Error();
}
#endif
