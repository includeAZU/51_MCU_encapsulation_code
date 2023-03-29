#include <REGX52.H>
#include <INTRINS.H>
sbit CS = P3 ^ 7;         //选择传感器
sbit SDA = P2 ^ 0;        //数据输入
sbit SCL = P2 ^ 1;        //时钟线
sbit DOUT = P2 ^ 5;       //数据输出
#define XPT2046_VBAT 0xAC //旋钮//1010 1100
#define XPT2046_AUX 0xEC  //热敏电阻
#define XPT2046_XP 0x9C   //光敏电阻	//0xBC
#define XPT2046_YP 0xDC   // 8位模式

void Delayms(int num) //@11.0592MHz
{
    unsigned char i, j;
    while (num--)
    {
        _nop_();
        _nop_();
        _nop_();
        i = 11;
        j = 190;
        do
        {
            while (--j)
                ;
        } while (--i);
    }
}

int XPT2046_get_data(char command)
{
    char i;
    int mydata = 0; // 16位
    CS = 0;         //低电平有效
    for (i = 0; i < 8; i++)
    { //低电平放数据在数据线上,高电平写入
        SCL = 0;
        SDA = command & (0x80 >> i);
        SCL = 1;
    }
    Delayms(10);

    for (i = 0; i < 8; i++)
    { //高电平放数据在数据线上,低电平写入
    //8位模式
        SCL = 1;
        SCL = 0;
        if (DOUT)

        {
            mydata |= (0x80 >> i);
        }
    }
    CS = 1;
    return mydata;
}
// #include"LCD1602.h"
// void main (){
// LCD_Init();
// while (1)
// {
//     LCD_ShowNum(1,1,XPT2046_get_data(XPT2046_VBAT				),4);
//     Delayms(100);

// }

// }