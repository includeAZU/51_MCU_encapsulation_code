#include <REGX52.H>

#include <INTRINS.H>

sbit LEDARRAY_LAT = P3 ^ 6; //高电平数据并行输出
sbit LEDARRAY_CLK = P3 ^ 5; //高电平数据下移
sbit LEDARRAY_DI = P3 ^ 4;	//数据输入端

void Send_Byte(unsigned char dat) // 74HC595
//从低到高写入
{
	unsigned char i;
	LEDARRAY_CLK = 0;
	_nop_();
	LEDARRAY_LAT = 0;
	_nop_();

	for (i = 0; i < 8; i++)
	{
		LEDARRAY_DI = dat & (0x01 << i);

		LEDARRAY_CLK = 1; //上升沿移位

		_nop_();
		LEDARRAY_CLK = 0;
		_nop_();
	}
}

void lattice_screen(unsigned char *Display_word, int x)
{
	unsigned char k;

	char  count;
	int a;
	while (1)
	{

		for (count = 0; count < x; count++)
		{
			for (a = 0; a <= 500; a++) //更改a的置,改变两个图像显示时间间隔
			{
				for (k = count * 8; k <= (((count + 1) * 8) - 1); k++)
				{
                  //把行与列写入,一起并行输出
					Send_Byte(~(0x80 >> (k % 8)));//阳极//0为选中
					Send_Byte(Display_word[k]);//1亮,0不亮//低位在下面
					LEDARRAY_LAT = 1;//上升沿锁存

					_nop_();

					LEDARRAY_LAT = 0;
					_nop_();
				}
			}
		}
	}
}
void main()
{
	unsigned char code Display_word[] =
		{

			0x00, 0x48, 0x2A, 0x8E, 0xFB, 0x0E, 0x2A, 0x48,
			0x0C, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0x0C};

	int a = sizeof(Display_word) / sizeof(unsigned char) / 8;
	lattice_screen(Display_word, a);
}
