#include "Async_Test.h"

#if ASYNC_TEST_EN > 0

#include "Hall.h"
#include "Dio.h"
#include "XGate.h"
#include "Adc.h"
#include "Ads1018.h"
#include "BridgeInsu.h"
#define LOG_LEVEL LOG_LEVEL_OFF
#include "logger.h"


typedef struct {
    Async_EventType event;
    uint8 counter;
} TestEvent;


#ifdef __HC12__

typedef struct {
    const char *name;
    Dio_ChannelType channel;
} DinputsType;

const DinputsType dinputs[] = {
    {"OBC", DIO_CHANNEL_OBC_POWER},
    {"KEYON", DIO_CHANNEL_KEY_ON},
    {"CRDY", DIO_CHANNEL_CHARGER_READY},
    {"ELFB", DIO_CHANNEL_EL_FEEDBACK},
    {"SW1", DIO_CHANNEL_SW_IN_1},
    {"SW2", DIO_CHANNEL_SW_IN_2},
    {"SIG1", DIO_CHANNEL_SIG_IN_1},
    {"SIG2", DIO_CHANNEL_SIG_IN_2},
};

#endif


static void di_dump(void) {
    uint8 i;
    (void)printf("Dinputs: ");
    for (i = 0U; i < ARRAY_SIZE(dinputs); ++i) {
        (void)printf("%s(%d), ", dinputs[i].name, Dio_ReadChannel(dinputs[i].channel));
    }
    (void)printf("\n");
}

extern void hall_dump(void);
extern void shunt_dump(void);


static Async_EvnetCbkReturnType async_test_cbk(TestEvent *event, uint8 trigger) {
    static uint32 heartbeat = 0;

    (void)trigger;
    (void)event;
    (void)printf("\nHeartbeat: %lu\n", heartbeat++);
#if OS_TASK_STAT_EN > 0
    (void)printf("\nOSCPUUsage: %u\n", OSCPUUsage);
#endif
    // XGate_SoftwareTrigger(0);

#ifdef __HC12__
    dump_adt();
    hall_dump();
    shunt_dump();
    hvadc_dump();
    di_dump();
    dump_insu();
#endif

    return ASYNC_EVENT_CBK_RETURN_OK;
}
#endif

// XGATE_ISR_PROTYPE(XGateSoftTriggerHandler);

void async_test(Async_LooperType *looper) {
    //static TestEvent testEvent;
    //uint16 func;

    (void)looper;
    // XGate_AddrGlobalToXGate(&func, HCS12_GetXGateIsrFunc(XGateSoftTriggerHandler));
    // XGateIrq_InstallVector(IRQ_XGATE_SOFTWARE_TRIGGER_0, func, 0);
    // XGate_RouteInterrupt(IRQ_XGATE_SOFTWARE_TRIGGER_0, TRUE, 2);

#if ASYNC_TEST_EN > 0
    // testEvent.counter = 0;
    //Async_EventInit(&testEvent.event, looper, (Async_EventCbkType)async_test_cbk, 1000);
    //(void)Async_EventRegisterToLooper(&testEvent.event);
#endif
}
