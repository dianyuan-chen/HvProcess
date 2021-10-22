#ifndef _CPU_H_
#define _CPU_H_

#include "Std_Types.h"
#include "Irq_Types.h"
#include "ucos_port/cpu/os_cpu.h"

typedef unsigned short imask_t;

#define Irq_Disable()       _asm("sei");
#define Irq_Enable()        _asm("cli");

#define Irq_SuspendAll()    Irq_Disable()
#define Irq_ResumeAll()     Irq_Enable()

#define Irq_SuspendOs()     Irq_Disable()
#define Irq_ResumeOs()      Irq_Enable()

#define Irq_Save(flags)     (flags = OS_CPU_SR_Save())
#define Irq_Restore(flags)  (OS_CPU_SR_Restore(flags))

void HC12XIrq_InstallVector(Irq_Type vector, HC12XIrq_HandlerFunc func, uint8 priority);
void XGateIrq_InstallVector(Irq_Type vector, uint16 func, uint16 dat);

Std_ReturnType Cpu_AddrLogicToXGate(uint16 *xgateAddr, void *__far logicAddr);
Std_ReturnType Cpu_AddrLogicToGlobal(void *__far *globalAddr, void *__far logicAddr);
Std_ReturnType Cpu_AddrLogicToXGate(uint16 *xgateAddr, void *__far globalAddr);


#endif /* CPU_H_ */
