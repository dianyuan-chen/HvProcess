/**
 * \addtogroup autosar
 * \{
 * \addtogroup CAN
 * \{
 */

#ifndef _CAN_GENERALTYPES_H_
#define _CAN_GENERALTYPES_H_

#include "ComStack_Types.h"

#define CAN_DATA_DLC (0x8U)

typedef uint32 Can_IdType;

typedef uint8 Can_ControllerRefIdType;
typedef uint8 Can_HwHandleType;


typedef struct {
    uint8 xx;
} Can_HwType;

typedef struct {
    PduIdType swPduHandle;
    uint8 length;
    Can_IdType id;
    uint8 *sdu;
} Can_PduType;

typedef enum {
    CAN_OK = 0,
    CAN_NOT_OK = 1,
    CAN_BUSY = 2,
} Can_ReturnType;

typedef struct {
    Can_HwHandleType controllerRef;
    Can_IdType id;
    uint8 phyHohType;
    uint8 filterRef;
} Can_HardwareObjectConfig;

#endif

/**
 * \}
 * \}
 */
