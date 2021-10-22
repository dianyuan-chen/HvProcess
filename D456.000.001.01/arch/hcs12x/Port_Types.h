#ifndef PORT_TYPES_H_
#define PORT_TYPES_H_

#include "Std_Types.h"

#define PORT_A_BASE          (uint8)((uint8)0x00<<3)
#define PORT_B_BASE          (uint8)((uint8)0x01<<3)
#define PORT_C_BASE          (uint8)((uint8)0x02<<3)
#define PORT_D_BASE          (uint8)((uint8)0x03<<3)
#define PORT_E_BASE          (uint8)((uint8)0x04<<3)
#define PORT_F_BASE          (uint8)((uint8)0x05<<3)
#define PORT_H_BASE          (uint8)((uint8)0x06<<3)
#define PORT_J_BASE          (uint8)((uint8)0x07<<3)
#define PORT_K_BASE          (uint8)((uint8)0x08<<3)
#define PORT_L_BASE          (uint8)((uint8)0x09<<3)
#define PORT_M_BASE          (uint8)((uint8)0x0A<<3)
#define PORT_P_BASE          (uint8)((uint8)0x0B<<3)
#define PORT_R_BASE          (uint8)((uint8)0x0C<<3)
#define PORT_S_BASE          (uint8)((uint8)0x0D<<3)
#define PORT_T_BASE          (uint8)((uint8)0x0E<<3)
#define PORT_AN_08_15_BASE   (uint8)((uint8)0x0F<<3)
#define PORT_AN_00_07_BASE   (uint8)((uint8)0x10<<3)
#define PORT_AN_24_31_BASE   (uint8)((uint8)0x11<<3)
#define PORT_AN_16_23_BASE   (uint8)((uint8)0x12<<3)

#define PORT_INDEX_MAX       0x12U
#define PORT_BITMASK         0x07U
#define PORT_BASEMASK        0xF8U

