#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include <string.h>
#include "clcd.h"
#include "digital_keypad.h"
#include "adc.h"
#include "ds1307.h"
#include "i2c.h"
#include "car_black_box.h"
#include "timers.h"

/* Operation Status Codes */
#define SUCCESS                 0x01
#define BACK_SIGNAL             0x02
#define OP_COMPLETE             0x11
#define OP_FAILED               0x22 

/* Screen Flags */
#define STATE_DASHBOARD         0x02
#define STATE_LOGIN             0x04
#define STATE_MENU              0x06
#define STATE_VIEW_LOG          0x08
#define STATE_CLEAR_LOG         0x0A
#define STATE_CHANGE_PWD        0x0B

/* Reset Constants */
#define RESET_PWD_ENTRY         0x11
#define RESET_MENU_NAV          0x13
#define RESET_LOG_VIEW          0x15
#define RESET_EEPROM_STORAGE    0x17
#define RESET_PWD_CHANGE        0x19
#define REFRESH_OFF             0xFF

#endif