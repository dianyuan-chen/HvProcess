#ifndef I2C_H__
#define I2C_H__

#include "Std_Types.h"


typedef Std_ReturnType (*i2c_init_func)(void *private_data);
typedef uint8 (*i2c_transmit_func)(void *private_data,
                                   uint8 addr,
                                   const uint8 *w,
                                   uint8 wlen,
                                   uint8 *r,
                                   uint8 rlen);

typedef void (*i2c_deinit_func)(void *private_data);

struct i2c_operations {
    i2c_init_func init;
    i2c_deinit_func deinit;
    i2c_transmit_func transmit;
};

struct i2c_bus {
    void *private_data;
    const struct i2c_operations *ops;
};



#define i2c_init(bus) (bus)->ops->init((bus)->private_data)
#define i2c_transmit(bus, addr, w, wlen, r, rlen) (bus)->ops->transmit((bus)->private_data, addr, w, wlen, r, rlen)

#endif

