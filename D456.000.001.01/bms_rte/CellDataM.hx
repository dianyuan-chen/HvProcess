/**
 * \file CellDataM.hx
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief XGate电池数据管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161230 |
 */
/**
 * \addtogroup CellDataM 电池数据管理
 \{
 */

#ifndef CELLDATAM_HX_
#define CELLDATAM_HX_

#if defined(__XGATE__)
#include <intrinsics_xgate.h>
#endif
#include "Std_Types.h"
#include "App_Types.h"
#include "CellDataM.h"

/**
 * \brief 从机电压信息接收
 * \note 接收从机传输到主机的以物理编号的单体电压数据并以紧凑型逻辑编号的形式存储下来
 *
 * \param slave_id 从机号 0,1...
 * \param *rec_data 从机上传的单体电压数据，物理编号方式,DID为0x480的数据
 * \param length 数据长度
 * \remarks 内部单体电压数据均以逻辑编号形式获取
 */
void XCellDataM_RxBmuVoltage(App_SlaveIdType slave_id, uint8 *rec_data, uint16 length);

/**
 * \brief 从机温度信息接收
 * \note 接收从机传输到主机的以物理编号的温度数据并以紧凑型逻辑编号的形式存储下来
 *
 * \param slave_id 从机号 0,1...
 * \param *rec_data 从机上传的温度数据，物理编号方式,DID为0x484的数据
 * \param length 数据长度
 * \remarks 内部电池温度数据均以逻辑编号形式获取
 */
void XCellDataM_RxBmuTemperature(App_SlaveIdType slave_id, uint8 *rec_data, uint16 length);

/**
 * \brief 清除指定从机单体电压信息
 *
 * \param slave_id 指定的从机编号
 */
void XCellDataM_ClearBmuVoltageData(App_SlaveIdType slave_id);

/**
 * \brief 清除指定从机温度信息
 *
 * \param slave_id 指定的从机编号
 */
void XCellDataM_ClearBmuTemperatureData(App_SlaveIdType slave_id);

/**
 * \brief 清除从机所有信息
 * \details 出现从机通信中断时此函数会被触发，清除通信中断从机相关所有信息
 *
 * \param slave_id 通信中断的从机号
 */
void XCellDataM_ClearBmuData(App_SlaveIdType slave_id);




#endif


/**
 * \}
 */