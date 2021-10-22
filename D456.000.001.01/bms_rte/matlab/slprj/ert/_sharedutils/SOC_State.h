/*lint -e* -w0*/
/*
 *
 * File: SOC_State.h
 *
 * Code generated for Simulink model 'Udan_SOC'.
 *
 * Model version                  : 1.643
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Wed Jul 24 14:36:40 2019
 */

#ifndef RTW_HEADER_SOC_State_h_
#define RTW_HEADER_SOC_State_h_
#include "rtwtypes.h"

typedef enum {
  SOC_STATE_INIT = 0,                  /* Default value */
  SOC_STATE_OCV,
  SOC_STATE_OCV_LONG,
  SOC_STATE_SOH,
  SOC_STATE_INTEGRATE,
  SOC_STATE_FULL,
  SOC_STATE_EMPTY,
  SOC_STATE_DCHGSOH
} SOC_State;

#endif                                 /* RTW_HEADER_SOC_State_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
