/*lint -e* -w0*/
/*
 *
 * File: Udan_SOC.h
 *
 * Code generated for Simulink model 'Udan_SOC'.
 *
 * Model version                  : 1.679
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Fri Oct 23 13:53:05 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Udan_SOC_h_
#define RTW_HEADER_Udan_SOC_h_
#include <stddef.h>
#include <string.h>
#ifndef Udan_SOC_COMMON_INCLUDES_
# define Udan_SOC_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "ParameterM.h"
#include "Statistic.h"
#include "Soc.h"
#include "DatetimeM.h"
#include "SocDiagCalib.h"
#include "ChargeConnectM.h"
#endif                                 /* Udan_SOC_COMMON_INCLUDES_ */

#include "Udan_SOC_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* user code (top of header file) */
/*lint -e* -w0 */

/* Block signals for system '<S12>/Function-Call Subsystem4' */
typedef struct {
  int32_T Switch;                      /* '<S160>/Switch' */
  uint32_T Switch_j;                   /* '<S173>/Switch' */
  uint32_T soc;                        /* '<S176>/Add' */
  uint32_T soc_b;                      /* '<S172>/Add' */
  uint16_T Switch_l;                   /* '<S161>/Switch' */
} B_FunctionCallSubsystem4_Udan_T;

/* Block signals for system '<S12>/LKTSOC' */
typedef struct {
  uint32_T soc;                        /* '<S211>/Add' */
  uint16_T SohOut;                     /* '<S206>/Chart1' */
} B_LKTSOC_Udan_SOC_T;

/* Block signals for system '<S12>/CapAdder1' */
typedef struct {
  uint32_T LeftCapIn;                  /* '<S114>/LeftCapIn' */
  uint32_T Switch;                     /* '<S113>/Switch' */
  uint32_T Switch_g;                   /* '<S126>/Switch' */
  uint32_T Switch2;                    /* '<S132>/Switch2' */
  uint16_T soc;                        /* '<S126>/Lookup Table Dynamic1' */
} B_CapAdder1_Udan_SOC_T;

/* Block states (auto storage) for system '<S12>/CapAdder1' */
typedef struct {
  uint32_T Delay_DSTATE;               /* '<S117>/Delay' */
  uint32_T Delay1_DSTATE;              /* '<S117>/Delay1' */
  uint32_T Delay2_DSTATE;              /* '<S117>/Delay2' */
  uint32_T Delay3_DSTATE;              /* '<S117>/Delay3' */
  uint16_T ticks;                      /* '<S113>/Chart' */
  uint16_T ticks_b;                    /* '<S113>/Chart' */
  uint8_T is_active_c34_Udan_SOC;      /* '<S113>/Chart' */
  uint8_T is_c34_Udan_SOC;             /* '<S113>/Chart' */
  boolean_T TimerOut;                  /* '<S113>/Chart' */
  boolean_T Init;                      /* '<S113>/Chart' */
  boolean_T Init_m;                    /* '<S113>/Chart' */
} DW_CapAdder1_Udan_SOC_T;

/* Zero-crossing (trigger) state for system '<S12>/CapAdder1' */
typedef struct {
  ZCSigState FunctionCallSubsystem_Trig_ZC_p;/* '<S25>/Function-Call Subsystem' */
} ZCE_CapAdder1_Udan_SOC_T;

