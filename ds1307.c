/*
 * File:   ds1307.c
 * Author: sanket
 *
 * Created on 7 January, 2025, 8:08 PM
 */

#include <xc.h>
#include "i2c.h"
#include "ds1307.h"

void setup_ds1307(void) {
    unsigned char val;
    val = get_rtc_data(ADDR_SEC);
    val &= 0x7F; // Clear CH bit
    set_rtc_data(ADDR_SEC, val);
}

unsigned char get_rtc_data(unsigned char addr) {
    unsigned char res;
    i2c_trigger_start();
    i2c_send_byte(RTC_WRITE_ADDR);
    i2c_send_byte(addr);
    i2c_trigger_rep_start();
    i2c_send_byte(RTC_READ_ADDR);
    res = i2c_receive_byte(0);
    i2c_trigger_stop();
    return res;
}

void set_rtc_data(unsigned char addr, unsigned char data) {
    i2c_trigger_start();
    i2c_send_byte(RTC_WRITE_ADDR);
    i2c_send_byte(addr);
    i2c_send_byte(data);
    i2c_trigger_stop();
}