/**
 * \file SaveM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 存储管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161213 |
 */

/**
 * \addtogroup SaveM 存储管理
 * \{
 */

#ifndef SAVEM_H_
#define SAVEM_H_

#include "Std_Types.h"
#include "RuntimeM.h"
#include "GBRtMsg.h"

typedef struct {
    uint32 default_cycle;
    uint32 (*getCycle)(void);
    const GB32960_RecordItemType *recList;
} SaveM_RecordDataType;


typedef struct {
    GB32960_RtMessageHeader *headerData;
    SaveM_RecordDataType onPowerUpOnceData;
    SaveM_RecordDataType fixedCycleData;
    SaveM_RecordDataType unfixedCycleData;
} SaveM_RecordConfigDataType;

extern const SaveM_RecordConfigDataType SaveMRecordConfigData;

//extern const SaveM_RecordDataType OnPowerUpOnceData;
//extern const SaveM_RecordDataType FixedCycleData;
//extern const SaveM_RecordDataType UnfixedCycleData;

void SaveM_Init(uint8 taskPri);
void SaveM_Cancel(void);
uint16 SaveM_EraseAll(void);
uint16 SaveM_GetEraseLeftBlockNum(void);
boolean SaveM_PowerDownSaveCbk(RuntimeM_SignalType signal);

#endif

/**
 * \}
 */
