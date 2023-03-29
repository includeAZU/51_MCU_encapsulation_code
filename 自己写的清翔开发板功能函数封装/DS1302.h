  /// @brief 
  void DS1302_init();//使用之前要初始化
  void DS1302_SetTime(void);//设置时间要设置 DS1302_Time[]数组
  void DS1302_ReadTime(void);//分别读取DS1302_Time[]数据






  
  // DS1302_Time[0] ;
//   #define DS1302_SECOND 0x80 //+2是读指令//|0x01
// #define DS1302_MINUTE 0x82
// #define DS1302_HOUR 0x84
// #define DS1302_DATE 0x86
// #define DS1302_MONTH 0x88
// #define DS1302_DAY 0x8A
// #define DS1302_YEAR 0x8C
// #define DS1302_WP 0x8E