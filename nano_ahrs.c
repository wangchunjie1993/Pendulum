#include<iom128v.h>
#include<MATH.H>
#include"def.h"
#include"lib.h"
#include"usart.h"

float_data X_acc={0},Y_acc={0},Z_acc={0};							  //���ٶȼƲ�õļ��ٶ�

float_data X_mag={0},Y_mag={0},Z_mag={0};							  //�Ÿ�Ӧ�Ʋ�õĴų�ǿ��

float_data X_gyr={0},Y_gyr={0},Z_gyr={0};							  //�����ǲ�õĽǶ�

float horiz_acc=0,verti_acc=0;			  				  //ˮƽ����ֱ������ٶ�
float horiz_acc_pre=0,verti_acc_pre=0;
		  
float_data roll={0},pitch={0},yaw={0};								  //�����ǲ�õĽǶ�

float pole_angle=0;					  	  //������Դ�ֱλ�õ����
float plate_angle=0;						  //ƽ�����ˮƽλ�õ����
float relat_angle_pre=0,relat_angle_curr=0;						  //ƽ�������֮��ļн�
float angle_move=0;												  //ƽ�������֮��нǵı仯�����������ת���ĽǶ�

extern char read_flag;			//���ڽ����������ͱ�־��0--��ȡ������ٶȣ�1--��ȡ�Ƕ�
extern int receive_count;		//���ڽ������ݼ���
/************************
* ��������ʼ��
************************/
void sensor_init()
{
 usart1_puts("#o0");		//��ֹ�����
 delayms(5);
 usart1_puts("#oc");		//���봫����У��ģʽ
 delayms(5);
 usart1_puts("#on");		//У������������
 delayms(5);
 usart1_puts("#on");
 delayms(5);
 usart1_puts("#on");
 delayms(5);
}

/************************
* ���������Դ�ֱλ�õ����
************************/
void calc_pole_angle()
{
 pole_angle = (yaw.data_use-ERROR)/180*_PI;
}

/************************
* ������ٶȼƲ�ü��ٶ�ת��Ϊˮƽ����ֱ������ٶ�
************************/
void acc_dirct_convert()
{
 float a1=0,a2=0;
 
 calc_pole_angle();
 
 X_acc.data_use*=0.004;
 Y_acc.data_use*=0.004;
 Z_acc.data_use*=0.004;
 
 a1=Y_acc.data_use-sinf(pole_angle);
 a2=cosf(pole_angle)-Z_acc.data_use;
 
 horiz_acc = a2*sinf(pole_angle)-a1*cosf(pole_angle);
 verti_acc = a2*cosf(pole_angle)+a1*sinf(pole_angle);
}

/************************
* ����ƽ�����ˮƽλ�õ����
************************/
void calc_plate_angle()
{
 acc_dirct_convert();
 plate_angle = atan2f(horiz_acc, 1-verti_acc);
}

/************************
* ��ȡ��ǰ����������ٶȴ������������
************************/
void read_sensor()
{
 usart1_puts("#oscb");		//���У����Ĵ���������
 //delayms(5);
 read_flag=0;		//��ȡ������ٶ�
 receive_count=12;
 usart1_puts("#o1");			//ʹ�������
 while(receive_count>0);
 usart1_puts("#o0");			//��ֹ�����
 	
 usart1_puts("#ob");		//����Ƕ�
 //delayms(5);
 read_flag=1;		//��ȡ�Ƕ�
 receive_count=12;
 usart1_puts("#o1");			//ʹ�������
 while(receive_count>0);
 usart1_puts("#o0");			//��ֹ�����
}

/************************
* ������ɰڳ�ʼ״̬
************************/
void get_init_state()
{
 read_sensor();
 acc_dirct_convert();
 //horiz_acc_pre=horiz_acc;
 verti_acc_pre=verti_acc;
 
 read_sensor();
 acc_dirct_convert();
 
 calc_pole_angle();
 while(((verti_acc-verti_acc_pre)<THRESHOLD)&&((verti_acc_pre-verti_acc)<THRESHOLD))  		//û�м�⵽����ʱ�ļ��ٶ�
 {
  read_sensor();
  calc_pole_angle();
  acc_dirct_convert();
  verti_acc_pre=verti_acc;
 }
 relat_angle_pre=_PI/2+pole_angle;
}

/************************
* ��������Ҫת���ĽǶ�
************************/
void calc_angle_move()
{
 calc_pole_angle();
 calc_plate_angle();
 relat_angle_curr = _PI/2-plate_angle+pole_angle;					
 angle_move       = relat_angle_curr-relat_angle_pre;
}
