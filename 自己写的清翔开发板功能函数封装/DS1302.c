#include <REGX52.H>
#include <INTRINS.H>

//引脚定义
sbit DS1302_SCLK = P1 ^ 0;   //时钟线
sbit DS1302_IO = P1 ^ 1;     //数据接口
sbit DS1302_CE = P1 ^ 2;     //芯片使能
#define MAIN_Fosc 11059200UL //晶振
//寄存器写入地址/指令定义
#define DS1302_SECOND 0x80 //+2是读指令//|0x01
#define DS1302_MINUTE 0x82
#define DS1302_HOUR 0x84
#define DS1302_DATE 0x86
#define DS1302_MONTH 0x88
#define DS1302_DAY 0x8A
#define DS1302_YEAR 0x8C
#define DS1302_WP 0x8E

//时间数组，索引0~6分别为年、月、日、时、分、秒、星期
unsigned char DS1302_Time[] = {22, 11, 8, 12, 59, 55, 6};
//设置时间
/**
 * @brief  DS1302初始化
 * @param  无
 * @retval 无
 */
void DS1302_Init(void) //初始化
{                      //单片机上电默认高电平
    DS1302_CE = 0;     //芯片不使能
    DS1302_SCLK = 0;
}

/**
 * @brief  DS1302写一个字节
 * @param  Command 命令字/地址
 * @param  Data 要写入的数据
 * @retval 无
 */
void DS1302_WriteByte(unsigned char Command, char Data)
{
    unsigned char i;
    DS1302_CE = 1; //芯片使能

    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 0;
        DS1302_IO = Command & (0x01 << i);
        DS1302_SCLK = 1; //高电平写入
    }
    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 0;
        DS1302_IO = Data & (0x01 << i);
        DS1302_SCLK = 1; //高电平写入
    }
    DS1302_CE = 0; //芯片不使能
}

/**
 * @brief  DS1302读一个字节
 * @param  Command 命令字/地址
 * @retval 读出的数据
 */
unsigned char DS1302_ReadByte(unsigned char Command)
{ //从DS1302中读取数据
    unsigned char i, Data = 0x00;
    Command |= 0x01; //将指令转换为读指令
    DS1302_CE = 1;   //芯片使能
    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 0;
        DS1302_IO = Command & (0x01 << i);

        DS1302_SCLK = 1; //低电平把数据放数据线上,高电平写入
    }
    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 1; //从高电平到低电平,芯片把一个数据放io
        DS1302_SCLK = 0;
        if (DS1302_IO) //如果是1
        {
            Data |= (0x01 << i);
        }
    }
    DS1302_CE = 0;
    DS1302_IO = 0; //读取后将IO设置为0，否则读出的数据会出错
    return Data;
}

/**
 * @brief  DS1302设置时间，调用之后，DS1302_Time数组的数字会被设置到DS1302中
 * @param  无
 * @retval 无
 */
// BCD码转十进制：DEC=BCD/16*10+BCD%16; （2位BCD）
//十进制转BCD码：BCD=DEC/10*16+DEC%10; （2位BCD）

void DS1302_SetTime(void)
{
    DS1302_WriteByte(DS1302_WP, 0x00);                                             //清除写保护
    DS1302_WriteByte(DS1302_YEAR, DS1302_Time[0] / 10 * 16 + DS1302_Time[0] % 10); //十进制转BCD码后写入
    DS1302_WriteByte(DS1302_MONTH, DS1302_Time[1] / 10 * 16 + DS1302_Time[1] % 10);
    DS1302_WriteByte(DS1302_DATE, DS1302_Time[2] / 10 * 16 + DS1302_Time[2] % 10);
    DS1302_WriteByte(DS1302_HOUR, DS1302_Time[3] / 10 * 16 + DS1302_Time[3] % 10);
    DS1302_WriteByte(DS1302_MINUTE, DS1302_Time[4] / 10 * 16 + DS1302_Time[4] % 10);
    DS1302_WriteByte(DS1302_SECOND, DS1302_Time[5] / 10 * 16 + DS1302_Time[5] % 10);
    DS1302_WriteByte(DS1302_DAY, DS1302_Time[6] / 10 * 16 + DS1302_Time[6] % 10);
    DS1302_WriteByte(DS1302_WP, 0x80); //设置写保护
}

/**
 * @brief  DS1302读取时间，调用之后，DS1302中的数据会被读取到DS1302_Time数组中
 * @param  无
 * @retval 无
 */
void DS1302_ReadTime(void)
{
    unsigned char Temp;
    Temp = DS1302_ReadByte(DS1302_YEAR);         //码转十进制后读取
    DS1302_Time[0] = Temp / 16 * 10 + Temp % 16; // BCD
    Temp = DS1302_ReadByte(DS1302_MONTH);
    DS1302_Time[1] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_DATE);
    DS1302_Time[2] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_HOUR);
    DS1302_Time[3] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_MINUTE);
    DS1302_Time[4] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_SECOND);
    DS1302_Time[5] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_DAY);
    DS1302_Time[6] = Temp / 16 * 10 + Temp % 16;
}

