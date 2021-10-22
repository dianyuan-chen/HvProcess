#ifndef __HCS12_I2C_H__
#define __HCS12_I2C_H__

#include "Std_Types.h"


typedef struct hcs12_i2c *hcs12_i2c_t;

/// \brief hcs12_i2c_init 初始化.
///
/// \param i2c 对应的IO底层接口.
Std_ReturnType hcs12_i2c_init(hcs12_i2c_t i2c);

void hcs12_i2c_deinit(hcs12_i2c_t i2c);

/// \brief hcs12_i2c_write I2C些数据.
///
/// \param i2c 对应的IO底层接口.
/// \param addr SLAVE地址, 7位, 不包含读写位, 最终总线上的第一个8位周期为:(addr << 1).
/// \param dat 需要写入的数据.
/// \param len 需要写入的数据的长度.
///
/// \return 写入的数据的长度.
uint8 hcs12_i2c_write(hcs12_i2c_t i2c,
                      uint8 addr,
                      const uint8 *dat,
                      uint8 len);

/// \brief hcs12_i2c_read I2C读取数据.
///
/// \param i2c 对应的IO底层接口.
/// \param addr SLAVE地址, 7位, 不包含读写位, 最终总线上的第一个8位周期为:((addr << 1) + 1).
/// \param dat 读取的数据存放的地址.
/// \param len 期望读取的数据长度.
///
/// \return 已读取的数据的长度.
uint8 hcs12_i2c_read(hcs12_i2c_t i2c,
                     uint8 addr,
                     uint8 *dat,
                     uint8 len);

/// \brief hcs12_i2c_write_then_read 先写后读.
///
/// \param i2c 对应的IO底层接口.
/// \param addr SLAVE地址, 7位, 不包含读写位, 最终总线上的第一个8位周期为:((addr << 1) + RW).
/// \param w 需要写入的数据.
/// \param wlen 需要写入的数据的长度.
/// \param r 读取的数据存放的地址.
/// \param rlen 期望读取的数据长度.
///
/// \return 写入和读取的数据的字节数相加.
uint8 hcs12_i2c_write_then_read(hcs12_i2c_t i2c,
                                uint8 addr,
                                const uint8 *w,
                                uint8 wlen,
                                uint8 *r,
                                uint8 rlen);

///  @}
#endif

