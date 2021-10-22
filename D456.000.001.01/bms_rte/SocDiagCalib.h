/**
 * \file SocDiagCalib.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief Soc诊断校正头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170223 |
 */
#ifndef SOC_DIAG_CALIB_H_
#define SOC_DIAG_CALIB_H_

#include "Soc.h"

/**
 * \brief SOC不校正原因类型定义
 */
typedef enum{
    SOC_NO_CALIB_REASON_NO_TRIGGER, /**< 未触发校准 */
    SOC_NO_CALIB_REASON_NORMAL, /**< 校准正常 */
    SOC_NO_CALIB_REASON_NOT_REL, /**< 上次校准未释放 */
    SOC_NO_CALIB_REASON_SOC_HIGH, /**< SOC过高 */
    SOC_NO_CALIB_REASON_SOC_LOW, /**< SOC过低 */
    SOC_NO_CALIB_REASON_HAV, /**< 平均电压过高 */
    SOC_NO_CALIB_REASON_LAV, /**< 平均电压过低 */
    SOC_NO_CALIB_REASON_DELAY, /**< 校正延时中 */
    SOC_NO_CALIB_REASON_MEMORY, /**< 参数读取 */
    SOC_NO_CALIB_REASON_OTHERS
}SocDiagCalib_NoCalibReasonType;


/**
 * \brief SOC内部参数类型定义
 */
typedef struct{
    uint8 fullCalibFlag; /**< 满校正标志 */
    uint8 emptyCalibFlag; /**< 空校正标志 */
    uint8 emptyCalibStartFlag; /**< 空校正启动标志，用于空校正延时 */
    uint32 emptyCalibLastTime; /**< 空校正延时 */
    SocDiagCalib_NoCalibReasonType noFullReason; /**< 未满校正原因 */
    SocDiagCalib_NoCalibReasonType noEmptyReason; /**< 未空校正原因 */
}SocDiagCalib_InnerDataType;

/**
 * \brief SOC诊断校正模块标定参数类型定义
 */
typedef struct{
    App_VoltageType CapHighCalibAverageVolt; /**< 过充容量校正平均电压阈值 */
    App_VoltageType CapLowCalibAverageVolt; /**< 过放容量校正平均电压阈值 */
    App_SocType CapLowCalibSoc; /**< 过放容量校正SOC阈值 */
    uint16 CapLowCalibDelay; /**< 过放容量校正延时 */
}SocDiagCalib_CalibConfigType;

/**
 * \brief SOC空校正检查函数
 * \details 用于SOC空校正延时检查并进行空校正
 */
void SocDiagCalib_EmptyCalibCheck(void);

/**
 * \brief SOC满校正函数
 * \details 检查SOC满校正条件，条件成立则将SOC校准为100%，否则不校准
 */
void SocDiagCalib_FullCalib(void);

/**
 * \brief SOC满校正条件释放函数
 * \details 调用此函数后允许启动下次SOC满校准，否则不允许
 */
void SocDiagCalib_FullCalibRel(void);

/**
 * \brief SOC空校正函数
 * \details 检查SOC空校正条件，条件成立则启动SOC空校正延时，延时完成后才会对SOC进行空校正，此
 *          函数在校正条件成立后仅仅启动空校正延时，不做空校正动作
 */
void SocDiagCalib_EmptyCalib(void);

/**
 * \brief SOC空校正释放函数
 * \details 调用此函数会停止空校正延时及允许下次SOC空校正，否则不允许
 */
void SocDiagCalib_EmptyCalibRel(void);

/**
 * \brief 获取SOC满校准无法校准自诊断原因
 *
 * \return 未校准原因
 */
SocDiagCalib_NoCalibReasonType SocDiagCalib_GetFullReason(void);

/**
 * \brief 获取SOC空校准无法校准自诊断原因
 *
 * \return 未校准原因
 */
SocDiagCalib_NoCalibReasonType SocDiagCalib_GetEmptyReason(void);


#endif