/* Block signals (auto storage) */
typedef struct {
  int32_T AuS;                         /* '<S26>/Math Function' */
  int32_T AuS_o;                       /* '<S25>/Math Function' */
  uint32_T SFunction5_o2;              /* '<S1>/S-Function5' */
  uint32_T soc;                        /* '<S287>/Add' */
  uint32_T soc_d;                      /* '<S253>/Add' */
  uint32_T soc_f;                      /* '<S241>/Add' */
  uint32_T RtcTimeIn;                  /* '<S33>/RtcTimeIn' */
  uint32_T AmS;                        /* '<S26>/Switch2' */
  uint32_T DLeftCapIn;                 /* '<S146>/DLeftCapIn' */
  uint32_T AmS_b;                      /* '<S16>/Divide1' */
  uint32_T Divide2;                    /* '<S16>/Divide2' */
  uint32_T soc_k;                      /* '<S65>/Add' */
  uint32_T Divide;                     /* '<S17>/Divide' */
  uint32_T Divide2_a;                  /* '<S17>/Divide2' */
  uint32_T soc_kh;                     /* '<S76>/Add' */
  uint32_T Divide3;                    /* '<S99>/Divide3' */
  uint32_T AmS_g;                      /* '<S23>/Divide1' */
  uint32_T Divide2_m;                  /* '<S24>/Divide2' */
  uint32_T AmS_m;                      /* '<S24>/MinMax' */
  uint32_T Switch1;                    /* '<S25>/Switch1' */
  uint32_T Switch2;                    /* '<S47>/Switch2' */
  uint32_T Switch5;                    /* '<S47>/Switch5' */
  uint32_T AmS_h;                      /* '<S45>/Divide7' */
  uint32_T AmS_i;                      /* '<S45>/Switch4' */
  uint32_T soc_m;                      /* '<S13>/Add' */
  SOC_State SOC_State_d;               /* '<S12>/CalclnCore' */
  uint16_T GetEmptyCalibFunc;          /* '<S1>/GetEmptyCalibFunc' */
  uint16_T SFunction4;                 /* '<S1>/S-Function4' */
  uint16_T Switch;                     /* '<S16>/Switch' */
  uint16_T SohOut;                     /* '<S61>/Chart2' */
  uint16_T DCHSOHOUt;                  /* '<S17>/Switch' */
  uint16_T SohOut_b;                   /* '<S71>/Chart1' */
  uint16_T Switch1_b;                  /* '<S47>/Switch1' */
  uint16_T Switch1_e;                  /* '<S45>/Switch1' */
  uint16_T Switch2_p;                  /* '<S79>/Switch2' */
  uint8_T SFunction3;                  /* '<S1>/S-Function3' */
  uint8_T SFunction;                   /* '<S1>/S-Function' */
  uint8_T SFunction_b;                 /* '<S300>/S-Function' */
  uint8_T SFunction_o;                 /* '<S299>/S-Function' */
  uint8_T SFunction_j;                 /* '<S298>/S-Function' */
  boolean_T LogicalOperator;           /* '<S305>/Logical Operator' */
  boolean_T LogicalOperator_k;         /* '<S304>/Logical Operator' */
  boolean_T LogicalOperator_g;         /* '<S303>/Logical Operator' */
  boolean_T LogicalOperator_h;         /* '<S302>/Logical Operator' */
  boolean_T LogicalOperator_c;         /* '<S10>/Logical Operator' */
  boolean_T LogicalOperator5;          /* '<S10>/Logical Operator5' */
  boolean_T LogicalOperator8;          /* '<S10>/Logical Operator8' */
  B_CapAdder1_Udan_SOC_T CapAdder1;    /* '<S12>/CapAdder1' */
  B_LKTSOC_Udan_SOC_T LKTSOC;          /* '<S12>/LKTSOC' */
  B_FunctionCallSubsystem4_Udan_T FunctionCallSubsystem4;/* '<S12>/Function-Call Subsystem4' */
} B_Udan_SOC_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  int32_T Delay5_DSTATE;               /* '<S12>/Delay5' */
  int32_T Delay7_DSTATE;               /* '<S12>/Delay7' */
  uint32_T Delay1_DSTATE;              /* '<S12>/Delay1' */
  uint32_T Delay8_DSTATE;              /* '<S12>/Delay8' */
  uint32_T Delay9_DSTATE;              /* '<S12>/Delay9' */
  uint32_T Delay1_DSTATE_o;            /* '<S52>/Delay1' */
  uint32_T Delay1_DSTATE_f;            /* '<S53>/Delay1' */
  uint32_T Delay1_DSTATE_e;            /* '<S55>/Delay1' */
  uint32_T Delay1_DSTATE_h;            /* '<S265>/Delay1' */
  uint32_T Delay1_DSTATE_em;           /* '<S264>/Delay1' */
  uint32_T Delay_DSTATE_p;             /* '<S51>/Delay' */
  uint32_T Delay1_DSTATE_ow;           /* '<S51>/Delay1' */
  uint32_T OcvCalibTime;               /* '<S12>/CalclnCore' */
  boolean_T Delay10_DSTATE;            /* '<S12>/Delay10' */
  boolean_T Delay11_DSTATE;            /* '<S12>/Delay11' */
  boolean_T Delay6_DSTATE;             /* '<S12>/Delay6' */
  boolean_T Delay4_DSTATE[2];          /* '<S12>/Delay4' */
  boolean_T Delay1_DSTATE_c;           /* '<S10>/Delay1' */
  boolean_T Delay10_DSTATE_a;          /* '<S10>/Delay10' */
  uint8_T is_active_c19_Udan_SOC;      /* '<S12>/CalclnCore' */
  uint8_T is_c19_Udan_SOC;             /* '<S12>/CalclnCore' */
  boolean_T LargeCurrentFlag;          /* '<S12>/Data Store Memory1' */
  boolean_T FullFnshFlag;              /* '<S12>/Data Store Memory2' */
  boolean_T ChgClearWOCalibFlag;       /* '<S12>/Data Store Memory4' */
  boolean_T SohCond;                   /* '<S12>/CalclnCore' */
  DW_CapAdder1_Udan_SOC_T CapAdder1;   /* '<S12>/CapAdder1' */
} DW_Udan_SOC_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState SetSOHCalcFlagFullChg_Trig_ZCE;/* '<S12>/SetSOHCalcFlagFullChg' */
  ZCSigState SetSOHCalcFlag_Trig_ZCE;  /* '<S12>/SetSOHCalcFlag' */
  ZCSigState FunctionCallSubsystem_Trig_ZCE;/* '<S12>/Function-Call Subsystem' */
  ZCSigState FunctionCallSubsystem_Trig_ZC_i;/* '<S26>/Function-Call Subsystem' */
  ZCE_CapAdder1_Udan_SOC_T CapAdder1;  /* '<S12>/CapAdder1' */
} PrevZCX_Udan_SOC_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint16_T DataTypeConversion1;  /* '<S223>/Data Type Conversion1' */
  const uint16_T DataTypeConversion1_b;/* '<S217>/Data Type Conversion1' */
  const uint16_T DataTypeConversion1_g;/* '<S157>/Data Type Conversion1' */
  const uint16_T DataTypeConversion1_p;/* '<S151>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_i; /* '<S12>/Data Type Conversion1' */
} ConstB_Udan_SOC_T;

