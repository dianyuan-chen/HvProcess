#ifndef _DCM_CFG_H_
#define _DCM_CFG_H_

#include "Dcm_Types.h"
#include "PduR.h"

#define  UseBlockId                                                 (0x01U)
#define  UseDataClientServer                                        (0x02U)
#define  UseDataSenderReceiver                                      (0x03U)
#define  UseEcuSignal                                               (0x04U)
#define  UseFnc                                                     (0x05U)
#define  DCM_NULL                                                   ((void*)0U)
#define  SUB_FUNCTION_NOT_SUPPORTED                                 (0x00U)
#define  SUB_FUNCTION_SUPPORTED                                     (0x01U)
#define  PHYSICAL_REQ_SUPPORTED                                     (0x01U)
#define  FUNCTIONAL_REQ_SUPPORTED                                   (0x02U)
#define  PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED                      (0x03U)
/* For 0x19 */
#define DCM_REPORTNUMBEROFDTCBYSTATUSMASK                           (0x01U)
#define DCM_REPORTDTCBYSTATUSMASK                                   (0x02U)
#define DCM_REPORTDTCSNAPSHOTIDENTIFICATION                         (0x03U)
#define DCM_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER                      (0x04U)
#define DCM_REPORTDTCSNAPSHOTRECORDBYRECORDNUMBER                   (0x05U)
#define DCM_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER                  (0x06U)
#define DCM_REPORTNUMBEROFDTCBYSEVERITYMASKRECORD                   (0x07U)
#define DCM_REPORTDTCBYSEVERITYMASKRECORD                           (0x08U)
#define DCM_REPORTSEVERITYINFORMATIONOFDTC                          (0x09U)
#define DCM_REPORTSUPPORTEDDTC                                      (0x0AU)
#define DCM_REPORTFIRSTTESTFAILEDDTC                                (0x0BU)
#define DCM_REPORTFIRSTCONFIRMEDDTC                                 (0x0CU)
#define DCM_REPORTMOSTRECENTTESTFAILEDDTC                           (0x0DU)
#define DCM_REPORTMOSTRECENTCONFIRMEDDTC                            (0x0EU)
#define DCM_REPORTMIRRORMEMORYDTCBYSTATUSMASK                       (0x0FU)
#define DCM_REPORTMIRRORMEMORYDTCEXTENDEDDATARECORDBYDTCNUMBER      (0x10U)
#define DCM_REPORTNUMBEROFMIRRORMEMORYDTCBYSTATUSMASK               (0x11U)
#define DCM_REPORTNUMBEROFEMISSIONSRELATEDOBDDTCBYSTATUSMASK        (0x12U)
#define DCM_REPORTEMISSIONSRELATEDOBDDTCBYSTATUSMASK                (0x13U)

/* For 0x27 */
#define REQUEST_SEED_L1                                             (0x01U)
#define SEND_KEY_L1                                                 (0x02U)
#define REQUEST_SEED_L2                                             (0x03U)
#define SEND_KEY_L2                                                 (0x04U)
#define REQUEST_SEED_L3                                             (0x05U)
#define SEND_KEY_L3                                                 (0x06U)
#define REQUEST_SEED_L4                                             (0x07U)
#define SEND_KEY_L4                                                 (0x08U)
#define REQUEST_SEED_L5                                             (0x09U)
#define SEND_KEY_L5                                                 (0x0AU)
#define REQUEST_SEED_L6                                             (0x0BU)
#define SEND_KEY_L6                                                 (0x0CU)
#define REQUEST_SEED_L7                                             (0x0DU)
#define SEND_KEY_L7                                                 (0x0EU)
#define REQUEST_SEED_L8                                             (0x0FU)
#define SEND_KEY_L8                                                 (0x10U)
/* For 0x28 */
#define ENABLE_RX_AND_TX                                            (0x00U)
#define ENBALE_RX_AND_DISABLE_TX                                    (0x01U)
#define DISABLE_RX_AND_ENBALE_TX                                    (0x02U)
#define DISABLE_RX_AND_TX                                           (0x03U)
#define NORMAL_MSG                                                  (0x01U)
#define NM_MSG                                                      (0x02U)
#define BOTH_NORMAL_AND_NM_MSG                                      (0x03U)
/* For 0x2C */
#define DEFINEBYIDENTIFIER                                          (0x01U)
#define DEFINEBYMEMORYADDRESS                                       (0x02U)
#define CLEARDYNAMICALLYDEFINEDDATAIDENTIFIER                       (0x03U)
/* For 0x2F */
#define RETURN_CONTROL_TO_ECU                                       (0x00U)
#define RESET_TO_DEFAULT                                            (0x01U)
#define FREEZE_CURRENT_STATE                                        (0x02U)
#define SHORT_TERM_ADJUSTMENT                                       (0x03U)
/* For 0x31 */
#define START_ROUTINE                                               (0x01U)
#define STOP_ROUTINE                                                (0x02U)
#define REQUEST_ROUTINE_RESULT                                      (0x03U)
/* For 0x3E */
#define ZERO_SUB_FUNCTION                                           (0x00U)
/* For 0x85 */
#define DTC_RECORD_ON                                               (0x01U)
#define DTC_RECORD_OFF                                              (0x02U)
#define DcmTransmit(DcmTxPduId,PduInfoPtr)                          PduR_DcmTransmit(DcmTxPduId,PduInfoPtr)
#define Dcm_DefaultSessionPost(result)                              App_DefaultPost(result)

