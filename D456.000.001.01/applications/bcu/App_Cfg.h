/**
 * \addtogroup app_cfg 应用层配置
 * \{
 */

/**
 * \file App_Cfg.h
 * \brief 应用层配置文件
 */

#ifndef APP_CFG_H_
#define APP_CFG_H_


/**
 * \brief 任务优先级定义
 */
#define DRIVER_LOOPER_TASK_PRI              (1U)
#define VCUCOMM_TASK_PRI                    (2U)
#define CURRENTM_TASK_PRI                   (3U)
#define INTERNALCOMM_TX_TASK_PRI            (4U)
#define START_TASK_PRI                      (5U)
#define LTC6804COMM_SAMPLE_TASK_PRI         (6U)
#define DIAGNOSIS_TASK_PRI                  (7U)
#define HVADC_TEST_TASK_PRI                 (8U)
#define HEAT_CURRENT_TASK_PRI               (9U)
#define HVPROCESS_TASK_PRI                  (10U)
#define CHARGERCOMM_TASK_PRI                (11U)
#define EXTERNCANCOMM_TASK_PRI              (12U)
#define SHELL_LOOPER_TASK_PRI               (13U)
#define DTU_TASK_PRI                        (14U)
#define EXT_LOOPER_TASK_PRI                 (15U)
#define SHUNT_LOOPER_TASK_PRI               (16U)
#define SAVE_M_TASK_PRI               		(17U)

#endif

/** \} */
