
#ifndef SYSTEMCONNECTION_H_
#define SYSTEMCONNECTION_H_


#include "DeviceInfo.h"

/**
 * \电池数据参数管理配置类型
 */
#pragma push
#pragma align on

typedef struct{
    App_SlaveIdType SlaveNum; /**< 从机个数 */
    boolean DtuSupport; /**< 是否支持内置DTU */
    boolean BcuIsAllInOne; /** 是否为一体机 */
    DeviceInfo_DeviceTypeType BcuType; /**< 主机类型 */

    uint8 heatTemperatureEnable; /**< 加热温感使能 */
    uint8 poleTemperatureEnable; /**< 极柱温感使能 */
    uint16 voltageNum; /**< 电池电压个数 */
    uint16 voltageSampleBoardNum; /**< 电压采集板个数 */
    uint16 temperatureSampleBoardNum; /**< 温感采集板个数 */
    uint16 temperatureNum; /**< 电池温感个数 */
    uint16 heatTemperatureNum; /**< 加热温感个数 */
    uint16 poleTemperatureNum; /**< 极柱温感个数 */
    uint16 balanceBuffSize; /**< 均衡缓存长度 */
    uint8 sampleBoardNumOnDaisyChain; /**< 菊花式链接的采集板个数 */
} SystemConnection_ConfigInfoType;

#pragma pop


#pragma push
#pragma DATA_SEG __GPAGE_SEG XGATE_DATA
#pragma CONST_SEG __GPAGE_SEG XGATE_CONST

extern const SystemConnection_ConfigInfoType SystemConnection_ConfigInfo;
extern const DeviceInfo_DeviceTypeType SystemConnection_SlaveTypesTable[];

/**
 * \brief 定义电池连接位图,最低位表示靠近负端的电池
 */
extern const uint16 CellDataM_CellsSetup[];
/**
 * \brief 定义温度连接位图,最低位表示第一串温度
 */
extern const uint8 CellDataM_TempsSetup[];
/**
 * \brief 每个从机单体电压逻辑编号最大值表定义
 * \note 每个从机逻辑编号最大值为对应从机最后一串电池的逻辑编号+1
 */
extern const uint16 CellDataM_BmuVoltageLogicIdMax[];

/**
 * \brief 从机内各采集板电池电压逻辑最大值表定义
 * \note 每个采集板逻辑编号最大值为本采集板最后一串电池的逻辑编号+1
 */
extern const uint8 CellDataM_BmuBoardVoltageLogicIdMax[];

/**
 * \brief 电池电压逻辑编号到物理编号映射表定义
 * \note 表内存放逻辑电池电压编号对应的在从机内物理连接位置，每个从机物理位置编号从0开始
 */
extern const uint8 CellDataM_VoltageLogicIdToPhysicalIdMap[];

/**
 * \brief 每个从机温度逻辑编号最大值表定义
 * \note 每个从机逻辑编号最大值为对应从机最后一个温度的逻辑编号+1
 */
extern const uint16 CellDataM_BmuTemperatureLogicIdMax[];
/**
 * \brief 从机内各采集板温度逻辑最大值表定义
 * \note 每个采集板逻辑编号最大值为本采集板最后一个温度的逻辑编号+1
 */
extern const uint8 CellDataM_BmuBoardTemperatureLogicIdMax[];

/**
 * \brief 温度逻辑编号到物理编号映射表定义
 * \note 表内存放逻辑温度编号对应的在从机内物理连接位置，每个从机物理位置编号从0开始
 */
extern const uint8 CellDataM_TemperatureLogicIdToPhysicalIdMap[];

/**
 * \brief 每个从机加热温度逻辑编号最大值表定义
 * \note 每个从机逻辑编号最大值为对应从机最后一个加热温度的逻辑编号+1
 */
extern const uint16 CellDataM_BmuHeatTemperatureLogicIdMax[];
/**
 * \brief 从机内各采集板加热温度逻辑最大值表定义
 * \note 每个采集板逻辑编号最大值为本采集板最后一个加热温度的逻辑编号+1
 */
extern const uint8 CellDataM_BmuBoardHeatTemperatureLogicIdMax[];

/**
 * \brief 加热温度逻辑编号到物理编号映射表定义
 * \note 表内存放逻辑加热温度编号对应的在从机内物理连接位置，每个从机物理位置编号从0开始
 */
extern const uint8 CellDataM_HeatTemperatureLogicIdToPhysicalIdMap[];

/**
 * \brief 每个从机极柱温度逻辑编号最大值表定义
 * \note 每个从机逻辑编号最大值为对应从机最后一个极柱温度的逻辑编号+1
 */
extern const uint16 CellDataM_BmuPoleTemperatureLogicIdMax[];
/**
 * \brief 从机内各采集板极柱温度逻辑最大值表定义
 * \note 每个采集板逻辑编号最大值为本采集板最后一个极柱温度的逻辑编号+1
 */
extern const uint8 CellDataM_BmuBoardPoleTemperatureLogicIdMax[];

/**
 * \brief 极柱温度逻辑编号到物理编号映射表定义
 * \note 表内存放逻辑极柱温度编号对应的在从机内物理连接位置，每个从机物理位置编号从0开始
 */
extern const uint8 CellDataM_PoleTemperatureLogicIdToPhysicalIdMap[];

extern const uint8 SystemConnection_SlaveSampleBoardNumTable[];

#pragma pop

extern const uint8 SystemConnection_SlaveCellNumTable[];
extern const uint8 SystemConnection_SlaveTempNumTable[];
extern uint8 BalanceM_BalanceStatus[];
extern uint8 BalanceM_BalanceCmdBits[];
extern const uint8 BalanceM_BalanceBuffSize;

/**
 * \brief 获取从机采集电池个数
 * \details 根据主机及从机型号获取对应从机的采集电池个数，当为一体机时，1号从机使用BAU的采集电池个数
 *
 * \param SlaveId 从机号 0,1,2...
 * \return 采集电池个数，异常返回0
 */
uint8 SysteConnection_GetSlaveBoardNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机采集电池个数
 * \details 根据主机及从机型号获取对应从机的采集电池个数，当为一体机时，1号从机使用BAU的采集电池个数
 *
 * \param SlaveId 从机号 0,1,2...
 * \return 采集电池个数，异常返回0
 */
uint16 SysteConnection_GetSlaveCellNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机采集温感个数
 * \details 根据主机及从机型号获取对应从机的采集温感个数，当为一体机时，1号从机使用BAU的采集温感个数
 *
 * \param SlaveId 从机号 0,1,2...
 * \return 采集温感个数，异常返回0
 */
uint16 SysteConnection_GetSlaveTempNum(App_SlaveIdType SlaveId);

#endif
