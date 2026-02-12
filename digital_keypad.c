/*
 * File:   digital_keypad.c
 * Author: sanket
 *
 * Created on 7 January, 2025, 8:08 PM
 */

#include <xc.h>
#include "digital_keypad.h"

void setup_keypad(void) {
    KEYPAD_PORT_DDR |= MASK_INPUTS;
}

unsigned char get_key(unsigned char detection_mode) {
    static unsigned char active = 1;
    if (detection_mode == MODE_LEVEL) return KEYPAD_PORT & MASK_INPUTS;
    
    if (((KEYPAD_PORT & MASK_INPUTS) != NO_KEY) && active) {
        active = 0;
        return KEYPAD_PORT & MASK_INPUTS;
    } else if ((KEYPAD_PORT & MASK_INPUTS) == NO_KEY) {
        active = 1;
    }
    return NO_KEY;
}