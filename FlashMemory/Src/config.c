#include "config.h"

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
int ScanConfig(__const char * format, va_list args) {
    unsigned i=0;
    char ch = 0;
    char buffer[256];
    int ret = 0;
    while((i<sizeof(buffer))&&(ch!='\n')&&(ch!='\r')){
        HAL_StatusTypeDef status = HAL_TIMEOUT;
        while (status == HAL_TIMEOUT) {
            status =  HAL_UART_Receive(&UartHandle1, (uint8_t *)&ch,1, HAL_MAX_DELAY);
            if (status == HAL_TIMEOUT) {
                HAL_UART_DeInit(&UartHandle1);
                HAL_UART_Init(&UartHandle1);
            }
            else
                break;
        }

        buffer[i]=ch;
        i++;
        ret = vsscanf(buffer, format, args);
     //   if (ret > 0)
       //     break;
    }
    buffer[i]='\0';
    return ret;
}
int Scan(__const char * format, ...) {
    va_list args;
    va_start(args, format);
    int size = ScanConfig(format, args);
    va_end(args);
    return size;
}
void MPUConfig(void){
	MPU_Region_InitTypeDef MPU_InitStruct;
	/* Disable the MPU */
	HAL_MPU_Disable();
	/* Configure the MPU attributes for SDRAM */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = 0x080E0000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_128KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	/* Enable the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}


