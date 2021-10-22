/**
 * \addtogroup Drivers
 * \{
 * \addtogroup DRV8844
 * \{
 */
#ifndef DRV8844_CONFIG_TYPES_H
#define DRV8844_CONFIG_TYPES_H

#include "Dio.h"
#include "Adc.h"
#include "Drv8844_Cfg.h"

/**
 * \brief DRV8844驱动的配置.
 */
typedef struct {
    Dio_ChannelType DoCtrl[4]; /**< 4路输出的控制 */
    Dio_ChannelType DoEn[4]; /**< 4路输出使能的控制 */
    Dio_ChannelType DiFault; /**< 错误反馈输入 */
    Dio_ChannelType DoReset; /**< 复位控制 */
    Dio_ChannelType DoSleep; /**< 休眠控制 */
} Drv8844_ConfigType;

/**
 * \brief DRV8844的驱动通道.
 * \details 每个DRV8844有4个驱动通道.
 */
typedef uint8 Drv8844_ChannelType;

#define DRV8844_CHANNEL(_chipid, _subchannel) ((uint8)((uint8)(_chipid) << 2) + (_subchannel))

#define DRV8844_SUBCHANNEL_1 0U /**< 驱动通道1 */
#define DRV8844_SUBCHANNEL_2 1U /**< 驱动通道2 */
#define DRV8844_SUBCHANNEL_3 2U /**< 驱动通道3 */
#define DRV8844_SUBCHANNEL_4 3U /**< 驱动通道4 */

/**
 * \brief 驱动通道的输出状态.
 */
typedef enum {
    DRV8844_DRIVE_OFF = 0x00, /**< 输出高阻状态 */
    DRV8844_DRIVE_LOW = 0x01, /**< 输出低电位 */
    DRV8844_DRIVE_HIGH = 0x02, /**< 输出高电位 */
} Drv8844_DriveType;

/**
 * \brief DRV8844的诊断状态.
 */
typedef enum {
    DRV8844_STATUS_OK, /**< DRV8844诊断状态正常 */
    DRV8844_STATUS_ERR, /**< DRV8844诊断状态异常 */
} Drv8844_DiagnosisStatus;

/**
 * \brief 初始化
 */
void Drv8844_Init(void);

/**
 * \brief 获取DRV8844的诊断状态.
 *
 * \param id 驱动器ID索引.
 * \return 诊断状态
 */
Drv8844_DiagnosisStatus Drv8844_GetDiagnosisStatus(uint8 chipid);

/**
 * \brief 设置DRV8844某个通道的输出状态.
 * \details 返回值只是反映执行操作的结果, 不带诊断结果信息.
 *
 * \param ch 驱动通道
 * \param drive 输出状态
 * \return 设置成功(E_OK), 设置失败(E_NOT_OK).
 */
Std_ReturnType Drv8844_Drive(Drv8844_ChannelType ch, Drv8844_DriveType drive);

void Drv8844_NewOutputVolAdcValue(Drv8844_ChannelType ch, Adc_ValueGroupType v);

#endif
/**
 * \}
 * \}
 */
