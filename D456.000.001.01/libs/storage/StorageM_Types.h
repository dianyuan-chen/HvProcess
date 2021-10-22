#ifndef __STORAGE_M_TYPES_H__
#define __STORAGE_M_TYPES_H__

#include "Std_Types.h"

#ifdef __MINGW32__
#include <time.h>
#include <Winsock2.h>
#define PACKED __attribute__((packed))
#else
#define PACKED
#define ntohl(a)    a
#define ntohs(a)    a
#define htons(a)    a
#define htonl(a)    a
#endif

#define STORAGEM_PARTITION_TYPE_FULLCHIP        0xFU
#define STORAGEM_PARTITION_ZERO_INDEX_ID_DEF(type)  ((uint8)(((type) & 0xFU) << 4))
#define STORAGEM_PARTITION_ID_DEF(index,type)   ((uint8)((index) & 0xFU) | (uint8)(((type) & 0xFU) << 4))
#define STORAGEM_PARTITION_ID_GET_TYPE(id)      ((uint8)(((id) >> 4) & 0xFU))
#define STORAGEM_PARTITION_ID_GET_INDEX(id)     ((uint8)((id) & 0xFU))

typedef uint8 PartitionIdType;

struct StorageMPartitionType {
    uint8 type;
    uint8 reserved;
    uint16 first_block;
    uint16 last_block;
} PACKED;

struct StorageMDevice {
    const struct SpiNandPlatformType *platform;
    const struct sync_locks *locks;
};

struct StorageMConfigType {
    const struct StorageMDevice *device;
    const struct StorageMPartitionType *partitions;
    uint8 *bad_block_flags;
};

struct StorageMBaseInfoType {
    uint32 ValidFlag;       /*!< 存储信息的有效标识 */
    uint16 version;     /*!< 存储信息的版本号 */
    uint16 len;         /*!< 存储信息附加数据长度,在该字段后面紧跟附加数据,例如分区信息 */
};

#endif
