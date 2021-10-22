/*lint -save*/
/*lint -e451 -e537*/


#include "CanIf.h"
#include "CanIf_Cbk.h"
//#include "Dem.h"
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
#include "Det.h"
#endif

#if (1 == CAN_CONTROLLER_MAX_NUM)
#define CANIF_CANCONTROLLER_TX        (0u)
#define CANIF_CANCONTROLLER_RX        (0u)
#define CANIF_CONTROLLER_ID           (0u)
#else
#define CANIF_CANCONTROLLER_TX        \
     (CanHardwareObject[(CanIfTxPduConfig[CanTxPduId]).Hth].controllerRef)
#define CANIF_CANCONTROLLER_RX        \
                                    (CanHardwareObject[Hrh].controllerRef)
#define CANIF_CONTROLLER_ID           (ControllerId)
#endif
#if(STD_ON == CANIF_HRH_RANGE_FILTER)
#define CANIF_HRH_CANID_TYPE          \
                             (CanIfHrhRangeCfg[Hrh].HrhRangeRxPduRangeCanIdType)
#define CANIF_HRH_LOWER_CANID         \
                                 (CanIfHrhRangeCfg[Hrh].HrhRangeRxPduLowerCanId)
#define CANIF_HRH_UPPER_CANID         \
                                 (CanIfHrhRangeCfg[Hrh].HrhRangeRxPduUpperCanId)

#endif
#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
#define CANIF_RXPDU_RANGECFG   (CanIfRxPduConfig[handle].RxPduCanIdRangeCfg)
#endif

static PduIdType /*CANIF_PRIVATE_DATA*/ CanIf_TotalRxPduIds = 0U;
static PduIdType /*CANIF_PRIVATE_DATA*/ CanIf_TotalTxPduIds = 0U;

static CanIf_ControllerModeType /*CANIF_PRIVATE_DATA*/ CanIf_ControllerMode[CAN_CONTROLLER_MAX_NUM];

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
static CanIf_InitType /*CANIF_PRIVATE_DATA*/ CanIf_InitStatus = CANIF_UNINITIALIZED;
#endif

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
static PduIdType /*CANIF_PRIVATE_DATA*/ CanIfTxBufferFillCount;
#endif

#if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
static CanIf_PduGetModeType /*CANIF_PRIVATE_DATA*/ CanIfPduMode[CAN_CONTROLLER_MAX_NUM];
#endif

static void CanIf_MemSet(void *const pDest, const uint8 data, uint32 length);
static void CanIf_MemCpy(void *const dest, const void *const source, uint32 length);

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
static Std_ReturnType CanIf_RxParCheck(const Can_HwHandleType Hrh, const Can_IdType CanId, const uint8 CanDlc, const uint8 *const CanSduPtr);
#endif

static Std_ReturnType CanIf_DlcCheck(const uint8 CanDlc, const PduIdType handle, PduLengthType *const dlc);

static void CanIf_MemSet(void *const pDest, const uint8 data, uint32 length) {
    if (NULL_PTR != pDest) {
        while (length > 0x0UL) {
            length--;
            ((uint8 *)pDest)[length] = data;
        }
    }
}

static void CanIf_MemCpy(void *const dest, const void *const source, uint32 length) {
    uint8 *const sd = (uint8 * const)dest;
    const uint8 *const ss = (const uint8 * const )source;
    uint32 i = 0U;

    if ((NULL_PTR != sd) && (NULL_PTR != ss)) {
        while (length > 0x0UL) {
            sd[i] = ss[i];
            i++;
            length--;
        }
    }
}

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
static Std_ReturnType CanIf_RxParCheck(const Can_HwHandleType Hrh, const Can_IdType CanId, const uint8 CanDlc, const uint8 *const CanSduPtr) {
    Std_ReturnType ret = E_NOT_OK;

    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_UNINIT);
    } else if (Hrh >= CanIfInitNumberofHrh) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_PARAM_HRH);
    } else if (CanId > CANIF_MAX_CANID) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_PARAM_CANID);
    } else if (CanDlc > CAN_DATA_DLC) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_PARAM_DLC);
    } else if (NULL_PTR == CanSduPtr) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_PARAM_POINTER);
    } else {
        ret = E_OK;
    }

    return ret;
}
#endif

