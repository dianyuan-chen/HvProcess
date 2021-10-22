#ifndef NTC_H_
#define NTC_H_

#include "Std_Types.h"

typedef struct {
    uint16 dataId;
    sint8 offset;
    uint8 length;
    uint8 isPtOrder;
    const uint16 *tabV4096;
} NTC_ConfigDataType;

typedef struct {
    uint16 crc;
}NTC_InnerDataType;

extern const NTC_ConfigDataType *const CellNTCConfigData;
extern const NTC_ConfigDataType *const DCChgSckNTCConfigData;
extern const NTC_ConfigDataType *const ACChgSckNTCConfigData;
extern const NTC_ConfigDataType *const OnboardNTCConfigData;

/**
 * \brief 温感模块初始化
 */
void NTC_Init(void);

/**
 * \brief 把温感电压根据温感表转换成温度值.
 *
 * \param cfgData 温感表
 * \param vol 电压
 *
 * \return 温度值
 */
uint8 NTC_FromRef4096(const NTC_ConfigDataType *cfgData, uint16 vol);

/**
 * \brief 把单体温感的电压转换成温度值.
 *
 * \param vol 电压
 *
 * \return 温度值
 */
uint8 NTC_CellFromRef4096(uint16 vol);

/**
 * \brief 把充电插座温感的电压转换成温度值.
 *
 * \param vol 电压
 *
 * \return 温度值
 */
uint8 NTC_ACChgSckTemperatureFromTAB(uint16 vol);
uint8 NTC_DCChgSckTemperatureFromTAB(uint16 vol);

/**
 * \brief 把板载温感的电压转换成温度值.
 *
 * \param vol 电压
 *
 * \return 温度值
 */
uint8 NTC_OnboardFromRef4096(uint16 vol);

/**
 * \brief 获取电池温感类型CRC校验值
 * \details 校验包含NTC_ConfigDataType定义及温感数组
 * \return 校验值
 */
uint16 NTC_GetCellCrc(void);


#endif
