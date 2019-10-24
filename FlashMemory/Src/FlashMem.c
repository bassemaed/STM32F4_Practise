#include "FlashMem.h"

int Erase(uint32_t StartAddress, uint32_t EndAddress){
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t FirstSector = 0;
	uint32_t NbOfSectors = 0;
	uint32_t SECTORError = 0;
	HAL_FLASH_Unlock();
	/* Get the 1st sector to erase */
	FirstSector = GetSector(StartAddress);
	/* Get the number of sector to erase from 1st sector*/
	NbOfSectors = GetSector(EndAddress) - FirstSector + 1;
	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector        = FirstSector;
	EraseInitStruct.NbSectors     = NbOfSectors;

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
		return 0;
	HAL_FLASH_Lock();
	return 1;
}
int ProgramByByte(uint32_t InAddress, uint32_t InSize, uint8_t* InData){
	HAL_FLASH_Unlock();
	int i = 0;
	for(i=0;i< InSize;i++){
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, InAddress, *(InData+i)) == HAL_OK){
			InAddress = InAddress + 1;
		}
		else
			return 0;
	}
	HAL_FLASH_Lock();
	return 1;
}
int ProgramByHalfWord(uint32_t InAddress, uint32_t InSize, uint16_t* InData){
	HAL_FLASH_Unlock();
	int i = 0;
	for(i=0;i< InSize;i++){
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, InAddress, *(InData+i)) == HAL_OK){
			InAddress = InAddress + 2;
		}
		else
			return 0;
	}
	HAL_FLASH_Lock();
	return 1;
}
int ProgramByWord(uint32_t InAddress, uint32_t InSize, uint32_t* InData){
	HAL_FLASH_Unlock();
	int i = 0;
	for(i=0;i< InSize;i++){
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, InAddress, *(InData+i)) == HAL_OK){
			InAddress = InAddress + 4;
		}
		else
			return 0;
	}
	HAL_FLASH_Lock();
	return 1;
}
int ProgramByDoubleWord(uint32_t InAddress, uint32_t InSize, uint64_t* InData){
	HAL_FLASH_Unlock();
	int i = 0;
	for(i=0;i< InSize;i++){
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, InAddress, *(InData+i)) == HAL_OK){
			InAddress = InAddress + 8;
		}
		else
			return 0;
	}
	HAL_FLASH_Lock();
	return 1;
}
void ReadByByte(uint32_t InAddress, uint32_t InSize, uint8_t* InData){
	int i = 0;
	for(i = 0;i< InSize;i++){
		InData[i] = *(__IO uint8_t *)InAddress;
		InAddress = InAddress + 1;
	}
}
void ReadByHalfWord(uint32_t InAddress, uint32_t InSize, uint16_t* InData){
	int i = 0;
	for(i = 0;i< InSize;i++){
		InData[i] = *(__IO uint16_t *)InAddress;
		InAddress = InAddress + 2;
	}
}
void ReadByWord(uint32_t InAddress, uint32_t InSize, uint32_t* InData){
	int i = 0;
	for(i = 0;i< InSize;i++){
		InData[i] = *(__IO uint32_t *)InAddress;
		InAddress = InAddress + 4;
	}
}
void ReadByDoubleWord(uint32_t InAddress, uint32_t InSize, uint64_t* InData){
	int i = 0;
	for(i = 0;i< InSize;i++){
		InData[i] = *(__IO uint64_t *)InAddress;
		InAddress = InAddress + 8;
	}
}
static uint32_t GetSector(uint32_t Address){
	uint32_t sector = 0;
	if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
		sector = FLASH_SECTOR_0;
	else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
		sector = FLASH_SECTOR_1;
	else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
		sector = FLASH_SECTOR_2;
	else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
		sector = FLASH_SECTOR_3;
	else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
		sector = FLASH_SECTOR_4;
	else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
		sector = FLASH_SECTOR_5;
	else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
		sector = FLASH_SECTOR_6;
	else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
		sector = FLASH_SECTOR_7;
	else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
		sector = FLASH_SECTOR_8;
	else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
		sector = FLASH_SECTOR_9;
	else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
		sector = FLASH_SECTOR_10;
	else if((Address < ADDR_FLASH_SECTOR_12) && (Address >= ADDR_FLASH_SECTOR_11))
		sector = FLASH_SECTOR_11;
	else if((Address < ADDR_FLASH_SECTOR_13) && (Address >= ADDR_FLASH_SECTOR_12))
		sector = FLASH_SECTOR_12;
	else if((Address < ADDR_FLASH_SECTOR_14) && (Address >= ADDR_FLASH_SECTOR_13))
		sector = FLASH_SECTOR_13;
	else if((Address < ADDR_FLASH_SECTOR_15) && (Address >= ADDR_FLASH_SECTOR_14))
		sector = FLASH_SECTOR_14;
	else if((Address < ADDR_FLASH_SECTOR_16) && (Address >= ADDR_FLASH_SECTOR_15))
		sector = FLASH_SECTOR_15;
	else if((Address < ADDR_FLASH_SECTOR_17) && (Address >= ADDR_FLASH_SECTOR_16))
		sector = FLASH_SECTOR_16;
	else if((Address < ADDR_FLASH_SECTOR_18) && (Address >= ADDR_FLASH_SECTOR_17))
		sector = FLASH_SECTOR_17;
	else if((Address < ADDR_FLASH_SECTOR_19) && (Address >= ADDR_FLASH_SECTOR_18))
		sector = FLASH_SECTOR_18;
	else if((Address < ADDR_FLASH_SECTOR_20) && (Address >= ADDR_FLASH_SECTOR_19))
		sector = FLASH_SECTOR_19;
	else if((Address < ADDR_FLASH_SECTOR_21) && (Address >= ADDR_FLASH_SECTOR_20))
		sector = FLASH_SECTOR_20;
	else if((Address < ADDR_FLASH_SECTOR_22) && (Address >= ADDR_FLASH_SECTOR_21))
		sector = FLASH_SECTOR_21;
	else if((Address < ADDR_FLASH_SECTOR_23) && (Address >= ADDR_FLASH_SECTOR_22))
		sector = FLASH_SECTOR_22;
	else
		sector = FLASH_SECTOR_23;
  return sector;
}
static uint32_t GetSectorSize(uint32_t Sector){
	uint32_t sectorsize = 0x00;
	if((Sector == FLASH_SECTOR_0) || (Sector == FLASH_SECTOR_1) || (Sector == FLASH_SECTOR_2) ||\
     (Sector == FLASH_SECTOR_3) || (Sector == FLASH_SECTOR_12) || (Sector == FLASH_SECTOR_13) ||\
     (Sector == FLASH_SECTOR_14) || (Sector == FLASH_SECTOR_15))
		sectorsize = 16 * 1024;
	else if((Sector == FLASH_SECTOR_4) || (Sector == FLASH_SECTOR_16))
		sectorsize = 64 * 1024;
	else
		sectorsize = 128 * 1024;
	return sectorsize;
}
