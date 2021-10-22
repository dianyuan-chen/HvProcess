#ifndef AISHELL_H__
#define AISHELL_H__

#include "Std_Types.h"

typedef struct {
    uint16 *buffer;
    uint8 size;
    uint8 index;
    uint32 sum;
    uint16 result;
} AiShell_BufferType;

typedef struct {
    const char *signalName;
    const char *adcPort;
    sint16 offset;
    sint16 mul;
    sint16 div;
    AiShell_BufferType *ab;
} AiShell_NamedAiSignalType;



#define AISHELL_DEF_STATIC_BUFF(name, size) \
static uint16 __##name##_buffer[size]; \
static AiShell_BufferType aiShellBuf##name = {&__##name##_buffer[0], size, 0U, 0U, 0xffffU};

#define AISHELL_DEF_BUFF(name, size) \
static uint16 __##name##_buffer[size]; \
AiShell_BufferType aiShellBuf##name = {&__##name##_buffer[0], size, 0U, 0U, 0xffffU};

#define AISHELL_BUFF_PROTYPE(name) \
extern AiShell_BufferType aiShellBuf##name;

void AiShell_AdcValue(AiShell_BufferType *ab, uint16 val);
uint16 Analog_GetSingalValue(const char *name);

extern const AiShell_NamedAiSignalType AiShellNamedAiSignal[];


#endif
