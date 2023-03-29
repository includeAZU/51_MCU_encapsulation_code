#include <REGX52.H>

unsigned char UART_receive_byte()
{
	unsigned char byte;
	if (RI == 1) // ri==1,说明接收到了来自电脑的数据
	{
		byte = SBUF;
		RI = 0; //接收位置0
		return byte;
	}
}