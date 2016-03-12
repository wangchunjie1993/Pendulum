#include<iom128v.h>
#include"def.h"
#include"lib.h"
#include"motor.h"
#include"nano_ahrs.h"
#include"usart.h"

extern int ctc_count;
extern float angle_move;
extern float relat_angle_pre,relat_angle_curr;
extern float_data X_acc,Y_acc,Z_acc;
extern float_data roll,pitch,yaw;
int i,j;
 
void port_init();

void main()
{
 delayms(2000);
 port_init();
 usart0_init(16);
 usart1_init(16);
 UCSR1B&=(~(1<<7))&(~(1<<4));		//关闭串口接收
 motor_init();
 sensor_init();
 UCSR1B|=(1<<4)|(1<<7);				//使能串口接收中断
 SREG=0x80;
 
 //get_init_state();

 while(1)
 {
  /*read_sensor();
  calc_angle_move();
  move(angle_move);
  
  relat_angle_pre = relat_angle_curr;*/
  left_move(3200);
  delayms(1500);
 }
 while(1);
}


void port_init()
{
 DDRA|=(1<<0);	   		//电机转向控制端口
}

#pragma interrupt_handler timer0_cmp_isr:16
void timer0_cmp_isr()
{
 ctc_count--;
}