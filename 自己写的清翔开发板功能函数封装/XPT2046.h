#define XPT2046_VBAT	0xAC//旋钮
#define XPT2046_AUX		0xEC//热敏电阻	
#define XPT2046_XP		0x9C//光敏电阻	//0xBC
#define XPT2046_YP		0xDC

int XPT2046_get_data(char command);