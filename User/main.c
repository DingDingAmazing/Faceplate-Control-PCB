#include "main.h"



int main(void)
{
	SysTick_Configuration();
	iobus_init();
	usart_init();
//	setTestTimer1();//testing
//	CT(1,1);
//	CT(2,1);
//	CT(3,1);
//	CT(4,1);
//	CT(5,1);
//	CT(6,1);
//	CT(7,1);
//	CT(8,1);
//	CT(9,1);
//	CT(10,1);
//	CT(11,1);
//	CT(12,1);
//	CT(13,1);
//	CT(14,1);
//	CT(15,1);
//	CT(16,1);
//	CT(17,1);
//	CT(18,1);
//	J_J(1,1);
//	J_J(2,1);
//	J_J(3,1);
//	J_J(4,1);
//	PW(1,1);
//	PW(2,1);
//	MSC(1,1);
//	MSC(2,1);
//	ROT(1,1);
//	ROT(2,1);
//	ROT(3,1);
//	ROT(4,1);
//	USBCT(1,1);
//	bsp_mDelay(1000);
//	USBCT(1,0);
//	USBCT(2,1);
//	USBCT(3,1);
//	USBCT(4,1);
//	USBCT(5,1);
//	USBCT(6,1);
//	USBCT(7,1);

	while(1)
	{
//		Uart_send_feckback();
//		bsp_mDelay(200);
//		if(1)
//			{
//				if(usbtem!=0xff)
//				usart_putc(0xf1);
//				bsp_mDelay(200);
//			}
		UartFrameHandle();
		Uart2FrameOperate();
		EnventHandle();
//		timerUsartTest();//testing
		bsp_uDelay(5);
	}
}
