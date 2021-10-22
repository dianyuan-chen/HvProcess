#include <string.h>
#include "ucos_ii.h"
#include "Dcm_Types.h"
#include "Dcm.h"
#include "App_PBCfg.h"
#include "CellDataM.h"
#include "HLSS.h"
#include "HWDiagnosis.h"
#include "Hv.h"
#include "Shunt.h"
#include "Hall.h"
#include "ChgSckTmpM.h"
#include "EL.h"
#include "BalanceM.h"
#include "InternalComm.h"
#include "InternalComm_Cbk.h"
#include "AppInfo.h"
#include "DtuComm_M35.h"
#include "ChargeConnectM.h"
#include "HardWareIO.h"
#include "Insu.h"
#include "Soc.h"
#include "Soh.h"
#include "Statistic.h"
#include "DateTimeM.h"
#include "ChargerComm.h"
#include "HardwareSn.h"
#include "GB32960.h"
#include "PwmCapture_Lcfg.h"
#include "Crc.h"
#include "Mcu.h"
#include "AnalogInput.h"
#include "DigitalInput.h"
#include "AppParameterM.h"
#include "DcmUpload.h"
#include "SaveM.h"
#include "StorageM.h"
#include "StorageRecord.h"
#include "UserStrategy.h"
#include "DischargeM.h"
#include "ChargeM.h"
#include "GBRtMsg.h"
#include "SocOcvCalib.h"
#include "BridgeInsu.h"
#include "ExternCanComm.h"
#include "SystemConnection_Lcfg.h"

#define LOG_LEVEL LOG_LEVEL_OFF
#include "Logger.h"

#if(DCM_SERVICE_28_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_85_ENABLED == STD_ON)
uint8 gDTCSwitch;
#endif

#if(DCM_SERVICE_3D_ENABLED == STD_ON)
#define W8(addr, value)              (*((uint8 *) (addr)) = (value))
#define R8(addr)                     (*((uint8 *) (addr)))
#endif

#if(ISO_15031_5 == STD_ON)
/* For 0x01*/
/* For 0x02*/
/* For 0x06*/
/* For 0x09*/
#endif

/* For 0x22*/
#define ReadHandle_0x0100   (0u)
#define ReadHandle_0x0101   (1u)
#define ReadHandle_0x0102   (2u)
#define ReadHandle_0x0103   (3u)
#define ReadHandle_0x0104   (4u)
#define ReadHandle_0x0105   (5u)
#define ReadHandle_0x0106   (6u)
#define ReadHandle_0x0200   (7u)
#define ReadHandle_0x0201   (8u)
#define ReadHandle_0x0202   (9u)
#define ReadHandle_0x0203   (10u)
#define ReadHandle_0x0204   (11u)
#define ReadHandle_0x0205   (12u)
#define ReadHandle_0x0206   (13u)
#define ReadHandle_0x0207   (14u)
#define ReadHandle_0x0208   (15u)
#define ReadHandle_0x0209   (16u)
#define ReadHandle_0x020A   (17u)
#define ReadHandle_0x020B   (18u)
#define ReadHandle_0x0489   (19u)
#define ReadHandle_0x0620   (20u)
#define ReadHandle_0x0900   (21u)
#define ReadHandle_0x0901   (22u)
#define ReadHandle_0x0902   (23u)
#define ReadHandle_0x0905   (24u)
#define ReadHandle_0x0950   (25u)
#define ReadHandle_0x0960   (26u)
#define ReadHandle_0x0961   (27u)
#define ReadHandle_0x0962   (28u)
#define ReadHandle_0x0E00   (29u)
#define ReadHandle_0x0E11   (30u)
#define ReadHandle_0x0E20   (31u)
#define ReadHandle_0x0E21   (32u)
#define ReadHandle_0x0E40   (33u)
#define ReadHandle_0x0E60   (34u)
#define ReadHandle_0x0E61   (35u)
#define ReadHandle_0x0E70   (36u)
#define ReadHandle_0x0E71   (37u)
#define ReadHandle_0x0EA0   (38u)
#define ReadHandle_0x0EA1   (39u)
#define ReadHandle_0x0EB0   (40u)
#define ReadHandle_0x0ED0   (41u)
#define ReadHandle_0x0ED1   (42u)
#define ReadHandle_0x0ED2   (43u)
#define ReadHandle_0x0ED5   (44u)
#define ReadHandle_0x0EF0   (45u)
#define ReadHandle_0x0F10   (46u)
#define ReadHandle_0x0F11   (47u)
#define ReadHandle_0x0F12   (48u)
#define ReadHandle_0x0F30   (49u)
#define ReadHandle_0x0F50   (50u)
#define ReadHandle_0x0F60   (51u)
#define ReadHandle_0x1300   (52u)
#define ReadHandle_0x1305   (53u)
#define ReadHandle_0x1600   (54u)
#define ReadHandle_0x1620   (55u)
#define ReadHandle_0x2800   (56u)
#define ReadHandle_0x2801   (57u)
#define ReadHandle_0x2802   (58u)
#define ReadHandle_0x2803   (59u)
#define ReadHandle_0x2804   (60u)
#define ReadHandle_0x2810   (61u)
#define ReadHandle_0x2820   (62u)
#define ReadHandle_0x2828   (63u)
#define ReadHandle_0x2830   (64u)
#define ReadHandle_0x2838   (65u)
#define ReadHandle_0x2850   (66u)
#define ReadHandle_0x2851   (67u)
#define ReadHandle_0x2852   (68u)
#define ReadHandle_0x2853   (69u)
#define ReadHandle_0x2854   (70u)
#define ReadHandle_0x2855   (71u)
#define ReadHandle_0x2856   (72u)
#define ReadHandle_0x2857   (73u)
#define ReadHandle_0x3002   (74u)
#define ReadHandle_0x3010   (75u)
#define ReadHandle_0x3021   (76u)
#define ReadHandle_0x3022   (77u)
#define ReadHandle_0x3030   (78u)
#define ReadHandle_0x3031   (79u)
#define ReadHandle_0x3032   (80u)
#define ReadHandle_0x3033   (81u)
#define ReadHandle_0x3034   (82u)
#define ReadHandle_0x3035   (83u)
#define ReadHandle_0x3036   (84u)
#define ReadHandle_0x3037   (85u)
#define ReadHandle_0x3040   (86u)
#define ReadHandle_0x3041   (87u)
#define ReadHandle_0x3042   (88u)
#define ReadHandle_0x3043   (89u)
#define ReadHandle_0x3050   (90u)
#define ReadHandle_0x3051   (91u)
#define ReadHandle_0x3052   (92u)
#define ReadHandle_0x3053   (93u)
#define ReadHandle_0x3054   (94u)
#define ReadHandle_0x3055   (95u)
#define ReadHandle_0x3056   (96u)
#define ReadHandle_0x3057   (97u)
#define ReadHandle_0x3058   (98u)
#define ReadHandle_0x3059   (99u)
#define ReadHandle_0x305A   (100u)
#define ReadHandle_0x305B   (101u)
#define ReadHandle_0x3070   (102u)
#define ReadHandle_0x3071   (103u)
#define ReadHandle_0x3080   (104u)
#define ReadHandle_0x3081   (105u)
#define ReadHandle_0x3082   (106u)
#define ReadHandle_0x3083   (107u)
#define ReadHandle_0x3090   (108u)
#define ReadHandle_0x3091   (109u)
#define ReadHandle_0x3092   (110u)
#define ReadHandle_0x3093   (111u)
#define ReadHandle_0x30A0   (112u)
#define ReadHandle_0x30A1   (113u)
#define ReadHandle_0x30A2   (114u)
#define ReadHandle_0x30A3   (115u)
#define ReadHandle_0x30B0   (116u)
#define ReadHandle_0x30B1   (117u)
#define ReadHandle_0x30B2   (118u)
#define ReadHandle_0x30B3   (119u)
#define ReadHandle_0x30C0   (120u)
#define ReadHandle_0x30C1   (121u)
#define ReadHandle_0x30C2   (122u)
#define ReadHandle_0x30C3   (123u)
#define ReadHandle_0x30D0   (124u)
#define ReadHandle_0x30D1   (125u)
#define ReadHandle_0x30D2   (126u)
#define ReadHandle_0x30D3   (127u)
#define ReadHandle_0x30E0   (128u)
#define ReadHandle_0x30E1   (129u)
#define ReadHandle_0x30E2   (130u)
#define ReadHandle_0x30E3   (131u)
#define ReadHandle_0x30E4   (132u)
#define ReadHandle_0x30E5   (133u)
#define ReadHandle_0x30E6   (134u)
#define ReadHandle_0x30F0   (135u)
#define ReadHandle_0x30F1   (136u)
#define ReadHandle_0x30F2   (137u)
#define ReadHandle_0x30F3   (138u)
#define ReadHandle_0x3140   (139u)
#define ReadHandle_0x3141   (140u)
#define ReadHandle_0x3142   (141u)
#define ReadHandle_0x3143   (142u)
#define ReadHandle_0x3150   (143u)
#define ReadHandle_0x3151   (144u)
#define ReadHandle_0x3152   (145u)
#define ReadHandle_0x3153   (146u)
#define ReadHandle_0x4000   (147u)
#define ReadHandle_0x4010   (148u)
#define ReadHandle_0x4011   (149u)
#define ReadHandle_0x4012   (150u)
#define ReadHandle_0x4018   (151u)
#define ReadHandle_0x4019   (152u)
#define ReadHandle_0x401A   (153u)
#define ReadHandle_0xA500   (154u)
#define ReadHandle_0xA501   (155u)
#define ReadHandle_0xA502   (156u)
#define ReadHandle_0xA503   (157u)
#define ReadHandle_0xA504   (158u)
#define ReadHandle_0xA505   (159u)
#define ReadHandle_0xA506   (160u)
#define ReadHandle_0xA507   (161u)
#define ReadHandle_0xA508   (162u)
#define ReadHandle_0xA509   (163u)
#define ReadHandle_0xA50A   (164u)
#define ReadHandle_0xA50B   (165u)
#define ReadHandle_0xA50C   (166u)
#define ReadHandle_0xA50D   (167u)
#define ReadHandle_0xA50E   (168u)
#define ReadHandle_0xA50F   (169u)
#define ReadHandle_0xDFEF   (170u)
#define ReadHandle_0xF101   (171u)
#define ReadHandle_0xF110   (172u)
#define ReadHandle_0xF112   (173u)
#define ReadHandle_0xF113   (174u)
#define ReadHandle_0xF180   (175u)
#define ReadHandle_0xF181   (176u)
#define ReadHandle_0xF182   (177u)
#define ReadHandle_0xF184   (178u)
#define ReadHandle_0xF185   (179u)
#define ReadHandle_0xF186   (180u)
#define ReadHandle_0xF187   (181u)
#define ReadHandle_0xF189   (182u)
#define ReadHandle_0xF18A   (183u)
#define ReadHandle_0xF18B   (184u)
#define ReadHandle_0xF18C   (185u)
#define ReadHandle_0xF18E   (186u)
#define ReadHandle_0xF190   (187u)
#define ReadHandle_0xF192   (188u)
#define ReadHandle_0xF193   (189u)
#define ReadHandle_0xF194   (190u)
#define ReadHandle_0xF195   (191u)
#define ReadHandle_0xF197   (192u)
#define ReadHandle_0xF198   (193u)
#define ReadHandle_0xF199   (194u)
#define ReadHandle_0xF19D   (195u)
#define ReadHandle_0xF19E   (196u)

/* For 0x24*/

/* For 0x27 */
#define Request_Seed_L1_Hanle        (0U)
#define Request_Seed_L2_Hanle        (1U)
#define Request_Seed_L3_Hanle        (2U)
#define Request_Seed_L4_Hanle        (3U)
#define Request_Seed_L5_Hanle        (4U)
#define Request_Seed_L6_Hanle        (5U)
#define Request_Seed_L7_Hanle        (6U)

/* For 0x28 */
#define Dcm_EnRx_EnTx                (0U)
#define Dcm_DisRx_EnTx               (1U)
#define Dcm_EnRx_DisTx               (2U)
#define Dcm_DisRx_DisTx              (3U)


/* For 0x2A*/

/* For 0x2C*/

