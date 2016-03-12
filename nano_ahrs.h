#include<iom128v.h>

#ifndef __NANO_AHRS_H__
#define __NANO_AHRS_H__

void calc_pole_angle();
void acc_dirct_convert();
void calc_plate_angle();
void read_sensor();
void get_init_state();
void calc_angle_move();
void sensor_init();

#endif