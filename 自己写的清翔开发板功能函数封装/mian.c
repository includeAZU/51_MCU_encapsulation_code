

#include "DS18B20.h"
#include"LCD1602.h"
  float T;

 void main()
 {
     LCD_Init();
     LCD_ShowString(1,3,"temperature");
     while (1)
     {
         DS18B20_change_temperature();
         Delayms(100);
         T = DS18B20_show_temperature();
         LCD_ShowNum(2, 6, T, 2); 
         LCD_ShowChar(2, 8, '.');
         LCD_ShowNum(2, 9, (unsigned long)(T * 100) % 100, 2);
     }
 }
