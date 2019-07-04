#include "config.h"

uint8_t RxBuffer[2], TxBuffer[2];

/*
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
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
void SpiConfig(void){
	SpiHandle1.Instance            		= SPIx;
	SpiHandle1.Init.BaudRatePrescaler 	= SPI_BAUDRATEPRESCALER_16;
	SpiHandle1.Init.Direction         	= SPI_DIRECTION_2LINES;
	SpiHandle1.Init.CLKPhase          	= SPI_PHASE_1EDGE;
	SpiHandle1.Init.CLKPolarity       	= SPI_POLARITY_LOW;
	SpiHandle1.Init.DataSize          	= SPI_DATASIZE_8BIT;
	SpiHandle1.Init.FirstBit          	= SPI_FIRSTBIT_MSB;
	SpiHandle1.Init.TIMode            	= SPI_TIMODE_DISABLE;
	SpiHandle1.Init.CRCCalculation    	= SPI_CRCCALCULATION_DISABLE;
	SpiHandle1.Init.CRCPolynomial     	= 7;
	SpiHandle1.Init.NSS               	= SPI_NSS_SOFT;
	SpiHandle1.Init.Mode				= SPI_MODE_MASTER;

	if(HAL_SPI_Init(&SpiHandle1) != HAL_OK){
		/* Initialization Error */
		Error_Handler();
	}
}
void SetNSS(void){
	HAL_GPIO_WritePin(SPIx_NSS_GPIO_PORT,SPIx_NSS_PIN, GPIO_PIN_SET);
}
void ResetNSS(void){
	HAL_GPIO_WritePin(SPIx_NSS_GPIO_PORT,SPIx_NSS_PIN, GPIO_PIN_RESET);
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
void GpioConfig(void){
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	/* Configure Key Button */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
}
StatusTypeDef SensorInit(void){
	uint8_t LocalData = 0;
	/* Write CTRL_REG_2 */
	SensorWriteReg(L3G4200_CTRL_REG_2, 0x00);
	LocalData = SensorReadReg(L3G4200_CTRL_REG_2);
	if(LocalData != 0) return STATUS_ERROR;
	/* Write CTRL_REG_4 */
	SensorWriteReg(L3G4200_CTRL_REG_4, 0x00);
	LocalData = SensorReadReg(L3G4200_CTRL_REG_4);
	if(LocalData != 0) return STATUS_ERROR;
	/* Write CTRL_REG_5 */
	SensorWriteReg(L3G4200_CTRL_REG_5, 0x12);
    LocalData = SensorReadReg(L3G4200_CTRL_REG_5);
    if(LocalData != 0x12) return STATUS_ERROR;
	/* Write CTRL_REG_1 */
    SensorWriteReg(L3G4200_CTRL_REG_1, 0x1F);
    LocalData = SensorReadReg(L3G4200_CTRL_REG_1);
    if(LocalData != 0x1F) return STATUS_ERROR;
    /* Check WHO_AM_I */
    LocalData = SensorReadReg(L3G4200_WHO_AM_I);
    if(LocalData != 0xD3) return STATUS_ERROR;
    return STATUS_OK;
}
uint8_t SensorReadReg(uint8_t InAdd){
	uint8_t LocalDataOut;
	ResetNSS();
	TxBuffer[0] = InAdd | 0x80;
	if(HAL_SPI_Transmit(&SpiHandle1,(uint8_t*)TxBuffer,1,SPI_TIMEOUT_MAX) != HAL_OK) Error_Handler();
	if(HAL_SPI_Receive(&SpiHandle1,(uint8_t*)RxBuffer,1,SPI_TIMEOUT_MAX) != HAL_OK) Error_Handler();
	LocalDataOut =  (uint8_t)RxBuffer[0];
	SetNSS();
	TxBuffer[0] = 0;
	TxBuffer[1] = 0;
	RxBuffer[0] = 0;
	RxBuffer[1] = 0;
	return LocalDataOut;
}
void SensorWriteReg(uint8_t InAdd, uint8_t InData){
	uint8_t TxBuffer[2];
	ResetNSS();
	TxBuffer[0] = InAdd;
	TxBuffer[1] = InData;
	if(HAL_SPI_Transmit(&SpiHandle1,(uint8_t*)TxBuffer,2,SPI_TIMEOUT_MAX) != HAL_OK) Error_Handler();
	SetNSS();
	TxBuffer[0] = 0;
	TxBuffer[1] = 0;
	RxBuffer[0] = 0;
	RxBuffer[1] = 0;
}
uint8_t SensorGetData(SensorData* InSensorData){
	uint8_t LocalDataOut;
	uint8_t LocalDataHi, LocalDataLo;
	float LocalTemp;
	LocalDataOut = SensorReadReg(L3G4200_STATUS_REG);
    if(LocalDataOut & 0x08){
    	if(LocalDataOut & 0x80){
    		LocalDataHi =  SensorReadReg(L3G4200_OUT_X_H);
    		LocalDataLo =  SensorReadReg(L3G4200_OUT_X_L);
    		InSensorData->DataX = ((LocalDataHi << 8) | LocalDataLo);
    		LocalTemp = (float)(InSensorData->DataX*8.75*0.001);
    		InSensorData->DataX = (int16_t)LocalTemp;
    		LocalDataHi =  SensorReadReg(L3G4200_OUT_Y_H);
    		LocalDataLo =  SensorReadReg(L3G4200_OUT_Y_L);
    		InSensorData->DataY = ((LocalDataHi << 8) | LocalDataLo);
    		LocalTemp = (float)(InSensorData->DataY*8.75*0.001);
    		InSensorData->DataY = (int16_t)LocalTemp;
    		LocalDataHi =  SensorReadReg(L3G4200_OUT_Z_H);
    		LocalDataLo =  SensorReadReg(L3G4200_OUT_Z_L);
    		InSensorData->DataZ = ((LocalDataHi << 8) | LocalDataLo);
    		LocalTemp = (float)(InSensorData->DataZ*8.75*0.001);
    		InSensorData->DataZ = (int16_t)LocalTemp;
    		return 1;
    	}
    	return 0;
    }
    return 0;
}
void SensorPrintData(SensorData* InSensorData){
	Print("X Is: %hd ", InSensorData->DataX);
	Print("Y Is: %hd ", InSensorData->DataY);
	Print("Z Is: %hd ", InSensorData->DataZ);
	Print("\n");
}
