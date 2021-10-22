/**
 * \file ParameterM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 参数管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20161209 |
 */

/**
 * \addtogroup ParameterM 参数管理
 * \{
 */

#ifndef PARAMETERM_H_
#define PARAMETERM_H_

#include "Eeprom.h"
#include "Eeeprom.h"
#include "Diagnosis_Cfg.h"
#include "Diagnosis.h"
#include "Soc.h"
#include "SocDiagCalib.h"
#include "Charge_Types.h"
#include "RuntimeM.h"

#define PARAMETERM_DEV_ERROR_DETECT         STD_OFF

#define PARAMETERM_PARA_USE_EEEP_NUM        4U

#define PARAMETERM_CALIB_PARA_DFLASH_ADDR   0x100000UL

/**
 * \brief 获取标定参数地址
 *
 * \param  member 类型定义中成员名
 */
#define PARAMETERM_MEMBER_OF_STRUCT(PTR, MEMBER) (&(PTR)->MEMBER)
#define PARAMETERM_GET_CALIB_PARA_ADDR(PARA) \
    ((uint32)(uint8*)(PARAMETERM_MEMBER_OF_STRUCT(ParameterM_CurrentCalibParaPtr, PARA)))

#define PARAMETERM_GET_DFLASH_CALIB_PARA_ADDR(PARA) \
    ((uint32)(uint8*)(PARAMETERM_MEMBER_OF_STRUCT(ParameterM_DFlashCalibParaPtr, PARA)))

#define PARAMETERM_GET_PFLASH_CALIB_PARA_ADDR(PARA) \
    ((uint32)(uint8*)(PARAMETERM_MEMBER_OF_STRUCT(ParameterM_PFlashCalibParaPtr, PARA)))

#define PARAMETERM_GET_DIAG_CALIB_PARA_START_ADDR(index) \
    (PARAMETERM_GET_CALIB_PARA_ADDR(diagnosisPara) + (uint32)Diagnosis_ItemToIndex(index) * sizeof(Diagnosis_ParaType))

#define PARAMETERM_GET_DFLASH_DIAG_CALIB_PARA_START_ADDR(index) \
    (PARAMETERM_GET_DFLASH_CALIB_PARA_ADDR(diagnosisPara) + (uint32)Diagnosis_ItemToIndex(index) * sizeof(Diagnosis_ParaType))

#define PARAMETERM_GET_PFLASH_DIAG_CALIB_PARA_START_ADDR(index) \
    (PARAMETERM_GET_PFLASH_CALIB_PARA_ADDR(diagnosisPara) + (uint32)Diagnosis_ItemToIndex(index) * sizeof(Diagnosis_ParaType))

#define ParameterM_Read     ParameterM_CalibRead

/**
 * \brief 参数管理模块参数类型定义
 */
typedef uint16 ParameterM_DataType;


/**
 * \brief 标定参数类型类型
 */
typedef enum{
    PARAMETERM_CALIB_PARA_TYPE_PFLASH,
    PARAMETERM_CALIB_PARA_TYPE_DFLASH
}ParameterM_CalibParaTypeType;

/**
 * \brief Eeeprom参数数据格式定义
 */
typedef struct{
    uint16 data[PARAMETERM_PARA_USE_EEEP_NUM]; /**< Eeeprom保存数据，包含数据、数据校验值、备份数据、备份数据校验值 */
}ParameterM_EeepParaDataType;

/**
 * \brief Eeeprom参数索引类型定义
 * \details 此处定义参数均存储在Eeeprom中
 */
