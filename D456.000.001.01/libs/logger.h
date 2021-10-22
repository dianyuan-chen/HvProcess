/**
 * Usage:
 * #define LOG_LEVEL LOG_LEVEL_XXX
 * #include "logger.h"
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include "Std_Types.h"
#include "Termio.h"
#include "ucos_ii.h"

enum {
    LOG_LEVEL_TRACE = 0,
    LOG_LEVEL_VERBOSE = 1,
    LOG_LEVEL_DEBUG = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_WARN = 4,
    LOG_LEVEL_ERROR = 5,
    LOG_LEVEL_OFF = 6,

    LOG_LEVEL_T = LOG_LEVEL_TRACE,
    LOG_LEVEL_V = LOG_LEVEL_VERBOSE,
    LOG_LEVEL_D = LOG_LEVEL_DEBUG,
    LOG_LEVEL_I = LOG_LEVEL_INFO,
    LOG_LEVEL_W = LOG_LEVEL_WARN,
    LOG_LEVEL_E = LOG_LEVEL_ERROR,
};

//#undef LOG_LEVEL
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_OFF
#endif

char get_log_string(uint8 level);

#if defined(__PCLINT__)

#define LOG(lvl, args)
#define LOGNH(lvl, args)

#elif defined(__HC12__)

#pragma push
#pragma MESSAGE DISABLE C4000 //Condition always false
#define LOG(lvl, args) if (LOG_LEVEL_##lvl >= LOG_LEVEL) { \
    (void)printf("[%c:%ld][%s(%d)]:", get_log_string(LOG_LEVEL_##lvl), OSTimeGet(), strrchr(__FILE__, '\\') + 1, (uint16)__LINE__); \
    (void)print##args; \
    TERMIO_PutChar('\n'); \
}
#define LOGNH(lvl, args) if (LOG_LEVEL_##lvl >= LOG_LEVEL) { (void)print##args; }
#pragma pop

#elif defined(__MINGW32__)

#include <stdio.h>

#define f(fmt, args...) fprintf(stderr, fmt, ##args)
#define LOG(lvl, fmt) if (LOG_LEVEL_##lvl >= LOG_LEVEL) { \
    (void)fprintf(stderr, "[%c:%ld][%s.%s(%d)]:", get_log_string(LOG_LEVEL_##lvl), OSTimeGet(), strrchr(__FILE__, '\\') + 1, __func__, (uint16)__LINE__); \
    (void)fmt; \
    (void)fprintf(stderr, "\n"); \
    (void)fflush(stderr); \
}
#define LOGNH(lvl, fmt) if (LOG_LEVEL_##lvl >= LOG_LEVEL) { (void)fmt; }

#else

#define f(fmt, args...) printf(fmt, ##args)
#define LOG(lvl, fmt) if (LOG_LEVEL_##lvl >= LOG_LEVEL) { \
    (void)printf("[%c:%ld][%s.%s(%d)]:", get_log_string(LOG_LEVEL_##lvl), OSTimeGet(), strrchr(__FILE__, '\\') + 1, __func__, (uint16)__LINE__); \
    (void)fmt; \
    TERMIO_PutChar('\n'); \
}
#define LOGNH(lvl, fmt) if (LOG_LEVEL_##lvl >= LOG_LEVEL) { (void)fmt; }

#endif // defined(__HC12__)


#endif

