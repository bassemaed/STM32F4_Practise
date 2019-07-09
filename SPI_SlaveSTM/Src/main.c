#include "config.h"

uint8_t aTxBuffer[] = {15,20,33,69,45};
#define BUFFERSIZE						(COUNTOF(aTxBuffer) - 1)
#define COUNTOF(__BUFFER__)   			(sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
uint8_t aRxBuffer[5];
enum {
  TRANSFER_WAIT,
  TRANSFER_COMPLETE,
  TRANSFER_ERROR
};
__IO uint32_t wTransferState = TRANSFER_WAIT;


int main(void){
    HAL_Init();
    SystemClock_Config();
    UartConfig();
    SpiConfig();
    GpioConfig();
#ifdef MASTER_BOARD
    while(1){
    	BSP_LED_Off(LED1);
    	BSP_LED_Off(LED2);
    	BSP_LED_Off(LED3);
    	BSP_LED_Off(LED4);
    	while (BSP_PB_GetState(BUTTON_USER) != GPIO_PIN_SET){
    	    	    BSP_LED_Toggle(LED2);
    	    	    HAL_Delay(100);
    	}
    	BSP_LED_Off(LED2);

    	if(HAL_SPI_Transmit_DMA(&SpiHandle1, (uint8_t*)aTxBuffer, 5) != HAL_OK){
    		Print("Error In Send \n");
    		Error_Handler();
    	}
    	while (wTransferState == TRANSFER_WAIT){}
    	switch(wTransferState){
    		case TRANSFER_COMPLETE :
    			Print("Tx Transfer complete \n");
    			wTransferState = TRANSFER_WAIT;
    	    	break;
    	    default :
    	    	Print("Tx Transfer not complete \n");
    	    	Error_Handler();
    	    	break;
    	}
    	HAL_Delay(2000);

    }
}
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
    /* Turn LED2 on: Transfer in transmission process is complete */
	BSP_LED_On(LED2);
    wTransferState = TRANSFER_COMPLETE;
}
#else
    while(1){
    	BSP_LED_Off(LED1);
    	BSP_LED_Off(LED2);
    	BSP_LED_Off(LED3);
    	BSP_LED_Off(LED4);
    	if(HAL_SPI_Receive_DMA(&SpiHandle1,(uint8_t *)aRxBuffer, 5) != HAL_OK){
    		Print("Error In Receive \n");
    		Error_Handler();
    	}
    	while (wTransferState == TRANSFER_WAIT){}
    	switch(wTransferState){
    		case TRANSFER_COMPLETE :
    			Print("Rx Transfer complete: ");
    			wTransferState = TRANSFER_WAIT;
    			for(int i = 0;i<5;i++)Print("%d ", *(aRxBuffer+i));
    			Print("\n");
    	    	break;
    	    default :
    	    	Print("Rx Transfer not complete \n");
    	    	Error_Handler();
    	    	break;
    	}

    }
}
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	/* Turn LED4 on: Transfer in reception process is complete */
	BSP_LED_On(LED4);
	wTransferState = TRANSFER_COMPLETE;
}
#endif
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi){
	wTransferState = TRANSFER_ERROR;
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){
  /* Infinite loop */
  while (1)
  {
  }
}
#endif
