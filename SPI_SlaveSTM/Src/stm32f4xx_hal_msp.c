#include "config.h"

static DMA_HandleTypeDef hdma_tx;
static DMA_HandleTypeDef hdma_rx;

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi){
	GPIO_InitTypeDef  GPIO_InitStruct;
	if (hspi->Instance == SPIx){
		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		SPIx_SCK_GPIO_CLK_ENABLE();
		SPIx_MISO_GPIO_CLK_ENABLE();
		SPIx_MOSI_GPIO_CLK_ENABLE();
		/* Enable SPI clock */
		SPIx_CLK_ENABLE();
	    DMAx_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* SPI SCK GPIO pin configuration  */
		GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = SPIx_SCK_AF;
		HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MISO GPIO pin configuration  */
		GPIO_InitStruct.Pin 		= SPIx_MISO_PIN;
		GPIO_InitStruct.Alternate 	= SPIx_MISO_AF;
		HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MOSI GPIO pin configuration  */
		GPIO_InitStruct.Pin 		= SPIx_MOSI_PIN;
		GPIO_InitStruct.Alternate 	= SPIx_MOSI_AF;
		HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);

	    hdma_tx.Instance                 = SPIx_TX_DMA_STREAM;
	    hdma_tx.Init.Channel             = SPIx_TX_DMA_CHANNEL;
	    hdma_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	    hdma_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	    hdma_tx.Init.MemBurst            = DMA_MBURST_INC4;
	    hdma_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	    hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	    hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	    hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
	    hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	    hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	    hdma_tx.Init.Mode                = DMA_NORMAL;
	    hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;

	    HAL_DMA_Init(&hdma_tx);

	    /* Associate the initialized DMA handle to the the SPI handle */
	    __HAL_LINKDMA(hspi, hdmatx, hdma_tx);

	    /* Configure the DMA handler for Transmission process */
	    hdma_rx.Instance                 = SPIx_RX_DMA_STREAM;
	    hdma_rx.Init.Channel             = SPIx_RX_DMA_CHANNEL;
	    hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	    hdma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	    hdma_rx.Init.MemBurst            = DMA_MBURST_INC4;
	    hdma_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	    hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	    hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	    hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
	    hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	    hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	    hdma_rx.Init.Mode                = DMA_NORMAL;
	    hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;

	    HAL_DMA_Init(&hdma_rx);

	    /* Associate the initialized DMA handle to the the SPI handle */
	    __HAL_LINKDMA(hspi, hdmarx, hdma_rx);

	    /*##-4- Configure the NVIC for DMA #######################################*/
	    /* NVIC configuration for DMA transfer complete interrupt (SPI2_TX) */
	    HAL_NVIC_SetPriority(SPIx_DMA_TX_IRQn, 1, 1);
	    HAL_NVIC_EnableIRQ(SPIx_DMA_TX_IRQn);

	    /* NVIC configuration for DMA transfer complete interrupt (SPI2_RX) */
	    HAL_NVIC_SetPriority(SPIx_DMA_RX_IRQn, 1, 0);
	    HAL_NVIC_EnableIRQ(SPIx_DMA_RX_IRQn);

	    /*##-5- Configure the NVIC for SPI #######################################*/
	    HAL_NVIC_SetPriority(SPIx_IRQn, 1, 2);
	    HAL_NVIC_EnableIRQ(SPIx_IRQn);
	}
}
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi){
	if(hspi->Instance == SPIx){
		/*##-1- Reset peripherals ##################################################*/
		SPIx_FORCE_RESET();
		SPIx_RELEASE_RESET();

		/*##-2- Disable peripherals and GPIO Clocks ################################*/
		/* Configure SPI SCK as alternate function  */
		HAL_GPIO_DeInit(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN);
		/* Configure SPI MISO as alternate function  */
		HAL_GPIO_DeInit(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN);
		/* Configure SPI MOSI as alternate function  */
		HAL_GPIO_DeInit(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN);

	    /*##-3- Disable the DMA ####################################################*/
	    /* De-Initialize the DMA associated to transmission process */
	    HAL_DMA_DeInit(&hdma_tx);
	    /* De-Initialize the DMA associated to reception process */
	    HAL_DMA_DeInit(&hdma_rx);

	    /*##-4- Disable the NVIC for DMA ###########################################*/
	    HAL_NVIC_DisableIRQ(SPIx_DMA_TX_IRQn);
	    HAL_NVIC_DisableIRQ(SPIx_DMA_RX_IRQn);

	    /*##-5- Disable the NVIC for SPI ###########################################*/
	    HAL_NVIC_DisableIRQ(SPIx_IRQn);
	}
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart){
    GPIO_InitTypeDef  GPIO_InitStruct;

    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    USARTx_TX_GPIO_CLK_ENABLE();
    USARTx_RX_GPIO_CLK_ENABLE();

    /* Enable USARTx clock */
    USARTx_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/
    /* UART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = USARTx_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = USARTx_TX_AF;

    HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

    /* UART RX GPIO pin configuration  */
    GPIO_InitStruct.Pin = USARTx_RX_PIN;
    GPIO_InitStruct.Alternate = USARTx_RX_AF;

    HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    /*##-1- Reset peripherals ##################################################*/
    USARTx_FORCE_RESET();
    USARTx_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks #################################*/
    /* Configure USART6 Tx as alternate function  */
    HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
    /* Configure USART6 Rx as alternate function  */
    HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
}
