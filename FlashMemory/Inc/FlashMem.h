#ifndef __FLASHMEM_H__
#define __FLASHMEM_H__

#include "stm32f4xx_hal.h"
#include "FlashAddresses.h"

int Erase(uint32_t, uint32_t);
int ProgramByByte(uint32_t, uint32_t, uint8_t*);
void ReadByByte(uint32_t, uint32_t, uint8_t*);
static uint32_t GetSector(uint32_t Address);
static uint32_t GetSectorSize(uint32_t Sector);


#endif