static Std_ReturnType CanIf_DlcCheck(const uint8 CanDlc, const PduIdType handle, PduLengthType *const dlc) {
    Std_ReturnType ret = E_OK;
    PduLengthType tempDlc = 0U;

#if(STD_ON == CANIF_PRIVATE_DLC_CHECK)
    /* AUTOSAR Standard method */
#if(CANIF_DLC_CHECK_TYPE ==  CANIF_DLC_CHECK_AUTOSAR)
    /*CANIF026: The CanIf shall accept all L-PDUs with a
    received DLC value equal or greater then the configured DLC value. */
    if (CanDlc < (CanIfRxPduConfig[handle].Length)) {
        ret = E_NOT_OK;
    } else {
        /*If the CanIf has accepted a L-PDU received via
        CanIf_RxIndication() during DLC check, the CanIf shall
        copy the number of bytes according to the configured
        DLC value to the static receive buffer, if configured
        for that L-PDU , or allow copying the data to the upper
        layer modules.*/
        tempDlc = CanIfRxPduConfig[handle].Length;
    }

#endif

#if(CANIF_DLC_CHECK_TYPE ==  CANIF_DLC_CHECK_UNEQUAL)
    /* The CanIf will accept L-PDU only when its received DLC value equal to
     the configured DLC value. */
    if (CanDlc == (CanIfRxPduConfig[handle].Length)) {
        tempDlc = CanDlc;
    } else {
        /* */
#if(CANIF_DLC_CHECK_FAIL_INDICATION == STD_OFF)
        ret = E_NOT_OK;
#else
        tempDlc = CanDlc;
        ret = E_OK;
#endif

    }
#endif

#if(CANIF_DLC_CHECK_TYPE ==  CANIF_DLC_CHECK_USER)

#endif

#else
    /*In case of the DLC check is disabled,  the received DLC value is passed in
    the receive indication type <User_RxIndication>(CanRxPduId,*PduInfoPtr),to
    upper layer modules .The upper layer module copies the data to its own
    buffer always according to the received DLC value and not to the configured
    DLC value.*/
    (void)handle;
    tempDlc = CanDlc; /*lint !e838 */
#endif

    if (NULL_PTR != dlc) {
        *dlc = tempDlc;
    }

    return ret;

}

/* const CanIf_ConfigType* ConfigPtr */
void CanIf_Init(void) {
    uint8 i;

    for (i = 0U; i < CanUsedControllerNum; i++) {
#if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
        CanIfPduMode[i] = CANIF_GET_ONLINE;
#endif

        CanIf_ControllerMode[i] = CANIF_CS_UNINIT;
    }

    CanIf_TotalRxPduIds = CanIfInitNumberOfCanRxPduIds;
    CanIf_TotalTxPduIds = CanIfInitNumberOfCanTxPduIds;
    (void)CanIf_TotalRxPduIds;
    (void)CanIf_TotalTxPduIds;

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
    CanIf_MemSet(CanIfTxBufferPDUFillflag, FALSE, (uint32)CanIf_TotalTxPduIds);

    CanIf_MemSet(CanIfTxBufferSdu, 0U, ((uint32)CanIf_TotalTxPduIds * CAN_DATA_DLC));

    CanIf_MemSet(CanIfTxBufferPdu, 0U,
                 (((uint32)(sizeof(Can_PduType))) * CanIf_TotalTxPduIds));

    CanIfTxBufferFillCount = 0U;
#endif

#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
    for (i = 0U; i < CanIf_TotalTxPduIds; i++) {
        if (DYNAMIC_TXPDU == CanIfTxPduConfig[i].TxPduType) {
            CanIfTxPduCanIdForDynamic[i] = CanIfTxPduConfig[i].CanId;
        }
    }
#endif

#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
    CanIf_MemSet(CanIfTxNotifStatus, CANIF_NO_NOTIFICATION,
                 (((PduIdType)sizeof(CanIf_NotifStatusType))) * CanIf_TotalTxPduIds);
#endif

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
    CanIf_MemSet(CanIfRxNotifStatus, CANIF_NO_NOTIFICATION,
                 (((PduIdType)sizeof(CanIf_NotifStatusType))) * CanIf_TotalTxPduIds);
#endif


#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
    CanIf_MemSet(CanIfRxBufferSduData, 0U, CAN_DATA_DLC * CanIf_TotalRxPduIds);
    CanIf_MemSet(CanIfRxBufferSduLength, CANIF_RX_BUFFER_SDU_LENGTH_INITIAL,
                 (((PduIdType)sizeof(PduLengthType))) * CanIf_TotalRxPduIds);
#endif

    for (i = 0U; i < CanUsedControllerNum; i++) {

        CanIf_ControllerMode[i] = CANIF_CS_STOPPED;
    }
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    CanIf_InitStatus = CANIF_INITIALIZED;
#endif
}

Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, CanIf_ControllerModeType ControllerMode) {
    Std_ReturnType ret = E_OK;

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETCONTROLLERMODE_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;
    } else if (ControllerId >= CANIF_USED_CONTROLLER_NUM) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETCONTROLLERMODE_APIID,
                        CANIF_E_PARAM_CONTROLLERID);
        ret = E_NOT_OK;
    } else
