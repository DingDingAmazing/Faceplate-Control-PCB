#ifndef _UART_APP_H
#define _UART_APP_H

#include "uart_driver.h"
#include "string.h"
#include "key_logic.h"


/******************************************************/
#define BUFSIZE512 512
#define DataLength_Max 	128
extern uint8_t key_num;
/******************************************************/


/******************************************************/
extern void Uart_send_feckback(void);
extern void UartFrameHandle(void);
extern void Uart2FrameOperate(void);
extern void EnventHandle(void);
extern void setTestTimer1(void);
extern void timerUsartTest(void);
/******************************************************/


/******************************************************/
//
typedef	struct 
{
    uint8_t   Step;
    uint8_t   EndFlag;
}STRUCT_UARTDEAL;
//
typedef	struct 
{
    uint16_t  Cmd;
    uint16_t  DataLen;
    uint8_t   DataBuf[BUFSIZE512];
}STRUCT_UARTFRAME;

/******************************************************/


#endif
