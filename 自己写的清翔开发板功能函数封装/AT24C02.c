#include <REGX52.H>

sbit SCL = P2^1;        //时钟线
sbit SDA = P2^0;        //数据线
#define AT24C02_ADDR 0xa0 // AT24C02地址

void I2C_start(void)//开始
{ // SCL高电平期间，SDA从高电平切换到低电平
    SDA = 1;
    SCL = 1;
    SDA = 0;
    SCL = 0;
}
void I2C_stop(void)//结束
{ // SCL高电平期间，SDA从低电平切换到高电平
    SDA = 0;
    SCL = 1;
    SDA = 1;
    SCL = 0;
}

void I2C_send_byte(char _data)//发送一字节数据,AT24C02写数据
{ // SCL低电平期间，主机将数据位依次放到SDA线上（高位在前），然后拉高SCL，
  //从机将在SCL高电平期间读取数据位，所以SCL高电平期间SDA不允许有数据变化,
  //依次循环上述过程8次，即可发送一个字节

    char i;

    for (i = 0; i < 8; i++)
    {
        SCL = 0;
        SDA = _data & (0x80 >> i);
        SCL = 1;
        SCL = 0;
    }
}
unsigned char I2C_recerve_byte(void) //读取AT24C02写数据
//为什么unsigned char会影响读数
{
    //接收一个字节：SCL低电平期间，从机将数据位依次放到SDA线上（高位在前），
    //然后拉高SCL，主机将在SCL高电平期间读取数据位，所以SCL高电平期间SDA不允许有数据变化，
    //依次循环上述过程8次，即可接收一个字节（主机在接收之前，需要释放SDA）

    char i;
    unsigned char _data = 0x00;
    SDA = 1;//释放SDA
    for (i = 0; i < 8; i++)
    {
        SCL = 0;
        SCL = 1;
        // SDA已经把数据放数据线上了
        if (SDA)
        {
            _data |= (0x80 >> i);
        }
        SCL = 0;
    }
    return _data;
}
void I2C_send_response(bit _data)
{ //发送应答：在接收完一个字节之后主机在下一个时钟发送一位数据，数据0表示应答，数据1表示非应答

    SCL = 0;
    SDA = _data;
    SCL = 1;
    SCL = 0;
}

bit I2C_reserve_response(void)
{ //在发送完一个字节之后，主机在下一个时钟接收一位数据，判断从机是否应答，
    //数据0表示应答，数据1表示非应答（主机在接收之前，需要释放SDA）
    bit _data;
    SDA = 1;
    SCL = 0;
    SCL = 1;
    _data = SDA;
    SCL = 0;
    return _data;
}

void AT24C02_write(char WordAddress, char _data)
{
    I2C_start();
    I2C_send_byte(AT24C02_ADDR); //// AT24C02地址
    I2C_reserve_response();
    I2C_send_byte(WordAddress); //写在AT24C02哪里
    I2C_reserve_response();
    I2C_send_byte(_data);
    I2C_reserve_response();
    I2C_stop();
}
char AT24C02_read(char WordAddress)
{
    char _data;
    I2C_start();
    I2C_send_byte(AT24C02_ADDR);//// AT24C02地址
    I2C_reserve_response();
    I2C_send_byte(WordAddress);//AT24C02内部地址
    I2C_reserve_response();
    I2C_start();
    I2C_send_byte(AT24C02_ADDR | 0x01); //代表读指令
    I2C_reserve_response();
    _data = I2C_recerve_byte();
    I2C_send_response(0);
    I2C_stop();
    return _data;
}
// #include "LCD1602.h"
// #include <INTRINS.H>
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
// void main()
// {

//     LCD_Init();
//     Delayms(10);
//     AT24C02_write(8, 0x0a);
//     Delayms(10);

//     Delayms(10);

//     while (1)
//     {
//         Delayms(100);
//         LCD_ShowSignedNum(1, 2, AT24C02_read(8), 2); //无法显示负数
//         P1 = AT24C02_read(0);
//         Delayms(100);
//     }
// }
