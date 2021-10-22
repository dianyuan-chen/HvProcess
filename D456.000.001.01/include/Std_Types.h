/**
 * \addtogroup autosar
 * \{
 * \addtogroup General General
 * \{
 */

/** @file Std_Types.h
 *  Definitions of General types.
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/*
Autosar include files....
TODO: we haven't really defined the autosar types yet.
      the standard types are uint8, etc.
*/

#include "Platform_Types.h" /*TODO: move*/
#include "Compiler.h"

#ifndef     NULL
/*lint -esym(960,20.2) // PC-Lint LINT EXCEPTION*/
#define NULL    0
#endif
/*
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
*/

typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8  instanceID;

    uint8 sw_major_version;    /**< Vendor numbers */
    uint8 sw_minor_version;    /**< Vendor numbers */
    uint8 sw_patch_version;    /**< Vendor numbers */

    uint8 ar_major_version;    /**< Autosar spec. numbers */
    uint8 ar_minor_version;    /**< Autosar spec. numbers */
    uint8 ar_patch_version;    /**< Autosar spec. numbers */
} Std_VersionInfoType;

/** make compare number... #if version > 10203  ( 1.2.3 ) */
#define STD_GET_VERSION (_major,_minor,_patch) (_major * 10000U + _minor * 100U + _patch)

/** Create Std_VersionInfoType */
/*PC-Lint Exception MISRA rule 19.12*/
/*lint -save -esym(960,19.12)*/
#define STD_GET_VERSION_INFO(_vi,_module) \
    if(_vi != NULL) {\
        ((_vi)->vendorID =  _module ## _VENDOR_ID);\
        ((_vi)->moduleID = _module ## _MODULE_ID);\
        ((_vi)->sw_major_version = _module ## _SW_MAJOR_VERSION);\
        ((_vi)->sw_minor_version =  _module ## _SW_MINOR_VERSION);\
        ((_vi)->sw_patch_version =  _module ## _SW_PATCH_VERSION);\
        ((_vi)->ar_major_version =  _module ## _AR_MAJOR_VERSION);\
        ((_vi)->ar_minor_version =  _module ## _AR_MINOR_VERSION);\
        ((_vi)->ar_patch_version =  _module ## _AR_PATCH_VERSION);\
    }
/*lint -restore*/

#ifndef MIN
#define MIN(_x,_y) (((_x) < (_y)) ? (_x) : (_y))
#endif
#ifndef MAX
#define MAX(_x,_y) (((_x) > (_y)) ? (_x) : (_y))
#endif

#ifndef BIT_SET
#define BIT_SET(data, bit)          ((data) |= ((1UL) << (unsigned char)(bit)))
#endif
#ifndef BIT_CLR
#define BIT_CLR(data, bit)          ((data) &= (((1UL) << (unsigned char)(bit)) ^ (~0UL)))
#endif
#ifndef BIT_TEST
#define BIT_TEST(data, bit)         ((data) & (1UL << (unsigned char)(bit)))
#endif

typedef uint8 Std_ReturnType;

/**
 * \brief 电路故障标准类型定义
 */
typedef enum{
    STD_CIRCUIT_FAULT_NONE, /**< 电路正常 */
    STD_CIRCUIT_FAULT_OPEN, /**< 电路开路故障 */
    STD_CIRCUIT_FAULT_SHORT /**< 电路短路故障 */
}Std_CircuitFaultType;

/**
 * \brief 通信故障标准类型定义
 */
typedef enum{
    STD_COMMUNICATION_OK, /**< 通信正常 */
    STD_COMMUNICATION_ABORT /**< 通信中断 */
}Std_CommunicationFaultType;


#define E_OK                    (Std_ReturnType)0U
#define E_NOT_OK                (Std_ReturnType)1U

#define E_NO_DTC_AVAILABLE      (Std_ReturnType)2U
#define E_SESSION_NOT_ALLOWED   (Std_ReturnType)4U
#define E_PROTOCOL_NOT_ALLOWED  (Std_ReturnType)5U
#define E_REQUEST_NOT_ACCEPTED  (Std_ReturnType)8U
#define E_REQUEST_ENV_NOK       (Std_ReturnType)9U

#define E_PENDING               (Std_ReturnType)10U
#define E_COMPARE_KEY_FAILED    (Std_ReturnType)11U
#define E_FORCE_RCRRP           (Std_ReturnType)12U

#define STD_HIGH        0x01U
#define STD_LOW         0x00U

#define STD_ACTIVE      0x01U
#define STD_IDLE        0x00U

#define STD_ON          0x01U
#define STD_OFF         0x00U


#endif
/**
 * \}
 * \}
 */
