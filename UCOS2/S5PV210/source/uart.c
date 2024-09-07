#define GPA0CON		0xE0200000
#define UCON0 		0xE2900004
#define ULCON0 		0xE2900000
#define UMCON0 		0xE290000C
#define UFCON0 		0xE2900008
#define UBRDIV0 	0xE2900028
#define UDIVSLOT0	0xE290002C
#define UTRSTAT0	0xE2900010
#define UTXH0		0xE2900020	
#define URXH0		0xE2900024	
 
#define rGPA0CON	(*(volatile unsigned int *)GPA0CON)
#define rUCON0		(*(volatile unsigned int *)UCON0)
#define rULCON0		(*(volatile unsigned int *)ULCON0)
#define rUMCON0		(*(volatile unsigned int *)UMCON0)
#define rUFCON0		(*(volatile unsigned int *)UFCON0)
#define rUBRDIV0	(*(volatile unsigned int *)UBRDIV0)
#define rUDIVSLOT0	(*(volatile unsigned int *)UDIVSLOT0)
#define rUTRSTAT0		(*(volatile unsigned int *)UTRSTAT0)
#define rUTXH0		(*(volatile unsigned int *)UTXH0)
#define rURXH0		(*(volatile unsigned int *)URXH0)
 
// 串口初始化程序
void uart_init(void)
{
	// 1、初始化Tx Rx对应的GPIO引脚
	rGPA0CON &= ~(0xff<<0);			// 把寄存器的bit0～7全部清零
	rGPA0CON |= 0x00000022;			// 0b0010, Rx Tx
	
	// 2、几个关键寄存器的设置
	rULCON0 = 0x3;
	rUCON0 = 0x5;
	rUMCON0 = 0;
	rUFCON0 = 0;
	
    // 3、设置波特率
	// 波特率设置公式：DIV_VAL = PCLK / (bps x 16) - 1	
	// 其中PCLK_PSYS = 66.7，bps表示想设置的波特率
	// DIV_VAL =  66700000/(115200*16) - 1 = 35.18
    // 整数部分是35，小数部分是0.18
 
    //整数部分是35
	rUBRDIV0 = 35; 
 
	// (rUDIVSLOT中的1的个数)/16=上一步计算的余数=0.18
	// (rUDIVSLOT中的1的个数 = 16*0.18= 2.88 = 3
    // 3个1，查官方推荐表得到这个数字0x0888
	rUDIVSLOT0 = 0x0888;		
}
 
 
// 串口发送程序，发送一个字节
void uart_putc(char c)
{                  	
	// 串口发送一个字符，其实就是把一个字节丢到发送缓冲区中去
	// 因为串口控制器发送1个字节的速度远远低于CPU的速度，所以CPU发送1个字节前必须
	// 确认串口控制器当前缓冲区是空的（意思就是串口已经发完了上一个字节）
	// 如果缓冲区非空则位为0，此时应该循环，直到位为1
	while (!(rUTRSTAT0 & (1<<1))); //rUTRSTAT0的bit[1]表示是否发完，为1则发完
	rUTXH0 = c;
}
 
// 串口接收程序，轮询方式，接收一个字节
char uart_getc(void)
{  
    //rUTRSTAT0的bit[0]表示是否接收完成，为1则接收完
	while (!(rUTRSTAT0 & (1<<0)));
	return (rURXH0 & 0x0f);//这里应该是 return (rURXH0 & 0xff)？
}
