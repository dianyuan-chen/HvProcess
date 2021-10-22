#ifndef DIO_TYPES_H
#define DIO_TYPES_H

typedef uint8 Dio_ChannelType;
typedef uint8 Dio_PortType;

/** @req DIO021 */
/** @req DIO022 */
typedef struct
{
  Dio_PortType port;
  uint8 offset;
  uint8 mask;
} Dio_ChannelGroupType;

typedef uint8 Dio_PortLevelType;
#define DIO_END_OF_PORT_LIST  (0xFFU)
#define DIO_END_OF_CHANNEL_GROUP {DIO_END_OF_PORT_LIST, 0, 0}

// Physical ports
typedef enum {
    DIO_PORT_A = 0x00,
    DIO_PORT_B = 0x01,
    DIO_PORT_C = 0x02,
    DIO_PORT_D = 0x03,
    DIO_PORT_E = 0x04,
    DIO_PORT_F = 0x05,
    DIO_PORT_H = 0x06,
    DIO_PORT_J = 0x07,
    DIO_PORT_K = 0x08,
    DIO_PORT_L = 0x09,
    DIO_PORT_M = 0x0A,
    DIO_PORT_P = 0x0B,
    DIO_PORT_R = 0x0C,
    DIO_PORT_S = 0x0D,
    DIO_PORT_T = 0x0E,
    DIO_PORT_AN_00_07 = 0x0F,
    DIO_PORT_AN_08_15 = 0x10,
    DIO_PORT_AN_16_23 = 0x11,
    DIO_PORT_AN_24_31 = 0x12,
} Dio_PortTypesType;

#define DIO_CHANNEL(port, index) ((uint8)((uint8)(DIO_PORT_##port) << 3) + (index))
#define DIO_CHANNEL_NONE      (0xFFU)

#endif