typedef enum {
    PORT_PA0 = PORT_A_BASE,
    PORT_PA1 = PORT_A_BASE + 1U,
    PORT_PA2 = PORT_A_BASE + 2U,
    PORT_PA3 = PORT_A_BASE + 3U,
    PORT_PA4 = PORT_A_BASE + 4U,
    PORT_PA5 = PORT_A_BASE + 5U,
    PORT_PA6 = PORT_A_BASE + 6U,
    PORT_PA7 = PORT_A_BASE + 7U,
    PORT_PB0 = PORT_B_BASE,
    PORT_PB1 = PORT_B_BASE + 1U,
    PORT_PB2 = PORT_B_BASE + 2U,
    PORT_PB3 = PORT_B_BASE + 3U,
    PORT_PB4 = PORT_B_BASE + 4U,
    PORT_PB5 = PORT_B_BASE + 5U,
    PORT_PB6 = PORT_B_BASE + 6U,
    PORT_PB7 = PORT_B_BASE + 7U,
    PORT_PC0 = PORT_C_BASE,
    PORT_PC1 = PORT_C_BASE + 1U,
    PORT_PC2 = PORT_C_BASE + 2U,
    PORT_PC3 = PORT_C_BASE + 3U,
    PORT_PC4 = PORT_C_BASE + 4U,
    PORT_PC5 = PORT_C_BASE + 5U,
    PORT_PC6 = PORT_C_BASE + 6U,
    PORT_PC7 = PORT_C_BASE + 7U,
    PORT_PD0 = PORT_D_BASE,
    PORT_PD1 = PORT_D_BASE + 1U,
    PORT_PD2 = PORT_D_BASE + 2U,
    PORT_PD3 = PORT_D_BASE + 3U,
    PORT_PD4 = PORT_D_BASE + 4U,
    PORT_PD5 = PORT_D_BASE + 5U,
    PORT_PD6 = PORT_D_BASE + 6U,
    PORT_PD7 = PORT_D_BASE + 7U,
    PORT_PE0 = PORT_E_BASE,
    PORT_PE1 = PORT_E_BASE + 1U,
    PORT_PE2 = PORT_E_BASE + 2U,
    PORT_PE3 = PORT_E_BASE + 3U,
    PORT_PE4 = PORT_E_BASE + 4U,
    PORT_PE5 = PORT_E_BASE + 5U,
    PORT_PE6 = PORT_E_BASE + 6U,
    PORT_PE7 = PORT_E_BASE + 7U,
    PORT_PF0 = PORT_F_BASE,
    PORT_PF1 = PORT_F_BASE + 1U,
    PORT_PF2 = PORT_F_BASE + 2U,
    PORT_PF3 = PORT_F_BASE + 3U,
    PORT_PF4 = PORT_F_BASE + 4U,
    PORT_PF5 = PORT_F_BASE + 5U,
    PORT_PF6 = PORT_F_BASE + 6U,
    PORT_PF7 = PORT_F_BASE + 7U,
    PORT_PH0 = PORT_H_BASE,
    PORT_PH1 = PORT_H_BASE + 1U,
    PORT_PH2 = PORT_H_BASE + 2U,
    PORT_PH3 = PORT_H_BASE + 3U,
    PORT_PH4 = PORT_H_BASE + 4U,
    PORT_PH5 = PORT_H_BASE + 5U,
    PORT_PH6 = PORT_H_BASE + 6U,
    PORT_PH7 = PORT_H_BASE + 7U,
    PORT_PJ0 = PORT_J_BASE,
    PORT_PJ1 = PORT_J_BASE + 1U,
    PORT_PJ2 = PORT_J_BASE + 2U,
    PORT_PJ3 = PORT_J_BASE + 3U,
    PORT_PJ4 = PORT_J_BASE + 4U,
    PORT_PJ5 = PORT_J_BASE + 5U,
    PORT_PJ6 = PORT_J_BASE + 6U,
    PORT_PJ7 = PORT_J_BASE + 7U,
    PORT_PK0 = PORT_K_BASE,
    PORT_PK1 = PORT_K_BASE + 1U,
    PORT_PK2 = PORT_K_BASE + 2U,
    PORT_PK3 = PORT_K_BASE + 3U,
    PORT_PK4 = PORT_K_BASE + 4U,
    PORT_PK5 = PORT_K_BASE + 5U,
    PORT_PK6 = PORT_K_BASE + 6U,
    PORT_PK7 = PORT_K_BASE + 7U,
    PORT_PL0 = PORT_L_BASE,
    PORT_PL1 = PORT_L_BASE + 1U,
    PORT_PL2 = PORT_L_BASE + 2U,
    PORT_PL3 = PORT_L_BASE + 3U,
    PORT_PL4 = PORT_L_BASE + 4U,
    PORT_PL5 = PORT_L_BASE + 5U,
    PORT_PL6 = PORT_L_BASE + 6U,
    PORT_PL7 = PORT_L_BASE + 7U,
    PORT_PM0 = PORT_M_BASE,
    PORT_PM1 = PORT_M_BASE + 1U,
    PORT_PM2 = PORT_M_BASE + 2U,
    PORT_PM3 = PORT_M_BASE + 3U,
    PORT_PM4 = PORT_M_BASE + 4U,
    PORT_PM5 = PORT_M_BASE + 5U,
    PORT_PM6 = PORT_M_BASE + 6U,
    PORT_PM7 = PORT_M_BASE + 7U,
    PORT_PP0 = PORT_P_BASE,
    PORT_PP1 = PORT_P_BASE + 1U,
    PORT_PP2 = PORT_P_BASE + 2U,
    PORT_PP3 = PORT_P_BASE + 3U,
    PORT_PP4 = PORT_P_BASE + 4U,
    PORT_PP5 = PORT_P_BASE + 5U,
    PORT_PP6 = PORT_P_BASE + 6U,
    PORT_PP7 = PORT_P_BASE + 7U,
    PORT_PR0 = PORT_R_BASE,
    PORT_PR1 = PORT_R_BASE + 1U,
    PORT_PR2 = PORT_R_BASE + 2U,
    PORT_PR3 = PORT_R_BASE + 3U,
    PORT_PR4 = PORT_R_BASE + 4U,
    PORT_PR5 = PORT_R_BASE + 5U,
    PORT_PR6 = PORT_R_BASE + 6U,
    PORT_PR7 = PORT_R_BASE + 7U,
    PORT_PS0 = PORT_S_BASE,
    PORT_PS1 = PORT_S_BASE + 1U,
    PORT_PS2 = PORT_S_BASE + 2U,
    PORT_PS3 = PORT_S_BASE + 3U,
    PORT_PS4 = PORT_S_BASE + 4U,
    PORT_PS5 = PORT_S_BASE + 5U,
    PORT_PS6 = PORT_S_BASE + 6U,
    PORT_PS7 = PORT_S_BASE + 7U,
    PORT_PT0 = PORT_T_BASE,
    PORT_PT1 = PORT_T_BASE + 1U,
    PORT_PT2 = PORT_T_BASE + 2U,
    PORT_PT3 = PORT_T_BASE + 3U,
    PORT_PT4 = PORT_T_BASE + 4U,
    PORT_PT5 = PORT_T_BASE + 5U,
    PORT_PT6 = PORT_T_BASE + 6U,
    PORT_PT7 = PORT_T_BASE + 7U,
    PORT_AN_08_15_0 = PORT_AN_08_15_BASE,
    PORT_AN_08_15_1 = PORT_AN_08_15_BASE + 1U,
    PORT_AN_08_15_2 = PORT_AN_08_15_BASE + 2U,
    PORT_AN_08_15_3 = PORT_AN_08_15_BASE + 3U,
    PORT_AN_08_15_4 = PORT_AN_08_15_BASE + 4U,
    PORT_AN_08_15_5 = PORT_AN_08_15_BASE + 5U,
    PORT_AN_08_15_6 = PORT_AN_08_15_BASE + 6U,
    PORT_AN_08_15_7 = PORT_AN_08_15_BASE + 7U,
    PORT_AN_00_07_0 = PORT_AN_00_07_BASE,
    PORT_AN_00_07_1 = PORT_AN_00_07_BASE + 1U,
    PORT_AN_00_07_2 = PORT_AN_00_07_BASE + 2U,
    PORT_AN_00_07_3 = PORT_AN_00_07_BASE + 3U,
    PORT_AN_00_07_4 = PORT_AN_00_07_BASE + 4U,
    PORT_AN_00_07_5 = PORT_AN_00_07_BASE + 5U,
    PORT_AN_00_07_6 = PORT_AN_00_07_BASE + 6U,
    PORT_AN_00_07_7 = PORT_AN_00_07_BASE + 7U,
    PORT_AN_24_31_0 = PORT_AN_24_31_BASE,
    PORT_AN_24_31_1 = PORT_AN_24_31_BASE + 1U,
    PORT_AN_24_31_2 = PORT_AN_24_31_BASE + 2U,
    PORT_AN_24_31_3 = PORT_AN_24_31_BASE + 3U,
    PORT_AN_24_31_4 = PORT_AN_24_31_BASE + 4U,
    PORT_AN_24_31_5 = PORT_AN_24_31_BASE + 5U,
    PORT_AN_24_31_6 = PORT_AN_24_31_BASE + 6U,
    PORT_AN_24_31_7 = PORT_AN_24_31_BASE + 7U,
    PORT_AN_16_23_0 = PORT_AN_16_23_BASE,
    PORT_AN_16_23_1 = PORT_AN_16_23_BASE + 1U,
    PORT_AN_16_23_2 = PORT_AN_16_23_BASE + 2U,
    PORT_AN_16_23_3 = PORT_AN_16_23_BASE + 3U,
    PORT_AN_16_23_4 = PORT_AN_16_23_BASE + 4U,
    PORT_AN_16_23_5 = PORT_AN_16_23_BASE + 5U,
    PORT_AN_16_23_6 = PORT_AN_16_23_BASE + 6U,
    PORT_AN_16_23_7 = PORT_AN_16_23_BASE + 7U,
} Port_PinType;



