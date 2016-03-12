#include<iom128v.h>
#include<MATH.H>
#include"def.h"
#include"lib.h"
#include"usart.h"

float_data X_acc={0},Y_acc={0},Z_acc={0};							  //加速度计测得的加速度

float_data X_mag={0},Y_mag={0},Z_mag={0};							  //磁感应计测得的磁场强度

float_data X_gyr={0},Y_gyr={0},Z_gyr={0};							  //陀螺仪测得的角度

float horiz_acc=0,verti_acc=0;			  				  //水平和竖直方向加速度
float horiz_acc_pre=0,verti_acc_pre=0;
		  
float_data roll={0},pitch={0},yaw={0};								  //陀螺仪测得的角度

float pole_angle=0;					  	  //杆子相对垂直位置的倾角
float plate_angle=0;						  //平板相对水平位置的倾角
float relat_angle_pre=0,relat_angle_curr=0;						  //平板与杆子之间的夹角
float angle_move=0;												  //平板与杆子之间夹角的变化量，即电机需转过的角度

extern char read_flag;			//串口接收数据类型标志，0--读取三轴加速度，1--读取角度
extern int receive_count;		//串口接收数据计数
/************************
* 传感器初始化
************************/
void sensor_init()
{
 usart1_puts("#o0");		//禁止流输出
 delayms(5);
 usart1_puts("#oc");		//进入传感器校正模式
 delayms(5);
 usart1_puts("#on");		//校正各个传感器
 delayms(5);
 usart1_puts("#on");
 delayms(5);
 usart1_puts("#on");
 delayms(5);
}

/************************
* 计算杆子相对垂直位置的倾角
************************/
void calc_pole_angle()
{
 pole_angle = (yaw.data_use-ERROR)/180*_PI;
}

/************************
* 三轴加速度计测得加速度转换为水平和竖直方向加速度
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
* 计算平板相对水平位置的倾角
************************/
void calc_plate_angle()
{
 acc_dirct_convert();
 plate_angle = atan2f(horiz_acc, 1-verti_acc);
}

/************************
* 读取当前陀螺仪与加速度传感器测得数据
************************/
void read_sensor()
{
 usart1_puts("#oscb");		//输出校正后的传感器数据
 //delayms(5);
 read_flag=0;		//读取三轴加速度
 receive_count=12;
 usart1_puts("#o1");			//使能流输出
 while(receive_count>0);
 usart1_puts("#o0");			//禁止流输出
 	
 usart1_puts("#ob");		//输出角度
 //delayms(5);
 read_flag=1;		//读取角度
 receive_count=12;
 usart1_puts("#o1");			//使能流输出
 while(receive_count>0);
 usart1_puts("#o0");			//禁止流输出
}

/************************
* 获得自由摆初始状态
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
 while(((verti_acc-verti_acc_pre)<THRESHOLD)&&((verti_acc_pre-verti_acc)<THRESHOLD))  		//没有检测到放下时的加速度
 {
  read_sensor();
  calc_pole_angle();
  acc_dirct_convert();
  verti_acc_pre=verti_acc;
 }
 relat_angle_pre=_PI/2+pole_angle;
}

/************************
* 计算电机需要转过的角度
************************/
void calc_angle_move()
{
 calc_pole_angle();
 calc_plate_angle();
 relat_angle_curr = _PI/2-plate_angle+pole_angle;					
 angle_move       = relat_angle_curr-relat_angle_pre;
}
