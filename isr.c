#include <xc.h>
#include "main.h"

unsigned char sec, return_time;

void __interrupt() core_isr(void) {
    static unsigned int ticks = 0;
    if (TMR2IF) {
        if (++ticks == 1250) {
            ticks = 0;
            if (sec > 0) sec--;
            else if (sec == 0 && return_time > 0) return_time--;
        }
        TMR2IF = 0;
    }
}