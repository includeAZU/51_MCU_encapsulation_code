void lattice_screen(unsigned char Display_word[],int x);
//先创建数组Display_word[],x为数组元素个数,数组用数组名传参

// void main()
// {
// 	unsigned char code Display_word[] =
// 		{

// 			0x00, 0x48, 0x2A, 0x8E, 0xFB, 0x0E, 0x2A, 0x48,
// 			0x0C, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0x0C};

// 	int a = sizeof(Display_word) / sizeof(unsigned char) / 8;
// 	lattice_screen(Display_word, a);
// }