#define DCM_DSP_DATA_USE_PORT                                       UseFnc
#define DCM_DEV_ERROR_DETECT                                        STD_OFF
#define DCM_OEM_INDICATION                                          STD_OFF
#define DCM_SUPPLIER_INDICATION                                     STD_OFF
#define DCM_RESPONSE_ALL_REQ                                        STD_OFF
#define DCM_VERSION_INFO_API                                        STD_OFF
/* For 15031-5 */
#define ISO_15031_5                                                 STD_OFF
#define ISO_15031_5_MultiChannel                                    STD_OFF
/* Related to Dcm calling cycle */
#define DCM_TASK_TIME                                               (2UL)
/* Related to 0x78 negative response */
#define DCM_DSL_DIAG_RESP_FORCE_RESP_PEND_EN                        STD_ON
#define DCM_NUM_MAX_RESPPEND                                        (0xFFFFFFFFUL)
/* Related to customized service */
#define DCM_COSTOMIZED_SERVCIE_SUPPORTED                            STD_OFF
/* Related to Obd service */
/* Related to Uds service */
#define DCM_NUM_OF_SERVICE                                          (16U)
#define DCM_NUM_OF_SUB_SERVICE                                      (NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION +\
                                                                     NUM_OF_19_SUB_FUNCTION + NUM_OF_27_SUB_FUNCTION +\
                                                                     NUM_OF_28_SUB_FUNCTION + NUM_OF_2C_SUB_FUNCTION +\
                                                                     NUM_OF_31_SUB_FUNCTION + NUM_OF_3E_SUB_FUNCTION +\
                                                                     NUM_OF_85_SUB_FUNCTION + NUM_OF_86_SUB_FUNCTION + 1U)
#define UDS_SERVICE_WITHOUT_SUB_FUNCTION                            (0U)
#define UDS_SERVICE_WITH_SUB_FUNCTION                               (1U)
#define DCM_DSDSIDTABID                                             (1U)
#define DCM_SUBSERVICESTART                                         (0U)

#define DCM_SERVICE_10_ENABLED                                      STD_ON
#define NUM_OF_10_SUB_FUNCTION                                      (3U)
#define KIND_OF_SESSION                                             (3U)
#define DEFAULT_AND_EXTENDED_SEESION_HANDLE                         (DCM_SESSION_DEFAULT  | DCM_SESSION_EXTENDED_DIAGNOSTIC)
#define EXTENDED_SEESION_HANDLE                                     DCM_SESSION_EXTENDED_DIAGNOSTIC
#define RESPONSE_WITH_P2TIMER                                       STD_ON

#define DCM_SERVICE_11_ENABLED                                      STD_ON
#define NUM_OF_11_SUB_FUNCTION                                      (2U)

#define DCM_SERVICE_14_ENABLED                                      STD_ON

