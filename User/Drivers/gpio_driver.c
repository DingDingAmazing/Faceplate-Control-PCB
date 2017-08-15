#include "gpio_driver.h"

//void GPIO_Configuration(void)
//{
//	GPIO_InitTypeDef        GPIO_InitStructure;
//	
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA |RCC_AHBPeriph_GPIOB |RCC_AHBPeriph_GPIOC |RCC_AHBPeriph_GPIOF, ENABLE);
////PA	3 pin
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
////PB	8 pin
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11 |
//																GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//		
////PC 5 pin
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8 |
//	                              GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//	
//}

#define IOBUS_GPIO_RCC     (RCC_AHBPeriph_GPIOA |RCC_AHBPeriph_GPIOB |RCC_AHBPeriph_GPIOC)

#define HC595_OE1     GPIO_Pin_9     //PC9
#define HC595_OE2     GPIO_Pin_1     //PC1
#define HC595_OE3     GPIO_Pin_8     //PC8
#define HC595_OE4     GPIO_Pin_0     //PC0
#define HC595_OE5     GPIO_Pin_8     //PA8

#define HC595_STCP    GPIO_Pin_11    //PA11
#define HC595_SHCP    GPIO_Pin_12    //PA12

#define HC595_SDI1    GPIO_Pin_6     //PC6
#define HC595_SDI2    GPIO_Pin_15    //PB15
#define HC595_SDI3    GPIO_Pin_14    //PB14
#define HC595_SDI4    GPIO_Pin_2     //PA2
#define HC595_SDI5    GPIO_Pin_15    //PA15

#define M_595_OE1_HIGH()     GPIO_SetBits(GPIOC, HC595_OE1)
#define M_595_OE1_LOW()      GPIO_ResetBits(GPIOC, HC595_OE1)

#define M_595_OE2_HIGH()     GPIO_SetBits(GPIOC, HC595_OE2)
#define M_595_OE2_LOW()      GPIO_ResetBits(GPIOC, HC595_OE2)

#define M_595_OE3_HIGH()     GPIO_SetBits(GPIOC, HC595_OE3)
#define M_595_OE3_LOW()      GPIO_ResetBits(GPIOC, HC595_OE3)

#define M_595_OE4_HIGH()     GPIO_SetBits(GPIOC, HC595_OE4)
#define M_595_OE4_LOW()      GPIO_ResetBits(GPIOC, HC595_OE4)

#define M_595_OE5_HIGH()     GPIO_SetBits(GPIOA, HC595_OE5)
#define M_595_OE5_LOW()      GPIO_ResetBits(GPIOA, HC595_OE5)

#define M_595_STCP_HIGH()    GPIO_SetBits(GPIOA, HC595_STCP)
#define M_595_STCP_LOW()     GPIO_ResetBits(GPIOA, HC595_STCP)

#define M_595_SHCP_HIGH()    GPIO_SetBits(GPIOA,     HC595_SHCP)
#define M_595_SHCP_LOW()     GPIO_ResetBits(GPIOA,   HC595_SHCP)

#define M_595_SDI1_HIGH()    GPIO_SetBits(GPIOC,     HC595_SDI1)
#define M_595_SDI1_LOW()     GPIO_ResetBits(GPIOC,   HC595_SDI1)

#define M_595_SDI2_HIGH()    GPIO_SetBits(GPIOB,     HC595_SDI2)
#define M_595_SDI2_LOW()     GPIO_ResetBits(GPIOB,   HC595_SDI2)

#define M_595_SDI3_HIGH()    GPIO_SetBits(GPIOB,     HC595_SDI3)
#define M_595_SDI3_LOW()     GPIO_ResetBits(GPIOB,   HC595_SDI3)

#define M_595_SDI4_HIGH()    GPIO_SetBits(GPIOA,     HC595_SDI4)
#define M_595_SDI4_LOW()     GPIO_ResetBits(GPIOA,   HC595_SDI4)

