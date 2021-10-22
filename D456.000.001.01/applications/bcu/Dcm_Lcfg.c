#include "Dcm_Types.h"
#include "Dcm_Cfg.h"
#include "App_PBCfg.h"
#include "Diagnosis_Cfg.h"

/* Config S3 time */
//CONST(Dcm_DspNonDefaultSessionS3ServerType, DCM_CONFIG_CONST) gDcmDspNonDefaultSessionS3Server = 5000UL;/*Unit:ms*/

/* Config Session */
const DcmDspSessionRow/*DCM_CONFIG_CONST*/ gDcmDspSessionRow[KIND_OF_SESSION] = {
    {
        DCM_NO_BOOT,
        /* Session */
        DCM_SESSION_DEFAULT,
        /* P2Server */ 50UL,
        /* P2*Server */ 2000UL,
    },
    {
        DCM_NO_BOOT,
        /* Session */ DCM_SESSION_PROGRAMMING,
        /* P2Server */ 50UL,
        /* P2*Server */ 2000UL,
    },
    {
        DCM_NO_BOOT,
        /* Session */ DCM_SESSION_EXTENDED_DIAGNOSTIC,
        /* P2Server */ 50UL,
        /* P2*Server */ 2000UL,
    }
};

#if(DCM_SERVICE_27_ENABLED == STD_ON)
const DcmDspSecurityRow/*DCM_CONFIG_CONST*/  gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL] = {
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        4UL,  /* Key Size */
        DCM_SEC_LEV_L1, /* Level */
        3U,  /* Attempt Number */
        4UL  /* Seed Size */
    },
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L2, /* Level */
        2U,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L3, /* Level */
        2U,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L4, /* Level */
        2U,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L5, /* Level */
        2U,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L6, /* Level */
        2U,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L7, /* Level */
        2U,  /* Attempt Number */
        2UL  /* Seed Size */
    }
};
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)
const Dcm_22_ServiceInfoType/*DCM_CONFIG_CONST*/ gDcmDsdSubService_22[] = {
    {
        (uint32)0x0100U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0100, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0101U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0101, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0102U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0102, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0103U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0103, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0104U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0104, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0105U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0105, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0106U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0106, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0200U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0200, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0201U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0201, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0202U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0202, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0203U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0203, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0204U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0204, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0205U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0205, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0206U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0206, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0207U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0207, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0208U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0208, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0209U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0209, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x020AU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x020A, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x020BU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x020B, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0489U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0489, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0620U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0620, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0900U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0900, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0901U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0901, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0902U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0902, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0905U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0905, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0950U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0950, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0960U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0960, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0961U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0961, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0962U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0962, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E00U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E00, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E11U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E11, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E20U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E20, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E21U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E21, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E40U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E40, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E60U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E60, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E61U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E61, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E70U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E70, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E71U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0E71, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0EA0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0EA0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0EA1U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0EA1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0EB0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0EB0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0ED0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0ED0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0ED1U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0ED1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0ED2U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0ED2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0ED5U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0ED5, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0EF0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0EF0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0F10U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0F10, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0F11U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0F11, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0F12U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0F12, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0F30U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0F30, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0F50U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0F50, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0F60U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x0F60, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x1300U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x1300, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x1305U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x1305, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x1600U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x1600, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x1620U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x1620, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2800U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2800, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2801U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2801, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2802U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2802, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2803U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2803, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2804U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2804, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2810U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2810, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2820U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2820, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2828U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2828, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2830U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2830, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2838U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2838, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2850U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2850, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2851U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2851, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2852U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2852, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2853U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2853, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2854U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2854, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2855U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2855, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2856U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2856, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2857U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x2857, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3002U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3002, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3010U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3010, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3021U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3021, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3022U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3022, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3030U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3030, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3031U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3031, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3032U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3032, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3033U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3033, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3034U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3034, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3035U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3035, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3036U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3036, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3037U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3037, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3040U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3040, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3041U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3041, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3042U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3042, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3043U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3043, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3050U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3050, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3051U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3051, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3052U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3052, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3053U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3053, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3054U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3054, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3055U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3055, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3056U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3056, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3057U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3057, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3058U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3058, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3059U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3059, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x305AU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x305A, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x305BU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x305B, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3070U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3070, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3071U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3071, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3080U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3080, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3081U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3081, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3082U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3082, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3083U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3083, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3090U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3090, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3091U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3091, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3092U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3092, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3093U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3093, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30A0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30A0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30A1U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30A1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30A2U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30A2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30A3U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30A3, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30B0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30B0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30B1U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30B1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30B2U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30B2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30B3U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30B3, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30C0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30C0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30C1U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30C1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30C2U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30C2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30C3U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30C3, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30D0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30D0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30D1U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30D1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30D2U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30D2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30D3U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30D3, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30E0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E1U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30E1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E2U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30E2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E3U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30E3, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E4U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30E4, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E5U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30E5, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E6U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30E6, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30F0U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30F0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30F1U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30F1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30F2U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30F2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30F3U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x30F3, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3140U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3140, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3141U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3141, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3142U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3142, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3143U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3143, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3150U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3150, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3151U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3151, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3152U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3152, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3153U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x3153, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x4000U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x4000, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x4010U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x4010, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x4011U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x4011, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x4012U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x4012, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x4018U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x4018, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x4019U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x4019, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x401AU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x401A, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA500U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xA500, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA501U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF18A, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA502U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF197, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA503U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xA503, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA504U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF18B, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA505U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF181, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA506U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF184, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA507U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF194, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA508U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF182, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA509U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF185, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA50AU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xA50A, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA50BU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xA50B, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA50CU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF195, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA50DU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF192, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA50EU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF193, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xA50FU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xA50F, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_PROGRAMMING | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xDFEFU, /* DID */
        STD_ON, /* Switch */
        64U, /* Data Size */
        App_Read0xDFEF, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF101U, /* DID */
        STD_ON, /* Switch */
        56U, /* Data Size */
        App_Read0xF101, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF110U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Read0xF110, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF112U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Read0xF112, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF113U, /* DID */
        STD_ON, /* Switch */
        4U, /* Data Size */
        App_Read0xF113, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF180U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Read0xF180, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF181U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF181, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF182U, /* DID */
        STD_ON, /* Switch */
        40U, /* Data Size */
        App_Read0xF182, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF184U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF184, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF185U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Read0xF185, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF186U, /* DID */
        STD_ON, /* Switch */
        1U, /* Data Size */
        App_Read0xF186, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF187U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Read0xF187, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF189U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Read0xF189, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF18AU, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0xF18A, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF18BU, /* DID */
        STD_ON, /* Switch */
        4U, /* Data Size */
        App_Read0xF18B, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF18CU, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Read0xF18C, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF18EU, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Read0xF18E, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF190U, /* DID */
        STD_ON, /* Switch */
        17U, /* Data Size */
        App_Read0xF190, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF192U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Read0xF192, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF193U, /* DID */
        STD_ON, /* Switch */
        1U, /* Data Size */
        App_Read0xF193, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF194U, /* DID */
        STD_ON, /* Switch */
        40U, /* Data Size */
        App_Read0xF194, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF195U, /* DID */
        STD_ON, /* Switch */
        1U, /* Data Size */
        App_Read0xF195, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF197U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Read0xF197, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF198U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Read0xF198, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF199U, /* DID */
        STD_ON, /* Switch */
        4U, /* Data Size */
        App_Read0xF199, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC | DCM_SESSION_PROGRAMMING), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF19DU, /* DID */
        STD_ON, /* Switch */
        4U, /* Data Size */
        App_Read0xF19D, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF19EU, /* DID */
        STD_ON, /* Switch */
        32U, /* Data Size */
        App_Read0xF19E, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x1301U, /* DID */
        STD_ON, /* Switch */
        DCM_DID_SIZE_UNUSED, /* Data Size */
        App_Read0x1301, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
    },
};

