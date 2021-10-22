    #ifndef UCOS_II_FAKE_H
#define UCOS_II_FAKE_H

#include "pt.h"
#include "Std_Types.h"

typedef struct {
    uint32 start;
    uint32 end;
} Pt_TimerType;



void Pt_TimerSet(Pt_TimerType *t, uint32 interval_ms);
boolean Pt_TimerIsExpired(Pt_TimerType *t);

uint32 OSTimeGet(void);
void OSTimeDly(uint16 t);
void OSTimeTick(void);

typedef uint16 OS_CPU_SR;
OS_CPU_SR  near OS_CPU_SR_Save(void);
void       near OS_CPU_SR_Restore(OS_CPU_SR os_cpu_sr);

#define  OS_INIT_CRITICAL()   OS_CPU_SR cpu_sr
#define  OS_ENTER_CRITICAL()  (cpu_sr = OS_CPU_SR_Save())
#define  OS_EXIT_CRITICAL()   (OS_CPU_SR_Restore(cpu_sr))

#define OS_TICKS_PER_SEC 1000

#endif