#include "config.h"

double Temp;
int main(void){
	HAL_Init();
	SystemClock_Config();
	GpioConfig();
	UartConfig();
	I2CConfig();
	if (BMP_SensorInit() != STATUS_OK)
		Error_Handler();
	while (1){
		Temp = BMP_GetTemp();
		Print("Temp is %.1f \n", Temp);
		HAL_Delay(1000);
    }
	return 0;
}