uint8 Dcm_NumberOfReadDID = (uint8)ARRAY_SIZE(gDcmDsdSubService_22);
#endif

/* 0x23 0x3D */
#if((DCM_SERVICE_23_ENABLED == STD_ON)||(DCM_SERVICE_3D_ENABLED == STD_ON))
/* Config AddressFormat Bytes and SizeFormat Bytes */
const Dcm_MemoryAddressFormatType/*DCM_CONFIG_CONST*/  gMemoryAddressFormat = 0U;
const Dcm_MemorySizeFormatType/*DCM_CONFIG_CONST*/ gMemorySizeFormat = 0U;
#endif

/* 0x23 */
#if(DCM_SERVICE_23_ENABLED == STD_ON)
const DcmDspReadMemoryRangeInfo/*DCM_CONFIG_CONST*/   gDcmDspReadMemoryRangeInfo_23[NUMBER_OF_READ_ADDRESS_SEG] = {
};
#endif

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
const Dcm_24_ServiceInfoType/*DCM_CONFIG_CONST*/  gDcmDsdSubService_24[NUMBER_OF_READ_DID_24] = {
};
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
const Dcm_2A_ServiceInfoType/*DCM_CONFIG_CONST*/   gDcmDsdSubService_2A[NUMBER_OF_PERIODIC_DID] = {
};
#endif

