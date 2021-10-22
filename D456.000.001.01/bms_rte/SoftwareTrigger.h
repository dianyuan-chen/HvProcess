/**
 * \file SoftwareTrigger.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief HCS12软件中断触发头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161228 |
 */

#ifndef SOFTWARETRIGGER_H_
#define SOFTWARETRIGGER_H_




/**
 * \brief HCS12主处理器软件中断0处理函数
 * \details 此通道用于内网通信请求通道0通知协处理器完成从机响应处理处理后中断告知主处理器进行后续请求处理
 */
void HCS12SoftTrigger0Handler(void);

/**
 * \brief HCS12主处理器软件中断1处理函数
 * \details 此通道用于内网通信请求通道1通知协处理器完成从机响应处理处理后中断告知主处理器进行后续请求处理
 */
void HCS12SoftTrigger1Handler(void);

/**
 * \brief HCS12主处理器软件中断2处理函数
 * \details 此通道用于内网通信请求通道2通知协处理器完成从机响应处理处理后中断告知主处理器进行后续请求处理
 */
void HCS12SoftTrigger2Handler(void);

/**
 * \brief HCS12主处理器软件中断3处理函数
 * \details 此通道用于内网通信请求通道3通知协处理器完成从机响应处理处理后中断告知主处理器进行后续请求处理
 */
void HCS12SoftTrigger3Handler(void);









#endif