#define M_595_SDI5_HIGH()    GPIO_SetBits(GPIOA,     HC595_SDI5)
#define M_595_SDI5_LOW()     GPIO_ResetBits(GPIOA,   HC595_SDI5)
/////////////////////////////////////////////////////////////////
#define HC244_A1     GPIO_Pin_0     //PB0
#define HC244_A2     GPIO_Pin_2     //PB2
#define HC244_B1     GPIO_Pin_5     //PC5
#define HC244_B2     GPIO_Pin_10    //PB10
#define HC244_CHA    GPIO_Pin_1     //PB1
#define HC244_CHB    GPIO_Pin_11     //PB11

#define M_244_A1_HIGH()     GPIO_SetBits(GPIOB, HC244_A1)
#define M_244_A1_LOW()      GPIO_ResetBits(GPIOB, HC244_A1)

#define M_244_A2_HIGH()     GPIO_SetBits(GPIOB, HC244_A2)
#define M_244_A2_LOW()      GPIO_ResetBits(GPIOB, HC244_A2)

#define M_244_B1_HIGH()     GPIO_SetBits(GPIOC, HC244_B1)
#define M_244_B1_LOW()      GPIO_ResetBits(GPIOC, HC244_B1)

#define M_244_B2_HIGH()     GPIO_SetBits(GPIOB, HC244_B2)
#define M_244_B2_LOW()      GPIO_ResetBits(GPIOB, HC244_B2)

#define M_244_CHA_HIGH()     GPIO_SetBits(GPIOB, HC244_CHA)
#define M_244_CHA_LOW()      GPIO_ResetBits(GPIOB, HC244_CHA)

#define M_244_CHB_HIGH()     GPIO_SetBits(GPIOB, HC244_CHB)
#define M_244_CHB_LOW()      GPIO_ResetBits(GPIOB, HC244_CHB)

//////////////////////////////////////////////////////////////
iobus_t iobus_data;

//////////////////////////////////////////////////////////////
void bsp_uDelay (const uint32_t usec)
{
    uint32_t count = 0;
    const uint32_t utime = (48 * usec / 7);
    do
    {
        if ( ++count > utime )
        {
            return ;
        }
    }
    while (1);
}

void bsp_mDelay (const uint32_t msec)
{
    bsp_uDelay(msec * 1000);   
}

//////////////////////////////////////////////////////////////
static void RCC_Configuration(void)
{
  RCC_AHBPeriphClockCmd(IOBUS_GPIO_RCC, ENABLE);
}

static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = HC595_STCP | HC595_SHCP | HC595_SDI4 | HC595_OE5 | HC595_SDI5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = HC244_A1 | HC244_CHA | HC244_A2 | HC244_B2 | HC244_CHB | HC595_SDI3 | HC595_SDI2;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = HC595_OE4 | HC244_B1 | HC595_SDI1 | HC595_OE3 | HC595_OE2 | HC595_OE1;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	M_595_OE1_HIGH();
	M_595_OE2_HIGH();
	M_595_OE3_HIGH();
	M_595_OE4_HIGH();
	M_595_OE5_HIGH();
	M_595_STCP_HIGH();
	M_595_SHCP_HIGH();
	
	M_595_SDI1_LOW();
	M_595_SDI2_LOW();
	M_595_SDI3_LOW();
	M_595_SDI4_LOW();
	M_595_SDI5_LOW();
}

