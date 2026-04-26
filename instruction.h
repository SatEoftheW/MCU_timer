#ifndef INSTRUCTION_H
#define INSTRUCTION_H

//读指令
unsigned char readInstruction();
//写指令
void writeInstruction(unsigned char i);
//写数据
void writeData(unsigned char i);
//BF检查
void BF();
//创建CGRAM字模
void LCD_createCGRAM(unsigned char CGRAMaddress, unsigned char CGRAMcharacter[8]);
//字符显示
void LCD_showChar(unsigned char row, unsigned char column, unsigned char char_show);
//字符串显示
void LCD_showStr(unsigned char row, unsigned char column, unsigned char str[]);
#endif