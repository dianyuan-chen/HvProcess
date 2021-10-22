#include "Dcm_Cfg.h"
#include "Dcm.h"

const uint8/*DCM_CONFIG_CONST*/  gSidMap_1[DCM_MAX_NUMBER_OF_SID_MAP] = {
#if(ISO_15031_5 == STD_ON)
    /* 0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07 */
    0xFFU, 0x00U, 0x01U, 0x02U, 0x03U, 0xFFU, 0x04U, 0x05U,
    /* 0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
    0x06U, 0x07U, 0x08U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
#else
    /* 0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07 */
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
    /* 0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFu,
#endif
    /* 0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17 */
    0x0U, 0x1U, 0xFFU, 0xFFU, 0x2U, 0xFFU, 0xFFU, 0xFFU,
    /* 0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F */
    0xFFU, 0x3U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
    /* 0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27 */
    0xFFU, 0xFFU, 0x4U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x5U,
    /* 0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F */
    0x6U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x7U, 0x8U,
    /* 0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37 */
    0xFFU, 0x9U, 0xFFU, 0xFFU, 0x0aU, 0xbU, 0xcU, 0xdU,
    /* 0x38  0x39  0x3A  0x3B  0x3C  0x3D  0x3E  0x3F */
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xeU, 0xFFU,
    /* 0x80  0x81  0x82  0x83  0x84  0x85  0x86  0x87 */
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xfU, 0xFFU, 0xFFU
};


const CurrentSidMapType *const gCurrentSidMap = gSidMap_1;

/* 0x10*/
const DcmDsdSubService/*DCM_CONFIG_CONST*/  gDcmDsdSubService_0x10[] = {
    {
        App_Default, /* App Callback Funtion */
        App_DefaultPost, /* App Post Callback Funtion */
        DCM_DEFAULT_SESSION, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_Programming, /* App Callback Funtion */
        App_ProgrammingPost, /* App Post Callback Funtion */
        DCM_PROGRAMMING_SESSION, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_Extended_Diagnostic, /* App Callback Funtion */
        App_Extended_DiagnosticPost, /* App Post Callback Funtion */
        DCM_EXTENDED_DIAGNOSTIC_SESSION, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        1U, /* Table End Flag */
    },
};

/* 0x11*/
const DcmDsdSubService/*DCM_CONFIG_CONST*/  gDcmDsdSubService_0x11[] = {
    {
        App_Hard_Reset_Reset, /* App Callback Funtion */
        App_Hard_Reset_ResetPost, /* App Post Callback Funtion */
        DCM_HARD_RESET, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_Soft_Reset_Reset, /* App Callback Funtion */
        App_Soft_Reset_ResetPost, /* App Post Callback Funtion */
        DCM_SOFT_RESET, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_Soft_Reset_ResetToData, /* App Callback Funtion */
        App_Soft_Reset_ResetToDataPost, /* App Post Callback Funtion */
        0x61U, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        1U, /* Table End Flag */
    },
};

/* 0x19*/
const DcmDsdSubService/*DCM_CONFIG_CONST*/  gDcmDsdSubService_0x19[] = {

    {
        App_Fault_Memory_Read_Number, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        DCM_REPORTNUMBEROFDTCBYSTATUSMASK, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_Fault_Memory_Read_identified_errors, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        DCM_REPORTDTCBYSTATUSMASK, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_Fault_Memory_Read_Snapshot, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        DCM_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_Fault_Memory_Read_supported_errors, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        DCM_REPORTSUPPORTEDDTC, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        1U, /* Table End Flag */
    },
};

/* 0x27*/
const DcmDsdSubService/*DCM_CONFIG_CONST*/  gDcmDsdSubService_0x27[] = {
    {
        App_Request_Seed_L1, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        REQUEST_SEED_L1, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_Send_Key_L1, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        SEND_KEY_L1, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
        1U, /* Table End Flag */
    },
};

/* 0x28*/
const DcmDsdSubService/*DCM_CONFIG_CONST*/  gDcmDsdSubService_0x28[] = {
    {
        App_EnableRxAndEnableTx_Control, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        ENABLE_RX_AND_TX, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },

    {
        App_DisableRxAndDisableTx_Control, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        DISABLE_RX_AND_TX, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        1U, /* Table End Flag */
    },
};

/* 0x31*/
const DcmDsdSubService/*DCM_CONFIG_CONST*/  gDcmDsdSubService_0x31[NUM_OF_31_SUB_FUNCTION] = {
    {
        DCM_NULL, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        START_ROUTINE, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_ALL), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        DCM_NULL, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        STOP_ROUTINE, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_ALL), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        DCM_NULL, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        REQUEST_ROUTINE_RESULT, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_ALL), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        1U, /* Table End Flag */
    },
};

