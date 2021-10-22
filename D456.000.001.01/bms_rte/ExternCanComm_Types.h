/**
 * \file ExternCanComm_Types.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 扩展CAN通信类型定义头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170309 |
 */

/**
 * \addtogroup ExternCanComm 扩展CAN通信
 * \{
 */

#include "ComStack_Types.h"
#include "App_Types.h"

#ifndef EXTERNCANCOMM_TYPES_H_
#define EXTERNCANCOMM_TYPES_H_

#define EXTERNCANCOMM_PROTOCOL_IS_GB(protocol)    (((protocol) == EXTERNCANCOMM_PROTOCOL_GB2015) || \
                                                    ((protocol) == EXTERNCANCOMM_PROTOCOL_GB2011))

/**
 * \brief 定义扩展CAN通信单个充电通信阶段监控接收报文的最大个数
 */
#define EXTERNCANCOMM_MONITOR_REC_MSG_NUM_PER_STAGE   5U
#define EXTERNCANCOMM_REC_TRIGGER_RECEIVE_DATA        0x80U

/**
 * \brief 扩展CAN通信数据发送回调函数类型定义
 */
typedef void (*ExternCanCommSendFuncCbk)(uint8 *dataPtr, uint16 *Length);

/**
 * \brief 发送条件检查函数类型定义
 */
typedef Std_ReturnType (*CharerCommSendCondCheckFunc)(void);

/**
 * \brief 扩展CAN通信数据接收回调函数类型定义
 */
typedef void (*ExternCanCommRecFuncCbk)(const uint8 *dataPtr, uint16 Length);

/**
 * \brief 获取接收报文超时参数
 *
 * \return 超时时间
 */
typedef uint16 (*ExternCanCommGetRecIPduTimeout)(void);

/**
 * \brief 扩展CAN通信报文接收超时回调函数类型定义
 */
typedef void (*ExternCanCommRecTimeoutCbk)(void);

/**
 * \brief 扩展CAN通信发送Ipdu配置类型定义
 */
typedef struct{
    PduIdType IPdu; /**< 发送IPdu */
    uint16 Length; /**< 发送数据长度 */
    uint16 Cycle; /**< 数据发送周期 */
    CharerCommSendCondCheckFunc CondFunc; /**< 发送条件检查函数 */
    ExternCanCommSendFuncCbk Func; /**< 数据发送回调函数 */
}ExternCanComm_SendIPduCfgType;

/**
 * \brief 扩展CAN通信接收Ipdu信息类型定义
 */
typedef struct{
    PduIdType IPdu; /**< 接收IPdu */
    uint16 Length; /**< 数据长度 */
    uint16 Timeout; /**< 超时时间 */
    ExternCanCommGetRecIPduTimeout TimeoutFunc; /**< 获取IPdu超时时间回调函数，当此函数有效时，Timeout配置参数无效 */
    ExternCanCommRecFuncCbk RecFunc; /**< 数据接收回调函数 */
    ExternCanCommRecTimeoutCbk TimeoutEventFunc; /**< 数据接收超时事件回调函数 */
}ExternCanComm_RecIPduInfoType;

/**
 * \brief 扩展CAN通信接收IPdu配置类型定义
 */
typedef struct{
    uint8 IPduNum; /**< IPdu个数 */
    const ExternCanComm_RecIPduInfoType *IPduInfo; /**< 各IPdu配置信息 */
}ExternCanComm_RecIPduCfgType;

/**
 * \brief 扩展CAN协议类型定义
 */
typedef enum{
    EXTERNCANCOMM_PROTOCOL_NONE = 0, /**< 无通信协议 */
    EXTERNCANCOMM_PROTOCOL_GB2011 = 1, /**< 2011国标通信协议 */
    EXTERNCANCOMM_PROTOCOL_GB2015 = 2, /**< 2015国标通信协议 */
    EXTERNCANCOMM_PROTOCOL_GB = EXTERNCANCOMM_PROTOCOL_GB2015, /**< 国标通信协议 */
    EXTERNCANCOMM_PROTOCOL_USER  = 3, /**< 用户协议，默认为铁城协议 */
}ExternCanComm_ProtocolType;


/**
 * \brief 扩展CAN通信配置类型定义
 */
typedef struct{
    ExternCanComm_ProtocolType Protocol; /**< 协议 */
    uint8 RelayType; /**< 继电器 */
    uint8 SendRetryNum; /**< 发送重试次数 */
    App_VoltageType CellDeltaVoltMinForCV; /**< 满足恒压时单体电芯最小压差设定值 */
}ExternCanComm_ConfigType;


/**
 * \brief 扩展CAN通信IPdu类型定义
 * \notes 格式：国标优先，发送报文优先
 */

extern const PduIdType EXTERNCANCOMM_TX_IPDU_GB_START;
extern const PduIdType EXTERNCANCOMM_TX_IPDU_GB_STOP;

