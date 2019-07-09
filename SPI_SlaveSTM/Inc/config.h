#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>
#include <stdarg.h>
#include <inttypes.h>
#include "stm32f4xx_hal.h"
#include "stm32469i_discovery.h"

UART_HandleTypeDef                      UartHandle1;
SPI_HandleTypeDef						SpiHandle1;

//#define MASTER_BOARD

#define USARTx                          USART3
#define USARTx_CLK_ENABLE()             __HAL_RCC_USART3_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

#define USARTx_TX_PIN                   GPIO_PIN_11
#define USARTx_TX_GPIO_PORT             GPIOB
#define USARTx_TX_AF                    GPIO_AF7_USART3
#define USARTx_RX_PIN                   GPIO_PIN_10
#define USARTx_RX_GPIO_PORT             GPIOB
#define USARTx_RX_AF                    GPIO_AF7_USART3

#define USARTx_FORCE_RESET()            __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()          __HAL_RCC_USART3_RELEASE_RESET()

#define SPIx                            SPI2
#define SPIx_CLK_ENABLE()              	__HAL_RCC_SPI2_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()     	__HAL_RCC_GPIOD_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_NSS_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOH_CLK_ENABLE()

#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()

#define SPIx_FORCE_RESET()              __HAL_RCC_SPI2_FORCE_RESET()
#define SPIx_RELEASE_RESET()            __HAL_RCC_SPI2_RELEASE_RESET()

#define SPIx_TX_DMA_STREAM               DMA1_Stream4
#define SPIx_RX_DMA_STREAM               DMA1_Stream3
#define SPIx_TX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPIx_RX_DMA_CHANNEL              DMA_CHANNEL_0

/* Definition for SPIx's NVIC */
#define SPIx_IRQn                        SPI2_IRQn
#define SPIx_IRQHandler                  SPI2_IRQHandler

#define SPIx_DMA_TX_IRQn                 DMA1_Stream4_IRQn
#define SPIx_DMA_RX_IRQn                 DMA1_Stream3_IRQn

#define SPIx_DMA_TX_IRQHandler           DMA1_Stream4_IRQHandler
#define SPIx_DMA_RX_IRQHandler           DMA1_Stream3_IRQHandler

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                    GPIO_PIN_3
#define SPIx_SCK_GPIO_PORT              GPIOD
#define SPIx_SCK_AF                     GPIO_AF5_SPI2
#define SPIx_MISO_PIN                   GPIO_PIN_14
#define SPIx_MISO_GPIO_PORT             GPIOB
#define SPIx_MISO_AF                    GPIO_AF5_SPI2
#define SPIx_MOSI_PIN                   GPIO_PIN_15
#define SPIx_MOSI_GPIO_PORT             GPIOB
#define SPIx_MOSI_AF                    GPIO_AF5_SPI2
#define SPIx_NSS_PIN                    GPIO_PIN_6
#define SPIx_NSS_GPIO_PORT              GPIOH

typedef enum {
	STATUS_OK       = 0x00U,
	STATUS_ERROR    = 0x01U,
	STATUS_BUSY     = 0x02U,
	STATUS_TIMEOUT  = 0x03U
}StatusTypeDef;

/* Size of buffer */
#define BUFFERSIZE                     	(COUNTOF(aTxBuffer) - 1)
#define SPI_TIMEOUT_MAX					50
#define CMD_LENGTH                    	((uint16_t)0x0001)
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

void SystemClock_Config(void);
void Error_Handler(void);
void SpiConfig(void);
void UartConfig(void);
int PrintConfig (__const char * format,va_list args);
int Print (__const char * format, ...);
void GpioConfig(void);

#endif /* __CONFIG_H__ */