#define DCM_SERVICE_19_ENABLED                                      STD_ON
#define NUM_OF_19_SUB_FUNCTION                                      (4U)
#define reportNumberOfDTCByStatusMask                               STD_ON
#define reportDTCByStatusMask                                       STD_ON
#define reportDTCSnapshotIdentification                             STD_OFF
#define reportDTCSnapshotRecordByDTCNumber                          STD_ON
#define reportDTCSnapshotRecordByRecordNumber                       STD_OFF
#define reportDTCExtendedDataRecordByDTCNumber                      STD_OFF
#define reportNumberOfDTCBySeverityMaskRecord                       STD_OFF
#define reportDTCBySeverityMaskRecord                               STD_OFF
#define reportSeverityInformationOfDTC                              STD_OFF
#define reportSupportedDTC                                          STD_ON
#define reportFirstTestFailedDTC                                    STD_OFF
#define reportFirstConfirmedDTC                                     STD_OFF
#define reportMostRecentTestFailedDTC                               STD_OFF
#define reportMostRecentConfirmedDTC                                STD_OFF
#define reportMirrorMemoryDTCByStatusMask                           STD_OFF
#define reportMirrorMemoryDTCExtendedDataRecordByDTCNumber          STD_OFF
#define reportNumberOfMirrorMemoryDTCByStatusMask                   STD_OFF
#define reportNumberOfEmissionsRelatedOBDDTCByStatusMask            STD_OFF
#define reportEmissionsRelatedOBDDTCByStatusMask                    STD_OFF

#define DCM_SERVICE_22_ENABLED                                      STD_ON
#define DCM_SERVICE_22_COMBINED_DID                                 STD_OFF
#define MAX_NUM_OF_DID_TO_READ                                      (1U)
#define NUMBER_OF_READ_DID                                          Dcm_NumberOfReadDID

#define DCM_SERVICE_23_ENABLED                                      STD_OFF

#define DCM_SERVICE_24_ENABLED                                      STD_OFF

#define DCM_SERVICE_27_ENABLED                                      STD_ON
#define NUM_OF_27_SUB_FUNCTION                                      (2U)
#define KIND_OF_SECURITY_LEVEL                                      (7U)
#define DISABLE_SECURITY_ACCESS_ATTEMPT_NUMBER_RESET                STD_OFF
#define SECURITY_SAVE_ATTEMPT_NUMBER_API                            STD_OFF

#define DCM_SERVICE_28_ENABLED                                      STD_ON
#define NUM_OF_28_SUB_FUNCTION                                      (3U)

#define DCM_SERVICE_2A_ENABLED                                      STD_OFF

#define DCM_SERVICE_2C_ENABLED                                      STD_OFF
#define NUM_OF_2C_SUB_FUNCTION                                      (0U)

#define DCM_SERVICE_2E_ENABLED                                      STD_ON
#define NUMBER_OF_WRITE_DID                                         Dcm_NumberOfWriteDID

#define DCM_SERVICE_2F_ENABLED                                      STD_ON
#define NUMBER_OF_CONTROL_DID                                       (3U)

#define DCM_SERVICE_31_ENABLED                                      STD_ON
#define NUM_OF_31_SUB_FUNCTION                                      (3U)
#define NUMBER_OF_RID                                               Dcm_NumberOfRoutineDID/*(9U)*/

#define DCM_SERVICE_34_ENABLED                                      STD_ON
#define DCM_SERVICE_35_ENABLED                                      STD_ON
#define DCM_SERVICE_36_ENABLED                                      STD_ON
#define DCM_SERVICE_37_ENABLED                                      STD_ON

#define DCM_SERVICE_3D_ENABLED                                      STD_OFF

#define DCM_SERVICE_3E_ENABLED                                      STD_ON
#define NUM_OF_3E_SUB_FUNCTION                                      (1U)

#define DCM_SERVICE_85_ENABLED                                      STD_ON
#define NUM_OF_85_SUB_FUNCTION                                      (2U)

#define DCM_SERVICE_86_ENABLED                                      STD_OFF
#define NUM_OF_86_SUB_FUNCTION                                      (0U)

/* Related to diagnostic buffer */
#define DCM_PAGEDBUFFER_ENABLED                                     STD_OFF
#define UDS_FUNC_BUFFER_SIZE                                        (8U)
#define UDS_PHYS_BUFFER_SIZE                                        (820U)
#define NEG_RESP_BUFFER_SIZE                                        (3U)
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#define PERODIC_RESP_BUFFER_SIZE                                    (8U)
#endif
/* Additional applicaiton callback */
#define DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL                          STD_ON

