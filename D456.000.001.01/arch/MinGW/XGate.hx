#ifndef XGATE_HXGATE_
#define XGATE_HXGATE_

#include "Std_Types.h"


#define HCS12_SetSem(x)                (1)
#define HCS12_IsSemSet(x)              (0)
#define HCS12_ReleaseSem(x)
#define HCS12_GetXGateIsrFunc(fn)
#define XGATE_ISR_PROTYPE(fn)

#define XGate_SoftwareTrigger(x)
#define XGate_ClearSoftwareTrigger(x)

/**
 * \brief 共享资源通道定义
 */
#define XGATE_CELL_DATA_SEM_CHL        0
#define XGATE_PWM_SEM_CHL              1

/**
 * \brief 一体机通信XGATE软件中断占用通道
 */
#define XGATE_BAU_SW_ISR_CHL            3

#endif /* XGATE_H_ */
