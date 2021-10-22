/**
 * \addtogroup autosar
 * \{
 * \addtogroup DIO
 * \{
 */
#ifndef DIO_CFG_H
#define DIO_CFG_H

#define DIO_DEV_ERROR_DETECT              STD_OFF

extern const Dio_ChannelGroupType DioGroupHwId; /** 硬件版本标识DIO组. */
extern const Dio_ChannelGroupType DioGroupLDMPGA; /** LDM模块前置放大倍数选择控制的DIO组. */
extern const Dio_ChannelGroupType DioGroupExtWakeupSignal; /** 外部唤醒源的DIO组. */
extern const Dio_ChannelGroupType DioGroupWakeupSignal; /** 唤醒源的DIO组. */

#define DIO_GROUP_HasExtWakeupSignal()   (Dio_ReadChannelGroup(&DioGroupExtWakeupSignal) != 0x19U)

#define DIO_GROUP_HW_INDENTIFY            (&DioGroupHwId) /**< 硬件版本标识DIO组 */
#define DIO_CHANNEL_SUSPEND               DIO_CHANNEL(C, 4U) /**< 休眠电压控制, 高电平开启板上所有电源 */
#define DIO_CHANNEL_SYSTEM_POWER_LATCH    DIO_CHANNEL(C, 5U) /**< 外部供电使能自锁, 高电平自锁电源 */
#define DIO_CHANNEL_NAND_POWER_EN         DIO_CHANNEL(C, 7U) /**< NAND FLASH电源控制, 高电平或高阻态使能NAND FLASH的电源 */
#define DIO_CHANNEL_LTC6820_EN            DIO_CHANNEL(K, 5U) /**< LTC6820使能控制 */

#define DIO_CHANNEL_NAND_CS               DIO_CHANNEL(H, 3U)
#define DIO_CHANNEL_LTC68XX_CS            DIO_CHANNEL(H, 7U)

#define DIO_CAHNNEL_LDM_PGA_S1            DIO_CHANNEL(B, 1U)
#define DIO_CAHNNEL_LDM_PGA_S2            DIO_CHANNEL(B, 2U)
#define DIO_CHANNEL_LDM_PGA_EN            DIO_CHANNEL(B, 3U) /**< LDM模块前置放大使能控制 */
#define DIO_CHANNEL_LDM_POS_SW            DIO_CHANNEL(AN_16_23, 4U) /**< LDM模块正端开关控制, 高电平开关导通 */
#define DIO_CHANNEL_LDM_NEG_SW            DIO_CHANNEL(S, 0U) /**< LDM模块负端开关控制, 高电平开关导通 */

#define DIO_CHANNEL_CHARGER_GB_S2         DIO_CHANNEL(AN_16_23, 0U) /**< 国标充电S2开关控制 */
#define DIO_CHANNEL_CHARGER_CP            DIO_CHANNEL(T, 1U) /**< 国标充电CP信号 */

#define DIO_CHANNEL_CHARGER_READY         DIO_CHANNEL(P, 6U) /**< 充电桩辅助电源 */
#define DIO_CHANNEL_KEY_ON                DIO_CHANNEL(P, 5U) /**< KEY_ON输入 */
#define DIO_CHANNEL_RTC_INT               DIO_CHANNEL(P, 4U) /**< RTC中断输入 */
#define DIO_CHANNEL_POWER_DUMP            DIO_CHANNEL(P, 3U) /**< 掉电中断输入 */
#define DIO_CHANNEL_OBC_POWER             DIO_CHANNEL(P, 2U) /**< 车载充电机辅助电源 */
#define DIO_CHANNEL_SIG_IN_1              DIO_CHANNEL(T, 2U) /**< 电平信号输入1 */
#define DIO_CHANNEL_SIG_IN_2              DIO_CHANNEL(T, 3U) /**< 电平信号输入2 */

#define DIO_CHANNEL_SW_IN_1               DIO_CHANNEL(AN_00_07, 6U) /**< 开关量输入1 */
#define DIO_CHANNEL_SW_IN_2               DIO_CHANNEL(AN_08_15, 6U) /**< 开关量输入2 */

#define DIO_CHANNEL_8V_HALL_EN            DIO_CHANNEL(AN_16_23, 1U) /**< HALL供电使能, 低电平使能 */
#define DIO_CHANNEL_ONBOARD_LED           DIO_CHANNEL(B, 4U) /**< 板上LED控制IO, 高电平点亮 */

#define DIO_CHANNEL_FB_MUX_EN             DIO_CHANNEL(K, 0U) /**< 板载反馈多路复用选择使能控制 */
#define DIO_CHANNEL_FB_MUX_A              DIO_CHANNEL(K, 3U)
#define DIO_CHANNEL_FB_MUX_B              DIO_CHANNEL(K, 2U)
#define DIO_CHANNEL_FB_MUX_C              DIO_CHANNEL(K, 1U)