#endif
    {
        switch (ControllerMode) {
        case CANIF_CS_STARTED:

            if (CANIF_CS_SLEEP == CanIf_ControllerMode[CANIF_CONTROLLER_ID]) {
                //ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                //CAN_T_WAKEUP);
            }
            if (E_OK == ret) { /*lint !e774 */
                //ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                //CAN_T_START);
            }

            break;

        case CANIF_CS_SLEEP:

            if (CANIF_CS_STOPPED != CanIf_ControllerMode[CANIF_CONTROLLER_ID]) {
                //ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                //CAN_T_STOP);
            }

            if (E_OK == ret) { /*lint !e774 */
                // ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                //CAN_T_SLEEP);
            }

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
            if (E_OK == ret) { /*lint !e774 */
                CanIf_ClearTransmitBuffer(CANIF_CONTROLLER_ID);
            }
#endif

            break;

        case CANIF_CS_STOPPED:

            //ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
            //CAN_T_STOP);
#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
            if (E_OK == ret) { /*lint !e774 */
                CanIf_ClearTransmitBuffer(CANIF_CONTROLLER_ID) ;
            }
#endif

            break;

        case CANIF_CS_UNINIT:

            break;

        default:
            ret = E_NOT_OK;
            break;
        }

    }

    return ret;

}

Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, CanIf_ControllerModeType *ControllerModePtr) {
    Std_ReturnType ret = E_OK;

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETCONTROLLERMODE_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;
    } else if (ControllerId >= CANIF_USED_CONTROLLER_NUM) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETCONTROLLERMODE_APIID,
                        CANIF_E_PARAM_CONTROLLERID);
        ret = E_NOT_OK;
    } else if (NULL_PTR == ControllerModePtr) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETCONTROLLERMODE_APIID,
                        CANIF_E_PARAM_POINTER);
        ret = E_NOT_OK;
    } else
#endif

    {
        *ControllerModePtr = (CanIf_ControllerMode[CANIF_CONTROLLER_ID]);
    }

    return ret;

}

#if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduSetModeType PduModeRequest) {
    Std_ReturnType ret = E_OK;
    uint8 tempMode = (uint8)CanIfPduMode[CANIF_CONTROLLER_ID];

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETPDUMODE_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;
    } else if (ControllerId >= CANIF_USED_CONTROLLER_NUM) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETPDUMODE_APIID,
                        CANIF_E_PARAM_CONTROLLERID);
        ret = E_NOT_OK;
    } else
#endif
    {
        switch (PduModeRequest) {
        case CANIF_SET_OFFLINE:
            tempMode = (uint8)CANIF_GET_OFFLINE;
            break;

        case CANIF_SET_ONLINE:
            tempMode = (uint8)CANIF_GET_ONLINE;
            break;

        case CANIF_SET_RX_OFFLINE:
            tempMode = tempMode & CANIF_RX_INDICATION_DISABLE_MASK;
            break;

        case CANIF_SET_RX_ONLINE:
            tempMode = tempMode | CANIF_RX_INDICATION_ENABLE_MASK;
            break;

        case CANIF_SET_TX_OFFLINE:
            tempMode = tempMode & CANIF_TX_REQUEST_DISABLE_MASK;
            tempMode = tempMode & CANIF_TX_NOTIFY_DISABLE_MASK;
            break;

        case CANIF_SET_TX_OFFLINE_ACTIVE:
            tempMode = tempMode & CANIF_TX_REQUEST_DISABLE_MASK;
            tempMode = tempMode | CANIF_TX_NOTIFY_ENABLE_MASK;
            break;

        case CANIF_SET_TX_ONLINE:
            tempMode = tempMode | CANIF_TX_REQUEST_ENABLE_MASK;
            tempMode = tempMode | CANIF_TX_NOTIFY_ENABLE_MASK;
            break;

        default:
            break;

        }
        tempMode = tempMode & CANIF_PDU_GETMODE_MASK;
        /*******************************************************************
        * PRQA S 1482
        * Uint8 cast to enum type, to fulfill the AUTOSAR type and function.
        * This part of code is verified manually and has no impact.
        *******************************************************************/
        CanIfPduMode[CANIF_CONTROLLER_ID] = (CanIf_PduGetModeType)tempMode;
    }
    return ret;
}

Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduGetModeType *PduModePtr) {
    Std_ReturnType ret = E_OK;

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETPDUMODE_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;
    } else if (ControllerId >= CANIF_USED_CONTROLLER_NUM) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETPDUMODE_APIID,
                        CANIF_E_PARAM_CONTROLLERID);
        ret = E_NOT_OK;
    } else if (NULL_PTR == PduModePtr) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETPDUMODE_APIID,
                        CANIF_E_PARAM_POINTER);
        ret = E_NOT_OK;
    } else
