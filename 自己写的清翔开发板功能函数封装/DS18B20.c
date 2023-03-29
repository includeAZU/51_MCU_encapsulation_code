#include <REGX52.H>
#include "INTRINS.H"
sbit one_wire = P2 ^ 2; //数据线

char one_wire_init(void)//初始化
{//主机将总线拉低至少480us，然后释放总线
//等待15~60us后，存在的从机会拉低总线60~240us以响应主机，
//之后从机将释放总线
    char i;
    char AckBit;

    one_wire = 0;

    i = 247;
    while (--i); // Delay 500us

    one_wire = 1;

    i = 32;
    while (--i); // Delay 70us

    AckBit = one_wire;

    i = 247;
    while (--i); // Delay 500us

    return AckBit;
}

void one_wire_send_bit(char _data)//发送一位
 {//主机将总线拉低60~120us，然后释放总线，表示发送0；
// 主机将总线拉低1~15us，然后释放总线，
// 表示发送1。从机将在总线拉低30us后（典型值）读取电平，整个时间片应大于60us
    char i;
    one_wire = 0;

    i = 4;
    while (--i)
        ; // Delay 10us

    one_wire = _data;//如果是1,释放总线

    i = 24;
    while (--i);         // Delay 50us
    one_wire = 1; //释放总线
}

unsigned char one_wire_reserve_bit(void)
{ //主机将总线拉低1~15us，然后释放总线，并在拉低后15us内读取总线电平（尽量贴近15us的末尾），
    //读取为低电平则为接收0，读取为高电平则为接收1 ，整个时间片应大于60us
    unsigned char i;
    unsigned char Bit;
    one_wire = 0;
    i = 2;
    while (--i); // Delay 5us
    one_wire = 1;
    i = 2;
    while (--i); // Delay 5us
    Bit = one_wire;//尽量贴近15us的末尾
    i = 24;
    while (--i) ; // Delay 50us
    return Bit;
}

void DS18B20_send_byte(char _data)
{//连续调用8次发送一位的时序，
//依次发送一个字节的8位（低位在前）
    char i;
    for (i = 0; i < 8; i++)
    {//两位同时为1,就是1
        one_wire_send_bit((_data & (0x01 << i)));
    }
}

char DS18B20_reserve_byte(void)
{
    char i;
    char _data = 0x00;
    for (i = 0; i < 8; i++)
    {
        if (one_wire_reserve_bit())
        {
            _data |= (0x01 << i);
        }
    }
    return _data;
}
void DS18B20_change_temperature(void ) //温度转换
{//温度变换：初始化→跳过ROM →开始温度变换

    one_wire_init();
    DS18B20_send_byte(0xcc);
    DS18B20_send_byte(0x44);
}
float DS18B20_show_temperature(void) //显示温度
{//初始化→跳过ROM →读暂存器→连续的读操作
    unsigned char hight, low;
    int temperature;
    float T;
    one_wire_init();
    DS18B20_send_byte(0xcc);
    DS18B20_send_byte(0xbe);
    low = DS18B20_reserve_byte();
    hight = DS18B20_reserve_byte(); //转化为10进制
    temperature = (hight << 8) | low;
    //和定时器一样
    T = temperature / 16.0;
    return T;
}
// #include "LCD1602.h"
// void Delayms(int num) //@11.0592MHz
// {
//     unsigned char i, j;
//     while (num--)
//     {
//         _nop_();
//         _nop_();
//         _nop_();
//         i = 11;
//         j = 190;
//         do
//         {
//             while (--j)
//                 ;
//         } while (--i);
//     }
// }

// float T;

// void main()
// {
//     LCD_Init();
//     LCD_ShowString(1,3,"temperature");
//     while (1)
//     {
//         DS18B20_change_temperature();
//         Delayms(100);
//         T = DS18B20_show_temperature();
//         LCD_ShowNum(2, 6, T, 2); //显示温度整数部分
//         LCD_ShowChar(2, 8, '.');
//         LCD_ShowNum(2, 9, (unsigned long)(T * 100) % 100, 2);
//     }
// }
