#ifndef __FLASHMEM_H__
#define __FLASHMEM_H__

#include "stm32f4xx_hal.h"
#include "FlashAddresses.h"
#include <stdint.h>

int Erase(uint32_t, uint32_t);
int ProgramByByte(uint32_t, uint32_t, uint8_t*);
int ProgramByHalfWord(uint32_t, uint32_t, uint16_t*);
int ProgramByWord(uint32_t, uint32_t, uint32_t*);
int ProgramByDoubleWord(uint32_t, uint32_t, uint64_t*);
void ReadByByte(uint32_t, uint32_t, uint8_t*);
void ReadByHalfWord(uint32_t, uint32_t, uint16_t*);
void ReadByWord(uint32_t, uint32_t, uint32_t*);
void ReadByDoubleWord(uint32_t, uint32_t, uint64_t*);
static uint32_t GetSector(uint32_t Address);
static uint32_t GetSectorSize(uint32_t Sector);


#endif
