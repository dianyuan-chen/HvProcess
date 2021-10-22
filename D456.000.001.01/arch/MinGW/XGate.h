#ifndef XGATE_H_
#define XGATE_H_

#include "Std_Types.h"
#include "Irq_Types.h"

#define HCS12_SetSem(x)             (1)
#define HCS12_IsSemSet(x)           (0)
#define HCS12_ReleaseSem(x)         (0)
#define HCS12_GetXGateIsrFunc(fn)   (fn)
#define XGATE_ISR_PROTYPE(fn)       (fn)

#define XGate_SoftwareTrigger(x)
#define XGate_ClearSoftwareTrigger(x)

#define XGATE_SOFT_TRIGGER_CHANNEL(n) (0x0101u << (n))
#define XGATE_SOFT_TRIGGER_CHANNEL_0 XGATE_SOFT_TRIGGER_CHANNEL(0)
#define XGATE_SOFT_TRIGGER_CHANNEL_1 XGATE_SOFT_TRIGGER_CHANNEL(1)
#define XGATE_SOFT_TRIGGER_CHANNEL_2 XGATE_SOFT_TRIGGER_CHANNEL(2)
#define XGATE_SOFT_TRIGGER_CHANNEL_3 XGATE_SOFT_TRIGGER_CHANNEL(3)
#define XGATE_SOFT_TRIGGER_CHANNEL_4 XGATE_SOFT_TRIGGER_CHANNEL(4)
#define XGATE_SOFT_TRIGGER_CHANNEL_5 XGATE_SOFT_TRIGGER_CHANNEL(5)
#define XGATE_SOFT_TRIGGER_CHANNEL_6 XGATE_SOFT_TRIGGER_CHANNEL(6)
#define XGATE_SOFT_TRIGGER_CHANNEL_7 XGATE_SOFT_TRIGGER_CHANNEL(7)

void XGate_Setup(void);
void XGate_RouteInterrupt(Irq_Type irq, boolean toXgate, uint8 prio);


Std_ReturnType XGate_AddrLogicToXGate(uint16 *xgateAddr, void *gptr);
Std_ReturnType XGate_AddrGlobalToXGate(uint16 *xgateAddr, void *gptr);

#endif /* __XGATE_H_ */