typedef enum{
    PARAMETERM_EEEP_PARA_START = 0,
    PARAMETERM_EEEP_TOTAL_CAP_INDEX = PARAMETERM_EEEP_PARA_START, /**< 总容量 */
    PARAMETERM_EEEP_LEFT_CAP_INDEX = 1, /**< 剩余容量 */
    PARAMETERM_EEEP_DISCHARGE_CNT_INDEX = 2, /**< 充放电次数 */
    PARAMETERM_EEEP_DISCHARGE_CNT_STATE_INDEX = 3, /**< 充放电次数状态 */
    PARAMETERM_EEEP_HALL1_ZEROOFFSET_INDEX = 4, /**< HALL1零点电流校准值 */
    PARAMETERM_EEEP_HALL2_ZEROOFFSET_INDEX = 5, /**< HALL2零点电流校准值 */
    PARAMETERM_EEEP_SHUNT_ZEROOFFSET_INDEX = 6, /**< Shunt零点电流校准值 */
    PARAMETERM_EEEP_OCVSOC_TIME_HIGH_INDEX = 7, /**< OCV-SOC校准时间高字节 */
    PARAMETERM_EEEP_OCVSOC_TIME_LOW_INDEX = 8, /**< OCV-SOC校准时间低字节 */
    PARAMETERM_EEEP_VIN1_INDEX = 9, /**< VIN码 */
    PARAMETERM_EEEP_VIN2_INDEX = 10, /**< VIN码 */
    PARAMETERM_EEEP_VIN3_INDEX = 11, /**< VIN码 */
    PARAMETERM_EEEP_VIN4_INDEX = 12, /**< VIN码 */
    PARAMETERM_EEEP_VIN5_INDEX = 13, /**< VIN码 */
    PARAMETERM_EEEP_VIN6_INDEX = 14, /**< VIN码 */
    PARAMETERM_EEEP_VIN7_INDEX = 15, /**< VIN码 */
    PARAMETERM_EEEP_VIN8_INDEX = 16, /**< VIN码 */
    PARAMETERM_EEEP_VIN9_INDEX = 17, /**< VIN码 */
    PARAMETERM_EEEP_LEFTCAP_INTEGRAL_L_INDEX = 18, /**< 积分容量低字 */
    PARAMETERM_EEEP_LEFTCAP_INTEGRAL_H_INDEX = 19, /**< 积分容量高字 */
    PARAMETERM_EEEP_CUMULATIVE_CHG_CAP_L_INDEX = 20, /**< 累计充电容量低字节 */
    PARAMETERM_EEEP_CUMULATIVE_CHG_CAP_H_INDEX = 21, /**< 累计充电容量高字节 */
    PARAMETERM_EEEP_CUMULATIVE_DCHG_CAP_L_INDEX = 22, /**< 累计放电容量低字节 */
    PARAMETERM_EEEP_CUMULATIVE_DCHG_CAP_H_INDEX = 23, /**< 累计放电容量高字节 */
    PARAMETERM_EEEP_SHUNT_GAIN_ERROR_INDEX = 24, /**< 分流器增益误差 */
    PARAMETERM_EEEP_HALL1_GAIN_ERROR_INDEX = 25, /**< HALL1增益误差 */
    PARAMETERM_EEEP_HALL2_GAIN_ERROR_INDEX = 26, /**< HALL2增益误差 */
    PARAMETERM_EEEP_HVBPOS_GAIN_ERROR_INDEX = 27, /**< HV_CHANNEL_BPOS增益误差 */
    PARAMETERM_EEEP_HV1_GAIN_ERROR_INDEX = 28, /**< HV_CHANNEL_HV1增益误差 */
    PARAMETERM_EEEP_HV2_GAIN_ERROR_INDEX = 29, /**< HV_CHANNEL_HV2增益误差 */
    PARAMETERM_EEEP_HV3_GAIN_ERROR_INDEX = 30, /**< HV_CHANNEL_HV3增益误差 */
    PARAMETERM_EEEP_HV4_GAIN_ERROR_INDEX = 31, /**< HV_CHANNEL_HV4增益误差 */
    PARAMETERM_EEEP_HV5_GAIN_ERROR_INDEX = 32, /**< HV_CHANNEL_HV5增益误差 */
    PARAMETERM_EEEP_DCHG_OLV_CNT_STATE_INDEX = 33, /**< 电池过放电计数状态变化，用于记录需掉电保存的状态 */
    PARAMETERM_EEEP_DCHG_OLV_CNT_INDEX = 34, /**< 电池过放电计数 */
    PARAMETERM_EEEP_LEFTCAP_H_INDEX=35, /**< 真实剩余容量高字 Ams/bit */
    PARAMETERM_EEEP_LEFTCAP_L_INDEX=36, /**< 真实剩余容量低字 Ams/bit */
    PARAMETERM_EEEP_MODEL_DSOC_INDEX=37,/**< 显示SOC 0.01%/bit */
    PARAMETERM_EEEP_MODEL_TSOC_INDEX=38,/**< 目标SOC 0.01%/bit */
    PARAMETERM_EEEP_POWER_LIMIT_INDEX=39,
    PARAMETERM_EEEP_SOH_Full_INDEX=40, /**< SOH计算标志*/
    PARAMETERM_EEEP_SOH_INDEX=41, /**< SOH 0.1%/bit */
    PARAMETERM_EEEP_LEFTCAP_WOCALIB_H_INDEX=42, /**< SOH计算中用到的累积充电/放电高字节 Ams/bit */
    PARAMETERM_EEEP_LEFTCAP_WOCALIB_L_INDEX=43, /**< SOH计算中用到的累积充电/放电低字节 Ams/bit */

    PARAMETERM_EEEP_LOWER_INDEX_END = 43, /**< 低段参数索引结束(不单独占用一个索引)， 注：处于PARAMETERM_EEEP_LOWER_INDEX_END和PARAMETERM_EEEP_HIGHER_INDEX_START之间的参数不进行存储有效性校验 */

    PARAMETERM_EEEP_HIGHER_INDEX_START = 118, /**< 高段参数索引起始(不单独占用一个索引) */

    PARAMETERM_EEEP_REMOTEABLE_COMMAND_INDEX = 118, /*远程使能命令*/
    PARAMETERM_EEEP_REMOTELINK_TIME_HIGH_INDEX = 119,/**< 远程均衡命令下发时间高字 精度：1S/bit */
    PARAMETERM_EEEP_REMOTELINK_TIME_LOW_INDEX = 120,/**< 远程均衡命令下发时间低字 精度：1S/bit */
    PARAMETERM_EEEP_NOMINAL_CAP_INDEX = 121, /**< 额定容量 */
    PARAMETERM_EEEP_CUMULATIVE_CHG_TIME_L_INDEX = 122, /**< 累计充电时间低字 精度：1S/bit */
    PARAMETERM_EEEP_CUMULATIVE_CHG_TIME_H_INDEX = 123, /**< 累计充电时间高字 精度：1S/bit */
    PARAMETERM_EEEP_CUMULATIVE_DCHG_TIME_L_INDEX = 124, /**< 累计放电时间低字 精度：1S/bit */
    PARAMETERM_EEEP_CUMULATIVE_DCHG_TIME_H_INDEX = 125, /**< 累计放电时间高字 精度：1S/bit */
    PARAMETERM_EEEP_CHARGE_INTEGRAL_EFFICIENCY = 126, /**< 充电效率因子 精度：0.1% */
    PARAMETERM_EEEP_DCHARGE_INTEGRAL_EFFICIENCY = 127, /**< 放电效率因子 精度：0.1% */
}ParameterM_EeepParaIndexType;