typedef uint32 DcmDslBufferSize;
typedef void (*EcucFunctionNameDef)(void);
/* removed by larry 2013.11.12 QAC no used for this typedef */
/*
typedef uint8 (*EcucSubFunctionNameDef)(Dcm_MsgContextType*);
*/
typedef void (*VoidEcucSubFunctionNameDef)(Dcm_MsgContextType *pMsgContext);
typedef void (*EcucPostSubFunctionNameDef)(Std_ReturnType Result);

/* For Uds sub-service table */
typedef struct {
    VoidEcucSubFunctionNameDef  DcmDsdSubFunction;/* self-defined */
    EcucPostSubFunctionNameDef  DcmDsdSubFunctionPost;/* self-defined */
    uint8 DcmDsdSubServiceId;
    uint8 DcmDsdSubServiceIdSupported;/* self-defined */
    uint8 DcmDsdSubServiceSecurityLevelRef;
    uint8 DcmDsdSubServiceSessionLevelRef;
    uint8 AddressingMode;/* self-defined */
    uint8 TableEndFlag;
} DcmDsdSubService;

/* For Uds service table */
typedef struct {
    EcucFunctionNameDef DcmDsdSidTabFnc;
    uint8 DcmDsdSidTabSecurityLevelRef;
    uint8 DcmDsdSidTabSessionLevelRef;
} DcmDsdService;

typedef struct {
    uint8 DcmDsdSidTabId;
    DcmDsdService           ServiceTable;
    const DcmDsdSubService *SubServiceTable;
    uint8 AddressingMode;
} DcmDsdServiceTable;


/* For security access */
typedef struct {
    /* uint32 DcmDspSecurityADRSize;*/
    uint32 DcmDspSecurityDelayTime;
    uint32 DcmDspSecurityDelayTimeOnBoot;
    uint32 DcmDspSecurityKeySize;
    uint8 DcmDspSecurityLevel;
    uint8 DcmDspSecurityNumAttDelay;
    uint32 DcmDspSecuritySeedSize;
} DcmDspSecurityRow;
typedef enum {
    KEY_IS_NOT_VALID = 0x00U,
    KEY_IS_VALID = 0x01U
} DcmDspSecurityAccessKey;
/* For session control */
typedef enum {
    DCM_NO_BOOT,
    DCM_OEM_BOOT,
    DCM_SYS_BOOT
} DcmDspSessionForBoot;
typedef struct {
    DcmDspSessionForBoot DcmDspSession;
    uint8 DcmDspSessionLevel;
    uint32               DcmDspSessionP2ServerMax;
    uint32               DcmDspSessionP2StarServerMax;
} DcmDspSessionRow;

/* For 0x22 */
typedef struct {
    uint32                 DcmDspDidIdentifier;
    boollean                DcmDspDidUsed;
    uint16                 DcmDspDataSize;
#if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef DcmDspDataReadFnc;
#endif
#if(DCM_DSP_DATA_USE_PORT == UseEcuSignal)
    VoidEcucSubFunctionNameDef DcmDspDataEcuSignal;
    VoidEcucSubFunctionNameDef DcmDspDataReadEcuSignal;
#endif
    uint8 DcmDspDidReadSecurityLevelRef;
    uint8 DcmDspDidReadSessionRef;
    uint8 AddressingMode;
} Dcm_22_ServiceInfoType;

/* For 0x23 */
typedef struct {
    uint32 DcmDspReadMemoryRangeHigh;
    uint32 DcmDspReadMemoryRangeLow;
    uint8 DcmDspReadMemoryRangeSecurityLevelRef;
    uint8 DcmDspReadMemoryRangeSessionRef;
    uint8 AddressingMode;
} DcmDspReadMemoryRangeInfo;

typedef uint8 Dcm_MemoryAddressFormatType;
typedef uint8 Dcm_MemorySizeFormatType;

/* For 0x24 */
typedef struct {
    uint32                 DcmDspDidIdentifier;
    boollean                DcmDspDidUsed;
    uint16                 DcmDspDataSize;
#if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef DcmDspDataGetScalingInfoFnc;
#endif
#if(DCM_DSP_DATA_USE_PORT == UseEcuSignal)
    VoidEcucSubFunctionNameDef DcmDspDataEcuSignal;
    VoidEcucSubFunctionNameDef DcmDspDataReadEcuSignal;
#endif
    uint8 DcmDspDidReadSecurityLevelRef;
    uint8 DcmDspDidReadSessionRef;
    uint8 AddressingMode;
} Dcm_24_ServiceInfoType;

