#ifndef __STORAGE_DTC_CFG_H__
#define __STORAGE_DTC_CFG_H__

#define STORAGE_DTC_CODE_NUM 		10U

extern const struct StorageCycleObjectType StorageDtcObject;

extern const uint32 dtc_list[STORAGE_DTC_CODE_NUM];
extern uint16 dtc_last_page_addr_list[STORAGE_DTC_CODE_NUM];

#endif
