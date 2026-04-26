#include "delay.h"
#include "instruction.h"

void LCD_initial()
{
	//上电后延时40ms(使状态稳定)
	Delay40ms();
	
	//初始化指令1
	writeInstruction(0x30);
	//延时大于4.1ms
	Delay5ms();
	
	//初始化指令1
	writeInstruction(0x30);
	//延时超过100us
	Delay110us();
	
	//初始化指令1
	writeInstruction(0x30);
	//延时超过37us
	Delay110us();
	
	//Functionset
	writeInstruction(0x3C);
	
	//Displayoff
	writeInstruction(0x08);
	//Displayclear
	writeInstruction(0x01);
	//Entrymodeset
	writeInstruction(0x05);
	//Displayon
	writeInstruction(0x0F);
}