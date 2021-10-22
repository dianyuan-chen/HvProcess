#include "SyncLocks.h"
#include "Std_Types.h"

#ifdef __MINGW32__
#include <windows.h>

struct LockCtx {
    CRITICAL_SECTION sem_token;
};

static int sl_init(void *private_data) {
    struct LockCtx *c = (struct LockCtx *)private_data;
    InitializeCriticalSection(&c->sem_token);
    // DeleteCriticalSection
    return 0;
}

static int sl_lock(void *private_data) {
    struct LockCtx *c = (struct LockCtx *)private_data;
    EnterCriticalSection(&c->sem_token);
    return 0;
}

static int sl_unlock(void *private_data) {
    struct LockCtx *c = (struct LockCtx *)private_data;
    LeaveCriticalSection(&c->sem_token);
    return 0;
}

#else

#include "ucos_ii.h"

struct LockCtx {
    OS_EVENT *sem_token;
};

static int sl_init(void *private_data) {
    struct LockCtx *c = (struct LockCtx *)private_data;
    c->sem_token = OSSemCreate(1U);
    return 0;
}

static int sl_lock(void *private_data) {
    struct LockCtx *c = (struct LockCtx *)private_data;
    uint8 err;
    int ret = 1;
    OSSemPend(c->sem_token, 0U, &err);
    if (err == OS_ERR_NONE) {
        ret = 0;
    }
    return ret;
}

static int sl_unlock(void *private_data) {
    struct LockCtx *c = (struct LockCtx *)private_data;
    return (int)OSSemPost(c->sem_token);
}

#endif

static struct LockCtx ctx;
static const struct sync_locks_ops ops = {
    sl_init,
    sl_lock,
    sl_unlock
};
const struct sync_locks locks = {
    &ctx,
    &ops
};
