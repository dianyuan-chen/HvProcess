#ifndef HMI_H__
#define HMI_H__

#include "Async_Event.h"

Std_ReturnType Hmi_Init(Async_LooperType *looper, uint32 baud);



typedef struct Modbus_ReadRegion {
    uint16 startaddr; /*功能函数可处理的起始地址*/
    uint16 endaddr; /*功能函数可处理的结束地址*/
    uint16 (*getRegisterValue)(const struct Modbus_ReadRegion *regs, uint16 addr);
            /*功能函数。参数说明：regs,为当前结构体; addr,当前读取目标地址。可利用addr减去起始地址得到偏移地址*/
} Modbus_ReadRegionType;

typedef struct {
    const Modbus_ReadRegionType *regRegions;
    uint8 regionsNum;
    uint8 addrIncEachWord;/*读取目标是coil还是register. 16->coil, 1->register*/
} Modbus_ReadTableType;

typedef struct Modbus_WriteRegion {
    uint16 startaddr;
    uint16 endaddr;
    void (*WriteRegisterValue)(const struct Modbus_WriteRegion *regs, uint16 addr, const uint8 *dat, uint16 len);
} Modbus_WriteRegionType;

typedef struct {
    const Modbus_WriteRegionType *regRegions;
    uint8 regionsNum;
    uint8 addrIncEachWord;/*写入目标是coil还是register. 16->coil, 1->register*/
} Modbus_WriteTableType;

/*modbus功能初始化结构体，需在Hmi_Lcfg.c中配置*/
typedef struct {
    uint8  slaveaddr;/*从机地址*/
    uint8  broadcastaddr;/*广播地址*/
    uint16 CRCpolynomial;/*CRC校验多项式*/
    uint16 CRCInit;/*CRC校验初始值*/
    uint16 FrameTimeout; /*帧超时时间ms*/
    Modbus_ReadTableType Modbus_X01registerTable;/*01功能码的处理结构体*/
    Modbus_ReadTableType Modbus_X02registerTable;/*02功能码的处理结构体*/
    Modbus_ReadTableType Modbus_X03registerTable;/*03功能码的处理结构体*/
    Modbus_ReadTableType Modbus_X04registerTable;/*04功能码的处理结构体*/
    Modbus_WriteTableType Modbus_X06registerTable;/*06功能码的处理结构体*/
    Modbus_WriteTableType Modbus_X16registerTable;/*16功能码的处理结构体*/
} Modbus_Cfg;

extern const Modbus_Cfg ModbusCfg;


#endif
