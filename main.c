

/**
 * main.c
 */
#include "msp.h"
#include "A8.h"
#include "A9.h"
#include "A2.h"

//volatile uint16_t to_transmit;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	set_DCO(FREQ_24_MHz);
	UART_init();
	ADC_init();

    uint16_t data = 0;
    uint16_t to_transmit;

	while(1)
	{
	    if(get_global_flag())
	    {

	        data = get_conversion_results();
	        to_transmit = voltage_conversion(data);  // convert to volts*100
	        transmit_word(to_transmit);
	        set_global_flag(0);
	        ADC14 -> CTL0 |= ADC14_CTL0_SC; //initiate a new sample for the ADC14
	        ADC14 -> IER0 |= ADC14_IER0_IE0;
	    }
	}
}
