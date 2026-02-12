#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H

#define MODE_LEVEL              0
#define MODE_STATE              1

#define KEYPAD_PORT             PORTB
#define KEYPAD_PORT_DDR         TRISB
#define MASK_INPUTS             0x3F

/* Key Map */
#define BUTTON_1                0x3E
#define BUTTON_2                0x3D
#define BUTTON_3                0x3B
#define BUTTON_4                0x37
#define BUTTON_5                0x2F
#define BUTTON_6                0x1F

#define NO_KEY                  MASK_INPUTS

unsigned char get_key(unsigned char detection_mode);
void setup_keypad(void);

#endif