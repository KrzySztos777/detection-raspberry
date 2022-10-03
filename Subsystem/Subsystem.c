/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.c
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

#include "Subsystem.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_roundd_snf(real_T u);
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void Subsystem_step(void)
{
  real_T rtb_DiscreteTimeIntegrator;
  real_T rtb_DeadZone;
  real_T rtb_FilterCoefficient;
  boolean_T rtb_FixPtRelationalOperator_h;
  boolean_T rtb_LogicalOperator2;
  real_T u0;
  real_T currentAngle_tmp;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  rtb_DiscreteTimeIntegrator = rtDW.DiscreteTimeIntegrator_DSTATE;

  /* Outport: '<Root>/dirSignal' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  RelationalOperator: '<S50>/FixPt Relational Operator'
   *  UnitDelay: '<S50>/Delay Input1'
   *
   * Block description for '<S50>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtY.dirSignal = (rtDW.DiscreteTimeIntegrator_DSTATE > rtDW.DelayInput1_DSTATE);

  /* Saturate: '<S1>/Saturation1' incorporates:
   *  Inport: '<Root>/destAngle'
   */
  if (rtU.destAngle > 80.0) {
    rtb_DeadZone = 80.0;
  } else if (rtU.destAngle < -80.0) {
    rtb_DeadZone = -80.0;
  } else {
    rtb_DeadZone = rtU.destAngle;
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* Sum: '<S1>/Sum1' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  rtb_DeadZone -= rtDW.DiscreteTimeIntegrator_DSTATE;

  /* DeadZone: '<S1>/Dead Zone' */
  if (rtb_DeadZone > 7.5) {
    rtb_DeadZone -= 7.5;
  } else if (rtb_DeadZone >= -7.5) {
    rtb_DeadZone = 0.0;
  } else {
    rtb_DeadZone -= -7.5;
  }

  /* End of DeadZone: '<S1>/Dead Zone' */

  /* Gain: '<S36>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S28>/Filter'
   *  Gain: '<S27>/Derivative Gain'
   *  Sum: '<S28>/SumD'
   */
  rtb_FilterCoefficient = (0.181449753667093 * rtb_DeadZone - rtDW.Filter_DSTATE)
    * 22.9834626882175;

  /* Quantizer: '<S1>/Quantizer' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  Quantizer: '<S3>/Quantizer'
   */
  currentAngle_tmp = rt_roundd_snf(rtDW.DiscreteTimeIntegrator_DSTATE / 0.1125) *
    0.1125;

  /* Outport: '<Root>/currentAngle' incorporates:
   *  Quantizer: '<S1>/Quantizer'
   */
  rtY.currentAngle = currentAngle_tmp;

  /* RelationalOperator: '<S49>/FixPt Relational Operator' incorporates:
   *  UnitDelay: '<S49>/Delay Input1'
   *
   * Block description for '<S49>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtb_FixPtRelationalOperator_h = (currentAngle_tmp != rtDW.DelayInput1_DSTATE_j);

  /* Logic: '<S3>/Logical Operator2' incorporates:
   *  Constant: '<S48>/Constant'
   *  Delay: '<S3>/Delay'
   *  Logic: '<S3>/Logical Operator'
   *  Logic: '<S3>/Logical Operator1'
   *  Memory: '<S3>/Memory'
   *  RelationalOperator: '<S48>/Compare'
   */
  rtb_LogicalOperator2 = ((rtDW.Memory_PreviousInput ||
    rtb_FixPtRelationalOperator_h) && (!(rtDW.Delay_DSTATE[0] >= 0.5)));

  /* Outport: '<Root>/stepSignal' */
  rtY.stepSignal = rtb_LogicalOperator2;

  /* Sum: '<S42>/Sum' incorporates:
   *  DiscreteIntegrator: '<S33>/Integrator'
   *  Gain: '<S38>/Proportional Gain'
   */
  u0 = (6.01792661067178 * rtb_DeadZone + rtDW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Saturate: '<S1>/Saturation' */
  if (u0 > 281.25) {
    u0 = 281.25;
  } else {
    if (u0 < -281.25) {
      u0 = -281.25;
    }
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE += 0.0001 * u0;

  /* Update for UnitDelay: '<S50>/Delay Input1'
   *
   * Block description for '<S50>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtDW.DelayInput1_DSTATE = rtb_DiscreteTimeIntegrator;

  /* Update for DiscreteIntegrator: '<S28>/Filter' */
  rtDW.Filter_DSTATE += 0.0001 * rtb_FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S33>/Integrator' incorporates:
   *  Gain: '<S30>/Integral Gain'
   */
  rtDW.Integrator_DSTATE += 6.70591201705588 * rtb_DeadZone * 0.0001;

  /* Update for UnitDelay: '<S49>/Delay Input1'
   *
   * Block description for '<S49>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtDW.DelayInput1_DSTATE_j = currentAngle_tmp;

  /* Update for Memory: '<S3>/Memory' */
  rtDW.Memory_PreviousInput = rtb_LogicalOperator2;

  /* Update for Delay: '<S3>/Delay' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   */
  rtDW.Delay_DSTATE[0] = rtDW.Delay_DSTATE[1];
  rtDW.Delay_DSTATE[1] = rtb_FixPtRelationalOperator_h;
}

/* Model initialize function */
void Subsystem_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
