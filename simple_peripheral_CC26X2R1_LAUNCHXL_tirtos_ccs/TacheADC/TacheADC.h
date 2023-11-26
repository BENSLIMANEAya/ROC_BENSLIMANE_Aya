/*
 * TacheADC.h
 *
 *  Created on: 22 nov. 2023
 *      Author: TP-EO-5
 */


#ifndef TACHEADC_TACHEADC_H_
#define TACHEADC_TACHEADC_H_

void TacheADC_CreateTask(void);
void turn_on_LEDS(void);
void turn_off_LEDS(void);
void myClockSwiFxn(uintptr_t arg0);
void Sampling(uint_least8_t Board_ADC_Number);
void TacheADC_init(void);
#endif /* TACHEADC_TACHEADC_H_ */