#endif

    {
        *PduModePtr = CanIfPduMode[CANIF_CONTROLLER_ID];
    }

    return ret;
}
#endif

Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr) {

    uint8 i;
    uint8 CanIfTxPduBuffer[CAN_DATA_DLC];
    Can_PduType CanIfTxPduObject;
    Can_ReturnType CanTxResult;
    Std_ReturnType ret;
#if(CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
    CanIf_PduGetModeType tempMode;
#endif


    CanIfTxPduObject.sdu = CanIfTxPduBuffer;
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        ret = E_NOT_OK;
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TRANSMIT_APIID,
                        CANIF_E_UNINIT);

    } else if (CanTxPduId >= CanIf_TotalTxPduIds) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TRANSMIT_APIID,
                        CANIF_E_INVALID_TXPDUID);
        ret = E_NOT_OK;
    } else if (NULL_PTR == PduInfoPtr) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TRANSMIT_APIID,
                        CANIF_E_PARAM_POINTER);
        ret = E_NOT_OK;
    } else
#endif
    {


#if(CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
        tempMode = CanIfPduMode[CANIF_CANCONTROLLER_TX];
#endif

        /* if controller is not in start or the channel is in txoffline
           the tx request will not accept */
        if
        ((CANIF_CS_STARTED !=  CanIf_ControllerMode[CANIF_CANCONTROLLER_TX])
#if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
                || (CANIF_GET_OFFLINE == tempMode) || (CANIF_GET_RX_ONLINE == tempMode)
#endif
        ) {

            //Dem_ReportErrorStatus(CANIF_E_STOPPED, DEM_EVENT_STATUS_FAILED);
            ret = E_NOT_OK;
        } else {
#if(CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
            if ((CANIF_GET_OFFLINE_ACTIVE == tempMode)
                    || (CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE == tempMode)) {
                ret = E_OK;
                CanIf_TxConfirmation(CanTxPduId);
            } else
#endif
            {
                CanIfTxPduObject.swPduHandle = CanTxPduId;

#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
                /*So that,CanIf_SetDynamicTxId()will not be interrupted
                by CanIf_Transmit()*/

                if (DYNAMIC_TXPDU == CanIfTxPduConfig[CanTxPduId].TxPduType) {
                    CanIfTxPduObject.id = CanIfTxPduCanIdForDynamic[CanTxPduId];
                } else
#endif
                {
                    CanIfTxPduObject.id = CanIfTxPduConfig[CanTxPduId].CanId;
                }

                /*DLC Check,must be smaller or equal to 8*/
                if ((PduInfoPtr->SduLength) > ((PduLengthType)CAN_DATA_DLC)) {
                    CanIfTxPduObject.length = CAN_DATA_DLC;
                } else {
                    CanIfTxPduObject.length = (uint8)PduInfoPtr->SduLength;
                }

                for (i = 0U; i < (CanIfTxPduObject.length); i++) {
                    CanIfTxPduObject.sdu[i] = PduInfoPtr->SduDataPtr[i];
                }

                CanTxResult = Can_Write((CanIfTxPduConfig[CanTxPduId].Hth),
                                        &CanIfTxPduObject);

                if (CAN_OK == CanTxResult ) {
                    ret = E_OK;
                } else {
                    ret =  E_NOT_OK;
                }

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
                /*when CAN driver is return busy ,CAN Interface store the
                complete CANIF Tx L-PDU in the appropriate*/
                if (CAN_BUSY == CanTxResult) {
                    CANIF_ENTER_CRITICAL_SECTION();
                    /*CanIfTxBufferFillCount is used for counting the num of
                    CanIfTxBufferPdu which is used*/
                    if (FALSE == CanIfTxBufferPDUFillflag[CanTxPduId]) {
                        CanIfTxBufferPDUFillflag[CanTxPduId] = TRUE;
                        CanIfTxBufferFillCount++;
                    }

                    /* CANIF068:If the function CanIf_Transmit() is called and
                    if the CanIf has to store the L-PDU in the transmit L-PDU
                    buffer, then if the corresponding CanIfTxBuffer is already
                    filled, the CanIf shall overwrite the older L-PDU with the
                    recent L-PDU.*/
                    CanIf_MemCpy(CanIfTxBufferSdu[CanTxPduId],
                                 CanIfTxPduObject.sdu,
                                 (uint32)CanIfTxPduObject.length);

                    CanIfTxBufferPdu[CanTxPduId].id = CanIfTxPduObject.id;
                    CanIfTxBufferPdu[CanTxPduId].length =
                        CanIfTxPduObject.length;
                    CanIfTxBufferPdu[CanTxPduId].sdu =
                        CanIfTxBufferSdu[CanTxPduId];
                    CanIfTxBufferPdu[CanTxPduId].swPduHandle = CanTxPduId;

                    CANIF_LEAVE_CRITICAL_SECTION();
                    ret = E_OK;

                }
#endif /*end of #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)*/

            }
        }
    }
    return ret;
}

#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON)
Std_ReturnType CanIf_CancelTransmit(PduIdType CanTxPduId) {
    (void)CanTxPduId;
    return E_OK;
}
#endif

