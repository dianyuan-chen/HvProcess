#ifndef __STORAGE_UTIL_H__
#define __STORAGE_UTIL_H__

#include "Std_Types.h"
#include "StorageM.h"
#include <stdio.h>

struct BSearch {
    /**
     * 用于比较的回调函数
     * @param  thiz   查找对象
     * @param  left  左值索引号
     * @param  right 右值索引号
     * @param  shift 用于返回索引号微调步长
     * @return       返回比较结果
     * @retval > 0   取右边
     * @retval < 0   取左边
     */
    int (*cmp)(const struct BSearch *thiz, uint32 left, uint32 right, int *shift);
    void *private_data;
};

uint32 binary_search_max(const struct BSearch *thiz, uint32 start, uint32 end);
uint32 binary_search_min(const struct BSearch *thiz, uint32 start, uint32 end);


#define INVALID_ID      0x00000000UL
#define IDLE_ID         0xFFFFFFFFUL
struct StorageSearchItem {
    uint32 index;
    uint32 id;
};
struct StorageCycleContextType {
    uint8 *cache;
    uint8 spare[4];
    uint8 active;
    uint8 attach;
    uint16 current_index;
    uint32 last_sector_id;
    uint32 last_sector_addr;
};

struct StorageCycleObjectType {
    PartitionIdType id;
    struct StorageCycleContextType *ctx;
};

struct StorageSearchCtx {
    const struct StorageCycleObjectType *obj;
    struct StorageSearchItem left;
    struct StorageSearchItem right;
};

/**
 * 内存查找函数
 * @param  dest      被查找的内存
 * @param  dest_size 内存大小
 * @param  src       查找的内存数据
 * @param  src_size  内存大小
 * @return           返回查找的位置,-1表示失败
 */
sint32 memfind(const uint8 *dest, uint16 dest_size, const uint8 *src, uint16 src_size);
uint32 get_system_time(void);

uint32 storage_get_id_with_block(PartitionIdType pid, uint32 index);
uint32 storage_get_id_with_page(PartitionIdType pid, uint32 index);
uint32 storage_get_id_with_sector(PartitionIdType pid, uint32 index);
void storage_update_id(const struct BSearch *thiz, uint32 left, uint32 right, uint32 (*get_id)(PartitionIdType pid, uint32 index));
int storage_cmp_max(const struct StorageSearchCtx *ctx, int *shift);
int storage_cmp_with_block(const struct BSearch *thiz, uint32 left, uint32 right, int *shift);
int storage_cmp_with_page(const struct BSearch *thiz, uint32 left, uint32 right, int *shift);
int storage_cmp_with_sector(const struct BSearch *thiz, uint32 left, uint32 right, int *shift);
int storage_cmp_min(const struct StorageSearchCtx *ctx, int *shift);
int storage_cmp_min_with_block(const struct BSearch *thiz, uint32 left, uint32 right, int *shift);
int storage_cmp_min_with_page(const struct BSearch *thiz, uint32 left, uint32 right, int *shift);
int storage_cmp_min_with_sector(const struct BSearch *thiz, uint32 left, uint32 right, int *shift);
int storage_next_block(const struct StorageCycleObjectType *obj);
int storage_next_page(const struct StorageCycleObjectType *obj);
int storage_next_sector(const struct StorageCycleObjectType *obj);



#endif
