/*
 * A9.h
*/
#ifndef A9_H_
#define A9_H_

void ADC_init();

uint32_t get_conversion_results();

void set_global_flag(uint8_t val);

uint8_t get_global_flag();

void ADC14_IRQHandler();

#endif /* A9_H_ */