#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
Std_ReturnType CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId) {
    Std_ReturnType  ret = E_OK;

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)

    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETDYNAMICTXID_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;
    } else if ((CanTxPduId >= CanIf_TotalTxPduIds) ||
               (STATIC_TXPDU == CanIfTxPduConfig[CanTxPduId].TxPduType)) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETDYNAMICTXID_APIID,
                        CANIF_E_INVALID_TXPDUID);
        ret = E_NOT_OK;
    }

    else if (CanId > CANIF_MAX_CANID) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETDYNAMICTXID_APIID,
                        CANIF_E_PARAM_CANID);
        ret = E_NOT_OK;
    } else
#endif

    {
        CANIF_ENTER_CRITICAL_SECTION();
        CanIfTxPduCanIdForDynamic[CanTxPduId] = CanId;
        CANIF_LEAVE_CRITICAL_SECTION();
    }

    return ret;
}
#endif

#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
CanIf_NotifStatusType CanIf_ReadTxNotifStatus(PduIdType CanTxPduId) {
    CanIf_NotifStatusType ret = CANIF_NO_NOTIFICATION;

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)

    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READTXNOTIFSTATUS_APIID,
                        CANIF_E_UNINIT);
    } else if ((CanTxPduId >= CanIf_TotalTxPduIds) ||
               (FALSE == CanIfTxPduConfig[CanTxPduId].TxPduReadNotifyStatus)) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READTXNOTIFSTATUS_APIID,
                        CANIF_E_INVALID_TXPDUID);
    } else
#endif
    {
        if (CANIF_TX_RX_NOTIFICATION == CanIfTxNotifStatus[CanTxPduId]) {
            ret =  CANIF_TX_RX_NOTIFICATION;
            CanIfTxNotifStatus[CanTxPduId] = CANIF_NO_NOTIFICATION;
        }

    }
    return ret;
}
#endif

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
CanIf_NotifStatusType CanIf_ReadRxNotifStatus(PduIdType CanRxPduId) {
    CanIf_NotifStatusType ret = CANIF_NO_NOTIFICATION;

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)

    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXNOTIFSTATUS_APIID,
                        CANIF_E_UNINIT);
    } else if ((CanRxPduId >= CanIf_TotalRxPduIds) ||
               (FALSE == CanIfRxPduConfig[CanRxPduId].RxPduReadNotifyStatus)) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXNOTIFSTATUS_APIID,
                        CANIF_E_INVALID_RXPDUID);
    } else
#endif
    {
        if (CANIF_TX_RX_NOTIFICATION == CanIfRxNotifStatus[CanRxPduId]) {
            ret =  CANIF_TX_RX_NOTIFICATION;
            CanIfRxNotifStatus[CanRxPduId] = CANIF_NO_NOTIFICATION;
        }
    }
    return ret;
}
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
Std_ReturnType CanIf_ReadRxPduData(PduIdType CanRxPduId, PduInfoType *PduInfoPtr) {
    Std_ReturnType ret = E_NOT_OK;

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXPDUDATA_APIID,
                        CANIF_E_UNINIT);
    } else if ((CanRxPduId >= CanIf_TotalRxPduIds) ||
               (FALSE == CanIfRxPduConfig[CanRxPduId].RxPduReadData)) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXPDUDATA_APIID,
                        CANIF_E_INVALID_RXPDUID);
    } else if (NULL_PTR == PduInfoPtr) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXPDUDATA_APIID,
                        CANIF_E_PARAM_POINTER);
    } else
#endif
    {
        /*already has data in buffer*/
        if (CAN_DATA_DLC >= CanIfRxBufferSduLength[CanRxPduId]) {
#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
            if (NULL_PTR == CanIfRxPduConfig[CanRxPduId].RxPduCanIdRangeCfg)
#endif
            {
                /*During the call of this API the buffer of PduInfoPtr is
                controlled by the CanIf and this buffer should not be accessed
                for read/write from another call context. After return of this
                call the ownership changes to the upper layer.*/

                CANIF_ENTER_CRITICAL_SECTION();

                CanIf_MemCpy(PduInfoPtr->SduDataPtr,
                             CanIfRxBufferSduData[CanRxPduId],
                             (CanIfRxBufferSduLength[CanRxPduId]));
                PduInfoPtr->SduLength = CanIfRxBufferSduLength[CanRxPduId];

                CANIF_LEAVE_CRITICAL_SECTION();

                ret = E_OK ;
            }
        }

    }
    return ret;
}
#endif

#if (STD_ON == CANIF_PUBLIC_VERSION_INFO_API)
void CanIf_GetVersionInfo(Std_VersionInfo_Type *VersionInfo) {
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfo) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETVERSIONINFO,
                        CANIF_E_PARAM_POINTER);
    } else
