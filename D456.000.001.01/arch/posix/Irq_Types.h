#ifndef IRQ_TYPES_H
#define IRQ_TYPES_H

typedef void (*Irq_HandlerFunc)(void);

typedef enum {
    IRQ_SURIOUS_INTERRUPT,
    IRQ_SYSTEM_CALL,
    IRQ_MPU_ACCESS_ERROR,
    IRQ_XGATE_SOFT_ERROR,
    IRQ_RES18,
    IRQ_RES1A,
    IRQ_RES1C,
    IRQ_RES1E,
    IRQ_RES20,
    IRQ_RES22,
    IRQ_RES24,
    IRQ_RES26,
    IRQ_RES28,
    IRQ_RES2A,
    IRQ_RES2C,
    IRQ_RES2E,
    IRQ_RES30,
    IRQ_RES32,
    IRQ_RES34,
    IRQ_RES36,
    IRQ_RES38,
    IRQ_RES3A,
    IRQ_ATD1_COMPARE,
    IRQ_ATD0_COMPARE,
    IRQ_TIM_ACC_A_OVERFLOW,
    IRQ_TIM_ACC_INPUT_EDGE,
    IRQ_TIM_OVERFLOW,
    IRQ_TIM_CHANNEL_7,
    IRQ_TIM_CHANNEL_6,
    IRQ_TIM_CHANNEL_5,
    IRQ_TIM_CHANNEL_4,
    IRQ_TIM_CHANNEL_3,
    IRQ_TIM_CHANNEL_2,
    IRQ_TIM_CHANNEL_1,
    IRQ_TIM_CHANNEL_0,
    IRQ_SCI7,
    IRQ_PIT7,
    IRQ_PIT6,
    IRQ_PIT5,
    IRQ_PIT4,
    IRQ_RES60,
    IRQ_RES62,
    IRQ_XGATE_SOFTWARE_TRIGGER_7,
    IRQ_XGATE_SOFTWARE_TRIGGER_6,
    IRQ_XGATE_SOFTWARE_TRIGGER_5,
    IRQ_XGATE_SOFTWARE_TRIGGER_4,
    IRQ_XGATE_SOFTWARE_TRIGGER_3,
    IRQ_XGATE_SOFTWARE_TRIGGER_2,
    IRQ_XGATE_SOFTWARE_TRIGGER_1,
    IRQ_XGATE_SOFTWARE_TRIGGER_0,
    IRQ_PIT3,
    IRQ_PIT2,
    IRQ_PIT1,
    IRQ_PIT0,
    IRQ_HIGH_TEMPRATURE,
    IRQ_API,
    IRQ_LVI,
    IRQ_IIC1,
    IRQ_SCI5,
    IRQ_SCI4,
    IRQ_SCI3,
    IRQ_SCI2,
    IRQ_PWM_SHUTDOWN,
    IRQ_PORTP,
    IRQ_CAN4_TX,
    IRQ_CAN4_RX,
    IRQ_CAN4_ERR,
    IRQ_CAN4_WAKE,
    IRQ_CAN3_TX,
    IRQ_CAN3_RX,
    IRQ_CAN3_ERR,
    IRQ_CAN3_WAKE,
    IRQ_CAN2_TX,
    IRQ_CAN2_RX,
    IRQ_CAN2_ERR,
    IRQ_CAN2_WAKE,
    IRQ_CAN1_TX,
    IRQ_CAN1_RX,
    IRQ_CAN1_ERR,
    IRQ_CAN1_WAKE,
    IRQ_CAN0_TX,
    IRQ_CAN0_RX,
    IRQ_CAN0_ERR,
    IRQ_CAN0_WAKE,
    IRQ_FLASH,
    IRQ_FLASH_FAULT,
    IRQ_SPI2,
    IRQ_SPI1,
    IRQ_IIC0,
    IRQ_SCI6,
    IRQ_CRG_SELF_CLOCK_MODE,
    IRQ_CRG_PLL_LOCK,
    IRQ_PULSE_ACC_B_OVERFLOW,
    IRQ_MODULUS_COUNTER_OVERFLOW,
    IRQ_PORTH,
    IRQ_PORTJ,
    IRQ_ATD1,
    IRQ_ATD0,
    IRQ_SCI1,
    IRQ_SCI0,
    IRQ_SPI0,
    IRQ_PULUS_ACC_INPUT_EDGE,
    IRQ_PULSE_ACC_A_OVERFLOW,
    IRQ_STANDARD_TIM_OVERFLOW,
    IRQ_STANDARD_TIM_7,
    IRQ_STANDARD_TIM_6,
    IRQ_STANDARD_TIM_5,
    IRQ_STANDARD_TIM_4,
    IRQ_STANDARD_TIM_3,
    IRQ_STANDARD_TIM_2,
    IRQ_STANDARD_TIM_1,
    IRQ_STANDARD_TIM_0,
    IRQ_RTI,
    IRQ_IRQ,
    IRQ_XIRQ,
    IRQ_SWI,
    IRQ_UNIMPLEMENTED_INSTRUCTUION,
    IRQ_COP,
    IRQ_CLOCK_MONITOR_FAIL,
    IRQ_RESET,
    IRQ_TOTAL_NUM,
} Irq_Type;

#endif
