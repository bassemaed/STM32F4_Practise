#include "config.h"

uint8_t RxBuffer[2], TxBuffer[2];

int16_t AC1, AC2, AC3, B1, B2, MB, MC, MD;
uint16_t AC4, AC5, AC6, UT;
double MC_, MD_, AC5_;

void SystemClock_Config(void){
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8; /* if left 25 that will give us a frequency of 57.6 M instead of 180 M */
    RCC_OscInitStruct.PLL.PLLN = 360;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    RCC_OscInitStruct.PLL.PLLR = 6;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* Activate the Over-Drive mode */
    HAL_PWREx_EnableOverDrive();

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}
void Error_Handler(void){
    while(1){
        BSP_LED_On(LED2);
    }
}
void GpioConfig(void){
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
}
void UartConfig(void){
    UartHandle1.Instance                    = USARTx;
    UartHandle1.Init.BaudRate               = 9600;
    UartHandle1.Init.WordLength             = UART_WORDLENGTH_8B;
    UartHandle1.Init.StopBits               = UART_STOPBITS_1;
    UartHandle1.Init.Parity                 = UART_PARITY_NONE;
    UartHandle1.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
    UartHandle1.Init.Mode                   = UART_MODE_TX_RX;
    UartHandle1.Init.OverSampling           = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&UartHandle1) != HAL_OK){
        Error_Handler();
    }
}
int PrintConfig (__const char * format, va_list args) {
    int size;
    char buffer[256];
    size = vsnprintf (buffer, sizeof(buffer)-1, format, args);
    buffer[size]=0;
    HAL_UART_Transmit(&UartHandle1, (uint8_t *)buffer, size, HAL_MAX_DELAY); //0xFFFF);
    return size;
}
int Print (__const char * format, ...) {
    va_list args;
    va_start(args, format);
    int size = PrintConfig(format, args);
    va_end(args);
    return size;
}
void I2CConfig(void){
	I2CHandle1.Instance =  I2Cx;
	I2CHandle1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2CHandle1.Init.ClockSpeed = 100000;
	I2CHandle1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	I2CHandle1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2CHandle1.Init.OwnAddress1 = 0;
	I2CHandle1.Init.OwnAddress2 = 0;
	I2CHandle1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	I2CHandle1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	if (HAL_I2C_Init(&I2CHandle1) != HAL_OK)
		Error_Handler();
}
StatusTypeDef BMP_SensorInit(void){
	uint8_t Data[22];
	uint8_t i = 0;
	if (HAL_I2C_Mem_Read(&I2CHandle1, BMP180_ADDRESS, 0xAA, I2C_MEMADD_SIZE_8BIT, &Data[0], 22,1000) != HAL_OK)
		Error_Handler();
	AC1 = 	(int16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	AC2 = 	(int16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	AC3 = 	(int16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	AC4 = 	(uint16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	AC5 = 	(uint16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	AC6 = 	(uint16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	B1 	= 	(int16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	B2 	= 	(int16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	MB 	= 	(int16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	MC 	= 	(int16_t)	(Data[i] << 8 | Data[i + 1]); i += 2;
	MD 	= 	(int16_t)	(Data[i] << 8 | Data[i + 1]);

	AC5_ = (double)((pow(2,-15) / 160) * AC5);
	MC_  = (double)((pow(2,11) / pow(160,2)) * MC);
	MD_  = (double) (MD / 160.0);
	/*
	 * Debugging the EEPROM values
	Print("AC1 %d  AC2 %d  AC3 %d AC4 %d  AC5 %d AC6 %d \n",AC1,AC2,AC3,AC4,AC5,AC6);
	Print("B1 %d B2 %d  MB %d MC %d  MD %d  \n",B1,B2,MB,MC,MD);
	*/
	return STATUS_OK;
}
double BMP_GetTemp(void){
	uint8_t LocalData = 0x2E;
	uint8_t OutputData[2];
	long LocalUt = 0;
	double OutTemp;
	double LocalA;
	if (HAL_I2C_Mem_Write(&I2CHandle1, BMP180_ADDRESS, 0xF4, I2C_MEMADD_SIZE_8BIT,&LocalData,1, 100) != HAL_OK)
		Error_Handler();
	HAL_Delay(5);
	if (HAL_I2C_Mem_Read(&I2CHandle1, BMP180_ADDRESS, 0xF6, I2C_MEMADD_SIZE_8BIT, &OutputData[0], 2,100) != HAL_OK)
		Error_Handler();
	LocalUt = (long) (OutputData[0]*256 + OutputData[1]);

	LocalA = (double)(AC5_*(LocalUt - AC6));
	OutTemp = (double)(LocalA + (MC_ / (LocalA + MD_)));
	return OutTemp;
}
