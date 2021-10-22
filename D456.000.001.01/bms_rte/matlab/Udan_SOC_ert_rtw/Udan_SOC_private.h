/*lint -e* -w0*/
/*
 *
 * File: Udan_SOC_private.h
 *
 * Code generated for Simulink model 'Udan_SOC'.
 *
 * Model version                  : 1.674
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Fri Apr 17 14:01:18 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Udan_SOC_private_h_
#define RTW_HEADER_Udan_SOC_private_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "Udan_SOC.h"

/* Includes for objects with custom storage classes. */
#include "SocOcvCalib.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFU) ) || ( INT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFL) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Imported (extern) block signals */
extern int16_T SOC_Current100mA;       /* '<Root>/SOC_Current100mA' */
extern uint32_T SOC_Timestampms;       /* '<Root>/SOC_Timestampms' */
extern uint8_T SocCalibFlag;           /* '<Root>/SocCalibFlag' */
extern uint32_T Udan_SOC_BitRotate(uint32_T rtu_u);
extern void Udan_SOC_Subsystem(boolean_T rtu_Enable, uint16_T rtu_HighIndex,
  uint16_T rtu_LowIndex, uint32_T *rty_soc);
extern void Udan_SOC_MATLABFunction(uint8_T rty_y[18]);
extern void Udan_SOC_BitRotate_o(uint32_T rtu_u, uint32_T *rty_y);
extern void Udan_SOC_FunctionCallSubsystem4(uint8_T rtu_CellLowTemp, uint8_T
  rtu_SocCalibFlag, uint16_T rtu_UCell, uint32_T *rty_EEEPLeftCap, uint16_T
  *rty_EEEPSOH, uint32_T *rty_EEEPDLeftCap, B_FunctionCallSubsystem4_Udan_T
  *localB);
extern void Udan_SOC_Chart1_Init(uint8_T *rty_SOHWriteResult, uint16_T
  *rty_SohOut);
extern void Udan_SOC_Chart1(uint32_T rtu_CalcSOH, uint8_T rtu_MaxDiff, uint8_T
  rtu_MaxCal, uint8_T rtu_MaxCal1, uint16_T rtu_EEEPSOH, uint8_T
  *rty_SOHWriteResult, uint16_T *rty_SohOut);
extern void Udan_SOC_LKTSOC_Init(B_LKTSOC_Udan_SOC_T *localB);
extern void Udan_SOC_LKTSOC(uint8_T rtu_CellLowTemp, uint16_T rtu_UCell,
  uint16_T rtu_SOH, uint32_T rtu_Capacity, uint32_T rtu_DCapacity, SOC_State
  rtu_Soc_State, uint32_T *rty_LeftCap, uint32_T *rty_DLeftCap, uint16_T
  *rty_SohOut, uint32_T *rty_LookUpLeftCap, B_LKTSOC_Udan_SOC_T *localB);
extern void Udan_SOC_CapAdder1_Init(DW_CapAdder1_Udan_SOC_T *localDW);
extern void Udan_SOC_CapAdder1(uint32_T rtu_Capacity, int32_T rtu_AmpereMicrosec,
  int16_T rtu_Current100mA, uint8_T rtu_CellLowTemp, uint16_T rtu_UCell,
  uint16_T rtu_SOH, uint8_T rtu_IsCharging, int32_T rtu_LeftCapAusIn, uint8_T
  rtu_SocCalibFlag, uint32_T *rty_NewCap, int32_T *rty_LeftCapAusOut, uint32_T
  *rty_CulumChargeAh, uint32_T *rty_CulumDchargeAh, B_CapAdder1_Udan_SOC_T
  *localB, DW_CapAdder1_Udan_SOC_T *localDW, ZCE_CapAdder1_Udan_SOC_T *localZCE);
extern void Udan_SOC_WriteOCVTime(uint32_T rtu_RTCTimeOut, SOC_State rtu_OCVCmd,
  uint32_T rtu_RtcTime, uint32_T *rty_SOC_RTCTime, boolean_T
  *rtd_LargeCurrentFlag);
extern uint32_T Udan_SOC_BitRotate_a(uint32_T rtu_u);
extern void Udan_SOC_EnabledSubsystem(boolean_T rtu_Enable,
  ParameterM_EeepParaIndexType rtu_index, uint16_T rtu_data, uint8_T
  *rty_EeepWriteFailure);
extern void Udan_SOC_EnabledSubsystem4(boolean_T rtu_Enable,
  ParameterM_EeepParaIndexType rtu_index, uint16_T rtu_data, boolean_T
  *rty_EeepWriteFailure);
extern void SOC_Calculate_Init(void);
extern void SOC_Calculate(void);

/* Exported data declaration */

/* Const memory section */
/* Declaration for custom storage class: ImportFromFile */
extern const Soc_ConfigInfoType Soc_ConfigInfo;

#endif                                 /* RTW_HEADER_Udan_SOC_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
