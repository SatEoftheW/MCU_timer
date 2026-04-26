#include <REGX52.H>
#include "delay.h"

void main()
{
	//定义
	unsigned char second = 0;
	unsigned char second_show, minute, minute_show, hour;
	/*延时*/
	Delay1000ms(); //延时1s
	/*计算*/
	second++;
	second_show = second % 60;
	minute = second - second_show;
	minute_show = minute % 60;
	hour = minute - minute_show;
	/*显示*/
}