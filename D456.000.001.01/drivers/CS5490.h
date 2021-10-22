#ifndef __CS5490_H__
#define __CS5490_H__

#include "Std_Types.h"
#include "Std_Types.h"
#include "Dio.h"
#include "Uart.h"
#include "spi_bus.h"


#define CS5490_REGISTER_ERR_VAL 0xffffffffUL


#define CS_OP_REGISTER_READ     0x00U
#define CS_OP_REGISTER_WRITE    0x40U
#define CS_OP_PAGE_SELECT       0x80U
#define CS_OP_INSTRUCTION       0xC0U

// **************************************************************************************************************
// CS5490 Instructions:

// C[5] specifies the instruction type:
// 0 = Controls
// 1 = Calibrations

// Controls:
#define CS_INSTRUCTION_SOFT_RESET     0x01U        // xxx0 0001 - Software Reset
#define CS_INSTRUCTION_STANDBY        0x02U        // xxx0 0010 - Standby
#define CS_INSTRUCTION_WAKEUP         0x03U        // xxx0 0011 - Wakeup
#define CS_INSTRUCTION_SINGLE_CONV    0x14U        // xxx1 0100 - Single Conv.
#define CS_INSTRUCTION_CONT_CONV      0x15U        // xxx1 0101 - Continuous Conv.
#define CS_INSTRUCTION_HALT_CONV      0x18U        // xxx1 1000 - Halt Conv.

#define CS_INSTRUCTION_DO_CAL         0x20U        // xx1x xxxx - Cal instruction flag
// Calibration:
#define CS_CAL_DC_OFFSET              0x00U        // xxx0 0xxx - DC Offset cal
#define CS_CAL_AC_OFFSET              0x10U        // xxx1 0xxx - AC offset cal
#define CS_CAL_GAIN                   0x18U        // xxx1 1xxx - calibrate gain
// 1 00 C2 C1 C0  DC Offset
// 1 10 C2 C1 C0  AC Offset*
// 1 11 C2 C1 C0  Gain
// *AC offset calibration valid only for current channel.
// For calibration, C[4:3] specifies the type of calibration.
#define CS_CAL_CHANNEL_I              0x01U        // xxxx x001 - Cal current channel
#define CS_CAL_CHANNEL_V              0x02U        // xxxx x010 - cal voltage channel
#define CS_CAL_CHANNEL_V_I            0x03U        // xxxx x110 - call both V and I channel
// 1 C4 C3  0 0 1   I
// 1 C4 C3  0 1 0   V
// 1 C4 C3  1 1 0   I & V
// For calibration, C[2:0] specifies the channel(s).

typedef struct {
    uint8 page;
    uint8 addr;
    uint32 val;
} CS5490_RegValueType;

typedef struct {
    boolean useUart;
    struct spi_bus spi;
    uint8 spiChannel;
    Uart_ChannelType uart;
    uint16 uartBaud;
    uint32 oscFreq;
    Dio_ChannelType resetPin;
    Dio_LevelType resetAssertLevel;
    uint8 regNum;
    const CS5490_RegValueType *regVals;
} CS5490_PlatformType;

typedef enum {
    CS5490_IGAIN_X10,
    CS5490_IGAIN_X50,
} CS5490_IGainType;


typedef struct cs5490 {
    const CS5490_PlatformType *platform;
    CS5490_IGainType igain1;
    CS5490_IGainType igain2;
    uint8 recv_index;
    uint8 recv_buffer[10];
} CS5490_DeviceType;

typedef enum {
    CS5490_SAMPLE_CURRENT,
    CS5490_SAMPLE_VOLTAGE,
} CS5490_SampleChannel;


Std_ReturnType cs5490_init(struct cs5490 *dev);
Std_ReturnType cs5490_write_reg(const struct cs5490 *dev, uint8 pg, uint8 addr, uint32 value);
Std_ReturnType cs5490_send_instruction(const struct cs5490 *dev, uint8 cmd);
Std_ReturnType cs5490_set_igain(struct cs5490 *dev, CS5490_IGainType gain1, CS5490_IGainType gain2);

Std_ReturnType cs5490_write_and_check(struct cs5490 *dev, uint8 page, uint8 addr, uint32 val);
Std_ReturnType cs4509_calibration_dc_current(struct cs5490 *dev, uint32 count);
Std_ReturnType cs5490_set_sample_count(struct cs5490 *dev, uint32 count);
// Std_ReturnType cs5490_single_conv_irms(struct cs5490 *dev, uint16 timeout, sint32 *result);
Std_ReturnType cs5490_single_conv_ipeak(struct cs5490 *dev, uint16 timeout, sint32 *result);
// Std_ReturnType cs5490_single_conv(struct cs5490 *dev, uint16 timeout, sint32 *rms, sint32 *peak);

#define cs5490_clear_status_flag(dev, flag)  cs5490_write_reg(dev, 0U, 23U, flag)


Std_ReturnType cs5490_read_signed_reg(struct cs5490 *dev, uint8 page, uint8 addr, sint32 *result);
#define cs5490_read_pavg1(dev, result) cs5490_read_signed_reg(dev, 16U, 5U, result)
#define cs5490_read_pavg2(dev, result) cs5490_read_signed_reg(dev, 16U, 11U, result)
#define cs5490_read_temperature(dev, result)  cs5490_read_signed_reg(dev, 16U, 27U, result)


Std_ReturnType cs5490_read_unsigned_reg(struct cs5490 *dev, uint8 page, uint8 addr, uint32 *result);
#define cs5490_read_irms1(dev, result) cs5490_read_unsigned_reg(dev, 16U, 6U, result)
#define cs5490_read_irms2(dev, result) cs5490_read_unsigned_reg(dev, 16U, 12U, result)
#define cs5490_read_status0(dev, result)  cs5490_read_unsigned_reg(dev, 0U, 23U, result)

#define CS5490_STATUS0_I1_OVERFLOW (1UL << 12)
#define CS5490_STATUS0_P1_OVERFLOW (1UL << 14)
#define CS5490_STATUS0_DRDY        (1UL << 23)

#define cs5409_start_continue_conv(dev) cs5490_send_instruction(dev, CS_INSTRUCTION_CONT_CONV)

Std_ReturnType cs5490_get_irms1(struct cs5490 *dev, sint32 *result);
Std_ReturnType cs5490_get_irms2(struct cs5490 *dev, sint32 *result);

#endif
