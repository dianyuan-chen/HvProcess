#ifndef ATCMD_ABSTRACT___H__
#define ATCMD_ABSTRACT___H__

#include "Std_Types.h"
#include "ucos_ii.h"

typedef struct {
    /// 期望应答的起始字符串.
    const char *expect;
    /// 用于保存匹配的应答行的缓存.
    char *recvBuffer;
    /// 缓存大小.
    uint8 recvLen;
} ATCMD_Expect;


typedef uint16 (*ATCMD_CopySendData)(uint8 *buf, uint16 len);
typedef struct ATCmd_Data ATCmd_DataType;

typedef Std_ReturnType (*ATCMD_InitType)(const void *private_data);
typedef Std_ReturnType (*ATCMD_ExecCommandType)(void *private_data, const char *atcmd, const ATCMD_Expect *exp, uint32 timeoutTick) ;
typedef Std_ReturnType (*ATCMD_GetCIMIType)(void *private_data, char *buf, uint8 len);
typedef Std_ReturnType (*ATCMD_GetIMEIType)(void *private_data, char *buf, uint8 len);
typedef Std_ReturnType (*ATCMD_ConnectTcpServerType)(ATCmd_DataType *ATCmd_Data, void *private_data, const char *addr, uint16 port);
typedef Std_ReturnType (*ATCMD_DisconnectTcpServerType)(void *private_data);
typedef Std_ReturnType (*ATCMD_SendSMSType)(void *private_data, const char *dest, const char *msg) ;
typedef Std_ReturnType (*ATCMD_SendDataViaGPRSCallbackType)(void *private_data, ATCMD_CopySendData copySendData, uint16 total_len);
typedef Std_ReturnType (*ATCMD_GetSignalQualityType)(void *private_data, uint8 *rssi, uint8 *ber);
typedef Std_ReturnType (*ATCMD_GetDataSentInfoType)(void *private_data, uint32 *sent, uint32 *acked, uint32 *unacked);
typedef Std_ReturnType (*ATCMD_GetOPSType)(void *private_data, char *buf, uint8 len);
typedef Std_ReturnType (*ATCMD_GetVoltageType)(void *private_data, uint16 *vol);
typedef Std_ReturnType (*ATCMD_GetLacCiType)(void *private_data, uint32 lac_ci[2]);
typedef Std_ReturnType (*ATCMD_GetCellLocType)(void *private_data, sint32 loc[2]);
typedef Std_ReturnType (*ATCMD_SetApn)(void *private_data, const char *atcmd);


typedef struct {
    ATCMD_InitType Init;
    ATCMD_ConnectTcpServerType ConnectTcpServer;
    ATCMD_SendDataViaGPRSCallbackType SendDataViaGPRSCallback;
    ATCMD_GetDataSentInfoType GetDataSentInfo;
    ATCMD_GetOPSType GetOPS;
    ATCMD_GetLacCiType GetLacCi;
    ATCMD_ExecCommandType ExecCommand;
    ATCMD_GetCIMIType GetCIMI;
    ATCMD_GetIMEIType GetIMEI;
    ATCMD_DisconnectTcpServerType DisconnectTcpServer;
    ATCMD_SendSMSType SendSMS;
    ATCMD_GetSignalQualityType GetSignalQuality;
    ATCMD_GetVoltageType GetVoltage;
    ATCMD_GetCellLocType GetCellLoc;
    ATCMD_SetApn SetApn;
} ATCmd_OperationsType;

struct ATCmd_Data {
    void *private_data;
    const ATCmd_OperationsType *ops;
};


#define ATCMD_Init(at) (at)->ops->Init((at)->private_data)
#define ATCMD_ExecCommand(at,atcmd,exp, timeoutTick) (at)->ops->ExecCommand((at)->private_data, atcmd, exp, timeoutTick)
#define ATCMD_GetCIMI(at,buf,len) (at)->ops->GetCIMI((at)->private_data,buf,len)
#define ATCMD_GetIMEI(at,buf, len) (at)->ops->GetIMEI((at)->private_data,buf, len)
#define ATCMD_ConnectTcpServer(at,addr, port) (at)->ops->ConnectTcpServer((ATCmd_DataType *)(at),(at)->private_data,addr, port)
#define ATCMD_DisconnectTcpServer(at) (at)->ops->DisconnectTcpServer((at)->private_data)
#define ATCMD_SendSMS(at, dest, msg) (at)->ops->SendSMS((at)->private_data, dest, msg)
#define ATCMD_SendDataViaGPRSCallback(at,copySendData, total_len) (at)->ops->SendDataViaGPRSCallback((at)->private_data,copySendData, total_len)
#define ATCMD_GetSignalQuality(at, rssi, ber) (at)->ops->GetSignalQuality((at)->private_data, rssi, ber)
#define ATCMD_GetDataSentInfo(at,sent, acked, unacked) (at)->ops->GetDataSentInfo((at)->private_data,sent, acked, unacked)
#define ATCMD_GetOPS(at, buf,len) (at)->ops->GetOPS((at)->private_data, buf, len)
#define ATCMD_GetVoltage(at,vol) (at)->ops->GetVoltage((at)->private_data, vol)
#define ATCMD_GetLacCi(at,lac_ci) (at)->ops->GetLacCi((at)->private_data, lac_ci)
#define ATCMD_GetCellLoc(at,loc) (at)->ops->GetCellLoc((at)->private_data, loc)
#define ATCMD_SetApn(at,apn) (at)->ops->SetApn((at)->private_data, apn)

Std_ReturnType ATCMD_RetryUntilExpect(const ATCmd_DataType *at, const char *atcmd, const char *expect, uint8 times, uint16 timeout);
Std_ReturnType ATCMD_RetryUntilExpects(const ATCmd_DataType *at, const char *atcmd, const char *const *expects, uint16 times, uint16 timeout);

#endif