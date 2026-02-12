/* 
 * File:   ds1307.h
 * Author: sanket
 *
 * Created on 7 January, 2025, 8:06 PM
 */
#ifndef DS1307_H
#define DS1307_H

#define RTC_WRITE_ADDR          0xD0 
#define RTC_READ_ADDR           0xD1 

#define ADDR_SEC                0x00
#define ADDR_MIN                0x01
#define ADDR_HOUR               0x02

void setup_ds1307(void);
unsigned char get_rtc_data(unsigned char addr);
void set_rtc_data(unsigned char addr, unsigned char data);

#endif