/* For 0x2E*/
#define WriteHandle_0x0E11  (0u)
#define WriteHandle_0x0E61  (1u)
#define WriteHandle_0x2801  (2u)
#define WriteHandle_0x3021  (3u)
#define WriteHandle_0x3030  (4u)
#define WriteHandle_0x3032  (5u)
#define WriteHandle_0x3034  (6u)
#define WriteHandle_0x3036  (7u)
#define WriteHandle_0x3040  (8u)
#define WriteHandle_0x3042  (9u)
#define WriteHandle_0x3050  (10u)
#define WriteHandle_0x3052  (11u)
#define WriteHandle_0x3054  (12u)
#define WriteHandle_0x3056  (13u)
#define WriteHandle_0x3058  (14u)
#define WriteHandle_0x305A  (15u)
#define WriteHandle_0x3070  (16u)
#define WriteHandle_0x3080  (17u)
#define WriteHandle_0x3082  (18u)
#define WriteHandle_0x3090  (19u)
#define WriteHandle_0x3092  (20u)
#define WriteHandle_0x30A0  (21u)
#define WriteHandle_0x30A2  (22u)
#define WriteHandle_0x30B0  (23u)
#define WriteHandle_0x30B2  (24u)
#define WriteHandle_0x30C0  (25u)
#define WriteHandle_0x30C2  (26u)
#define WriteHandle_0x30D0  (27u)
#define WriteHandle_0x30D2  (28u)
#define WriteHandle_0x30E0  (29u)
#define WriteHandle_0x30E1  (30u)
#define WriteHandle_0x30E3  (31u)
#define WriteHandle_0x30E5  (32u)
#define WriteHandle_0x30F0  (33u)
#define WriteHandle_0x30F2  (34u)
#define WriteHandle_0x3140  (35u)
#define WriteHandle_0x3142  (36u)
#define WriteHandle_0x3150  (37u)
#define WriteHandle_0x3152  (38u)
#define WriteHandle_0x4011  (39u)
#define WriteHandle_0x4019  (40u)
#define WriteHandle_0xDFEF  (41u)
#define WriteHandle_0xF101  (42u)
#define WriteHandle_0xF110  (43u)
#define WriteHandle_0xF112  (44u)
#define WriteHandle_0xF190  (45u)
#define WriteHandle_0xF197  (46u)
#define WriteHandle_0xF198  (47u)
#define WriteHandle_0xF199  (48u)
#define WriteHandle_0xF19D  (49u)

/* For 0x2F*/
#define IOcontrolHandle_0x0489  (0u)
#define IOcontrolHandle_0x0918  (1u)
#define IOcontrolHandle_0x0968  (2u)

/* For 0x31*/
#define RoutineHandle_0xF000    (0u)
#define RoutineHandle_0xF001    (1u)
#define RoutineHandle_0xF002    (2u)
#define RoutineHandle_0xF003    (3u)
#define RoutineHandle_0xF004    (4u)
#define RoutineHandle_0xF005    (5u)
#define RoutineHandle_0xF006    (6u)
#define RoutineHandle_0xF007    (7u)
#define RoutineHandle_0xF008    (8u)
#define RoutineHandle_0xF009    (9u)
#define RoutineHandle_0xF00A    (10u)

/*******************************************************************************
* Global variables(Scope:local)
********************************************************************************/
#if(ISO_15031_5 == STD_ON)
/* For 0x02*/
/* For 0x03*/
/* For 0x04*/
/* For 0x07*/
/* For 0x08*/
/* For 0x0A*/
#endif

static uint8 DTCStatusAvailabilityMask = 0xffU;
uint32 SupportedDTCGroup = 0x00U;
static uint32 SupportedDTC[] = {
    0x100000U,
    0x100001U,
    0x100002U,
    0x100003U,
    0x100004U,
    0x100005U
};
const uint16 Dcm_NumberOfDTC = ARRAY_SIZE(SupportedDTC);
#define NUM_OF_DTC 6U
uint8 DTCStatus[NUM_OF_DTC];

uint8 DATA_0xDFEF[64];
uint8 DATA_0xF101[56];
uint8 DATA_0xF110[8];
uint8 DATA_0xF112[8];
uint8 DATA_0xF113[4];
uint8 DATA_0xF180[16];
uint8 DATA_0xF186[1];
uint8 DATA_0xF187[8];
uint8 DATA_0xF189[16];
uint8 DATA_0xF18A[6];
uint8 DATA_0xF18B[4];
uint8 DATA_0xF18C[16];
uint8 DATA_0xF18E[16];
uint8 DATA_0xF193[16];
uint8 DATA_0xF195[16];
uint8 DATA_0xF197[8];
uint8 DATA_0xF198[16];
uint8 DATA_0xF199[4];
uint8 DATA_0xF19D[4];
uint8 DATA_0xF19E[32];
/*
static uint8 ApplicationSoftwareIdentification[32] =
{
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b,
    0x1c, 0x1d, 0x1e, 0x1f
};
*/
/* Below codes are demo for 0x27, all of them can be deleted */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
static uint8 MagicSeed[4];
#endif

#if(DCM_SERVICE_28_ENABLED == STD_ON)
// static uint8 Dcm_NmMessage_Status = Dcm_EnRx_EnTx;
// static uint8 Dcm_ComMessage_Status = Dcm_EnRx_EnTx;
#endif

#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
Std_ReturnType App_DiagnosticActive(void) {
    return E_OK;
}
#endif

#if(ISO_15031_5 == STD_ON)
#if(DCM_SERVICE_01_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_03_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_04_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_06_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_07_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_08_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_09_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_0A_ENABLED == STD_ON)
#endif
#endif

/* 0x10 */
#if(DCM_SERVICE_10_ENABLED == STD_ON)

void App_Default(Dcm_MsgContextType *pMsgContext) {
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if (GetSuppressPosResponseBit() == 0U) { /* If positive response is supressed, dont' need make it */
#if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax);
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2StarServerMax / 10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
#else
        pMsgContext->resDataLen = 2U;
#endif
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_ProcessingDoneNoResponse();
    }
}


void App_DefaultPost(Std_ReturnType Result) {
    uint8 i;

    if (Result == E_OK) {
        Set_SesCtrl(DCM_SESSION_DEFAULT);
        for (i = 0U; i < KIND_OF_SECURITY_LEVEL; i++) {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;

        /* reset routine Control */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */
        for (i = 0U; i < NUMBER_OF_RID; i++) {
            gRountineControlSequence[i] = 0U;
        }
#endif

        /* Reset the CommunicationControl Flags */
#if(DCM_SERVICE_28_ENABLED == STD_ON)
#endif

        /* add your code here*/

        if (RuntimeM_GetMode() == RUNTIMEM_RUNMODE_DTU) {
            RuntimeM_RequestPowerDown();
        }
    } else {
    }
}

void App_Programming(Dcm_MsgContextType *pMsgContext) {
    Std_ReturnType res;
    uint32 tempP2Star;

    /* Step 1:Transmit positive response*/
    res = RuntimeM_RequestToProgram();
    if (GetSuppressPosResponseBit() == 0U && res == E_OK) { /* If positive response is supressed, dont' need make it */
        GBRtMsg_Cancel();
#if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2ServerMax);
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2StarServerMax / 10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
#else
        pMsgContext->resDataLen = 2U;
#endif
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
    }
}


void App_ProgrammingPost(Std_ReturnType Result) {
    uint8 i;

    if (Result == E_OK) {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_PROGRAMMING);
        for (i = 0U; i < KIND_OF_SECURITY_LEVEL; i++) {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;

        /* reset routine Control */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */
        for (i = 0U; i < NUMBER_OF_RID; i++) {
            gRountineControlSequence[i] = 0U;
        }
#endif

        /* add your code here*/
    } else {
    }
}

void App_Extended_Diagnostic(Dcm_MsgContextType *pMsgContext) {
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if (GetSuppressPosResponseBit() == 0U) { /* If positive response is supressed, dont' need make it */
#if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax);
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2StarServerMax / 10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
#else
        pMsgContext->resDataLen = 2U;
#endif
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_ProcessingDoneNoResponse();
    }
}


void App_Extended_DiagnosticPost(Std_ReturnType Result) {
    uint8 i;

    if (Result == E_OK) {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_EXTENDED_DIAGNOSTIC);
        for (i = 0U; i < KIND_OF_SECURITY_LEVEL; i++) {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;

        /* reset routine Control */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */
        for (i = 0U; i < NUMBER_OF_RID; i++) {
            gRountineControlSequence[i] = 0U;
        }
#endif

        /* add your code here*/
    } else {
    }
}
#endif

/* 0x11 */
#if(DCM_SERVICE_11_ENABLED == STD_ON)
void App_Hard_Reset_Reset(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == RuntimeM_StartReset(RUNTIMEM_RUNMODE_NORMAL)) {
        pMsgContext->resData[DCM_INDEX_1] = 0x01U;
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
    }
}

void App_Hard_Reset_ResetPost(Std_ReturnType Result) {

    if (Result == E_OK) {
        /* Reset MCU at here. */
    } else {
    }
}

void App_Soft_Reset_Reset(Dcm_MsgContextType *pMsgContext) {
    pMsgContext->resData[DCM_INDEX_1] = 0x01U;
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}

void App_Soft_Reset_ResetPost(Std_ReturnType Result) {
    uint8 i;

    if (Result == E_OK) {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);

        for (i = 0U; i < KIND_OF_SECURITY_LEVEL; i++) {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;

        /* reset routine Control */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */
        for (i = 0U; i < NUMBER_OF_RID; i++) {
            gRountineControlSequence[i] = 0U;
        }
#endif
    } else {
    }
}

void App_Soft_Reset_ResetToData(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == RuntimeM_StartReset(RUNTIMEM_RUNMODE_DATA)) {
        pMsgContext->resData[DCM_INDEX_1] = 0x61U;
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
    }
}

void App_Soft_Reset_ResetToDataPost(Std_ReturnType Result) {
    if (Result == E_OK) {
        /* Reset MCU at here. */
    } else {
    }
}

#endif

