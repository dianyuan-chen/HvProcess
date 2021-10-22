/**
 * \file DeviceInfo.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 设备信息类型头文件.
 *
 * 这里详细说明.
 *
 * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170106 |
 */

/**
 * \addtogroup DeviceInfo 设备信息类型
 * \{
 */
#ifndef DEVICE_INFO_H_
#define DEVICE_INFO_H_

#include "Std_Types.h"
#include "App_Types.h"
#include "AT24.h"

#define DEVICEINFO_DEV_ERROR_DETECT     STD_OFF

/**
 * \brief 设备类型个数定义
 */
// #define DEVICE_BCU_TYPE_INDEX(TYPE)     ((uint8)(TYPE) - (uint8)DEVICE_TYPE_BCU_START)
// #define DEVICE_BAU_TYPE_INDEX(TYPE)     ((uint8)(TYPE) - (uint8)DEVICE_TYPE_BAU_START)
// #define DEVICE_BMU_TYPE_INDEX(TYPE)     ((uint8)(TYPE) - (uint8)DEVICE_TYPE_BMU_START)
//
// define DEVICE_BCU_TYPE_NUM             DEVICE_BCU_TYPE_INDEX(DEVICE_TYPE_BCU_STOP)
// #define DEVICE_BAU_TYPE_NUM             DEVICE_BAU_TYPE_INDEX(DEVICE_TYPE_BAU_STOP)
// #define DEVICE_BMU_TYPE_NUM             DEVICE_BMU_TYPE_INDEX(DEVICE_TYPE_BMU_STOP)
//
// #define DEVICE_IS_BCU_TYPE(TYPE)        ((TYPE) >= DEVICE_TYPE_BCU_START && (TYPE) <= DEVICE_TYPE_BCU_STOP)
// #define DEVICE_IS_BAU_TYPE(TYPE)        ((TYPE) >= DEVICE_TYPE_BAU_START && (TYPE) <= DEVICE_TYPE_BAU_STOP)
// #define DEVICE_IS_BMU_TYPE(TYPE)        ((TYPE) >= DEVICE_TYPE_BMU_START && (TYPE) <= DEVICE_TYPE_BMU_STOP)


/**
 * \brief 采集板支持的最大采集个数
 */
#define DEVICE_BOARD_SAMPLE_VOLT_NUM_MAX    12U
#define DEVICE_BOARD_SAMPLE_TEMP_NUM_MAX    4U

#define DEVICEINFO_FWVERSION_BUFFER_LENGTH      10U

/**
 * \brief 设备型号类型定义
 */
typedef enum{
    DEVICE_TYPE_UNKNOWN = 0x00U, /**< 未知设备 */

    DEVICE_TYPE_C600 = 0x01U, /**< 主机 */
    DEVICE_TYPE_C601 = 0x02U, /**< 同C600，支持远程无线数据通信 */
    DEVICE_TYPE_C602 = 0x03U, /**< 同C600，支持菊花链 */
    DEVICE_TYPE_C603 = 0x04U, /**< 同C602，支持远程无线数据通信 */

    DEVICE_TYPE_A600 = 0x80U, /**< 24路电压检测、8路温度检测、100mA被动均衡，其它同C600 */
    DEVICE_TYPE_A601 = 0x81U, /**< 24路电压检测、8路温度检测、100mA被动均衡，其它同C601 */
    DEVICE_TYPE_A602 = 0x82U, /**< 48路电压检测、8路温度检测、100mA被动均衡，其它同C600 */
    DEVICE_TYPE_A603 = 0x83U, /**< 48路电压检测、8路温度检测、100mA被动均衡，其它同C601 */
    DEVICE_TYPE_A650 = 0xA0U, /**< 24路电压检测、8路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A651 = 0xA1U, /**< 24路电压检测、8路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A652 = 0xA2U, /**< 48路电压检测、16路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A653 = 0xA3U, /**< 48路电压检测、16路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A660 = 0xA4U, /**< 36路电压检测、12路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A661 = 0xA5U, /**< 36路电压检测、12路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A640 = 0xB0U, /**< 12路电压检测、4路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A641 = 0xB1U, /**< 12路电压检测、4路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A655 = 0xA6U, /**< 24路电压检测、8路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A657 = 0xA7U, /**< 48路电压检测、16路温度检测、100mA被动均衡 */
    DEVICE_TYPE_A665 = 0xA8U, /**< 36路电压检测、12路温度检测、100mA被动均衡 */

    DEVICE_TYPE_M600 = 0x01U, /**< 2路高边输出、24路电压检测、12路温度检测、100mA被动均衡 */
    DEVICE_TYPE_M601 = 0x02U, /**< 2路高边输出、36路电压检测、12路温度检测、100mA被动均衡 */
    DEVICE_TYPE_M602 = 0x03U, /**< 2路高边输出、48路电压检测、12路温度检测、100mA被动均衡 */
    DEVICE_TYPE_M603 = 0x04U, /**< 2路高边输出、60路电压检测、12路温度检测、100mA被动均衡 */
    DEVICE_TYPE_M630 = 0x20U,
}DeviceInfo_DeviceTypeType;

/**
 * \brief 从机设备电池串数类型定义
 */
typedef enum{
    DEVICE_SLAVE_CELL_NUM_24, /**< 24串从机 */
    DEVICE_SLAVE_CELL_NUM_36, /**< 36串从机 */
    DEVICE_SLAVE_CELL_NUM_48, /**< 48串从机 */
    DEVICE_SLAVE_CELL_NUM_60, /**< 60串从机 */
    DEVICE_SLAVE_CELL_NUM_MAX
}DeviceInfo_SlaveCellNumTypeType;


typedef uint8 DeviceInfo_HwIDChannelType;
typedef uint8 DeviceInfo_FwVersionChannelType;
/**
 * \brief 设备信息类型定义
 */
typedef struct{
    uint8 HwID[AT24_HW_SERIAL_NUMBER_SIZE];
    uint8 FWVersion[DEVICEINFO_FWVERSION_BUFFER_LENGTH];
}DeviceInfo_DeviceInfoType;


extern uint16 DeviceInfo_ReceiveHWIDFlag;
extern uint16 DeviceInfo_ReceiveFWVersionFlag;

/**
 * \brief 获取对应通道的HWID
 *
 * \param channel 通道号
 * \param DataPtr 缓存指针
 * \param Length 缓存大小，返回实际写入长度
 */
void DeviceInfo_GetHWID(DeviceInfo_HwIDChannelType channel, uint8 *DataPtr, uint16 *Length);
const DeviceInfo_DeviceInfoType *DeviceInfo_GetPtr(void);

/**
 * \brief 获取对应通道的FW Version
 *
 * \param channel 通道号
 * \param DataPtr 缓存指针
 * \param Length 缓存大小，返回实际写入长度
 */
void DeviceInfo_GetFWVersion(DeviceInfo_HwIDChannelType channel, uint8 *DataPtr, uint16 *Length);

/**
 * \brief 检查对应通道HWID是否有效
 *
 * \param channel 通道号
 * \return E_OK: 有效 E_NOT_OK: 无效
 */
Std_ReturnType DeviceInfo_HWIDIsValid(DeviceInfo_HwIDChannelType channel);

/**
 * \brief 检查对应通道FW Version是否有效
 *
 * \param channel 通道号
 * \return E_OK: 有效 E_NOT_OK: 无效
 */
Std_ReturnType DeviceInfo_FWVersionIDIsValid(DeviceInfo_HwIDChannelType channel);


#endif

/**
 * \}
 */
