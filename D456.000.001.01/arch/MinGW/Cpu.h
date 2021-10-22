#ifndef _CPU_H_
#define _CPU_H_

#include "Std_Types.h"
#include "Irq_Types.h"
#include "ucos_ii.h"

typedef uint16 imask_t;


#define Irq_Disable()       OS_ENTER_CRITICAL()
#define Irq_Enable()        OS_EXIT_CRITICAL()

#define Irq_SuspendAll()    Irq_Disable()
#define Irq_ResumeAll()     Irq_Enable()

#define Irq_SuspendOs()     Irq_Disable()
#define Irq_ResumeOs()      Irq_Enable()

#define Irq_Save(flags)    Irq_Disable()
#define Irq_Restore(flags) Irq_Enable()


void HC12XIrq_InstallVector(Irq_Type vector, HC12XIrq_HandlerFunc func, uint8 priority);
void XGateIrq_InstallVector(Irq_Type vector, uint16 func, uint16 dat);

#endif /* CPU_H_ */
