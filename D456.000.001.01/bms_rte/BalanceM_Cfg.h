/**
 * \file BalanceM_Cfg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 均衡管理配置头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170622 |
 */

/**
 * \addtogroup BalanceM 均衡管理
 * \{
 */

#ifndef BALANCEM_CFG_H_
#define BALANCEM_CFG_H_


/**
 * \brief 故障检测开关
 */
#define BALANCEM_DEV_ERROR_DETECT               STD_OFF

/**
 * \brief 采集板支持最大均衡个数定义
 */
#define BALANCEM_BMU_BOARD_BALANCE_NUM_MAX      2U

/**
 * \brief 从机均衡控制命令缓存长度定义
 */
#define BALANCEM_BALANCE_COMMAND_BUFFER_SIZE    10U

/**
 * \brief 采集板支持最大均衡个数定义
 */
#define BALANCEM_REMOTE_BMU_BOARD_BALANCE_NUM_MAX      6U


#endif

/**
 * \}
 */
