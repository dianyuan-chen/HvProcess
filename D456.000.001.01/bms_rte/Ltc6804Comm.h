/**
 * \file Ltc6804Comm.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Ltc6804通信头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170119 |
 */

/**
 * \addtogroup Ltc6804Comm LTC6804通信
 * \{
 */

#ifndef LTC6804_COMM_H_
#define LTC6804_COMM_H_

#include "App_Types.h"
#include "Ltc6804.h"
#include "Ltc6804Comm_Cfg.h"
#include "Dio.h"
#include "Async_Looper.h"
#include "InnerTp.h"

#define LTC6804COMM_BCU_REQ_DATA_BUFFER_SIZE    50U

typedef struct{
    uint16 writeIndex;
    uint8 data[LTC6804COMM_BCU_REQ_DATA_BUFFER_SIZE];
}Ltc6804Comm_BcuReqDataInfo;


extern const struct Ltc6804CFG gLtc6804CfgDefault;
extern const struct Ltc6804 ltc6804_dev;


/**
 * \brief LTC6804通信初始化
 * \param istestmode 是否初始化成测试模式, 测试模式下均衡不使用占空比
 */
Async_LooperType *Ltc6804Comm_Init(uint8 pri, boolean istestmode);

void Ltc6804Comm_HandlerM630(const InnerTp_RequestHandlerType* requestHandler, const PduInfoType *InfoPtr);
void Ltc6804Comm_HandlerAllInOne(const InnerTp_RequestHandlerType* requestHandler, const PduInfoType *InfoPtr);
/**
 * \brief 启动BCU请求数据接收
 *
 * \return E_OK:启动成功 E_NOT_OK:启动失败
 */
Std_ReturnType Ltc6804Comm_StartBcuReqRx(void);

Std_ReturnType Ltc6804Comm_SetGpio(uint8 mod_index, Dio_PortLevelType level);

/* Ltc6804_SampleVoltageEx文件函数声明 */

uint16 SampleVoltage_Process(uint8 mod_count);
uint8 SampleVoltage_GetBatteryVoltage(uint8 type, uint16 *buffer, uint8 size);
Std_ReturnType Sample_GetModuleStatus(uint8 mod_index, struct Ltc6804STxVal *state);
uint8 Sample_GetBatteryVoltage(uint8 mod_index, uint16 *buf, uint8 buf_size);
uint16 Sample_GetBatteryVoltageWireBreak(uint8 mod_index);
boolean Sample_IsPowerWireBreak(uint16 flags);
uint16 Sample_GetBatteryVoltageSuspicious(uint8 mod_index);
uint8 Ltc6804Comm_GetModuleCommAbortCnt(uint8 module);

#endif

/**
 * \}
 */
