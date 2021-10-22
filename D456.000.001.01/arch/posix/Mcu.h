#ifndef MCU_H_
#define MCU_H_

#define MCU_SW_MAJOR_VERSION        2
#define MCU_SW_MINOR_VERSION        0
#define MCU_SW_PATCH_VERSION        0

#define MCU_AR_MAJOR_VERSION        2
#define MCU_AR_MINOR_VERSION        2
#define MCU_AR_PATCH_VERSION        2


#include "Std_Types.h"
#include "Mcu_Cfg.h"
#include "Irq_Types.h"

/** @name Service id's */
//@{
#define MCU_INIT_SERVICE_ID                 0x00
#define MCU_INITRAMSECTION_SERVICE_ID       0x01
#define MCU_INITCLOCK_SERVICE_ID            0x02
#define MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID   0x03
#define MCU_GETPLLSTATUS_SERVICE_ID         0x04
#define MCU_GETRESETREASON_SERVICE_ID       0x05
#define MCU_GETRESETRAWVALUE_SERVICE_ID     0x06
#define MCU_PERFORMRESET_SERVICE_ID         0x07
#define MCU_SETMODE_SERVICE_ID              0x08
#define MCU_GETVERSIONINFO_SERVICE_ID       0x09
#define MCU_INTCVECTORINSTALL_SERVICE_ID    0x0A // Not in spec but follows pattern
//@}

/** @name Error Codes */
//@{
#define MCU_E_PARAM_CONFIG                  0x0A
#define MCU_E_PARAM_CLOCK                   0x0B
#define MCU_E_PARAM_MODE                    0x0C
#define MCU_E_PARAM_RAMSECTION              0x0D
#define MCU_E_PLL_NOT_LOCKED                0x0E
#define MCU_E_UNINIT                        0x0F
//@}

/* Specific return values */
#define MCU_GETRESETRAWVALUE_NORESETREG_RV  0x00 /**< MCU006 */
#define MCU_GETRESETRAWVALUE_UNINIT_RV      0xffffffff /**< MCU135 */


typedef enum {
    MCU_PLL_LOCKED,
    MCU_PLL_UNLOCKED,
    MCU_PLL_STATUS_UNDEFINED,
} Mcu_PllStatusType;


//TODO
typedef uint8 Mcu_RamSectionType;

typedef uint32 Mcu_RawResetType;

typedef enum {
    MCU_POWER_ON_RESET,
    MCU_WATCHDOG_RESET,
    MCU_SW_RESET,
    MCU_RESET_UNDEFINED,
    MCU_OSC_FAILURE_RESET,
    MCU_CPU_RESET,
    MCU_EXT_RESET,
    MCU_VSW_RESET
} Mcu_ResetType;

typedef struct {
    //  This is the frequency for the specific instance of the McuClockReference-
    //  Point container. It shall be givn in Hz.
    uint32 McuClockReferencePointFrequency;
    uint8 Pll1; // PLL setting 1
    uint8 Pll2; // PLL setting 2
    uint8 PITPrescale0;
    uint8 PITPrescale1;
    uint8 EtcPrescale;
} Mcu_ClockSettingConfigType;

typedef struct {
    // This parameter shall represent the Data pre-setting to be initialized
    uint32 McuRamDefaultValue;

    // This parameter shall represent the MCU RAM section base address
    uint32 McuRamSectionBaseAddress;

    // This parameter shall represent the MCU RAM Section size
    uint32 McuRamSectionSize;

} Mcu_RamSectorSettingConfigType;

typedef struct {
    //  Enables/Disables clock failure notification. In case this feature is not supported
    //  by HW the setting should be disabled.
    uint8 McuClockSrcFailureNotification;

    //  This parameter shall represent the number of Modes available for the
    //  MCU. calculationFormula = Number of configured McuModeSettingConf
    //uint8 McuNumberOfMcuModes; /* Not supported */

    //  This parameter shall represent the number of RAM sectors available for
    //  the MCU. calculationFormula = Number of configured McuRamSectorSet-
    //  tingConf
    uint8 McuRamSectors;

    //  This parameter shall represent the number of clock setting available for
    //  the MCU.
    uint8 McuClockSettings;

    // This parameter defines the default clock settings that should be used
    // It is an index into the McuClockSettingsConfig
    Mcu_ClockType McuDefaultClockSettings;

    //  This parameter relates to the MCU specific reset configuration. This ap-
    //  plies to the function Mcu_PerformReset, which performs a microcontroller
    //  reset using the hardware feature of the microcontroller.
    //uint32 McuResetSetting;

    //  This container contains the configuration (parameters) for the
    //  Clock settings of the MCU. Please see MCU031 for more in-
    //  formation on the MCU clock settings.
    const Mcu_ClockSettingConfigType *McuClockSettingConfig;

    //  This container contains the configuration (parameters) for the
    //  Mode setting of the MCU. Please see MCU035 for more information
    //  on the MCU mode settings.
    //Mcu_ModeSettingConfigType  *McuModeSettingConfig;

    //  This container contains the configuration (parameters) for the
    //  RAM Sector setting. Please see MCU030 for more information
    //  on RAM sec-tor settings.
    const Mcu_RamSectorSettingConfigType *McuRamSectorSettingConfig;

} Mcu_ConfigType;

extern const Mcu_ConfigType McuConfigData[];



void Mcu_Init(const Mcu_ConfigType *configPtr);
void Mcu_DeInit(void);
Std_ReturnType Mcu_InitRamSection(const Mcu_RamSectionType RamSection);
Std_ReturnType Mcu_InitClock(const Mcu_ClockType ClockSetting);
void Mcu_DistributePllClock(void);
Mcu_PllStatusType Mcu_GetPllStatus(void);
Mcu_ResetType Mcu_GetResetReason(void);
Mcu_RawResetType Mcu_GetResetRawValue(void);
#if ( MCU_PERFORM_RESET_API == STD_ON )
void Mcu_PerformReset(void);
#endif
void Mcu_SetMode(const Mcu_ModeType McuMode);

#if ( MCU_VERSION_INFO_API == STD_ON )
#define Mcu_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,MCU)
#endif

void Irq_GenerateSoftInt(Irq_Type vector);
//uint8 Irq_GetCurrentPriority(Cpu_t cpu);
uint32 McuE_GetSystemClock(void);
void Mcu_Arc_EnterLowPower(int mode);
void McuE_LowPowerRecoverFlash(void);

#endif /*MCU_H_*/
/** @} */