//////////////////////////////////////////////////////////////
void iobus_s2p_group_output(void)
{
	uint8_t loop;
	M_595_OE1_LOW();
	M_595_OE2_LOW();
	M_595_OE3_LOW();
	M_595_OE4_LOW();
	M_595_OE5_LOW();
	M_595_STCP_LOW();
	bsp_uDelay(5);
	
	for(loop=0;loop<8;loop++)
  {
		if(iobus_data.s2p_data[0]&(0x80>>loop))
            M_595_SDI1_HIGH();	
        else
            M_595_SDI1_LOW();	
		if(iobus_data.s2p_data[1]&(0x80>>loop))
            M_595_SDI2_HIGH();	
        else
            M_595_SDI2_LOW();	
    if(iobus_data.s2p_data[2]&(0x80>>loop))
            M_595_SDI3_HIGH();	
        else
            M_595_SDI3_LOW();	
    if(iobus_data.s2p_data[3]&(0x80>>loop))
				    M_595_SDI4_HIGH();		
        else
				    M_595_SDI4_LOW();	
		if(iobus_data.s2p_data[4]&(0x80>>loop))
				    M_595_SDI5_HIGH();		
        else
				    M_595_SDI5_LOW();	

        bsp_uDelay(5);
        M_595_SHCP_LOW();		
        bsp_uDelay(5);
        M_595_SHCP_HIGH();		
        bsp_uDelay(5);
    }
    bsp_uDelay(5);
    M_595_STCP_HIGH();		
    bsp_uDelay(5);
}

void iobus_s2p_all_set(void)
{
	iobus_data.s2p_data[0] = 0xfe;
  iobus_data.s2p_data[1] = 0xfe;
  iobus_data.s2p_data[2] = 0xfe;
  iobus_data.s2p_data[3] = 0xfe;
	iobus_data.s2p_data[4] = 0xfe;
	iobus_s2p_group_output();
}

void iobus_s2p_all_clear(void)
{
  iobus_data.s2p_data[0] = 0;
  iobus_data.s2p_data[1] = 0;
  iobus_data.s2p_data[2] = 0;
  iobus_data.s2p_data[3] = 0;
	iobus_data.s2p_data[4] = 0;
  iobus_s2p_group_output();
}

void iobus_hc244_init(void)
{
	M_244_CHA_LOW();
	M_244_CHB_LOW();
	M_244_A1_LOW();
	M_244_B1_LOW();
	M_244_A2_LOW();
	M_244_B2_LOW();
}

void iobus_init(void)
{
  RCC_Configuration();
  GPIO_Configuration();
  iobus_s2p_all_clear();
	iobus_hc244_init();
}

//////////////////////////////////////////////////////////////
static void iobus_s2p_set(iobus_group_t group, iobus_offset_t offset)
{
    iobus_data.s2p_data[group] |= offset;
}

static void iobus_s2p_clear(iobus_group_t group, iobus_offset_t offset)
{
    iobus_data.s2p_data[group] &= ~offset;	
}

static void key_on(uint16_t idx)
{
    iobus_param_t iobus_param;

    iobus_param.group = HIBYTE(idx);
    iobus_param.offset = LOBYTE(idx);
	
    iobus_s2p_set(iobus_param.group,iobus_param.offset);
}

void key_off(uint16_t idx)
{
    iobus_param_t iobus_param;

    iobus_param.group = HIBYTE(idx);
    iobus_param.offset = LOBYTE(idx);

    iobus_s2p_clear(iobus_param.group,iobus_param.offset);
}

//////////////////////////////////////////////////////////////
void key_set(uint16_t idx, uint8_t val)
{
    if(val)
    {
        key_on(idx);
    }
    else
    {
        key_off(idx);
    }
}

void key_update(void)
{
    iobus_s2p_group_output();
}

//////////////////////////////////////////////////////////////
void ROT(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 1:
			if(en)
				M_244_A1_HIGH();
			else
				M_244_A1_LOW();
			break;
			
		case 2:
			if(en)
				M_244_A2_HIGH();
			else
				M_244_A2_LOW();
			break;
			
		case 3:
			if(en)
				M_244_B1_HIGH();
			else
				M_244_B1_LOW();
			break;
			
		case 4:
			if(en)
				M_244_B2_HIGH();
			else
				M_244_B2_LOW();
			break;
			
		default:
			break;
	}
	key_update();
}
