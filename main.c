/*
 * File:   main.c
 * Author: sanket
 *
 * Created on 7 January, 2025, 8:05 PM
 */

#include <xc.h>
#include "main.h"

#pragma config WDTE = OFF

char *gears[] = {"GN", "GR", "G1", "G2", "G3", "G4"};

static void initialize_system(void) {
    setup_clcd();
    setup_i2c(100000);
    setup_ds1307();
    setup_adc();
    setup_keypad();
    setup_timer2();
    PEIE = 1;
    GIE = 1;
}

void main(void) {
    char current_event[3] = "ON";
    unsigned char velocity = 0;
    unsigned char system_state = STATE_DASHBOARD;
    unsigned char input_key, rst, choice;
    unsigned char gear_idx = 0;

    initialize_system();
    record_event(current_event, velocity);
    
    // Default Pwd setup
    eeprom_write(0x00, '2');
    eeprom_write(0x01, '4');
    eeprom_write(0x02, '2');
    eeprom_write(0x03, '4');

    while (1) {
        velocity = get_adc_value() / 10;
        if (velocity > 99) velocity = 99;
        
        input_key = get_key(MODE_STATE);
        for (int i = 3000; i--;); // Small debounce

        if (input_key == BUTTON_1) {
            strcpy(current_event, "C ");
            record_event(current_event, velocity);
        } else if (input_key == BUTTON_2 && gear_idx < 6) {
            strcpy(current_event, gears[gear_idx++]);
            record_event(current_event, velocity);
        } else if (input_key == BUTTON_3 && gear_idx > 0) {
            strcpy(current_event, gears[--gear_idx]);
            record_event(current_event, velocity);
        } else if ((system_state == STATE_DASHBOARD) && (input_key == BUTTON_4 || input_key == BUTTON_5)) {
            refresh_screen();
            clcd_print_string(" ENTER PASSWORD ", ROW1(0));
            clcd_cmd_write(START_CURSOR_POS, COMMAND_MODE);
            clcd_cmd_write(DISP_ON_WITH_CURSOR, COMMAND_MODE);
            system_state = STATE_LOGIN;
            rst = RESET_PWD_ENTRY;
            TMR2ON = 1;
        } else if (system_state == STATE_MENU && (input_key == BUTTON_6)) {
            switch (choice) {
                case 0:
                    refresh_screen();
                    clcd_print_string("# TIME     E  SP", ROW1(0));
                    system_state = STATE_VIEW_LOG;
                    rst = RESET_LOG_VIEW;
                    break;
                case 1:
                    record_event("CL", velocity);
                    refresh_screen();
                    system_state = STATE_CLEAR_LOG;
                    rst = RESET_EEPROM_STORAGE;
                    break;
                case 2:
                    record_event("CP", velocity);
                    refresh_screen();
                    system_state = STATE_CHANGE_PWD;
                    rst = RESET_PWD_CHANGE;
                    break;
            }
        }

        switch (system_state) {
            case STATE_DASHBOARD:
                show_dashboard(current_event, velocity);
                break;
            case STATE_LOGIN:
                switch (validate_login(input_key, rst)) {
                    case BACK_SIGNAL:
                        system_state = STATE_DASHBOARD;
                        TMR2ON = 0;
                        clcd_cmd_write(DISP_ON_NO_CURSOR, COMMAND_MODE);
                        break;
                    case OP_COMPLETE:
                        system_state = STATE_MENU;
                        rst = RESET_MENU_NAV;
                        refresh_screen();
                        clcd_cmd_write(DISP_ON_NO_CURSOR, COMMAND_MODE);
                        TMR2ON = 0;
                        continue;
                }
                break;
            case STATE_MENU:
                choice = access_menu(input_key, rst);
                break;
            case STATE_VIEW_LOG:
                display_logs(input_key, rst);
                break;
            case STATE_CLEAR_LOG:
                if (delete_all_logs(rst) == OP_COMPLETE) {
                    refresh_screen();
                    system_state = STATE_MENU;
                    rst = RESET_MENU_NAV;
                    continue;
                }
                break;
            case STATE_CHANGE_PWD:
                if (update_password(input_key, rst) == OP_COMPLETE) {
                    refresh_screen();
                    clcd_cmd_write(DISP_ON_NO_CURSOR, COMMAND_MODE);
                    system_state = STATE_MENU;
                    rst = RESET_MENU_NAV;
                    continue;
                }
                break;
        }
        rst = REFRESH_OFF;
    }
}