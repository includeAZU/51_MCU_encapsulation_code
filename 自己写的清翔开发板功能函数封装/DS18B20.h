void DS18B20_change_temperature(void) ;//使用之前先转化温度
float DS18B20_show_temperature(void);
//建议使用整数与小数分开显示,即
//T=float DS18B20_show_temperature(void);
//整数:T*100/100
//小数:T*100%100