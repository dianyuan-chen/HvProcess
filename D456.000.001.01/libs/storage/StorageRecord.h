#ifndef __STORAGE_RECORD_H__
#define __STORAGE_RECORD_H__

#include "StorageM.h"
#include "StorageUtil.h"
#include "StorageRecord_Cfg.h"

/**
 * \brief      用户自定义记录类型
 * \param      ver   自定义记录的版本号
 * \param      type  自定义记录类型(0~15)
 */
#define RECORD_CUSTOM_TYPE(ver, type)    (((uint16)ver) << 8| (uint8)(0xE0 + (0xF & type)))

typedef uint16 (*RecordCopyFunc)(uint8 *buffer, uint16 size);

int StorageRecord_Init(const struct StorageCycleObjectType *obj);

int StorageRecord_ReadInit(const struct StorageCycleObjectType *obj);

int StorageRecord_DeInit(const struct StorageCycleObjectType *obj);

int StorageRecord_Save(const struct StorageCycleObjectType *obj, uint16 type, const uint8 *pdata, uint16 size);

int StorageRecord_SaveEx(const struct StorageCycleObjectType *obj, uint16 type, RecordCopyFunc copy, uint16 size);

int StorageRecord_Flush(const struct StorageCycleObjectType *obj);

uint32 StorageRecord_GetSectorIndex(const struct StorageCycleObjectType *obj);

#ifdef __MINGW32__
char *StorageRecord_take(const struct StorageCycleObjectType *obj, uint16 *size, uint16 type);

int StorageRecord_read_reset(const struct StorageCycleObjectType *obj);

int StorageRecord_dump_id(const struct StorageCycleObjectType *obj, uint16 block);

int StorageRecord_dump_record(const struct StorageCycleObjectType *obj, uint16 type);

int StorageRecord_cat(const struct StorageCycleObjectType *obj);
#endif

#endif
