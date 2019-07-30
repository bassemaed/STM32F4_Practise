#include "config.h"


SensorData g_SensorData;

int main(void){
	HAL_Init();
	SystemClock_Config();
	GpioConfig();
	UartConfig();
	I2CConfig();
	if (L3G4200_SensorInit() != STATUS_OK){
		Error_Handler();
	}
	while(1){
		if (L3G4200_GetData(&g_SensorData))
			L3G4200_PrintData(&g_SensorData);
	    	HAL_Delay(500);
	    }
	return 0;
}