/**
 * \brief 标定参数类型定义
 */
typedef struct{
    char FWID[16]; /**< 与之对应的FWID */
    Diagnosis_AllItemParaType diagnosisPara; /**< 故障诊断参数 */
    Soc_CalibConfigType SocPara; /**< SOC标定参数 */
    SocDiagCalib_CalibConfigType SocDiagPara; /**< SOC诊断校正参数 */
    Charge_CalibConfigInfoType ChargePara; /**< 充电参数 */
}ParameterM_CalibParaType;

/**
 * \brief 参数管理模块配置信息类型定义
 */
typedef struct{
    ParameterM_EeepParaIndexType eeepLowerEndIndex; /**< 低段参数索引结束(不单独占用一个索引) */
    ParameterM_EeepParaIndexType eeepHigherStartIndex; /**< 高段参数索引起始(不单独占用一个索引) */
}ParameterM_ConfigInfoType;

/**
 * \brief 参数管理模块内部参数类型定义
 */
typedef struct {
    ParameterM_CalibParaTypeType type;
}ParameterM_innerDataType;

extern const Diagnosis_ParaType ParameterM_NoneCalibrateDiagConfig[];
extern const ParameterM_DataType ParameterM_EeepParaDefault[];
extern const ParameterM_EeepParaIndexType ParameterM_EeepParaNum;
extern const ParameterM_ConfigInfoType ParameterM_ConfigInfo;
extern const ParameterM_CalibParaType *const ParameterM_PFlashCalibParaPtr;
extern const ParameterM_CalibParaType *ParameterM_CurrentCalibParaPtr;
extern const ParameterM_CalibParaType *const ParameterM_DFlashCalibParaPtr;
/**
 * @brief 应用层参数长度
 */
extern const uint16 ParameterM_AppParaLength;

/**
 * \brief 参数管理模块初始化
 */
void ParameterM_Init(void);

/**
 * \brief 参数管理模块反初始化
 */
