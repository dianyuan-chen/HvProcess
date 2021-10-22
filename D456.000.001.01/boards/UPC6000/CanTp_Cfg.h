#ifndef _CANTP_CFG_H_
#define _CANTP_CFG_H_

#include  "CanIf.h"
#include  "Dcm_Cbk.h"
#include  "PduR.h"
#define CANTP_DEV_ERROR_CHECK         STD_OFF
#define CANTP_DEV_ERROR_REPORT        STD_OFF
#define CANTP_VERSION_INFO_API        STD_OFF
#define CANTP_TC                      STD_ON
#define CANTP_RC                      STD_OFF
#define CANTP_CHANGE_PARAMETER_API    STD_OFF
#define CANTP_SHUTDOWN_API            STD_OFF
#define CANTP_MAIN_FUNCTION_PERIOD    (2u)

#define CANTP_FILLPATTERN    ((uint8)0x00u)
#define CANTP_CHANNELS         (5u)

//#define CANTP_RXSDU_PADDING_ENABLE
#define CANTP_RXSDU_PADDING_DISABLE
#define CANTP_RXSDU_TXFC_PADDING_ENABLE
//#define CANTP_RXSDU_TXFC_PADDING_DISABLE


#if defined(CANTP_RXSDU_PADDING_ENABLE)&& defined(CANTP_RXSDU_PADDING_DISABLE)
#error "none or one kind of RXSDU padding can be defined"
#endif

#define CANTP_TXSDU_PADDING_ENABLE
//#define CANTP_TXSDU_PADDING_DISABLE
//#define CANTP_TXSDU_RXFC_PADDING_ENABLE
#define CANTP_TXSDU_RXFC_PADDING_DISABLE

#if defined(CANTP_TXSDU_PADDING_ENABLE)&& defined(CANTP_TXSDU_PADDING_DISABLE)
#error "none or one kind of TXSDU padding can be defined"
#endif

#define CANTP_ADDRESSING_STANDARD_ONLY

#if defined(CANTP_ADDRESSING_STANDARD_ONLY)
#if defined(CANTP_ADDRESSING_EXTENDED_ONLY)|| defined(CANTP_ADDRESSING_MIX_ONLY)
#error "Exist more than one adressing"
#endif
#endif
#define CANTP_CHANNEL_HALF_DUPLEX_ONLY
#if defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY)&& defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
#error "only one channel mode can be defined"
#endif

#if(CANTP_CHANNELS>0u)
#else
#error "The "CANTP_CHANNELS" should not be 0"
#endif

extern const PduIdType CANTP_NUM_RX_SDUS;
extern const PduIdType CANTP_NUM_TX_SDUS;

#define CANTP_NUM_RX_CHANNELS               ((PduIdType)CANTP_CHANNELS)
#define CANTP_NUM_TX_CHANNELS               ((PduIdType)CANTP_CHANNELS)

#define CanTp_CanInterruptDisable()  CANIF_ENTER_CRITICAL_SECTION()/* DisableInterrupts; */
#define CanTp_CanInterruptRestore()  CANIF_LEAVE_CRITICAL_SECTION()/* EnableInterrupts;  */

#define CanTp_CanTransmit(txSduIdx,pduInfo)    CanIf_Transmit(txSduIdx,pduInfo)
#define CanTp_CanCancelTransmit(txSduIdx)    CanIf_CancelTransmit(txSduIdx)
#define CanTp_NUSDataIndication(rxSduIdx,canTpErrorCode)     PduR_CanTpRxIndication(rxSduIdx,canTpErrorCode)
#define CanTp_NUSDataConfirm(txSduIdx,canTpErrorCode)     PduR_CanTpTxConfirmation(txSduIdx,canTpErrorCode)
#define CanTp_NUSDataFFIndication(rxSduIdx,length,bufferSizePtr)     PduR_CanTpStartOfReception(rxSduIdx,length,bufferSizePtr)
#define CanTp_NUSDataSFIndication(rxSduIdx,length,bufferSizePtr)     PduR_CanTpStartOfReception(rxSduIdx,length,bufferSizePtr)
#define CanTp_CopyRxData(rxSduIdx,pduInfo,bufferSizePtr)      PduR_CanTpCopyRxData(rxSduIdx,pduInfo,bufferSizePtr)
#define CanTp_CopyTxData(txSduIdx,pduInfo,NULL_PTR,bufferSizePtr)      PduR_CanTpCopyTxData(txSduIdx,pduInfo,NULL_PTR,bufferSizePtr)

#endif
