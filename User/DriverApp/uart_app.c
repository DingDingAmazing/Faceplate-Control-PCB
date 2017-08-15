#include "uart_app.h"

/*************************************************************************************/ 
STRUCT_UARTDEAL     gUart2Deal;
STRUCT_UARTFRAME 	  gUart2Frame;  

uint8_t key_num;
/*************************************************************************************/


/*************************************************************************************/
//
void Uart_send_feckback(void)
{
	uint8_t Data_Temp[DataLength_Max];

	memset(&Data_Temp,0,DataLength_Max); 

	Data_Temp[0] = 0xaa;
	Data_Temp[1] = 0xbb;		
	
	rt_serial_write(&Data_Temp, 2); 
}
/*************************************************************************************/


/*************************************************************************************/
//
void UartFrameHandle(void)
{
    uint8_t      Data = 0;
    static uint16_t       Cmd = 0;
    static uint16_t       Len = 0;
    static uint16_t   PackLen = 0;
    Uart2TimeOut = 3000;	//300ms¶¨Ê±
    while(1)
    {
        if(gUart2Deal.EndFlag == TRUE)	
        {
            break;
        }

        if(!Uart2TimeOut)		
        {
            gUart2Deal.EndFlag = TRUE;
            break;
        }
				
				if(rt_serial_read(&Data,1)==0)
        {
            break;
        }
				
      switch(gUart2Deal.Step)
      {
				case 0:
        if(Data == 0x55)		
        {
          gUart2Deal.Step++;
          PackLen  = 0;
        }
				else
        {
          gUart2Deal.EndFlag = TRUE;
        }
        break;
        
				case 1:
        if(Data == 0xaa)		
        {
          gUart2Deal.Step++;
          PackLen	 = 0;
        }
        else
        {
          gUart2Deal.EndFlag = TRUE;
					gUart2Deal.Step = 0;
        }
        break;
        
				case 2:								
        if(Data > 0xf0)	
        {
          Cmd = Data<<8;
          gUart2Deal.Step++;
        }
        else
        {
          memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
          Cmd = 0;
          Len = 0;
          PackLen = 0;
          gUart2Deal.EndFlag = TRUE;
          gUart2Deal.Step = 0;
        }
        break;
         
				case 3:						
        Cmd |= Data;
        gUart2Frame.Cmd = Cmd;
        gUart2Deal.Step++;
        if(gUart2Frame.Cmd == 0)
        {
          memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
          Cmd      = 0;
          Len      = 0;
          PackLen  = 0;
          gUart2Deal.EndFlag = TRUE;
          gUart2Deal.Step = 0;
        }
        break;
				
				case 4:
        if((Data > 0)&&(Data != 0xcc))		
        {
					gUart2Frame.DataBuf[PackLen++] = Data;
        }
				else if(Data == 0xcc)
				{
					Cmd      = 0;
          Len      = 0;
          PackLen  = 0;
          gUart2Deal.Step = 0;
					gUart2Deal.EndFlag = TRUE;
				}
				else
				{
					memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
					Cmd      = 0;
          PackLen  = 0;
          gUart2Deal.EndFlag = TRUE;
          gUart2Deal.Step = 0;
				}
				break;
           
//				case 4:								
//				Len = Data;
//        gUart2Frame.DataLen = Len;
//        gUart2Deal.Step++;
//				key117 = 0x10;
//        if((gUart2Frame.DataLen == 0)||(gUart2Frame.DataLen >100))		
//        {
//					memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
//					Cmd      = 0;
//          Len      = 0;
//          PackLen  = 0;
//          gUart2Deal.EndFlag = TRUE;
//          gUart2Deal.Step = 0;
//					key117 = 0x11;
//        }
//        break;
//            
//				case 5:						
//        if(Len > 1)
//        {
//          gUart2Frame.DataBuf[PackLen++] = Data;
//          Len--;
//					key117 = 0x12;
//         }
//         else						
//         {
//					 gUart2Frame.DataBuf[PackLen++] = Data;
//           gUart2Deal.Step++;
//					 key117 = 0x13;
//         }
//         break;
//				 
//         case 6:								
//         if(Data == 0xcc)
//         {
//           Cmd      = 0;
//           Len      = 0;
//           PackLen  = 0;
//           gUart2Deal.Step = 0;
//					 key117 = 0x14;
//         }
//         else
//				 {
//					 memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
//           Cmd      = 0;
//           Len      = 0;
//           PackLen  = 0;
//           gUart2Deal.Step = 0;
//					 key117 = 0x15;
//         }
//         gUart2Deal.EndFlag = TRUE;
//         break;
            
				 default:
         memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
         Cmd      = 0;
         Len      = 0;
         PackLen  = 0;
         gUart2Deal.Step = 0;
         gUart2Deal.EndFlag = TRUE;
				 break;
		}
	}
}
/*************************************************************************************/


