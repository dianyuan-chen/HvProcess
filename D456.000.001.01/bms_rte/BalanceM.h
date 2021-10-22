/**
 * \file BalanceM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 均衡管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161207 |
 */

/**
 * \addtogroup BalanceM 均衡管理
 * \{
 */

#ifndef BALANCEM_H_
#define BALANCEM_H_

#include "Std_Types.h"
#include "BalanceM_Cfg.h"
#include "DeviceInfo.h"
#include "App_Types.h"
#include "CellDataM.h"
#include "Async_Event.h"
#include "Diagnosis.h"
#include "InternalComm.h"

/**
 * \从机均衡状态控制DID
 */
#define BALANCEM_SLAVE_BALANCE_CONTROL_DID  0x488U

/**
 * \brief 从机均衡控制电池编号无效值
 */
#define BALANCE_SLAVE_BALANCE_INVALID_BAT_NUM   0xFFU

typedef boolean (*RemoteBalanceEnable)(void);
/**
 * \brief 均衡类别定义
 */
typedef enum{
    BALANCEM_BALANCE_NONE, /**< 无均衡 */
    BALANCEM_BALANCE_PASSTIVE, /**< 被动均衡 */
    BALANCEM_BALANCE_ACTIVE, /**< 主动均衡 */
}BalanceM_BalanceCategoryType;

/**
 * \brief 均衡类型定义
 */
typedef enum{
    BALANCE_CHARGE_BALANCE, /**< 充电均衡 */
    BALANCE_STATIC_BALANCE, /**< 静态均衡 */
    BALANCE_REMOTE_BALANCE, /**< 远程均衡 */
}BalanceM_BalanceTypeType;

typedef enum{
    BALANCEM_REFERENCE_AVERAGE, /**< 平均电压为参考基准 */
    BALANCEM_REFERENCE_LV_MAX, /**< 最低电压为参考基准 */
}BalanceM_ReferenceTypeType;

/**
 * \brief 均衡管理均衡配置类型
 */
typedef struct{
    uint8 balance_en; /**< 均衡使能控制 */
    App_VoltageType start_voltage; /**< 均衡启动电压 */
    App_VoltageType voltage_min; /**< 均衡最小电压 */
    App_VoltageType delta_volt_min; /**< 均衡最小压差 */
    App_VoltageType delta_volt_max; /**< 均衡最大压差 */
}BalanceM_BalanceConfigType;

typedef struct{
    uint8 balance_en; /**< 均衡使能控制 */
    RemoteBalanceEnable func; /**< 均衡启动电压 */
    uint32 enable_default_balance_time; /**< 超过该时间没有接收到远程均衡指令就开启默认均衡 */
}BalanceM_RemoteBalanceConfigType;

/**
 * \brief 均衡管理配置类型
 */
typedef struct{
    BalanceM_BalanceCategoryType type; /**< 均衡类别 */
    BalanceM_BalanceConfigType chg_bal_config; /**< 充电均衡参数配置 */
    BalanceM_BalanceConfigType stc_bal_config; /**< 静态均衡参数配置 */
    BalanceM_RemoteBalanceConfigType remote_bal_config; /**< 远程均衡参数配置 */
    Diagnosis_LevelType disable_bal_ht_level; /**< 禁止均衡高温等级 */
    Diagnosis_LevelType disable_bal_lv_level; /**< 禁止均衡低压等级 */
    BalanceM_ReferenceTypeType reference; /**< 参考基准电压 */
    uint16 current_max; /**< 均衡允许最大充放电电流 */
}BalanceM_ConfigType;

/**
 * \brief 均衡控制命令类型定义
 */
typedef enum{
    BALANCEM_COMMAND_NORMAL, /**< 正常策略命令 */
    BALANCEM_COMMAND_FORCE, /**< 强控命令 */
}BalanceM_CommandTypeType;

/**
 * \brief 均衡控制命令参数类型定义
 */
