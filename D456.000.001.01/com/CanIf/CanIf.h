#ifndef _CANIF_H_
#define _CANIF_H_

#include "CanIf_Types.h"
#include "CanIf_Cfg.h"
#if(STD_ON == CANIF_SUPPORT_OSEK_NM)
#include "OsekNm.h"
#endif

#define CANIF_MSK_EXT_ID_MSB                    (0x00000800UL)
#define CANIF_ENTER_CRITICAL_SECTION()          Can_DisableGlobalInterrupts()
#define CANIF_LEAVE_CRITICAL_SECTION()          Can_EnableGlobalInterrupts()
#define CANIF_MAX_CANID                         (0x1fffffffUL)

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
#define CANIF_RX_BUFFER_SDU_LENGTH_INITIAL      (0xffU)
#endif

#if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
#if(CAN_USED_HOH_MAX_NUM > 255)
#define  CANIF_LAST_HRH_RXPDUID       ((PduIdType)0xFFFFU)
#else
#define  CANIF_LAST_HRH_RXPDUID       ((PduIdType)0xFFU)
#endif
#endif


#if(CANIF_DISPATCH_UL_CAN_SM == CANIF_DISPATCH_USERCTRLBUSOFF_UL)
#define  CANIF_DISPATCH_USERCTRLBUSOFF_NAME   \
                                              CanSM_ControllerBusOff(Controller)
#elif(CANIF_DISPATCH_UL_CDD == CANIF_DISPATCH_USERCTRLBUSOFF_UL)
#define  CANIF_DISPATCH_USERCTRLBUSOFF_NAME   \
                                      CANIF_DISPATCH_USERCTRLBUSOFF_DEFINED_NAME
#else
#error "!!!ERROR FOR CANIF_DISPATCH_USERCTRLBUSOFF_UL!!!"
#endif

#if(CANIF_DISPATCH_UL_ECUM == CANIF_DISPATCH_USERSETWAKEUP_UL)
#define  CANIF_DISPATCH_USERSETWAKEUP_NAME   \
                                               EcuM_ControllerWakeUp(Controller)
#elif(CANIF_DISPATCH_UL_CDD == CANIF_DISPATCH_USERSETWAKEUP_UL)
#define  CANIF_DISPATCH_USERSETWAKEUP_NAME       \
                                  CANIF_DISPATCH_USERSETWAKEUP_DEFINED_NAME
#else
#error "!!!ERROR FOR CANIF_DISPATCH_USERSETWAKEUP_UL!!!"
#endif

#define CANIF_USERWAKEUP_FUN       CANIF_DISPATCH_USERSETWAKEUP_NAME
#define CANIF_USERCTRLBUSOFF_FUN   CANIF_DISPATCH_USERCTRLBUSOFF_NAME


#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
#define CANIF_E_PARAM_CANID                       (0x10u)
#define CANIF_E_PARAM_DLC                         (0x11u)
#define CANIF_E_PARAM_HRH                         (0x12u)
#define CANIF_E_PARAM_LPDU                        (0x13u)
#define CANIF_E_PARAM_CONTROLLER                  (0x14u)
#define CANIF_E_PARAM_CONTROLLERID                (0x15u)
#define CANIF_E_PARAM_WAKEUPSOURCE                (0x16u)
#define CANIF_E_PARAM_TRCV                        (0x17u)
#define CANIF_E_PARAM_TRCVMODE                    (0x18u)
#define CANIF_E_PARAM_TRCVWAKEUPMODE              (0x19u)
#define CANIF_E_PARAM_POINTER                     (0x20u)

#define CANIF_E_UNINIT                            (0x30u)
#define CANIF_E_NOK_NOSUPPORT                     (0x40u)
#define CANIF_E_INVALID_TXPDUID                   (0x50u)
#define CANIF_E_INVALID_RXPDUID                   (0x60u)

#define CANIF_SETCONTROLLERMODE_APIID             (0x03u)
#define CANIF_GETCONTROLLERMODE_APIID             (0x04u)
#define CANIF_TRANSMIT_APIID                      (0x05u)
#define CANIF_READRXPDUDATA_APIID                 (0x06u)
#define CANIF_READTXNOTIFSTATUS_APIID             (0x07u)
#define CANIF_READRXNOTIFSTATUS_APIID             (0x08u)
#define CANIF_SETPDUMODE_APIID                    (0x09u)
#define CANIF_GETPDUMODE_APIID                    (0x0au)
#define CANIF_GETVERSIONINFO                      (0x0bu)
#define CANIF_SETDYNAMICTXID_APIID                (0x0cu)
#define CANIF_TXCONFIRMATION_APIID                (0x13u)
#define CANIF_RXINDICATION_APIID                  (0x14u)
#define CANIF_CANCELTXCONFIRMATION_APIID          (0x15u)
#define CANIF_CONTROLLERBUSOFF_APIID              (0x16u)
#define CANIF_CONTROLLERMODEINDICATION_APIID      (0x17u)
#endif

#if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
#define CANIF_RX_INDICATION_ENABLE_MASK   ((uint8)0x01U)
#define CANIF_RX_INDICATION_DISABLE_MASK  ((uint8)0xfeU)
#define CANIF_TX_REQUEST_ENABLE_MASK      ((uint8)0x02U)
#define CANIF_TX_REQUEST_DISABLE_MASK     ((uint8)0xfdU)
#define CANIF_TX_NOTIFY_ENABLE_MASK       ((uint8)0x04U)
#define CANIF_TX_NOTIFY_DISABLE_MASK      ((uint8)0xfbU)
#define CANIF_PDU_GETMODE_MASK            ((uint8)0x07U)
#endif

typedef enum {
    CANIF_UNINITIALIZED = 0,
    CANIF_INITIALIZED = 1
} CanIf_InitType;

