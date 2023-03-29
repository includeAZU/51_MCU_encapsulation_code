#include "REGX52.H"
#include "LCD1602.h"
void timer0_init() //设置定时器
{
    TMOD &= 0xF0; //设置定时器模式
    TMOD |= 0x01; //设置定时器模式
    TL0 = 0;      //设置定时初值
    TH0 = 0;      //设置定时初值
    TF0 = 0;      //清除TF0标志
    TR0 = 0;      //定时器0不计时
}
void timer0_set_counter(int count) //设置定时器时间
{
    TH0 = count / 256;
    TL0 = count % 256;
}
unsigned int timer0_get_counter() //获取定时器时间
{

    return ((TH0 << 8) | TL0);
}
void timer0_run(char ifstate) //是否启动定时器
{

    TR0 = ifstate;
}

void interrupt0_init() //中断设置,下降沿触发
{
    IT0 = 1;
    IE0 = 0;
    EX0 = 1;
    EA = 1;
    PX0 = 1;
}
int ir_time;
char ir_state; // ir 状态
char ir_data[4];
char ir_pdata;
char ir_data_flag; //接收数据位
char ir_repeat_flag;
char ir_address;
char ir_comnand;

void itr0() interrupt 0
{
    if (ir_state == 0) //空闲状态//默认为0
    {
        timer0_set_counter(0);
        timer0_run(1); //开始计时
        ir_state = 1;  //准备接收数据
    }
    else if (ir_state == 1) //开始接收数据
    {
        ir_time = timer0_get_counter(); //获取上一次中断到此次中断的时间
        timer0_set_counter(0);

        if (ir_time > 12442 - 500 && ir_time < 12442 + 500)
        {
            ir_state = 2; //是开始信号,接收数据
        }
        else if (ir_time > 10368 - 500 && ir_time < 10368 + 500)
        {
            ir_repeat_flag = 1; //重发标志
            timer0_run(0);
            ir_state = 0;
        }
        else //接收出错
        {
            ir_state = 1; //置状态为1
        }
    }

    else if (ir_state == 2)
    {
        ir_time = timer0_get_counter();
        timer0_set_counter(0);
        if (ir_time > 1032 - 500 && ir_time < 1032 + 500)
        { // 0
            ir_data[ir_pdata / 8] &= ~(0x01 << (ir_pdata % 8));
            // 0101  0110
            // 0000  0001
            // 1111  1110
            // ir_data[ir_pdata / 8] &= ~(0x01 << (ir_pdata % 8));
            ir_pdata++;
        }
        else if (ir_time > 2074 - 500 && ir_time < 2074 + 500)
        {
            // 1
            //低位在前,高位在后
            ir_data[ir_pdata / 8] &= (0x01 << (ir_pdata % 8));
            ir_pdata++;
        }
        else //接收出错
        {
            ir_pdata = 0; //数据位置指针清0
            ir_state = 1; //置状态为1
        }

        if (ir_pdata >= 32)
        {
            ir_pdata = 0;
            if (ir_data[0] == ~ir_data[1] && ir_data[2] == ~ir_data[3])
            { //正反校验
                ir_address = ir_data[0];

                ir_comnand = ir_data[2];
                ir_data_flag = 1; //接收数据成功
            }
            timer0_run(0);
            ir_state = 0;
        }
    }
}

char ret_ir_comnand(void)
{
    return ir_comnand;
}

char infrared_receiver(void)
{
    timer0_init();
    interrupt0_init();
    return ret_ir_comnand();
}
