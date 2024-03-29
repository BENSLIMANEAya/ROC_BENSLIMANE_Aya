/* 
 * File:   main.c
 * Author: Table2
 *
 * Created on 16 novembre 2022, 10:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "Robot.h"
#include "ToolBox.h"
#include "PWM.h"
#include "ADC.h"

int main(void) {
    /***************************************************************************************************/
    //Initialisation de l?oscillateur
    /****************************************************************************************************/
    InitOscillator();

    /****************************************************************************************************/
    // Configuration des entr�es sorties
    /****************************************************************************************************/
    InitIO();

    InitTimer23();
    InitTimer1();
    InitPWM();
    InitADC1();


    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;




    /****************************************************************************************************/
    // Boucle Principale
    /****************************************************************************************************/
    while (1) {
        ADC1StartConversionSequence();
        unsigned int * result = ADCGetResult();
        unsigned int ADCValue0 = result[0];
        unsigned int ADCValue1 = result[1];
        unsigned int ADCValue2 = result[2];

        //PWMSetSpeedConsigne(-20,MOTEUR_GAUCHE);
        if (ADCValue0 < 100) {
            LED_ORANGE = 1;
        } else {
            LED_ORANGE = 0;
        }
        if (ADCValue1 < 100) {
            LED_BLEUE = 1;
        } else {
            LED_BLEUE = 0;
        }
        if (ADCValue2 < 100) {
            LED_BLANCHE = 1;
        } else
            LED_BLANCHE = 0;
        if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [2])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [0])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
        }


    }
    // fin main
}
