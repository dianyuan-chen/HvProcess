#ifndef __HCS12_I2C_PRIVATE_H__
#define __HCS12_I2C_PRIVATE_H__

#include "hcs12_i2c.h"
#include "derivative.h"

struct hcs12_i2c_regs {
    volatile IIC1_IBADSTR address;
    volatile IIC1_IBFDSTR freq_div;
    volatile IIC1_IBCRSTR control;
    volatile IIC1_IBSRSTR status;
    volatile IIC1_IBDRSTR dat;
    volatile IIC1_IBCR2STR control2;
};

struct hcs12_i2c_platform {
    struct hcs12_i2c_regs *near regs;
    uint8 freq_div;
};

struct hcs12_i2c {
    //struct hcs12_i2c_regs *regs;
    const struct hcs12_i2c_platform *platform;
    union {
        uint8 byte;
        struct {
            uint16 aquired: 1;
            uint16 txing: 1;
            uint16 rxing: 1;
            uint16 txing_addr: 1;
            uint16 txed_addr: 1;
        } bits;
    } flags;

    const uint8 *tx_data;
    uint8 *rx_data;
    uint8 tx_length;
    uint8 tx_index;
    uint8 rx_length;
    uint8 rx_index;
    uint8 slave_addr;
};

void hcs12_i2c_isr(struct hcs12_i2c *i2c);

extern const struct i2c_operations hcs12_i2c_ops;

#endif
