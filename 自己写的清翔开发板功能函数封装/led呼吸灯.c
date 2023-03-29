// #include <REGX52.H>
// #include "lattice_screen.h"



// void Delay(unsigned int t)
// {
//     while (t--)
//         ;
// }

// void main()
// {
//     unsigned char Time, i;
//     while (1)
//     {
//         for (Time = 0; Time < 100; Time++)
//         {
//             for (i = 0; i < 100; i++)
//             {
//                 P1_0= 0;
//                 Delay(Time);
//                  P1_0 = 1;
//                 Delay(100 - Time);
//             }
//         }
//         for (Time = 0; Time < 100; Time++)
//         {
//             for (i = 0; i < 100; i++)
//             {
//               P1_0 = 1;
//                 Delay(Time);
//                P1_0 = 0;
//                 Delay(100 - Time);
//             }
//         }
//     }
// }