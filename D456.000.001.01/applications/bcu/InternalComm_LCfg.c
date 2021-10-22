/**
 * \file InternalComm_LCfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 内网通信链接配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20161215 |
 */

#include "InternalComm.h"
#include "InternalComm_Cfg.h"
#include "InternalComm_Cbk.h"
#include "HLSS_Cbk.h"
#include "BalanceM_Cbk.h"
#include "SystemConnection_Lcfg.h"

#if SYSTEM_BMU_NUM <= 4U
    #define INTERNALCOMM_CELL_VOLT_REQ_CYCLE    200U
    #define INTERNALCOMM_CELL_TEMP_REQ_CYCLE    200U
#elif SYSTEM_BMU_NUM <= 8U
    #define INTERNALCOMM_CELL_VOLT_REQ_CYCLE    300U
    #define INTERNALCOMM_CELL_TEMP_REQ_CYCLE    300U
#elif SYSTEM_BMU_NUM <= 12U
    #define INTERNALCOMM_CELL_VOLT_REQ_CYCLE    400U
    #define INTERNALCOMM_CELL_TEMP_REQ_CYCLE    400U
#else
    #define INTERNALCOMM_CELL_VOLT_REQ_CYCLE    500U
    #define INTERNALCOMM_CELL_TEMP_REQ_CYCLE    500U
#endif

/**
 * \内网通信DID请求周期默认值
 */
#define INTERNALCOMM_DID_CYCLE_DEFAULT      600U

/**
 * \brief 从机各DID请求参数定义
 */
const InternalComm_ScheduleItemType InternalComm_ScheduleItem[INTERNALCOMM_SLAVE_DID_NUM] = {
    /* 0 */
    {
        INTERNALCOMM_SLAVE_CELL_VOLTAGE_DID, /**< 从机物理连接单体电压DID */
        INTERNALCOMM_CELL_VOLT_REQ_CYCLE, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x480_Cbk /**< Request */
    },
    /* 1 */
    {
        INTERNALCOMM_SLAVE_CELL_TEMPERATURE_DID, /**< 从机物理连接温度值DID */
        INTERNALCOMM_CELL_TEMP_REQ_CYCLE, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x484_Cbk /**< Request */
    },
    /* 2 */
    {
        INTERNALCOMM_SLAVE_CELL_BALANCE_BYTE_DID, /**< 从机均衡状态DID */
        1000U, /**< Interval */
        BalanceM_GetSlaveBalanceControlSendData_Cbk, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x488_Cbk /**< Request */
    },
    /* 3 */
    {
        INTERNALCOMM_SLAVE_CELL_HSS_STATUS_DID, /**< 从机HLSS状态DID */
        1000U, /**< Interval */
        HLSS_GetDriveSlaveHlssSendData_Cbk, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x900_Cbk /**< Request */
    },
    /* 4 */
    {
        INTERNALCOMM_SLAVE_CELL_HSS_VOLTAGE_DID, /**< 从机HLSS反馈电压DID */
        2000U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x901_Cbk /**< Request */
    },
    /* 5 */
    {
        INTERNALCOMM_SLAVE_CELL_HSS_CURRENT_DID, /**< 从机HLSS反馈电流DID */
        2000U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x902_Cbk /**< Request */
    },
    /* 6 */
    {
        INTERNALCOMM_SLAVE_CELL_DIGITAL_INPUT_DID, /**< 从机数字输入反馈DID */
        2000U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0xF10_Cbk /**< Request */
    },
    /* 7 */
    {
        INTERNALCOMM_SLAVE_CELL_ANALOG_INPUT_DID, /**< 从机模拟输入反馈DID */
        2000U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0xF30_Cbk /**< Request */
    },
    /* 8 */
    {
        INTERNALCOMM_SLAVE_BOARD_VOLTAGE_DID, /**< 从机板载电压DID */
        2000U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x1600_Cbk /**< Request */
    },
    /* 9 */
    {
        INTERNALCOMM_SLAVE_BOARD_TEMPERATURE_DID, /**< 从机板载温度DID */
        2000U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x1620_Cbk /**< Request */
    },
    /* 10 */
    {
        INTERNALCOMM_FW_VERSION_DID, /**< 从机固件版本DID */
        3000U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0xA50C_Cbk /**< Request */
    },
    /* 11 */
    {
        INTERNALCOMM_HW_ID_DID, /**< 从机HWID DID */
        3000U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0xA50D_Cbk /**< Request */
    },
    /* 12 */
    {
        INTERNALCOMM_SLAVE_TEMPERATURE_TYPE_DID, /**< 从机HWID DID */
        100U, /**< Interval */
        InternalComm_GetRequireDidData, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x48B_Cbk /**< Request */
    },
    /* 13 */
    {
        INTERNALCOMM_SLAVE_TEMPERATURE_TYPE_CFG_DID, /**< 从机HWID DID */
        100U, /**< Interval */
        InternalComm_GetTemperatureTypeSendData_Cbk, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x48C_Cbk /**< Request */
    },
    /* 14 */
    {
        INTERNALCOMM_SLAVE_CELL_BALANCE_BITMAP_DID, /**< 从机HWID DID */
        1000U, /**< Interval */
        InternalComm_GetSlaveBalanceBitmapSendData_Cbk, /**< 获取通信数据回调函数 */
        InternalComm_RequestDID0x48D_Cbk /**< Request */
    },
};

/**
 * \brief 内网通信请求通道转换为Xgate数据处理通道
 */
const uint8 InternalComm_ReqChannelToXgate[] = {
    0U, 1U, 2U, 3U
};

/**
 * \brief Xgate软件数据处理通道转换为内网通信请求通道
 */
const uint8 InternalComm_XgateSoftwareIsrChlToReq[] = {
    0U, 1U, 2U, 3U
};

const InternalComm_ConfigInfoType InternalComm_ConfigInfo = {
    NULL, /**< recVoltHook: 接收到电压数据钩子函数 */
    NULL, /**< recTempHook: 接收到温度数据钩子函数 */
};
