#include "uart_driver.h"

/*************************************************************************************/
/* UART1 device driver structure */
struct serial_ringbuffer uart1_int_rx;
struct serial_ringbuffer uart1_int_tx;
struct stm32_uart uart1 =
{
    USART1,
    USART1_IRQn,
};
struct rt_serial_device serial1;
/*************************************************************************************/


///*************************************************************************************/
////
void USART1_uConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//	//USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_BaudRate = 115200; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); 
	USART_Cmd(USART1, ENABLE);
	
}

void NVIC_uConfiguration(void)
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/////////////////////////////////////////////////////
void serial_ringbuffer_putc(struct serial_ringbuffer *rbuffer,char ch)
{
    rbuffer->buffer[rbuffer->put_index] = ch;
    rbuffer->put_index = (rbuffer->put_index + 1) & (SERIAL_RBUFFER_SIZE - 1);

    if (rbuffer->put_index == rbuffer->get_index)
    {
        rbuffer->get_index = (rbuffer->get_index + 1) & (SERIAL_RBUFFER_SIZE - 1);
    }
		
}
/////////////////////////////////////////////////////
void rt_hw_serial_isr(struct rt_serial_device *serial)
{
    int ch = -1;

    while (1)
    {
        ch = usart_getc();
        if (ch == -1)
            break; 
        serial_ringbuffer_putc(serial->int_rx, ch);
    }   
}

void rt_hw_uart()
{
	int ch = -1;
	while(1)
	{
		ch = usart_getc();
		if(ch == -1)
			break;
		uart1_int_rx.buffer[uart1_int_rx.put_index] = ch;
    uart1_int_rx.put_index = (uart1_int_rx.put_index + 1) & (SERIAL_RBUFFER_SIZE - 1);

    if (uart1_int_rx.put_index == uart1_int_rx.get_index)
    {
        uart1_int_rx.get_index = (uart1_int_rx.get_index + 1) & (SERIAL_RBUFFER_SIZE - 1);
    }
	}
}

void USART1_RecTask(void)
{
	unsigned char ubTemp = 0;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		ubTemp = USART_ReceiveData(USART1);
		USART_SendData(USART1,ubTemp);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET); 
	}
}

uint8_t usbtem;
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
			//usbtem = usart_getc();
			
			//usbtem = USART_ReceiveData(USART1);
			//USART_SendData(USART1,usbtem);
			
			rt_hw_serial_isr(&serial1);
			//rt_hw_uart();//test
			
      USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
    if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
    {
			USART_ClearITPendingBit(USART1, USART_IT_TC);
    }
			
}
/*************************************************************************************/


/*************************************************************************************/
//
int usart_putc(char c)
{
    while (!(USART1->ISR & USART_FLAG_TXE));
    USART1->TDR = c;
	
    return 1;
}
//
int usart_getc(void)
{
    int ch;
    ch = -1;
    if (USART1->ISR & USART_FLAG_RXNE)
    {
        ch = USART1->RDR & 0xff;
    }

    return ch;
}

int serial_ringbuffer_getc(void)
{
    int ch;

    ch = -1;

    if (uart1_int_rx.get_index != uart1_int_rx.put_index)
    {
        ch = uart1_int_rx.buffer[uart1_int_rx.get_index];
        uart1_int_rx.get_index = (uart1_int_rx.get_index + 1) & (SERIAL_RBUFFER_SIZE - 1);
    }

    return ch;
}
//
unsigned long  rt_serial_read(void *buffer,unsigned long size)
{
    uint8_t *ptr;
    uint32_t read_nbytes;
    ptr = (uint8_t *)buffer;

    while (size)
    {
        int ch;

        ch = serial_ringbuffer_getc();
        if (ch == -1)
            break;
    
        *ptr = ch & 0xff;
        ptr ++;
        size --;
    }
    
    read_nbytes = (uint32_t)ptr - (uint32_t)buffer;
    
    return read_nbytes;
}

//
unsigned long rt_serial_write(void *buffer,unsigned long size)
{
    uint8_t *ptr;
    unsigned long write_nbytes = 0;
    ptr = (uint8_t*)buffer;
    /* polling mode */
    while (size)
    { 

        usart_putc(*ptr);

        ++ ptr;
        -- size;
    }

    write_nbytes = (uint32_t)ptr - (uint32_t)buffer;

    return write_nbytes;
}
//
void serial_ringbuffer_init(void)
{
	struct stm32_uart* uart;
	uart = &uart1;
	
	serial1.int_rx = &uart1_int_rx;
	serial1.int_tx = &uart1_int_tx;
	serial1.user_data = uart;
	
  memset(uart1_int_rx.buffer, 0, sizeof(uart1_int_rx.buffer));
  uart1_int_rx.put_index = 0;
  uart1_int_rx.get_index = 0;
	
	memset(uart1_int_tx.buffer, 0, sizeof(uart1_int_rx.buffer));
  uart1_int_tx.put_index = 0;
  uart1_int_tx.get_index = 0;
	
}
/*************************************************************************************/


/*************************************************************************************/
void usart_init(void)
{
	USART1_uConfiguration();
	NVIC_uConfiguration();
	serial_ringbuffer_init();
}