/* For 0x2A */
typedef struct {
    uint8 DcmDspDidIdentifier;
    boollean                DcmDspDidUsed;
    uint16                 DcmDspDataSize;
#if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef DcmDspDataReadFnc;
#endif
    uint8 DcmDspDidReadSecurityLevelRef;
    uint8 DcmDspDidReadSessionRef;
    uint8 AddressingMode;
} Dcm_2A_ServiceInfoType;

/* For 0x2C */
typedef struct {
    uint32                 DcmDspDidIdentifier;
    uint16                 DcmDspDataSize;
    uint8 DcmDspDidReadSecurityLevelRef;/* security level must be the same as in 0x22 */
    uint8 DcmDspDidReadSessionRef;/* session type must be the same as in 0x22 */
    uint8 AddressingMode;
} Dcm_2C_ServiceInfoType;
/* For 0x2E */
typedef struct {
    uint32                 DcmDspDidIdentifier;
    boollean                DcmDspDidUsed;
    uint16                 DcmDspDataSize;
#if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef DcmDspDataWriteFnc;
#endif
#if(DCM_DSP_DATA_USE_PORT == UseEcuSignal)
    VoidEcucSubFunctionNameDef DcmDspDataEcuSignal;
#endif
    uint8 DcmDspDidWriteSecurityLevelRef;
    uint8 DcmDspDidWriteSessionRef;
    uint8 AddressingMode;
} Dcm_2E_ServiceInfoType;

/* For 0x2F */
typedef struct {
    uint32 DcmDspDidControlOptionRecordSize;   /* This define the size of controlOptionRecord without the InputOutputControlParameter */
    uint32 DcmDspDidControlEnableMaskRecordSize;/* This is only useful when use InputOutputControlParameter */
    uint32 DcmDspDidControlStatusRecordSize;
} DcmDspDidControlRecordSizes;
typedef struct {
    uint32                       DcmDspDidIdentifier;
    uint8 DcmDspDidControlSecurityLevelRef;
    uint8 DcmDspDidControlSessionRef;
    uint8 AddressingMode;
    DcmDspDidControlRecordSizes  RecordSizes;
#if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef   DcmDspDataReturnControlToEcuFnc;
    VoidEcucSubFunctionNameDef   DcmDspDataResetToDefaultFnc;
    VoidEcucSubFunctionNameDef   DcmDspDataFreezeCurrentStateFnc;
    VoidEcucSubFunctionNameDef   DcmDspDataShortTermAdjustmentFnc;
#endif
    VoidEcucSubFunctionNameDef       OtherFnc;/* self-defined */
} Dcm_2F_ServiceInfoType;

/* For 0x31 */
typedef struct {
    uint8 DcmDspRoutineSecurityLevelRef;
    uint8 DcmDspRoutineSessionRef;
    uint8 AddressingMode;
} DcmDspRoutineAuthorization;
typedef struct {
    uint32 DcmDspRoutineSignalLength;
    /* uint32 DcmDspRoutineSignalPos; */ /* Reserved */
} DcmDspRoutineSignal;
typedef struct {
    DcmDspRoutineAuthorization  RoutineAuthorization;
    DcmDspRoutineSignal         DcmDspRoutineRequestResOut;/*not used */
    DcmDspRoutineSignal         DcmDspRoutineStopIn;
    DcmDspRoutineSignal         DcmDspRoutineStopOut;  /*not used */
    DcmDspRoutineSignal         DcmDspStartRoutineIn;
    DcmDspRoutineSignal         DcmDspStartRoutineOut; /*not used */
} DcmDspRoutineInfo;
typedef struct {
    uint16                      DcmDspRoutineIdentifier;
    boollean                     DcmDspRoutineUsed;     /*not used */
    boollean                     DcmDspRoutineUsePort;/*not used */
    boollean                     DcmDspRoutineFixedLength;
    VoidEcucSubFunctionNameDef  DcmDspStartRoutineFnc;
    VoidEcucSubFunctionNameDef  DcmDspStopRoutineFnc;
    VoidEcucSubFunctionNameDef  DcmDspRequestResultsRoutineFnc;
    DcmDspRoutineInfo           DcmDspRoutineInfoRef;
} DcmDspRoutine;

