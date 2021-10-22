/**
 * \file HvProcess_Chg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 极限保护头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20180707 |
 */

/**
 * \addtogroup LimitProtect 极限保护
 * \{
 */

#ifndef __LIMIT_PROTECT_H_
#define __LIMIT_PROTECT_H_

#include "Async_Looper.h"
#include "Async_Event.h"


/**
 * \brief 极限保护策略内部数据类型
 */
typedef struct{
    Async_EventType event; /**< 异步事件 */
    boolean is_protect; /**< 是否已经产生极限保护 */
}LimitProtect_InnerDataType;


/**
 * \brief 极限保护初始化函数
 *
 * \param looper 异步looper
 */
void LimitProtect_Init(Async_LooperType *looper);

/**
 * \brief 是否已经触发极限保护
 * \return TRUE-是 FALSE-否
 */
boolean LimitProtect_IsProtected(void);



#endif

/**
 * \}
 */