/* 0x2C */
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
const Dcm_2C_ServiceInfoType/*DCM_CONFIG_CONST*/ gDcmDsdSubService_2C[NUMBER_OF_DYN_DID] = {
};
#endif

/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
const Dcm_2E_ServiceInfoType/*DCM_CONFIG_CONST*/ gDcmDsdSubService_2E[] = {
    {
        (uint32)0x0E11U, /* DID */
        STD_ON, /* Switch */
        12U, /* Data Size */
        App_Write0x0E11, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x0E61U, /* DID */
        STD_ON, /* Switch */
        2U, /* Data Size */
        App_Write0x0E61, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x2801U, /* DID */
        STD_ON, /* Switch */
        4U, /* Data Size */
        App_Write0x2801, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3021U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3021, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3030U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3030, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3032U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3032, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3034U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3034, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3036U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3036, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3040U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3040, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3042U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3042, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3050U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3050, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3052U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3052, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3054U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3054, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3056U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3056, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3058U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3058, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x305AU, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x305A, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3070U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3070, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3080U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3080, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3082U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3082, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3090U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3090, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3092U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x3092, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30A0U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30A0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30A2U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30A2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30B0U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30B0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30B2U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30B2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30C0U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30C0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30C2U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30C2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30D0U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30D0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30D2U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30D2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E0U, /* DID */
        STD_ON, /* Switch */
        4U, /* Data Size */
        App_Write0x30E0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E1U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Write0x30E1, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E3U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30E3, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30E5U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30E5, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30F0U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30F0, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x30F2U, /* DID */
        STD_ON, /* Switch */
#if DIAGNOSIS_SUPPORT_LEVEL>=4U
        32U, /* Data Size */
#else
        24U, /* Data Size */
#endif
        App_Write0x30F2, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3140U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Write0x3140, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3142U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Write0x3142, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3150U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Write0x3150, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x3152U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Write0x3152, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x4011U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Write0x4011, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0x4019U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Write0x4019, /* App Callback Funtion */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xDFEFU, /* DID */
        STD_ON, /* Switch */
        64U, /* Data Size */
        App_Write0xDFEF, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF101U, /* DID */
        STD_ON, /* Switch */
        56U, /* Data Size */
        App_Write0xF101, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF110U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Write0xF110, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF112U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Write0xF112, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF190U, /* DID */
        STD_ON, /* Switch */
        17U, /* Data Size */
        App_Write0xF190, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF197U, /* DID */
        STD_ON, /* Switch */
        8U, /* Data Size */
        App_Write0xF197, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF198U, /* DID */
        STD_ON, /* Switch */
        16U, /* Data Size */
        App_Write0xF198, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF199U, /* DID */
        STD_ON, /* Switch */
        4U, /* Data Size */
        App_Write0xF199, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
    {
        (uint32)0xF19DU, /* DID */
        STD_ON, /* Switch */
        4U, /* Data Size */
        App_Write0xF19D, /* App Callback Funtion */
        (DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_REQ_SUPPORTED, /* Supported Address Type */
    },
};

uint8 Dcm_NumberOfWriteDID = (uint8)ARRAY_SIZE(gDcmDsdSubService_2E);
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
const Dcm_2F_ServiceInfoType/*DCM_CONFIG_CONST*/ gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID] = {
    {
        (uint32)0x0489U, /* DID */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        {
            0U,
            DCM_SID_0x2F_SIZE_UNUSED,
            DCM_SID_0x2F_SIZE_UNUSED
        },
        App_ReturnControlToEcu0x0489, /* ReturnControlToEcuFnc */
        DCM_NULL, /* ResetToDefaultFnc */
        DCM_NULL, /* FreezeCurrentStateFnc */
        App_ShortTermAdjustment0x0489, /* ShortTermAdjustmentFnc */
        DCM_NULL, /* Self Defined App Callback Funtion*/
    },
    {
        (uint32)0x0918U, /* DID */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        {
            0U,
            2U,
            2U
        },
        App_ReturnControlToEcu0x0918, /* ReturnControlToEcuFnc */
        DCM_NULL, /* ResetToDefaultFnc */
        DCM_NULL, /* FreezeCurrentStateFnc */
        App_ShortTermAdjustment0x0918, /* ShortTermAdjustmentFnc */
        DCM_NULL, /* Self Defined App Callback Funtion*/
    },
    {
        (uint32)0x0968U, /* DID */
        (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1), /* Supported Security Level */
        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
        {
            0U,
            2U,
            2U
        },
        App_ReturnControlToEcu0x0968, /* ReturnControlToEcuFnc */
        DCM_NULL, /* ResetToDefaultFnc */
        DCM_NULL, /* FreezeCurrentStateFnc */
        App_ShortTermAdjustment0x0968, /* ShortTermAdjustmentFnc */
        DCM_NULL, /* Self Defined App Callback Funtion*/
    },
};
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
const DcmDspRoutine/*DCM_CONFIG_CONST*/  DcmDspRoutineIdentifierTable_31[] = {
    {
        0xF000U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF000, /* StartRoutineFnc */
        DCM_NULL, /* StopRoutineFnc */
        DCM_NULL, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                6UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF001U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF001, /* StartRoutineFnc */
        DCM_NULL, /* StopRoutineFnc */
        DCM_NULL, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF002U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF002, /* StartRoutineFnc */
        DCM_NULL, /* StopRoutineFnc */
        DCM_NULL, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF003U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF003, /* StartRoutineFnc */
        DCM_NULL, /* StopRoutineFnc */
        DCM_NULL, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF004U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF004, /* StartRoutineFnc */
        DCM_NULL, /* StopRoutineFnc */
        DCM_NULL, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF006U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF006, /* StartRoutineFnc */
        DCM_NULL, /* StopRoutineFnc */
        APP_RequestResultsRoutine0xF006, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF007U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF007, /* StartRoutineFnc */
        DCM_NULL, /* StopRoutineFnc */
        DCM_NULL, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF008U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF008, /* StartRoutineFnc */
        App_StopRoutine0xF008, /* StopRoutineFnc */
        APP_RequestResultsRoutine0xF008, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF009U, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF009, /* StartRoutineFnc */
        App_StopRoutine0xF009, /* StopRoutineFnc */
        APP_RequestResultsRoutine0xF009, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    {
        0xF00AU, /* SID */
        STD_ON, /* Switch */
        0U, /* RoutineUsePort, Reserved */
        STD_OFF, /* Fixed Length Check Flag */
        App_StartRoutine0xF00A, /* StartRoutineFnc */
        App_StopRoutine0xF00A, /* StopRoutineFnc */
        APP_RequestResultsRoutine0xF00A, /* RequestResultsRoutineFnc */
        {
            {
                /* Supported Security Level */
     (DCM_SEC_LEV_LOCK | DCM_SEC_LEV_L1),
                        (DCM_SESSION_DEFAULT | DCM_SESSION_EXTENDED_DIAGNOSTIC), /* Supported Session */
                     PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED, /* Supported Address Type */
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                2UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
};

const uint8 Dcm_NumberOfRoutineDID = (uint8)ARRAY_SIZE(DcmDspRoutineIdentifierTable_31);
uint8 /*DCM_NOINIT_DATA*/gRountineControlSequence[(uint8)ARRAY_SIZE(DcmDspRoutineIdentifierTable_31)];

#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
const DcmDspWriteMemoryRangeInfo/*DCM_CONFIG_CONST*/  gDcmDspWriteMemoryRangeInfo_3D[NUMBER_OF_WRITE_ADDRESS_SEG] = {
};
#endif
