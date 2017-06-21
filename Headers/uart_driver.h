#ifndef _UART_DRIVER_H
#define _UART_DRIVER_H

#include "stm32f0xx.h"
#include "string.h"
/******************************************************/
#define BAUD_RATE_4800                  4800
#define BAUD_RATE_9600                  9600
#define BAUD_RATE_115200                115200
#define SERIAL_RBUFFER_SIZE             1024  ///3k byte
/******************************************************/

/******************************************************/
extern struct serial_ringbuffer uart1_int_rx;
extern struct serial_ringbuffer uart1_int_tx;

extern void usart_init(void);
extern int usart_putc(char c);
extern int usart_getc(void);	
extern int serial_ringbuffer_getc(void);
extern unsigned long  rt_serial_read(void *buffer,unsigned long size);
extern unsigned long rt_serial_write(void *buffer,unsigned long size);
/******************************************************/


/******************************************************/
struct stm32_uart
{
    USART_TypeDef* uart_device;
    IRQn_Type irq;
};
//
struct serial_ringbuffer
{
    uint8_t  buffer[SERIAL_RBUFFER_SIZE];
    uint16_t put_index, get_index;
};
//
struct rt_list_node
{
    struct rt_list_node *next;                          /**< point to next node. */
    struct rt_list_node *prev;                          /**< point to prev node. */
};
typedef struct rt_list_node rt_list_t;                  /**< Type for lists. */
//
struct rt_data_queue
{
    uint16_t size;
    uint16_t lwm;
    int   waiting_lwm;

    uint16_t get_index;
    uint16_t put_index;

    struct rt_data_item *queue;
 //   rt_list_t suspended_push_list;
 //   rt_list_t suspended_pop_list;
    /* event notify */
    void (*evt_notify)(struct rt_data_queue *queue, uint32_t event);
};
//
typedef struct rt_serial_device
{
    struct stm32_uart*       user_data;
    /* rx structure */
    struct serial_ringbuffer *int_rx;
    /* tx structure */
    struct serial_ringbuffer *int_tx;

    struct rt_data_queue     tx_dq;/* tx dataqueue */
    
    volatile int             dma_flag;/* dma transfer flag */
	
	  int				  		         last_rx_char;
}rt_serial_t;
/*******************************************************************/
extern uint8_t usbtem;


#endif