// sbit TSCLK = P1 ^ 0; //时钟线
// sbit TIO = P1 ^ 1;   //数据线
// sbit TRST = P1 ^ 2;  //芯片使能
//  #define MAIN_Fosc		11059200UL
// #define TSECOND 0x80 //秒
// #define TMINUTE 0x82 //分
// #define THOUR 0x84   //小时
// #define TDATE 0x86   //日期
// #define TMONTH 0x88  //月
// #define TDAY 0x8A    //星期
// #define TYEAR 0x8C   //年
// #define TWP 0x8E     //写保护
// void DS1302_init()
// {
//     TRST = 0;  //芯片不使能
//     TSCLK = 0; //时钟线置低
// }

// void Delayms(int num) //@11.0592MHz
// {
// 	unsigned char i, j;
// 	while(num--)
// 	{
// 		_nop_();
// 	_nop_();
// 	_nop_();
// 	i = 11;
// 	j = 190;
// 	do
// 	{
// 		while (--j);
// 	} while (--i);
// 	}
// }
// void Twrite_byte(char command, char mydata)
// {
//     int i;
//     TRST = 1; //芯片使能

//     for (i = 0; i < 8; i++)
//     { //在TCLK是低电平时,把数据放到TIO,TCLK高电平写入

//         TIO = command & (0x01 << i);
//         TCLK = 1;
//         TCLK = 0;
//     }
//     for (i = 0; i < 8; i++)
//     { //在TCLK是低电平时,把数据放到TIO,TCLK高电平写入

//         TIO = mydata & (0x01 << i);
//         TCLK = 1;
//         TCLK = 0;
//     }
//     TRST = 0;
// }

// char DS1302_read_byte(char command)
// {
//     int i;
//     int Data = 0x00; //

//     command |= 0x01; //把写指令变为读指令
//     TRST = 1;
//     // 0101 1010
//     // 0000 0001
//     for (i = 0; i < 8; i++)
//     {

//         TIO = command & (0x01 << i);
//         TSCLK = 0;
//         TSCLK = 1;
//     }
//     for (i = 0; i < 8; i++)
//     {

//         TSCLK = 1;
//         TSCLK = 0;
//         if (TIO)
//         {

//             Data |= (0x01 << i);
//             // 0000 0010
//             // 0000 0001
//         }
//     }

//     TRST = 0; //芯片不使能
//     TIO = 0;
//     return Data;
// }
// unsigned char DS1302_Time[] = {19,11,16,12,59,55,6};
// void DS1302_SetTime()
// {
//     Twrite_byte(TWP, 0x00); //清空写保护
//     Twrite_byte(TYEAR, DS1302_Time[0] / 10 * 16 + DS1302_Time[0] % 10);
//     Twrite_byte(TMONTH, DS1302_Time[1] / 10 * 16 + DS1302_Time[1] % 10);
//     Twrite_byte(TDATE, DS1302_Time[2] / 10 * 16 + DS1302_Time[2] % 10);
//     Twrite_byte(THOUR, DS1302_Time[3] / 10 * 16 + DS1302_Time[3] % 10);
//     Twrite_byte(TMINUTE, DS1302_Time[4] / 10 * 16 + DS1302_Time[4] % 10);
//     Twrite_byte(TSECOND, DS1302_Time[5] / 10 * 16 + DS1302_Time[5] % 10);
//     Twrite_byte(TDAY, DS1302_Time[6] / 10 * 16 + DS1302_Time[6] % 10);
//     Twrite_byte(TWP, 0x80); //设置写保护
// }
// void DS1302_read_time()
// {
//     char ret;

//     ret = DS1302_read_byte(TYEAR);
//     DS1302_Time[0] = ret / 16 * 10 + ret % 16;
//     ret = DS1302_read_byte(TMONTH);
//     DS1302_Time[1] = ret / 16 * 10 + ret % 16;
//     ret = DS1302_read_byte(TDATE);

//     DS1302_Time[2] = ret / 16 * 10 + ret % 16;
//     ret = DS1302_read_byte(THOUR);

//     DS1302_Time[3] = ret / 16 * 10 + ret % 16;
//     ret = DS1302_read_byte(TMINUTE);

//     DS1302_Time[4] = ret / 16 * 10 + ret % 16;
//     ret = DS1302_read_byte(TSECOND);
//     DS1302_Time[5] = ret / 16 * 10 + ret % 16;

//     ret = DS1302_read_byte(TDAY);
//     DS1302_Time[6] = ret / 16 * 10 + ret % 16;
// }
// void main()
// {
//     LCD_Init();
//     DS1302_init();
//     DS1302_SetTime();

// while (1)
//    { Delayms(200);
//         DS1302_read_time();
//          Delayms(200);
//         LCD_ShowNum(1, 1, DS1302_Time[2], 2);
//         LCD_ShowNum(1, 4, DS1302_Time[3], 2);
//         LCD_ShowNum(1, 7, DS1302_Time[4], 2);

// }}
