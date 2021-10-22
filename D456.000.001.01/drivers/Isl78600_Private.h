#ifndef __ISL78600_PRIVATE_H__
#define __ISL78600_PRIVATE_H__

#define ISL_PAGE_SAMPLE_R                       0x01U
#define ISL_PAGE_CONFIG_R                       0x02U
#define ISL_PAGE_CONFIG_W                       0x0AU
#define ISL_PAGE_COMMAND_R                      0x03U
#define ISL_PAGE_EEPROM_R                       0x04U
#define ISL_PAGE_CHECKSUM_R                     0x05U

/**
 * if(v < 0x2000) voltage = v * 15.935 * 2500 / 8192
 * else voltage = (v - 16384) * 15.935 * 2500 / 8192
 */
#define ISL_REG_SAMPLE_VBAT                     0x00U
/**
 * if(v < 0x2000) voltage = v * 2 * 2500 / 8192
 * else voltage = (v - 16384) * 2 * 2500 / 8192
 */
#define ISL_REG_SAMPLE_V1                       0x01U
#define ISL_REG_SAMPLE_V2                       0x02U
#define ISL_REG_SAMPLE_V3                       0x03U
#define ISL_REG_SAMPLE_V4                       0x04U
#define ISL_REG_SAMPLE_V5                       0x05U
#define ISL_REG_SAMPLE_V6                       0x06U
#define ISL_REG_SAMPLE_V7                       0x07U
#define ISL_REG_SAMPLE_V8                       0x08U
#define ISL_REG_SAMPLE_V9                       0x09U
#define ISL_REG_SAMPLE_V10                      0x0AU
#define ISL_REG_SAMPLE_V11                      0x0BU
#define ISL_REG_SAMPLE_V12                      0x0CU
#define ISL_REG_SAMPLE_VALL                     0x0FU

#define ISL_REG_SAMPLE_IT                       0x10U
#define ISL_REG_SAMPLE_ET1                      0x11U
#define ISL_REG_SAMPLE_ET2                      0x12U
#define ISL_REG_SAMPLE_ET3                      0x13U
#define ISL_REG_SAMPLE_ET4                      0x14U
#define ISL_REG_SAMPLE_SRV                      0x15U
#define ISL_REG_SAMPLE_SCNT                     0x16U
#define ISL_REG_SAMPLE_TALL                     0x1FU

#define ISL_REG_CONFIG_OV_FAULT                 0x00U
#define ISL_REG_CONFIG_UV_FAULT                 0x01U
#define ISL_REG_CONFIG_OW_FAULT                 0x02U
#define ISL_REG_CONFIG_FAULT_SETUP              0x03U
#define ISL_REG_CONFIG_FAULT_STATUS             0x04U
#define ISL_REG_CONFIG_CELL_SETUP               0x05U
#define ISL_REG_CONFIG_OT_FAULT                 0x06U
#define ISL_REG_CONFIG_ALL_FAULT                0x0FU
#define ISL_REG_CONFIG_OV_LIMIT                 0x10U
#define ISL_REG_CONFIG_UV_LIMIT                 0x11U
#define ISL_REG_CONFIG_ET_LIMIT                 0x12U
#define ISL_REG_CONFIG_BL_SETUP                 0x13U
#define ISL_REG_CONFIG_BL_STATUS                0x14U
#define ISL_REG_CONFIG_WDT_TIME                 0x15U
#define ISL_REG_CONFIG_USER_L                   0x16U
#define ISL_REG_CONFIG_USER_H                   0x17U
#define ISL_REG_CONFIG_COMMS_SETUP              0x18U
#define ISL_REG_CONFIG_DEV_SETUP                0x19U
#define ISL_REG_CONFIG_IT_LIMIT                 0x1AU
#define ISL_REG_CONFIG_SN_L                     0x1BU
#define ISL_REG_CONFIG_SN_H                     0x1CU
#define ISL_REG_CONFIG_TRIM_VOLTAGE             0x1DU
#define ISL_REG_CONFIG_ALL_SETUP                0x1FU
#define ISL_REG_CONFIG_BL_ENABLE                0x3BU

#define ISL_REG_COMMAND_SCAN_VOTLAGES           0x01U
#define ISL_REG_COMMAND_SCAN_TEMPS              0x02U
#define ISL_REG_COMMAND_SCAN_MIXED              0x03U
#define ISL_REG_COMMAND_SCAN_WIRES              0x04U
#define ISL_REG_COMMAND_SCAN_ALL                0x05U
#define ISL_REG_COMMAND_SCAN_CONTINUOUS         0x06U
#define ISL_REG_COMMAND_SCAN_INHIBIT            0x07U
#define ISL_REG_COMMAND_MEASURE                 0x08U
#define ISL_REG_COMMAND_IDENTIFY                0x09U
#define ISL_REG_COMMAND_SLEEP                   0x0AU
#define ISL_REG_COMMAND_NAK                     0x0BU
#define ISL_REG_COMMAND_ACK                     0x0CU
#define ISL_REG_COMMAND_COMMS_FAILURE           0x0EU
#define ISL_REG_COMMAND_WAKEUP                  0x0FU
#define ISL_REG_COMMAND_BL_ENABLE               0x10U
#define ISL_REG_COMMAND_BL_INHIBIT              0x11U
#define ISL_REG_COMMAND_RESET                   0x12U
#define ISL_REG_COMMAND_CALC_CHECKSUM           0x13U
#define ISL_REG_COMMAND_CHECK_CHECKSUM          0x14U

#define ISL_INVALID_REG                         0xFFU
#define ISL_ALL_DEVICES_ADDRESS                 0x0FU

Isl_ReturnType Isl78600_DaisySendCmd(const struct Isl78600 *dev, uint8 addr, uint8 page, uint8 reg, uint8 suffix);
Isl_ReturnType Isl78600_DaisyReadData(const struct Isl78600 *dev, uint8 addr, uint8 page, uint8 reg, uint16 *value);
Isl_ReturnType Isl78600_DaisyWriteData(const struct Isl78600 *dev, uint8 addr, uint8 page, uint8 reg, uint16 value);
Isl_ReturnType Isl78600_DaisyIdentify(const struct Isl78600 *dev);

Isl_ReturnType Isl78600_NonDaisySendCmd(const struct Isl78600 *dev, uint8 add, uint8 page, uint8 reg, uint8 suffix);
Isl_ReturnType Isl78600_NonDaisyReadData(const struct Isl78600 *dev, uint8 addr, uint8 page, uint8 reg, uint16 *value);
Isl_ReturnType Isl78600_NonDaisyWriteData(const struct Isl78600 *dev, uint8 addr, uint8 page, uint8 reg, uint16 value);
Isl_ReturnType Isl78600_NonDaisyIdentify(const struct Isl78600 *dev);

#endif
