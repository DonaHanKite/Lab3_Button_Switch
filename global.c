#include "global.h"

int status = INIT;
int sub_status = AUTO_RED_GREEN;
int temp_value = 0;
int Red_max = 5;
int Amber_max = 2;
int Green_max = 3;
int count_ns = 0;
int count_we = 0;
int led_buffer[4] = {0, 0, 0, 0};

int status_ns = STATE_RED;
int status_we = STATE_GREEN;