extern const PduIdType EXTERNCANCOMM_RX_IPDU_GB_START;
extern const PduIdType EXTERNCANCOMM_RX_IPDU_GB_STOP;


/**
 * \brief 扩展CAN自诊断类型定义
 */
typedef enum{
    EXTERNCANCOMM_SELFDIAG_NORMAL = 0,
    EXTERNCANCOMM_SELFDIAG_BMS_FAULT_START = 1, /**< BMS停止充电原因开始 */
    EXTERNCANCOMM_SELFDIAG_BMS_FULL_CHARGE = EXTERNCANCOMM_SELFDIAG_BMS_FAULT_START, /**< 满充停止充电 */
    EXTERNCANCOMM_SELFDIAG_BMS_HTV = 2, /**< 总压过高故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_HV = 3, /**< 单体过充故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_LTV = 4, /**< 总压过低故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_LV = 5, /**< 单体过低故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_DV = 6, /**< 压差过大故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_DT = 7, /**< 温差过大故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_SLAVE_COMM = 8, /**< 内网通信中断故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_VOLT_LINE = 9, /**< 电压排线故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_TEMP_LINE = 10, /**< 温感排线故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_LSOC = 11, /**< SOC过低故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_HSOC = 12, /**< SOC过高故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_LEAK = 13, /**< 漏电故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_HT = 14, /**< 高温故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_LT = 15, /**< 低温故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_OCC = 16, /**< 充电过流故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_ODC = 17, /**< 放电过流故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_TV_EXCEPTION = 18, /**< 总压异常 */
    EXTERNCANCOMM_SELFDIAG_BMS_RELAY_FAULT = 19, /**< 继电器故障 */
    EXTERNCANCOMM_SELFDIAG_BMS_FAULT_STOP = EXTERNCANCOMM_SELFDIAG_BMS_RELAY_FAULT, /**< BMS停止充电原因结束 */

    EXTERNCANCOMM_SELFDIAG_CHR_COMMON_FAULT_START = 20, /**< 充电机停止充电通用故障开始  */
    EXTERNCANCOMM_SELFDIAG_CHR_NOT_ENABLE = EXTERNCANCOMM_SELFDIAG_CHR_COMMON_FAULT_START, /**< 充电机通信未使能 */
    EXTERNCANCOMM_SELFDIAG_CHR_NOT_CONNECT = 21, /**< 充电机未连接 */
    EXTERNCANCOMM_SELFDIAG_CHR_TIMEOUT_CNT = 22, /**< 通信超时计数过多 */
    EXTERNCANCOMM_SELFDIAG_CHR_POSITIVE_STOP = 23, /**< 充电机主动停止充电 */
    EXTERNCANCOMM_SELFDIAG_CHR_COMMON_FAULT_STOP = EXTERNCANCOMM_SELFDIAG_CHR_POSITIVE_STOP, /**< 充电机停止充电通用故障结束 */

    EXTERNCANCOMM_SELFDIAG_CHR_GB_FAULT_START = 24, /**< 国标充电机停止充电故障开始 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3901 = EXTERNCANCOMM_SELFDIAG_CHR_GB_FAULT_START, /**< 接收国标充电机未就绪辨识报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3902 = 25, /**<接收充电机就绪辨识报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3903 = 26, /**<接收充电机最大输出能力报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3904 = 27, /**<接收充电机完成充电准备报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3905 = 28, /**<接收充电机充电状态报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3906 = 29, /**<接收充电机中止充电报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3907 = 30, /**<接收充电机充电统计报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3921 = 31, /**<接收BMS辨识报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3922 = 32, /**<接收BMS充电参数报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3923 = 33, /**<接收BMS完成充电准备报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3924 = 34, /**<接收BMS电池总状态报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3925 = 35, /**<接收BMS充电要求报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3926 = 36, /**<接收BMS中止充电报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3927 = 37, /**<接收BMS充电统计报文超时 */
    EXTERNCANCOMM_SELFDIAG_CHR_GB_FAULT_STOP = EXTERNCANCOMM_SELFDIAG_CHR_GB_SPN3927, /**<  国标充电机停止充电故障结束 */

    EXTERNCANCOMM_SELFDIAG_OTHERS = 38, /**< 其他故障 */
    EXTERNCANCOMM_SELFDIAG_MAX = 39
}ExternCanComm_SelfDiagnosisType;