#define DIO_CHANNEL_DTU_ID                DIO_CHANNEL(C, 0U) /**< DTU子板是否安装识别 */
#define DIO_CHANNEL_DTU_POWER_EN          DIO_CHANNEL(C, 1U) /**< DTU子板电源控制 */
#define DIO_CHANNEL_DTU_POWER_KEY         DIO_CHANNEL(C, 2U) /**< DTU子板电源按键控制 */
#define DIO_CHANNEL_DTU_STATUS            DIO_CHANNEL(C, 3U) /**< DTU子板状态反馈 */
#define DIO_CHANNEL_DTU_IS_PRESENT()      (Dio_ReadChannel(DIO_CHANNEL_DTU_ID) == STD_LOW)

#define DIO_CHANNEL_ADC_DRDY              DIO_CHANNEL(S, 4U)
#define DIO_CHANNEL_ADC_SPI_CS1           DIO_CHANNEL(S, 1U) /**< SPI ADC CS控制1 */
#define DIO_CHANNEL_ADC_SPI_CS2           DIO_CHANNEL(S, 7U) /**< SPI ADC CS控制2 */

#define DIO_CHANNEL_SHUNT_INT             DIO_CHANNEL(J, 7U) /**< 分流器中断输入 */
#define DIO_CHANNEL_SHUNT_RESET           DIO_CHANNEL(J, 6U) /**< 分流器复位 */

#define DIO_CHANNEL_CAN2_STB              DIO_CHANNEL(AN_16_23, 5U) /**< CAN2低功耗控制 */
#define DIO_CHANNEL_CAN2_EN               DIO_CHANNEL(AN_16_23, 6U) /**< CAN2使能控制 */
#define DIO_CHANNEL_CAN2_ERR              DIO_CHANNEL(AN_16_23, 7U) /**< CAN2错误输入 */
#define DIO_CHANNEL_CAN2_INH              DIO_CHANNEL(P, 7U) /**< CAN2使能控制 */

#define DIO_CHANNEL_HSS_1                 DIO_CHANNEL(E, 2U) /**< 高边开关1输出控制 */
#define DIO_CHANNEL_HSS_2                 DIO_CHANNEL(D, 0U) /**< 高边开关2输出控制 */
#define DIO_CHANNEL_HSS_3                 DIO_CHANNEL(D, 1U) /**< 高边开关3输出控制 */
#define DIO_CHANNEL_HSS_4                 DIO_CHANNEL(D, 3U) /**< 高边开关4输出控制 */
#define DIO_CHANNEL_HSS_5                 DIO_CHANNEL(A, 0U) /**< 高边开关5输出控制 */
#define DIO_CHANNEL_HSS_6                 DIO_CHANNEL(P, 0U) /**< 高边开关6输出控制 */
#define DIO_CHANNEL_HSS_7                 DIO_CHANNEL(P, 1U) /**< 高边开关7输出控制 */
#define DIO_CHANNEL_HSS_8                 DIO_CHANNEL(A, 1U) /**< 高边开关8输出控制 */
#define DIO_CHANNEL_LSS_1                 DIO_CHANNEL(D, 5U) /**< 低边开关1输出控制 */
#define DIO_CHANNEL_LSS_2                 DIO_CHANNEL(D, 6U) /**< 低边开关2输出控制 */
#define DIO_CHANNEL_HSS_DEN               DIO_CHANNEL(E, 3U) /**< 高边开关诊断使能控制 */
#define DIO_CHANNEL_HSS_DSEL              DIO_CHANNEL(D, 2U) /**< 高边开关诊断选择控制 */

#define DIO_CHANNEL_EL_FEEDBACK           DIO_CHANNEL(D, 7U) /**< 电子锁反馈输入 */
#define DIO_CHANNEL_EL_DRV_EN_1           DIO_CHANNEL(A, 6U) /**< 电子锁驱动使能1 */
#define DIO_CHANNEL_EL_DRV_EN_2           DIO_CHANNEL(A, 7U) /**< 电子锁驱动使能2 */
#define DIO_CHANNEL_EL_DRV_CTRL_1         DIO_CHANNEL(A, 5U) /**< 电子锁驱动控制1 */
#define DIO_CHANNEL_EL_DRV_CTRL_2         DIO_CHANNEL(A, 4U) /**< 电子锁驱动控制2 */
#define DIO_CHANNEL_EL_DRV_FAULT          DIO_CHANNEL(A, 3U) /**< 电子锁驱动错误反馈 */
#define DIO_CHANNEL_EL_DRV_SLEEP          DIO_CHANNEL(D, 4U) /**< 电子锁休眠控制 */
#define DIO_CHANNEL_EL_DRV_RESET          DIO_CHANNEL(A, 2U) /**< 电子锁复位控制 */

#endif

/**
 * \}
 * \}
 */