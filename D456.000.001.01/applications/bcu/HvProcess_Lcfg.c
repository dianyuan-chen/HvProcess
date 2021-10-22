/**
 * \file HvProcess_Lcfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压流程链接配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170927 |
 */
#include "HvProcess_Types.h"
#include "HvProcess_Chg.h"
#include "HvProcess_Dchg.h"
#include "HvProcess_DC2Chg.h"
#include "GB32960.h"

static boolean dchgIsEnable(void);

const HvProcess_ProcessDataType HvProcess_ProcessList[] = {
    {
        (uint16)HVPROCESS_CHG_STATE_MAX, /**< StateNum: 高压流程状态数 */
        HvProcess_ChgStateConfig, /**< Config: 高压流程配置指针 */
        (HvProcess_GetStateFuncPtr)HvProcess_GetChgState, /**< GetState: 读取状态函数指针 */
        (HvProcess_SetStateFuncPtr)HvProcess_SetChgState, /**< SetState: 设置状态函数指针 */
        HvProcess_ChgInit, /**< Init: 初始化函数指针 */
        NULL, /**< IsEnable: 使能函数指针 */
        HvProcess_ChgPoll, /**< Poll: 轮循函数指针 */
    },
    {
        (uint16)HVPROCESS_DCHG_STATE_MAX, /**< StateNum: 高压流程状态数 */
        HvProcess_DchgStateConfig, /**< Config: 高压流程配置指针 */
        (HvProcess_GetStateFuncPtr)HvProcess_GetDchgState, /**< GetState: 读取状态函数指针 */
        (HvProcess_SetStateFuncPtr)HvProcess_SetDchgState, /**< SetState: 设置状态函数指针 */
        HvProcess_DchgInit, /**< Init: 初始化函数指针 */
        dchgIsEnable, /**< IsEnable: 使能函数指针 */
        HvProcess_DchgPoll, /**< Poll: 轮循函数指针 */
    },
    {
        (uint16)HVPROCESS_DC2CHG_STATE_MAX, /**< StateNum: 高压流程状态数 */
        HvProcess_DC2ChgStateConfig, /**< Config: 高压流程配置指针 */
        (HvProcess_GetStateFuncPtr)HvProcess_GetDC2ChgState, /**< GetState: 读取状态函数指针 */
        (HvProcess_SetStateFuncPtr)HvProcess_SetDC2ChgState, /**< SetState: 设置状态函数指针 */
        HvProcess_DC2ChgInit, /**< Init: 初始化函数指针 */
        NULL, /**< IsEnable: 使能函数指针 */
        HvProcess_DC2ChgPoll, /**< Poll: 轮循函数指针 */
    },
};

const uint8 HvProcess_ProcessListNum = (uint8)ARRAY_SIZE(HvProcess_ProcessList);

static boolean dchgIsEnable(void)
{
    return GB32960_IsDchgAllowed();
}
