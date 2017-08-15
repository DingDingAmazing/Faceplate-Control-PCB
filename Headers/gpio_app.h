#ifndef _GPIO_APP_H
#define _GPIO_APP_H

#include "gpio_driver.h"

#define MAKE_KEY(GROUP,OFFSET)   (WORD)((WORD)(GROUP<<8) + (WORD)(1 << OFFSET))

#define C1        		MAKE_KEY(0,7)
#define C2        		MAKE_KEY(0,6)
#define C3        		MAKE_KEY(0,5)
#define C4        		MAKE_KEY(0,4)
#define C5        		MAKE_KEY(0,3)
#define C6        		MAKE_KEY(0,2)
#define C7        		MAKE_KEY(0,1)
#define C8        		MAKE_KEY(1,7)
#define C9        		MAKE_KEY(1,6)
#define C10       		MAKE_KEY(1,5)
#define C11       		MAKE_KEY(1,4)
#define C12       		MAKE_KEY(1,3)
#define C13       		MAKE_KEY(1,2)
#define C14       		MAKE_KEY(1,1)
#define C15        	  MAKE_KEY(2,7)
#define C16        	  MAKE_KEY(2,6)
#define C17        	  MAKE_KEY(2,5)
#define C18        	  MAKE_KEY(2,4)
#define C19        	  MAKE_KEY(2,3)
#define C20        	  MAKE_KEY(2,2)
#define C21        	  MAKE_KEY(2,1)
#define C22        	  MAKE_KEY(3,6)
#define C23        	  MAKE_KEY(3,5)
#define C24        	  MAKE_KEY(3,4)
#define C25        	  MAKE_KEY(3,3)
#define C26        	  MAKE_KEY(3,2)
#define C27        	  MAKE_KEY(3,1)
#define USBCTL1       MAKE_KEY(4,7)
#define USBCTL2       MAKE_KEY(4,6)
#define USBCTL3       MAKE_KEY(4,5)
#define USBCTL4       MAKE_KEY(4,4)
#define USBCTL5       MAKE_KEY(4,3)
#define USBCTL6       MAKE_KEY(4,2)
#define USBCTL7       MAKE_KEY(4,1)

#define CT1     C1
#define CT2     C2
#define CT3     C3
#define CT4     C4
#define CT5     C5
#define CT6     C6
#define CT7     C7
#define CT8     C8
#define CT9     C9
#define CT10    C10
#define CT11    C11
#define CT12    C12
#define CT13    C13
#define CT14    C14
#define CT15    C15
#define CT16    C16
#define CT17    C17
#define CT18    C18
#define J1      C19
#define J2      C20
#define J3      C21
#define J4      C22
#define PW1     C23
#define PW2     C24
#define M3A     C25
#define M10A    C26

extern void CT(uint8_t num, uint8_t en);
extern void J_J(uint8_t num, uint8_t en);
extern void PW(uint8_t num, uint8_t en);
extern void MSC(uint8_t num, uint8_t en);
extern void USBCT(uint8_t num, uint8_t en);
#endif
