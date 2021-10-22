#ifndef XGATE_H_
#define XGATE_H_

#include "derivative.h"
#include "Std_Types.h"
#include "XGate_Cfg.h"
#include "XGate.hx"
#include "Irq_Types.h"

#define XGate_SoftTriggerChannelType uint16;

#define XGATE_SOFT_TRIGGER_CHANNEL(n) ((uint16)((uint16)0x0101U << (n)))
#define XGATE_SOFT_TRIGGER_CHANNEL_0 XGATE_SOFT_TRIGGER_CHANNEL(0U)
#define XGATE_SOFT_TRIGGER_CHANNEL_1 XGATE_SOFT_TRIGGER_CHANNEL(1U)
#define XGATE_SOFT_TRIGGER_CHANNEL_2 XGATE_SOFT_TRIGGER_CHANNEL(2U)
#define XGATE_SOFT_TRIGGER_CHANNEL_3 XGATE_SOFT_TRIGGER_CHANNEL(3U)
#define XGATE_SOFT_TRIGGER_CHANNEL_4 XGATE_SOFT_TRIGGER_CHANNEL(4U)
#define XGATE_SOFT_TRIGGER_CHANNEL_5 XGATE_SOFT_TRIGGER_CHANNEL(5U)
#define XGATE_SOFT_TRIGGER_CHANNEL_6 XGATE_SOFT_TRIGGER_CHANNEL(6U)
#define XGATE_SOFT_TRIGGER_CHANNEL_7 XGATE_SOFT_TRIGGER_CHANNEL(7U)

void XGate_Setup(void);
void XGate_RouteInterrupt(Irq_Type irq, boolean toXgate, uint8 prio);


Std_ReturnType XGate_AddrLogicToXGate(uint16 *xgateAddr, const void *__far gptr);
Std_ReturnType XGate_AddrGlobalToXGate(uint16 *xgateAddr, const void *__far gptr);

#endif /* __XGATE_H_ */
