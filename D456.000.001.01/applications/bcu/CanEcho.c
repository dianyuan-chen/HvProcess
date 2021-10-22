#include <string.h>
#include "CanEcho.h"
#include "CanEcho_Cbk.h"
#include "ComStack_Types.h"
#include "CanIf_Lcfg.h"

static boolean busy = FALSE;
static uint8 buf[8];
static uint8 count[3] = {0U, 0U, 0U};

Async_EventType thisEvent;

static Async_EvnetCbkReturnType cbk(Async_EventType *event, uint8  byWhat) {
    PduInfoType info;
    (void)event;


    if (byWhat != ASYNC_TRIGGER_BY_TIMEOUT) {
        info.SduLength = 8U;
        info.SduDataPtr = buf;
        if (byWhat == CANIF_RX_CANECHO_0) {
            (void)CanIf_Transmit(CANIF_TX_CANECHO_0, &info);
        } else if (byWhat == CANIF_RX_CANECHO_1) {
            (void)CanIf_Transmit(CANIF_TX_CANECHO_1, &info);
        } else if (byWhat == CANIF_RX_CANECHO_2) {
            (void)CanIf_Transmit(CANIF_TX_CANECHO_2, &info);
        } else {
        }
        busy = FALSE;
    }
    return ASYNC_EVENT_CBK_RETURN_OK;
}

void CanEcho_Init(Async_LooperType *looper) {
    (void)Async_EventInit(&thisEvent, looper, cbk, 1000UL * 60UL * 60UL);
    (void)Async_EventRegisterToLooper(&thisEvent);
}

void CanEcho_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr) {
    boolean needRelay = TRUE;
    imask_t mask;

    if (RxPduId == CANIF_RX_CANECHO_0) {
        count[0]++;
    } else if (RxPduId == CANIF_RX_CANECHO_1) {
        count[1]++;
    } else if (RxPduId == CANIF_RX_CANECHO_2) {
        count[2]++;
    } else {
        needRelay = FALSE;
    }

    if (needRelay) {
        Irq_Save(mask);
        if (!busy) {
            (void)memcpy(buf, PduInfoPtr->SduDataPtr, 8U);
            if (E_OK == Async_EventTrigger(&thisEvent, RxPduId)) {
                busy = TRUE;
            }
        }
        Irq_Restore(mask);
    }
}

void CanEcho_TxConfirmation(PduIdType RxPduId) {
    (void)RxPduId;
}


#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

const char shell_summary_cantest[] = "shell help";
const char shell_help_cantest[] = "\
 rxnum index \n\
 send index dat\n\
    rxnum 1/2/3  - Read received frame number of specified can drive\n\
    send 1/2/3 5    - Read received frame number of specified can drive\n\
";

int shell_func_cantest(int argc, const char *const *argv);
int shell_func_cantest(int argc, const char *const *argv) {
    int ret = -1;
    boolean arg_err = TRUE;
    uint8 index;
    uint8 dat;


    if (argc == 3) {
        if (strcmp(argv[1], "rxnum") == 0) {
            index = (uint8)atoi(argv[2]);
            if (index < 1U || index > 3U) {
            } else {
                index = index - 1U;
                (void)printf("%d\n", count[index]);
                arg_err = FALSE;
                ret = 0;
            }
        }
    } else if (argc == 4) {
        if (strcmp(argv[1], "send") == 0) {
            index = (uint8)atoi(argv[2]);
            dat = (uint8)atoi(argv[3]);
            (void)memset(buf, (int)dat, sizeof(buf));

            if (index == 1U) {
                arg_err = FALSE;
                ret = (int)Async_EventTrigger(&thisEvent, CANIF_RX_CANECHO_0);
            } else if (index == 2U) {
                arg_err = FALSE;
                ret = (int)Async_EventTrigger(&thisEvent, CANIF_RX_CANECHO_1);
            } else if (index == 3U) {
                arg_err = FALSE;
                ret = (int)Async_EventTrigger(&thisEvent, CANIF_RX_CANECHO_2);
            } else {
            }
        }
    } else {

    }

    if (arg_err) {
        ret =  Shell_ArgsError(argv[0]);
    }

    return ret;
}
