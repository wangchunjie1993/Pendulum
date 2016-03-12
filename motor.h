#include<iom128v.h>

#ifndef __MOTOR_H__
#define __MOTOR_H__

void motor_init();
void left_move(int count);
void right_move(int count);
void move(int angle);

#endif