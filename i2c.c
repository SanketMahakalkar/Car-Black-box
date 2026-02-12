#include <xc.h>
#include "i2c.h"

void setup_i2c(unsigned long baud_rate) {
    SSPM3 = 1; // Master mode
    SSPADD = (unsigned char)(SYSTEM_FOSC / (4 * baud_rate)) - 1;
    SSPEN = 1; // Enable
}

static void wait_for_idle(void) {
    while (R_nW || (SSPCON2 & 0x1F));
}

void i2c_trigger_start(void) {
    wait_for_idle();
    SEN = 1;
}

void i2c_trigger_rep_start(void) {
    i2c_trigger_stop();
    i2c_trigger_start();
}

void i2c_trigger_stop(void) {
    wait_for_idle();
    PEN = 1;
}

unsigned char i2c_receive_byte(unsigned char ack) {
    unsigned char d;
    wait_for_idle();
    RCEN = 1;
    wait_for_idle();
    d = SSPBUF;
    ACKDT = (ack == 1) ? 1 : 0;
    ACKEN = 1;
    return d;
}

int i2c_send_byte(unsigned char data) {
    wait_for_idle();
    SSPBUF = data;
    return !ACKSTAT;
}