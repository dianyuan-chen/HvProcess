/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                              (c) Copyright 2002, Micrium, Inc., Weston, FL
*                                          All Rights Reserved
*
*
*                                       Paged MC9S12X Specific code
*                                           (Codewarrior v4.5)
*
* File         : OS_CPU.H
* By           : Eric Shufro
*********************************************************************************************************
*/

#ifndef OS_CPU_H
#define OS_CPU_H

/*
*********************************************************************************************************
*                                   INTERRUPT DISABLE TIME MEASUREMENT
*********************************************************************************************************
*/

#define  OS_CPU_INT_DIS_MEAS_EN    0

/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned int   INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   int   INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */
typedef long long      INT64S;
typedef unsigned long long INT64U;

typedef unsigned char  OS_STK;                   /* Each stack entry is 8-bit wide                     */
typedef unsigned short OS_CPU_SR;                /* Define size of CPU status register (PSW = 16 bits) */

typedef unsigned char  ubyte;    // 1 byte unsigned; prefix: ub
typedef signed char    sbyte;    // 1 byte signed;   prefix: sb
typedef unsigned int   uword;    // 2 byte unsigned; prefix: uw
typedef signed int     sword;    // 2 byte signed;   prefix: sw
typedef unsigned long  ulong;    // 4 byte unsigned; prefix: ul
typedef signed long    slong;    // 4 byte signed;   prefix: sl
typedef unsigned short ushort;   // 2 byte unsigned; prefix: us
typedef signed short   sshort;   // 2 byte signed;   prefix: ss
/*
*********************************************************************************************************
*                                              CONSTANTS
*********************************************************************************************************
*/

#ifndef  FALSE
#define  FALSE    0U
#endif

#ifndef  TRUE
#define  TRUE     1U
#endif

#define __NEAR near

/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

void  OSStartHighRdy(void);
void  OSIntCtxSw    (void);
void  OSCtxSw       (void);

/*
*********************************************************************************************************
*                                               MC9S12X
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*
* NOTE(s)  :  1) The current version of the compiler does NOT allow method #2 to be used without changing
*                the processor independent portion of uC/OS-II.
*             2) The current version of the compiler does NOT allow method #3 either.  However, this can
*                be implemented in OS_CPU_A.S by defining the functions: OSCPUSaveSR() and
*                OSCPURestoreSR().
*********************************************************************************************************
*/
#define  OS_CRITICAL_METHOD    3

#if      OS_CRITICAL_METHOD == 3
#define  OS_INIT_CRITICAL()   OS_CPU_SR cpu_sr
#define  OS_ENTER_CRITICAL()  (cpu_sr = OS_CPU_SR_Save())    /* Disable interrupts                        */
#define  OS_EXIT_CRITICAL()   (OS_CPU_SR_Restore(cpu_sr))    /* Enable  interrupts                        */
#endif

#define  OS_TASK_SW()          _asm("swi")

#define  OS_STK_GROWTH        1                  /* Define stack growth: 1 = Down, 0 = Up              */

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/
#if      OS_CRITICAL_METHOD == 3
OS_CPU_SR  near OS_CPU_SR_Save(void);                    /* Return the value of the CCR register and then ...  */
                                                    /* ... disable interrupts via SEI instruction.        */
void       near OS_CPU_SR_Restore(OS_CPU_SR os_cpu_sr);  /* Set CCR register to 'os_cpu_sr'                    */
#endif
#endif
