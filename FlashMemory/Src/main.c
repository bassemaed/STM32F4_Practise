#include "config.h"

#define FLASH_START_ADD   ADDR_FLASH_SECTOR_11
#define FLASH_END_ADD		ADDR_FLASH_SECTOR_12-1

int main(void){
	HAL_Init();
	SystemClock_Config();
	UartConfig();
	char C;
	/* Initialize LED1, LED2 and LED3 */
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	uint8_t TheData[5] = {0x98, 0x12, 0x77, 0x55, 0x68};
	uint8_t OutData[5];
	Print("Enter P for programming and R for reading \n");
	Scan("%c", &C);
	if(C == 'P' || C=='p'){
		Print("Program pressed \n");
		if (Erase(FLASH_START_ADD,FLASH_END_ADD) != 1) Error_Handler();
		if (ProgramByByte(FLASH_START_ADD, 5, TheData)!= 1) Error_Handler();
	}
	if(C == 'R' || C=='r'){
		Print("Read pressed \n");
		ReadByByte(FLASH_START_ADD,5,OutData);
		Print("Data is: ");
		for(int i = 0 ; i < 5;i++){
			Print("%d ", (int)OutData[i]);
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
