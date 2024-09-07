#include "led.h"
#include "uart.h"



int main(void)
{
    uart_init();
	uart_putc('O');
	uart_putc('K');
    led_blink();
    for(;;)
    	;
}