/* Real-time Model Data Structure */
struct tag_RTM_Udan_SOC_T {
  const char_T *errorStatus;
};

/* Block signals (auto storage) */
extern B_Udan_SOC_T Udan_SOC_B;

/* Block states (auto storage) */
extern DW_Udan_SOC_T Udan_SOC_DW;

/* External data declarations for dependent source files */
extern const SOX_SocType Udan_SOC_rtZSOX_SocType;/* SOX_SocType ground */
extern const ConstB_Udan_SOC_T Udan_SOC_ConstB;/* constant block i/o */

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint8_T SOC_OcvCalibCmd;        /* '<Root>/SOC_OcvCalibCmd' */
extern SOX_SocType SOC_DResult;        /* '<S22>/Signal Conversion6' */
extern SOX_SocType SOC_Result;         /* '<S21>/Signal Conversion6' */
extern uint32_T SOC_DLeftCap;          /* '<S12>/DLeftCap' */
extern uint32_T SOC_LeftCap;           /* '<S12>/LeftCap' */
extern uint32_T SOC_LeftCahrgeTime;    /*  */
extern uint32_T SOC_RTCTime;           /* '<S57>/Switch8' */
extern uint32_T SOC_CulumDchargeAh;    /* '<S117>/Add4' */
extern uint32_T SOC_CulumChargeAh;     /* '<S117>/Add5' */
extern uint32_T SOC_LookUpLeftCap;     /* '<S47>/Divide14' */
extern uint16_T SOC_SohOut;            /* '<S12>/Switch3' */
extern uint16_T SOC_RealSoc;           /* '<S21>/Data Type Conversion' */
extern uint16_T SOC_LeftEnergy;        /* '<S12>/CalcnSOC' */
extern boolean_T SOC_OcvCmd;           /* '<S12>/Logical Operator10' */
extern boolean_T SOC_ClearBufferCmd;   /* '<S12>/Logical Operator7' */
extern boolean_T SOC_SocInitFns;       /* '<S12>/Relational Operator3' */

/* Model entry point functions */
extern void Udan_SOC_initialize(void);
extern void Udan_SOC_step(void);
extern void Udan_SOC_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Udan_SOC_T *const Udan_SOC_M;

/* Exported data declaration */

/* Const memory section */
/* Declaration for custom storage class: Const */
extern const uint8_T DenominatorOfIntegratorFactor;
extern const uint8_T SOC_CalcSohLKT;
extern const uint8_T SOC_CapTemp_HLimit;
extern const uint8_T SOC_CapTemp_LLimit;
extern const uint8_T SOC_DchgEndCalib;
extern const uint8_T SOC_EfficientHighLimit;
extern const uint8_T SOC_EfficientLowLimit;
extern const int32_T SOC_EmptyAus;
extern const uint8_T SOC_HighRealSoc;
extern const uint8_T SOC_LowRealSoc;
extern const uint32_T SOC_NominalCap_AmS;
extern const uint8_T SOC_OCVTemp_HLimit;
extern const uint8_T SOC_OCVTemp_LLimit;
extern const uint16_T SOC_SOCResolution;
extern const uint16_T SOC_SOHResolution;
extern const uint8_T SOC_ShortCalibDSoc;
extern const uint16_T SOC_TempCap_CapBuffer[18];
extern const uint8_T SOC_TempCap_TempBuffer[18];
extern const uint8_T SOHCalibCycle;

