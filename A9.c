/*
 * A9.c
 */

#include "msp.h"
#include "A9.h"

uint8_t receive = 0;

/* 14-bit -> 3FFF = 16383
 * */
void ADC_init()
{
    P5 -> SEL0 |= BIT4; //config. A1 pin for ADC tertiary mode for adc
    P5 -> SEL1 |= BIT4;

    P5 -> DIR |= BIT4; // set input
    P5 -> OUT |= BIT4; // out on

    ADC14 -> CTL0 &= ~ADC14_CTL0_ENC; //ADC14 disable while configure

    ADC14 -> CTL0 |= ADC14_CTL0_ON //ADC14 on - reset is removed
                  |  ADC14_CTL0_SSEL_4 //SMCLK
                  | ADC14_CTL0_SHP // internal sample timer
                  | ADC14_CTL0_SHT0_0; // sample every 4 clock cycles

    ADC14 -> CTL1 |= ADC14_CTL1_RES__14BIT; //conversion result resolution
    ADC14 -> MCTL[0] |= ADC14_MCTL_INCH_1; //input channel select bc A1
    ADC14 -> CTL0 |= ADC14_CTL0_ENC; //must be set to 1 before any conv.enable adc to start running
    ADC14 -> IER0 |= ADC14_IER0_IE0; //where to write in memory when interrupt
    NVIC -> ISER[0] = 1 <<(ADC14_IRQn & 31); //set NVIC interrupt
    _enable__irq(); //enabled global interrupts

    ADC14 -> CTL0 |= ADC14_CTL0_SC; //start conversion
}

uint32_t get_conversion_results() // returns weird number look at p62 -> voltage you want
{
    uint32_t data = 0;
    data = (ADC14 -> MEM[0] |= ADC14_MEMN_CONVRES_MASK); //conversion results are written to ADC14MEM
    return data;
}
uint16_t voltage_conversion(uint32_t data){ //
    uint16_t voltage;
    voltage = data; // formula
}

void transmit_word(char data_array[]){
    uint16_t i;
    for(i=0; i<data_array.size(); i++){
        transmit_data(data_array[i]);
    }

}

void set_global_flag(uint8_t val){
    receive = val;
}

uint8_t get_global_flag(){
    return receive;
}

void make_new_sample(){

}

void ADC14_IRQHandler(){
    ADC14 -> IER0 &= ~EUSCI_A_IE_RXIE;   //disable interrupt
    receive = 1;
}