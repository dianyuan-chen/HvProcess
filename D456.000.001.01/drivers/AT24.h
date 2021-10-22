/**
 * \addtogroup Drivers
 * \{
 * \addtogroup AT24 Atmel I2C EEPROM 驱动
 * \{
 */
#ifndef AT24_H_
#define AT24_H_

#include "Std_Types.h"
#include "i2c.h"
#include "AT24_Cfg.h"

/** brief AT24 EEPROM配置数据结构体. */
typedef struct {
    struct i2c_bus bus; /**< 芯片连接的I2C总线 */
    uint8 addr; /**< 芯片地址线A[2:0]的配置 */
} AT24_ConfigType;

/**
 * \brief 读取芯片的序列号.
 *
 * \param[in] at24 配置数据指针.
 * \param[out] serial 用于保存读取到的序列号.
 *
 * \retval E_OK 读取成功.
 * \retval E_OK 读取失败.
 *
 * \note 传入的serial缓冲大小必须不小于16字节.
 */
Std_ReturnType AT24_ReadSerialNum(const AT24_ConfigType *at24, uint8 serial[16]);

#endif

/**
 * \}
 * \}
 */