#include "gpio_app.h"

void CT(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 1:
			if(en)
				key_set(CT1, 1);
			else
				key_set(CT1, 0);
			break;
			
		case 2:
			if(en)
				key_set(CT2, 1);
			else
				key_set(CT2, 0);
			break;
			
		case 3:
			if(en)
				key_set(CT3, 1);
			else
				key_set(CT3, 0);
			break;
			
		case 4:
			if(en)
				key_set(CT4, 1);
			else
				key_set(CT4, 0);
			break;
		

		case 5:
			if(en)
				key_set(CT5, 1);
			else
				key_set(CT5, 0);
			break;
			
		case 6:
			if(en)
				key_set(CT6, 1);
			else
				key_set(CT6, 0);
			break;
			
		case 7:
			if(en)
				key_set(CT7, 1);
			else
				key_set(CT7, 0);
			break;
			
		case 8:
			if(en)
				key_set(CT8, 1);
			else
				key_set(CT8, 0);
			break;
			
		case 9:
			if(en)
				key_set(CT9, 1);
			else
				key_set(CT9, 0);
			break;
			
		case 10:
			if(en)
				key_set(CT10, 1);
			else
				key_set(CT10, 0);
			break;
			
		case 11:
			if(en)
				key_set(CT11, 1);
			else
				key_set(CT11, 0);
			break;
			
		case 12:
			if(en)
				key_set(CT12, 1);
			else
				key_set(CT12, 0);
			break;
			
		case 13:
			if(en)
				key_set(CT13, 1);
			else
				key_set(CT13, 0);
			break;
			
		case 14:
			if(en)
				key_set(CT14, 1);
			else
				key_set(CT14, 0);
			break;
			
		case 15:
			if(en)
				key_set(CT15, 1);
			else
				key_set(CT15, 0);
			break;
			
		case 16:
			if(en)
				key_set(CT16, 1);
			else
				key_set(CT16, 0);
			break;
			
		case 17:
			if(en)
				key_set(CT17, 1);
			else
				key_set(CT17, 0);
			break;
			
		case 18:
			if(en)
				key_set(CT18, 1);
			else
				key_set(CT18, 0);
			break;
			
		default:
			break;
	}
	key_update();
}

void J_J(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 1:
			if(en)
				key_set(J1, 1);
			else
				key_set(J1, 0);
			break;
			
		case 2:
			if(en)
				key_set(J2, 1);
			else
				key_set(J2, 0);
			break;
			
		case 3:
			if(en)
				key_set(J3, 1);
			else
				key_set(J3, 0);
			break;
			
		case 4:
			if(en)
				key_set(J4, 1);
			else
				key_set(J4, 0);
			break;
			
		default:
			break;
	}
	key_update();
}

void PW(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 1:
			if(en)
				key_set(PW1, 1);
			else
				key_set(PW1, 0);
			break;
			
		case 2:
			if(en)
				key_set(PW2, 1);
			else
				key_set(PW2, 0);
			break;
			
		default:
			break;
	}
	key_update();
}

void MSC(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 1:
			if(en)
				key_set(M3A, 1);
			else
				key_set(M3A, 0);
			break;
			
		case 2:
			if(en)
				key_set(M10A, 1);
			else
				key_set(M10A, 0);
			break;
			
		default:
			break;
	}
	key_update();
}

void USBCT(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 1:
			if(en)
			{
//				key_set(USBCTL1, 1);
				key_set(CT8, 0);
				key_set(CT9, 0);
				key_set(CT10, 0);
				key_set(CT11, 0);
				key_set(CT12, 0);
				key_set(CT13, 0);
				
				key_set(CT14, 1);
			}
			else
//				key_set(USBCTL1, 0);
				key_set(CT14, 0);
			break;
			
		case 2:
			if(en)
			{
//				key_set(USBCTL2, 1);
				key_set(CT8, 0);
				key_set(CT9, 0);
				key_set(CT10, 0);
				key_set(CT11, 0);
				key_set(CT12, 0);
				key_set(CT14, 0);
				
				key_set(CT13, 1);
			}
			else
//				key_set(USBCTL2, 0);
				key_set(CT13, 0);
			break;
			
		case 3:
			if(en)
			{
//				key_set(USBCTL3, 1);
				key_set(CT8, 0);
				key_set(CT9, 0);
				key_set(CT10, 0);
				key_set(CT11, 0);
				key_set(CT13, 0);
				key_set(CT14, 0);
				
				key_set(CT12, 1);
			}
			else
//				key_set(USBCTL3, 0);
				key_set(CT12, 0);
			break;
			
		case 4:
			if(en)
			{
//				key_set(USBCTL4, 1);
				key_set(CT8, 0);
				key_set(CT9, 0);
				key_set(CT10, 0);
				key_set(CT12, 0);
				key_set(CT13, 0);
				key_set(CT14, 0);
				
				key_set(CT11, 1);
			}
			else
//				key_set(USBCTL4, 0);
				key_set(CT11, 0);
			break;
			
		case 5:
			if(en)
			{
//				key_set(USBCTL5, 1);
				key_set(CT8, 0);
				key_set(CT9, 0);
				key_set(CT11, 0);
				key_set(CT12, 0);
				key_set(CT13, 0);
				key_set(CT14, 0);
				
				key_set(CT10, 1);
			}
			else
//				key_set(USBCTL5, 0);
				key_set(CT10, 0);
			break;
			
		case 6:
			if(en)
			{
//				key_set(USBCTL6, 1);
				key_set(CT8, 0);
				key_set(CT10, 0);
				key_set(CT11, 0);
				key_set(CT12, 0);
				key_set(CT13, 0);
				key_set(CT14, 0);
				
				key_set(CT9, 1);
			}
			else
//				key_set(USBCTL6, 0);
				key_set(CT9, 0);
			break;
			
		case 7:
			if(en)
			{
//				key_set(USBCTL7, 1);
				key_set(CT9, 0);
				key_set(CT10, 0);
				key_set(CT11, 0);
				key_set(CT12, 0);
				key_set(CT13, 0);
				key_set(CT14, 0);
				
				key_set(CT8, 1);
			}
			else
//				key_set(USBCTL7, 0);
				key_set(CT8, 0);
			break;
			
		default:
			break;
	}
	key_update();
}
