/**
 * \addtogroup autosar
 * \{
 * \addtogroup PWM PWM驱动
 * \{
 */

#ifndef PWM_H_
#define PWM_H_


#include "Std_Types.h"
#include "Pwm_Types.h"

typedef uint8 Pwm_ErrorType;

typedef uint16 Pwm_DutyCycleType;

#define PWM_PERCENT_100    0x8000
#define PWM_PERCENT_0      0


typedef enum {
	PWM_LOW,
	PWM_HIGH
} Pwm_OutputStateType;

typedef enum {
	PWM_FALLING_EDGE = PWM_LOW,
	PWM_RISING_EDGE =  PWM_HIGH,
	PWM_BOTH_EDGES = PWM_RISING_EDGE + 1
} Pwm_EdgeNotificationType;

#define PWM_NO_EDGES (PWM_BOTH_EDGES + 1)

typedef enum {
	PWM_VARIABLE_PERIOD,
	PWM_FIXED_PERIOD,
	PWM_FIXED_PERIOD_SHIFTED
} Pwm_ChannelClassType;

typedef void (*Pwm_NotificationHandlerType)();

#include "Pwm_Cfg.h"

extern const Pwm_ConfigType PwmConfig;

void Pwm_Init(const Pwm_ConfigType* ConfigPtr);
void Pwm_DeInit();
void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, Pwm_DutyCycleType DutyCycle);
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, Pwm_DutyCycleType DutyCycle);
void Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber);
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType ChannelNumber);
void Pwm_DisableNotification(Pwm_ChannelType ChannelNumber);
void Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification);

#endif /* PWM_H_ */

/**
 * \}
 * \}
 */
