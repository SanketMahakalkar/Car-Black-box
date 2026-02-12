/*
 * File:   timers.c
 * Author: sanket
 *
 * Created on 7 January, 2025, 8:09 PM
 */

#include <xc.h>
#include "timers.h"

void setup_timer2(void) {
    T2CKPS0 = 1; // 1:16 Prescale
    T2CKPS1 = 1;
    PR2 = 250;   // Match value
    TMR2IE = 1;  // Enable interrupt
    TMR2ON = 0;  // Default OFF
}