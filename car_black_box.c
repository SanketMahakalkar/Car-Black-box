#include "main.h"

unsigned char rtc_buffer[3];
char timestamp[7];
char record[11];
char storage_idx = -1;
int total_events = 0;

extern unsigned char sec;
extern unsigned char return_time;

char *options[] = {"View log", "Clear log", "Change passwrd"};

static void update_time_strings(void) {
    rtc_buffer[0] = get_rtc_data(ADDR_HOUR);
    rtc_buffer[1] = get_rtc_data(ADDR_MIN);
    rtc_buffer[2] = get_rtc_data(ADDR_SEC);
    timestamp[0] = ((rtc_buffer[0] >> 4) & 0x03) + '0';
    timestamp[1] = (rtc_buffer[0] & 0x0F) + '0';
    timestamp[2] = ((rtc_buffer[1] >> 4) & 0x07) + '0';
    timestamp[3] = (rtc_buffer[1] & 0x0F) + '0';
    timestamp[4] = ((rtc_buffer[2] >> 4) & 0x07) + '0';
    timestamp[5] = (rtc_buffer[2] & 0x0F) + '0';
    timestamp[6] = '\0';
}

void show_dashboard(char event[], unsigned char speed) {
    clcd_print_string("  TIME     E  SP", ROW1(0));
    update_time_strings();
    clcd_send_char(timestamp[0], ROW2(2));
    clcd_send_char(timestamp[1], ROW2(3));
    clcd_send_char(':', ROW2(4));
    clcd_send_char(timestamp[2], ROW2(5));
    clcd_send_char(timestamp[3], ROW2(6));
    clcd_send_char(':', ROW2(7));
    clcd_send_char(timestamp[4], ROW2(8));
    clcd_send_char(timestamp[5], ROW2(9));
    
    clcd_print_string(event, ROW2(11));
    clcd_send_char((speed / 10) + '0', ROW2(14));
    clcd_send_char((speed % 10) + '0', ROW2(15));
}

void record_event(char event[], unsigned char speed) {
    update_time_strings();
    strncpy(record, timestamp, 6);
    strncpy(&record[6], event, 2);
    record[8] = (speed / 10) + '0';
    record[9] = (speed % 10) + '0';
    record[10] = '\0';
    
    unsigned char addr;
    storage_idx++;
    if (storage_idx == 10) storage_idx = 0;
    
    addr = storage_idx * 10 + 5;
    for (int i = 0; record[i] != '\0'; i++) {
        eeprom_write(addr++, record[i]);
    }
    if (total_events < 9) total_events++;
}

void refresh_screen(void) {
    clcd_cmd_write(CLEAR_SCREEN, COMMAND_MODE);
    __delay_us(100);
}

char validate_login(unsigned char key, unsigned char rst_flag) {
    static char input_pwd[4];
    static unsigned char tries, p_idx;
    char saved_pwd[4];
    
    if (rst_flag == RESET_PWD_ENTRY) {
        return_time = 5;
        tries = '3';
        p_idx = 0;
        key = NO_KEY;
    }
    if (return_time == 0) return BACK_SIGNAL;
    
    if (key == BUTTON_4 && p_idx < 4) {
        input_pwd[p_idx++] = '4';
        clcd_send_char('*', ROW2(6 + p_idx - 1));
        return_time = 5;
    } else if (key == BUTTON_5 && p_idx < 4) {
        input_pwd[p_idx++] = '2';
        clcd_send_char('*', ROW2(6 + p_idx - 1));
        return_time = 5;
    }
    
    if (p_idx == 4) {
        for (int j = 0; j < 4; j++) saved_pwd[j] = eeprom_read(j);
        if (strncmp(input_pwd, saved_pwd, 4) == 0) return OP_COMPLETE;
        
        tries--;
        if (tries == '0') {
            clcd_cmd_write(DISP_ON_NO_CURSOR, COMMAND_MODE);
            clcd_print_string(" System Locked  ", ROW1(0));
            sec = 60;
            while (sec != 0) {
                clcd_send_char((sec / 10) + '0', ROW2(11));
                clcd_send_char((sec % 10) + '0', ROW2(12));
            }
            tries = '3';
        } else {
            refresh_screen();
            clcd_print_string(" ACCESS DENIED  ", ROW1(0));
            clcd_send_char(tries, ROW2(0));
            clcd_print_string(" tries left", ROW2(1));
            __delay_ms(3000);
        }
        refresh_screen();
        clcd_print_string(" ENTER PASSWORD ", ROW1(0));
        clcd_cmd_write(START_CURSOR_POS, COMMAND_MODE);
        clcd_cmd_write(DISP_ON_WITH_CURSOR, COMMAND_MODE);
        p_idx = 0;
        return_time = 5;
    }
    return 0x10;
}

