#ifndef GBRTMSG_H
#define GBRTMSG_H

#include "Async_Looper.h"
#include "GB32960.h"
#include "RelayM.h"

void GBRtMsg_Init(Async_LooperType *looper);
void GBRtMsg_Start(void);
void GBRtMsg_Cancel(void);


typedef struct {
    uint8 msgType;
} GB32960_PACKED GB32960_RtMessageHeader;

typedef struct {
    uint16 start;
    uint16 end;
    uint8 ptrType;
    union {
        const void *ptr;
        const uint8 *dat;
        const uint8 *(*getDataPtr)(void);
        uint16 (*copy)(uint16 offset, uint8 *buf, uint16 len);
    } ptr;
} GB32960_CopySegmentType;


typedef void (*GB32960_FillMessageFuncType)(GB32960_RtMessageHeader *msgHeader);

typedef struct {
    uint16 id;
    uint16 length;
    uint16 (*getLength)(void);
    GB32960_FillMessageFuncType fillMessage;
    const GB32960_CopySegmentType *copyRecordSegments;
    uint8 copyRecordSegmentsNum;
    boolean (*isValid)(void);
} GB32960_RecordItemType;



#define PTR_TYPE_DATA       0U
#define PTR_TYPE_GET_DATA   1U
#define PTR_TYPE_COPY_DATA  2U

#define LEN_TYPE_LENGTH     0U
#define LEN_TYPE_GET_LENGTH 1U
#define LEN_VALUE(x)        ((uint16 (*)(void))(x))



typedef struct {
    uint8 id;
    boolean isNotChargingData;
    uint8 lenType;
    uint16 length;
    uint16 (*getLength)(void);
    GB32960_FillMessageFuncType fillMessage;
    const GB32960_CopySegmentType *copySegments;
    uint8 copySegmentsNum;
} GB32960_RTMessageItemType;

typedef struct {
    GB32960_RtMessageHeader *headerWithBuffer;
    const GB32960_RTMessageItemType *loginOnceData;
    const GB32960_RTMessageItemType *intervalData;
    void (*intervalBeginHook)(void);
} GB32960_RtMessageConfigDataType;

extern const GB32960_RtMessageConfigDataType GB32960RtMessageConfigData;


uint16 GBRtMsg_CopyFromSegment(const GB32960_CopySegmentType *segs, uint8 segNum, uint16 offset, uint8 *buf, uint16 len);
uint16 GBRtMsg_GetRecordLength(const GB32960_RecordItemType *item);

#endif
