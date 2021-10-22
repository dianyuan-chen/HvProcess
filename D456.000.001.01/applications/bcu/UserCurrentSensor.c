#include "CurrentM.h"
#include "Async_Event.h"
#include "ComStack_Types.h"
#include "CurrentM_Lcfg.h"
#include "CanIf_Lcfg.h"
#include "UserCurrentSensor_Cbk.h"

#define TIMES 20U  //平均电流统计周期


#if !(USERCURRENTSENSOR1_TMPL && USERCURRENTSENSOR2_TMPL)
typedef struct {
    Async_EventType event;
    uint32  rxtime;
    sint32  currentSum;
    Current_CurrentType current;
    OS_EVENT *newCurrentSem;
    uint8 index;
    uint8 state;
    uint8 rxQualityOrErrcode;
} UserCurrentSensor_DataType;
#endif


#if !USERCURRENTSENSOR1_TMPL    //判断是否需要定义，如果模板没有给出此定义（表示userdef1使能），则定义

static UserCurrentSensor_DataType userCurrentSensor1Data;


Std_ReturnType UserCurrentSensor1_WaitCurrentCalibrated(Current_TimedCurrentType *current, uint16 timeout) {
    uint8 err;
    imask_t flag;
    Std_ReturnType ret = E_NOT_OK;

    if (current != NULL) {
        Irq_Save(flag);
        OSSemPend(userCurrentSensor1Data.newCurrentSem, timeout, &err);
        if (err != OS_ERR_NONE) {
            Irq_Restore(flag);
            ret = E_NOT_OK;
        } else {
            OSSemSet(userCurrentSensor1Data.newCurrentSem, 0U, &err);
            current->timestamp = userCurrentSensor1Data.rxtime;
            if (userCurrentSensor1Data.state == E_OK) {
                current->current = userCurrentSensor1Data.current;
            } else {
                current->current = (sint16)CURRENT_INVALID_VALUE;
            }
            Irq_Restore(flag);
            ret = E_OK;
        }
    }
    return ret;
}


Current_CurrentType UserCurrentSensor1_GetCurrent(void) {
    Current_CurrentType ret;
    imask_t mask;

    Irq_Save(mask);
    if (userCurrentSensor1Data.state == E_OK) {
        ret = userCurrentSensor1Data.current;
    } else {
        ret = (sint16)CURRENT_INVALID_VALUE;
    }
    Irq_Restore(mask);

    return ret;
}

static Async_EvnetCbkReturnType async_UserCurrentSensor1_cbk(UserCurrentSensor_DataType *event, uint8 trigger) {
    imask_t mask;
    uint32 time;
    uint8 err;

    (void)trigger;
    (void)event;


    Irq_Save(mask);
    time = userCurrentSensor1Data.rxtime;
    Irq_Restore(mask);


    if ((OSTimeGet() - time) > (TIMES * 10UL + 500UL)) {
        userCurrentSensor1Data.state = E_NOT_OK;
        OSSemSet(userCurrentSensor1Data.newCurrentSem, 0U, &err);
    }

    return ASYNC_EVENT_CBK_RETURN_OK;
}

#endif

#if !USERCURRENTSENSOR2_TMPL    //判断是否需要定义，如果模板没有给出此定义（表示userdef2使能），则定义
static UserCurrentSensor_DataType userCurrentSensor2Data;
Std_ReturnType UserCurrentSensor2_WaitCurrentCalibrated(Current_TimedCurrentType *current, uint16 timeout) {
    uint8 err;
    imask_t flag;
    Std_ReturnType ret = E_NOT_OK;

    if (current != NULL) {
        Irq_Save(flag);
        OSSemPend(userCurrentSensor2Data.newCurrentSem, timeout, &err);
        if (err != OS_ERR_NONE) {
            Irq_Restore(flag);
            ret = E_NOT_OK;
        } else {
            OSSemSet(userCurrentSensor2Data.newCurrentSem, 0U, &err);
            current->timestamp = userCurrentSensor2Data.rxtime;
            if (userCurrentSensor2Data.state == E_OK) {
                current->current = userCurrentSensor2Data.current;
            } else {
                current->current = (sint16)CURRENT_INVALID_VALUE;
            }
            Irq_Restore(flag);
            ret = E_OK;
        }
    }
    return ret;
}


Current_CurrentType UserCurrentSensor2_GetCurrent(void) {
    Current_CurrentType ret;
    imask_t mask;

    Irq_Save(mask);
    if (userCurrentSensor2Data.state == E_OK) {
        ret = userCurrentSensor2Data.current;
    } else {
        ret = (sint16)CURRENT_INVALID_VALUE;
    }
    Irq_Restore(mask);

    return ret;
}

