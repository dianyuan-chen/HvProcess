#ifndef __SYNC_LOCKS_H__
#define __SYNC_LOCKS_H__






struct sync_locks_ops {
    int (*init)(void *private_data);
    int (*lock)(void *private_data);
    int (*unlock)(void *private_data);
};

struct sync_locks {
    void *private_data;
    const struct sync_locks_ops *ops;
};

int SyncLocks_Init(const struct sync_locks *thiz);
int SyncLocks_Lock(const struct sync_locks *thiz);
int SyncLocks_UnLock(const struct sync_locks *thiz);


#endif
