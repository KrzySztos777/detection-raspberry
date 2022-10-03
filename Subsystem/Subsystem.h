/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.h
 *
 * Code generated for Simulink model 'Subsystem'.
 *
 * Model version                  : 1.179
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri May 28 00:18:28 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Subsystem_h_
#define RTW_HEADER_Subsystem_h_
#include <math.h>
#ifndef Subsystem_COMMON_INCLUDES_
# define Subsystem_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Subsystem_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE[2];              /* '<S3>/Delay' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real_T DelayInput1_DSTATE;           /* '<S50>/Delay Input1' */
  real_T Filter_DSTATE;                /* '<S28>/Filter' */
  real_T Integrator_DSTATE;            /* '<S33>/Integrator' */
  real_T DelayInput1_DSTATE_j;         /* '<S49>/Delay Input1' */
  boolean_T Memory_PreviousInput;      /* '<S3>/Memory' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T destAngle;                    /* '<Root>/destAngle' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T currentAngle;                 /* '<Root>/currentAngle' */
  boolean_T stepSignal;                /* '<Root>/stepSignal' */
  boolean_T dirSignal;                 /* '<Root>/dirSignal' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void Subsystem_initialize(void);
extern void Subsystem_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Manual Switch' : Eliminated due to constant selection input
 * Block '<S1>/Manual Switch1' : Eliminated due to constant selection input
 * Block '<S1>/Delay1' : Unused code path elimination
 * Block '<S1>/Gain' : Unused code path elimination
 * Block '<S1>/Sign' : Unused code path elimination
 * Block '<S1>/Sum2' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('model2/Subsystem')    - opens subsystem model2/Subsystem
 * hilite_system('model2/Subsystem/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'model2'
 * '<S1>'   : 'model2/Subsystem'
 * '<S2>'   : 'model2/Subsystem/PID Controller'
 * '<S3>'   : 'model2/Subsystem/SubsystemDriver'
 * '<S4>'   : 'model2/Subsystem/PID Controller/Anti-windup'
 * '<S5>'   : 'model2/Subsystem/PID Controller/D Gain'
 * '<S6>'   : 'model2/Subsystem/PID Controller/Filter'
 * '<S7>'   : 'model2/Subsystem/PID Controller/Filter ICs'
 * '<S8>'   : 'model2/Subsystem/PID Controller/I Gain'
 * '<S9>'   : 'model2/Subsystem/PID Controller/Ideal P Gain'
 * '<S10>'  : 'model2/Subsystem/PID Controller/Ideal P Gain Fdbk'
 * '<S11>'  : 'model2/Subsystem/PID Controller/Integrator'
 * '<S12>'  : 'model2/Subsystem/PID Controller/Integrator ICs'
 * '<S13>'  : 'model2/Subsystem/PID Controller/N Copy'
 * '<S14>'  : 'model2/Subsystem/PID Controller/N Gain'
 * '<S15>'  : 'model2/Subsystem/PID Controller/P Copy'
 * '<S16>'  : 'model2/Subsystem/PID Controller/Parallel P Gain'
 * '<S17>'  : 'model2/Subsystem/PID Controller/Reset Signal'
 * '<S18>'  : 'model2/Subsystem/PID Controller/Saturation'
 * '<S19>'  : 'model2/Subsystem/PID Controller/Saturation Fdbk'
 * '<S20>'  : 'model2/Subsystem/PID Controller/Sum'
 * '<S21>'  : 'model2/Subsystem/PID Controller/Sum Fdbk'
 * '<S22>'  : 'model2/Subsystem/PID Controller/Tracking Mode'
 * '<S23>'  : 'model2/Subsystem/PID Controller/Tracking Mode Sum'
 * '<S24>'  : 'model2/Subsystem/PID Controller/postSat Signal'
 * '<S25>'  : 'model2/Subsystem/PID Controller/preSat Signal'
 * '<S26>'  : 'model2/Subsystem/PID Controller/Anti-windup/Passthrough'
 * '<S27>'  : 'model2/Subsystem/PID Controller/D Gain/Internal Parameters'
 * '<S28>'  : 'model2/Subsystem/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S29>'  : 'model2/Subsystem/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S30>'  : 'model2/Subsystem/PID Controller/I Gain/Internal Parameters'
 * '<S31>'  : 'model2/Subsystem/PID Controller/Ideal P Gain/Passthrough'
 * '<S32>'  : 'model2/Subsystem/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S33>'  : 'model2/Subsystem/PID Controller/Integrator/Discrete'
 * '<S34>'  : 'model2/Subsystem/PID Controller/Integrator ICs/Internal IC'
 * '<S35>'  : 'model2/Subsystem/PID Controller/N Copy/Disabled'
 * '<S36>'  : 'model2/Subsystem/PID Controller/N Gain/Internal Parameters'
 * '<S37>'  : 'model2/Subsystem/PID Controller/P Copy/Disabled'
 * '<S38>'  : 'model2/Subsystem/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S39>'  : 'model2/Subsystem/PID Controller/Reset Signal/Disabled'
 * '<S40>'  : 'model2/Subsystem/PID Controller/Saturation/Passthrough'
 * '<S41>'  : 'model2/Subsystem/PID Controller/Saturation Fdbk/Disabled'
 * '<S42>'  : 'model2/Subsystem/PID Controller/Sum/Sum_PID'
 * '<S43>'  : 'model2/Subsystem/PID Controller/Sum Fdbk/Disabled'
 * '<S44>'  : 'model2/Subsystem/PID Controller/Tracking Mode/Disabled'
 * '<S45>'  : 'model2/Subsystem/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S46>'  : 'model2/Subsystem/PID Controller/postSat Signal/Forward_Path'
 * '<S47>'  : 'model2/Subsystem/PID Controller/preSat Signal/Forward_Path'
 * '<S48>'  : 'model2/Subsystem/SubsystemDriver/Compare To Constant'
 * '<S49>'  : 'model2/Subsystem/SubsystemDriver/Detect Change'
 * '<S50>'  : 'model2/Subsystem/SubsystemDriver/Detect Increase'
 */
#endif                                 /* RTW_HEADER_Subsystem_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
