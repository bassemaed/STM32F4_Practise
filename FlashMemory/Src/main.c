#include "config.h"

#define FLASH_START_ADD   	ADDR_FLASH_SECTOR_10
#define FLASH_END_ADD		ADDR_FLASH_SECTOR_11-1

uint8_t 	InDataArray8[] = {0x12, 0x34, 0x56, 0x9A};
uint16_t 	InDataArray16[4] = {0x1234, 0x5678, 0x9ABC, 0xDE11};
uint32_t 	InDataArray32[4] = {0x12345678, 0x9ABCDEF1, 0x23456789, 0xABCDE123};

uint8_t		OutDataArray8[4];
uint16_t	OutDataArray16[4];
uint32_t	OutDataArray32[4];

uint32_t 	MemAddress = 0;
int main(void){
	HAL_Init();
	SystemClock_Config();
	MPUConfig();
	UartConfig();
	char C;
	/* Initialize LED1, LED2 and LED3 */
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	Print("Enter P for programming and R for reading \n");
	Scan("%c", &C);
	if(C == 'P' || C=='p'){
		Print("Program pressed \n");
		MemAddress =  FLASH_START_ADD;
		if (Erase(FLASH_START_ADD,FLASH_END_ADD) != 1) Error_Handler();
		if (ProgramByByte(MemAddress, 4, InDataArray8)!= 1) Error_Handler();
		MemAddress =  MemAddress+4;
		if (ProgramByHalfWord(MemAddress, 4, InDataArray16)!= 1) Error_Handler();
		MemAddress =  MemAddress+8;
		if (ProgramByWord(MemAddress, 4, InDataArray32)!= 1) Error_Handler();
		Print("Programming done \n");
	}
	if(C == 'R' || C=='r'){
		Print("Read pressed \n");
		MemAddress =  FLASH_START_ADD;
		ReadByByte(MemAddress,4,OutDataArray8);
		MemAddress = MemAddress + 4;
		ReadByHalfWord(MemAddress,4,OutDataArray16);
		MemAddress = MemAddress + 8;
		ReadByWord(MemAddress,4,OutDataArray32);
		Print("Data is: ");
		for(int j = 0; j<3;j++){
			for(int i = 0 ; i < 4;i++){
				if (j==0)
					Print("%X ", OutDataArray8[i]);
				if (j==1)
					Print("%X ", OutDataArray16[i]);
				if (j==2)
					Print("%X ", OutDataArray32[i]);
			}
			Print("\n");
		}
	}
	while (1){
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line){
  /* Infinite loop */
  while (1)
  {
  }
}
#endif
