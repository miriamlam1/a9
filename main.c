

/**
 * main.c
 */
#include "msp.h"
#include "A8.h"
#include "A9.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	UART_init();
	ADC_init();
    uint32_t data;
    uint16_t to_transmit;

	while(1)
	{
	    if(get_global_flag())
	    {
	        data = get_conversion_results();
	        to_transmit = voltage_conversion(data);  // convert to volts
	        // make to characters/list
	        // be able to print decimal wo floats
	        transmit_data(data);
	        set_global_flag(0);
	        ADC14 -> CTL0 |= ADC14_CTL0_SC; //initiate a new sample for the ADC14
	    }
	}
}
