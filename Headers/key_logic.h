#ifndef _KEY_LOGIC_H
#define _KEY_LOGIC_H

#include "gpio_app.h"
#include "stm32f0xx_it.h"

#define bool_t _Bool
#define FALSE  0
#define TRUE   (!FALSE)

typedef enum
{
    release = 0,
    short_push,
    long_push,
} mode_state_t;

typedef enum
{
		stop = 0,
    clockwise,
    anticlockwise,
} rotate_mode_t;


/**************struct tmr_t************/
typedef enum
{
    TMR_STOPPED = 0,
    TMR_STARTED,
    TMR_EXPIRED,
} tmr_state_t;

typedef uint32_t tmr_ticks_t;

typedef struct
{
    tmr_state_t state;           ///< State of timer: STOPPED, STARTED or EXPIRED
    tmr_ticks_t start_tick;      ///< Tick when timer started
    tmr_ticks_t delay_in_ticks;  ///< Timer delay
} tmr_t;
/**************end struct tmr_t************/

extern void SysTick_Configuration(void);
extern void tmr_start(tmr_t *tmr,const tmr_ticks_t delay_in_ticks);
extern bool_t tmr_has_expired(tmr_t *tmr);
extern void tmr_reset(tmr_t *tmr);
extern void tmr_stop(tmr_t *tmr);

extern void hardkey_short(uint8_t key);
extern void hardkey_long(uint8_t key);
extern void power_on(uint8_t power_num);
extern void power_off(uint8_t power_num);
extern void rotate_up(uint8_t rotate_num,uint8_t step);
extern void rotate_down(uint8_t rotate_num,uint8_t step);
extern void SW_J_on(uint8_t SWJ_num);
extern void SW_J_off(uint8_t SWJ_num);
extern void Uart_send_feckback(void);
extern void keyCombination1(void);
extern void keyCombination2(void);
extern void knob_up(uint8_t knob_num, uint8_t vol);
extern void knob_down(uint8_t knob_num, uint8_t vol);
extern void aux_switch(void);

extern tmr_t hardkey_tmr[19];
extern mode_state_t hardkey_mod[19];
extern uint8_t once_start[19];
extern uint8_t pwr_mod[3];
extern tmr_t rotate_tmr[3];
extern rotate_mode_t rotate_mode[3];
extern uint8_t rotate_step[3];
extern uint8_t roate_st[3];
extern uint8_t msc_3A;
extern uint8_t msc_10A;
extern uint8_t J[5];
extern uint8_t USB[8];
extern tmr_t combinTmr[2];
extern uint8_t combinStatus[2];
extern uint8_t combinOnceStart[3];
extern rotate_mode_t knob_mode[3];
extern uint8_t knob_vol[3];
extern uint8_t knob_start[3];
extern uint8_t aux_st;

#endif
