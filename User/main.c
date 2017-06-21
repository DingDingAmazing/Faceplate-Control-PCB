#include "main.h"


int main(void)
{
	SysTick_Configuration();
	iobus_init();
	usart_init();
	if(1)
	{
	CT(16,1);
	CT(17,1);
	CT(18,1);
	}
	bsp_mDelay(1000);
	if(1)
	{
	CT(16,0);
	CT(17,0);
	CT(18,0);
	}
	bsp_mDelay(50);
//	if(0)
//	{
//	J_J(4,1);
//	PW(1,1);
//	PW(2,1);
//	MSC(1,1);
//	}
//	if(0)
//	{
//		while(1)
//		{
//			if(0)
//			{
//				if(usbtem!=0xff)
//				usart_putc(usbtem);
//				bsp_mDelay(200);
//			}
//			if(1)
//			{
//				bsp_uDelay(5);
//			}
//		}
//	}
	while(1)
	{
		UartFrameHandle();
		Uart2FrameOperate();
		EnventHandle();
		bsp_uDelay(5);
	}
}
