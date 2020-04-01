
#ifndef RTW_HEADER_ModeloConFiltro_h_
#define RTW_HEADER_ModeloConFiltro_h_
#ifndef ModeloConFiltro_COMMON_INCLUDES_
# define ModeloConFiltro_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ModeloConFiltro_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE[12];         /* '<S1>/Unit Delay' */
  real_T UnitDelay1_DSTATE[12];        /* '<S1>/Unit Delay1' */
  real_T UnitDelay2_DSTATE[12];        /* '<S1>/Unit Delay2' */
  real_T UnitDelay3_DSTATE[12];        /* '<S1>/Unit Delay3' */
  real_T UnitDelay5_DSTATE[12];        /* '<S1>/Unit Delay5' */
  real_T UnitDelay4_DSTATE[12];        /* '<S1>/Unit Delay4' */
  real_T Filter1_FILT_STATES[4];       /* '<S1>/Filter1' */
} DW;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: [3 6 5 3 7 6 1 4 2 7 6 4]
   * Referenced by: '<S1>/Constant1'
   */
  real_T Constant1_Value[12];
} ConstP;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Out1[12];                     /* '<Root>/Out1' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (auto storage) */
extern DW rtDW;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY rtY;

/* Constant parameters (auto storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void ModeloConFiltro_initialize(void);
extern void ModeloConFiltro_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

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
 * hilite_system('ModeloMasFiltro/ModeloConFiltro')    - opens subsystem ModeloMasFiltro/ModeloConFiltro
 * hilite_system('ModeloMasFiltro/ModeloConFiltro/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ModeloMasFiltro'
 * '<S1>'   : 'ModeloMasFiltro/ModeloConFiltro'
 */
#endif                                 /* RTW_HEADER_ModeloConFiltro_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */