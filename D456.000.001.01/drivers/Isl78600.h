#ifndef __ISL78600_H__
#define __ISL78600_H__

#include "Std_Types.h"
#include "Dio.h"
#include "spi_bus.h"
#include "Isl78600_Cfg.h"


#if 1
#define ISL78600ISERR_R_W 0U
#define ISL78600ISERR_R 1U

typedef uint8 IslScanModeType;
#define kIslScanIndex_Voltage     0U
#define kIslScanIndex_Temp        1U
#define kIslScanIndex_Wire        2U
#define kIslScanIndexMax          3U

typedef uint8 Isl_ReturnType;
#define ISL_E_OK                  0U
#define ISL_E_NOT_OK              1U
#define ISL_E_CRC                 2U
#define ISL_E_NAK                 3U
#define ISL_E_PAGE                4U
#define ISL_E_REG                 5U
#define ISL_E_BUSY                6U
#define ISL_E_UNREADY             7U
#define ISL_E_COMM                8U
#define ISL_E_REF                 9U
#define ISL_E_RXABORT             10U
#else
typedef enum {
    kIslScanIndex_Voltage,
    kIslScanIndex_Temp,
    kIslScanIndex_Wire,

    kIslScanIndexMax
} IslScanModeType;

typedef enum {
    ISL_E_OK,
    ISL_E_NOT_OK,
    ISL_E_CRC,
    ISL_E_NAK,
    ISL_E_PAGE,
    ISL_E_REG,
    ISL_E_BUSY,
    ISL_E_UNREADY,
    ISL_E_COMM,
} Isl_ReturnType;
#endif

struct Isl78600_AllVoltage {
    uint16 value[12];
};

struct Isl78600_AllTemp {
    uint16 value[4];
};

struct Isl78600_PrivateType {
    uint8 device_num;
};

struct Isl78600 {
    struct Isl78600_PrivateType *private_data;
    uint8 flags;
    const struct spi_bus *bus;
    Dio_ChannelType dready;
    Dio_LevelType dready_level;
};

Isl_ReturnType Isl78600_SendCmd(const struct Isl78600 *dev, uint8 addr, uint8 page, uint8 reg, uint8 suffix);
Isl_ReturnType Isl78600_ReadData(const struct Isl78600 *dev, uint8 addr, uint8 page, uint8 reg, uint16 *value);
Isl_ReturnType Isl78600_WriteData(const struct Isl78600 *dev, uint8 addr, uint8 page, uint8 reg, uint16 value);
Isl_ReturnType Isl78600_Init(const struct Isl78600 *dev, uint8 num);
Isl_ReturnType Isl78600_Identify(const struct Isl78600 *dev);
Isl_ReturnType Isl78600_Scan(const struct Isl78600 *dev, IslScanModeType type);
Isl_ReturnType Isl78600_GetAllVoltageWithSetup(const struct Isl78600 *dev, uint8 addr, struct Isl78600_AllVoltage *v, uint16 setup);
Isl_ReturnType Isl78600_GetAllVoltage(const struct Isl78600 *dev, uint8 addr, struct Isl78600_AllVoltage *v);
Isl_ReturnType Isl78600_GetAllTempValueWithSetup(const struct Isl78600 *dev, uint8 addr, struct Isl78600_AllTemp *t, uint8 setup);
Isl_ReturnType Isl78600_GetAllTempValue(const struct Isl78600 *dev, uint8 addr, struct Isl78600_AllTemp *t);
Isl_ReturnType Isl78600_SetBalanceFlag(const struct Isl78600 *dev, uint8 addr, uint16 flags);
Isl_ReturnType Isl78600_GetBalanceFlag(const struct Isl78600 *dev, uint8 addr, uint16 *flags);
Isl_ReturnType Isl78600_GetSerialNum(const struct Isl78600 *dev, uint8 addr, uint32 *sn);
Isl_ReturnType Isl78600_GetOpenWireFlag(const struct Isl78600 *dev, uint8 addr, uint16 *flags);
Isl_ReturnType Isl78600_ClrOpenWireFlag(const struct Isl78600 *dev, uint8 addr);
Isl_ReturnType Isl78600_Reset(const struct Isl78600 *dev, uint8 addr);
Isl_ReturnType Isl78600_GetScanCount(const struct Isl78600 *dev, uint8 addr, uint16 *cnt);
Isl_ReturnType Isl78600_SetCellMask(const struct Isl78600 *dev, uint8 addr, uint16 mask);
Isl_ReturnType Isl78600_SetDeviceSetup(const struct Isl78600 *dev, uint8 addr, uint16 value);

uint16 Isl78600IsErr(const struct Isl78600 *dev, uint8 flag);
Isl_ReturnType Isl78600_CheckRef(const struct Isl78600 *dev, uint8 addr);
extern const struct Isl78600 isl78600_dev;

#endif
