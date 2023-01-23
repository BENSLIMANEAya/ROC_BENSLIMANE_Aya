#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "Robot.h"
#include "PWM.h"
#include "ToolBox.h"
#include "ADC.h"

unsigned int ADCValue[4];

int main (void){
/***************************************************************************************************/
//Initialisation de l?oscillateur
//Initialisation Timer23
/****************************************************************************************************/
InitOscillator();
/****************************************************************************************************/
// Configuration des entrées sorties
/****************************************************************************************************/
InitIO();
InitTimer1();
InitTimer23();
InitPWM();
InitADC1();


LED_BLANCHE = 1;
LED_BLEUE = 1;
LED_ORANGE = 1;

 if (ADCIsConversionFinished()){
     ADCValue[0]=ADCGetResult()[0];
     ADCClearConversionFinishedFlag();
 }
/****************************************************************************************************/
// Boucle Principale
/****************************************************************************************************/
while(1){
} // fin main

}