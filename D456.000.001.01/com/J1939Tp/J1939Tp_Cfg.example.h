/**
 * \file J1939Tp_Cfg.H
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief J1939Tp配置头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170224 |
 */


#ifndef J1939TP_CFG_H
#define J1939TP_CFG_H

#define CANSM_DEV_ERROR_DETECT          STD_ON
#define J1939TP_DEV_ERROR_DETECT        STD_ON
#define J1939TP_VERSION_INFO_API        STD_OFF
#define J1939TP_CANCELLATION_SUPPORT    STD_ON
#define J1939TP_DYNAMIC_BLOCK_CALCULATION   STD_OFF

#define J1939TP_PACKETS_PER_BLOCK       5
#define J1939TP_MAIN_FUNCTION_PERIOD    2
#define J1939TP_TX_CONF_TIMEOUT         99

#endif /*J1939TP_CFG_H*/
