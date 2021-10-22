#ifndef USER_CURRENT_SENSOR_H__
#define USER_CURRENT_SENSOR_H__

void UserCurrentSensor_Init(Async_LooperType *looper);

Std_ReturnType UserCurrentSensor1_WaitCurrentCalibrated(Current_TimedCurrentType *current, uint16 timeout);
Current_CurrentType UserCurrentSensor1_GetCurrent(void);
Std_ReturnType UserCurrentSensor2_WaitCurrentCalibrated(Current_TimedCurrentType *current, uint16 timeout);
Current_CurrentType UserCurrentSensor2_GetCurrent(void);

#endif