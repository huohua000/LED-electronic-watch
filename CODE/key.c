#include "headfile.h"
#define KB1 P32//上
#define KB2 P33//中
#define KB3 P34//下
char key_up=1;
int tim_counter=0;
char Key_Scan(void)
{

	
	if(key_up&&(KB1==0||KB2==0||KB3==0))
	{

		tim_counter++;
		if(tim_counter==10)
		{
			tim_counter=0;
			key_up=0;
			if     (KB1==0)	
				return 1;
			else if(KB2==0)
				return 2;
			else if(KB3==0)
				return 3;
		}
	}
	else if(!KB1==0&&!KB2==0&&!KB3==0)
	{
		key_up=1;
	}
 	return 0;//无按键按下
}