/**
 *
 * \file dtu_atcmd.h
 * \brief DTU AT命令的封装声明.
 */

#ifndef __DTU_ATCMD_H__
#define __DTU_ATCMD_H__

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Uart.h"
#include "atcmd_Abstract.h"

typedef struct {
    Uart_ChannelType uart;

} ATCMD_ConfigType;

#if 0
/// \brief ATCMD_SerialRecvLine AT命令接收一个字节的数据.
///
/// \param b 接收的数据
void ATCMD_SerialRecvByte(uint8 b);

/// \brief ATCMD_RuntimeInit AT命令运行环境初始化.
///
/// \param send_byte 通过AT串口发送数据的函数.
void ATCMD_RuntimeInit(const ATCMD_ConfigType *cfgOps);

/// \brief ATCMD_ExecCommand 执行AT命令, 并等待回应.
///
/// \param cmd AT命令字符串, 不包括'\r'.
/// \param expect 期望的应答.
/// \param timeoutTick 超时时间.
///
/// \retval E_OK AT 命令等到了期望应答;
/// \retval E_NOT_OK 等待期望应答超时.
Std_ReturnType ATCMD_ExecCommand(const char *cmd, const ATCMD_Expect *expect, uint32 timeoutTick);

/// \brief ATCMD_RetryUntilExpect 多次尝试发送AT命令, 直到等到期望应答或超时.
///
/// \param atcmd 发送的AT命令.
/// \param expect 期望应答的字符串.
/// \param times 尝试的次数.
/// \param timeout 每次等待的超时.
///
/// \return TRUE 发送成功, 并等到了期望应答; FALSE 尝试多次没有等到期望应答.
Std_ReturnType ATCMD_RetryUntilExpect(const char *atcmd, const char *expect, uint8 times, uint16 timeout);
Std_ReturnType ATCMD_RetryUntilExpects(const char *atcmd, const char *const *expects, uint16 times, uint16 timeout);

/// \brief ATCMD_ConnectTcpServer 连接到服务器.
///
/// \param addr 服务器的地址, 可以是IP地址或者域名.
/// \param port 连接的TCP端口.
///
/// \retval E_OK 连接服务器成功
/// \retval FALSE 连接服务器失败.
Std_ReturnType ATCMD_ConnectTcpServer(const char *addr, uint16 port);
Std_ReturnType ATCMD_DisconnectTcpServer(void);

/// \brief ATCMD_SendSMS 发送短信.
///
/// \param dest 接收端的电话号码.
/// \param msg 发送的信息内容.
///
/// \return TRUE 发送成功; FALSE 发送失败.
Std_ReturnType ATCMD_SendSMS(const char *dest, const char *msg);

/// \brief ATCMD_SendDataViaGPRS 通过GPRS发送数据.
///
/// \param dat 需要发送的数据的指针.
/// \param len 需要发送的数据的长度.
///
/// \retval E_OK 发送成功;
/// \retval E_NOT_OK 发送错误.
Std_ReturnType ATCMD_SendDataViaGPRS(const uint8 *dat, uint16 len);

typedef uint16 (*ATCMD_CopySendData)(uint8 *buf, uint16 len);

/// \brief ATCMD_SendDataViaGPRSCallback 通过GPRS发送数据, 发送的数据通过传入的一个函数读取.
///
/// \param len 需要发送的数据的长度.
/// \param getSendData 读取数据的函数.
///
/// \retval E_OK 发送成功;
/// \retval E_NOT_OK 发送错误.
Std_ReturnType ATCMD_SendDataViaGPRSCallback(ATCMD_CopySendData copySendData, uint16 len);
Std_ReturnType ATCMD_GetCellLoc(sint32 loc[2]);
Std_ReturnType ATCMD_GetOPS(char *buf, uint8 len);
Std_ReturnType ATCMD_GetLacCi(uint32 lac_ci[2]);
Std_ReturnType ATCMD_GetCIMI(char *buf, uint8 len);
Std_ReturnType ATCMD_GetIMEI(char *buf, uint8 len);
Std_ReturnType ATCMD_GetSignalQuality(uint8 *rssi, uint8 *ber);
Std_ReturnType ATCMD_GetDataSentInfo(uint32 *sent, uint32 *acked, uint32 *unacked);
Std_ReturnType ATCMD_GetVoltage(uint16 *vol);

#endif


#endif
