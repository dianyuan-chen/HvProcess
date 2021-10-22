#ifndef XGATE_HXGATE_
#define XGATE_HXGATE_

#include <MC9S12XEP100.h>
#include "Std_Types.h"

#if defined(__XGATE__)
#include <intrinsics_xgate.h>
#define XGATE_ISR_PROTYPE(fn)           interrupt fn(uint16 dat)
#endif

#if defined(__HC12__)
#define HCS12_SetSem(x)                 (XGSEM = (uint16)0x0101U << (x))
#define HCS12_IsSemSet(x)               (XGSEM & (uint16)0x0001U << (x))
#define HCS12_ReleaseSem(x)             (XGSEM = (uint16)0x0100U << (x))
#define HCS12_GetXGateIsrFunc(fn)       __X_##fn
#define XGATE_ISR_PROTYPE(fn)           extern uint16 HCS12_GetXGateIsrFunc(fn)[]
#endif

#define XGate_SoftwareTrigger(x)        (XGSWT = (uint16)0x0101U << (x))
#define XGate_ClearSoftwareTrigger(x)   (XGSWT = (uint16)0x0100U << (x))

/**
 * \brief 共享资源通道定义
 */
#define XGATE_CELL_DATA_SEM_CHL         0U
#define XGATE_PWM_SEM_CHL               1U
#define XGATE_STATISTIC_DATA_SEM_CHL    2U

/**
 * \brief 一体机通信XGATE软件中断占用通道
 */
#define XGATE_BAU_SW_ISR_CHL            0U

#endif /* XGATE_H_ */