/* 0x3E*/
const DcmDsdSubService/*DCM_CONFIG_CONST*/  gDcmDsdSubService_0x3E[] = {
    {
        DCM_NULL, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        ZERO_SUB_FUNCTION, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        1U, /* Table End Flag */
    },
};

/* 0x85*/
const DcmDsdSubService/*DCM_CONFIG_CONST*/  gDcmDsdSubService_0x85[] = {
    {
        App_ON_Send, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        DTC_RECORD_ON, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        0U, /* Table End Flag */
    },
    {
        App_OFF_Send, /* App Callback Funtion */
        DCM_NULL, /* App Post Callback Funtion */
        DTC_RECORD_OFF, /* Subfunction ID */
        SUB_FUNCTION_SUPPORTED, /* Subfunction Flag */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        1U, /* Table End Flag */
    },
};


const DcmDsdServiceTable/*DCM_CONFIG_CONST*/   gServiceTable_1[DCM_NUM_OF_SERVICE] = {
    /*10*/
#if(DCM_SERVICE_10_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_DiagnosticSessionControl, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        &gDcmDsdSubService_0x10[0], /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*11*/
#if(DCM_SERVICE_11_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_EcuReset, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        &gDcmDsdSubService_0x11[0], /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*14*/
#if(DCM_SERVICE_14_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_ClearDiagnosticInformation, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC) /* Supported Session */
        },
        NULL, /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*19*/
#if(DCM_SERVICE_19_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_ReadDTCInformation, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC) /* Supported Session */
        },
        &gDcmDsdSubService_0x19[0], /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*22*/
#if(DCM_SERVICE_22_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_ReadDataByIdentifier, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        NULL, /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*27*/
#if(DCM_SERVICE_27_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_SecurityAccess, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        &gDcmDsdSubService_0x27[0], /* Subfunction Table */
        PHYSICAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*28*/
#if(DCM_SERVICE_28_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_CommunicationControl, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC) /* Supported Session */
        },
        &gDcmDsdSubService_0x28[0], /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*2E*/
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_WriteDataByIdentifier, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC) /* Supported Session */
        },
        NULL, /* Subfunction Table */
        PHYSICAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*2F*/
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_InputOutputControlByIdentifier, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC) /* Supported Session */
        },
        NULL, /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*31*/
#if(DCM_SERVICE_31_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_RoutineControl, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        &gDcmDsdSubService_0x31[0], /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*34*/
#if(DCM_SERVICE_34_ENABLED == STD_ON)
    {
        /* Reserved */
        UDS_SERVICE_WITHOUT_SUB_FUNCTION,
        {
            App_RequestDownload, /* Internal Callback Funtion */
            (DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        NULL, /* Subfunction Table */
        PHYSICAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*35*/
#if(DCM_SERVICE_35_ENABLED == STD_ON)
    {
        /* Reserved */
        UDS_SERVICE_WITHOUT_SUB_FUNCTION,
        {
            App_RequestUpload, /* Internal Callback Funtion */
            (DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC) /* Supported Session */
        },
        NULL, /* Subfunction Table */
        PHYSICAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*36*/
#if(DCM_SERVICE_36_ENABLED == STD_ON)
    {
        /* Reserved */
        UDS_SERVICE_WITHOUT_SUB_FUNCTION,
        {
            App_DataTransfer, /* Internal Callback Funtion */
            (DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        NULL, /* Subfunction Table */
        PHYSICAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*37*/
#if(DCM_SERVICE_37_ENABLED == STD_ON)
    {
        /* Reserved */
        UDS_SERVICE_WITHOUT_SUB_FUNCTION,
        {
            App_TransferExit, /* Internal Callback Funtion */
            (DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        NULL, /* Subfunction Table */
        PHYSICAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*3E*/
#if(DCM_SERVICE_3E_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_TesterPresent, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        &gDcmDsdSubService_0x3E[0], /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    },
#endif
    /*85*/
#if(DCM_SERVICE_85_ENABLED == STD_ON)
    {
        /* Reserved */
        DCM_DSDSIDTABID,
        {
            DspInternal_Uds_ControlDTCSetting, /* Internal Callback Funtion */
            (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING) /* Supported Session */
        },
        &gDcmDsdSubService_0x85[0], /* Subfunction Table */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED /* Supported Address Type */
    }
#endif
};
