#ifndef _CANTP_H_
#define _CANTP_H_

#include "ComStack_Types.h"
#include "CanTp_Cfg.h"

#define CANTP_VENDOR_ID             (uint16 )(0x0000u)
#define CANTP_MODULE_ID             (uint16 )(0x0000u)
#define CANTP_INSTANCE_ID           ((uint8 )0)

#define CANTP_SW_MAJOR_VERSION      (uint8 )(0x01u)
#define CANTP_SW_MINOR_VERSION      (uint8 )(0x00u)
#define CANTP_SW_PATCH_VERSION      (uint8 )(0x00u)

#define CANTP_AR_MAJOR_VERSION      (uint8 )(0x01u)
#define CANTP_AR_MINOR_VERSION      (uint8 )(0x00u)
#define CANTP_AR_PATCH_VERSION      (uint8 )(0x00u)

#define CANTP_MODE_HALF_DUPLEX      ((uint8 )0x00u)
#define CANTP_MODE_FULL_DUPLEX      ((uint8 )0x01u)

#define CANTP_MAX_FRAME_LENGTH            8u
#define CANTP_MAX_FRAME_LENGTH_uint8 ((uint8 )CANTP_MAX_FRAME_LENGTH)
#define CANTP_MAX_FRAME_LENGTH_uint16 ((uint16 )CANTP_MAX_FRAME_LENGTH)

#define CANTP_UNUSED                (0xFFu)

#define CANTP_AR_RELEASE_MAJOR_VERSION          (1u)
#define CANTP_AR_RELEASE_MINOR_VERSION          (0u)
#define CANTP_AR_RELEASE_REVISION_VERSION       (0u)



#define CANTP_INSTANCE_ID_DET                   (0x00u)

#define CANTP_SID_INIT                           (0x01u)
#define CANTP_SID_SHUTDOWN                       (0x02u)
#define CANTP_SID_TRANSMIT                       (0x03u)
#define CANTP_SID_RXINDICATION                   (0x42u)
#define CANTP_SID_TXCONFIRMATION                 (0x05u)
#define CANTP_SID_MAINFUNCTION                   (0x06u)
#define CANTP_SID_GETVERSIONINFO                 (0x07u)
#define CANTP_SID_CANCELTRANSMIT                 (0x08u)
#define CANTP_SID_CANCELRECEIVE                  (0x09u)
#define CANTP_SID_CHANGEPARAMETER                (0x0Au)
#define CANTP_SID_READPARAMETER                  (0x0Bu)
#define CANTP_SID_MAINFUNCTIONRX                 (0x20u)
#define CANTP_SID_MAINFUNCTIONTX                 (0x21u)

#define CANTP_SID_RXGETBUFFER                    (0x30u)
#define CANTP_SID_TXGETBUFFER                    (0x31u)
#define CANTP_SID_RXTRANSMITFRAME                (0x32u)
#define CANTP_SID_TXTRANSMITFRAME                (0x33u)
#define CANTP_SID_RXINIT                         (0x34u)
#define CANTP_SID_TXINIT                         (0x35u)
#define CANTP_SID_STOPSEPARATIONTIME             (0x36u)

#define CANTP_E_NO_ERROR            0x00
#define CANTP_E_INVALID_CHANNEL     0xFE
#define CANTP_E_INVALID_ADDRESS     0xFD

#define CANTP_E_PARAM_CONFIG        0x01
#define CANTP_E_PARAM_ID            0x02
#define CANTP_E_PARAM_POINTER       0x03
#define CANTP_E_UNINIT              0x20
#define CANTP_E_INVALID_TX_ID       0x30
#define CANTP_E_INVALID_RX_ID       0x40
#define CANTP_E_INVALID_TX_BUFFER   0x50
#define CANTP_E_INVALID_RX_BUFFER   0x60
#define CANTP_E_INVALID_TX_LENGTH   0x70
#define CANTP_E_INVALID_RX_LENGTH   0x80
#define CANTP_E_INVALID_TATYPE      0x90
#define CANTP_E_OPER_NOT_SUPPORTED  0xA0
#define CANTP_E_COM                 0xB0
#define CANTP_E_RX_COM              0xC0
#define CANTP_E_TX_COM              0xD0

#if (CANTP_DEV_ERROR_REPORT == STD_ON)
#define CanTp_DetReportError(ApiId, ErrorId) ((void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID_DET, (ApiId), (ErrorId) )) /* PRQA S 3412 */ /* MD_CanTp_3412 */
#else
#define CanTp_DetReportError(ApiId, ErrorId)
#endif

/* 数据结构定义 */
typedef enum {
    CANTP_OFF = 0,
    CANTP_ON = 1u
} CanTpInternalState;

typedef enum {
    CANTP_RX_CHANNEL = 0,
    CANTP_TX_CHANNEL = 1u
} CanTpChannelType;


typedef enum {
    CANTP_STANDARD = 0,
    CANTP_EXTENDED = 1u,
    CANTP_MIXED = 2u
} CanTpAddressingFormat;

typedef enum {
    CANTP_PHYSICAL = 0,
    CANTP_FUNCTIONAL = 1u
} CanTpTaType;

typedef enum {
    CANTP_BS_PARAMETER = 0,
    CANTP_STMIN_PARAMETER = 1u
} CanTpParameterType;