/* Const memory section */
/* Declaration for custom storage class: Const */
extern const uint8_T SOC_CalcSOHTempLimit;
extern const uint8_T SOC_CapPerCycle;
extern const uint16_T SOC_DSOCJumpMax;
extern const uint8_T SOC_DiffVoltMin;
extern const uint8_T SOC_EnableOcv;
extern const uint16_T SOC_LKTSohCycles[163];
extern const uint16_T SOC_LKTSohTable[163];
extern const uint16_T SOC_NominalVol;
extern const uint8_T SOC_SohCalcCapPercent;
extern const uint8_T SOC_SohCalcHighLimit;
extern const uint8_T SOC_SohCalcLowLimit;
extern const uint8_T SOC_SohCalcMidLimit;
extern const uint16_T SocOcvCalib_SocBuffer1[21];
extern const uint8_T SocOcvCalib_TempBuffer[18];
extern const uint16_T SocOcvCalib_VoltageBuffer1[378];

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S9>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S64>/Data Type Duplicate' : Unused code path elimination
 * Block '<S64>/Data Type Propagation' : Unused code path elimination
 * Block '<S75>/Data Type Duplicate' : Unused code path elimination
 * Block '<S75>/Data Type Propagation' : Unused code path elimination
 * Block '<S79>/Data Type Duplicate' : Unused code path elimination
 * Block '<S79>/Data Type Propagation' : Unused code path elimination
 * Block '<S21>/Data Type Conversion1' : Unused code path elimination
 * Block '<S93>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S94>/Data Type Duplicate' : Unused code path elimination
 * Block '<S94>/Data Type Propagation' : Unused code path elimination
 * Block '<S95>/Data Type Duplicate' : Unused code path elimination
 * Block '<S95>/Data Type Propagation' : Unused code path elimination
 * Block '<S96>/Data Type Duplicate' : Unused code path elimination
 * Block '<S96>/Data Type Propagation' : Unused code path elimination
 * Block '<S97>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S98>/Data Type Duplicate' : Unused code path elimination
 * Block '<S98>/Data Type Propagation' : Unused code path elimination
 * Block '<S23>/Constant1' : Unused code path elimination
 * Block '<S100>/Data Type Duplicate' : Unused code path elimination
 * Block '<S100>/Data Type Propagation' : Unused code path elimination
 * Block '<S23>/Divide' : Unused code path elimination
 * Block '<S23>/MinMax' : Unused code path elimination
 * Block '<S103>/Data Type Duplicate' : Unused code path elimination
 * Block '<S103>/Data Type Propagation' : Unused code path elimination
 * Block '<S25>/Constant25' : Unused code path elimination
 * Block '<S106>/Add5' : Unused code path elimination
 * Block '<S106>/Constant22' : Unused code path elimination
 * Block '<S106>/Constant26' : Unused code path elimination
 * Block '<S106>/Divide3' : Unused code path elimination
 * Block '<S106>/Divide4' : Unused code path elimination
 * Block '<S106>/Divide6' : Unused code path elimination
 * Block '<S118>/Data Type Duplicate' : Unused code path elimination
 * Block '<S118>/Data Type Propagation' : Unused code path elimination
 * Block '<S119>/Data Type Duplicate' : Unused code path elimination
 * Block '<S119>/Data Type Propagation' : Unused code path elimination
 * Block '<S120>/Data Type Duplicate' : Unused code path elimination
 * Block '<S120>/Data Type Propagation' : Unused code path elimination
 * Block '<S121>/Data Type Duplicate' : Unused code path elimination
 * Block '<S121>/Data Type Propagation' : Unused code path elimination
 * Block '<S122>/Data Type Duplicate' : Unused code path elimination
 * Block '<S122>/Data Type Propagation' : Unused code path elimination
 * Block '<S123>/Data Type Duplicate' : Unused code path elimination
 * Block '<S123>/Data Type Propagation' : Unused code path elimination
 * Block '<S124>/Data Type Duplicate' : Unused code path elimination
 * Block '<S124>/Data Type Propagation' : Unused code path elimination
 * Block '<S132>/Data Type Duplicate' : Unused code path elimination
 * Block '<S132>/Data Type Propagation' : Unused code path elimination
 * Block '<S133>/Data Type Duplicate' : Unused code path elimination
 * Block '<S133>/Data Type Propagation' : Unused code path elimination
 * Block '<S134>/Data Type Duplicate' : Unused code path elimination
 * Block '<S134>/Data Type Propagation' : Unused code path elimination
 * Block '<S116>/Data Type Duplicate' : Unused code path elimination
 * Block '<S116>/Data Type Propagation' : Unused code path elimination
 * Block '<S147>/Data Type Duplicate' : Unused code path elimination
 * Block '<S147>/Data Type Propagation' : Unused code path elimination
 * Block '<S12>/Constant13' : Unused code path elimination
 * Block '<S12>/Constant14' : Unused code path elimination
 * Block '<S35>/Constant' : Unused code path elimination
 * Block '<S37>/Constant' : Unused code path elimination
 * Block '<S45>/Constant20' : Unused code path elimination
 * Block '<S45>/Divide' : Unused code path elimination
 * Block '<S166>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S45>/Relational Operator7' : Unused code path elimination
 * Block '<S168>/Data Type Duplicate' : Unused code path elimination
 * Block '<S168>/Data Type Propagation' : Unused code path elimination
 * Block '<S46>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S196>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S200>/Data Type Duplicate' : Unused code path elimination
 * Block '<S200>/Data Type Propagation' : Unused code path elimination
 * Block '<S201>/Data Type Duplicate' : Unused code path elimination
 * Block '<S201>/Data Type Propagation' : Unused code path elimination
 * Block '<S202>/Data Type Duplicate' : Unused code path elimination
 * Block '<S202>/Data Type Propagation' : Unused code path elimination
 * Block '<S203>/Data Type Duplicate' : Unused code path elimination
 * Block '<S203>/Data Type Propagation' : Unused code path elimination
 * Block '<S204>/Data Type Duplicate' : Unused code path elimination
 * Block '<S204>/Data Type Propagation' : Unused code path elimination
 * Block '<S205>/Data Type Duplicate' : Unused code path elimination
 * Block '<S205>/Data Type Propagation' : Unused code path elimination
 * Block '<S210>/Data Type Duplicate' : Unused code path elimination
 * Block '<S210>/Data Type Propagation' : Unused code path elimination
 * Block '<S12>/Logical Operator5' : Unused code path elimination
 * Block '<S12>/Relational Operator4' : Unused code path elimination
 * Block '<S12>/Relational Operator5' : Unused code path elimination
 * Block '<S48>/Data Type Duplicate' : Unused code path elimination
 * Block '<S48>/Data Type Propagation' : Unused code path elimination
 * Block '<S261>/Logical Operator' : Unused code path elimination
 * Block '<S282>/Data Type Duplicate' : Unused code path elimination
 * Block '<S282>/Data Type Propagation' : Unused code path elimination
 * Block '<S295>/Logical Operator' : Unused code path elimination
 * Block '<S18>/Logical Operator' : Eliminated due to no operation
 * Block '<S25>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S117>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S117>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S26>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S264>/Logical Operator1' : Eliminated due to no operation
 * Block '<S265>/Logical Operator1' : Eliminated due to no operation
 * Block '<S55>/Logical Operator1' : Eliminated due to no operation
 * Block '<S58>/Data Type Conversion' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Udan_SOC'
 * '<S1>'   : 'Udan_SOC/SOC_Calculate'
 * '<S2>'   : 'Udan_SOC/SOC_Calculate/Enumerated Constant'
 * '<S3>'   : 'Udan_SOC/SOC_Calculate/Enumerated Constant1'
 * '<S4>'   : 'Udan_SOC/SOC_Calculate/Enumerated Constant2'
 * '<S5>'   : 'Udan_SOC/SOC_Calculate/Enumerated Constant3'
 * '<S6>'   : 'Udan_SOC/SOC_Calculate/Enumerated Constant4'
 * '<S7>'   : 'Udan_SOC/SOC_Calculate/Enumerated Constant5'
 * '<S8>'   : 'Udan_SOC/SOC_Calculate/Enumerated Constant6'
 * '<S9>'   : 'Udan_SOC/SOC_Calculate/Interval Test Dynamic'
 * '<S10>'  : 'Udan_SOC/SOC_Calculate/Subsystem'
 * '<S11>'  : 'Udan_SOC/SOC_Calculate/Subsystem1'
 * '<S12>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn'
 * '<S13>'  : 'Udan_SOC/SOC_Calculate/Subsystem1/Subsystem'
 * '<S14>'  : 'Udan_SOC/SOC_Calculate/Subsystem1/Subsystem/Bit Rotate'
 * '<S15>'  : 'Udan_SOC/SOC_Calculate/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S16>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH'
 * '<S17>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH'
 * '<S18>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcSocEffiient'
 * '<S19>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalclnCore'
 * '<S20>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime'
 * '<S21>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnSOC'
 * '<S22>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnSOC1'
 * '<S23>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalibEmptySOC'
 * '<S24>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalibFullSOC'
 * '<S25>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1'
 * '<S26>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder2'
 * '<S27>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearLeftCapWOCalib'
 * '<S28>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearLeftCapWOCalib2'
 * '<S29>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearSOHCalcFlag'
 * '<S30>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/DchgPower1'
 * '<S31>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/DchgPower2'
 * '<S32>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/DchgPower3'
 * '<S33>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enabled Subsystem'
 * '<S34>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant'
 * '<S35>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant1'
 * '<S36>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant12'
 * '<S37>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant2'
 * '<S38>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant3'
 * '<S39>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant4'
 * '<S40>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant5'
 * '<S41>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant6'
 * '<S42>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant7'
 * '<S43>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Enumerated Constant8'
 * '<S44>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem'
 * '<S45>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4'
 * '<S46>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Interval Test Dynamic'
 * '<S47>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC'
 * '<S48>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Saturation Dynamic'
 * '<S49>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlag'
 * '<S50>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlagFullChg'
 * '<S51>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh'
 * '<S52>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreDSOC'
 * '<S53>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreLeftCap'
 * '<S54>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC'
 * '<S55>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreTSOC'
 * '<S56>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Subsystem1'
 * '<S57>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime'
 * '<S58>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH'
 * '<S59>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/DchgPower2'
 * '<S60>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/DchgPower4'
 * '<S61>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/Subsystem'
 * '<S62>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/Subsystem1'
 * '<S63>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/Subsystem/Chart2'
 * '<S64>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/Subsystem/Saturation Dynamic'
 * '<S65>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/Subsystem1/Subsystem'
 * '<S66>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/Subsystem1/Subsystem/Bit Rotate'
 * '<S67>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcChgSOH/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S68>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/DchgPower1'
 * '<S69>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/DchgPower2'
 * '<S70>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/DchgPower4'
 * '<S71>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/Subsystem'
 * '<S72>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/Subsystem1'
 * '<S73>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/Subsystem/Chart1'
 * '<S74>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/Subsystem/DchgPower1'
 * '<S75>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/Subsystem/Saturation Dynamic'
 * '<S76>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/Subsystem1/Subsystem'
 * '<S77>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/Subsystem1/Subsystem/Bit Rotate'
 * '<S78>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcDchgSOH/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S79>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcSocEffiient/Saturation Dynamic1'
 * '<S80>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/CalcLeftTime'
 * '<S81>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/CalcLeftTime1'
 * '<S82>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/DiagDrop1'
 * '<S83>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/Triggered Subsystem'
 * '<S84>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/Triggered Subsystem1'
 * '<S85>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/Triggered Subsystem4'
 * '<S86>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/CalcLeftTime/CalcLeftTime'
 * '<S87>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/CalcLeftTime/SelectChgCurrent'
 * '<S88>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/CalcLeftTime/SelectChgCurrent1'
 * '<S89>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/CalcLeftTime1/CalcLeftTime'
 * '<S90>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/CalcLeftTime1/SelectChgCurrent'
 * '<S91>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/CalcLeftTime1/SelectChgCurrent1'
 * '<S92>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnLeftChargeTime/DiagDrop1/DiagDropCore'
 * '<S93>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnSOC/Interval Test Dynamic'
 * '<S94>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnSOC/Saturation Dynamic'
 * '<S95>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnSOC/Saturation Dynamic1'
 * '<S96>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnSOC/Saturation Dynamic2'
 * '<S97>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnSOC1/Interval Test Dynamic'
 * '<S98>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalcnSOC1/Saturation Dynamic'
 * '<S99>'  : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalibEmptySOC/ConvertSOC2AH'
 * '<S100>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalibEmptySOC/ConvertSOC2AH/Saturation Dynamic'
 * '<S101>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalibFullSOC/DchgPower2'
 * '<S102>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalibFullSOC/DchgPower4'
 * '<S103>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalibFullSOC/Saturation Dynamic'
 * '<S104>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CalibFullSOC/Subsystem'
 * '<S105>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Chart'
 * '<S106>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH'
 * '<S107>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH1'
 * '<S108>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH2'
 * '<S109>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH3'
 * '<S110>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH4'
 * '<S111>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH5'
 * '<S112>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH6'
 * '<S113>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1'
 * '<S114>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Function-Call Subsystem'
 * '<S115>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT'
 * '<S116>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Saturation Dynamic'
 * '<S117>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/StoreCulumutiveAh'
 * '<S118>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH/Saturation Dynamic'
 * '<S119>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH1/Saturation Dynamic'
 * '<S120>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH2/Saturation Dynamic'
 * '<S121>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH3/Saturation Dynamic'
 * '<S122>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH4/Saturation Dynamic'
 * '<S123>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH5/Saturation Dynamic'
 * '<S124>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/ConvertSOC2AH6/Saturation Dynamic'
 * '<S125>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Chart'
 * '<S126>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Enabled Subsystem1'
 * '<S127>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Enumerated Constant'
 * '<S128>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Function-Call Subsystem'
 * '<S129>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Enabled Subsystem1/CalcLeftCap'
 * '<S130>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Enabled Subsystem1/MATLAB Function'
 * '<S131>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Enabled Subsystem1/CalcLeftCap/Chart'
 * '<S132>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Enabled Subsystem1/CalcLeftCap/Saturation Dynamic'
 * '<S133>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Enabled Subsystem1/CalcLeftCap/Saturation Dynamic1'
 * '<S134>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/Enabled Subsystem1/Enabled Subsystem1/CalcLeftCap/Saturation Dynamic2'
 * '<S135>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp20'
 * '<S136>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp40'
 * '<S137>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp45'
 * '<S138>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp20/Current_1C'
 * '<S139>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp20/Current_1C1'
 * '<S140>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp40/Current_1C'
 * '<S141>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp40/Current_1C1'
 * '<S142>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp45/Current_1C'
 * '<S143>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/LKT/LKT_Temp45/Current_1C1'
 * '<S144>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/StoreCulumutiveAh/Enumerated Constant'
 * '<S145>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder1/StoreCulumutiveAh/Enumerated Constant3'
 * '<S146>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder2/Function-Call Subsystem'
 * '<S147>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/CapAdder2/Saturation Dynamic'
 * '<S148>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearLeftCapWOCalib/Subsystem'
 * '<S149>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearLeftCapWOCalib2/DchgPower2'
 * '<S150>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearLeftCapWOCalib2/DchgPower4'
 * '<S151>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearLeftCapWOCalib2/Subsystem'
 * '<S152>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearLeftCapWOCalib2/Subsystem/Bit Rotate'
 * '<S153>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearLeftCapWOCalib2/Subsystem/Bit Rotate/bit_rotate'
 * '<S154>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/ClearSOHCalcFlag/DchgPower1'
 * '<S155>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem/DchgPower2'
 * '<S156>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem/DchgPower4'
 * '<S157>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem/Subsystem'
 * '<S158>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem/Subsystem/Bit Rotate'
 * '<S159>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem/Subsystem/Bit Rotate/bit_rotate'
 * '<S160>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Enabled Subsystem'
 * '<S161>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Enabled Subsystem1'
 * '<S162>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Enumerated Constant'
 * '<S163>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Enumerated Constant1'
 * '<S164>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Enumerated Constant2'
 * '<S165>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Enumerated Constant3'
 * '<S166>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Interval Test Dynamic'
 * '<S167>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/MATLAB Function'
 * '<S168>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Saturation Dynamic'
 * '<S169>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem1'
 * '<S170>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2'
 * '<S171>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Enabled Subsystem1/Enumerated Constant2'
 * '<S172>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem1/Subsystem'
 * '<S173>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem1/Subsystem1'
 * '<S174>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem1/Subsystem/Bit Rotate'
 * '<S175>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S176>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem1/Subsystem1/Subsystem'
 * '<S177>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem1/Subsystem1/Subsystem/Bit Rotate'
 * '<S178>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem1/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S179>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2/DchgPower1'
 * '<S180>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2/DchgPower2'
 * '<S181>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2/Enumerated Constant8'
 * '<S182>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2/MATLAB Function2'
 * '<S183>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2/MATLAB Function3'
 * '<S184>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2/Subsystem'
 * '<S185>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2/Subsystem/Bit Rotate'
 * '<S186>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Function-Call Subsystem4/Subsystem2/Subsystem/Bit Rotate/bit_rotate'
 * '<S187>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/CalcLeftCap'
 * '<S188>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Chart'
 * '<S189>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/DchgPower1'
 * '<S190>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/DchgPower2'
 * '<S191>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/DchgPower4'
 * '<S192>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Enumerated Constant1'
 * '<S193>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Enumerated Constant2'
 * '<S194>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Enumerated Constant3'
 * '<S195>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Enumerated Constant6'
 * '<S196>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Interval Test Dynamic'
 * '<S197>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/MATLAB Function'
 * '<S198>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/MATLAB Function1'
 * '<S199>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/MATLAB Function2'
 * '<S200>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Saturation Dynamic'
 * '<S201>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Saturation Dynamic1'
 * '<S202>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Saturation Dynamic2'
 * '<S203>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Saturation Dynamic3'
 * '<S204>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Saturation Dynamic4'
 * '<S205>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Saturation Dynamic5'
 * '<S206>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Subsystem'
 * '<S207>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Subsystem1'
 * '<S208>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Subsystem/Chart1'
 * '<S209>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Subsystem/DchgPower1'
 * '<S210>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Subsystem/Saturation Dynamic'
 * '<S211>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Subsystem1/Subsystem'
 * '<S212>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Subsystem1/Subsystem/Bit Rotate'
 * '<S213>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/LKTSOC/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S214>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlag/DchgPower1'
 * '<S215>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlag/DchgPower2'
 * '<S216>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlag/DchgPower4'
 * '<S217>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlag/Subsystem'
 * '<S218>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlag/Subsystem/Bit Rotate'
 * '<S219>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlag/Subsystem/Bit Rotate/bit_rotate'
 * '<S220>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlagFullChg/DchgPower1'
 * '<S221>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlagFullChg/DchgPower2'
 * '<S222>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlagFullChg/DchgPower4'
 * '<S223>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlagFullChg/Subsystem'
 * '<S224>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlagFullChg/Subsystem/Bit Rotate'
 * '<S225>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/SetSOHCalcFlagFullChg/Subsystem/Bit Rotate/bit_rotate'
 * '<S226>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/Enumerated Constant'
 * '<S227>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/Enumerated Constant1'
 * '<S228>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/Enumerated Constant2'
 * '<S229>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/Enumerated Constant3'
 * '<S230>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh'
 * '<S231>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1'
 * '<S232>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/DchgPower1'
 * '<S233>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/DchgPower2'
 * '<S234>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/DchgPower3'
 * '<S235>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/DchgPower4'
 * '<S236>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/Enumerated Constant'
 * '<S237>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/Subsystem'
 * '<S238>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/Subsystem1'
 * '<S239>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/Subsystem/Bit Rotate'
 * '<S240>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/Subsystem/Bit Rotate/bit_rotate'
 * '<S241>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/Subsystem1/Subsystem'
 * '<S242>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/Subsystem1/Subsystem/Bit Rotate'
 * '<S243>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreChgAh/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S244>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/DchgPower1'
 * '<S245>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/DchgPower2'
 * '<S246>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/DchgPower3'
 * '<S247>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/DchgPower4'
 * '<S248>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/Enumerated Constant2'
 * '<S249>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/Subsystem'
 * '<S250>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/Subsystem1'
 * '<S251>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/Subsystem/Bit Rotate'
 * '<S252>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/Subsystem/Bit Rotate/bit_rotate'
 * '<S253>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/Subsystem1/Subsystem'
 * '<S254>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/Subsystem1/Subsystem/Bit Rotate'
 * '<S255>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreCulumutiveAh/StoreDchgAh1/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S256>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreDSOC/WriteLeftCap'
 * '<S257>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreDSOC/WriteLeftCap/Enumerated Constant'
 * '<S258>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreLeftCap/WriteLeftCap'
 * '<S259>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreLeftCap/WriteLeftCap/Enumerated Constant'
 * '<S260>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreLeftCap/WriteLeftCap/Enumerated Constant1'
 * '<S261>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreLeftCap/WriteLeftCap/Subsystem'
 * '<S262>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreLeftCap/WriteLeftCap/Subsystem/Bit Rotate'
 * '<S263>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreLeftCap/WriteLeftCap/Subsystem/Bit Rotate/bit_rotate'
 * '<S264>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem'
 * '<S265>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1'
 * '<S266>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1'
 * '<S267>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1/Bit Rotate1'
 * '<S268>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1/Bit Rotate2'
 * '<S269>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1/DchgPower1'
 * '<S270>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1/DchgPower2'
 * '<S271>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1/DchgPower3'
 * '<S272>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1/DchgPower4'
 * '<S273>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1/Bit Rotate1/bit_rotate'
 * '<S274>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem/Enabled Subsystem1/Bit Rotate2/bit_rotate'
 * '<S275>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1'
 * '<S276>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/Bit Rotate1'
 * '<S277>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/Bit Rotate2'
 * '<S278>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/DchgPower1'
 * '<S279>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/DchgPower2'
 * '<S280>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/DchgPower3'
 * '<S281>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/DchgPower4'
 * '<S282>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/Saturation Dynamic'
 * '<S283>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/Bit Rotate1/bit_rotate'
 * '<S284>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreSOC/Subsystem1/Enabled Subsystem1/Bit Rotate2/bit_rotate'
 * '<S285>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreTSOC/WriteLeftCap'
 * '<S286>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/StoreTSOC/WriteLeftCap/Enumerated Constant'
 * '<S287>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Subsystem1/Subsystem'
 * '<S288>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Subsystem1/Subsystem/Bit Rotate'
 * '<S289>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/Subsystem1/Subsystem/Bit Rotate/bit_rotate'
 * '<S290>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime/Enumerated Constant'
 * '<S291>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime/Enumerated Constant1'
 * '<S292>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime/Enumerated Constant2'
 * '<S293>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime/Enumerated Constant6'
 * '<S294>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime/Enumerated Constant7'
 * '<S295>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime/Subsystem'
 * '<S296>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime/Subsystem/Bit Rotate'
 * '<S297>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteOCVTime/Subsystem/Bit Rotate/bit_rotate'
 * '<S298>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enabled Subsystem'
 * '<S299>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enabled Subsystem1'
 * '<S300>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enabled Subsystem2'
 * '<S301>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enabled Subsystem3'
 * '<S302>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enabled Subsystem4'
 * '<S303>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enabled Subsystem5'
 * '<S304>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enabled Subsystem6'
 * '<S305>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enabled Subsystem7'
 * '<S306>' : 'Udan_SOC/SOC_Calculate/UdanSOCCalcn/WriteSOH/Enumerated Constant2'
 */
#endif                                 /* RTW_HEADER_Udan_SOC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
