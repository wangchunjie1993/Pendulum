#include<iom128v.h>
#include"def.h"
#include"lib.h"

int ctc_count=0;

void motor_init()
{
 TCCR0=0x00;
 TCNT0=0x00;
 OCR0=0x58;
 TCCR0|=(7<<2);
}

void left_move(int count)
{
 ctc_count=count;
 PORTA|=(1<<0);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 while(ctc_count>0);
 DDRB&=~(1<<4);
 TIMSK&=~(1<<1);
}

void right_move(int count)
{
 ctc_count=count;
 PORTA&=~(1<<0);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 while(ctc_count>0);
 DDRB&=~(1<<4);
 TIMSK&=~(1<<1);
}

void move(int angle)
{
 if(angle>0)
  left_move(angle*8.89);
 else 
  right_move(-angle*8.89);
}
