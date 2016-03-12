#ifndef __DEF_H__
#define __DEF_H__

#define uchar unsigned char
#define uint unsigned int

/***********ľ�����(cm)**************/
#define a 110	//��
#define b 115	//��
#define L1 116
#define L2 149
#define R 25
#define START_POINT 6
#define OFFSET 9
#define PER_STEP_1 207.5
#define PER_STEP_2 203.5

/***************��������*****************/
#define MOD (PIND&0x01)
#define SHU (PIND&0x02)
#define OK  (PIND&0x04)


/************1602LCD��������************/
/*#define RS_1 PORTA|=BIT(5)
#define RS_0 PORTA&=~BIT(5)

#define RW_1 PORTA|=BIT(6)
#define RW_0 PORTA&=~BIT(6)

#define E_1 PORTA|=BIT(7)
#define E_0 PORTA&=~BIT(7)*/

//#define EN_0 PORTF&=~BIT(3);
//#define EN_1 PORTF|=BIT(3);
//#define RS_C PORTF&=~BIT(2);
//#define RS_D PORTF|=BIT(2);

/**************��翪��****************/
#define NO_1 (PINF&(1<<0))
#define NO_2 (PINF&(1<<1))
#define NO_3 (PINF&(1<<2))
#define NO_4 (PINF&(1<<3))


#define DOWN (PINA&(1<<0))

#define LEFT (PIND&(1<<1))
#define RIGHT (PIND&(1<<2))

/************��������������*************/
/*#define Trig_1 PORTB|=BIT(2)
#define Trig_0 PORTB&=~BIT(2)
#define Echo (PINB&BIT(3))*/


/************���ɰڲ���**************/
#define g 			9.8				//�������ٶ�
#define THRESHOLD	0.07			//���ڼ�����ɰڷ���ʱ���ٶȱ仯������ֵ
#define ERROR		-2				//��ʼλ�����ɰ������ֱλ�����	

typedef union
{
	uchar data_trans[4];		//���������ֽڴ���
	float data_use;				//ֱ��ʹ�õ�����
}float_data;

#endif