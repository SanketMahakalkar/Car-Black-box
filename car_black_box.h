#ifndef CAR_BLACK_BOX_H
#define CAR_BLACK_BOX_H

/* Core Dashboard and Logging Operations */
void show_dashboard(char event[], unsigned char speed);
void record_event(char event[], unsigned char speed);
void refresh_screen(void);

/* Authentication and User Interface Menus */
char validate_login(unsigned char key, unsigned char rst_flag);
char access_menu(unsigned char key, unsigned char rst_flag);
void display_logs(unsigned char key, unsigned char rst_flag);
char delete_all_logs(unsigned char rst_flag);
char update_password(unsigned char key, unsigned char rst_flag);

#endif