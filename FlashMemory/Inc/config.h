#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>
#include <stdarg.h>
#include "stm32f4xx_hal.h"
#include "stm32469i_discovery.h"
#include "FlashMem.h"
#include <inttypes.h>

UART_HandleTypeDef                      UartHandle1;

/* First UART - USART3 for printing */
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

void SystemClock_Config(void);
void Error_Handler(void);
void UartConfig(void);
int PrintConfig (__const char * format,va_list args);
int Print (__const char * format, ...);
int ScanConfig(__const char * format, va_list args);
int Scan(__const char * format, ...);
void MPUConfig(void);

#endif /* __CONFIG_H__ */

