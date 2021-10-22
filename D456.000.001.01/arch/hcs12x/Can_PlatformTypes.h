#ifndef CAN_PLATFOMR_TYPES_H_
#define CAN_PLATFOMR_TYPES_H_

#include "Cpu.h"
#include "CanIf_Types.h"

#define CAN_CTRL_MAX 5

#define Can_DisableGlobalInterrupts() imask_t flag; Irq_Save(flag)
#define Can_EnableGlobalInterrupts() Irq_Restore(flag)

#pragma push
#pragma MESSAGE DISABLE C1106
typedef union {
     volatile uint32 R;
     struct {
         volatile uint16 xx_1:8;
         volatile uint16 xx_23:16;
         volatile uint16 BIT1ERR:1;
         volatile uint16 BIT0ERR:1;
         volatile uint16 ACKERR:1;
         volatile uint16 CRCERR:1;
         volatile uint16 FRMERR:1;
         volatile uint16 STFERR:1;
         volatile uint16 TXWRN:1;
         volatile uint16 RXWRN:1;
     } B;
} Can_ErrorType;
#pragma pop


typedef enum {
    CAN_CTRL_0 = 0,
    CAN_CTRL_1 = 1,
    CAN_CTRL_2 = 2,
    CAN_CTRL_3 = 3,
    CAN_CTRL_4 = 4,
    CAN_CTRL_NONE = 0xFF,
} Can_ControllerHwIdType;

typedef uint8 CanConfigIdType;


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


typedef struct {
    void (*CancelTxConfirmation)(PduIdType CanTxPduId);
    void (*RxIndication)(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);
    void (*ControllerBusOff)(uint8 Controller);
    void (*TxConfirmation)(PduIdType CanTxPduId);
    void (*ControllerWakeup)(uint8 Controller);
    void (*ControllerModeIndication)(uint8 Controller, CanIf_ControllerModeType mode);
    void (*Error)(uint8 Controller, Can_ErrorType error);
} Can_CallbackType;


typedef enum {
    CAN_IDAM_2_32BIT = (uint16)0U << 4,
    CAN_IDAM_4_16BIT = (uint16)1U << 4,
    CAN_IDAM_8_8BIT = (uint16)2U << 4,
    CAN_IDAM_FILTER_CLOSED = (uint16)3U << 4,
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
    Can_ControllerRefIdType controllerRef;

    // Specifies if the HardwareObject is used as Transmit or as Receive object
    Can_ObjectTypeType CanObjectType;

    // End Of List. Set to TRUE is this is the last object in the list.
    boolean EndFlag;
} Can_HardwareObjectType;

typedef enum {
    CAN_PROCESS_TYPE_INTERRUPT,
    CAN_PROCESS_TYPE_POLLING
} Can_ProcessType;

typedef struct {
    // Defines if a CAN controller is used in the configuration.
    boolean CanControllerActivation;

    // Specifies the buadrate of the controller in kbps.
    uint32 CanControllerBaudRate;

    // Specifies propagation delay in time quantas.
    uint32 CanControllerPropSeg;

    // Specifies phase segment 1 in time quantas.
    uint32 CanControllerSeg1;

    // Specifies phase segment 2 in time quantas.
    uint32 CanControllerSeg2;

    //  Specifies the time quanta for the controller. The calculation of the resulting
    //  prescaler value depending on module clocking and time quanta shall be
    //  done offline Hardware specific.
    uint32 CanControllerTimeQuanta;

    //  Reference to the CPU clock configuration, which is set in the MCU driver
    //  configuration
    uint32 CanCpuClockRef;

    //  This parameter contains a reference to the Wakeup Source for this
    //  controller as defined in the ECU State Manager. Implementation Type:
    //  reference to EcuM_WakeupSourceType
    uint32 CanWakeupSourceRef;

    // List of Hoh id's that belong to this controller
    const Can_HardwareObjectType *CanHardwareObject;

    boolean Can_Loopback;

    // Set this to use the fifo
    boolean Can_Fifo;

    const Can_FilterMaskType *CanFilterMaskRef;
    uint16 CanBOR_Time;
} Can_HardwareConfigType;


typedef struct {
    const Can_HardwareConfigType *CanHardwareConfig;
    const Can_CallbackType CanCallbacks;
} Can_ConfigType;


#endif /*CAN_CFG_H_*/
