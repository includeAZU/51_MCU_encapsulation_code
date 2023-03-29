
#include <REGX52.H>
void init_UART() // 11.0592
{
	//波特率4800
	//模式:8位自动重载
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	//AUXR |= 0x40;		//定时器时钟1T模式
	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xB8;		//设置定时初始值
	TH1 = 0xB8;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;
	ES=1;

}

 void  UART_send_byte(unsigned char byte) //发送数据给电脑
{

	SBUF = byte;

	//直接把数据放SBUF这个寄存器里,电脑自动读取
	while (TI == 0);	//是否发送完成,否则等待
	TI = 0; //手动置零
}