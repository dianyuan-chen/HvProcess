#ifndef __ISL78600_COMM_H__
#define __ISL78600_COMM_H__


#include "App_Types.h"
#include "Isl78600.h"
#include "Async_Event.h"
#include "Async_Looper.h"
#include "InnerTp.h"

Async_LooperType *Isl78600Comm_Init(uint8 pri, boolean istestmode);
void Isl78600Comm_HandlerAllInOne(const InnerTp_RequestHandlerType* requestHandler, const PduInfoType *InfoPtr);
uint8* Isl78600Comm_GetBalanceStateBitMapBuffPtr(void);
void Isl78600Comm_SampleUpdateBalanceBitmapFlag(const uint8 *command, uint8 length);
App_VoltageType* Isl78600Comm_GetVoltageBuffPtr(void);
App_TemperatureType* Isl78600Comm_GetTemperatureBuffPtr(void);
void Isl78600Comm_SetBalanceFlag(const uint8 *balance, uint8 length);
uint8* Isl78600Comm_GetBalanceBuffPtr(void);


extern const Dio_ChannelType Isl78600_DaisyChainPowerEnableCtrl;
extern const boolean Isl78600_IsHighWhenDaisyChainPowerEnableCtrlOn;
extern const Dio_ChannelType Isl78600_PowerEnableCtrl;
extern const boolean Isl78600_IsHighWhenPowerEnableCtrlOn;


#endif
