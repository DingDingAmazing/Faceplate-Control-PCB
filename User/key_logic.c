#include "key_logic.h"
void SysTick_Configuration(void)
{
	SysTick_Config(SystemCoreClock/1000);
}

//18 key 2 power 2rotate 4 swithj
tmr_t hardkey_tmr[19];
mode_state_t hardkey_mod[19];
uint8_t once_start[19];

tmr_t combinTmr[2];
uint8_t combinStatus[2] = {0,0}; 
uint8_t combinOnceStart[3] = {0,0,0};


uint8_t pwr_mod[3]={0,0,0};

tmr_t rotate_tmr[3];
rotate_mode_t rotate_mode[3];
uint8_t rotate_step[3];
uint8_t step_count[3];
uint8_t roate_st[3];
uint8_t wise=0;

uint8_t msc_3A;
uint8_t msc_10A;
uint8_t J[5];

/**********************faceplate hardkey{release/shortpush/longpush}****************************/
void hardkey_short(uint8_t key)
{	
	if(once_start[key] == 1)//�յ�cmdʹ��once_start
	{
		CT(key,1);
		if(hardkey_mod[key] == short_push)
		{
			tmr_start(&hardkey_tmr[key],500);
		}
		once_start[key] = 0;//һ��cmdֻ����һ��tmr_start
	}
	
	if(tmr_has_expired(&hardkey_tmr[key]))
	{
		CT(key,0);
		tmr_stop(&hardkey_tmr[key]);
		hardkey_mod[key] = release;
		Uart_send_feckback();
	}
}

void hardkey_long(uint8_t key)
{	
	if(once_start[key] == 1)//�յ�cmdʹ��once_start
	{
		CT(key,1);
		if(hardkey_mod[key] == long_push)
		{
			tmr_start(&hardkey_tmr[key],2000);
		}
		once_start[key] = 0;//һ��cmdֻ����һ��tmr_start
	}
	
	if(tmr_has_expired(&hardkey_tmr[key]))
	{
		CT(key,0);
		tmr_stop(&hardkey_tmr[key]);
		hardkey_mod[key] = release;
		Uart_send_feckback();
	}
}
/**********************end faceplate hardkey{release/shortpush/longpush}****************************/


/**********************combination key****************************/
void keyCombination1(void)
{
	if(combinOnceStart[0] == 1)
	{
		CT(3,1);
		combinTmr[0].start_tick = rt_tick;
		combinTmr[0].state = TMR_STARTED;
		combinOnceStart[0] = 0;
	}
	if((rt_tick - combinTmr[0].start_tick) > 7100)
	{
		CT(1,0);
		combinStatus[0] = 0;//process finish
		Uart_send_feckback();
	}
	else if((rt_tick - combinTmr[0].start_tick) > 1100)
	{
		CT(2,0);
		CT(1,1);
	}
	else if((rt_tick - combinTmr[0].start_tick) > 550)
	{
		CT(3,0);
		CT(2,1);
	}
}

void keyCombination2(void)
{
	if(combinOnceStart[0] == 1)
	{
		CT(3,1);
		combinTmr[0].start_tick = rt_tick;
		combinTmr[0].state = TMR_STARTED;
		combinOnceStart[0] = 0;
	}
	if((rt_tick - combinTmr[0].start_tick) > 12100)
	{
		CT(1,0);
		combinStatus[1] = 0;//process finish
		Uart_send_feckback();
	}
	else if((rt_tick - combinTmr[0].start_tick) > 1100)
	{
		CT(2,0);
		CT(1,1);
	}
	else if((rt_tick - combinTmr[0].start_tick) > 550)
	{
		CT(3,0);
		CT(2,1);
	}
}
/**********************end combination key****************************/


/**********************NGI power1/power2****************************/
void power_on(uint8_t power_num)
{
	PW(power_num,1);
	pwr_mod[power_num]=0;
	Uart_send_feckback();
}

void power_off(uint8_t power_num)
{
	PW(power_num,0);
	pwr_mod[power_num]=0;
	Uart_send_feckback();
}
/**********************end NGI power1/power2****************************/


/**********************faceplate rotate turn step****************************/
void rotate_up(uint8_t rotate_num,uint8_t step)
{
	if(roate_st[rotate_num] == 1)
	{
		step_count[rotate_num] =  0;
		ROT(rotate_num,1);
		tmr_start(&rotate_tmr[rotate_num],80);
		roate_st[rotate_num] = 0;
	}
	
	if(tmr_has_expired(&rotate_tmr[rotate_num]))
	{
		tmr_reset(&rotate_tmr[rotate_num]);
		wise = !wise;
		ROT((rotate_num+2),wise);
		step_count[rotate_num]++;
	}
	if(step_count[rotate_num] == step*2)
	{
		tmr_stop(&rotate_tmr[rotate_num]);
		rotate_mode[rotate_num] = stop;
		Uart_send_feckback();
	}
}

void rotate_down(uint8_t rotate_num,uint8_t step)
{
	if(roate_st[rotate_num] == 1)
	{
		step_count[rotate_num] =  0;
		ROT(rotate_num,0);//������Ҫ��ʵ�ʵ�16��CT��17��CT��gpioapp����˳��һ��
		tmr_start(&rotate_tmr[rotate_num],80);
		roate_st[rotate_num] = 0;
	}
	
	if(tmr_has_expired(&rotate_tmr[rotate_num]))
	{
		tmr_reset(&rotate_tmr[rotate_num]);
		wise = !wise;
		ROT( (2+rotate_num),wise);
		step_count[rotate_num]++;
	}
	if(step_count[rotate_num] == step*2)
	{
		tmr_stop(&rotate_tmr[rotate_num]);
		rotate_mode[rotate_num] = stop;
		Uart_send_feckback();
	}
}
/**********************end faceplate rotate turn step****************************/


/**********************faceplate swith connect****************************/
void SW_J_on(uint8_t SWJ_num)
{
	J_J(SWJ_num,1);
	Uart_send_feckback();
}


void SW_J_off(uint8_t SWJ_num)
{
	J_J(SWJ_num,0);
	Uart_send_feckback();
}
/**********************end faceplate swith connect****************************/


/**********************faceplate swith connect****************************/

/**********************end faceplate swith connect****************************/


void tmr_start(tmr_t *tmr,const tmr_ticks_t delay_in_ticks)
{
    tmr->delay_in_ticks = delay_in_ticks;
    tmr->start_tick     = 	rt_tick;
    tmr->state          =  TMR_STARTED;
}

bool_t tmr_has_expired(tmr_t *tmr)
{
    tmr_ticks_t  tick_old;

    if(tmr->state == TMR_STOPPED)
        return FALSE;
    if(tmr->state != TMR_EXPIRED)
    {
        tick_old=rt_tick;	
        if(tick_old-tmr->start_tick > tmr->delay_in_ticks)
        {
            tmr->state = TMR_EXPIRED;
            return TRUE;
        }
        else
            return FALSE;			
    }
    else
        return TRUE;		
}

void tmr_reset(tmr_t *tmr)
{
    tmr->start_tick +=tmr->delay_in_ticks;
    //		tmr->start_tick =  rt_tick;
    tmr->state        =  TMR_STARTED;
}

void tmr_stop(tmr_t *tmr)
{
    tmr->state = TMR_STOPPED;
}