/*************************************************************************************/
//
void Uart2FrameOperate(void)
{	
    if(gUart2Deal.EndFlag == FALSE)
    {
        return;
    }
		
    switch(gUart2Frame.Cmd)
    {	
        case 0xf101: 
					if(gUart2Frame.DataBuf[0] == 01)
						pwr_mod[1] = 1;
					else if(gUart2Frame.DataBuf[0] == 02)
						pwr_mod[1] = 2;
            break;			

        case 0xf102:
					if(gUart2Frame.DataBuf[0] == 01)
						pwr_mod[2] = 1;
					else if(gUart2Frame.DataBuf[0] == 02)
						pwr_mod[2] = 2;
            break;
					
				//knob_ICI2_01
				case 0xf301:
					if((knob_mode[1] == 0)&&(gUart2Frame.DataBuf[0]<3)&&(gUart2Frame.DataBuf[1]<0x7f))
					{
						knob_mode[1] = gUart2Frame.DataBuf[0];
						knob_vol[1] = gUart2Frame.DataBuf[1];
						knob_start[1] = 1;
					}
					else
						knob_start[1] = 0;
						break;
				//knob_ICI2_02	
				case 0xf302:
					if((knob_mode[2] == 0)&&(gUart2Frame.DataBuf[0]<3)&&(gUart2Frame.DataBuf[1]<0x7f))
					{
						knob_mode[2] = gUart2Frame.DataBuf[0];
						knob_vol[2] = gUart2Frame.DataBuf[1];
						knob_start[2] = 1;
					}
					else
						knob_start[2] = 0;
						break;
								
				case 0xf401:
					msc_3A = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf402:
					msc_10A = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf501:
					J[1] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf502:
					J[2] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf503:
					J[3] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf504:
					J[4] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf601:
					USB[1] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf602:
					USB[2] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf603:
					USB[3] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf604:
					USB[4] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf605:
					USB[5] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf606:
					USB[6] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf607:
					USB[7] = gUart2Frame.DataBuf[0];
						break;
				
				case 0xf701:
					if(combinStatus[0] == 0)
					{
						combinStatus[0] = 1;
						combinOnceStart[0] = 1;
					}
					break;
				
				case 0xf702:
					if(combinStatus[1] == 0)
					{
						combinStatus[1] = 1;
						combinOnceStart[0] = 1;
					}
					break;
					
				//knob_NGI1_01
				case 0xf801:
					if((rotate_mode[1] == 0)&&(gUart2Frame.DataBuf[0]<3)&&(gUart2Frame.DataBuf[1]<0x7f))
					{
						rotate_mode[1] = gUart2Frame.DataBuf[0];
						rotate_step[1] = gUart2Frame.DataBuf[1];
						roate_st[1] = 1;
					}
					else
						roate_st[1] = 0;
						break;
				//knob_NGI1_02
				case 0xf802:
					if((rotate_mode[2] == 0)&&(gUart2Frame.DataBuf[0]<3)&&(gUart2Frame.DataBuf[1]<0x7f))
					{
						rotate_mode[2] = gUart2Frame.DataBuf[0];
						rotate_step[2] = gUart2Frame.DataBuf[1];
						roate_st[2] = 1;
					}
					else
						roate_st[2] = 0;
						break;
					
        default:
            break;
    }
		
		if((gUart2Frame.Cmd>>8) == 0xf2)
		{
			if(gUart2Frame.Cmd & 0xff)
			{
				key_num = (gUart2Frame.Cmd & 0xff);
					if(hardkey_mod[key_num] == release)
					{
						hardkey_mod[key_num] = gUart2Frame.DataBuf[0];
						once_start[key_num] = 1;
					}
					else
						once_start[key_num] = 0;
			}
		}	

    memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME)); 
    memset(&gUart2Deal,0, sizeof(STRUCT_UARTDEAL)); 
}
/*************************************************************************************/


/*************************************************************************************/
//


void proc_envent1(void)
{
	uint8_t n;
	for(n=1; n<19; n++)
	{
		if(hardkey_mod[n] == short_push)
			hardkey_short(n);
		else if(hardkey_mod[n] == long_push)
			hardkey_long(n);
	}
}

void proc_envent2(void)
{
	if(pwr_mod[1] == 1)
		power_on(1);
	else if(pwr_mod[1] == 2)
		power_off(1);
	
	if(pwr_mod[2] == 1)
		power_on(2);
	else if(pwr_mod[2] == 2)
		power_off(2);
}

//knob_envent_NGI1
void knob_envent_NGI1(void)
{
	if(rotate_mode[1]==clockwise)
			rotate_up(1,rotate_step[1]);
	else if(rotate_mode[1]==anticlockwise)
			rotate_down(1,rotate_step[1]);
	
	if(rotate_mode[2]==clockwise)
			rotate_up(2,rotate_step[2]);
	else if(rotate_mode[2]==anticlockwise)
			rotate_down(2,rotate_step[2]);
}

