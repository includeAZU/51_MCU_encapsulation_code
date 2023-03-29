#include <REGX52.H>
// 1毫秒@11.0592MHz
void Timer0Init() // 1毫秒@11.0592MHz
{
	//定时器时钟1T模式
			//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初始值
	TH0 = 0xD4;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时


	
	//运行中断设置
	ET0 = 1; //开启中断
	EA = 1;	 //在中段函数中,TF0会自动置0
	PT0 = 0;
}











//不用判断溢出
/*定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;

	}
}
*/

// void Timer1Init(void) // 50ms
// {
// 	TR1 = 1;	 //启动定时器1
// 	TMOD = 0x10; // T1为定时器,工作模式为16位模式
// 	TH1 = 0x4b;//两个组成,就是TH1,TL1共同组成一个16位
// 	TL1 = 0xfc; ////0x4bfc	定时50ms
// }

// TF1 == 1//是否溢出,每溢出一次是50ms
/*if(TF1 == 1)判断T1是否溢出
			{
				TH1 = 0x4b;
				TL1 = 0xfc;//清零
				TF1 = 0;//手动把溢出位置0

			}*/