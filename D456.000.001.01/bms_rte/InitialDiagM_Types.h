/**
 * \file InitialDiagM_Types.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 初始化诊断管理类型头文件.
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

#ifndef INITIAL_DIAG_M_TYPES_H_
#define INITIAL_DIAG_M_TYPES_H_

typedef enum{
    INITIALDIAGM_INIT_OK, /**< 初始化成功 */
    INITIALDIAGM_INIT_ERR, /**< 初始化失败 */
}InitialDiagM_InitTypeType;


typedef enum{
    INITIALDIAGM_ITEM_EEEPROM, /**< Eeeprom初始化诊断项 */
    INITIALDIAGM_ITEM_CAN, /**< CAN初始化诊断项 */
    INITIALDIAGM_ITEM_SLAVE_TEMP_TYPE, /**< 从机温感配置诊断项 */

    INITIALDIAGM_ITEM_MAX
}InitialDiagM_ItemType;




#endif

/**
 * \}
 */
