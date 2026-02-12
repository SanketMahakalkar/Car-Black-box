#ifndef ADC_H
#define ADC_H

/* System ADC Initialization */
void setup_adc(void);

/* Retrieve raw value from ADC Channel */
unsigned short get_adc_value(void);

#endif