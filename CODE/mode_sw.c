#include "headfile.h"
#define EX2 0x10
int sleep_mode_counter=0;
int wake_counter=0;
char wake_flag=0;
int vibration_counter=0;
char X8_last=0; 

void INT2_init()
{
  INTCLKO = EX2; 
	
	WKTCL = 0xff;         // 设置掉电唤醒时钟约为1s
	WKTCH = 0x87;	
  _nop_();
  _nop_();
	EA=1;
	PCON = 0x02; //MCU 掉电模式
	
}
void sleep_mode()
{
	W1=1;
	W2=1;
	W3=1;
	W4=1;	
	P2=1;
	P27=1;
	PCON = 0x02; //MCU 掉电模式
//	PCON = PD; 
  _nop_();
  _nop_();

	
}
void mode_sw()
{
	if(wake_flag==1)
	{
		PCON = 0x00;
		display_menu();//醒来
		wake_counter++;
		if(wake_counter>3000)
		{
			wake_counter=0;
			wake_flag=0;
		}
	}
	else//掉电模式
	{
	W1=1;
	W2=1;
	W3=1;
	W4=1;	
		P2=1;
		P27=1;
		sleep_mode_counter++;
		if(X8!=X8_last)
		{
			X8_last=X8;
			vibration_counter++;
		}
		if(sleep_mode_counter>1500)
		{
			if(vibration_counter<10)
			{
				sleep_mode();
			}
			else
			{
				wake_flag=1;			
				wake_counter=0;
			}
				sleep_mode_counter=0;
				vibration_counter=0;
		}
	}
}