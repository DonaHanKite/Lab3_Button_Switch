/*
 * timer.h
 *
 *  Created on: Oct 27, 2026
 *      Author: ACER
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;

void setTimer0(int duration);
void setTimer1(int duration);
void setTimer2(int duration);

void timerRun(void);

#endif /* INC_TIMER_H_ */
