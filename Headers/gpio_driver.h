#ifndef _GPIO_DRIVER_H
#define _GPIO_DRIVER_H

#include "stm32f0xx.h"

#define IOBUS_S2P_GROUP_NUM	4
typedef unsigned char UINT8;
typedef unsigned short UINT16;
#define BYTE UINT8
#define WORD UINT16
#define HIBYTE(a) ((BYTE)(a>>8))
#define LOBYTE(a) ((BYTE)a)

typedef struct iobus_s{
	uint8_t s2p_data[IOBUS_S2P_GROUP_NUM];	
}iobus_t;

typedef uint8_t 	iobus_group_t;
typedef uint8_t 	iobus_offset_t;

typedef struct iobus_param_s{
  uint8_t group;
  uint8_t offset;
}iobus_param_t;

extern iobus_t iobus_data;

extern void iobus_init(void);
extern void key_set(uint16_t idx, uint8_t val);
extern void key_update(void);
extern void ROT(uint8_t num, uint8_t en);
void bsp_mDelay (const uint32_t msec);
void bsp_uDelay (const uint32_t usec);
void iobus_s2p_all_set(void);
void iobus_s2p_all_clear(void);
#endif
