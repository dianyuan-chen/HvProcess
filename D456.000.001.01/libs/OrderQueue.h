#ifndef __ORDERQUEUE_H__
#define __ORDERQUEUE_H__

#define MAX_FIFO_LEN    10U

typedef unsigned short OrderQueueValueType;
typedef unsigned char OrderQueueIndexType;

struct OrderQueueItem {
    OrderQueueValueType value;
    OrderQueueIndexType index;
};

struct OrderQueue {
    OrderQueueIndexType head;
    OrderQueueIndexType end;
    OrderQueueIndexType len;
    OrderQueueIndexType size;
    struct OrderQueueItem list[MAX_FIFO_LEN];
};

void OrderQueue_Init(struct OrderQueue *obj, OrderQueueIndexType size);
void OrderQueue_Add(struct OrderQueue *obj, OrderQueueValueType value);
OrderQueueIndexType OrderQueue_TakeOrderValues(const struct OrderQueue *obj, OrderQueueValueType *buf, OrderQueueIndexType size);
OrderQueueIndexType OrderQueue_TakeRawValues(const struct OrderQueue *obj, OrderQueueValueType *buf, OrderQueueIndexType size);
OrderQueueIndexType OrderQueue_TakeOrderValuesByIndex(const struct OrderQueue *obj, OrderQueueValueType *buf, OrderQueueIndexType start, OrderQueueIndexType size);

#endif

