#ifndef __STORAGE_DTC_H__
#define __STORAGE_DTC_H__


#include "StorageM.h"
#include "StorageUtil.h"
#include "StorageDtc_Cfg.h"

typedef uint16 (*DtcCopyFunc)(uint8 *buffer, uint16 size);

int StorageDtc_Init(const struct StorageCycleObjectType *obj);
int StorageDtc_DeInit(const struct StorageCycleObjectType *obj);
int StorageDtc_Save(const struct StorageCycleObjectType *obj, uint32 dtc, const uint8 *pdata, uint16 size);
int StorageDtc_SaveEx(const struct StorageCycleObjectType *obj, uint32 dtc, DtcCopyFunc copy, uint16 size);
int StorageDtc_Read(const struct StorageCycleObjectType *obj, uint32 dtc, uint16 index, uint16 offset, uint8 *buffer, uint16 size);
uint16 StorageDtc_GetNum(const struct StorageCycleObjectType *obj, uint32 dtc);
int StorageDtc_Clear(const struct StorageCycleObjectType *obj, uint32 dtc);
int StorageDtc_ClearAll(const struct StorageCycleObjectType *obj);

#endif
