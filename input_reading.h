/*
 * input_processing.h
 *
 *  Created on: Oct 27, 2026
 *      Author: ACER
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

#define NO_OF_BUTTONS 3

#define BUTTON_IS_PRESSED  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

void button_reading(void);

int is_button_pressed(unsigned char index);

#endif /* INC_INPUT_READING_H_ */
