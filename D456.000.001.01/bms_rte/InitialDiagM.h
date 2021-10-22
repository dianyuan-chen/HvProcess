/**
 * \file InitialDiagM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 初始化诊断管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170501 |
 */
/**
 * \addtogroup InitialDiagM 初始化诊断管理
 * \{
 */

#ifndef INITIAL_DIAG_M_H_
#define INITIAL_DIAG_M_H_

#include "Std_Types.h"
#include "InitialDiagM_Types.h"


#define INITIALDIAGM_DIAG_BUFF_SIZE     10


typedef struct{
    uint8 diagBuff[INITIALDIAGM_DIAG_BUFF_SIZE];

}InitialDiagM_InnerDataType;

/**
 * \brief 初始化诊断管理初始化
 */
void InitialDiagM_Init(void);

/**
 * \brief 设置初始化管理诊断项的状态
 * \details 更新初始化成功或失败标志
 *
 * \param item 初始化诊断项
 * \param type 成功or失败
 */
void InitialDiagM_SetDiagFlag(InitialDiagM_ItemType item, InitialDiagM_InitTypeType type);

/**
 * \brief 获取初始化管理诊断项的初始化结果
 *
 * \param item 初始化诊断项
 */
InitialDiagM_InitTypeType InitialDiagM_GetDiagFlag(InitialDiagM_ItemType item);

/**
 * \brief BMS是否初始化失败
 * \return 0-正常 1-失败
 */
uint16 InitialDiagM_IsDiagFailure(void);


#endif

/**
 * \}
 */
