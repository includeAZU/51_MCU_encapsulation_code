#include <REGX52.H>
#include <INTRINS.H>

void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 216;
	j = 37;
	do
	{
		while (--j);
	} while (--i);
}






int get_matrix_keyboark_number()
{
int number=0;

P3=0xFF;
P3_4=0;
if (P3_0==0){Delay20ms();while (P3_0==0);Delay20ms();number=1;}
if (P3_1==0){Delay20ms();while (P3_1==0);Delay20ms();number=5;}
if (P3_2==0){Delay20ms();while (P3_2==0);Delay20ms();number=9;}
if (P3_3==0){Delay20ms();while (P3_3==0);Delay20ms();number=13;}

P3=0xFF;
P3_5=0;
if (P3_0==0){Delay20ms();while (P3_0==0);Delay20ms();number=2;}
if (P3_1==0){Delay20ms();while (P3_1==0);Delay20ms();number=6;}
if (P3_2==0){Delay20ms();while (P3_2==0);Delay20ms();number=10;}
if (P3_3==0){Delay20ms();while (P3_3==0);Delay20ms();number=14;}

P3=0xFF;
P3_6=0;
if (P3_0==0){Delay20ms();while (P3_0==0);Delay20ms();number=3;}
if (P3_1==0){Delay20ms();while (P3_1==0);Delay20ms();number=7;}
if (P3_2==0){Delay20ms();while (P3_2==0);Delay20ms();number=11;}
if (P3_3==0){Delay20ms();while (P3_3==0);Delay20ms();number=15;}

P3=0xFF;
P3_7=0;
if (P3_0==0){Delay20ms();while (P3_0==0);Delay20ms();number=4;}
if (P3_1==0){Delay20ms();while (P3_1==0);Delay20ms();number=8;}
if (P3_2==0){Delay20ms();while (P3_2==0);Delay20ms();number=12;}
if (P3_3==0){Delay20ms();while (P3_3==0);Delay20ms();number=16;}

return number;
}