typedef struct {
    const uint8 corePullUpRegister; // PUCR
    const uint8 coreReducedDriveRegister; // RDRIV
    const uint8 modeRoutingRegister; // MODRR
    const uint8 eclkControlRegister; // ECLKCTL
    const uint8 irqControlRegister; // IRQCR

    /**
     * Every port has:
     *  a direction (input or output)
     *  a default out value
     *  a mask that is 0 if the direction is allowed to change during runtime
     *
     * Some ports have:
     *  a reduced drive conf (power saving)
     *  a pull enable conf (enable pull-up/pull-down
     *  a pull direction conf (pull-up or pull-down)
     *  a wired mode (enable open drain outputs)
     */
#if ( PORTA_CONFIGURABLE == STD_ON )
    const uint8 portADirection;
    const uint8 portAOutValue;
    const uint8 portAMask;
#endif

#if ( PORTB_CONFIGURABLE == STD_ON )
    const uint8 portBDirection;
    const uint8 portBOutValue;
    const uint8 portBMask;
#endif

#if ( PORTC_CONFIGURABLE == STD_ON )
    const uint8 portCDirection;
    const uint8 portCOutValue;
    const uint8 portCMask;
#endif

#if ( PORTD_CONFIGURABLE == STD_ON )
    const uint8 portDDirection;
    const uint8 portDOutValue;
    const uint8 portDMask;
#endif

#if ( PORTE_CONFIGURABLE == STD_ON )
    const uint8 portEDirection;
    const uint8 portEOutValue;
    const uint8 portEMask;
#endif

#if ( PORTF_CONFIGURABLE == STD_ON )
    const uint8 portFDirection;
    const uint8 portFOutValue;
    const uint8 portFMask;
    const uint8 portFPullEnableRegister;
    const uint8 portFPullPolarityRegsiter;
    const uint8 portFReducedDriveRegister;
    const uint8 portFRoutingRegister;
#endif


#if ( PORTH_CONFIGURABLE == STD_ON )
    const uint8 portHDirection;
    const uint8 portHOutValue;
    const uint8 portHMask;
    const uint8 portHPullEnableRegister;
    const uint8 portHPullPolarityRegsiter;
    const uint8 portHReducedDriveRegister;
#endif

#if ( PORTJ_CONFIGURABLE == STD_ON )
    const uint8 portJDirection;
    const uint8 portJOutValue;
    const uint8 portJMask;
    const uint8 portJPullEnableRegister;
    const uint8 portJPullPolarityRegsiter;
    const uint8 portJReducedDriveRegister;
#endif

#if ( PORTK_CONFIGURABLE == STD_ON )
    const uint8 portKDirection;
    const uint8 portKOutValue;
    const uint8 portKMask;
#endif

#if ( PORTL_CONFIGURABLE == STD_ON )
    const uint8 portLDirection;
    const uint8 portLOutValue;
    const uint8 portLMask;
    const uint8 portLPullEnableRegister;
    const uint8 portLPullPolarityRegsiter;
    const uint8 portLWiredModeRegsiter;
    const uint8 portLReducedDriveRegister;
    const uint8 portLRoutingRegister;
#endif

#if ( PORTM_CONFIGURABLE == STD_ON )
    const uint8 portMDirection;
    const uint8 portMOutValue;
    const uint8 portMMask;
    const uint8 portMPullEnableRegister;
    const uint8 portMPullPolarityRegsiter;
    const uint8 portMWiredModeRegsiter;
    const uint8 portMReducedDriveRegister;
#endif

#if ( PORTP_CONFIGURABLE == STD_ON )
    const uint8 portPDirection;
    const uint8 portPOutValue;
    const uint8 portPMask;
    const uint8 portPPullEnableRegister;
    const uint8 portPPullPolarityRegsiter;
    const uint8 portPReducedDriveRegister;
#endif

#if ( PORTR_CONFIGURABLE == STD_ON )
    const uint8 portRDirection;
    const uint8 portROutValue;
    const uint8 portRMask;
    const uint8 portRPullEnableRegister;
    const uint8 portRPullPolarityRegsiter;
    const uint8 portRReducedDriveRegister;
    const uint8 portRRoutingRegister;
#endif

#if ( PORTS_CONFIGURABLE == STD_ON )
    const uint8 portSDirection;
    const uint8 portSOutValue;
    const uint8 portSMask;
    const uint8 portSPullEnableRegister;
    const uint8 portSPullPolarityRegsiter;
    const uint8 portSWiredModeRegsiter;
    const uint8 portSReducedDriveRegister;
#endif

#if ( PORTT_CONFIGURABLE == STD_ON )
    const uint8 portTDirection;
    const uint8 portTOutValue;
    const uint8 portTMask;
    const uint8 portTPullEnableRegister;
    const uint8 portTPullPolarityRegsiter;
    const uint8 portTReducedDriveRegister;
#endif

#if ( PORT_AN00_07_CONFIGURABLE == STD_ON )
    const uint8 portAN00_07Direction;
    const uint8 portAN00_07OutValue;
    const uint8 portAN00_07Mask;
    const uint8 portAN00_07PullUpEnableRegister;
    const uint8 portAN00_07ReducedDriveRegister;
    const uint8 portAN00_07DigitalInputEnable;
#endif

#if ( PORT_AN08_15_CONFIGURABLE == STD_ON )
    const uint8 portAN08_15Direction;
    const uint8 portAN08_15OutValue;
    const uint8 portAN08_15Mask;
    const uint8 portAN08_15PullUpEnableRegister;
    const uint8 portAN08_15ReducedDriveRegister;
    const uint8 portAN08_15DigitalInputEnable;
#endif

#if ( PORT_AN16_23_CONFIGURABLE == STD_ON )
    const uint8 portAN16_23Direction;
    const uint8 portAN16_23OutValue;
    const uint8 portAN16_23Mask;
    const uint8 portAN16_23PullUpEnableRegister;
    const uint8 portAN16_23ReducedDriveRegister;
    const uint8 portAN16_23DigitalInputEnable;
#endif

#if ( PORT_AN24_31_CONFIGURABLE == STD_ON )
    const uint8 portAN24_31Direction;
    const uint8 portAN24_31OutValue;
    const uint8 portAN24_31Mask;
    const uint8 portAN24_31PullUpEnableRegister;
    const uint8 portAN24_31ReducedDriveRegister;
    const uint8 portAN24_31DigitalInputEnable;
#endif
} Port_ConfigType;


extern const Port_ConfigType PortConfigData;

#endif