#endif

    {
        /* Copy the vendor Id */
        VersionInfo->vendorID = CANIF_VENDOR_ID_VALUE;
        /* Copy the module Id */
        VersionInfo->moduleID = CANIF_MODULE_ID_VALUE;
        /* Copy the instance Id */
        VersionInfo->instanceID = CANIF_INSTANCE_ID_VALUE_0;
        /* Copy Software Major Version */
        VersionInfo->sw_major_version = CANIF_SW_MAJOR_VERSION_VALUE;
        /* Copy Software Minor Version */
        VersionInfo->sw_minor_version = CANIF_SW_MINOR_VERSION_VALUE;
        /* Copy Software Patch Version */
        VersionInfo->sw_patch_version = CANIF_SW_PATCH_VERSION_VALUE;
    }

}
#endif

void CanIf_TxConfirmation(PduIdType CanTxPduId) {
#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
    uint8 i;
    Can_ReturnType Can_RetVal;
#endif
#if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
    uint8 tempMode;
#endif

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TXCONFIRMATION_APIID,
                        CANIF_E_UNINIT);
    } else if (CanTxPduId >= CanIf_TotalTxPduIds) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TXCONFIRMATION_APIID,
                        CANIF_E_INVALID_TXPDUID);
    } else
#endif

    {
#if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
        tempMode = (uint8)CanIfPduMode[CANIF_CANCONTROLLER_TX];
        if (0U != (tempMode & CANIF_TX_NOTIFY_ENABLE_MASK))
#endif
        {
            if (NULL_PTR != CanIfTxPduConfig[CanTxPduId].TxConfirmation) {
#if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
                (CanIfTxPduConfig[CanTxPduId].TxConfirmation)
                (CanIfTxPduConfig[CanTxPduId].UpperLayerHandle);
#else
                (CanIfTxPduConfig[CanTxPduId].TxConfirmation)(CanTxPduId);
#endif
            }
            /*
            If configuration parameters CANIF_READTXPDU_NOTIFY_STATUS_API
            (CANIF609_Conf) and CANIF_READTXPDU_NOTIFY_STATUS CANIF589_Conf for
            the transmitted L-PDU are set to TRUE, and if CanIf_TxConfirmation()
            is called, then the CanIf shall set the notification status for the
            transmitted L-PDU.
            */
#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
            if (TRUE == CanIfTxPduConfig[CanTxPduId].TxPduReadNotifyStatus) {
                CanIfTxNotifStatus[CanTxPduId] = CANIF_TX_RX_NOTIFICATION;
            }
#endif

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
            /*After one HTH is free,CANIF shoule initiate a new transmit request
            of that pending CanIf Tx L-PDU*/
            if (0U != CanIfTxBufferFillCount) {
                for (i = 0U; i < CanIf_TotalTxPduIds; i++) {
                    if ((CanIfTxPduConfig[i].Hth ==
                            CanIfTxPduConfig[CanTxPduId].Hth)
                            && (TRUE == CanIfTxBufferPDUFillflag[i])) {
                        Can_RetVal = Can_Write(CanIfTxPduConfig[i].Hth,
                                               &CanIfTxBufferPdu[i]);
                        if (CAN_OK == Can_RetVal) {
                            CanIfTxBufferPDUFillflag[i] = FALSE;
                            CanIfTxBufferFillCount--;
                        }

                        break; /*jump out ,only send once*/
                    }
                }
            }
#endif /*end of #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)*/

        }

    }

}

