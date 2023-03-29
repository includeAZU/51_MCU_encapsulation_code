#include <REGX52.H>
#include <INTRINS.H>
void Delay1ms() //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j)
			;
	} while (--i);
}

int number_code[] =
	{
		0x3F, //"0"
		0x06, //"1"
		0x5B, //"2"
		0x4F, //"3"
		0x66, //"4"
		0x6D, //"5"
		0x7D, //"6"
		0x07, //"7"
		0x7F, //"8"
		0x6F, //"9"
		0x77, //"A"
		0x7C, //"B"
		0x39, //"C"
		0x5E, //"D"
		0x79, //"E"
		0x71, //"F"
		0x76, //"H"
		0x38, //"L"
		0x37, //"n"
		0x3E, //"u"
		0x73, //"P"
		0x5C, //"o"
		0x40, //"-"
		0x00, //熄灭
		0x00  //自定义
};
// 0到9
void digital_tube_display(int site, int num) //位置,数字
{
	//选位置
	P2_7 = 1; //为0的那位是选择谁如1111  1110,第一位
	P0 = ~(0x01 << (site - 1));
	P2_7 = 0;
	//显示

	P2_6 = 1;
	P0 = number_code[num];
	Delay1ms();
	P0 = 0x00; //消影//0为不亮,1为亮//共阳极连接
	P2_6 = 0;
}
