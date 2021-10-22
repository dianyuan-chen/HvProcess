/**
 * \file Soh.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief SOH头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161213 |
 */

/**
 * \addtogroup Soh SOH
 * \{
 */
#ifndef SOH_CBK_H_
#define SOH_CBK_H_

/**
 * \brief 总容量变化更新SOH回调函数
 *
 * \param totalCap 总容量
 */
void Soh_NewTotalCapIndication(App_CapType totalCap);





#endif

/**
 * \}
 */