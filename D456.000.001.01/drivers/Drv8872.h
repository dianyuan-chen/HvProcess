/**
 * \addtogroup Drivers
 * \{
 * \addtogroup DRV8872
 * \{
 */
#ifndef DRV8872_CONFIG_TYPES_H
#define DRV8872_CONFIG_TYPES_H

#include "Dio.h"
#include "Adc.h"
#include "Drv8872_Cfg.h"
#include "Async_Looper.h"

/**
 * \brief DRV8872驱动的配置.
 */
typedef struct {
    Dio_ChannelType DoCtrl[2]; /**< 4路输出的控制 */
    Dio_ChannelType DiFault; /**< 错误反馈输入 */
    Adc_ValueGroupType MaxAdcValueWhenOff;
    Std_ReturnType (*getSupplyVoltage)(Adc_ValueGroupType *v);
} Drv8872_ConfigType;

/**
 * \brief 驱动通道的输出状态.
 */
typedef uint8 Drv8872_DriveType;
#define DRV8872_DRIVE_OFF      0x00U /**< 输出高阻状态 */
#define DRV8872_DRIVE_REVERSE  0x01U /**< 反转 */
#define DRV8872_DRIVE_FORWARD  0x02U /**< 正转 */
#define DRV8872_DRIVE_BRAKE    0x03U /**< 减速 */


/**
 * \brief DRV8872的诊断状态.
 */
typedef uint8 Drv8872_DiagnosisStatus;
#define DRV8872_STATUS_OK   0U /**< DRV8872诊断状态正常 */
#define DRV8872_STATUS_ERR  1U /**< DRV8872诊断状态异常 */

/**
 * \brief 初始化
 */
void Drv8872_Init(Async_LooperType *looper);

#define DRV8872_CHIPID_NONE                0xFFU
/**
 * \brief 获取DRV8872的诊断状态.
 *
 * \param id 驱动器ID索引.
 * \return 诊断状态
 */
Drv8872_DiagnosisStatus Drv8872_GetDiagnosisStatus(uint8 chipid);

/**
 * \brief 设置DRV8872某个通道的输出状态.
 * \details 返回值只是反映执行操作的结果, 不带诊断结果信息.
 *
 * \param ch 驱动通道
 * \param drive 输出状态
 * \return 设置成功(E_OK), 设置失败(E_NOT_OK).
 */
Std_ReturnType Drv8872_Drive(uint8 chipid, Drv8872_DriveType drive);

void Drv8872_NewOutputVolAdcValue(uint8 ch, Adc_ValueGroupType v);

#endif
/**
 * \}
 * \}
 */
