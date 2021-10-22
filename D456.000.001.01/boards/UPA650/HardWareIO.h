/**
 * \file HardWareIO.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 硬件IO版本头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161207 |
 */

/**
 * \addtogroup HardWareIO 硬件IO版本
 * \{
 */

#ifndef HARDWARE_IO_H_
#define HARDWARE_IO_H_

#include "Std_Types.h"
#include "Dio.h"

/**
 * \brief 硬件IO占用端口数
 */
#define HARDWAREIO_IO_NUM               3U
#define HARDWAREIO_HW_VERSION_MASK      0x07U

/**
 * \brief 获取硬件IO版本
 * \return 硬件IO版本
 */
uint8 HardWareIO_GetVersion(void);

/**
 * \brief 获取当前软件支持的硬件IO版本
 * \details 支持的硬件IO版本以bitmap表示 bit0-支持硬件IO版本0 bit1-支持硬件IO版本1,以此类推，共支持16个硬件IO版本
 * \return 软件支持硬件IO版本
 */
uint16 HardWareIO_GetSoftWareSupportVersion(void);


#endif

/**
 * \}
 */