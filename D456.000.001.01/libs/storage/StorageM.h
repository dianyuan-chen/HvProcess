#ifndef __STORAGE_M_H__
#define __STORAGE_M_H__

#include "Std_Types.h"
#include "SpiNand.h"
#include "StorageM_Types.h"
#include "StorageM_Cfg.h"

int StorageM_Init(const struct StorageMConfigType *config);

void StorageM_ScanBadBlock(void);

void StorageM_DeInit(void);

int StorageM_ReadPage(PartitionIdType id, uint32 page_addr);

int StorageM_WritePage(PartitionIdType id, uint32 page_addr);

int StorageM_Erase(PartitionIdType id, uint32 page_addr);

sint32 StorageM_ReadPageData(PartitionIdType id, uint16 offset, uint8 *buffer, uint16 size);

sint32 StorageM_WritePageData(PartitionIdType id, uint16 offset, const uint8 *buffer, uint16 size);

int StorageM_Lock(PartitionIdType id);

int StorageM_Unlock(PartitionIdType id);

const struct NandInfoType *StorageM_GetChipInfo(PartitionIdType id);

uint16 StorageM_GetPartitionBlockNum(PartitionIdType id);

uint32 StorageM_GetPartitionFirstSector(PartitionIdType id);

uint8 StorageM_IsBadBlock(PartitionIdType id, uint32 page_addr);

int StorageM_GetInitFlag(void);

#endif