typedef enum{
    EXTERNCANCOMM_STAGE_IDLE = 0, /**< 空闲状态 */

    EXTERNCANCOMM_STAGE_GB_START = 1,
    EXTERNCANCOMM_STAGE_GB_COMM_WAITING = EXTERNCANCOMM_STAGE_GB_START, /**< 国标通信：等待充电机通信 */
    EXTERNCANCOMM_STAGE_GB_CHM_TO_CRM = 2, /**< 国标通信：从握手启动阶段进入握手辨识阶段 */
    EXTERNCANCOMM_STAGE_GB_CRM = 3, /**< 直接进入握手辨识阶段 V2011 */
    EXTERNCANCOMM_STAGE_GB_RECOMM_CRM = 4, /**< 充电失败重新进入握手辨识阶段 */
    EXTERNCANCOMM_STAGE_GB_CRM_AA = 5, /**< 等待握手辨识成功阶段 */
    EXTERNCANCOMM_STAGE_GB_CTS_CML = 6, /**< 充电配置阶段 */
    EXTERNCANCOMM_STAGE_GB_CRO = 7, /**< 充电未就绪阶段 */
    EXTERNCANCOMM_STAGE_GB_CCS = 8, /**< 充电阶段 */
    EXTERNCANCOMM_STAGE_GB_CST_CSD = 9, /**< 中止充电及统计阶段 */
    EXTERNCANCOMM_STAGE_GB_CEM = 10, /**< 充电故障阶段 */
    EXTERNCANCOMM_STAGE_GB_STOP = EXTERNCANCOMM_STAGE_GB_CEM,

    EXTERNCANCOMM_STAGE_MAX = 11
}ExternCanComm_StageType;

/**
 * \brief 扩展CAN充电机异常状态
 */
typedef enum
{
    EXTERNCANCOMM_CHR_HARDWARE_FAULT_INDEX,                   /**< 充电机硬件故障编号 */
    EXTERNCANCOMM_CHR_OVER_TEMPERATURE_FAULT_INDEX,           /**< 充电机温度异常编号 */
    EXTERNCANCOMM_CHR_INPUT_VOLT_FAULT_INDEX,                 /**< 充电机输入电压异常编号 */
    EXTERNCANCOMM_CHR_RUN_STATUS_INDEX,                       /**< 充电机运行（启动）状态编号 */
    EXTERNCANCOMM_CHR_COMM_ABORT_WITH_BMS_INDEX,              /**< BMS通信故障编号 */
    EXTERNCANCOMM_CHR_OUTPUT_VOLT_FAULT_INDEX,                /**< 充电机输出电压异常编号 */
    EXTERNCANCOMM_CHR_BATTERY_REVERSE_CONNECT_INDEX,          /**< 电池反接异常编号 */
    EXTERNCANCOMM_CHR_STOP_CHG_WITH_FINISH,                   /**< 充电机充电达到完成条件停止充电状态编号 */
    EXTERNCANCOMM_CHR_INNER_OVER_TEMPERATURE_FAULT_INDEX,     /**< 充电机内部过温异常编号 */
    EXTERNCANCOMM_CHR_CHAGER_CONNECTOR_FAULT_INDEX,           /**< 充电连接器异常编号 */
    EXTERNCANCOMM_CHR_ENERGY_TRANSIMIT_FAULT_INDEX,           /**< 充电电量不能传输异常编号 */
    EXTERNCANCOMM_CHR_EMERGENCY_STOP_INDEX,                   /**< 充电机急停状态编号 */
    EXTERNCANCOMM_CHR_CURRENT_NOT_MATCH_INDEX,                /**< 电流不匹配编号 */
    EXTERNCANCOMM_CHR_PHASE_LACK_FAULT_INDEX,                 /**< 缺相异常编号 */
    EXTERNCANCOMM_CHR_HIGH_VOLT_ALARM_INDEX,                  /**< 充电机过压报警编号 */
    EXTERNCANCOMM_CHR_HIGH_CURRENT_ALARM_INDEX,               /**< 充电机过流报警编号 */
    EXTERNCANCOMM_CHR_OVER_PROTECT_VOLT_INDEX,                /**< 电池总压越充电机保护上限编号 */
    EXTERNCANCOMM_CHR_OVER_PROTECT_CURR_INDEX,                /**< 总电流越充电机保护上限编号 */
    EXTERNCANCOMM_CHR_OVER_NOMINAL_VOLT_INDEX,                /**< 电池总压越充电机额定总压上限编号 */
    EXTERNCANCOMM_CHR_OVER_NOMINAL_CURR_INDEX,                /**< 总电流越充电机额定电流上限编号 */
    EXTERNCANCOMM_CHR_BMS_STOP_CHARGE_FAULT_INDEX,            /**< BMS停止充电状态编号 */
    EXTERNCANCOMM_CHR_FAULT_FAULT_INDEX,                      /**< 充电机其他故障编号 */
    EXTERNCANCOMM_CHR_COMM_ABORT_WITH_CHARGE_SPOT_INDEX,      /**< 充电机与充电桩通信中断编号 */
    EXTERNCANCOMM_CHR_CHARGE_SPOT_ENERGENCY_STOP_INDEX,       /**< 充电桩急停状态编号 */
    EXTERNCANCOMM_CHR_MANUAL_STOP_INDEX,                      /**< 人工停止充电状态编号 */
    EXTERNCANCOMM_CHR_FAULT_INDEX_MAX
}ExternCanComm_ChargerFaultType;

#endif

/**
 * \}
 */
