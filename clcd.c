/*
 * File:   clcd.c
 * Author: sanket
 *
 * Created on 7 January, 2025, 8:08 PM
 */

#include <xc.h>
#include "clcd.h"

void clcd_cmd_write(unsigned char byte, unsigned char mode) {
    CLCD_RS = (__bit)mode;
    CLCD_DATA_PORT = byte;
    CLCD_EN = HIGH;
    __delay_us(100);
    CLCD_EN = LOW;
    __delay_us(4100);
}

static void setup_display_internal(void) {
    __delay_ms(30);
    clcd_cmd_write(MODE_8BIT, COMMAND_MODE);
    __delay_us(4100);
    clcd_cmd_write(MODE_8BIT, COMMAND_MODE);
    __delay_us(100);
    clcd_cmd_write(MODE_8BIT, COMMAND_MODE);
    __delay_us(1);
    clcd_cmd_write(DUAL_LINE_5x8, COMMAND_MODE);
    __delay_us(100);
    clcd_cmd_write(CLEAR_SCREEN, COMMAND_MODE);
    __delay_us(100);
    clcd_cmd_write(DISP_ON_NO_CURSOR, COMMAND_MODE);
    __delay_us(100);
}

void setup_clcd(void) {
    CLCD_DATA_PORT_DDR = 0x00;
    CLCD_RS_DDR = 0;
    CLCD_EN_DDR = 0;
    setup_display_internal();
}

void clcd_send_char(const char data, unsigned char addr) {
    clcd_cmd_write(addr, COMMAND_MODE);
    clcd_cmd_write(data, CHAR_MODE);
}

void clcd_print_string(const char *str, unsigned char addr) {
    clcd_cmd_write(addr, COMMAND_MODE);
    while (*str) clcd_cmd_write(*str++, CHAR_MODE);
}