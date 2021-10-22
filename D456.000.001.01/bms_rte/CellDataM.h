/**
 * \addtogroup CellDataM 电池数据管理
 * \{
 */

#ifndef CELLDATAM_H_
#define CELLDATAM_H_

#include "App_Types.h"
// #include "App_Cfg.h"
#include "CellDataM_Types.h"
#include "CellDataM_Cfg.h"
// #include "SystemConnection.h"
#include "DeviceInfo.h"

/**
 * \brief 总压无效值定义，分辨率：1mv/bit
 *
 * \todo 待定义了Helper后移动此定义到Helper
 */
#define TOTAL_VOLTAGE_INVALID_VALUE  (0xFFFFFFFFUL)

/**
 * \brief 总压无效值定义，分辨率：0.1V/bit
 *
 * \todo 待定义了Helper后移动此定义到Helper
 */
#define TOTAL_VOLTAGE_100MV_INVALID_VALUE  (0xFFFFU)

/**
 * \brief 单体电压无效值定义
 *
 * \todo 待定义了Helper后移动此定义到Helper
 */
#define CELL_VOLTAGE_INVALID_VALUE  (0xFFFFU)

/**
 * \brief 单体电压排线脱落值定义
 *
 * \todo 待定义了Helper后移动此定义到Helper
 */
#define CELL_VOLTAGE_OFFLINE_VALUE  (0xFFFEU)

/**
 * \brief 温度无效值定义
 *
 * \todo 待定义了Helper后移动此定义到Helper
 */
#define CELL_TEMPERATURE_INVALID_VALUE  (0xFFU)

/**
 * \brief 温感排线脱落值定义
 *
 * \todo 待定义了Helper后移动此定义到Helper
 */
#define CELL_TEMPERATURE_OFFLINE_VALUE  (0xFEU)

/**
 * \brief 温感排线短路值定义
 *
 * \todo 待定义了Helper后移动此定义到Helper
 */
#define CELL_TEMPERATURE_SHORT_CIRCUIT_VALUE    (0xFDU)

/**
 * \brief 电压排线是否脱落定义
 */
#define CellDataM_VoltageIsOffline(voltage)             (voltage == CELL_VOLTAGE_OFFLINE_VALUE)

/**
 * \brief 温感排线是否脱落定义
 */
#define CellDataM_TemperatureIsOffline(temperature)     (temperature == CELL_TEMPERATURE_OFFLINE_VALUE)

/**
 * \brief 温感排线是否脱落定义
 */
#define CellDataM_TemperatureIsShortCircuit(temperature)    (temperature == CELL_TEMPERATURE_SHORT_CIRCUIT_VALUE)

#pragma push
#pragma DATA_SEG __GPAGE_SEG XGATE_DATA
#pragma CONST_SEG __GPAGE_SEG XGATE_CONST

/**
 * \brief 电池数据管理从机实际采集电压串数
 */
extern uint8 CellDataM_ActureSampleVoltageNum[];

/**
 * \brief 电池数据管理从机实际采集温感个数
 */
extern uint8 CellDataM_ActureSampleTemperatureNum[];

/**
 * \brief 从机电压接收标志 位图形式
 */
extern uint16 CellDataM_SlaveVoltageReceiveFlag;

/**
 * \brief 电池数据管理逻辑单体电压缓存定义
 */
extern App_VoltageType CellDataM_LogicVoltageBuffer[];

/**
 * \brief 从机温度接收标志 位图形式
 */
extern uint16 CellDataM_SlaveTemperatureReceiveFlag;

/**
 * \brief 电池数据管理逻辑温度缓存定义
 */
extern App_TemperatureType CellDataM_LogicTemperatureBuffer[];

/**
 * \brief 电池数据管理逻辑加热温度缓存定义
 */
extern App_TemperatureType CellDataM_LogicHeatTemperatureBuffer[];

/**
 * \brief 电池数据管理逻辑加热温度缓存定义
 */
extern App_TemperatureType CellDataM_LogicPoleTemperatureBuffer[];

#pragma pop

/**
 * \brief 实际从机类型缓存定义
 */
extern DeviceInfo_DeviceTypeType CellDataM_SlaveTypeBuffer[];

/**
 * \brief 电池数据管理初始化
 */
void CellDataM_Init(void);

/**
 * \brief 电池数据管理反初始化
 */
void CellDataM_Deinit(void);


/**
 * \brief 获取单体电压值
 * \note 通过电压逻辑编号获取单体电压值
 *
 * \param Logic_index 电池电压逻辑编号
 * \return 单体电压值 返回0xFFFE为掉线电压 返回0xFFFF为无效温度
 */
App_VoltageType CellDataM_GetVoltage(CellDataM_CellLogicIndexType Logic_index);
const App_VoltageType *CellDataM_GetVoltagePtr(void);


/**
 * \brief 获取单体电压值
 * \note 通过电压逻辑编号获取多个单体电压值
 *
 * \param Logic_StartIndex 起始电池电压逻辑编号
 * \return 获取到单体电压的数量.
 */