typedef enum {
    STATIC_TXPDU = 0,
    DYNAMIC_TXPDU = 1
} CanIf_TxPduType;

typedef enum {
    STANDARD_CAN = 0,
    EXTENDED_CAN = 1
} CanIf_PduCanIdType;

typedef void (*User_RxIndication)(PduIdType CanUserRxPduId, const PduInfoType *PduInfoPtr);
typedef void (*Range_RxIndication)(PduIdType CanUserRxPduId, Can_IdType CanId, const PduInfoType *PduInfoPtr);
typedef void (*User_TxConfirmation)(PduIdType CanUserTxPduId);

typedef struct {
#if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
    PduIdType UpperLayerHandle; /*Remap the PduId for UpperLayer*/
#endif
    Can_IdType CanId;                 /* Can_IdType 16 or 32 bit */
    CanIf_PduCanIdType CanIdType;               /* CANIF_TXPDU_CANIDType */
    Can_HwHandleType Hth;                  /* Hardware transmit handle */
    uint8 Length;               /* DLC                      */
    User_TxConfirmation     TxConfirmation;       /* Confirmation function    */
#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
    CanIf_TxPduType TxPduType;     /* CanIfTxPduType DYNAMIC or STATIC*/
#endif
#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
    boollean TxPduReadNotifyStatus;
#endif
} CanIf_TxPduConfigType;

typedef struct {
    Can_IdType RxPduCanIdRangeLowerCanId ;
    Can_IdType RxPduCanIdRangeUpperCanId;
    Range_RxIndication              RangeRxIndication;
} CanIf_RxPduCanIdRangeType;


typedef struct {
#if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
    PduIdType UpperLayerHandle;
#endif
    Can_IdType CanId;          /* Can_IdType 16 or 32 bit  */
    CanIf_PduCanIdType CanIdType;      /* CANIF_RXPDU_CANIDType */
    Can_HwHandleType Hrh;            /* Hardware transmit handle */
    uint8 Length;         /* DLC                      */

    User_RxIndication RxIndication;   /* Indication function      */

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
    boollean RxPduReadNotifyStatus;
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
    boollean RxPduReadData;
#endif

#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
    const CanIf_RxPduCanIdRangeType *
    RxPduCanIdRangeCfg;
#endif

#if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
    PduIdType HrhNextRxPduID;
#endif
} CanIf_RxPduConfigType;

typedef struct {
    Can_IdType HrhRangeRxPduLowerCanId;
    Can_IdType HrhRangeRxPduUpperCanId;
    CanIf_PduCanIdType HrhRangeRxPduRangeCanIdType;
} CanIf_HrhRangeCfgType;

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
extern boollean/*CANIF_PRIVATE_DATA*/ CanIfTxBufferPDUFillflag[];
extern uint8/*CANIF_PRIVATE_DATA*/ CanIfTxBufferSdu[][CAN_DATA_DLC];
extern Can_PduType/*CANIF_PRIVATE_DATA*/ CanIfTxBufferPdu[];
#endif

#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
extern Can_IdType/*CANIF_PRIVATE_DATA*/ CanIfTxPduCanIdForDynamic[];
#endif

#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
extern CanIf_NotifStatusType/*CANIF_PRIVATE_DATA*/ CanIfTxNotifStatus[];
#endif

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
extern CanIf_NotifStatusType/*CANIF_PRIVATE_DATA*/ CanIfRxNotifStatus[];
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
extern uint8/*CANIF_PRIVATE_DATA*/ CanIfRxBufferSduData[][CAN_DATA_DLC];
extern PduLengthType/*CANIF_PRIVATE_DATA*/ CanIfRxBufferSduLength[];
#endif

extern const PduIdType/*CANIF_CONFIG_CONST*/ CanIfInitNumberOfCanRxPduIds ;
extern const PduIdType/*CANIF_CONFIG_CONST*/ CanIfInitNumberOfCanTxPduIds ;
extern const Can_HwHandleType/*CANIF_CONFIG_CONST*/ CanIfInitNumberofHrh ;

#if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
extern const Can_HwHandleType/*CANIF_CONFIG_CONST*/ CanIfHrhFirstRxPduID[];
#endif

#if(STD_ON == CANIF_HRH_RANGE_FILTER)
extern const CanIf_HrhRangeCfgType/*CANIF_CONFIG_CONST*/ CanIfHrhRangeCfg[];
#endif

extern const CanIf_RxPduConfigType/*CANIF_CONFIG_CONST*/ CanIfRxPduConfig[];
extern const CanIf_TxPduConfigType/*CANIF_CONFIG_CONST*/ CanIfTxPduConfig[];

extern void CanIf_Init(void);

extern Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
extern Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, CanIf_ControllerModeType *ControllerModePtr);

extern Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr);

#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON)
extern Std_ReturnType CanIf_CancelTransmit(PduIdType CanTxPduId);
#endif

#if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
extern Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduSetModeType PduModeRequest);
extern Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduGetModeType *PduModePtr);
#endif


#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
extern Std_ReturnType CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId);
#endif

#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
extern CanIf_NotifStatusType CanIf_ReadTxNotifStatus(PduIdType CanTxPduId);
#endif

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
extern CanIf_NotifStatusType CanIf_ReadRxNotifStatus(PduIdType CanRxPduId);
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
extern Std_ReturnType CanIf_ReadRxPduData(PduIdType CanRxPduId, PduInfoType *PduInfoPtr);
#endif

#if (STD_ON == CANIF_PUBLIC_VERSION_INFO_API)
extern void CanIf_GetVersionInfo(Std_VersionInfo_Type *VersionInfo);
#endif

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
extern void CanIf_ClearTransmitBuffer(uint8 ControllerId);
#endif

#endif