void CanIf_RxIndication(Can_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr) {
    PduIdType    handle;
    PduIdType    canIfRxPduId;
    PduInfoType  CanIf_PduRRxPduInfo;
    uint8 handleGetFlag = 0U;
#if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
    uint8 tempMode;
#endif
    uint8 dlcResult;
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    Std_ReturnType parResult;

    parResult = CanIf_RxParCheck(Hrh, CanId, CanDlc, CanSduPtr);
    if (E_OK == parResult)
#endif
    {
#if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
        tempMode = (uint8)CanIfPduMode[CANIF_CANCONTROLLER_RX];
        if (0U != (tempMode & CANIF_RX_INDICATION_ENABLE_MASK))
#endif
        {
#if(STD_ON == CANIF_HRH_RANGE_FILTER)
            if (((CanId >= CANIF_MSK_EXT_ID_MSB) && (STANDARD_CAN == CANIF_HRH_CANID_TYPE))
                    || ((CanId < CANIF_MSK_EXT_ID_MSB) && (EXTENDED_CAN == CANIF_HRH_CANID_TYPE))
                    || (CanId < CANIF_HRH_LOWER_CANID) || (CanId > CANIF_HRH_UPPER_CANID)) {
            } else
#endif

            {

#if(CANIF_FILTER_TYPE_INDEX == \
                                             CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
                for (handle = CanIfHrhFirstRxPduID[Hrh];
                        CANIF_LAST_HRH_RXPDUID != handle;
                        handle = CanIfRxPduConfig[handle].HrhNextRxPduID)
#else
                for (handle = 0U; handle < CanIf_TotalRxPduIds; handle++)
#endif

                {
#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
                    if (NULL_PTR != CANIF_RXPDU_RANGECFG) {
                        if ((CanId >= CANIF_RXPDU_RANGECFG->RxPduCanIdRangeLowerCanId)
                                && (CanId <= CANIF_RXPDU_RANGECFG->RxPduCanIdRangeUpperCanId)) {
                            handleGetFlag = 1U;
                        }
                    } else
#endif
                    {
                        if (((CanIfRxPduConfig[handle].CanId) == CanId)
                                && ((CanIfRxPduConfig[handle].Hrh) == Hrh)) {
                            handleGetFlag = 1U;
                        }
                    }
                    if (1U == handleGetFlag) {
                        break;
                    }
                }
#if(CANIF_FILTER_TYPE_INDEX == \
                                            CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)

                if (CANIF_LAST_HRH_RXPDUID != handle)
#else

                if (handle < CanIf_TotalRxPduIds)

#endif
                {
#if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
                    canIfRxPduId = CanIfRxPduConfig[handle].UpperLayerHandle ;
#else
                    canIfRxPduId = handle;
#endif

                    dlcResult = CanIf_DlcCheck(CanDlc, handle,
                                               &CanIf_PduRRxPduInfo.SduLength);
                    if (E_NOT_OK == dlcResult) {
                        /*abort this message*/
                        // Dem_ReportErrorStatus(
                        //CANIF_E_INVALID_DLC,
                        //DEM_EVENT_STATUS_FAILED
                        //);
                    } else {
                        /**********************************************************
                        * PRQA S 0311   MISRA-C:2004 Rule 11.5
                        * Pointer cast lost const qualification.
                        * This cast is to fulfill the AUTOSAR RxIndication API
                        * between CanIf and uplayer service moudle.
                        * This part of code is verified manually and has no impact.
                        **********************************************************/
                        CanIf_PduRRxPduInfo.SduDataPtr = (uint8 *)CanSduPtr;

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
                        if (TRUE == CanIfRxPduConfig[handle].RxPduReadNotifyStatus) {
                            CanIfRxNotifStatus[handle] = CANIF_TX_RX_NOTIFICATION;
                        }
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)

                        if (TRUE == CanIfRxPduConfig[handle].RxPduReadData) {
#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
                            /*CanIf_ReadRxPduData must not be used for
                            CanRxPduIds, which are defined to receive multiple
                            CAN-Ids (range reception)*/
                            if (NULL_PTR ==
                                    CanIfRxPduConfig[handle].RxPduCanIdRangeCfg)
#endif
                            {
                                /*If the CanIf has accepted a L-PDU received
                                via CanIf_RxIndication() during DLC check,
                                the CanIf shall copy the number of bytes
                                according to the configured DLC valueto the
                                static receive buffer, if configured for that
                                L-PDU , or allow copying the data to the upper
                                layer modules.*/

                                CanIf_MemCpy(
                                    CanIfRxBufferSduData[handle],
                                    CanSduPtr,
                                    CanIf_PduRRxPduInfo.SduLength);

                                CanIfRxBufferSduLength[handle] =
                                    CanIf_PduRRxPduInfo.SduLength;
                            }
                        }
#endif

#if (STD_ON==CANIF_RX_PDU_RANGE_CANID)
                        if (NULL_PTR != CANIF_RXPDU_RANGECFG) {
                            if (NULL_PTR != CANIF_RXPDU_RANGECFG->RangeRxIndication) {
                                (CANIF_RXPDU_RANGECFG->RangeRxIndication)
                                ( canIfRxPduId, CanId, &CanIf_PduRRxPduInfo);
                            }
                        } else
#endif
                        {
                            if (NULL_PTR != CanIfRxPduConfig[handle].RxIndication) {
                                (CanIfRxPduConfig[handle].RxIndication)
                                (canIfRxPduId, &CanIf_PduRRxPduInfo);

                            }
                        }


                    }

                }

            }

        }

    }

}

#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON)
void CanIf_CancelTxConfirmation(const Can_PduType *PduInfoPtr) {
    PduIdType CanTxPduId;

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CANCELTXCONFIRMATION_APIID,
                        CANIF_E_UNINIT);
    } else if (NULL_PTR == PduInfoPtr) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CANCELTXCONFIRMATION_APIID,
                        CANIF_E_PARAM_POINTER);
    } else
