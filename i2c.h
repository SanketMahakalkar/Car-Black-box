#ifndef I2C_H
#define I2C_H

#define SYSTEM_FOSC            20000000

void setup_i2c(unsigned long baud_rate);
void i2c_trigger_start(void);
void i2c_trigger_rep_start(void);
void i2c_trigger_stop(void);
unsigned char i2c_receive_byte(unsigned char ack);
int i2c_send_byte(unsigned char data);

#endif