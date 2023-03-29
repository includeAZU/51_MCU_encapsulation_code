// #include <REGX52.H>

// #include "get_matrix_keyboark_number.h"

// // 100微秒@11.0592MHz
// void Timer0Init() // 100微秒@11.0592MHz
// {
//     //定时器时钟1T模式
//     //定时器时钟1T模式
//     TMOD &= 0xF0; //设置定时器模式
//     TL0 = 0xAE;   //设置定时初始值
//     TH0 = 0xFB;   //设置定时初始值
//     TF0 = 0;      //清除TF0标志
//     TR0 = 1;

//     //运行中断设置
//     ET0 = 1; //开启中断
//     EA = 1;  //在中段函数中,TF0会自动置0
//     PT0 = 0;
// }

// int compear;
// int choice;//默认为0
// void main()
// {
//     Timer0Init();

//     while (1)
//     {
//         choice = get_matrix_keyboark_number();

//         if (choice == 1)
//         {
//             compear = 25;
//         }
//         if (choice == 2)
//         {
//             compear = 50;
//         }
//         if (choice == 3)
//         {
//             compear = 75;
//         }
//         if (choice == 4)
//         {
//             compear = 100;
//         }
//     }
// }
// int count ;
// void motor() interrupt 1
// {
//     TL0 = 0xAE; //设置定时初始值
//     TH0 = 0xFB;
//     count++;
//     count %= 100;

//     if (count < compear)
//     {
//         P1_1 = 0;
//     }
//     else
//     {
//         P1_1 = 1;
//     }
// }
