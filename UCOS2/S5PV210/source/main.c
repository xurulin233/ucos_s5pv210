#include "led.h"
#include "uart.h"
#include "ucos_ii.h"
#include "stdio.h"

OS_STK stk[1024];
void TestTask(void *pdata);

int main(void)
{
    uart_init();
	uart_putc('O');
	uart_putc('K');

    // 初始化内核，主要就是初始化所有的变量和数据结构
    OSInit();
    // 初始化tick time
    OSTimeSet(0);	
    // 将MainTask由睡眠态变成就绪态
    OSTaskCreate(TestTask,NULL,&stk[sizeof(stk)-1],0);
    // 开始多任务调度，OSStart之前用户至少创建一个任务。
    // 此时有三个任务:空闲任务idle、统计任务stat、maintask(优先级最高)
    OSStart();																					
    for(;;)
    	;
}
void TestTask(void *pdata)
{
	while(1)
	{	
		uart_putc('O');
	}
}