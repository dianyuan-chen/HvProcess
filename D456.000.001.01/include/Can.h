/**
 * \addtogroup autosar
 * \{
 * \addtogroup CAN CAN驱动
 * \{
 */

#ifndef CAN_H_
#define CAN_H_

#define CAN_VENDOR_ID               VENDOR_ID_UDAN
#define CAN_MODULE_ID               MODULE_ID_CAN
#define CAN_AR_MAJOR_VERSION    3
#define CAN_AR_MINOR_VERSION    1
#define CAN_AR_PATCH_VERSION    5

#define CAN_SW_MAJOR_VERSION    1
#define CAN_SW_MINOR_VERSION    0
#define CAN_SW_PATCH_VERSION    0

#define CAN_E_PARAM_POINTER     0x01
#define CAN_E_PARAM_HANDLE      0x02
#define CAN_E_PARAM_DLC         0x03
#define CAN_E_PARAM_CONTROLLER  0x04
// API service used without initialization
#define CAN_E_UNINIT            0x05
// Init transition for current mode
#define CAN_E_TRANSITION        0x06

#define CAN_E_DATALOST          0x07     /** @req 4.0.3/CAN395 */

/** @name Service id's */
//@{
#define CAN_INIT_SERVICE_ID                         0x00
#define CAN_MAINFUNCTION_WRITE_SERVICE_ID           0x01
#define CAN_INITCONTROLLER_SERVICE_ID               0x02
#define CAN_SETCONTROLLERMODE_SERVICE_ID            0x03
#define CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID  0x04
#define CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID   0x05
#define CAN_WRITE_SERVICE_ID                        0x06
#define CAN_GETVERSIONINFO_SERVICE_ID               0x07
#define CAN_MAINFUNCTION_READ_SERVICE_ID            0x08
#define CAN_MAINFUNCTION_BUSOFF_SERVICE_ID          0x09
#define CAN_MAINFUNCTION_WAKEUP_SERVICE_ID          0x0a
#define CAN_CBK_CHECKWAKEUP_SERVICE_ID              0x0b
//@}

#include "Std_Types.h"
#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"
#include "Can_PlatformTypes.h"
#include "ComStack_Types.h"
#include "Can_LCfg.h"

typedef enum {
    CAN_T_START,
    CAN_T_STOP,
    CAN_T_SLEEP,
    CAN_T_WAKEUP
} Can_StateTransitionType;

void Can_Init(const Can_ConfigType *Config);
void Can_DeInit(void);


#if ( CAN_VERSION_INFO_API == STD_ON )
#define Can_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,CAN)
#endif

Can_ReturnType Can_SetControllerMode(Can_ControllerRefIdType ref, Can_StateTransitionType transition);
void Can_DisableControllerInterrupts(Can_ControllerRefIdType ref);
void Can_EnableControllerInterrupts(Can_ControllerRefIdType ref);

Can_ReturnType Can_Write(Can_HwHandleType hth, const Can_PduType *pduInfo);

void Can_MainFunction_Write(void);
void Can_MainFunction_Read(void);
void Can_MainFunction_BusOff(void);
void Can_MainFunction_Error(void);
void Can_MainFunction_Wakeup(void);


#endif /*CAN_H_*/


/**
 * \}
 * \}
 */
