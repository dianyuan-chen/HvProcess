/**
 * \file Eeprom_LCfg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Eeprom链接配置头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20161208 |
 */

/**
 * \addtogroup Eeprom
 * \{
 */

#ifndef EEPROM_LCFG_H_
#define EEPROM_LCFG_H_

#include "Std_Types.h"

/**
 * \brief Eeprom起始地址定义
 */
#define EEPROM_ADDR_START   0x100000UL


/**
 * \brief Eeprom占用DFLASH扇区个数
 * \note Eeprom大小为4k
 */
#define EEPROM_USED_SECTOR_NUM     0x10UL


/**
 * \brief Eeprom地址类型定义
 */
typedef uint32 Eep_AddressType;


/**
 * \brief Eeprom配置参数类型定义
 */
typedef struct{
    uint8 FclkDiv; /**< FLASH时钟分频值 */
    Eep_AddressType StartAddress; /**< eeprom起始地址 */
    Eep_AddressType StopAddress; /**< eeprom结束地址 */
}Eep_ConfigType;


/**
 * \brief Eeprom模块配置参数
 */
extern const Eep_ConfigType Eeprom_ConfigInfo;



#if ((EEPROM_ADDR_START < 0x100000UL) || (EEPROM_ADDR_START > 0x107FF00UL))
    #error The define of "EEPROM_ADDR_START" should be in range from 0x100000UL to 0x107FF00UL in "Eeprom_LCfg.h" file.
#endif

#if EEPROM_USED_SECTOR_NUM == 0UL || EEPROM_USED_SECTOR_NUM > 128UL
    #error The define of "EEPROM_USED_SECTOR_NUM" should be in range from 1 to 128 in "Eeprom_LCfg.h" file.
#endif


#endif

/**
 * \}
 */