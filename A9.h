/*
 * A9.h
*/
#ifndef A9_H_
#define A9_H_

#include <string.h>
#include "A8.h"
void ADC_init();

uint32_t get_conversion_results();

void set_global_flag(uint8_t val);
uint16_t voltage_conversion(uint32_t data);
uint8_t get_global_flag();

void ADC14_IRQHandler();
void transmit_word(char *word);

#endif /* A9_H_ */
