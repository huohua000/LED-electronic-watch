#include "headfile.h"
//int aa=0;
void main()
{
	DisableGlobalIRQ();		//关闭总中断
	board_init();		//寄存器初始化
	//此处编写用户代码
  P2=0xff;
	DS1302_SetTime();
	W1=1;//关闭
	W2=1;
	W3=1;
	W4=1;	
	INT2_init();
	gpio_pull_set(P3_2,PULLUP);
	gpio_pull_set(P3_3,PULLUP);
	gpio_pull_set(P3_4,PULLUP);
	gpio_pull_set(P3_6,PULLUP);
  pca_init_interrupt_ms(PCA_1,1);	
	EnableGlobalIRQ();	//开启总中断
    while(1)
	{
		
  }
}



