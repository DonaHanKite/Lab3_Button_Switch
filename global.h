#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

#define INIT   0
#define MODE1  1
#define MODE2  2
#define MODE3  3
#define MODE4  4

#define AUTO_RED_GREEN   11
#define AUTO_RED_YELLOW  12
#define AUTO_GREEN_RED   13
#define AUTO_YELLOW_RED  14

extern int status;
extern int sub_status;
extern int temp_value;
extern int Red_max;
extern int Amber_max;
extern int Green_max;
extern int count_ns;
extern int count_we;
extern int led_buffer[4];

// Trạng thái độc lập cho từng hướng
#define STATE_GREEN   0
#define STATE_YELLOW  1
#define STATE_RED     2

extern int status_ns; // Trạng thái hiện tại của Bắc-Nam
extern int status_we; // Trạng thái hiện tại của Đông-Tây

#endif /* INC_GLOBAL_H_ */