void ParameterM_Deinit(void);

/**
 * \brief Eeeprom参数写入
 * \note 根据参数索引保存数据到 Eeeprom, 带重试机制，默认重试两次
 *
 * \param index 参数索引
 * \param data 参数值
 *
 * \return E_OK:写入成功 E_NOT_OK:写入失败
 */
Std_ReturnType ParameterM_EeepWrite(ParameterM_EeepParaIndexType index, ParameterM_DataType data);

/**
 * \brief Eeeprom读取参数
 *
 * \param index 参数索引
 * \param data 读取到的参数值
 *
 * \return E_OK:读取成功 E_NOT_OK:读取失败
 */
Std_ReturnType ParameterM_EeepRead(ParameterM_EeepParaIndexType index, ParameterM_DataType *data);

/**
 * \brief Eeeprom带校验读取参数
 *
 * \param index 参数索引
 * \param data 读取到的参数值
 *
 * \return E_OK:读取成功 E_NOT_OK:读取失败
 */
Std_ReturnType ParameterM_EeepReadCareFully(ParameterM_EeepParaIndexType index, ParameterM_DataType *data);

/**
 * \brief 写入标定参数
 *
 * \param address 起始地址
 * \param dataPtr 数据缓存
 * \param size 数据长度
 * \return E_OK：写入成功 E_NOT_OK：写入失败
 */
Std_ReturnType ParameterM_CalibWrite(uint32 address, const uint8 *dataPtr, uint16 size);

/**
 * \brief 读取标定参数
 *
 * \param address 起始地址
 * \param dataPtr 数据缓存
 * \param size 数据长度
 * \return E_OK：读取成功 E_NOT_OK：读取失败
 */
Std_ReturnType ParameterM_CalibRead(uint32 address, uint8 *dataPtr, uint16 size);

/**
 * \brief 读取当前使用的诊断标定参数值
 * \details 根据诊断索引、诊断等级及参数偏移读取当前使用的诊断参数
 *
 * \param index 诊断索引 参考\link Diagnosis_ItemType \endlink
 * \param level 报警等级 0-一级 1-二级 2-三级 3-四级
 * \param offset 参数偏移 0-触发阈值 1-释放阈值 2-触发延时 3-释放延时
 * \return 标定参数值
 */
uint16 ParameterM_DiagCalibRead(Diagnosis_ItemType index, uint8 level, uint8 offset);

/**
 * \brief 读取DFlash中的诊断标定参数值
 * \details 根据诊断索引、诊断等级及参数偏移读取当前使用的诊断参数
 *
 * \param index 诊断索引 参考\link Diagnosis_ItemType \endlink
 * \param level 报警等级 0-一级 1-二级 2-三级 3-四级
 * \param offset 参数偏移 0-触发阈值 1-释放阈值 2-触发延时 3-释放延时
 * \return 标定参数值
 */
uint16 ParameterM_DFlashDiagCalibRead(Diagnosis_ItemType index, uint8 level, uint8 offset);

/**
 * \brief 读取PFlash中的诊断标定参数值
 * \details 根据诊断索引、诊断等级及参数偏移读取当前使用的诊断参数
 *
 * \param index 诊断索引 参考\link Diagnosis_ItemType \endlink
 * \param level 报警等级 0-一级 1-二级 2-三级 3-四级
 * \param offset 参数偏移 0-触发阈值 1-释放阈值 2-触发延时 3-释放延时
 * \return 标定参数值
 */
uint16 ParameterM_PFlashDiagCalibRead(Diagnosis_ItemType index, uint8 level, uint8 offset);

/**
 * \brief 设置标定参数类型
 * \details 通过此接口可设置标定参数使用PFLASH中参数还是使用DFLASH中参数，DFLASH中参数支持参数标定
 *
 * \param type 标定参数类型
 */
void ParameterM_SetCalibParaPtr(ParameterM_CalibParaTypeType type);

/**
 * \brief 获取配置参数类型
 * \return 详见“ParameterM_CalibParaTypeType”定义
 */
ParameterM_CalibParaTypeType ParameterM_GetParaType(void);

/**
 * \brief 检查参数是否全部同步到DFLASH
 *
 * \retval TRUE 全部同步到DFLASH
 * \retval FALSE 未全部同步到DFLASH
 */
boolean ParameterM_SyncFinished(RuntimeM_SignalType signal);

#endif


/**
 * \}
 */
