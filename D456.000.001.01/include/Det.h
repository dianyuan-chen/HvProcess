/**
 * \addtogroup autosar
 * \{
 * \addtogroup DET
 * \{
 */

#ifndef DET_H
#define DET_H

#include "Std_Types.h"

#define DET_MODULE_ID            MODULE_ID_DET
#define DET_VENDOR_ID            VENDOR_ID_ARCCORE

/* Implementation version */
#define DET_SW_MAJOR_VERSION     1
#define DET_SW_MINOR_VERSION     0
#define DET_SW_PATCH_VERSION     0

/* AUTOSAR specification document version */
#define DET_AR_MAJOR_VERSION     3
#define DET_AR_MINOR_VERSION     1
#define DET_AR_PATCH_VERSION     5

#include "Det_Cfg.h"


// Error codes
#define DET_E_CBK_REGISTRATION_FAILED 0x01
#define DET_E_INDEX_OUT_OF_RANGE      0x02

#define DET_CALLBACK_API              0xFF

#define DET_CBK_REGISTRATION_FAILED_INDEX   0xFF

// Type used to store errors
typedef struct {
    uint16 moduleId;
    uint8 instanceId;
    uint8 apiId;
    uint8 errorId;
} Det_EntryType;

typedef void (*detCbk_t)( uint16 ModuleId, uint8 InstanceId , uint8 ApiId, uint8 ErrorId);
uint8 Det_AddCbk ( detCbk_t detCbk);
void Det_RemoveCbk ( uint8 detCbkIndex);

void Det_Init( void );
void Det_DeInit( void );
void Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
void Det_Start( void );
void Det_MainFunction(void);

#define Det_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,DET)

#endif /*DET_H*/

/**
 * \}
 * \}
 */