/* 0x14 */
#if(DCM_SERVICE_14_ENABLED == STD_ON)
void App_ClearDiagnosticInformation(Dcm_MsgContextType *pMsgContext) {
    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;

    Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_1], pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3]);
    for (i = 0U; i < NUM_OF_DTC; i++) {
        if (Dtc == SupportedDTC[i]) {
            break;
        } else {
            if (i == (NUM_OF_DTC - 1U)) {
                if ((Dtc != 0xffffffU) && (Dtc != SupportedDTCGroup)) {
                    error = 1U;
                    DsdInternal_SetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
                } else {
                }
            } else {
            }
        }
    }
    if (error == 0U) {
        for (i = 0U; i < NUM_OF_DTC; i++) {
            DTCStatus[i] = 0U;
        }
        pMsgContext->resDataLen = 1U;
        DsdInternal_ProcessingDone(pMsgContext);

        /* Add your code here to clear DTC information */
    } else {
    }
}
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)
void App_Read0x0100(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    (void)memcpy(&pMsgContext->resData[length], &BatteryInfo_BaseConfigInfo, sizeof(BatteryInfo_BaseConfigType));
    length += sizeof(BatteryInfo_BaseConfigType);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0101(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length = 0U;

    if (gDcmDsdSubService_22[ReadHandle_0x0101].DcmDspDataSize != DCM_DID_SIZE_UNUSED) {
        length = gDcmDsdSubService_22[ReadHandle_0x0101].DcmDspDataSize;
    } else {
        length = CellDataM_GetBmuVoltageLogicIdMax(SystemConnection_ConfigInfo.SlaveNum - 1U);
    }

    offset = DCM_INDEX_2;
    for (i = 0U; i < length; i++) {
        App_VoltageType volt = CellDataM_GetVoltage(i);
        pMsgContext->resData[offset++] = (uint8)(volt >> 8);
        pMsgContext->resData[offset++] = (uint8)volt;
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0102(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length = 0U;

    if (gDcmDsdSubService_22[ReadHandle_0x0102].DcmDspDataSize != DCM_DID_SIZE_UNUSED) {
        length = gDcmDsdSubService_22[ReadHandle_0x0102].DcmDspDataSize;
    } else {
        length = CellDataM_GetBmuTemperatureLogicIdMax(SystemConnection_ConfigInfo.SlaveNum - 1U);
    }

    offset = DCM_INDEX_2;
    for (i = 0U; i < length; i++) {
        pMsgContext->resData[offset++] = CellDataM_GetTemperature(i);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0103(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length = 0U;

    if (gDcmDsdSubService_22[ReadHandle_0x0103].DcmDspDataSize != DCM_DID_SIZE_UNUSED) {
        length = gDcmDsdSubService_22[ReadHandle_0x0103].DcmDspDataSize;
    } else {
        length = CellDataM_GetBmuHeatTemperatureLogicIdMax(SystemConnection_ConfigInfo.SlaveNum - 1U);
    }

    offset = DCM_INDEX_2;
    for (i = 0U; i < length; i++) {
        pMsgContext->resData[offset++] = CellDataM_GetHeatTemperature(i);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0104(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length = 0U;

    if (gDcmDsdSubService_22[ReadHandle_0x0104].DcmDspDataSize != DCM_DID_SIZE_UNUSED) {
        length = gDcmDsdSubService_22[ReadHandle_0x0104].DcmDspDataSize;
    } else {
        length = CellDataM_GetBmuPoleTemperatureLogicIdMax(SystemConnection_ConfigInfo.SlaveNum - 1U);
    }

    offset = DCM_INDEX_2;
    for (i = 0U; i < length; i++) {
        pMsgContext->resData[offset++] = CellDataM_GetPoleTemperature(i);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0105(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    length += BalanceM_GetBalanceStatus(&pMsgContext->resData[length]);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0106(Dcm_MsgContextType *pMsgContext) {
    uint16 i, length = DCM_INDEX_2;

    pMsgContext->resData[length++] = (uint8)SystemConnection_ConfigInfo.BcuType;

    for (i = 0U; i < SystemConnection_ConfigInfo.SlaveNum; i++) {
        pMsgContext->resData[length++] = (uint8)SystemConnection_SlaveTypesTable[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0200(Dcm_MsgContextType *pMsgContext) {
    uint16 i, size, length = DCM_INDEX_2;

    size = SystemConnection_ConfigInfo.SlaveNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = (uint8)(CellDataM_BmuVoltageLogicIdMax[i] >> 8);
        pMsgContext->resData[length++] = (uint8)CellDataM_BmuVoltageLogicIdMax[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0201(Dcm_MsgContextType *pMsgContext) {
    uint16 i, size, length = DCM_INDEX_2;

    size = SystemConnection_ConfigInfo.voltageSampleBoardNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = CellDataM_BmuBoardVoltageLogicIdMax[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0202(Dcm_MsgContextType *pMsgContext) {
    uint16 i, size, length = DCM_INDEX_2;

    size = SystemConnection_ConfigInfo.voltageNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = CellDataM_VoltageLogicIdToPhysicalIdMap[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0203(Dcm_MsgContextType *pMsgContext) {
    uint16 i, size, length = DCM_INDEX_2;

    size = SystemConnection_ConfigInfo.SlaveNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = (uint8)(CellDataM_BmuTemperatureLogicIdMax[i] >> 8);
        pMsgContext->resData[length++] = (uint8)CellDataM_BmuTemperatureLogicIdMax[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0204(Dcm_MsgContextType *pMsgContext) {
    uint16 i, size, length = DCM_INDEX_2;

    size = SystemConnection_ConfigInfo.temperatureSampleBoardNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = CellDataM_BmuBoardTemperatureLogicIdMax[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0205(Dcm_MsgContextType *pMsgContext) {
    uint16 i, size, length = DCM_INDEX_2;

    size = SystemConnection_ConfigInfo.temperatureNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = CellDataM_TemperatureLogicIdToPhysicalIdMap[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0206(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint16 i, size;

    size = SystemConnection_ConfigInfo.SlaveNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = (uint8)(CellDataM_BmuHeatTemperatureLogicIdMax[i] >> 8);
        pMsgContext->resData[length++] = (uint8)CellDataM_BmuHeatTemperatureLogicIdMax[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0207(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint16 i, size;

    size = SystemConnection_ConfigInfo.temperatureSampleBoardNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = CellDataM_BmuBoardHeatTemperatureLogicIdMax[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0208(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint16 i, size;

    size = SystemConnection_ConfigInfo.heatTemperatureNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = CellDataM_HeatTemperatureLogicIdToPhysicalIdMap[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0209(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint16 i, size;

    size = SystemConnection_ConfigInfo.SlaveNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = (uint8)(CellDataM_BmuPoleTemperatureLogicIdMax[i] >> 8);
        pMsgContext->resData[length++] = (uint8)CellDataM_BmuPoleTemperatureLogicIdMax[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x020A(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint16 i, size;

    size = SystemConnection_ConfigInfo.temperatureSampleBoardNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = CellDataM_BmuBoardPoleTemperatureLogicIdMax[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x020B(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint16 i, size;

    size = SystemConnection_ConfigInfo.poleTemperatureNum;
    for (i = 0U; i < size; i++) {
        pMsgContext->resData[length++] = CellDataM_PoleTemperatureLogicIdToPhysicalIdMap[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0489(Dcm_MsgContextType *pMsgContext) {
    uint16 i, length = DCM_INDEX_2;

    for (i = 0U; i < SystemConnection_ConfigInfo.SlaveNum; i++) {
        pMsgContext->resData[length ++] = (uint8)i;
        if (BalanceM_IsForceBalance((App_SlaveIdType)i) != 0U) {
            length += BalanceM_GetBalanceCommand((App_SlaveIdType)i, &pMsgContext->resData[length]);
        } else {
            (void)memset(&pMsgContext->resData[length], 0, BALANCEM_BALANCE_COMMAND_BUFFER_SIZE);
            length += BALANCEM_BALANCE_COMMAND_BUFFER_SIZE;
        }
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0620(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint32 temp;
    uint32 lacci[2];

    WRITE_BT_UINT8(pMsgContext->resData, length, DtuM35_GetRuntimeStatus(0U));
    WRITE_BT_UINT16(pMsgContext->resData, length, DtuM35_GetSupplyVoltage());

    temp = pMsgContext->resMaxDataLen - length;
    if (temp > 0xFFU) {
        temp = 0xFFU;
    }
    DtuM35_GetCCID((sint8 *)(&pMsgContext->resData[length]), (uint8)temp); //CCID
    length += strlen((const sint8 *)&pMsgContext->resData[length]) + 1U;

    temp = pMsgContext->resMaxDataLen - length;
    if (temp > 0xFFU) {
        temp = 0xFFU;
    }
    DtuM35_GetIMEI((sint8 *)(&pMsgContext->resData[length]), (uint8)temp); //IMEI
    length += strlen((const sint8 *)&pMsgContext->resData[length]) + 1U;

    DtuM35_GetLacCi(lacci);
    pMsgContext->resData[length++] = (uint8)(lacci[0]);
    pMsgContext->resData[length++] = (uint8)(lacci[0] >> 8);

    (void)memcpy(&pMsgContext->resData[length], &lacci[1], 4U);
    length += 4U;

    WRITE_BT_UINT8(pMsgContext->resData, length, DtuM35_GetOPS()); //ops
    DtuM35_GetSingalQuality(&pMsgContext->resData[length] + 1U, &pMsgContext->resData[length]);
    length += 2U;
    WRITE_BT_UINT8(pMsgContext->resData, length, DtuM35_GetGSMRegisteState()); //GSM
    WRITE_BT_UINT8(pMsgContext->resData, length, DtuM35_GetGPRSRegisteState()); //GPRS
    WRITE_BT_UINT32(pMsgContext->resData, length, DutM35_GetSentPacketCount());

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0900(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length;

    length = HLSS_BCU_DRIVER_NUM + HLSS_SINGLE_BMU_DRIVER_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum;

    offset = DCM_INDEX_2;
    for (i = 0U; i < length; ++i) {
        if (HLSS_GetActual((HLSS_ChannelType)i) == HLSS_DRIVE_ON) {
            pMsgContext->resData[offset++] = 1U;
        } else {
            pMsgContext->resData[offset++] = 0U;
        }
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0901(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length;

    length = HLSS_BCU_DRIVER_NUM + HLSS_SINGLE_BMU_DRIVER_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum;
    offset = DCM_INDEX_2;
    for (i = 0U; i < length; ++i) {
        HLSS_VoltageType volt = HLSS_GetDiagnosisVoltage((HLSS_ChannelType)i);
        pMsgContext->resData[offset++] = (uint8)(volt >> 8);
        pMsgContext->resData[offset++] = (uint8)(volt);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0902(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length;

    length = HLSS_BCU_DRIVER_NUM + HLSS_SINGLE_BMU_DRIVER_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum;

    offset = DCM_INDEX_2;
    for (i = 0U; i < length; ++i) {
        HLSS_CurrentType current = HLSS_GetDiagnosisCurrent((HLSS_ChannelType)i);
        pMsgContext->resData[offset++] = (uint8)(current >> 8);
        pMsgContext->resData[offset++] = (uint8)(current);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0905(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length;

    length = HLSS_BCU_DRIVER_NUM + HLSS_SINGLE_BMU_DRIVER_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum;

    offset = DCM_INDEX_2;
    for (i = 0U; i < length; ++i) {
        pMsgContext->resData[offset++] = HLSS_GetForce((HLSS_ChannelType)i);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0950(Dcm_MsgContextType *pMsgContext) {
    uint16 temp, length = DCM_INDEX_2;

    if (HLSS_GetActual(HLSS_BCU_BMU_ENABLE) == HLSS_DRIVE_ON) {
        pMsgContext->resData[length++] = 1U;
    } else {
        pMsgContext->resData[length++] = 0U;
    }
    temp = HLSS_GetDiagnosisVoltage(HLSS_BCU_BMU_ENABLE);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);

    temp = HLSS_GetDiagnosisCurrent(HLSS_BCU_BMU_ENABLE);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0960(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    if (EL_GetDriveState(0U) == EL_LOCK) {
        pMsgContext->resData[length++] = 1U;
    } else {
        pMsgContext->resData[length++] = 0U;
    }

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0961(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    if (EL_GetActualState(0U) == EL_LOCK) {
        pMsgContext->resData[length++] = 1U;
    } else {
        pMsgContext->resData[length++] = 0U;
    }

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0962(Dcm_MsgContextType *pMsgContext) {
    uint16 offset;

    offset = DCM_INDEX_2;
    pMsgContext->resData[offset++] = EL_GetForceControl(0U);
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0E00(Dcm_MsgContextType *pMsgContext) {
    uint16 i, length = DCM_INDEX_2;

    for (i = 0U; i < (uint16)HV_CHANNEL_MAX; ++i) {
        App_Tv100mvType volt = HV_GetVoltage((HV_ChannelType)i);
        pMsgContext->resData[length++] = (uint8)(volt >> 8);
        pMsgContext->resData[length++] = (uint8)(volt);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0E11(Dcm_MsgContextType *pMsgContext) {
    uint16 i, length = DCM_INDEX_2;

    for (i = 0U; i < (uint16)HV_CHANNEL_MAX; ++i) {
        App_Tv100mvType volt = HV_GetGainErr((HV_ChannelType)i);
        pMsgContext->resData[length++] = (uint8)(volt >> 8);
        pMsgContext->resData[length++] = (uint8)(volt);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0E20(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    WRITE_BT_UINT8(pMsgContext->resData, length, Insu_GetStatus());

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0E21(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    WRITE_BT_UINT16(pMsgContext->resData, length, Insu_GetPositive());
    WRITE_BT_UINT16(pMsgContext->resData, length, Insu_GetNegative());
    WRITE_BT_UINT16(pMsgContext->resData, length, Insu_GetSystem());

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0E40(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    Current_SensorCalibrateParam para;

    WRITE_BT_UINT16(pMsgContext->resData, length, Shunt_GetCurrent());
    WRITE_BT_UINT8(pMsgContext->resData, length, Shunt_GetTemperature());
    Shunt_GetCalibrateParam(&para);
    WRITE_BT_UINT16(pMsgContext->resData, length, (uint16)para.zeroOffset);
    WRITE_BT_UINT16(pMsgContext->resData, length, (uint16)para.zeroFilter);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0E60(Dcm_MsgContextType *pMsgContext) {
    uint16 temp = 0U, length = DCM_INDEX_2;

    if (CurrentM_ConfigInfo.main.enable == STD_ON &&
            CurrentM_ConfigInfo.main.channel == CURRENTM_SAMPLE_CHANNEL_SHUNT) {
        temp = 0x01U;
    } else if (CurrentM_ConfigInfo.heater.enable == STD_ON &&
               CurrentM_ConfigInfo.heater.channel == CURRENTM_SAMPLE_CHANNEL_SHUNT) {
        temp = 0x02U;
    } else {
    }
    WRITE_BT_UINT8(pMsgContext->resData, length, (uint8)temp);
    WRITE_BT_UINT16(pMsgContext->resData, length, ShuntSensorConfig.resistor);
    WRITE_BT_UINT16(pMsgContext->resData, length, ShuntSensorConfig.tempDrift);
    WRITE_BT_UINT16(pMsgContext->resData, length, CurrentM_ConfigInfo.zeroFilter[CURRENTM_SAMPLE_CHANNEL_SHUNT]);
    WRITE_BT_UINT8(pMsgContext->resData, length, 0x00U);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
void App_Read0x0E61(Dcm_MsgContextType *pMsgContext) {
    uint16 temp = 0U, length = DCM_INDEX_2;

    (void)ParameterM_EeepRead(PARAMETERM_EEEP_SHUNT_GAIN_ERROR_INDEX, &temp);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0E70(Dcm_MsgContextType *pMsgContext) {
    uint16 temp, length = DCM_INDEX_2;
    Current_SensorCalibrateParam zero_para;

    temp = (uint16)Hall_GetCurrent(0U);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);
    temp = (uint16)Hall_GetSampleVoltage(0U);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);
    Hall_GetCalibrateParam(0U, &zero_para);
    pMsgContext->resData[length++] = (uint8)((uint16)zero_para.zeroFilter >> 8);
    pMsgContext->resData[length++] = (uint8)(zero_para.zeroFilter);
    pMsgContext->resData[length++] = (uint8)((uint16)zero_para.zeroOffset >> 8);
    pMsgContext->resData[length++] = (uint8)(zero_para.zeroOffset);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0E71(Dcm_MsgContextType *pMsgContext) {
    uint16 temp, length = DCM_INDEX_2;
    Current_SensorCalibrateParam zero_para;

    temp = (uint16)Hall_GetCurrent(1U);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);
    temp = (uint16)Hall_GetSampleVoltage(1U);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);
    Hall_GetCalibrateParam(1U, &zero_para);
    pMsgContext->resData[length++] = (uint8)((uint16)zero_para.zeroFilter >> 8);
    pMsgContext->resData[length++] = (uint8)(zero_para.zeroFilter);
    pMsgContext->resData[length++] = (uint8)((uint16)zero_para.zeroOffset >> 8);
    pMsgContext->resData[length++] = (uint8)(zero_para.zeroOffset);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0EA0(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 length = DCM_INDEX_2;

    for (i = 0U; i < CHGSCKTMPM_TEMPERATURE_MAX_NUM; ++i) {
        pMsgContext->resData[length++] = ChgSckTmpM_GetTemperature(i);
    }

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0EA1(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 temp, length = DCM_INDEX_2;

    for (i = 0U; i < CHGSCKTMPM_TEMPERATURE_MAX_NUM; ++i) {
        temp = ChgSckTmpM_GetSampleVoltage(i);
        pMsgContext->resData[length++] = (uint8)(temp >> 8);
        pMsgContext->resData[length++] = (uint8)(temp);
    }

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0EB0(Dcm_MsgContextType *pMsgContext) {
    Diagnosis_ItemType i;
    uint16 length = DCM_INDEX_2;

    for (i = DIAGNOSIS_ITEM_CHGSCKTMP_START; i <= DIAGNOSIS_ITEM_CHGSCKTMP_STOP; ++i) {
        pMsgContext->resData[length++] = (uint8)Diagnosis_GetLevel(i);
    }

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0ED0(Dcm_MsgContextType *pMsgContext) {
    uint16 temp, length = DCM_INDEX_2;

    temp = ChargerConnectM_GetCCxResistanceStatus(CHARGECONNECTM_ADC_CC_CHANNEL);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);
    temp = ChargerConnectM_GetCCxVoltageStatus(CHARGECONNECTM_ADC_CC_CHANNEL);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0ED1(Dcm_MsgContextType *pMsgContext) {
    uint16 temp, length = DCM_INDEX_2;

    temp = ChargerConnectM_GetCCxResistanceStatus(CHARGECONNECTM_ADC_CC2_CHANNEL);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);
    temp = ChargerConnectM_GetCCxVoltageStatus(CHARGECONNECTM_ADC_CC2_CHANNEL);
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0ED2(Dcm_MsgContextType *pMsgContext) {
    uint16 temp, length = DCM_INDEX_2;

    temp = CP_GetFrequence();
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);
    temp = CP_GetDuty();
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0ED5(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    pMsgContext->resData[length++] = ChargeConnectM_GetS2();

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0EF0(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 length, index = DCM_INDEX_2;

    length = DIGITALINPUT_BCU_SW_NUM + DIGITALINPUT_SINGLE_BMU_SW_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum; /*lint !e835 !e845 */
    for (i = 0U; i < length; ++i) {
        pMsgContext->resData[index++] = (uint8)DigitalInput_GetSwitchState(i);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0F10(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 length, index = DCM_INDEX_2;

#if DIGITALINPUT_SINGLE_BMU_DIN_NUM != 1U
    length = DIGITALINPUT_BCU_DIN_NUM + DIGITALINPUT_SINGLE_BMU_DIN_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum;
#else
    length = DIGITALINPUT_BCU_DIN_NUM + (uint16)SystemConnection_ConfigInfo.SlaveNum;
#endif
    for (i = 0U; i < length; ++i) {
        pMsgContext->resData[index++] = DigitalInput_GetDinLevel(i);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0F11(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    pMsgContext->resData[length++] = 0U;
    pMsgContext->resData[length++] = 0U;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0F12(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    pMsgContext->resData[length++] = 0U;
    pMsgContext->resData[length++] = 0U;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0F30(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 temp, length, index = DCM_INDEX_2;
#if ANALOGINPUT_SINGLE_BMU_CHANNEL_NUM != 1U
    length = ANALOGINPUT_BCU_CHANNEL_NUM + ANALOGINPUT_SINGLE_BMU_CHANNEL_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum;
#else
    length = ANALOGINPUT_BCU_CHANNEL_NUM + (uint16)SystemConnection_ConfigInfo.SlaveNum;
#endif
    for (i = 0U; i < length; ++i) {
        temp = AnalogInput_Get(i);
        pMsgContext->resData[index++] = (uint8)(temp >> 8);
        pMsgContext->resData[index++] = (uint8)(temp);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0F50(Dcm_MsgContextType *pMsgContext) {
    uint8 length = DCM_INDEX_2;

    pMsgContext->resData[length++] = RuntimeM_GetWakeSignal();

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x0F60(Dcm_MsgContextType *pMsgContext) {
    uint16 temp, length = DCM_INDEX_2;

    pMsgContext->resData[length++] = HardWareIO_GetVersion();
    temp = (uint16)AppInfoTag.CompatibleHW;
    pMsgContext->resData[length++] = (uint8)(temp >> 8);
    pMsgContext->resData[length++] = (uint8)(temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x1300(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    const struct NandInfoType *info = StorageM_GetChipInfo(STORAGEM_FULLCHIP_ID);
    uint32 id = 0U;
    if (info) {
        id = info->id;
    }
    WRITE_BT_UINT32(pMsgContext->resData, length, id);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x1301(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint32 first = 0xFFFFFFFFU;
    uint32 last = 0xFFFFFFFFU;
    const struct NandInfoType *info = StorageM_GetChipInfo(STORAGEM_RECORD_ID);
    if (info) {
        uint32 base = StorageM_GetPartitionFirstSector(STORAGEM_RECORD_ID);
        first = base + StorageRecord_GetSectorIndex(&StorageRecordObjectRead);
        last = base + StorageRecord_GetSectorIndex(&StorageRecordObject);
    }
    WRITE_BT_UINT32(pMsgContext->resData, length, first);
    WRITE_BT_UINT32(pMsgContext->resData, length, last);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x1305(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    const struct NandInfoType *info = StorageM_GetChipInfo(STORAGEM_FULLCHIP_ID);

    pMsgContext->resData[length++] = 0U;
    pMsgContext->resData[length++] = (StorageM_GetInitFlag() == 0) && info ? 0U : 1U;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x1600(Dcm_MsgContextType *pMsgContext) {
    uint16 i, volt, index = DCM_INDEX_2, length;

    length = HWDIAGNOSIS_BCU_VOLT_MAX + HWDIAGNOSIS_SINGLE_BMU_VOLT_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum;
    for (i = 0U; i < length; ++i) {
        volt = HWDiagnosis_GetBoardVoltage(i);
        pMsgContext->resData[index++] = (uint8)(volt >> 8);
        pMsgContext->resData[index++] = (uint8)volt;
    }

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x1620(Dcm_MsgContextType *pMsgContext) {
    uint16 offset, i, length;
#if HWDIAGNOSIS_SINGLE_BMU_TEMP_NUM != 1U
    length = HWDIAGNOSIS_BCU_TEMP_MAX + HWDIAGNOSIS_SINGLE_BMU_TEMP_NUM * (uint16)SystemConnection_ConfigInfo.SlaveNum;
#else
    length = HWDIAGNOSIS_BCU_TEMP_MAX + (uint16)SystemConnection_ConfigInfo.SlaveNum;
#endif

    offset = DCM_INDEX_2;
    for (i = 0U; i < length; ++i) {
        pMsgContext->resData[offset++] = HWDiagnosis_GetBoardTemperature(i);
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += offset;
    pMsgContext->resDataLen += offset;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2800(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    WRITE_BT_UINT16(pMsgContext->resData, length, Soc_Get());
    WRITE_BT_UINT16(pMsgContext->resData, length, Soh_Get());
    WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcu100mvTotalVoltage());
    WRITE_BT_UINT16(pMsgContext->resData, length, CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN));
    WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcuDeltaVoltage());
    WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuDeltaTemperature());
    WRITE_BT_UINT8(pMsgContext->resData, length, RuntimeM_GetMode());

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2801(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    uint32 temp;

    (void)DatetimeM_GetDatetime(&temp);
    WRITE_BT_UINT32(pMsgContext->resData, length, temp);
    WRITE_BT_UINT32(pMsgContext->resData, length, DIVISION(OSTimeGet(), 1000U));
    temp = Statistic_GetCumuChgTime();
    WRITE_BT_UINT32(pMsgContext->resData, length, temp);
    temp = Statistic_GetCumuDchgTime();
    WRITE_BT_UINT32(pMsgContext->resData, length, temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2802(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    WRITE_BT_UINT8(pMsgContext->resData, length, SocDiagCalib_GetFullReason());
    WRITE_BT_UINT8(pMsgContext->resData, length, SocDiagCalib_GetEmptyReason());

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2803(Dcm_MsgContextType *pMsgContext) {
    uint8 temp;
    Diagnosis_ItemType value;
    uint16 length = DCM_INDEX_2;

    value = DischargeM_GetStartDiagFault();
    WRITE_BT_UINT8(pMsgContext->resData, length, value);
    value = DischargeM_GetDiagFaultFlag();
    WRITE_BT_UINT8(pMsgContext->resData, length, value);
    value = DischargeM_GetDiagFaultAction();
    WRITE_BT_UINT8(pMsgContext->resData, length, value);
    temp = (uint8)DischargeM_GetOthersFault();
    WRITE_BT_UINT8(pMsgContext->resData, length, temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2804(Dcm_MsgContextType *pMsgContext) {
    uint8 temp;
    Diagnosis_ItemType value;
    uint16 length = DCM_INDEX_2;

    value = ChargeM_GetStartDiagFault();
    WRITE_BT_UINT8(pMsgContext->resData, length, value);
    value = ChargeM_GetDiagFaultFlag();
    WRITE_BT_UINT8(pMsgContext->resData, length, value);
    value = ChargeM_GetDiagFaultAction();
    WRITE_BT_UINT8(pMsgContext->resData, length, value);
    temp = (uint8)ChargeM_GetChargerGBReadyFault();
    WRITE_BT_UINT8(pMsgContext->resData, length, temp);
    temp = (uint8)ChargeM_GetOthersFault();
    WRITE_BT_UINT8(pMsgContext->resData, length, temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2810(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    ParameterM_DataType capL, capH;
    uint32 cumuCap = 0U;

    WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcuValidVoltageNum());
    WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcuValidTemperatureNum());
    WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcuAverageVoltage());
    WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuAverageTemperature());
    WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcuDeltaVoltage());
    WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuDeltaTemperature());
    WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcuBatteryDischargeCount());

    if (E_OK == ParameterM_EeepRead(PARAMETERM_EEEP_CUMULATIVE_CHG_CAP_L_INDEX, &capL)) {
        if (E_OK == ParameterM_EeepRead(PARAMETERM_EEEP_CUMULATIVE_CHG_CAP_H_INDEX, &capH)) {
            cumuCap = ((uint32)capH << 16) + capL;
        }
    }
    WRITE_BT_UINT32(pMsgContext->resData, length, cumuCap);
    cumuCap = 0U;
    if (E_OK == ParameterM_EeepRead(PARAMETERM_EEEP_CUMULATIVE_DCHG_CAP_L_INDEX, &capL)) {
        if (E_OK == ParameterM_EeepRead(PARAMETERM_EEEP_CUMULATIVE_DCHG_CAP_H_INDEX, &capH)) {
            cumuCap = ((uint32)capH << 16) + capL;
        }
    }
    WRITE_BT_UINT32(pMsgContext->resData, length, cumuCap);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2820(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 length = DCM_INDEX_2;

    for (i = 0U; i < STATISTIC_VOLTAGE_NUM; i++) {
        WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcuHv(i));
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuHvSlaveNum(i));
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuHvIndex(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2828(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 length = DCM_INDEX_2;

    for (i = 0U; i < STATISTIC_VOLTAGE_NUM; i++) {
        WRITE_BT_UINT16(pMsgContext->resData, length, Statistic_GetBcuLv(i));
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuLvSlaveNum(i));
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuLvIndex(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2830(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 length = DCM_INDEX_2;

    for (i = 0U; i < STATISTIC_VOLTAGE_NUM; i++) {
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuHt(i));
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuHtSlaveNum(i));
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuHtIndex(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2838(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 length = DCM_INDEX_2;

    for (i = 0U; i < STATISTIC_VOLTAGE_NUM; i++) {
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuLt(i));
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuLtSlaveNum(i));
        WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetBcuLtIndex(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2850(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 length = DCM_INDEX_4, count = 0U, pos;
    Diagnosis_ItemType item;
    for (i = 0U; i < DIAGNOSIS_ITEM_DEFAULT_NUM; ) {
        item = Diagnosis_IndexToItem(i);
        item = Diagnosis_GetNextAlarmingItem(item);
        if (item != DIAGNOSIS_ITEM_INVALID_INDEX) {
            count += 1U;
            WRITE_BT_UINT8(pMsgContext->resData, length, item);
            WRITE_BT_UINT8(pMsgContext->resData, length, Diagnosis_GetLevel(item));
        } else {
            break;
        }
        i = Diagnosis_ItemToIndex(item) + 1U;
    }
    pos = DCM_INDEX_2;
    WRITE_BT_UINT16(pMsgContext->resData, pos, count);
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2851(Dcm_MsgContextType *pMsgContext) {
    Diagnosis_ItemType i;
    uint16 length = DCM_INDEX_2;

    for (i = DIAGNOSIS_ITEM_VOLT_START; i <= DIAGNOSIS_ITEM_VOLT_STOP; i++) {
        WRITE_BT_UINT8(pMsgContext->resData, length, Diagnosis_GetLevel(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2852(Dcm_MsgContextType *pMsgContext) {
    Diagnosis_ItemType i;
    uint16 length = DCM_INDEX_2;

    for (i = DIAGNOSIS_ITEM_TEMPERATURE_START; i <= DIAGNOSIS_ITEM_TEMPERATURE_STOP; i++) {
        WRITE_BT_UINT8(pMsgContext->resData, length, Diagnosis_GetLevel(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2853(Dcm_MsgContextType *pMsgContext) {
    Diagnosis_ItemType i;
    uint16 length = DCM_INDEX_2;

    for (i = DIAGNOSIS_ITEM_CURRENT_START; i <= DIAGNOSIS_ITEM_CURRENT_STOP; i++) {
        WRITE_BT_UINT8(pMsgContext->resData, length, Diagnosis_GetLevel(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2854(Dcm_MsgContextType *pMsgContext) {
    Diagnosis_ItemType i;
    uint16 length = DCM_INDEX_2;

    for (i = DIAGNOSIS_ITEM_SOC_START; i <= DIAGNOSIS_ITEM_SOC_STOP; i++) {
        WRITE_BT_UINT8(pMsgContext->resData, length, Diagnosis_GetLevel(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2855(Dcm_MsgContextType *pMsgContext) {
    Diagnosis_ItemType i;
    uint16 length = DCM_INDEX_2;

    for (i = DIAGNOSIS_ITEM_LINE_START; i <= DIAGNOSIS_ITEM_LINE_STOP; i++) {
        WRITE_BT_UINT8(pMsgContext->resData, length, Diagnosis_GetLevel(i));
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2856(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    WRITE_BT_UINT8(pMsgContext->resData, length, Diagnosis_GetLevel(DIAGNOSIS_ITEM_INTER_COMM));

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x2857(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    WRITE_BT_UINT8(pMsgContext->resData, length, Diagnosis_GetLevel(DIAGNOSIS_ITEM_LEAK));

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3002(Dcm_MsgContextType *pMsgContext) {
    uint16 i, index = DCM_INDEX_2, length = SystemConnection_ConfigInfo.SlaveNum;

    if (gDcmDsdSubService_22[ReadHandle_0x3002].DcmDspDataSize != DCM_DID_SIZE_UNUSED) {
        length = gDcmDsdSubService_22[ReadHandle_0x3002].DcmDspDataSize;
        if (length > SystemConnection_ConfigInfo.SlaveNum) {
            length = SystemConnection_ConfigInfo.SlaveNum;
        }
    }
    for (i = 0U; i < length; i++) {
        pMsgContext->resData[index++] = (uint8)SystemConnection_SlaveTypesTable[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3010(Dcm_MsgContextType *pMsgContext) {
    uint16 temp = 0U;
    uint16 index = DCM_INDEX_2, SlaveNum = SystemConnection_ConfigInfo.SlaveNum;

    if (SystemConnection_ConfigInfo.BcuIsAllInOne) {
        if (SlaveNum > 1U) {
            temp = 2U;
        } else {
            temp = 1U;
        }
    }
    WRITE_BT_UINT8(pMsgContext->resData, index, temp);
    WRITE_BT_UINT8(pMsgContext->resData, index, SlaveNum);
    temp = Soc_GetChgEfficiency();
    WRITE_BT_UINT16(pMsgContext->resData, index, temp);
    temp = Soc_GetDchgEfficiency();
    WRITE_BT_UINT16(pMsgContext->resData, index, temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3021(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_INTER_COMM),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3022(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_INTER_COMM),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);

    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3030(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_HTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3031(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_HTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3032(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_HTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3033(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_HTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3034(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_DTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3035(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_DTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3036(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_DTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3037(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_DTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3040(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_LTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3041(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_LTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3042(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_LTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3043(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_LTV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3050(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DC_CHG_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3051(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DC_CHG_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3052(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_AC_CHG_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3053(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_AC_CHG_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3054(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_FB_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3055(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_FB_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3056(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3057(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3058(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_SP_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3059(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_SP_OC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x305A(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_CUR_FAULT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x305B(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_CUR_FAULT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3070(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_LEAK),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3071(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_LEAK),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3080(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_HV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_Read0x3081
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Read0x3081(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_HV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3082(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_HV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3083(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_HV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3090(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_LV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3091(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_LV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3092(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_LV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3093(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_LV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30A0(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_DV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30A1(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_DV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30A2(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_DV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30A3(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_DV),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30B0(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_HT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30B1(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_HT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30B2(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_HT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30B3(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_HT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30C0(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_LT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30C1(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_LT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30C2(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_LT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30C3(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_LT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30D0(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_DT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30D1(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_CHG_DT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30D2(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_DT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30D3(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_DCHG_DT),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30E0(Dcm_MsgContextType *pMsgContext) {
    uint16 index = DCM_INDEX_2, temp = 0U;

    (void)ParameterM_EeepRead(PARAMETERM_EEEP_TOTAL_CAP_INDEX, &temp);
    WRITE_BT_UINT16(pMsgContext->resData, index, temp);
    temp = Soc_GetHighPrecisionLeftCap();
    WRITE_BT_UINT16(pMsgContext->resData, index, temp);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30E1(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_CALIB_PARA_ADDR(SocDiagPara.CapHighCalibAverageVolt),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30E2(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_CALIB_PARA_ADDR(SocDiagPara.CapHighCalibAverageVolt),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30E3(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_HSOC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30E4(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_HSOC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30E5(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_LSOC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30E6(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_LSOC),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30F0(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_VOLT_LINE),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30F1(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_VOLT_LINE),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30F2(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_TEMP_LINE),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x30F3(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Diagnosis_ParaType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(DIAGNOSIS_ITEM_TEMP_LINE),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3140(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(TemperatureM_HeatConfigType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(TemperatureMPara.chgHeatPara.temperatureOn),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3141(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(TemperatureM_HeatConfigType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_APP_PFLASH_CALIB_PARA_ADDR(TemperatureMPara.chgHeatPara),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3142(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(TemperatureM_HeatConfigType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(TemperatureMPara.dchgHeatPara.temperatureOn),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3143(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(TemperatureM_HeatConfigType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_APP_PFLASH_CALIB_PARA_ADDR(TemperatureMPara.dchgHeatPara),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3150(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(TemperatureM_HeatConfigType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(TemperatureMPara.chgRefrigerationPara.temperatureOn),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3151(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(TemperatureM_HeatConfigType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_APP_PFLASH_CALIB_PARA_ADDR(TemperatureMPara.chgRefrigerationPara),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3152(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(TemperatureM_HeatConfigType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(TemperatureMPara.dchgRefrigerationPara.temperatureOn),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x3153(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(TemperatureM_HeatConfigType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_APP_PFLASH_CALIB_PARA_ADDR(TemperatureMPara.dchgRefrigerationPara),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x4000(Dcm_MsgContextType *pMsgContext) {
    boolean flag = FALSE;
    uint16 length = DCM_INDEX_2;

    if (ChargeConnectM_GetDCACConnectType() == CHARGE_TYPE_NONE)
    {
        if (ChargeConnectM_GetDC2ConnectType() != CHARGE_TYPE_NONE)
        {
            flag = TRUE;
            ExternCanComm_GetChargerStatus((ExternCanComm_ChargerStatusType *)(&pMsgContext->resData[length]));
            length += sizeof(ExternCanComm_ChargerStatusType);
        }
    }
    if (!flag)
    {
        ChargerComm_GetChargerStatus((ChargerComm_ChargerStatusType *)(&pMsgContext->resData[length]));
        length += sizeof(ChargerComm_ChargerStatusType);
    }

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x4010(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    WRITE_BT_UINT8(pMsgContext->resData, length, ChargeM_ConfigInfo.AC_Para.enable);
    WRITE_BT_UINT8(pMsgContext->resData, length, ChargerComm_ConfigInfo.AC_Protocol);
    WRITE_BT_UINT8(pMsgContext->resData, length, ChargeConnectM_ConfigInfo.AC_Para.type);
    WRITE_BT_UINT16(pMsgContext->resData, length, ChargeM_ConfigInfo.AC_Para.chargeTimeMax);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x4011(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Charge_CalibConfigInfoType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_CALIB_PARA_ADDR(ChargePara.AC_Para.chargeTotalVoltMax),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x4012(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Charge_CalibConfigInfoType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_CALIB_PARA_ADDR(ChargePara.AC_Para.chargeTotalVoltMax),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x4018(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;

    WRITE_BT_UINT8(pMsgContext->resData, length, ChargeM_ConfigInfo.DC_Para.enable);
    WRITE_BT_UINT8(pMsgContext->resData, length, ChargerComm_ConfigInfo.DC_Protocol);
    WRITE_BT_UINT8(pMsgContext->resData, length, ChargeConnectM_ConfigInfo.DC_Para.type);
    WRITE_BT_UINT16(pMsgContext->resData, length, ChargeM_ConfigInfo.DC_Para.chargeTimeMax);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x4019(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Charge_CalibConfigInfoType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_DFLASH_CALIB_PARA_ADDR(ChargePara.DC_Para.chargeTotalVoltMax),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0x401A(Dcm_MsgContextType *pMsgContext) {
    uint16 length;

    length = sizeof(Charge_CalibConfigInfoType);
    (void)ParameterM_CalibRead(PARAMETERM_GET_PFLASH_CALIB_PARA_ADDR(ChargePara.DC_Para.chargeTotalVoltMax),
                               &pMsgContext->resData[DCM_INDEX_2],
                               length);
    length += DCM_INDEX_2;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xA500(Dcm_MsgContextType *pMsgContext) {
    uint16 length = DCM_INDEX_2;
    pMsgContext->resData[length++] = AppInfoTag.FWAddrSpace;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += length;
    pMsgContext->resDataLen += length;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xA503(Dcm_MsgContextType *pMsgContext) {
    uint8 i, index = DCM_INDEX_2;

    for (i = 0U; AppInfoTag.FWName[i] != 0; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.FWName[i];
    }
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xA50A(Dcm_MsgContextType *pMsgContext) {
    uint8 i, index = DCM_INDEX_2;

    for (i = 0U; AppInfoTag.BuildTime[i] != 0; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.BuildTime[i];
    }
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xA50B(Dcm_MsgContextType *pMsgContext) {
    uint8 i, index = DCM_INDEX_2;

    for (i = 0U; AppInfoTag.FWName[i] != 0; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.FWName[i];
    }
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xA50F(Dcm_MsgContextType *pMsgContext) {
    uint8 i, index = DCM_INDEX_2;

    for (i = 0U; AppInfoTag.ReleaseName[i] != 0; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.ReleaseName[i];
    }
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xDFEF(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xDFEF].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xDFEF[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF101(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF101].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF101[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF110(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF110].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF110[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF112(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF112].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF112[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF113(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF113].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF113[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF180(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF180].DcmDspDataSize; i++) {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[index++] = DATA_0xF180[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF181(Dcm_MsgContextType *pMsgContext) {
    uint8 i, index = DCM_INDEX_2;

    for (i = 0U; AppInfoTag.FWID[i] != 0; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.FWID[i];
    }
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF182(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF182].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.ConfigCommitId[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF184(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;

    for (i = 0U; AppInfoTag.BurnID[i] != 0; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.BurnID[i];
    }
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF185(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF185].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = 0U;
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF186(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF186].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF186[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF187(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF187[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF189(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF189].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF189[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF18A(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; AppInfoTag.SupplierName[i] != 0; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.SupplierName[i];
    }
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF18B(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF18B].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = 0U;
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF18C(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF18C].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF18C[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF18E(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF18E].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF18E[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF190(Dcm_MsgContextType *pMsgContext) {
    uint8 i, size;
    uint16 index = DCM_INDEX_2, vin;
    size = (uint8)((gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize + 1U) / 2U);
    for (i = 0U; i < size; i++) {
        if (i < 9U) {
            if (E_OK != ParameterM_EeepRead((ParameterM_EeepParaIndexType)((uint8)PARAMETERM_EEEP_VIN1_INDEX + i), &vin)) {
                vin = 0U;
            }
        } else {
            vin = 0U;
        }
        if ((i == size - 1U) && (size % 2U)) {
            pMsgContext->resData[index++] = (uint8)vin;
        } else {
            pMsgContext->resData[index++] = (uint8)(vin >> 8);
            pMsgContext->resData[index++] = (uint8)vin;
        }
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF192(Dcm_MsgContextType *pMsgContext) {
    uint16 index = DCM_INDEX_2;
    uint8 length = (uint8)gDcmDsdSubService_22[ReadHandle_0xF192].DcmDspDataSize;
    HardwareSn_Get(&pMsgContext->resData[index]);
    if (length > AT24_HW_SERIAL_NUMBER_SIZE) {
        length = AT24_HW_SERIAL_NUMBER_SIZE;
    }
    index += length;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF193(Dcm_MsgContextType *pMsgContext) {
    uint8 index = DCM_INDEX_2;

    pMsgContext->resData[index++] = HardWareIO_GetVersion() + 0x30U;
    pMsgContext->resData[index++] = 0U;

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF194(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF194].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.SourceCommitId[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF195(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; AppInfoTag.FWVersion[i] != 0; i++) {
        pMsgContext->resData[index++] = (uint8)AppInfoTag.FWVersion[i];
    }
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}

void App_Read0xF197(Dcm_MsgContextType *pMsgContext) {
    uint8 index = 2U;

    pMsgContext->resData[index++] = (uint8)('B');
    pMsgContext->resData[index++] = (uint8)('M');
    pMsgContext->resData[index++] = (uint8)('S');
    pMsgContext->resData[index++] = 0U;
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_Read0xF198
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Read0xF198(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF198].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF198[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_Read0xF199
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Read0xF199(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF199].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF199[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_Read0xF19D
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Read0xF19D(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF19D].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF19D[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_Read0xF19E
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Read0xF19E(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 index = DCM_INDEX_2;
    for (i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF19E].DcmDspDataSize; i++) {
        pMsgContext->resData[index++] = DATA_0xF19E[i];
    }
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
#else
    pMsgContext->resData += index;
    pMsgContext->resDataLen += index;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
#endif
#endif
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#endif

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
#endif

/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Write0x0E11
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0x0E11(Dcm_MsgContextType *pMsgContext) {
    uint8 i, Okflag = 1U;
    Std_ReturnType res1, res2;
    uint16 temp, index = DCM_INDEX_3;

    for (i = 0U; i < (uint8)HV_CHANNEL_MAX; i++) {
        temp = READ_BT_UINT16(pMsgContext->reqData, index);
        res1 = HV_SetGainErr((HV_ChannelType)i, temp);
        res2 = ParameterM_EeepWrite((ParameterM_EeepParaIndexType)(i + (uint8)PARAMETERM_EEEP_HVBPOS_GAIN_ERROR_INDEX), temp);
        if (res1 != E_OK || res2 != E_OK) {
            Okflag = 0U;
            break;
        }
    }
    if (Okflag == 1U) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
/******************************************************************************
* Name         :App_Write0x0E61
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0x0E61(Dcm_MsgContextType *pMsgContext) {
    uint16 temp, index = DCM_INDEX_3;
    Std_ReturnType res1, res2;

    temp = READ_BT_UINT16(pMsgContext->reqData, index);
    res1 = Shunt_SetGainErr(temp);
    res2 = ParameterM_EeepWrite(PARAMETERM_EEEP_SHUNT_GAIN_ERROR_INDEX, temp);
    if (res1 == E_OK && res2 == E_OK) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
/******************************************************************************
* Name         :App_Write0x2801
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0x2801(Dcm_MsgContextType *pMsgContext) {
    uint16 index = DCM_INDEX_3;
    uint32 time;

    if (pMsgContext->reqDataLen >= 7U) {
        time = READ_BT_UINT32(pMsgContext->reqData, index);
        DatetimeM_SetDatetime(time);
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0x----
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0x3021(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_INTER_COMM),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3021].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3030(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_HTV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3030].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3032(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_HTV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3032].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3034(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_DTV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3034].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3036(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_DTV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3036].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3040(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_LTV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3040].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3042(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_LTV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3042].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3050(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DC_CHG_OC),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3050].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3052(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_AC_CHG_OC),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3052].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3054(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_FB_OC),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3054].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3056(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_OC),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3056].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3058(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_SP_OC),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3058].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x305A(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_CUR_FAULT),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x305A].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3070(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_LEAK),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3070].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3080(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_HV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3080].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3082(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_HV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3082].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3090(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_LV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3090].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3092(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_LV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3092].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30A0(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_DV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30A0].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30A2(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_DV),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30A2].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30B0(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_HT),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30B0].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30B2(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_HT),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30B2].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30C0(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_LT),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30C0].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30C2(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_LT),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30C2].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30D0(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_CHG_DT),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30D0].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30D2(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_DCHG_DT),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30D2].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30E0(Dcm_MsgContextType *pMsgContext) {
    Std_ReturnType res;
    uint16 index = 3U;
    if (SoxUseModel){
        res = Soc_ModelConfigTotalCap(READ_BT_UINT16(pMsgContext->reqData, index));
        if (res == E_OK) {
            res = Soc_ModelConfigLeftCap(READ_BT_UINT16(pMsgContext->reqData, index));
        }
    }
    else{
        res = Soc_ConfigTotalCap(READ_BT_UINT16(pMsgContext->reqData, index));
        if (res == E_OK) {
            res = Soc_ConfigLeftCap(READ_BT_UINT16(pMsgContext->reqData, index));
        }
    }
    if (res == E_OK) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30E1(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_CALIB_PARA_ADDR(SocDiagPara.CapHighCalibAverageVolt),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30E1].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30E3(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_HSOC),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30E3].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30E5(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_LSOC),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30E5].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30F0(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_VOLT_LINE),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30F0].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x30F2(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(
                                          DIAGNOSIS_ITEM_TEMP_LINE),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x30F2].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3140(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(
                                          TemperatureMPara.chgHeatPara),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3140].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3142(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(
                                          TemperatureMPara.dchgHeatPara),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3142].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3150(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(
                                          TemperatureMPara.chgRefrigerationPara),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3150].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x3152(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(
                                          TemperatureMPara.dchgRefrigerationPara),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x3152].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x4011(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_CALIB_PARA_ADDR(ChargePara.AC_Para.chargeTotalVoltMax),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x4011].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
void App_Write0x4019(Dcm_MsgContextType *pMsgContext) {
    if (E_OK == ParameterM_CalibWrite(PARAMETERM_GET_DFLASH_CALIB_PARA_ADDR(ChargePara.DC_Para.chargeTotalVoltMax),
                                      &pMsgContext->reqData[3],
                                      gDcmDsdSubService_2E[WriteHandle_0x4019].DcmDspDataSize)) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}

/******************************************************************************
* Name         :App_Write0xDFEF
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xDFEF(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    for (i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xDFEF].DcmDspDataSize; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xDFEF[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF101
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xF101(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    for (i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF101].DcmDspDataSize; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF101[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF110
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xF110(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    for (i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF110].DcmDspDataSize; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF110[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF112
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xF112(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    for (i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF112].DcmDspDataSize; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF112[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF190
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xF190(Dcm_MsgContextType *pMsgContext) {
    uint8 i, size;
    uint16 index = 3U, vin;
    size = (uint8)((gDcmDsdSubService_2E[WriteHandle_0xF190].DcmDspDataSize + 1U) / 2U);
    if (size > 9U) {
        size = 9U;
    }
    for (i = 0U; i < size; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        if ((i == size - 1U) && (size % 2U)) {
            vin = READ_BT_UINT8(pMsgContext->reqData, index);
        } else {
            vin = READ_BT_UINT16(pMsgContext->reqData, index);
        }
        if (E_OK != ParameterM_EeepWrite((ParameterM_EeepParaIndexType)((uint8)PARAMETERM_EEEP_VIN1_INDEX + i), vin)) {
            break;
        }
    }
    if (i == size) {
        gMsgContextType.resDataLen = 3U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
    }
}
/******************************************************************************
* Name         :App_Write0xF197
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xF197(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    for (i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF197].DcmDspDataSize; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF197[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF198
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xF198(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    for (i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF198].DcmDspDataSize; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF198[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF199
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xF199(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    for (i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF199].DcmDspDataSize; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF199[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF19D
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_Write0xF19D(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    for (i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF19D].DcmDspDataSize; i++) {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF19D[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ReturnControlToEcu0489
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_ReturnControlToEcu0x0489 (Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    /* Add your code here */
    for (i = 0U; i < BCU_SLAVE_NUM_MAX; i++) {
        BalanceM_SlaveBalanceForceCancle(i);
    }
    /* Set response legnth */
    pMsgContext->resDataLen = 4U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0489
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_ShortTermAdjustment0x0489 (Dcm_MsgContextType *pMsgContext) {
    uint8 i, length;
    /* Add your code here */
    length = (uint8)(pMsgContext->reqDataLen - 4U);
    BalanceM_SlaveBalanceForce(pMsgContext->reqData[DCM_INDEX_4], &pMsgContext->reqData[DCM_INDEX_5], length - 1U);
    /* If response data needed, set response data */
    for (i = 0U; i < length; i++) {
        pMsgContext->resData[DCM_INDEX_4 + i] = pMsgContext->reqData[DCM_INDEX_4 + i];
    }
    length += DCM_INDEX_4;
    /* Set response length */
    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0918
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_ReturnControlToEcu0x0918 (Dcm_MsgContextType *pMsgContext) {
    HLSS_ChannelType i;
    /* Add your code here */
    for (i = 0U; i < HLSS_DRIVER_NUM; ++i) {
        HLSS_Force(i, HLSS_FORCE_NONE);
    }
    /* Set response legnth */
    pMsgContext->resDataLen = 4U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0918
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_ShortTermAdjustment0x0918 (Dcm_MsgContextType *pMsgContext) {
    /* Add your code here */
    HLSS_Force(pMsgContext->reqData[DCM_INDEX_4], pMsgContext->reqData[DCM_INDEX_5]);
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = pMsgContext->reqData[DCM_INDEX_4];
    pMsgContext->resData[DCM_INDEX_5] = pMsgContext->reqData[DCM_INDEX_5];
    /* Set response legnth */
    pMsgContext->resDataLen = 6U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0968
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_ReturnControlToEcu0x0968 (Dcm_MsgContextType *pMsgContext) {
    /* Add your code here */
    (void)EL_ForceAsync(0U, EL_FORCE_OFF);
    /* Set response legnth */
    pMsgContext->resDataLen = 4U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0968
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_ShortTermAdjustment0x0968 (Dcm_MsgContextType *pMsgContext) {
    /* Add your code here */
    if (pMsgContext->reqData[DCM_INDEX_5] == 2U) {
        (void)EL_ForceAsync(0U, EL_FORCE_LOCK);
    } else { /* if (pMsgContext->reqData[DCM_INDEX_5] == 1)*/
        (void)EL_ForceAsync(0U, EL_FORCE_UNLOCK);
    }
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = pMsgContext->reqData[DCM_INDEX_4];
    pMsgContext->resData[DCM_INDEX_5] = pMsgContext->reqData[DCM_INDEX_5];
    /* Set response legnth */
    pMsgContext->resDataLen = 6U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x19 */

#if(DCM_SERVICE_19_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ReportNumberOfDTCByStatusMask
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :Report number of DTC by status mask.
*
******************************************************************************/
void App_Fault_Memory_Read_Number(Dcm_MsgContextType *pMsgContext) {
    uint8 i;
    uint16 counter = 0U;
    uint8  DtcStatus_Temp;
    DtcStatus_Temp = pMsgContext->reqData[DCM_INDEX_2];

    for (i = 0U; i < NUM_OF_DTC; i++) {
        if ((DtcStatus_Temp & DTCStatus[i]) != 0U) {
            counter++;
        } else {
        }
    }

    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    /* Change below data if necessary */
    /* 0x00 ISO15031-6Format,0x01 ISO14229-1Format,0x02 J1939 Format */
    pMsgContext->resData[DCM_INDEX_3] = 0x00U;
    pMsgContext->resData[DCM_INDEX_4] = (uint8)(counter >> 8U);
    pMsgContext->resData[DCM_INDEX_5] = (uint8)(counter);
    /* Always equals 6, don't change it */
    pMsgContext->resDataLen = 6U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportDTCByStatusMask
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :Report DTC by status mask.
*
******************************************************************************/
void App_Fault_Memory_Read_identified_errors(Dcm_MsgContextType *pMsgContext) {
    uint8  i;
    uint16 index = DCM_INDEX_3;
    uint8  DtcStatus_Temp;
    DtcStatus_Temp = pMsgContext->reqData[DCM_INDEX_2];

    for (i = 0U; i < NUM_OF_DTC; i++) {
        if ((DtcStatus_Temp & DTCStatus[i]) != 0U) {
            pMsgContext->resData[index++] = (uint8)(SupportedDTC[i] >> 16U);
            pMsgContext->resData[index++] = (uint8)(SupportedDTC[i] >> 8U);
            pMsgContext->resData[index++] = (uint8)SupportedDTC[i];
            pMsgContext->resData[index++] = DTCStatus[i];
        } else {
        }
    }

    pMsgContext->resData[DCM_INDEX_1] = pMsgContext->reqData[DCM_INDEX_1];
    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    pMsgContext->resDataLen = index;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportDTCSnapshortRecordByDTCNumber
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_Fault_Memory_Read_Snapshot(Dcm_MsgContextType *pMsgContext) {
    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;
    uint8 DTCSnapshotRecordNumber;
    uint8 DTCSnapshotRecordLength = 0U;

    DTCSnapshotRecordNumber = pMsgContext->reqData[DCM_INDEX_5];

    Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3], pMsgContext->reqData[DCM_INDEX_4]);

    /* Check DTC */
    for (i = 0U; i < NUM_OF_DTC; i++) {
        if (Dtc == SupportedDTC[i]) {
            pMsgContext->resData[DCM_INDEX_5] = DTCStatus[i];
            break;
        } else {
            if (i == (NUM_OF_DTC - 1U)) {
                error = 1U;
                DsdInternal_SetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            } else {
                /* Do nothing */
            }
        }
    }

    if (error == 0U) {
        switch (DTCSnapshotRecordNumber) {
        /* Add your code here. Below codes should be changed as Spec */
        case 0xFF: /*return all DTCSnapshotRecordnumber*/
        case 0x01:
            pMsgContext->resData[6] = 0x01U;  /* DTCSnapshotRecordNumber #2 */
            pMsgContext->resData[7] = 0x01U;  /* DTCSnapshotRecordNumberOfIdentifiers #2 */

            /*the first Identifier 0x9abc*/
            pMsgContext->resData[8] = 0x9aU; /*Dataidentifier#1  byte#1(MSB)*/
            pMsgContext->resData[9] = 0xbcU; /*Dataidentifier#1  byte#1(LSB)*/
            pMsgContext->resData[10] = 0x13U;/*SnapshotData#1	 byte#1*/
            pMsgContext->resData[11] = 0x13U;/*SnapshotData#1	 byte#2*/
            pMsgContext->resData[12] = 0x13U;/*SnapshotData#1	 byte#3*/
            /* change below length according to App*/
            /* if the current DTCSnapshotRecordNumber is not available the length should 0 */
            DTCSnapshotRecordLength = 13U;
            break;

        default:
            DsdInternal_SetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            error = 1U;
            break;
        }
    } else {
        /* Do nothing */
    }
    if (error == 0U) {
        DTCSnapshotRecordLength += 8U;
        pMsgContext->resDataLen = DTCSnapshotRecordLength;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_ProcessingDone(pMsgContext);
    }
}

/******************************************************************************
* Name         :App_ReportSupportedDTC
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_Fault_Memory_Read_supported_errors(Dcm_MsgContextType *pMsgContext) {
    uint32 i;

    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    for (i = 0U; i < NUM_OF_DTC; i++) {
        pMsgContext->resData[DCM_INDEX_3 + i * 4U] = (uint8)(SupportedDTC[i] >> 16U);
        pMsgContext->resData[DCM_INDEX_4 + i * 4U] = (uint8)(SupportedDTC[i] >> 8U);
        pMsgContext->resData[DCM_INDEX_5 + i * 4U] = (uint8)(SupportedDTC[i]);
        pMsgContext->resData[DCM_INDEX_6 + i * 4U] = DTCStatus[i];
    }
    pMsgContext->resDataLen = 3U + NUM_OF_DTC * 4U;
    DsdInternal_ProcessingDone(pMsgContext);
}

#endif

/* 0x23 */
#if(DCM_SERVICE_23_ENABLED == STD_ON)
#endif

/* 0x27 */
#if(DCM_SERVICE_27_ENABLED == STD_ON)

static void CalculateKey(uint8 key[4], const uint8 seed[4])  {
    uint8 tmp[4];
    uint16 val;
    uint8 i;

    (void)memset(tmp, 0, sizeof(tmp));
    for (i = 0U; i < 4U; ++i) {
        tmp[i] |= seed[i] & 0x0FU;
        tmp[3U - i] |= seed[i] & 0xF0U;
    }
    val = Crc_CalculateCRC16(tmp, sizeof(tmp), 0x13F8U);
    key[0U] = (uint8)(val);
    key[2U] = (uint8)(val >> 8);


    (void)memset(tmp, 0, sizeof(tmp));
    for (i = 0U; i < 4U; ++i) {
        tmp[i] |= seed[i] & 0x3CU;
        tmp[3U - i] |= seed[i] & 0xC3U;
    }
    val = Crc_CalculateCRC16(tmp, sizeof(tmp), 0x76EDU);
    key[1U] = (uint8)(val);
    key[3U] = (uint8)(val >> 8);
}

/******************************************************************************
* Name         :GetKey
* Called by    :
* Preconditions:
* Parameters   :N/A
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
static void GetKey(uint8 Dcm_SecuirityLevel, uint8 *Key) {
    switch (Dcm_SecuirityLevel) {
    /* Add your code here to get Key according to last seed */
    case DCM_SEC_LEV_L1:
    case DCM_SEC_LEV_L2:
    case DCM_SEC_LEV_L3:
    case DCM_SEC_LEV_L4:
    case DCM_SEC_LEV_L5:
    case DCM_SEC_LEV_L6:
    case DCM_SEC_LEV_L7:
        CalculateKey(Key, MagicSeed);
        break;
    default:
        break;
    }
}

/******************************************************************************
* Name         :App_Request_Seed_L1
* Called by    :Dcm
* Preconditions:Dcm_MsgContextType* pMsgContext
* Parameters   :N/A
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_Request_Seed_L1(Dcm_MsgContextType *pMsgContext) {
    boolean enable = FALSE;
    Dcm_SesCtrlType type;
    RuntimeM_RunModeType mode;

    (void)Dcm_GetSessionType(&type);
    mode = RuntimeM_GetMode();
    if (type == DCM_PROGRAMMING_SESSION && mode == RUNTIMEM_RUNMODE_DTU) {
        enable = TRUE;
    } else if (type == DCM_EXTENDED_DIAGNOSTIC_SESSION && mode == RUNTIMEM_RUNMODE_DATA) {
        enable = TRUE;
    } else if (type == DCM_EXTENDED_DIAGNOSTIC_SESSION && mode == RUNTIMEM_RUNMODE_CALIBRATE) {
        enable = TRUE;
    } else {

    }
    if (enable) {
        uint8 i;
        uint32 seed = OSTimeGet();
        seed += McuE_GetRandom();

        MagicSeed[0] = (uint8)(seed >> 16);
        MagicSeed[1] = (uint8)(seed >> 24);
        MagicSeed[2] = (uint8)(seed);
        MagicSeed[3] = (uint8)(seed >> 8);


        LOG(D, f("Seed: %02X %02X %02X %02X",
                 MagicSeed[0], MagicSeed[1], MagicSeed[2], MagicSeed[3]));
        pMsgContext->resData[DCM_INDEX_1] = pMsgContext->reqData[DCM_INDEX_1];
        for (i = 0U; i < gDcmDspSecurityRow[Request_Seed_L1_Hanle].DcmDspSecuritySeedSize; i++) {
            /* add your code here, generate App Seed */
            gMsgContextType.resData[2U + i] = MagicSeed[i];
        }
        pMsgContext->resDataLen = gDcmDspSecurityRow[Request_Seed_L1_Hanle].DcmDspSecuritySeedSize + 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
    }
}

/******************************************************************************
* Name         :App_Send_Key_L1
* Called by    :Dcm
* Preconditions:Dcm_MsgContextType* pMsgContext
* Parameters   :N/A
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_Send_Key_L1(Dcm_MsgContextType *pMsgContext) {
    // uint8 temp = 0U;
    uint8 key[4];

    /* Add your code here, check key according last Seed */
    GetKey(DCM_SEC_LEV_L1, key);
    LOG(D, f("RecvKey: %02X %02X %02X %02X",
             pMsgContext->reqData[2],
             pMsgContext->reqData[3],
             pMsgContext->reqData[4],
             pMsgContext->reqData[5]));
    LOG(D, f("CalcKey: %02X %02X %02X %02X",
             key[0], key[1], key[2], key[3]));

    if (memcmp(&pMsgContext->reqData[2], key, 4U) == 0) {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1, KEY_IS_VALID);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    } else {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1, KEY_IS_NOT_VALID);
        DsdInternal_SetNegResponse(pMsgContext, DCM_E_INVALIDKEY);
    }
}
#endif

/* 0x28 */
#if(DCM_SERVICE_28_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_EnableRxAndEnableTx_Control
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_EnableRxAndEnableTx_Control(Dcm_MsgContextType *pMsgContext) {
    /* Add your code here */

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_DisableRxAndEnableTx_Control
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_DisableRxAndEnableTx_Control(Dcm_MsgContextType *pMsgContext) {
    /* Add your code here */

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_DisableRxAndDisableTx_Control
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_DisableRxAndDisableTx_Control(Dcm_MsgContextType *pMsgContext) {
    /* Add your code here */

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)

/******************************************************************************
* Name         :App_StartRoutine0xF000
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_StartRoutine0xF000(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    CurrentM_SampleChannelType i;
    Current_SensorCalibrateParam parameter;

    DsdInternal_RoutineStarted();
    /* Add your code here */
    for (i = CURRENTM_SAMPLE_CHANNEL_HALL; i < CURRENTM_SAMPLE_CHANNEL_MAX; i++) {
        (void)CurrentM_AutoCalibrated(i);
    }
    Shunt_GetCalibrateParam(&parameter);
    WRITE_BT_UINT16(pMsgContext->resData, length, parameter.zeroOffset);
    Hall_GetCalibrateParam(0U, &parameter);
    WRITE_BT_UINT16(pMsgContext->resData, length, parameter.zeroOffset);
    Hall_GetCalibrateParam(1U, &parameter);
    WRITE_BT_UINT16(pMsgContext->resData, length, parameter.zeroOffset);

    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_StartRoutine0xF001
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_StartRoutine0xF001(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    Current_SensorCalibrateParam parameter;

    DsdInternal_RoutineStarted();
    /* Add your code here */
    (void)CurrentM_AutoCalibrated(CURRENTM_SAMPLE_CHANNEL_SHUNT);

    Shunt_GetCalibrateParam(&parameter);
    WRITE_BT_UINT16(pMsgContext->resData, length, parameter.zeroOffset);

    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_StartRoutine0xF002
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_StartRoutine0xF002(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    Current_SensorCalibrateParam parameter;

    DsdInternal_RoutineStarted();
    /* Add your code here */
    (void)CurrentM_AutoCalibrated(CURRENTM_SAMPLE_CHANNEL_HALL1);

    Hall_GetCalibrateParam(0U, &parameter);
    WRITE_BT_UINT16(pMsgContext->resData, length, parameter.zeroOffset);

    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_StartRoutine0xF003
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_StartRoutine0xF003(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    Current_SensorCalibrateParam parameter;

    DsdInternal_RoutineStarted();
    /* Add your code here */
    (void)CurrentM_AutoCalibrated(CURRENTM_SAMPLE_CHANNEL_HALL2);

    Hall_GetCalibrateParam(1U, &parameter);
    WRITE_BT_UINT16(pMsgContext->resData, length, parameter.zeroOffset);

    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_StartRoutine0xF004
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
void App_StartRoutine0xF004(Dcm_MsgContextType *pMsgContext) {
    uint8 i, j;
    struct did_para_type {
        InternalComm_DidTypes did;
        InternalComm_GetSendDataFunc func;
    } did_para;

    DsdInternal_RoutineStarted();
    /* Add your code here */
    if (pMsgContext->reqDataLen >= 5U) {
        did_para.did = ((InternalComm_DidTypes)pMsgContext->reqData[4] << 8) + pMsgContext->reqData[5];
        if (pMsgContext->reqDataLen >= 8U) {
            did_para.func = (InternalComm_GetSendDataFunc)(((uint32)pMsgContext->reqData[6] << 16) + ((uint32)pMsgContext->reqData[7] << 8) + pMsgContext->reqData[8]); /*lint !e511 */
        } else {
            did_para.func = InternalComm_GetRequireDidData;
        }
        InternalComm_AddRequireDid(did_para.did, did_para.func);
    }
    for (i = 0U; i < DcmDspRoutineIdentifierTable_31[RoutineHandle_0xF004].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength; i++) {
        j = i + 4U;
        pMsgContext->resData[j] = pMsgContext->reqData[j];
    }
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xF004].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

void App_StartRoutine0xF006(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    uint16 block_num;
    DsdInternal_RoutineStarted();
    block_num = SaveM_EraseAll();
    WRITE_BT_UINT16(pMsgContext->resData, length, block_num);
    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}

void APP_RequestResultsRoutine0xF006(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    uint16 left = SaveM_GetEraseLeftBlockNum();
    WRITE_BT_UINT16(pMsgContext->resData, length, left);
    pMsgContext->resDataLen = length;
    if (left == 0U) {
        DsdInternal_RequestRoutineResults();
    }
    DsdInternal_ProcessingDone(pMsgContext);
}
void App_StartRoutine0xF007(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    DsdInternal_RoutineStarted();
    SocOcvCalib_AutoCalibStart();
    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
void App_StartRoutine0xF008(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    DsdInternal_RoutineStarted();
#if SYSTEM_BATTERY_CELL_NUM <= 48U
    BridgeInsu_Start(BRIDGEINSU_MOS_ALWAYS_ON);
#else
    BridgeInsu_Start(BRIDGEINSU_MOS_BY_VOL);
#endif
    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
void App_StopRoutine0xF008(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    DsdInternal_RoutineStopped();
    BridgeInsu_Stop();
    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
void APP_RequestResultsRoutine0xF008(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    uint16 res = Insu_GetSystem();
    WRITE_BT_UINT16(pMsgContext->resData, length, res);
    pMsgContext->resDataLen = length;
    DsdInternal_RequestRoutineResults();
    DsdInternal_ProcessingDone(pMsgContext);
}

void App_StartRoutine0xF009(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    DsdInternal_RoutineStarted();
    if (pMsgContext->reqDataLen >= 5U) {
        Statistic_SetSimulationHt(pMsgContext->reqData[4]);
        Statistic_SetSimulationLt(pMsgContext->reqData[5]);
        Statistic_SimulationHtLtEnable();
    }
    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
void App_StopRoutine0xF009(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    DsdInternal_RoutineStopped();
    Statistic_SimulationHtLtDisable();
    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
void APP_RequestResultsRoutine0xF009(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetSimulationHt());
    WRITE_BT_UINT8(pMsgContext->resData, length, Statistic_GetSimulationLt());
    pMsgContext->resDataLen = length;
    DsdInternal_RequestRoutineResults();
    DsdInternal_ProcessingDone(pMsgContext);
}

void App_StartRoutine0xF00A(Dcm_MsgContextType *pMsgContext) {
    uint8 command;
    uint16 length = 4U;
    DsdInternal_RoutineStarted();
    if (pMsgContext->reqDataLen >= 4U) {
        command = pMsgContext->reqData[4];
        if (command & 0x01U) {
            Statistic_SetCumuChgTime(0UL);
            (void)Statistic_SaveCumuChgTime(0UL);
        }
        if (command & 0x02U) {
            Statistic_SetCumuDchgTime(0UL);
            (void)Statistic_SaveCumuDchgTime(0UL);
        }
    }
    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
void App_StopRoutine0xF00A(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    DsdInternal_RoutineStopped();

    pMsgContext->resDataLen = length;
    DsdInternal_ProcessingDone(pMsgContext);
}
void APP_RequestResultsRoutine0xF00A(Dcm_MsgContextType *pMsgContext) {
    uint16 length = 4U;
    WRITE_BT_UINT32(pMsgContext->resData, length, Statistic_GetCumuChgTime());
    WRITE_BT_UINT32(pMsgContext->resData, length, Statistic_GetCumuDchgTime());
    pMsgContext->resDataLen = length;
    DsdInternal_RequestRoutineResults();
    DsdInternal_ProcessingDone(pMsgContext);
}

#endif

#include "DcmProgram.h"

#define TRANSFER_MODE_NONE      0U
#define TRANSFER_MODE_UPLOAD    1U
#define TRANSFER_MODE_DOWNLOAD  2U

static uint8 transfer_mode = TRANSFER_MODE_NONE;

/* 0x34 */
#if(DCM_SERVICE_34_ENABLED == STD_ON)
void App_RequestDownload(void) {
    uint32 addr;
    uint8 typ;
    uint32 len;

    if (gMsgContextType.reqDataLen != 9U) {
        DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    } else {
        if (gMsgContextType.reqData[1] != 0x00U) {
            DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        } else {
            if (gMsgContextType.reqData[2] != 0x24U) {
                DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            } else {
                typ = (gMsgContextType.reqData[3]);
                if (typ & 0xF8U) {
                    DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                } else {
                    addr = (uint32)(typ) << 24;
                    addr += (uint32)(gMsgContextType.reqData[4]) << 16;
                    addr += (uint32)(gMsgContextType.reqData[5]) << 8;
                    addr += gMsgContextType.reqData[6];

                    typ = (uint8)(gMsgContextType.reqData[7]);

                    len = ((uint32)typ & 0x0FU) << 8;
                    typ = typ >> 4;
                    len += gMsgContextType.reqData[8];
                    if (typ < 5U) {
                        if (typ == 0U) {
                        } else if (typ == 1U) {
                            len = len * 256U;
                        } else if (typ == 2U) {
                            len = len * 512U;
                        } else if (typ == 3U) {
                            len = len * 1024U;
                        } else {
                            len = len * 2048U;
                        }
                        if (len > 65535U) {
                            DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                        } else {
                            if (DcmProgram_RequestDownload(addr, (uint16)len) != E_OK) {
                                DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_REQUESTOUTOFRANGE);
                            } else {
                                transfer_mode = TRANSFER_MODE_DOWNLOAD;
                                gMsgContextType.resDataLen = 4U;
                                gMsgContextType.resData[1] = 0x20U;
                                gMsgContextType.resData[2] = 0x02U;
                                gMsgContextType.resData[3] = 0x00U;
                                DsdInternal_ProcessingDone(&gMsgContextType);
                            }
                        }
                    } else {
                        DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                }
            }
        }
    }
}
#endif


/* 0x35 */
#if(DCM_SERVICE_35_ENABLED == STD_ON)
void App_RequestUpload(void) {
    uint32 addr;
    uint8 typ;
    uint32 len;
    uint8 addr_seg = 0U;
    /*if (RuntimeM_GetMode() != RUNTIMEM_RUNMODE_DATA) {
        DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_GENERALREJECT);
    } else */{
        if (gMsgContextType.reqDataLen != 9U) {
            DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        } else {
            if (gMsgContextType.reqData[1] != 0x00U) {
                DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            } else {
                if (gMsgContextType.reqData[2] != 0x24U) {
                    DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                } else {
                    typ = (gMsgContextType.reqData[3]);
                    addr_seg = (typ >> 3);
                    /**
                    * 主机片内地址空间类型为 0
                    * 主机片外地址空间类型为 1 和 2
                    */
                    if ((addr_seg != 1U) && (addr_seg != 2U) && (addr_seg != 0U)) {
                        DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    } else {
                        addr = ((uint32)typ & 0x07U) << 24;
                        addr += (uint32)(gMsgContextType.reqData[4]) << 16;
                        addr += (uint32)(gMsgContextType.reqData[5]) << 8;
                        addr += gMsgContextType.reqData[6];

                        if (addr_seg == 2U) {
                            /**
                             * 地址类型值为2表示地址超出128M
                             */
                            addr += 0x8000000U;
                        }

                        typ = (uint8)(gMsgContextType.reqData[7]);

                        len = ((uint32)typ & 0x0FU) << 8;
                        typ = typ >> 4;
                        len += gMsgContextType.reqData[8];
                        if (typ < 5U) {
                            if (typ == 0U) {
                            } else if (typ == 1U) {
                                len = len * 256U;
                            } else if (typ == 2U) {
                                len = len * 512U;
                            } else if (typ == 3U) {
                                len = len * 1024U;
                            } else {
                                len = len * 2048U;
                            }
                            if (len > 65535U) {
                                DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                            } else {
                                if (DcmUpload_RequestUpload(addr_seg == 0U ? 1U : 0U, addr, (uint16)len) != E_OK) {
                                    DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_REQUESTOUTOFRANGE);
                                } else {
                                    transfer_mode = TRANSFER_MODE_UPLOAD;
                                    gMsgContextType.resDataLen = 4U;
                                    gMsgContextType.resData[1] = 0x20U;
                                    gMsgContextType.resData[2] = 0x02U;  // 512 bytes per frame
                                    gMsgContextType.resData[3] = 0x00U;
                                    DsdInternal_ProcessingDone(&gMsgContextType);
                                }
                            }
                        } else {
                            DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                        }
                    }
                }
            }
        }
    }
}
#endif

/* 0x34 */
#if(DCM_SERVICE_36_ENABLED == STD_ON)
void App_DataTransfer(void) {
    if (transfer_mode == TRANSFER_MODE_UPLOAD) {
        sint32 ret = DcmUpload_TransferData(gMsgContextType.reqData[1], &gMsgContextType.resData[2], 0x200U);
        if (ret < 0) {
            DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            transfer_mode = TRANSFER_MODE_NONE;
        } else {
            gMsgContextType.resDataLen = 2U + (uint32)ret;
            gMsgContextType.resData[1] = gMsgContextType.reqData[1];
            DsdInternal_ProcessingDone(&gMsgContextType);
        }
    } else if (transfer_mode == TRANSFER_MODE_DOWNLOAD) {
        if (DcmProgram_ProgramData(gMsgContextType.reqData[1], &gMsgContextType.reqData[2], (uint16)(gMsgContextType.reqDataLen - 2U)) != E_OK) {
            DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            transfer_mode = TRANSFER_MODE_NONE;
        } else {
            gMsgContextType.resDataLen = 2U;
            gMsgContextType.resData[1] = gMsgContextType.reqData[1];
            DsdInternal_ProcessingDone(&gMsgContextType);
        }
    } else {
    }
}
#endif

/* 0x37 */
#if(DCM_SERVICE_37_ENABLED == STD_ON)
void App_TransferExit(void) {
    if (gMsgContextType.reqDataLen != 1U) {
        DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    } else {
        uint flag = 1U;
        if (RuntimeM_GetMode() == RUNTIMEM_RUNMODE_DATA) {
            if (DcmUpload_ExitTransfer() != E_OK) {
                DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                flag = 0U;
            }
        } else {
            if (DcmProgram_ExitTransfer() != E_OK) {
                DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                flag = 0U;
            }
        }
        if (flag != 0U) {
            gMsgContextType.resDataLen = 1U;
            gMsgContextType.resData[1] = gMsgContextType.reqData[1];
            transfer_mode = TRANSFER_MODE_NONE;
            DsdInternal_ProcessingDone(&gMsgContextType);
        }
    }

}
#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
#endif

/* 0x85 */
#if(DCM_SERVICE_85_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ON_Send
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_ON_Send(Dcm_MsgContextType *pMsgContext) {
    (void)pMsgContext;
    /* Add your code here */
    gDTCSwitch = STD_ON;

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_OFF_Send
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*
******************************************************************************/
void App_OFF_Send(Dcm_MsgContextType *pMsgContext) {
    (void)pMsgContext;
    /* Add your code here */
    gDTCSwitch = STD_OFF;

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x86 */
#if(DCM_SERVICE_86_ENABLED == STD_ON)
#endif
