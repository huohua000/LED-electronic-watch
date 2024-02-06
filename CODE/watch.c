#include "headfile.h"

unsigned char seg1[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void point_twinkle()
{
	point=!point;
}

void dispall()
{
	P2=0;
	W1=0;
	W2=0;
	W3=0;
	W4=0;
}

void disp_single(int date)
{
	P2=seg1[date];
}

void disp(int dat,int mode)
{
	int ge,shi,bai,qian;
	ge=dat%10;
	shi=dat/10;shi=shi%10;
	bai=dat/100;bai=bai%10;
	qian=dat/1000;qian=qian%10;
	switch(mode)
	{
		case 1:
			W1=0;
			W2=1;
			W3=1;
			W4=1;
			disp_single(ge);
			break;
		case 2:
			W1=1;
			W2=0;
			W3=1;
			W4=1;	
			disp_single(shi);
			break;
		case 3:
			W1=1;
			W2=1;
			W3=0;
			W4=1;	
			disp_single(bai);	
			break;
		case 4:
			W1=1;
			W2=1;
			W3=1;
			W4=0;	
			disp_single(qian);
			break;
  }
}