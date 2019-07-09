#include "config.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

extern SPI_HandleTypeDef 	SpiHandle1;

void NMI_Handler(void){
}

void HardFault_Handler(void){
    while (1){
    }
}

void MemManage_Handler(void){
    while (1){
    }
}

void BusFault_Handler(void){
    while (1){
    }
}
void UsageFault_Handler(void){
    while (1){
    }
}
void SVC_Handler(void){
}

void DebugMon_Handler(void){
}

void PendSV_Handler(void){
}

void SysTick_Handler(void){
    HAL_IncTick();
}

void SPIx_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(SpiHandle1.hdmarx);
}

/**
  * @brief  This function handles DMA Tx interrupt request.
  * @param  None
  * @retval None
  */
void SPIx_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(SpiHandle1.hdmatx);
}

/**
  * @brief  This function handles SPI interrupt request.
  * @param  None
  * @retval None
  */
void SPIx_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&SpiHandle1);
}


