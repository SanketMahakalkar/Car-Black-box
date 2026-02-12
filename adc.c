/*
 * File:   adc.c
 * Author: sanket
 *
 * Created on 7 January, 2025, 8:08 PM
 */
#include <xc.h>
#include "adc.h"

void setup_adc(void) {
    ADFM = 1; // Right Justification
    ADON = 1; // Power on ADC
}

unsigned short get_adc_value(void) {
    unsigned short raw_conversion;
    GO = 1; // Start conversion
    while (nDONE); 
    raw_conversion = (unsigned short)(ADRESH << 8) | ADRESL;
    return raw_conversion;
}