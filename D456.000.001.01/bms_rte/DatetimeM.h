/**
 * \addtogroup RTE
 * \{
 * \addtogroup DATATIMEM 时间管理
 * \{
 */

/**
 * \file DatetimeM.h
 */

#ifndef DATETIMEM_H_
#define DATETIMEM_H_

#include "Std_Types.h"
#include "Datetime.h"
#include "Rtc.h"
#include "Async_Looper.h"
#include "DatetimeM_Cfg.h"

/**
 * \brief 获取时间可能的返回值.
 */
typedef enum {
    DATETIME_TRUSTY, /**< 正确获取到可信的时间 */
    DATETIME_UNTRUSTY, /**< 获取到的时间不可信 */
    DATETIME_ERR, /**< 获取时间失败, 没有可以使用的时间源 */
} DatetimeM_GetReturnType;



#define DATATIMEM_SOC_DATA_NOT_READ  0xFFFE
#define DATATIMEM_SOC_DATA_NOT_VALID  0xFFFF


/**
 * \brief 时间管理初始化.
 */
void DatetimeM_Init(Async_LooperType *looper);

/**
 * \brief 获取系统时间.
 *
 * \param sec [out] 该指针指向的内存用于存放获取到的时间.
 * \return \link DatetimeM_GetReturnType \endlink.
 */
DatetimeM_GetReturnType DatetimeM_GetDatetime(Datetime_SecondType *sec);

/**
 * \brief 设置系统时间.
 *
 * \note 成功设置时间之后, 该软件模块应该择机写入RTC.
 *
 * \param sec 把系统时间设置成该参数传入的时间.
 */
void DatetimeM_SetDatetime(Datetime_SecondType sec);

/**
 * \brief 写入SOC的小数部分.
 *
 * \param soc soc的小数部分.
 */
void DateTimeM_SetFractionSoc(uint8 soc);


/**
 * \brief 获取SOC的小数部分.
 *
 * \retval DATATIMEM_SOC_DATA_NOT_READ 还没有读取到
 * \retval DATATIMEM_SOC_DATA_NOT_VALID 读取到无效值
 * \retval <256 SOC的小数部分.
 */
uint16 DataTimeM_GetFractionSoc(void);

/**
 * \brief 立刻把系统时间同步到RTC.
 * \return 同步成功(E_OK), 同步失败(E_NOT_OK).
 */
// Std_ReturnType DatetimeM_SyncToRtc(void);

void IIC1_Isr(void);

extern const Rtc_DevicesType RtcDevice;

#endif

/**
 * \}
 * \}
 */