CellDataM_CellLogicIndexType CellDataM_GetMultiVoltage(App_VoltageType *buf, CellDataM_CellLogicIndexType Logic_StartIndex,  CellDataM_CellLogicIndexType Length);

/**
 * \brief 设置逻辑单体电压值
 * \details 通过电压逻辑编号设置对应单体电压值
 *
 * \param Logic_index 电池电压逻辑编号
 * \param Voltage 电压值
 *
 * \return E_OK:设置成功 E_NOT_OK:设置失败
 */
Std_ReturnType CellDataM_SetVoltage(CellDataM_CellLogicIndexType Logic_index, App_VoltageType Voltage);

/**
 * \brief 获取逻辑单体温度值
 * \details 通过温度逻辑编号获取单体温度值 编号从0开始
 *
 * \param Logic_index 电池温度逻辑编号
 * \return 单体温度度 返回0xFF为无效温度 返回0xFE为掉线温度
 */
App_TemperatureType CellDataM_GetTemperature(CellDataM_CellLogicIndexType Logic_index);
const App_TemperatureType *CellDataM_GetTempraturePtr(void);

/**
 * \brief 获取逻辑单体温度值
 * \note 通过电压逻辑编号获取多个单体温度值
 *
 * \param Logic_StartIndex 起始电池温度逻辑编号
 * \return 获取到单体温度的数量.
 */
CellDataM_CellLogicIndexType CellDataM_GetMultiTemperature(App_TemperatureType *buf, CellDataM_CellLogicIndexType Logic_StartIndex, CellDataM_CellLogicIndexType Length);

/**
 * \brief 获取从机实际类型
 * \details 获取根据从机通信上传的电压串数等信息确认从机的实际类型
 *
 * \param SlaveId 从机ID
 * \return 从机实际类型
 */
DeviceInfo_DeviceTypeType CellDataM_GetSlaveType(App_SlaveIdType SlaveId);

/**
 * \brief 更新从机实际类型信息
 * \details 根据从机通信上传的电压串数等信息确认从机的实际类型并保存下来
 *
 * \param SlaveId 从机ID
 * \param SlaveType 从机类型
 *
 * \return E_OK:更新成功 E_NOT_OK:更新失败
 */
Std_ReturnType CellDataM_SetSlaveType(App_SlaveIdType SlaveId, DeviceInfo_DeviceTypeType SlaveType);

/**
 * \brief 电池物理编号到逻辑编号转换
 * \details 将电池物理编号根据配置表转换为对应的逻辑编号
 *
 * \param Physical_Index 物理编号信息
 * \return 逻辑编号 0xFFFF表示无效编号
 */
CellDataM_CellLogicIndexType CellDataM_PhysicalToLogicIndex(CellDataM_CellPhysicalIndexType Physical_Index);

/**
 * \brief 获取从机逻辑电压最大编号值
 * \details 逻辑电压最大编号为全局逻辑编号，值为从机最后一串电压逻辑编号+1
 *
 * \param SlaveId 从机号
 * \return 逻辑最大编号，返回0表示无效
 */
