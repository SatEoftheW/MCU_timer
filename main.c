#include "initial.h"
#include "instruction.h"
#include "delay.h"


void main()
{
	/*初始化*/
	LCD_initial();
	/*字符显示*/
	LCD_showStr(1, 6, "Hello!");
	LCD_showStr(2, 5, "HD44780U");
	while(1)
	{
	}
}
