
#include "ModeloConFiltro.h"
#include "mbed.h"


const long interval = 200;

Serial ecgg(USBTX, USBRX);
AnalogIn   ain(A0);

float ECGd;
float ECG;
double numerito;

DW rtDW;
ExtY rtY;

RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

void main(void)
{
    ecgg.baud(9600);
    Timer timer;
    unsigned long currentMillis, previousMillis;
    timer.start();
    previousMillis = timer.read_ms();
    
    while(1)
    {     
          currentMillis = timer.read_ms();
          ECGd=ain.read();
          ECG= ECGd*3.3;
          const ConstP rtConstP = {
            { ECG}
            };


          real_T numAccum;
          real_T denAccum;
          int32_T ioIdx;
          real_T rtb_UnitDelay[12];
          real_T rtb_UnitDelay1[12];
          real_T rtb_UnitDelay2[12];
          real_T rtb_Resta1[12];
          real_T rtb_Resta2[12];
          int32_T i;
          for (i = 0; i < 1; i++) {
            /* UnitDelay: '<S1>/Unit Delay' */
            rtb_UnitDelay[i] = rtDW.UnitDelay_DSTATE[i];
        
            /* UnitDelay: '<S1>/Unit Delay1' */
            rtb_UnitDelay1[i] = rtDW.UnitDelay1_DSTATE[i];
        
            /* UnitDelay: '<S1>/Unit Delay2' */
            rtb_UnitDelay2[i] = rtDW.UnitDelay2_DSTATE[i];
        
            
            denAccum = (((((1.0 * rtConstP.Constant1_Value[i] + 53.3169 *
                            rtDW.UnitDelay_DSTATE[i]) + -161.5172 *
                           rtDW.UnitDelay1_DSTATE[i]) + 164.834 *
                          rtDW.UnitDelay2_DSTATE[i]) + -56.6596 *
                         rtDW.UnitDelay3_DSTATE[i]) + -0.9943 * rtDW.UnitDelay5_DSTATE[i])
              + 1.9941 * rtDW.UnitDelay4_DSTATE[i];
        
            
            rtb_Resta2[i] = denAccum + 95.3318;
            rtb_Resta1[i] = denAccum;
          }
        
          ioIdx = 0;
          for (i = 0; i < 1; i++) {
            denAccum = (0.00030412944238428512 * rtb_Resta2[ioIdx] - -1.9642129749667252
                        * rtDW.Filter1_FILT_STATES[0]) - 0.96542949273626266 *
              rtDW.Filter1_FILT_STATES[1];
            numAccum = (2.0 * rtDW.Filter1_FILT_STATES[0] + denAccum) +
              rtDW.Filter1_FILT_STATES[1];
            rtDW.Filter1_FILT_STATES[1] = rtDW.Filter1_FILT_STATES[0];
            rtDW.Filter1_FILT_STATES[0] = denAccum;
            denAccum = (0.017290512185698242 * numAccum - -0.96541897562860346 *
                        rtDW.Filter1_FILT_STATES[2]) - 0.0 * rtDW.Filter1_FILT_STATES[3];
            numAccum = (denAccum + rtDW.Filter1_FILT_STATES[2]) + 0.0 *
              rtDW.Filter1_FILT_STATES[3];
            rtDW.Filter1_FILT_STATES[3] = rtDW.Filter1_FILT_STATES[2];
            rtDW.Filter1_FILT_STATES[2] = denAccum;
            rtY.Out1[ioIdx] = numAccum;
            numerito=rtY.Out1[i];
            numerito=numerito-8000;                                     //Salida
            
            ioIdx++;
        
            rtDW.UnitDelay_DSTATE[i] = rtConstP.Constant1_Value[i];
        
            rtDW.UnitDelay1_DSTATE[i] = rtb_UnitDelay[i];
        
            rtDW.UnitDelay2_DSTATE[i] = rtb_UnitDelay1[i];
        
            rtDW.UnitDelay3_DSTATE[i] = rtb_UnitDelay2[i];
        
            rtDW.UnitDelay5_DSTATE[i] = rtDW.UnitDelay4_DSTATE[i];
        
            rtDW.UnitDelay4_DSTATE[i] = rtb_Resta1[i];
            wait(0.002);
            
            }
            
            
            if(currentMillis - previousMillis > interval)
        {
            //printf("%f \n",numerito);
            ecgg.printf("%f \n",numerito);
            
            previousMillis = currentMillis;
        }
  }

  
}
