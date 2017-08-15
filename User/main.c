#include "main.h"



int main(void)
{
	static uint8_t n;
	SysTick_Configuration();
	iobus_init();
	usart_init();
	
	if(1)
	{
		for(n=9; n<19; n++)
		{
			CT(n,1);
			bsp_mDelay(200);
			CT(n,0);
		}
	}

	while(1)
	{
		UartFrameHandle();
		Uart2FrameOperate();
		EnventHandle();
		bsp_uDelay(5);
	}
}