/* For 0x3D */
typedef struct {
    uint32 DcmDspWriteMemoryRangeHigh;
    uint32 DcmDspWriteMemoryRangeLow;
    uint8 DcmDspWriteMemoryRangeSecurityLevelRef;
    uint8 DcmDspWriteMemoryRangeSessionRef;
    uint8 AddressingMode;
} DcmDspWriteMemoryRangeInfo;

/* removed by larry QAC reserved for future */
/* For 0x86 */
/*
typedef struct
{
 void(*DcmDspDidRoeActivateFnc)();
 uint32 DcmDspDidRoeEventId;
 boollean DcmDspRoeInitOnDSC;
 uint32  DcmDspRoeInterMessageTime;
 uint16  DcmDspRoeMaxEventLength;
 uint8 DcmDspRoeMaxNumberOfRetry;
 uint16  DcmDspRoeMaxQueueLength;
 boollean DcmDspRoeQueueEnabled;
}DcmDspRoe;
*/
/**************************************************************************************************
* Pre-compile parameter
**************************************************************************************************/
#define DCM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
extern const uint8 /*DCM_CONFIG_CONST*/gSidMap_1[DCM_MAX_NUMBER_OF_SID_MAP];
extern const CurrentSidMapType *const gCurrentSidMap;
extern const DcmDsdServiceTable /*DCM_CONFIG_CONST*/gServiceTable_1[DCM_NUM_OF_SERVICE];
/* For 0x10,0x11,0x19,0x27,0x28,0x2C,0x31,0x3E,0x85 0x86 */
extern const DcmDsdSubService /*DCM_CONFIG_CONST*/gDcmDsdSubService[DCM_NUM_OF_SUB_SERVICE];

/**************************************************************************************************
* Link-compile parameter
**************************************************************************************************/
/* changed by larry 2013.11.11 QAC defination and declaration are not same */
/*extern const Dcm_DspNonDefaultSessionS3ServerType DCM_CONFIG_CONST gDcmDspNonDefaultSessionS3Server; */
extern const DcmDspSessionRow /*DCM_CONFIG_CONST*/gDcmDspSessionRow[KIND_OF_SESSION];

#if(DCM_SERVICE_27_ENABLED == STD_ON)
extern const DcmDspSecurityRow /*DCM_CONFIG_CONST*/gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL];
#endif

#if(DCM_SERVICE_22_ENABLED == STD_ON)
extern const Dcm_22_ServiceInfoType /*DCM_CONFIG_CONST*/gDcmDsdSubService_22[];    /* For 0x22 */
extern uint8 Dcm_NumberOfReadDID;
#endif

#if((DCM_SERVICE_23_ENABLED == STD_ON)|| (DCM_SERVICE_2C_ENABLED == STD_ON)||(DCM_SERVICE_3D_ENABLED == STD_ON))
extern const Dcm_MemoryAddressFormatType /*DCM_CONFIG_CONST*/gMemoryAddressFormat;
extern const Dcm_MemorySizeFormatType /*DCM_CONFIG_CONST*/gMemorySizeFormat;
#endif

#if(DCM_SERVICE_23_ENABLED == STD_ON)
extern const DcmDspReadMemoryRangeInfo /*DCM_CONFIG_CONST*/gDcmDspReadMemoryRangeInfo_23[NUMBER_OF_READ_ADDRESS_SEG];
#endif

#if(DCM_SERVICE_24_ENABLED == STD_ON)
extern const Dcm_24_ServiceInfoType /*DCM_CONFIG_CONST*/gDcmDsdSubService_24[NUMBER_OF_READ_DID_24]; /* For 0x24 */
#endif

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
extern const Dcm_2A_ServiceInfoType /*DCM_CONFIG_CONST*/gDcmDsdSubService_2A[NUMBER_OF_PERIODIC_DID];/* For 0x2A */
#endif

#if(DCM_SERVICE_2C_ENABLED == STD_ON)
extern const Dcm_2C_ServiceInfoType /*DCM_CONFIG_CONST*/gDcmDsdSubService_2C[NUMBER_OF_DYN_DID];     /* For 0x2C */
#endif

#if(DCM_SERVICE_2E_ENABLED == STD_ON)
extern const Dcm_2E_ServiceInfoType /*DCM_CONFIG_CONST*/gDcmDsdSubService_2E[];   /* For 0x2E */
extern uint8 Dcm_NumberOfWriteDID;
#endif