static Async_EvnetCbkReturnType async_UserCurrentSensor2_cbk(UserCurrentSensor_DataType *event, uint8 trigger) {
    imask_t mask;
    uint32 time;
    uint8 err;

    (void)trigger;
    (void)event;


    Irq_Save(mask);
    time = userCurrentSensor2Data.rxtime;
    Irq_Restore(mask);


    if ((OSTimeGet() - time) > (TIMES * 10UL + 500UL)) {
        userCurrentSensor2Data.state = E_NOT_OK;
        OSSemSet(userCurrentSensor2Data.newCurrentSem, 0U, &err);
    }

    return ASYNC_EVENT_CBK_RETURN_OK;
}

#endif


#if !(USERCURRENTSENSOR1_TMPL && USERCURRENTSENSOR2_TMPL)

#include <string.h>

void  UserCurrentSensor_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr) {
    uint32 current;
    uint8 state;
    sint32 scurrent;

    (void)PduInfoPtr;

    switch (RxPduId) {

#if !USERCURRENTSENSOR1_TMPL    //判断can电流传感器1是否开启
    case CANIF_RX_USERCURRENTSENSOR_1:
        if (PduInfoPtr->SduLength == 8U) {
            (void)memcpy(&current, PduInfoPtr->SduDataPtr, 4U);
            state = PduInfoPtr->SduDataPtr[4];
            userCurrentSensor1Data.rxQualityOrErrcode = state & 0xFEU;
            if ((0xFFFFFFFFUL == current) || (state & 0x01U)) {
                userCurrentSensor1Data.state = E_NOT_OK;
            } else {
                current = current - 0x80000000UL;
                scurrent = (sint32)current;
                if (scurrent > 32767L * 100L || scurrent < -32765L * 100L) {
                    userCurrentSensor1Data.state = E_NOT_OK;
                } else {
                    userCurrentSensor1Data.currentSum += scurrent;
                    ++userCurrentSensor1Data.index;
                    if (userCurrentSensor1Data.index >= TIMES) {
                        userCurrentSensor1Data.rxtime = OSTimeGet();
                        scurrent = userCurrentSensor1Data.currentSum / (sint32)(TIMES * 100U);
                        userCurrentSensor1Data.current = (sint16)scurrent;
                        userCurrentSensor1Data.state = E_OK;
                        userCurrentSensor1Data.index = 0U;
                        userCurrentSensor1Data.currentSum = 0;
                        (void)OSSemPost(userCurrentSensor1Data.newCurrentSem);
                    }
                }
            }
        } else {
            userCurrentSensor1Data.state = E_NOT_OK;
        }
        break;
#endif

#if !USERCURRENTSENSOR2_TMPL    //判断can电流传感器1是否开启
    case CANIF_RX_USERCURRENTSENSOR_2:
        if (PduInfoPtr->SduLength == 8U) {
            (void)memcpy(&current, PduInfoPtr->SduDataPtr, 4U);
            state = PduInfoPtr->SduDataPtr[4];
            userCurrentSensor2Data.rxQualityOrErrcode = state & 0xFEU;
            if ((0xFFFFFFFFUL == current) || (state & 0x01U)) {
                userCurrentSensor2Data.state = E_NOT_OK;
            } else {
                current = current - 0x80000000UL;
                scurrent = (sint32)current;
                if (scurrent > 32767L * 100L || scurrent < -32765L * 100L) {
                    userCurrentSensor2Data.state = E_NOT_OK;
                } else {
                    userCurrentSensor2Data.currentSum += scurrent;
                    ++userCurrentSensor2Data.index;
                    if (userCurrentSensor2Data.index >= TIMES) {
                        userCurrentSensor2Data.rxtime = OSTimeGet();
                        scurrent = userCurrentSensor2Data.currentSum / (sint32)(TIMES * 100U);
                        userCurrentSensor2Data.current = (sint16)scurrent;
                        userCurrentSensor2Data.state = E_OK;
                        userCurrentSensor2Data.index = 0U;
                        userCurrentSensor2Data.currentSum = 0;
                        (void)OSSemPost(userCurrentSensor2Data.newCurrentSem);
                    }
                }
            }
        } else {
            userCurrentSensor2Data.state = E_NOT_OK;
        }
        break;
#endif
    default:
        break;
    }
}

#endif

void UserCurrentSensor_TxConfirmation(PduIdType RxPduId) {
    (void)RxPduId;
}

void UserCurrentSensor_Init(Async_LooperType *looper) {
    (void) looper;
#if !USERCURRENTSENSOR1_TMPL    //判断can电流传感器1是否开启
    userCurrentSensor1Data.newCurrentSem = OSSemCreate(0U);
    (void)Async_EventInit(&userCurrentSensor1Data.event, looper, (Async_EventCbkType)async_UserCurrentSensor1_cbk, 500UL);
    (void)Async_EventRegisterToLooper(&userCurrentSensor1Data.event);
#endif

#if !USERCURRENTSENSOR2_TMPL    //判断can电流传感器2是否开启
    userCurrentSensor2Data.newCurrentSem = OSSemCreate(0U);
    (void)Async_EventInit(&userCurrentSensor2Data.event, looper, (Async_EventCbkType)async_UserCurrentSensor2_cbk, 500UL);
    (void)Async_EventRegisterToLooper(&userCurrentSensor2Data.event);
#endif
}
