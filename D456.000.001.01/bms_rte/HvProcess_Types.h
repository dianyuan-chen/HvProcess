/**
 * \file HvProcess_Types.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压流程控制类型头文件.
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

#ifndef HV_PROCESS_TYPES_H_
#define HV_PROCESS_TYPES_H_

#include "App_Types.h"
#include "Async_Looper.h"
#include "Async_Event.h"

/**
 * \brief 高压流程控制条件函数类型
 */
typedef boolean (*HvProcess_CondFunc)(void);

/**
 * \brief 高压流程控制动作函数类型
 */
typedef void (*HvProcess_ActionFunc)(void);

/**
 * \brief 高压流程控制状态信息类型
 */
typedef struct{
    HvProcess_CondFunc Cond; /**< 条件函数指针 */
    HvProcess_ActionFunc Action; /**< 动作函数指针 */
    uint16 Next; /**< 下一状态 */
}HvProcess_StateInfoType;

/**
 * \brief 高压流程控制状态配置类型
 */
typedef struct{
    uint8 Num; /**< 状态信息个数 */
    const HvProcess_StateInfoType *State; /**< 状态信息指针 */
}HvProcess_StateConfigType;

/**
 * \brief 读取当前状态函数指针类型定义
 */
typedef uint16 (*HvProcess_GetStateFuncPtr)(void);

/**
 * \brief 设置当前状态函数指针类型定义
 */
typedef void (*HvProcess_SetStateFuncPtr)(uint16 state);

/**
 * \brief 高压流程初始化函数指针类型定义
 */
typedef void (*HvProcess_InitFuncPtr)(Async_LooperType *looper);

/**
 * \brief 高压流程使能函数指针类型定义
 */
typedef boolean (*HvProcess_IsEnableFuncPtr)(void);

/**
 * \brief 高压流程轮循函数指针类型定义
 */
typedef void (*HvProcess_PollFuncPtr)(void);

/**
 * \brief 高压流程数据类型定义
 */
typedef struct{
    uint16 StateNum; /**< 高压流程状态数 */
    const HvProcess_StateConfigType *Config; /**< 高压流程配置指针 */
    HvProcess_GetStateFuncPtr GetState; /**< 读取状态函数指针 */
    HvProcess_SetStateFuncPtr SetState; /**< 设置状态函数指针 */
    HvProcess_InitFuncPtr Init; /**< 初始化函数指针 */
    HvProcess_IsEnableFuncPtr IsEnable; /**< 使能函数指针 */
    HvProcess_PollFuncPtr Poll; /**< 轮循函数指针 */
}HvProcess_ProcessDataType;




#endif


/**
 * \}
 */