//knob_envent_ICI2
void knob_envent_ICI2(void)
{
	if(knob_mode[1]==clockwise)
			knob_up(1,knob_vol[1]);
	else if(knob_mode[1]==anticlockwise)
			knob_down(1,knob_vol[1]);
	
	if(knob_mode[2]==clockwise)
			knob_up(2,knob_vol[2]);
	else if(knob_mode[2]==anticlockwise)
			knob_down(2,knob_vol[2]);
}

void proc_envent4(void)
{
	if(msc_3A==1)
	{
		//power_off(1);
		power_off(2);
		MSC(2,0);
		MSC(1,1);
		msc_3A = 0;
	}
	else if(msc_3A==2)
	{
		//power_off(1);
		power_off(2);
		MSC(2,0);
		MSC(1,0);
		msc_3A = 0;
	}
	else if(msc_10A==1)
	{
		//power_off(1);
		power_off(2);
		MSC(1,0);
		MSC(2,1);
		msc_10A = 0;
	}
	else if(msc_10A==2)
	{
		//power_off(1);
		power_off(2);
		MSC(1,0);
		MSC(2,0);
		msc_10A = 0;
	}
}

void proc_envent5(void)
{
	if(J[1]==1)
	{
		SW_J_on(1);
		J[1]=0;
	}
	else if(J[1]==2)
	{
		SW_J_off(1);
		J[1]=0;
	}
	
	else if(J[2]==1)
	{
		SW_J_on(2);
		J[2]=0;
	}
	else if(J[2]==2)
	{
		SW_J_off(2);
		J[2]=0;
	}
	
	else if(J[3]==1)
	{
		SW_J_on(3);
		J[3]=0;
	}
	else if(J[3]==2)
	{
		SW_J_off(3);
		J[3]=0;
	}
	
	else if(J[4]==1)
	{
		SW_J_on(4);
		J[4]=0;
	}
	else if(J[4]==2)
	{
		SW_J_off(4);
		J[4]=0;
	}
}

void proc_envent6(void)
{
	if(USB[1]==1)
	{
		USBCT(1,1);
		Uart_send_feckback();
		USB[1]=0;
	}
	else if(USB[1]==2)
	{
		USBCT(1,0);
		Uart_send_feckback();
		USB[1]=0;
	}
	
	else if(USB[2]==1)
	{
		USBCT(2,1);
		Uart_send_feckback();
		USB[2]=0;
	}
	else if(USB[2]==2)
	{
		USBCT(2,0);
		Uart_send_feckback();
		USB[2]=0;
	}
	
	else if(USB[3]==1)
	{
		USBCT(3,1);
		Uart_send_feckback();
		USB[3]=0;
	}
	else if(USB[3]==2)
	{
		USBCT(3,0);
		Uart_send_feckback();
		USB[3]=0;
	}
	
	else if(USB[4]==1)
	{
		USBCT(4,1);
		Uart_send_feckback();
		USB[4]=0;
	}
	else if(USB[4]==2)
	{
		USBCT(4,0);
		Uart_send_feckback();
		USB[4]=0;
	}
	
	else if(USB[5]==1)
	{
		USBCT(5,1);
		Uart_send_feckback();
		USB[5]=0;
	}
	else if(USB[5]==2)
	{
		USBCT(5,0);
		Uart_send_feckback();
		USB[5]=0;
	}
	
	else if(USB[6]==1)
	{
		USBCT(6,1);
		Uart_send_feckback();
		USB[6]=0;
	}
	else if(USB[6]==2)
	{
		USBCT(6,0);
		Uart_send_feckback();
		USB[6]=0;
	}
	
	else if(USB[7]==1)
	{
		USBCT(7,1);
		Uart_send_feckback();
		USB[7]=0;
	}
	else if(USB[7]==2)
	{
		USBCT(7,0);
		Uart_send_feckback();
		USB[7]=0;
	}
}

void proc_envent7(void)
{
	if(combinStatus[0] == 1)
		keyCombination1();
	if(combinStatus[1] == 1)
		keyCombination2();
}

void EnventHandle(void)
{
	proc_envent1();
	proc_envent2();
	knob_envent_ICI2();
	knob_envent_NGI1();
	proc_envent4();
	proc_envent5();
	proc_envent6();
	proc_envent7();
}

//for test
tmr_t testTmr1;
void setTestTimer1(void)
{
	tmr_start(&testTmr1,500);
}
//for test
void timerUsartTest(void)
{
	if(tmr_has_expired(&testTmr1))
	{
		Uart_send_feckback();
		tmr_reset(&testTmr1);
	}
}
