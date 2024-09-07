#include "s5pv210.h"

#define 	GPJ2CON 	(*(volatile unsigned long *) 0xE0200280)
#define 	GPJ2DAT		(*(volatile unsigned long *) 0xE0200284)

// 延时函数
void delay(unsigned long count)
{
	volatile unsigned long i = count;
	while (i--)
		;
}

void led_blink()				//LED 闪烁
{
	GPJ2CON = 0x00001111;		// 配置引脚
	while(1)					// 闪烁
	{
		GPJ2DAT = 0;			// LED on
		delay(0x100000);
		GPJ2DAT = 0xf;			// LED off
		delay(0x100000);
	}
}

void led_on()				
{
	GPJ2CON = 0x00001111;		
	GPJ2DAT = 0;			
}

void led_off()				
{
	GPJ2CON = 0x00001111;		
	GPJ2DAT = 0xf;			
}
