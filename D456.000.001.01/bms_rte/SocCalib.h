/**
 * \file SocCalib.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief SOC校正头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161213 |
 */

/**
 * \addtogroup SocCalib SOC校正
 * \{
 */


#ifndef SOCCALIB_H_
#define SOCCALIB_H_

#include "Std_Types.h"
#include "Soc.h"
#include "Async_looper.h"
#include "Async_Event.h"


#define SOCCALIB_DEV_ERROR_DETECT       STD_OFF

typedef struct{
    uint8 OcvSocEnable; /**< OCV-SOC校准使能控制 */
}SocCalib_CofnigType;

typedef struct{
    Async_EventType event; /**< 周期更新事件 */
}SocCalib_innerDataType;


extern const SocCalib_CofnigType SocCalib_ConfigInfo;

/**
 * \brief Soc校正模块初始化
 */
void SocCalib_Init(Async_LooperType *looper);



#endif

/**
 * \}
 */