typedef struct{
    BalanceM_CommandTypeType type; /**< 均衡命令类型 */
    uint8 command[BALANCEM_BALANCE_COMMAND_BUFFER_SIZE]; /**< 均衡开启命令缓存，存放均衡电池编号 */
}BalanceM_CommandInfoType;

/**
 * \brief 声明外部均衡管理模块配置参数
 */
extern const BalanceM_ConfigType BalanceM_ConfigInfo;

/**
 * \brief 均衡控制命令缓存定义
 * \note 用于存放各从机的均衡控制命令
 */
extern BalanceM_CommandInfoType BalanceM_BalanceCommand[BCU_SLAVE_NUM_MAX];

/**
 * \brief 均衡管理模块初始化
 *
 * \param config 均衡管理配置参数
 */
void BalanceM_Init(const BalanceM_ConfigType *config);

void BalanceM_RegisterLooper(Async_LooperType *looper);

/**
 * \brief 均衡管理模块反初始化
 */
void BalanceM_Deinit(void);

/**
 * \brief 更新从机均衡控制状态
 * \details 当此从机不在强控均衡状态下，可更新此从机正常均衡控制状态，由内网通信主动获取此状态来控制从机均衡
 *
 * \param SlaveNum 从机号
 * \param DataPtr 从机内均衡控制电池编号缓存
 * \param Length 缓存长度
 */
void BalanceM_SlaveBalanceDrive(App_SlaveIdType SlaveNum, const uint8 *DataPtr, uint8 Length);

/**
 * \brief 更新从机均衡强制控制状态
 * \details 更新此从机均衡强制控制状态，由内网通信主动获取此状态来控制从机均衡
 *
 * \param SlaveNum 从机号
 * \param DataPtr 从机内均衡强制控制电池编号缓存
 * \param Length 缓存长度
 */
void BalanceM_SlaveBalanceForce(App_SlaveIdType SlaveNum, const uint8 *DataPtr, uint8 Length);

/**
 * \brief 获取均衡状态
 * \note 本函数用于获取所有从机的实际均衡状态
 *
 * \param status 存储获取到的均衡状态 位图形式
 * \return 返回均衡字节长
 */
uint8 BalanceM_GetBalanceStatus(uint8* status);
const uint8 *BalanceM_GetBalanceStatusPtr(void);

/**
 * \brief 取消从机均衡强制控制状态
 * \details 取消此从机均衡强制控制状态，同时更新从机均衡控制电池编号缓存为无效状态
 *
 * \param SlaveNum 从机号
 */
void BalanceM_SlaveBalanceForceCancle(App_SlaveIdType SlaveNum);

/**
 * \brief 获取均衡控制命令
 * \note 本函数用于获取从机的实际均衡控制命令
 *
 * \param SlaveNum 从机号
 * \param command 存储获取到的均衡控制命令，返回对应从机当前控制均衡的电池编号
 * \return 获取到的命令长度
 */
uint8 BalanceM_GetBalanceCommand(App_SlaveIdType SlaveNum, uint8* command);

/**
 * \brief 从机是否为强制均衡控制状态
 *
 * \param SlaveNum 从机号
 * \return 0-ECU控制 1-强制控制
 */
uint8 BalanceM_IsForceBalance(App_SlaveIdType SlaveNum);

/**
 * \brief BMS是否正常进行均衡
 * \return FALSE-未均衡 TRUE-正在均衡
 */
boolean BalanceM_IsBalance(void);

/**
 * \brief 获取当前均衡配置指针
 */
const BalanceM_ConfigType* BalanceM_GetConfigPtr(void);

/**
 * \brief 获取均衡指令，0x48D，按位发送，每个采集板开6串
 */
void InternalComm_GetSlaveBalanceBitmapSendData_Cbk(App_SlaveIdType SlaveNum, InternalComm_DidTypes Did, InternalComm_MsgType DataBufferPtr, InternalComm_MsgLenType *Length);

/**
 * \brief 获取均衡状态,每个采集板开6串
 */
void BalanceM_RxBalanceNewStatusBitmapIndication(App_SlaveIdType SlaveNum, const uint8 *DataPtr, uint16 Length);

#endif

/**
 * \}
 */
