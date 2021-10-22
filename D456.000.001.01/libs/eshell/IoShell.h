#ifndef IO_SHELL_H
#define IO_SHELL_H

#include "Dio.h"

typedef struct {
    const char *ioName;
    const char *portName;
    Dio_ChannelType channel;
    boolean isRevert;
} IoShell_NamedIoType;

extern const IoShell_NamedIoType IoShellNamedIoConfigs[];

#endif
