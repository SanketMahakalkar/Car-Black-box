#ifndef CLCD_H
#define CLCD_H

#define _XTAL_FREQ                  20000000 

/* Hardware Port Mapping */
#define CLCD_DATA_PORT_DDR          TRISD
#define CLCD_RS_DDR                 TRISE2
#define CLCD_EN_DDR                 TRISE1

#define CLCD_DATA_PORT              PORTD
#define CLCD_RS                     RE2
#define CLCD_EN                     RE1

#define COMMAND_MODE                0
#define CHAR_MODE                   1

#define HIGH                        1
#define LOW                         0

#define ROW1(x)                    (0x80 + x)
#define ROW2(x)                    (0xC0 + x)

/* Display Commands */
#define MODE_8BIT                   0x33
#define DUAL_LINE_5x8               0x38
#define CLEAR_SCREEN                0x01
#define DISP_ON_NO_CURSOR           0x0C
#define DISP_ON_WITH_CURSOR         0x0F
#define START_CURSOR_POS            0xC6

void setup_clcd(void);
void clcd_send_char(const char data, unsigned char addr);
void clcd_print_string(const char *str, unsigned char addr);
void clcd_cmd_write(unsigned char byte, unsigned char mode);

#endif