#if(DCM_SERVICE_2F_ENABLED == STD_ON)
extern const Dcm_2F_ServiceInfoType /*DCM_CONFIG_CONST*/gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID]; /* For 0x2F */
#endif

#if(DCM_SERVICE_31_ENABLED == STD_ON)
extern const DcmDspRoutine /*DCM_CONFIG_CONST*/DcmDspRoutineIdentifierTable_31[];       /* For 0x31 */
extern const uint8 Dcm_NumberOfRoutineDID;

#endif

#if(DCM_SERVICE_3D_ENABLED == STD_ON)
extern const DcmDspWriteMemoryRangeInfo /*DCM_CONFIG_CONST*/gDcmDspWriteMemoryRangeInfo_3D[NUMBER_OF_WRITE_ADDRESS_SEG];
#endif

#define DCM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/**************************************************************************************************
* Application Callback Function Prototye
**************************************************************************************************/
#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
extern Std_ReturnType App_DiagnosticActive(void);
#endif

#if(DCM_COSTOMIZED_SERVCIE_SUPPORTED == STD_ON)
extern void App_CustomizedServcie(Dcm_MsgContextType *pMsgContext);
#endif

/* 10 */
extern void App_DefaultPost(Std_ReturnType Result);
extern void App_Default(Dcm_MsgContextType *pMsgContext);
extern void App_ProgrammingPost(Std_ReturnType Result);
extern void App_Programming(Dcm_MsgContextType *pMsgContext);
extern void App_Extended_DiagnosticPost(Std_ReturnType Result);
extern void App_Extended_Diagnostic(Dcm_MsgContextType *pMsgContext);
/* 11 */
extern void App_Hard_Reset_ResetPost(Std_ReturnType Result);
extern void App_Hard_Reset_Reset(Dcm_MsgContextType *pMsgContext);
extern void App_Soft_Reset_ResetPost(Std_ReturnType Result);
extern void App_Soft_Reset_Reset(Dcm_MsgContextType *pMsgContext);
extern void App_Soft_Reset_ResetToDataPost(Std_ReturnType Result);
extern void App_Soft_Reset_ResetToData(Dcm_MsgContextType *pMsgContext);
/* 14 */
extern void App_ClearDiagnosticInformation(Dcm_MsgContextType *pMsgContext);
/* 19 */
extern void App_Fault_Memory_Read_Number(Dcm_MsgContextType *pMsgContext);
extern void App_Fault_Memory_Read_identified_errors(Dcm_MsgContextType *pMsgContext);
extern void App_Fault_Memory_Read_Snapshot(Dcm_MsgContextType *pMsgContext);
extern void App_Fault_Memory_Read_supported_errors(Dcm_MsgContextType *pMsgContext);
/* 22 */
extern void App_Read0x0100(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0101(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0102(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0103(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0104(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0105(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0106(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0200(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0201(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0202(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0203(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0204(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0205(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0206(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0207(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0208(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0209(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x020A(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x020B(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0489(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0620(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0900(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0901(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0902(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0905(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0950(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0960(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0961(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0962(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E00(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E11(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E20(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E21(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E40(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E60(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E61(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E70(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0E71(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0EA0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0EA1(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0EB0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0ED0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0ED1(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0ED2(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0ED5(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0EF0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0F10(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0F11(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0F12(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0F30(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0F50(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x0F60(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x1300(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x1301(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x1305(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x1600(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x1620(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2800(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2801(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2802(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2803(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2804(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2810(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2820(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2828(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2830(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2838(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2850(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2851(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2852(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2853(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2854(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2855(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2856(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x2857(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3002(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3010(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3021(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3022(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3030(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3031(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3032(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3033(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3034(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3035(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3036(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3037(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3040(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3041(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3042(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3043(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3050(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3051(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3052(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3053(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3054(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3055(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3056(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3057(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3058(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3059(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x305A(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x305B(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3070(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3071(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3080(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3081(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3082(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3083(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3090(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3091(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3092(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3093(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30A0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30A1(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30A2(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30A3(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30B0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30B1(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30B2(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30B3(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30C0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30C1(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30C2(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30C3(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30D0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30D1(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30D2(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30D3(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30E0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30E1(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30E2(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30E3(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30E4(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30E5(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30E6(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30F0(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30F1(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30F2(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x30F3(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3140(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3141(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3142(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3143(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3150(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3151(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3152(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x3153(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x4000(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x4010(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x4011(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x4012(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x4018(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x4019(Dcm_MsgContextType *pMsgContext);
extern void App_Read0x401A(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xA500(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xA503(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xA50A(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xA50B(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xA50F(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xDFEF(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF101(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF110(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF112(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF113(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF180(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF181(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF182(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF184(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF185(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF186(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF187(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF189(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF18A(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF18B(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF18C(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF18E(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF190(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF192(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF193(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF194(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF195(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF197(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF198(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF199(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF19D(Dcm_MsgContextType *pMsgContext);
extern void App_Read0xF19E(Dcm_MsgContextType *pMsgContext);
/* 27 */
extern uint8/*DCM_VARIABLE*/   gSecurityAcessSequence[KIND_OF_SECURITY_LEVEL];
extern void App_Request_Seed_L1(Dcm_MsgContextType *pMsgContext);
extern void App_Send_Key_L1(Dcm_MsgContextType *pMsgContext);
/* 28 */
extern void App_EnableRxAndEnableTx_Control(Dcm_MsgContextType *pMsgContext);
extern void App_DisableRxAndEnableTx_Control(Dcm_MsgContextType *pMsgContext);
extern void App_DisableRxAndDisableTx_Control(Dcm_MsgContextType *pMsgContext);
/* 2E */
extern void App_Write0x0E11(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x0E61(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x2801(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3021(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3030(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3032(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3034(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3036(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3040(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3042(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3050(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3052(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3054(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3056(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3058(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x305A(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3070(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3080(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3082(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3090(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3092(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30A0(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30A2(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30B0(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30B2(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30C0(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30C2(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30D0(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30D2(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30E0(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30E1(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30E3(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30E5(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30F0(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x30F2(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3140(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3142(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3150(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x3152(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x4011(Dcm_MsgContextType *pMsgContext);
extern void App_Write0x4019(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xDFEF(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xF101(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xF110(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xF112(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xF190(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xF197(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xF198(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xF199(Dcm_MsgContextType *pMsgContext);
extern void App_Write0xF19D(Dcm_MsgContextType *pMsgContext);
/* 2F */
extern void App_ReturnControlToEcu0x0489(Dcm_MsgContextType *pMsgContext);
extern void App_ShortTermAdjustment0x0489(Dcm_MsgContextType *pMsgContext);
extern void App_ReturnControlToEcu0x0918(Dcm_MsgContextType *pMsgContext);
extern void App_ShortTermAdjustment0x0918(Dcm_MsgContextType *pMsgContext);
extern void App_ReturnControlToEcu0x0968(Dcm_MsgContextType *pMsgContext);
extern void App_ShortTermAdjustment0x0968(Dcm_MsgContextType *pMsgContext);
/* 31 */
extern uint8/*DCM_VARIABLE*/  gRountineControlSequence[];
extern uint8/*DCM_VARIABLE*/  gRountineControlDidHandle;

extern void App_StartRoutine0xDFF0(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF000(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF001(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF002(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF003(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF004(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF006(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF007(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF008(Dcm_MsgContextType *pMsgContext);
extern void App_StopRoutine0xF008(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF009(Dcm_MsgContextType *pMsgContext);
extern void App_StopRoutine0xF009(Dcm_MsgContextType *pMsgContext);
extern void App_StartRoutine0xF00A(Dcm_MsgContextType *pMsgContext);
extern void App_StopRoutine0xF00A(Dcm_MsgContextType *pMsgContext);

extern void APP_RequestResultsRoutine0xF006(Dcm_MsgContextType *pMsgContext);
extern void APP_RequestResultsRoutine0xF008(Dcm_MsgContextType *pMsgContext);
extern void APP_RequestResultsRoutine0xF009(Dcm_MsgContextType *pMsgContext);
extern void APP_RequestResultsRoutine0xF00A(Dcm_MsgContextType *pMsgContext);
/* 34 */
extern void App_RequestDownload(void);
/* 35 */
extern void App_RequestUpload(void);
/* 36 */
extern void App_DataTransfer(void);
/* 37 */
extern void App_TransferExit(void);
/* 85 */
extern uint8/*DCM_VARIABLE*/ gDTCSwitch;
extern void App_ON_Send(Dcm_MsgContextType *pMsgContext);
extern void App_OFF_Send(Dcm_MsgContextType *pMsgContext);

#endif