char access_menu(unsigned char key, unsigned char rst_flag) {
    static char selection;
    if (rst_flag == RESET_MENU_NAV) selection = 0;
    
    if (key == BUTTON_5 && selection < 2) {
        selection++;
        refresh_screen();
    } else if (key == BUTTON_4 && selection > 0) {
        selection--;
        refresh_screen();
    }
    
    if (selection < 2) {
        clcd_send_char('*', ROW1(0));
        clcd_print_string(options[selection], ROW1(2));
        clcd_print_string(options[selection + 1], ROW2(2));
    } else {
        clcd_print_string(options[selection - 1], ROW1(2));
        clcd_print_string(options[selection], ROW2(2));
        clcd_send_char('*', ROW2(0));
    }
    return selection;
}

void display_logs(unsigned char key, unsigned char rst_flag) {
    char entry[11];
    static unsigned char scroll_pos;
    if (total_events == -1) {
        clcd_print_string(" Log Empty", ROW2(0));
    } else {
        if (rst_flag == RESET_LOG_VIEW) scroll_pos = 0;
        if (key == BUTTON_5 && scroll_pos < (total_events - 1)) scroll_pos++;
        else if (key == BUTTON_4 && scroll_pos > 0) scroll_pos--;
        
        for (int i = 0; i < 10; i++) {
            entry[i] = eeprom_read((scroll_pos * 10 + 5) + i);
        }
        clcd_send_char(scroll_pos % 10 + '0', ROW2(0));
        clcd_send_char(entry[0], ROW2(2));
        clcd_send_char(entry[1], ROW2(3));
        clcd_send_char(':', ROW2(4));
        clcd_send_char(entry[2], ROW2(5));
        clcd_send_char(entry[3], ROW2(6));
        clcd_send_char(':', ROW2(7));
        clcd_send_char(entry[4], ROW2(8));
        clcd_send_char(entry[5], ROW2(9));
        clcd_send_char(entry[6], ROW2(11));
        clcd_send_char(entry[7], ROW2(12));
        clcd_send_char(entry[8], ROW2(14));
        clcd_send_char(entry[9], ROW2(15));
    }
}

char delete_all_logs(unsigned char rst_flag) {
    if (rst_flag == RESET_EEPROM_STORAGE) {
        total_events = -1;
        storage_idx = -1;
        clcd_print_string(" Clearing...    ", ROW1(0));
        __delay_ms(2000);
        return OP_COMPLETE;
    }
    return OP_FAILED;
}

char update_password(unsigned char key, unsigned char rst_flag) {
    static char buf[9];
    static int p, step;
    if (rst_flag == RESET_PWD_CHANGE) { p = 0; step = 1; }
    
    if (p < 4 && step) {
        step = 0;
        clcd_print_string("New Password:", ROW1(0));
        clcd_cmd_write(ROW2(0), COMMAND_MODE);
        clcd_cmd_write(DISP_ON_WITH_CURSOR, COMMAND_MODE);
    } else if (p >= 4 && step == 0) {
        step = 1;
        refresh_screen();
        clcd_print_string("Confirm Pwd:", ROW1(0));
        clcd_cmd_write(ROW2(0), COMMAND_MODE);
    }
    
    if (key == BUTTON_4) { buf[p] = '4'; clcd_send_char('*', ROW2(p % 4)); p++; }
    else if (key == BUTTON_5) { buf[p] = '2'; clcd_send_char('*', ROW2(p % 4)); p++; }
    
    if (p == 8) {
        if (strncmp(buf, &buf[4], 4) == 0) {
            for (int i = 0; i < 4; i++) eeprom_write(i, buf[i]);
            refresh_screen();
            clcd_print_string(" Updated!       ", ROW1(0));
            __delay_ms(2000);
            return OP_COMPLETE;
        } else {
            refresh_screen();
            clcd_print_string(" Match Failed   ", ROW1(0));
            __delay_ms(2000);
            return OP_COMPLETE;
        }
    }
    return 0x10;
}