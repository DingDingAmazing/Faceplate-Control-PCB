#include "gpio_driver.h"

/*********74hc595引脚定义*************************************/
#define HC595_OE1     GPIO_Pin_8     //PA8
#define HC595_OE2     GPIO_Pin_9     //PC9
#define HC595_OE3     GPIO_Pin_8     //PC8
#define HC595_OE4     GPIO_Pin_0     //PC0

#define HC595_STCP    GPIO_Pin_4     //PA4
#define HC595_SHCP    GPIO_Pin_5     //PA5

#define HC595_SDI1    GPIO_Pin_6     //PC6
#define HC595_SDI2    GPIO_Pin_15    //PB15
#define HC595_SDI3    GPIO_Pin_14    //PB14
#define HC595_SDI4    GPIO_Pin_13    //PB13

#define M_595_OE1_HIGH()     GPIO_SetBits(GPIOA, HC595_OE1)
#define M_595_OE1_LOW()      GPIO_ResetBits(GPIOA, HC595_OE1)

#define M_595_OE2_HIGH()     GPIO_SetBits(GPIOC, HC595_OE2)
#define M_595_OE2_LOW()      GPIO_ResetBits(GPIOC, HC595_OE2)

#define M_595_OE3_HIGH()     GPIO_SetBits(GPIOC, HC595_OE3)
#define M_595_OE3_LOW()      GPIO_ResetBits(GPIOC, HC595_OE3)

#define M_595_OE4_HIGH()     GPIO_SetBits(GPIOC, HC595_OE4)
#define M_595_OE4_LOW()      GPIO_ResetBits(GPIOC, HC595_OE4)

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

#define M_595_SDI4_HIGH()    GPIO_SetBits(GPIOB,     HC595_SDI4)
#define M_595_SDI4_LOW()     GPIO_ResetBits(GPIOB,   HC595_SDI4)

/*********74hc244引脚定义*************************************/
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

/*********微秒延时*************************************/
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

/*********毫秒延时*************************************/
void bsp_mDelay (const uint32_t msec)
{
    bsp_uDelay(msec * 1000);   
}

/*********使能GPIO口管脚时钟*************************************/
static void RCC_Configuration(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB| RCC_AHBPeriph_GPIOC, ENABLE);
}

/*********配置GPIO口输出模式*************************************/
static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = HC595_OE1 | HC595_STCP | HC595_SHCP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = HC595_SDI4 | HC595_SDI3 | HC595_SDI2 | HC244_A1 | HC244_CHA | HC244_A2 | HC244_B2 | HC244_CHB;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = HC595_OE4 | HC595_SDI1 | HC595_OE3 | HC595_OE2 | HC244_B1;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*********初始化GPIO口设置*************************************/
void iobus_init(void)//test pass
{
  RCC_Configuration();
  GPIO_Configuration();
	if(1)
	{
		M_595_OE1_HIGH();
		M_595_OE2_HIGH();
		M_595_OE3_HIGH();
		M_595_OE4_HIGH();
		
		M_595_STCP_HIGH();
		M_595_SHCP_HIGH();
		
		M_595_SDI1_LOW();
		M_595_SDI2_LOW();
		M_595_SDI3_LOW();
		M_595_SDI4_LOW();
		
		M_244_B1_LOW();
		M_244_A1_LOW();
		M_244_CHA_LOW();
		M_244_A2_LOW();
		M_244_B2_LOW();
		M_244_CHB_LOW();
	}
	
	if(0)//test pass
	{
		uint8_t loop;
		
		M_595_OE1_LOW();//ok
		M_595_OE2_LOW();//ok
		M_595_OE3_LOW();//ok
		M_595_OE4_LOW();//ok
		
		M_595_STCP_HIGH();//OK
		M_595_SHCP_HIGH();//OK
		
		M_595_SDI1_HIGH();//ok
		M_595_SDI2_HIGH();//ok
		M_595_SDI3_HIGH();//ok
		M_595_SDI4_HIGH();//ok
		
		M_244_B1_HIGH();//0k
		M_244_A1_LOW();//OK
		M_244_CHA_HIGH();//OK---CHA==1,then not change
		bsp_uDelay(5);
		M_244_A1_HIGH();//ok
		M_244_A2_HIGH();//ok
		M_244_B2_HIGH();//ok
		M_244_CHB_LOW();//ok
		
		
		M_595_STCP_LOW();
		bsp_uDelay(5);
		for(loop=0;loop<8;loop++)
		{
			M_595_SHCP_LOW();
			bsp_uDelay(5);
			M_595_SHCP_HIGH();		
			bsp_uDelay(5);
		}
		M_595_STCP_HIGH();
		
	}
	
}

/*********74hc595按组输出*************************************/
iobus_t iobus_data;
void iobus_s2p_group_output(void)//test pass
{
	uint8_t loop;
	M_595_OE1_LOW();
	M_595_OE2_LOW();
	M_595_OE3_LOW();
	M_595_OE4_LOW();
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

/*********74hc595输出测试*************************************/
void iobus_s2p_all_set(void)//test pass
{
	iobus_data.s2p_data[0] = 0xfe;
  iobus_data.s2p_data[1] = 0xfe;
  iobus_data.s2p_data[2] = 0xfe;
//  iobus_data.s2p_data[3] = 0x3d;
	iobus_s2p_group_output();
}

/*********74hc595输出测试2*************************************/
void iobus_s2p_all_clear(void)//test pass
{
  iobus_data.s2p_data[0] = 0;
  iobus_data.s2p_data[1] = 0;
  iobus_data.s2p_data[2] = 0;
//  iobus_data.s2p_data[3] = 0;
  iobus_s2p_group_output();
}

/*********74hc595逻辑1*************************************/
static void iobus_s2p_set(iobus_group_t group, iobus_offset_t offset)//test pass
{
    iobus_data.s2p_data[group] |= offset;
}
/*********74hc595逻辑2*************************************/
static void iobus_s2p_clear(iobus_group_t group, iobus_offset_t offset)//test pass
{
    iobus_data.s2p_data[group] &= ~offset;	
}
/*********按键控制逻辑1*************************************/
static void key_on(uint16_t idx)//test pass
{
    iobus_param_t iobus_param;

    iobus_param.group = HIBYTE(idx);
    iobus_param.offset = LOBYTE(idx);
	
    iobus_s2p_set(iobus_param.group,iobus_param.offset);
}
/*********按键控制逻辑2*************************************/
void key_off(uint16_t idx)//test pass
{
    iobus_param_t iobus_param;

    iobus_param.group = HIBYTE(idx);
    iobus_param.offset = LOBYTE(idx);

    iobus_s2p_clear(iobus_param.group,iobus_param.offset);
}
/*********按键控制逻辑3*************************************/
void key_set(uint16_t idx, uint8_t val)//test pass
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
/*********按键控制逻辑4*************************************/
void key_update(void)//test pass
{
    iobus_s2p_group_output();
}

/*********旋钮控制逻辑1*************************************/
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
}
