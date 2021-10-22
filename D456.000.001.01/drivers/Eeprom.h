/**
 * \file Eeprom.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Eeprom头文件.
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

#ifndef EEPROM_H_
#define EEPROM_H_

#include "Eeprom_LCfg.h"

/**
 * \brief 扇区大小定义
 */
#define DFLASH_SECTOR_SIZE  0x100U


/**
 * \brief Eeprom长度类型定义
 */
typedef uint8 Eep_LengthType;


/**
 * \brief Eeprom错误类型定义
 */
typedef enum{
    EEP_E_INIT_FAILED = 0x10, /**< 初始化错误 */
    EEP_E_PARAM_ADDRESS = 0x11, /**< 地址错误 */
    EEP_E_PARAM_DATA = 0x12, /**< 数据错误 */
    EEP_E_PARAM_LENGTH = 0x13, /**< 长度错误 */
    EEP_E_UNINIT = 0x20, /**< 未初始化错误 */
    EEP_E_BUSY = 0x21, /**< 操作忙错误 */
    EEP_E_TIMEOUT = 0x21, /**< 超时错误 */
    EEP_E_PARAM_POINTER = 0x23, /**< 指针错误 */
    EEP_E_ERASE_FAILED = 0x24, /**< 擦除错误 */
    EEP_E_WRITE_FAILED = 0x25, /**< 写入错误 */
    EEP_E_READ_FAILED = 0x26, /**< 读取错误 */
    EEP_E_COMPARE_FAILED = 0x27, /**< 比较错误 */
}Eep_ErrorType;

/**
 * \brief Eeprom模块初始化
 * \details 初始化Eeprom时钟及相关寄存器
 *
 * \param ConfigPtr Eeprom配置参数
 */
void Eep_Init(const Eep_ConfigType* ConfigPtr);


/**
 * \brief Eeprom模块反初始化
 */
void Eep_Deinit(void);


/**
 * \brief 读Eeprom
 * \details 从指定地址读取指定长度的数据
 *
 * \param EepromAddress Eeprom地址
 * \param DataBufferPtr 数据缓存
 * \param Length 数据长度
 *
 * \return E_OK:读取成功 E_NOT_OK:读取失败
 */
Std_ReturnType Eep_Read(Eep_AddressType EepromAddress, uint8* DataBufferPtr, Eep_LengthType Length);


/**
 * \brief 向指定地址的Eeprom写入数据
 *
 * \param EepromAddress Eeprom地址
 * \param DataBufferPtr 数据缓存
 * \param Length 数据长度
 *
 * \return E_OK-写入成功 E_NOT_OK-写入失败
 */
Std_ReturnType Eep_Write(Eep_AddressType EepromAddress, const uint8* DataBufferPtr, Eep_LengthType Length);


/**
 * \brief Eeprom擦除
 * \details 擦除指定地址长度的Eeprom存储空间
 *
 * \param EepromAddress Eeprom地址
 * \param Length Eeprom地址长度
 *
 * \return E_OK:擦除成功 E_NOT_OK:擦除失败
 */
Std_ReturnType Eep_Erase(Eep_AddressType EepromAddress, Eep_LengthType Length);


/**
 * \brief 比较指定地址的Eeprom数据
 *
 * \param EepromAddress Eeprom地址
 * \param DataBufferPtr 数据缓存
 * \param Length 数据长度
 *
 * \return E_OK-写入成功 E_NOT_OK-写入失败
 */
Std_ReturnType Eep_Compare(Eep_AddressType EepromAddress, const uint8* DataBufferPtr, Eep_LengthType Length);

/**
 * \brief 获取故障诊断信息
 * \details 用于获取Eeprom的诊断状态，此函数为非Autosar定义函数
 *
 * \param Status 诊断信息
 */
void Eep_GetDiagnosisStatus(Eep_ErrorType* Status);

/**
 * \brief Eeprom操作地址是否有效
 *
 * \param address eeprom操作地址
 * \return 如果不是Eeprom地址则返回E_NOT_OK，否则返回E_OK
 */
Std_ReturnType Eeprom_AddressIsValid(Eep_AddressType address);

#endif

/**
 * \}
 */