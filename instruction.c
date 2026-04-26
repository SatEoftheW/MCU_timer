#include <REGX52.H>
#include "delay.h"
#include "instruction.h"

sbit RS  = P2^6;
sbit RW  = P2^5;
sbit E 	 = P2^7;
sbit DB7 = P0^7;
sbit DB6 = P0^6;
sbit DB5 = P0^5;
sbit DB4 = P0^4;
sbit DB3 = P0^3;
sbit DB2 = P0^2;
sbit DB1 = P0^1;
sbit DB0 = P0^0;


unsigned char readInstruction()
{
	/*时序*/
	unsigned char i; //定义放最前面
	//进行RS, RW设置
	RS = 0; //指令
	RW = 1; //读
	//释放总线(原因尚不明确)
	P0 = 0xFF;
	//延时60ns以上(确保信号稳定)
	Delay10us();
	//E拉高
	E = 1;
	//延时大于450ns(E拉高的有效时长)
	Delay10us();
	//指令读取
	i	= DB7;
	//E拉低
	E = 0;
	
	return i;
}
void writeInstruction(unsigned char i)
{
	/*BF检查*/
	BF();
	/*时序*/
	//进行RS, RW设置
	RS = 0; //指令
	RW = 0; //写
	//延时60ns(确保信号稳定)
	Delay10us();
	//E拉高
	E = 1;
	//指令准备
	P0 = i;
	//延时大于195ns(确保数据信号稳定)
	Delay10us();
	//E拉低
	E = 0; //此时数据被锁存(写入)
	//恢复读状态(防止意外情况)
	RW = 1;
}
void writeData(unsigned char i)
{
	/*BF检查*/
	BF();
	/*时序*/
	//进行RS, RW设置
	RS = 1; //数据
	RW = 0; //写
	//延时60ns(确保信号稳定)
	Delay10us();
	//E拉高
	E = 1;
	//数据准备
	P0 = i;
	//延时大于195ns(确保数据信号稳定)
	Delay10us();
	//E拉低
	E = 0; //此时数据被锁存(写入)
	//恢复读状态(防止意外情况)
	RW = 1;
}

void BF()
{
	unsigned char BF = 1;
	while(BF) //BF为0时空闲, 退出函数
	{
		BF = readInstruction();
	}
}

void LCD_createCGRAM(unsigned char CGRAMaddress, unsigned char CGRAMcharacter[8])
{
	unsigned char i;
	
	//CGRAM地址建立(指向CGRAM存储区域)
	writeInstruction(CGRAMaddress);
	//CGRAM字模数据写入
	for(i = 0; i < 8; i++)
	{
		writeData(CGRAMcharacter[i]);
	}
	//CGRAM地址退出(AC指向DDRAM显示区域(一般状态))
	writeInstruction(0x80);
}

void LCD_showChar(unsigned char row, unsigned char column, unsigned char char_show)
{
	unsigned char DDRAMaddress;
	
	if(row == 1) //第一行
	{
		DDRAMaddress = 0x80 + column - 1;
	}
	else if(row == 2) //第二行
	{
		DDRAMaddress = 0xC0 + column - 1;
	}
	//DDRAM覆写(显示位置)
	writeInstruction(DDRAMaddress);
	//字符代码数据传入(显示内容)
	writeData(char_show);
}

void LCD_showStr(unsigned char row, unsigned char column, unsigned char str[])
{
	unsigned char i;
	unsigned char DDRAMaddress;
	
	if(row == 1) //第一行
	{
		DDRAMaddress = 0x80 + column - 1;
	}
	else if(row == 2) //第二行
	{
		DDRAMaddress = 0xC0 + column - 1;
	}
	//DDRAM覆写(显示位置)
	writeInstruction(DDRAMaddress);
	//字符代码数据传入(显示内容)
	for(i = 0; ; i++)
	{
		if(str[i] != '\0') //非尾部
		{
			writeData(str[i]);
		}
		else //尾部
		{
			break;
		}
	}
}