CellDataM_CellLogicIndexType CellDataM_GetBmuVoltageLogicIdMax(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机逻辑温度最大编号值
 * \details 逻辑温度最大编号为全局逻辑编号，值为从机最后一个温度逻辑编号+1
 *
 * \param SlaveId 从机号
 * \return 逻辑最大编号，返回0表示无效
 */
CellDataM_CellLogicIndexType CellDataM_GetBmuTemperatureLogicIdMax(App_SlaveIdType SlaveId);

/**
 * \brief 电池逻辑电压编号到从机号转换
 * \details 将电池逻辑电压编号根据配置表转换为此逻辑编号所在的从机号，0,1,2...
 *
 * \param Logic_Index 逻辑电压编号
 * \return 逻辑电压编号所属从机号 0xFF为无效值
 */
App_SlaveIdType CellDataM_LogicVoltIndexToSlaveIndex(CellDataM_CellLogicIndexType Logic_Index);

/**
 * \brief 电池逻辑电压编号到从机内物理电压编号转换
 * \details 将电池逻辑电压编号转换为其所在从机内的实际物理电压编号
 *
 * \param Logic_Index 逻辑电压编号
 * \return 从机内物理电压编号 0xFFFF为无效编号
 */
CellDataM_CellPhysicalIndexType CellDataM_LogicToPhysicalVoltIndexInSlave(CellDataM_CellLogicIndexType Logic_Index);

/**
 * \brief 电池逻辑温度编号到从机号转换
 * \details 将电池逻辑温度编号根据配置表转换为此逻辑温度编号所在的从机号，0,1,2...
 *
 * \param Logic_Index 逻辑温度编号
 * \return 逻辑温度编号所属从机号 0xFF为无效值
 */
App_SlaveIdType CellDataM_LogicTempIndexToSlaveIndex(CellDataM_CellLogicIndexType Logic_Index);

/**
 * \brief 电池逻辑温度编号到从机内物理温度编号转换
 * \details 将电池逻辑温度编号转换为其所在从机内的实际物理温度编号
 *
 * \param Logic_Index 逻辑温度编号
 * \return 从机内物理温度编号 0xFFFF为无效编号
 */
CellDataM_CellPhysicalIndexType CellDataM_LogicToPhysicalTempIndexInSlave(CellDataM_CellLogicIndexType Logic_Index);

/**
 * \brief 判断电压值是否有效定义
 */
uint8 CellDataM_VoltageIsValid(uint16 voltage);

/**
 * \brief 判断温度值是否有效定义
 */
uint8 CellDataM_TemperatureIsValid(uint16 temperature);

/**
 * \brief 从机内电压编号到整组电池逻辑编号转换
 *
 * \param Slave 从机号 从0开始
 * \param index 从机内编号 从0开始
 *
 * \return 电压逻辑编号 从0开始 返回0xFFFF表示无效
 */
CellDataM_CellLogicIndexType CellDataM_VoltageIndexToLogic(App_SlaveIdType Slave, uint8 index);

/**
 * \brief 从机内温度编号到整组电池温度逻辑编号转换
 *
 * \param Slave 从机号 从0开始
 * \param index 从机内编号 从0开始
 *
 * \return 温度逻辑编号 从0开始 返回0xFFFF表示无效
 */
CellDataM_CellLogicIndexType CellDataM_TemperatureIndexToLogic(App_SlaveIdType Slave, uint8 index);

/**
 * \brief 所有从机单体电压上传状态查询
 * \return TRUE-全部上传 FALSE-未全部上传
 */
uint8 CellDataM_AllSlaveVoltageIsReceive(void);

/**
 * \brief 所有从机单体温度上传状态查询
 * \return TRUE-全部上传 FALSE-未全部上传
 */
uint8 CellDataM_AllSlaveTemperatureIsReceive(void);

/**
 * \brief 所有从机单体电压已获取且有效
 * \return TRUE-全部有效 FALSE-非全部有效
 */
uint8 CellDataM_AllSlaveVoltageIsValid(void);

/**
 * \brief 所有从机温度已获取且有效
 * \return TRUE-全部有效 FALSE-非全部有效
 */
uint8 CellDataM_AllSlaveTemperatureIsValid(void);

/**
 * \brief 获取从机逻辑加热温度最大编号值
 * \details 逻辑加热温度最大编号为全局逻辑编号，值为从机最后一个加热温度逻辑编号+1
 *
 * \param SlaveId 从机号
 * \return 逻辑最大编号，返回0表示无效
 */
CellDataM_CellLogicIndexType CellDataM_GetBmuHeatTemperatureLogicIdMax(App_SlaveIdType SlaveId);

/**
 * \brief 获取从机逻辑极柱温度最大编号值
 * \details 逻辑极柱温度最大编号为全局逻辑编号，值为从机最后一个极柱温度逻辑编号+1
 *
 * \param SlaveId 从机号
 * \return 逻辑最大编号，返回0表示无效
 */
CellDataM_CellLogicIndexType CellDataM_GetBmuPoleTemperatureLogicIdMax(App_SlaveIdType SlaveId);

/**
 * \brief 获取逻辑单体加热温度值
 * \details 通过加热温度逻辑编号获取单体加热温度值 编号从0开始
 *
 * \param Logic_index 电池加热温度逻辑编号
 * \return 单体加热温度度 返回0xFF为无效加热温度 返回0xFE为掉线加热温度
 */
App_TemperatureType CellDataM_GetHeatTemperature(CellDataM_CellLogicIndexType Logic_index);

/**
 * \brief 获取逻辑单体极柱温度值
 * \details 通过极柱温度逻辑编号获取单体极柱温度值 编号从0开始
 *
 * \param Logic_index 电池极柱温度逻辑编号
 * \return 单体极柱温度度 返回0xFF为无效极柱温度 返回0xFE为掉线极柱温度
 */
App_TemperatureType CellDataM_GetPoleTemperature(CellDataM_CellLogicIndexType Logic_index);

/**
 * \brief 获取指定从机实际采集到有效的电池个数
 *
 * \param SlaveId 从机号
 * \return 实际采集有效电池个数
 */
uint8 CellDataM_GetSlaveActureVoltageNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取指定从机实际采集到有效的温感个数
 * \details 实际温感个数不包含加热温感和极柱温感
 *
 * \param SlaveId 从机号
 * \return 实际采集有效温感个数
 */
uint8 CellDataM_GetSlaveActureTemperatureNum(App_SlaveIdType SlaveId);

/**
 * \brief 获取指定所有实际采集到有效的电池个数
 *
 * \return 实际采集有效电池个数
 */
uint16 CellDataM_GetActureVoltageNum(void);

/**
 * \brief 获取指定所有实际采集到有效的温感个数
 * \details 实际温感个数不包含加热温感和极柱温感
 *
 * \return 实际采集有效电池个数
 */
uint16 CellDataM_GetActureTemperatureNum(void);

#endif

/**
 * \}
 */
