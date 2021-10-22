/**
 * \file HvProcess.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压流程控制头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170320 |
 */

/**
 * \addtogroup HvProcess 高压流程控制
 * \{
 */

#ifndef HV_PROCESS_H_
#define HV_PROCESS_H_

#include "HvProcess_Types.h"
#include "Async_Looper.h"
#include "Async_Event.h"

/**
 * \brief 高压流程控制内部数据类型
 */
typedef struct{
    Async_LooperType Looper; /**< 异步Looper */
    Async_EventType Event; /**< 异步事件 */
}HvProcess_InnerDataType;

extern const HvProcess_ProcessDataType HvProcess_ProcessList[];
extern const uint8 HvProcess_ProcessListNum;

/**
 * \brief 高压流程控制模块初始化
 */
void HvProcess_Init(uint8 taskPrio);

/**
 * \brief 获取高压流程异步事件
 * \details 返回高压流程充放电流程的异常事件指针
 * \return 异步事件
 */
Async_EventType *HvProcess_GetAsyncEvent(void);

#endif


/**
 * \}
 */
