#include<iom128v.h>
#include"def.h"

uchar data_rx=0;				//串口接收到的数据

char read_flag=0;			//串口接收数据类型标志，0--读取三轴加速度，1--读取角度
int receive_count=0;			//串口接收数据计数

extern float_data X_acc,Y_acc,Z_acc;
extern float_data roll,pitch,yaw;
uchar temp;
/***************
* usart0
***************/
void usart0_init(uint baud)
{
	UBRR0H=baud<<8;
	UBRR0L=baud;
	UCSR0B|=(1<<7)|(1<<4)|(1<<3);
	UCSR0C|=(3<<0);
}

void usart0_transmit(uchar data)
{
	while(!(UCSR0A&(1<<5)));
	UDR0=data;
}

void usart0_puts(uchar *str)
{
	while(*str)
	{
		usart0_transmit(*str++);
	}
}

#pragma interrupt_handler usart0_receive_isr:19
void usart0_receive_isr()
{
	//uchar data_rx;
	data_rx=UDR0;

}


/***************
* usart1
***************/
void usart1_init(uint baud)
{
	UBRR1H=baud<<8;
	UBRR1L=baud;
	UCSR1B|=(1<<7)|(1<<4)|(1<<3);
	UCSR1C|=(3<<0);
}

void usart1_transmit(uchar data)
{
	while(!(UCSR1A&(1<<5)));
	UDR1=data;
}

void usart1_puts(uchar *str)
{
	while(*str)
	{
		usart1_transmit(*str++);
	}
}

#pragma interrupt_handler usart1_receive_isr:31
void usart1_receive_isr()
{
	//uchar data_rx;
	//data_rx=UDR1;	
	switch(read_flag)
	{
		case 0:
		{
			if(receive_count>8)
			{
				X_acc.data_trans[12-receive_count]=UDR1;
			}
			else if(receive_count>4)
			{
				Y_acc.data_trans[8-receive_count]=UDR1;
			}
			else if(receive_count>0)
			{
				Z_acc.data_trans[4-receive_count]=UDR1;
			}
			else 
			{
				temp=UDR1;
				usart1_puts("#o0");			//禁止流输出
			}
			break;
		}
		case 1:
		{
			if(receive_count>8)
			{
				roll.data_trans[12-receive_count]=UDR1;
			}
			else if(receive_count>4)
			{
				pitch.data_trans[8-receive_count]=UDR1;
			}
			else if(receive_count>0)
			{
				yaw.data_trans[4-receive_count]=UDR1;
			}
			else 
			{
				temp=UDR1;
				usart1_puts("#o0");			//禁止流输出
			}
			break;
		}
		default:
		{
			temp=UDR1;
			usart1_puts("#o0");			//禁止流输出
			break;
		}
	}

	receive_count--;

}

