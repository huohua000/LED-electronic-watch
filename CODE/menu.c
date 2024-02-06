#include "headfile.h"
#define W1 P10
#define W2 P11
#define W3 P12
#define W4 P13
int sys_mode=0,disp_mode=0,disp_adjust=0;
int sequence_mode=0;
int flicker_counter=0;
int point_twinkle_counter=0;
extern unsigned char DS1302_Time[10];
void display_menu()
{
	if(sys_mode==0)////显示模式
	{
		  DS1302_ReadTime();
//////////////////////////////////////////////////////////////////////////		
		if(disp_mode==0)
		{
				point_twinkle_counter++;////分割点闪烁
			if(point_twinkle_counter<500)
				 P27=0;
			else if(point_twinkle_counter>1000)
				point_twinkle_counter=0;
			else
				P27=1;
	  }
		else
			P27=1;
////////////////////////////////////////////////////////////////////////////				
			sequence_mode++;//显示
		 if(sequence_mode==5)
			sequence_mode=1;
		 switch(disp_mode)
		 {
			 case 0:
				 disp(DS1302_Time[3]*100+DS1302_Time[4],sequence_mode);	//小时 分钟	
				 break;
			 case 1:
				 disp(DS1302_Time[6],sequence_mode);	//星期
			   break;
			 case 2:
				 disp(DS1302_Time[1]*100+DS1302_Time[2],sequence_mode);//月 日
			   break;
		 }
////////////////////////////////////////////////////////////////////////////		
		
		 switch(Key_Scan())////切换显示内容
		{
			case 1:
				sys_mode=1;
				break;			
			case 2:
				disp_mode++;
				if(disp_mode==3)
					disp_mode=0;
				break;
			case 3:
				disp_mode--;
				if(disp_mode==-1)
					disp_mode=2;
				break;			
			default:
				break;
		}
	}
	else if(sys_mode==1)//设置模式
	{
			sequence_mode++;//显示
		 if(sequence_mode==5)
			sequence_mode=1;	
		 switch(disp_mode)
		 {
			 case 0:
				 disp(DS1302_Time[3]*100+DS1302_Time[4],sequence_mode);	//小时 分钟	
				 break;
			 case 1:
				 disp(DS1302_Time[6],sequence_mode);	//星期
			   break;
			 case 2:
				 disp(DS1302_Time[1]*100+DS1302_Time[2],sequence_mode);//月 日
			   break;
			default:
				break;			 
		 }
////////////////////////////////////////////////////////////////////////////		 
		 if(disp_adjust==0)////选中时闪烁
		 {
			 flicker_counter++;
			 if(flicker_counter<500)
			 {
					W1=1;
					W2=1;	
			 }
			 else if(flicker_counter>1000)
			 flicker_counter=0;			 
		 }
		 else if(disp_adjust==1)
		 {
			 flicker_counter++;
			 if(flicker_counter<500)
			 {
					W3=1;
					W4=1;	
			 }
			 else if(flicker_counter>1000)
			 flicker_counter=0;			 
		 }			 
////////////////////////////////////////////////////////////////////////////		 
		 switch(Key_Scan())////按键
		{
			case 1:
				disp_adjust++;
			if(disp_adjust==2||(disp_adjust==1&&disp_mode==1))
			{
				sys_mode=0;
				disp_adjust=0;
				DS1302_SetTime();
			}
				break;			
			case 2://加
			if(disp_adjust==0)//右侧数据
			{
				switch(disp_mode)
				{
					case 0:
						DS1302_Time[4]++;
					if(DS1302_Time[4]>60)
						DS1302_Time[4]=0;
					  break;
					case 1:
						DS1302_Time[6]++;
					if(DS1302_Time[6]>7)
						DS1302_Time[6]=0;
					  break;
					case 2:
						DS1302_Time[2]++;
					  break;
				}
			}
			else if(disp_adjust==1)//左侧数据
			{
				switch(disp_mode)
				{
					case 0:
						DS1302_Time[3]++;
					if(DS1302_Time[3]>24)
						DS1302_Time[3]=0;
					  break;
					case 1:
						DS1302_Time[6]++;
					if(DS1302_Time[6]>7)
						DS1302_Time[6]=0;
					  break;
					case 2:
						DS1302_Time[1]++;
					if(DS1302_Time[1]>12)
						DS1302_Time[1]=1;
					  break;
				}				
			}
				
				break;
			case 3://减
			if(disp_adjust==0)//右侧数据
			{
				switch(disp_mode)
				{
					case 0:
						DS1302_Time[4]--;
					if(DS1302_Time[4]<0)
						DS1302_Time[4]=60;
					  break;
					case 1:
						DS1302_Time[6]--;
					if(DS1302_Time[6]<1)
						DS1302_Time[6]=7;
					  break;
					case 2:
						DS1302_Time[2]--;
					if(DS1302_Time[2]<1)
						DS1302_Time[2]=1;
					  break;
				}
			}
			else if(disp_adjust==1)//左侧数据
			{
				switch(disp_mode)
				{
					case 0:
						DS1302_Time[3]--;
					if(DS1302_Time[3]<0)
						DS1302_Time[3]=24;
					  break;
					case 1:
						DS1302_Time[6]--;
					if(DS1302_Time[6]<1)
						DS1302_Time[6]=7;
					  break;
					case 2:
						DS1302_Time[1]--;
					if(DS1302_Time[1]<1)
						DS1302_Time[1]=12;
					  break;
				}				
			}
				
				break;			
			default:
				break;
		}		
		
	}	
}


