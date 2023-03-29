#include <INTRINS.H>
void Delayms(int num) //@11.0592MHz
{
	unsigned char i, j;
	while(num--)
	{
		_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
	}
}
