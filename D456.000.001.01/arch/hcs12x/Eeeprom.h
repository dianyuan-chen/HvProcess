/**
 * \file Eeeprom.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Eeeprom头文件.
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

#ifndef EEEPROM_H_
#define EEEPROM_H_

#include "Eeeprom_LCfg.h"

#define EEEPROM_DEV_ERROR_DETECT        STD_OFF

/**
 * \brief EEEPROM支持的保存参数个数
 */
#define EEEPROM_PARAM_NUM_MAX           512U

/**
 * \brief EEEPROM Error define
 */
#define EEEP_ERROR_NONE                 0U
#define EEEP_ERROR_NO_PARTITION         1U
#define EEEP_ERROR_ERPART               2U
#define EEEP_ERROR_DFPART               3U
#define EEEP_ERROR_DEAD_SECTOR          4U
#define EEEP_ERROR_READY_SECTOR         5U
#define EEEP_ERROR_ENABLE_EMULATION     6U

/**
 * \brief bit masks for FTM FSTAT
 */
#define EEEP_FTM_MGSTAT0                0x01U
#define EEEP_FTM_MGSTAT1                0x02U
#define EEEP_FTM_MGBUSY                 0x08U
#define EEEP_FTM_FPVIOL                 0x10U
#define EEEP_FTM_ACCERR                 0x20U
#define EEEP_FTM_CCIF                   0x80U

/**
 * \brief bit masks for FTM FERSTAT
 */
#define EEEP_FTM_SFDIF                  0x01U
#define EEEP_FTM_DFDIF                  0x02U
#define EEEP_FTM_ERSVIF0                0x04U
#define EEEP_FTM_ERSVIF1                0x08U
#define EEEP_FTM_EPVIOLIF               0x10U
#define EEEP_FTM_PGMERIF                0x40U
#define EEEP_FTM_ERSERIF                0x80U

/**
 * \brief Eeeprom地址类型定义
 */
typedef uint16 Eeep_RamAddressType;

/**
 * \brief Eeeprom参数类型定义
 */
typedef uint16 Eeep_DataType;

/**
 * \brief Eeeprom数据长度类型
 */
typedef uint8 Eeep_DataLengthType;

/**
 * \brief Eeeprom状态类型
 */
typedef uint8 Eeep_ErrorStatusType;

/**
 * \brief Eeeprom分区状态类型
 */
typedef struct{
    uint8 fstat; /**< DFlash状态 */
    uint8 ferstat; /**< DFlash异常状态 */
    uint16 dfpart; /**< 用于Eeeprom的DFLASH扇区数 */
    uint16 erpart; /**< 用于Eeeprom的Buffer RAM扇区数 */
    uint16 ecount; /**< 下一就绪扇区(Ready_0)擦除次数 */
    uint8 deadSector; /**< 死扇区数 */
    uint8 readySector; /**< 就绪扇区数 */
}Eeep_PartitionStatusType;

/**
 * \brief Emulated Eeprom初始化
 * \details Emulated eeprom首次使用需要首先对DFLASH进行格式化，使用“Full Partition D-Flash Command”命令完成
 *
 * \todo 考虑可否使用EEPROM_QUERY确认是否已经完成格式化操作，取消在EEPROM中存储格式化标记
 */
void Eeep_Init(void);

/**
 * \brief 向Eeeprom RAM写入数据
 * \details Eeeprom的存储都是对RAM的操作，写RAM自动触发DFLASH的数据存储，故Address为RAM地址
 *
 * \param Eeep_RamOffset 待写入数据RAM偏移
 * \param DataBufferPtr 待写入数据缓存
 * \param Length 待写入数据长度
 *
 * \return E_OK:写入成功 E_NOT_OK:写入失败
 */
Std_ReturnType Eeep_Write(Eeep_RamAddressType Eeep_RamOffset, const Eeep_DataType *DataBufferPtr, Eeep_DataLengthType Length);

/**
 * \brief 读取Eeeprom RAM数据
 * \details 指定地址读取Eeeprom RAM中的数据
 *
 * \param Eeep_RamOffset 待写入数据RAM偏移
 * \param DataBufferPtr 读取到的数据缓存
 * \param Length 读取到的数据长度
 * \return E_OK:读取成功 E_NOT_OK:读取失败
 */
Std_ReturnType Eeep_Read(Eeep_RamAddressType Eeep_RamOffset, Eeep_DataType *DataBufferPtr, Eeep_DataLengthType Length);

/**
 * \brief 获取Eeeprom故障诊断状态
 *
 * \param status 诊断状态
 */
void Eeep_GetDiagnosisStatus(Eeep_ErrorStatusType* status);

/**
 * \brief 等待Eeeprom空闲
 *
 * \return E_OK: 已空闲 E_NOT_OK: Eeeprom忙
 */
Std_ReturnType Eeep_WaitIdle(void);

/**
 * \brief 检查Eeeprom是否全部同步到DFLASH
 *
 * \retval TRUE 全部同步到DFLASH
 * \retval FALSE 未全部同步到DFLASH
 */
boolean Eeep_IsIdle(void);

#endif

/**
 * \}
 */