#endif
    {
        CanTxPduId = PduInfoPtr->swPduHandle;
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
        if (CanTxPduId >= CanIf_TotalTxPduIds) {
            Det_ReportError(CANIF_MODULE_ID_VALUE,
                            CANIF_INSTANCE_ID_VALUE_0,
                            CANIF_CANCELTXCONFIRMATION_APIID,
                            CANIF_E_INVALID_TXPDUID);
        } else
#endif
        {
#if(STD_ON == CANIF_PUBLIC_TX_BUFFERING)
            /*CanIfTxBufferFillCount is used for counting the num of
            CanIfTxBufferPdu which is used*/
            if (FALSE == CanIfTxBufferPDUFillflag[CanTxPduId]) {
                CANIF_ENTER_CRITICAL_SECTION();
                CanIfTxBufferPDUFillflag[CanTxPduId] = TRUE;
                CanIfTxBufferFillCount++;

                /*CANIF054: When callback notification service
                CanIf_CancelTxConfirmation() is called,
                the CanIf shall store the aborted old L-PDU, which is referenced
                in parameter PduInfoPtr of CanIf_CancelTxConfirmation(), inside
                its transmit L-PDU buffer as long it is configured and free.*/
                /*This way of L-PDU storage ensures to keep the latest data of
                several pending transmit L-PDUs with the same L-PDU handle
                inside the CanIf's transmit L-PDU buffers.*/
                CanIf_MemCpy(CanIfTxBufferSdu[CanTxPduId],
                             PduInfoPtr->sdu,
                             (uint32)PduInfoPtr->length);

                CanIfTxBufferPdu[CanTxPduId].id = PduInfoPtr->id;
                CanIfTxBufferPdu[CanTxPduId].length = PduInfoPtr->length;
                CanIfTxBufferPdu[CanTxPduId].sdu = CanIfTxBufferSdu[CanTxPduId];
                CanIfTxBufferPdu[CanTxPduId].swPduHandle
                    = PduInfoPtr->swPduHandle;
                CANIF_LEAVE_CRITICAL_SECTION();
            }
#endif

        }

    }

}
#endif

void CanIf_ControllerBusOff(uint8 Controller) {
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERBUSOFF_APIID,
                        CANIF_E_UNINIT);
    } else if (Controller >= CANIF_USED_CONTROLLER_NUM) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERBUSOFF_APIID,
                        CANIF_E_PARAM_CONTROLLER);
    } else
#endif

    {
        /*******************************************************************
        * PRQA S 3138   MISRA-C:2004 Rule 14.3
        * PRQA S 3141
        * If not configed by user,CANIF_USERCTRLBUSOFF_FUN is Null.
        * This part of code is verified manually and has no impact.
        *******************************************************************/
        CANIF_USERCTRLBUSOFF_FUN;
#if(STD_ON == CANIF_SUPPORT_OSEK_NM)
        CanNm_BusOff(Controller);
#else
        (void)Controller;
#endif

    }

}

void CanIf_ControllerWakeUp(uint8 Controller) {
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)

    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERBUSOFF_APIID,
                        CANIF_E_UNINIT);
    } else if (Controller >= CANIF_USED_CONTROLLER_NUM) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERBUSOFF_APIID,
                        CANIF_E_PARAM_CONTROLLER);
    } else
#endif
    {
        /*******************************************************************
        * PRQA S 3138   MISRA-C:2004 Rule 14.3
        * PRQA S 3141
        * If not configed by user,CANIF_USERWAKEUP_FUN is Null.
        * This part of code is verified manually and has no impact.
        *******************************************************************/
        CANIF_USERWAKEUP_FUN;

#if(STD_ON == CANIF_SUPPORT_OSEK_NM)
        CanNm_WakeUp(Controller);
#else
        (void)Controller;
#endif
    }
}

void CanIf_ControllerModeIndication(uint8 Controller, CanIf_ControllerModeType ControllerMode) {
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if (CANIF_UNINITIALIZED == CanIf_InitStatus) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERMODEINDICATION_APIID,
                        CANIF_E_UNINIT);
    } else if (Controller >= CANIF_USED_CONTROLLER_NUM) {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERMODEINDICATION_APIID,
                        CANIF_E_PARAM_CONTROLLER);
    } else
#endif
    {
        switch (ControllerMode) {
        case CANIF_CS_SLEEP:
            CanIf_ControllerMode[Controller] = CANIF_CS_SLEEP;
            break;

        case CANIF_CS_STARTED:
            CanIf_ControllerMode[Controller] = CANIF_CS_STARTED;
            break;

        case CANIF_CS_STOPPED:
            CanIf_ControllerMode[Controller] = CANIF_CS_STOPPED;
            break;

        case CANIF_CS_UNINIT:

            break;

        default:

            break;
        }

    }

}

#if(STD_ON == CANIF_PUBLIC_TX_BUFFERING)
void CanIf_ClearTransmitBuffer(uint8 ControllerId) {
    Can_HwHandleType CanTxPduId;
    for (CanTxPduId = 0U; CanTxPduId < CanIf_TotalTxPduIds; CanTxPduId++) {
        if (CANIF_CONTROLLER_ID == CANIF_CANCONTROLLER_TX) {
            if (TRUE == CanIfTxBufferPDUFillflag[CanTxPduId]) {
                CanIfTxBufferFillCount--;
                CanIfTxBufferPDUFillflag[CanTxPduId] = FALSE;
            }
        }
    }
}
#endif

/*lint -restore*/