/* 配置数据结构定义 */
typedef struct {
    PduIdType CanTpChannelId;
    PduIdType CanTpRxNPduId;
    PduIdType CanTpTxFcNPduId;
    uint16 CanTpNar;
    uint16 CanTpNbr;
    uint16 CanTpNcr;
#if !defined(CANTP_RXSDU_PADDING_ENABLE)&&!defined(CANTP_RXSDU_PADDING_DISABLE)
    uint8 CanTpRxPaddingActive;
#endif
    CanTpTaType CanTpRxTaType;
#if !defined(CANTP_ADDRESSING_STANDARD_ONLY)&&!defined(CANTP_ADDRESSING_EXTENDED_ONLY)&&!defined(CANTP_ADDRESSING_MIX_ONLY)
    CanTpAddressingFormat          CanTpRxAddrFormat;
#endif
    uint8 CanTpBs;
    uint8 CanTpSTmin;
    uint8 CanTpRxWftMax;
    uint8 CanTpRxNAe;
    uint8 CanTpRxNSa;
    uint8 CanTpRxNTa;
} CanTp_RxNsduCfgType;

typedef struct {
    PduIdType CanTpChannelId;
    PduIdType CanTpTxNPduId;
    PduIdType CanTpRxFcNPduId;
    uint16 CanTpNas;
    uint16 CanTpNbs;
    uint16 CanTpNcs;
#if !defined(CANTP_TXSDU_PADDING_ENABLE)&&!defined(CANTP_TXSDU_PADDING_DISABLE)
    uint8 CanTpTxPaddingActive;
#endif
    CanTpTaType CanTpTxTaType;
#if !defined(CANTP_ADDRESSING_STANDARD_ONLY)&&!defined(CANTP_ADDRESSING_EXTENDED_ONLY)&&!defined(CANTP_ADDRESSING_MIX_ONLY)
    CanTpAddressingFormat          CanTpTxAddrFormat;
#endif
    uint8 CanTpTxNAe;
    uint8 CanTpTxNSa;
    uint8 CanTpTxNTa;
} CanTp_TxNsduCfgType;


typedef struct {
    uint8 CanTpChannelMode;
} CanTp_ChannelModeType;

typedef struct {
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
    const CanTp_ChannelModeType *const CanTp_ChannelMode;
#endif
    const CanTp_RxNsduCfgType *const CanTp_RxNsduCfg;
    const CanTp_TxNsduCfgType *const CanTp_TxNsduCfg;
} CanTp_ConfigType;

/* 内部数据结构定义 */
typedef struct {
    PduInfoType RxNPduInfo;
    PduIdType CurrentRxSduId;
    PduLengthType DataLength;
    PduLengthType MinBuffSize;
    PduLengthType AvailableBufLength;
    uint16 Timer;
    uint8 ChannelState;
    uint8 WFTCounter;
    uint8 BlockSizeCounter;
    uint8 BlockSize;
    uint8 STMin;
    uint8 FlowStatus;
    uint8 ExpectedSN;
    uint8 ChannelLastState;
    uint8 RxErrorType;
    uint8 RxFormatOffset;
    uint8 *RxBufPtr;
    uint8 *TxFCPtr;
    uint8 RxData[CANTP_MAX_FRAME_LENGTH];
    uint8 FCData[CANTP_MAX_FRAME_LENGTH];

} CanTp_RxStateType;

typedef struct {
    PduInfoType TxNPduInfo;
    PduIdType CurrentTxSduId;
    PduLengthType DataLength;
    PduLengthType RemainTxDataCnt;
    uint16 Timer;
    uint8 ChannelState;
    uint8 BlockSizeCounter;
    uint8 STMin;
    uint8 SeqNumber;
    uint8 TxFormatOffset;
    uint8 TxData[CANTP_MAX_FRAME_LENGTH];
} CanTp_TxStateType;

typedef struct {
    const CanTp_RxNsduCfgType *pRxNsduCfg;
    const CanTp_TxNsduCfgType *pTxNsduCfg;
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
    const CanTp_ChannelModeType *pChnModeCfg;
#endif
    CanTp_RxStateType *pRxState;
    CanTp_TxStateType *pTxState;
    CanTpInternalState InternalState; /* keep track of the initialization status */
} CanTp_AdminDataType;


typedef struct {
    const CanTp_RxNsduCfgType *_pRxSduCfg;
    const CanTp_TxNsduCfgType *_pTxSduCfg;
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
    const CanTp_ChannelModeType *_pChnMdCfg;
#endif
    CanTp_RxStateType *rxChannelState;
    CanTp_TxStateType *txChannelState;
    uint8 *_pTmpData;
    PduIdType _sduid;
    PduLengthType _candlc;
} CanTp_ContextType;

extern void CanTp_Init(const CanTp_ConfigType *const pCfgPtr);

#if(CANTP_SHUTDOWN_API == STD_ON)
extern void CanTp_Shutdown(void);
#endif
extern void CanTp_MainFunction(void);
extern Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType *CanTpTxInfoPtr);

#if (CANTP_TC == STD_ON)
extern Std_ReturnType CanTp_CancelTransmit(PduIdType CanTpTxSduId);
#endif

#if(CANTP_RC == STD_ON)
extern Std_ReturnType CanTp_CancelReceive(PduIdType CanTpRxSduId);
#endif

extern Std_ReturnType CanTp_ChangeParameter(PduIdType CanTpSduId, CanTpParameterType parameter, uint16 value);

#if (CANTP_VERSION_INFO_API == STD_ON)
extern void CanTp_GetVersionInfo(Std_VersionInfoType *VersionInfo);
#endif

extern const CanTp_ConfigType/*CANTP_CONFIG_CONST*/ CanTp_Cfg;

#endif
