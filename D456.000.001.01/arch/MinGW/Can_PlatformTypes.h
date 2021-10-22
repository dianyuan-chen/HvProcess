#ifndef CAN_PLATFORM_TYPES_H
#define CAN_PLATFORM_TYPES_H

#include "Can_GeneralTypes.h"
#include "usbcan.h"

#define Can_DisableGlobalInterrupts() 
#define Can_EnableGlobalInterrupts() 

typedef enum {
    CAN_CTRL_0 = 0,
    CAN_CTRL_1 = 1,
    CAN_CTRL_MAX = 2,
} Can_ControllerHwIdType;


typedef enum {
    CAN_ID_TYPE_EXTENDED,
    CAN_ID_TYPE_MIXED,
    CAN_ID_TYPE_STANDARD
} Can_IdTypeType;

typedef enum {
    CAN_OBJECT_TYPE_RECEIVE,
    CAN_OBJECT_TYPE_TRANSMIT
} Can_ObjectTypeType;


typedef enum {
    CAN_HANDLE_TYPE_BASIC,
    CAN_HANDLE_TYPE_FULL
} Can_HohType;


enum ControllerModeType;

typedef struct {
    void (*CancelTxConfirmation)(PduIdType CanTxPduId);
    void (*RxIndication)(uint8 , Can_IdType , uint8 , const uint8 *);
    void (*ControllerBusOff)(uint8);
    void (*TxConfirmation)(PduIdType);
    void (*ControllerWakeup)(uint8);
    void (*ControllerModeIndication)(uint8, enum ControllerModeType);
} Can_CallbackType;


typedef enum {
    CAN_IDAM_2_32BIT,
    CAN_IDAM_4_16BIT,
    CAN_IDAM_8_8BIT,
    CAN_IDAM_FILTER_CLOSED,
} Can_IDAMType;

typedef struct {
    uint8 idmr[8]; // Identifier Mask Register, 1 = ignore corresponding acceptance code register bit
    uint8 idar[8]; // Identifier Acceptance Register
    Can_IDAMType idam;
} Can_FilterMaskType;

typedef struct Can_HardwareObjectStruct {
    Can_HwHandleType Hoh;
    // Specifies whether the IdValue is of type - standard identifier - extended
    // identifier - mixed mode ImplementationType: Can_IdType
    Can_IdTypeType CanIdType;

    Can_ControllerRefIdType controllerRef;

    // Specifies if the HardwareObject is used as Transmit or as Receive object
    Can_ObjectTypeType CanObjectType;

    // Reference to the filter mask that is used for hardware filtering togerther
    // with the CAN_ID_VALUE
    Can_FilterMaskType *CanFilterMaskRef;

    // End Of List. Set to TRUE is this is the last object in the list.
    boolean EndFlag;
} Can_HardwareObjectType;

typedef struct {
    VCI_INIT_CONFIG InitConfig;
    const Can_HardwareObjectType *CanHardwareObject;
} Can_HardwareConfigType;


typedef struct {
    DWORD CanDeviceType;
    DWORD CanDeviceIndex;
    const Can_HardwareConfigType *CanHardwareConfig[CAN_USED_CONTROLLER_NUM];
    const Can_CallbackType CanCallbacks;
} Can_ConfigType;


#endif /*CAN_PLATFORM_TYPES_H*/
