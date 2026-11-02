#include "input_processing.h"
#include "global.h"
#include "timer.h"
#include "input_reading.h"
#include "display7SEG.h"

//static int sub_status_changed = 1;

void clearAllLEDs(void) {
    HAL_GPIO_WritePin(GPIOA, REDns_Pin | YELLOWns_Pin | GREENns_Pin
                           | REDwe_Pin | YELLOWwe_Pin | GREENwe_Pin, GPIO_PIN_SET);
}

void update_traffic_leds(void) {
    clearAllLEDs();

    if (status_ns == STATE_GREEN) {
        HAL_GPIO_WritePin(GPIOA, GREENns_Pin, GPIO_PIN_RESET);
    } else if (status_ns == STATE_YELLOW) {
        HAL_GPIO_WritePin(GPIOA, YELLOWns_Pin, GPIO_PIN_RESET);
    } else if (status_ns == STATE_RED) {
        HAL_GPIO_WritePin(GPIOA, REDns_Pin, GPIO_PIN_RESET);
    }

    if (status_we == STATE_GREEN) {
        HAL_GPIO_WritePin(GPIOA, GREENwe_Pin, GPIO_PIN_RESET);
    } else if (status_we == STATE_YELLOW) {
        HAL_GPIO_WritePin(GPIOA, YELLOWwe_Pin, GPIO_PIN_RESET);
    } else if (status_we == STATE_RED) {
        HAL_GPIO_WritePin(GPIOA, REDwe_Pin, GPIO_PIN_RESET);
    }
}

void fsm_for_input_processing(void) {
	switch (status) {
	        case INIT:
	            status = MODE1;
	            status_ns = STATE_RED;
	            count_ns = Red_max;

	            status_we = STATE_GREEN;
	            count_we = Green_max;

	            update_traffic_leds();
	            update7SEGBuffer(count_ns, count_we);
	            setTimer1(1000);
	            break;

	        case MODE1:
	            if (timer1_flag == 1) {
	                setTimer1(1000);

	                count_ns--;
	                if (count_ns <= 0) {
	                    if (status_ns == STATE_RED) {
	                        status_ns = STATE_GREEN;
	                        count_ns = Green_max;
	                    } else if (status_ns == STATE_GREEN) {
	                        status_ns = STATE_YELLOW;
	                        count_ns = Amber_max;
	                    } else if (status_ns == STATE_YELLOW) {
	                        status_ns = STATE_RED;
	                        count_ns = Red_max;
	                    }
	                }

	                count_we--;
	                if (count_we <= 0) {
	                    if (status_we == STATE_RED) {
	                        status_we = STATE_GREEN;
	                        count_we = Green_max;
	                    } else if (status_we == STATE_GREEN) {
	                        status_we = STATE_YELLOW;
	                        count_we = Amber_max;
	                    } else if (status_we == STATE_YELLOW) {
	                        status_we = STATE_RED;
	                        count_we = Red_max;
	                    }
	                }

	                // Cập nhật LED giao thông và LED 7 đoạn
	                update_traffic_leds();
	                update7SEGBuffer(count_ns, count_we);
	            }

	            // Chuyển Mode 2 khi bấm BT0 (index 0)
	            if (is_button_pressed(0)) {
	                clearAllLEDs();
	                status = MODE2;
	                temp_value = Red_max;
	                setTimer2(250);
	            }
	            break;

        case MODE2:
                    if (timer2_flag == 1) {
                        setTimer2(250);

                        HAL_GPIO_WritePin(GPIOA, GREENns_Pin | YELLOWns_Pin | GREENwe_Pin | YELLOWwe_Pin, GPIO_PIN_SET);

                        HAL_GPIO_TogglePin(GPIOA, REDns_Pin | REDwe_Pin);
                    }
                    update7SEGBuffer(2, temp_value);

                    if (is_button_pressed(1)) {
                        temp_value++;
                        if (temp_value > 99) temp_value = 1;
                    }
                    if (is_button_pressed(2)) {
                        Red_max = temp_value;
                    }
                    if (is_button_pressed(0)) {
                        clearAllLEDs();
                        status = MODE3;
                        temp_value = Amber_max;
                        setTimer2(250);
                    }
                    break;

                case MODE3:
                    if (timer2_flag == 1) {
                        setTimer2(250);

                        HAL_GPIO_WritePin(GPIOA, REDns_Pin | GREENns_Pin | REDwe_Pin | GREENwe_Pin, GPIO_PIN_SET);

                        HAL_GPIO_TogglePin(GPIOA, YELLOWns_Pin | YELLOWwe_Pin);
                    }
                    update7SEGBuffer(3, temp_value);

                    if (is_button_pressed(1)) {
                        temp_value++;
                        if (temp_value > 99) temp_value = 1;
                    }
                    if (is_button_pressed(2)) {
                        Amber_max = temp_value;
                    }
                    if (is_button_pressed(0)) {
                        clearAllLEDs();
                        status = MODE4;
                        temp_value = Green_max;
                        setTimer2(250);
                    }
                    break;

                case MODE4:
                    if (timer2_flag == 1) {
                        setTimer2(250);

                        HAL_GPIO_WritePin(GPIOA, REDns_Pin | YELLOWns_Pin | REDwe_Pin | YELLOWwe_Pin, GPIO_PIN_SET);

                        HAL_GPIO_TogglePin(GPIOA, GREENns_Pin | GREENwe_Pin);
                    }
                    update7SEGBuffer(4, temp_value);

                    if (is_button_pressed(1)) {
                        temp_value++;
                        if (temp_value > 99) temp_value = 1;
                    }
                    if (is_button_pressed(2)) {
                        Green_max = temp_value;
                    }
                    if (is_button_pressed(0)) {
                        clearAllLEDs();
                        status = INIT;
                    }
                    break;
    }
}
