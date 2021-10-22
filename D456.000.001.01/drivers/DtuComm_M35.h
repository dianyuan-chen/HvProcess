#ifndef DTUCOMM_M35_H
#define DTUCOMM_M35_H

#include "Std_Types.h"
#include "Dio.h"
#include "dtu_atcmd.h"
#include "Uart.h"
#include "ComStack_Types.h"
#include "DtuComm_M35_Platform.h"

#define DTU_MODULE_IS_MC20 0x01U
#define DTU_MODULE_IS_EC20 0x02U

void DtuM35_MainLoop(const DtuCommM35_ConfigType *config);

enum {
    DTUM35_RUNTIME_STATUS_UNKNOWN,
    DTUM35_RUNTIME_STATUS_POWERUP,
    DTUM35_RUNTIME_STATUS_CONFIGURE,
    DTUM35_RUNTIME_STATUS_WAIT_REGISTER,
    DTUM35_RUNTIME_STATUS_SEND_SMS,
    DTUM35_RUNTIME_STATUS_CONNECT_SERVER,
    DTUM35_RUNTIME_STATUS_GET_SIGNAL_QUALITY,
    DTUM35_RUNTIME_STATUS_CHECK_CONNECTION,
    DTUM35_RUNTIME_STATUS_WAIT_EVENT,
    DTUM35_RUNTIME_STATUS_SEND_DATA,
    DTUM35_RUNTIME_STATUS_RECV_DATA,
    DTUM35_RUNTIME_STATUS_RECV_SMS,
    DTUM35_RUNTIME_STATUS_DELAT_TO_RESTART,
    DTUM35_RUNTIME_STATUS_SIM_INIT,
};

/// \brief DtuM35_GetRunTimeStatus 获取运行状态.
///
/// \param index 运行状态的序号, 0当前运行状态, 1上一次重启的最后状态, 2上上次重启的错误状态...
///
/// \return 运行状态.
uint8 DtuM35_GetRuntimeStatus(uint8 index);
void DtuM35_GetRuntimeStatusAll(uint8 *buf, uint8 buffer_len);

/// \brief DtuM35_SendData 通过DTUM35这个功能模块发送数据.
///
/// \param dat 需要发送的数据.
/// \param len 数据的长度.
/// \param isMaster 是否为主机数据.
/// \return 保存到发送缓冲的长度.
//uint16 DtuM35_SendData(const uint8 *dat, uint16 len, uint8 isMaster);


//uint8 DtuM35_SendDataWithCallback(struct DtuM35_SendDataInfo *info);


/// DTU运营商列表.

/// 未知运营商.
#define DTU_OPS_UNKNOWN   0U
/// 中国联通.
#define DTU_OPS_CHINA_UNIONCOM  1U
/// 中国移动.
#define DTU_OPS_CHINA_MOBILE   2U
/// 中国电信.
#define  DTU_OPS_CHINA_TELECOM   3U

/// \brief DtuM35_GetOPS 获取注册的网络的运营商.
///
/// \return DTU_OPS定义的运营商.
uint8 DtuM35_GetOPS(void);

/// \brief DtuM35_GetSingalQuality 获取信号强度及误码率.
///
/// \param strength 信号强度存储在这个指针指向的字节.
/// \param err_rate 误码率存储在这个指针指向的字节.
void DtuM35_GetSingalQuality(uint8 *strength, uint8 *err_rate);

/// \brief DtuM35_GetLacCi 获取注册的基站的LAC和CI．
///
/// \param lacci[2]　LAC,CI存储在这个指针指向的内存, 先存LAC, 再存CI.
void DtuM35_GetLacCi(uint32 lacci[2]);

/// \brief DtuM35_GetLoc 获取注册的基站的LOC．
///
/// \param loc[2]　LAC,CI存储在这个指针指向的内存, 先存LAC, 再存CI.
void DtuM35_GetLoc(sint32 loc[2]);

/// \brief DtuM35_GetCCID 获取SIM卡的唯一标识.
///
/// \param ccid CCID存储在这个指针指向的内存.
/// \param len ccid这个内存的长度, 防止越界操作.
void DtuM35_GetCCID(char *ccid, uint8 len);

/// \brief DtuM35_GetIMEI 获取GSM模块的唯一标识.
///
/// \param imei IMEI存储在这个指针指向的内存.
/// \param len imei这个内存的长度, 防止越界操作.
void DtuM35_GetIMEI(char *imei, uint8 len);

/// \brief DtuM35_GetPhoneNum 获取SIM卡对应的电话号.
///
/// \param phone 电话号码存储在这个指针指向的内存.
/// \param len phone这个内存的长度, 防止越界操作.
void DtuM35_GetPhoneNum(char *phone, uint8 len);


/// \brief DtuM35_GetSupplyVoltage 获取M35的供电电压.
///
/// \return M35模块的供电电压.
uint16 DtuM35_GetSupplyVoltage(void);
uint32 DtuM35_GetPacketCounter(void);

uint8 DtuM35_GetGSMRegisteState(void);
uint8 DtuM35_GetGPRSRegisteState(void);
uint32 DutM35_GetSentPacketCount(void);


Std_ReturnType DtuM35_TcpTransmit(uint16 length, uint16 (*copyTxData)(uint8 *buf, uint16 len), void (*txConfirmation)(NotifResultType Result));
Std_ReturnType DtuM35_TcpConnect(const char *host, uint16 port, void (*ack)(Std_ReturnType Result));
Std_ReturnType DtuM35_TcpDisconnect(void (*ack)(Std_ReturnType Result));

#endif
