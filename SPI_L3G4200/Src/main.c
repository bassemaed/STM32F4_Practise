#include "config.h"

SensorData g_SensorData;

int main(void){
    HAL_Init();
    SystemClock_Config();
    UartConfig();
    SpiConfig();
    if (SensorInit() != STATUS_OK) Error_Handler();
    while(1){
    	if (SensorGetData(&g_SensorData))
    		SensorPrintData(&g_SensorData);
    	HAL_Delay(500);
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
