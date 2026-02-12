/*
 * File:   newfile.c
 * Author: sanket
 *
 * Created on 20 January, 2025, 6:09 PM
 */

#include <xc.h>

void eeprom_write(unsigned char addr, unsigned char data) {
    EEADR = addr;
    EEDATA = data;
    EEPGD = 0; // Data EEPROM
    WREN = 1;  // Enable write
    EECON2 = 0x55; // Unlock sequence
    EECON2 = 0xAA;
    WR = 1;    // Start write
    while (WR); // Wait for completion
    WREN = 0;
}

unsigned char eeprom_read(unsigned char addr) {
    EEADR = addr;
    EEPGD = 0;
    RD = 1;    // Start read
    return EEDATA;
}