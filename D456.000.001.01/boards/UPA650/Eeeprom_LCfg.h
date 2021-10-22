/**
 * \file Eeeprom_LCfg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Eeeprom链接配置头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20161209 |
 */

/**
 * \addtogroup Eeeprom
 * \{
 */

#ifndef EEEPROM_LCFG_H_
#define EEEPROM_LCFG_H_

#include "Std_Types.h"
#include "Eeprom_LCfg.h"

/**
 * \brief User DFLASH Partition 扇区个数定义
 * \note USER_DFPART<=128且EMUL_DFPART>=12
 */
#define EEEPROM_USER_DFPART_SIZE        0x10U
#define EEEPROM_EMUL_DFPART_SIZE_MAX    (128U - EEEPROM_USER_DFPART_SIZE)

/**
 * \brief Buffer RAM EEE RAM Partition扇区个数定义
 * \note ERPART<=16且(128-DFPART)/ERPART>=8
 */
#define EEEPROM_ERPART_SIZE_MAX         0x0EU


/**
 * \brief Eeeprom配置类型
 */
typedef struct{
    uint8 FclkDiv; /**< 时钟分频 */
    uint8 DfpartMax; /**< Eeeprom DFLASH使用最大扇区个数 */
    uint8 ErpartMax; /**< EEEPROM使用Buffer RAM最大扇区个数 */
    uint8 DeadSectorProportion; /**< 死扇区最大占比 % */
}Eeep_ConfigType;



/**
 * \brief Eeprom模块配置参数
 */
extern const Eeep_ConfigType Eeeprom_ConfigInfo;




#if EEEPROM_USER_DFPART_SIZE < EEPROM_USED_SECTOR_NUM
    #error The define of "EEEPROM_USER_DFPART_SIZE" in "Eeeprom_LCfg.h" file should not be less than the define of "EEPROM_USED_SECTOR_NUM" in "Eeprom_LCfg.h" file.
#endif

#if EEEPROM_ERPART_SIZE_MAX > 0U
    #if EEEPROM_USER_DFPART_SIZE > 116U
        #error The define of "EEEPROM_USER_DFPART_SIZE" should be meet the condition which is "128-DFPART>=12" in "Eeeprom_LCfg.h" file.
    #endif
#else
    #if EEEPROM_USER_DFPART_SIZE > 128U
        #error The define of "EEEPROM_USER_DFPART_SIZE" should not be more than 128 in "Eeeprom_LCfg.h" file.
    #endif
#endif

#if EEEPROM_ERPART_SIZE_MAX > 0U
    #if ((128UL-EEEPROM_USER_DFPART_SIZE)/EEEPROM_ERPART_SIZE_MAX) < 8U
        #error The define of "EEEPROM_USER_DFPART_SIZE" and "EEEPROM_ERPART_SIZE_MAX" should be meet the condition which is "(128-EEEPROM_USER_DFPART_SIZE)/EEEPROM_ERPART_SIZE_MAX >= 8" in "Eeeprom_LCfg.h" file.
    #endif
#else
    #if EEEPROM_ERPART_SIZE_MAX > 16U
        #error The define of "EEEPROM_ERPART_SIZE_MAX" should not be more than 16 in "Eeeprom_LCfg.h" file.
    #endif
#endif

#endif

/**
 * \}
 */