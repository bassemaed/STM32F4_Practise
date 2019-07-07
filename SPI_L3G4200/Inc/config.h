#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>
#include <stdarg.h>
#include <inttypes.h>
#include "stm32f4xx_hal.h"
#include "stm32469i_discovery.h"

UART_HandleTypeDef                      UartHandle1;
SPI_HandleTypeDef						SpiHandle1;

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

#define SPIx_FORCE_RESET()              __HAL_RCC_SPI2_FORCE_RESET()
#define SPIx_RELEASE_RESET()            __HAL_RCC_SPI2_RELEASE_RESET()

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

#define L3G4200_WHO_AM_I				0x0F
#define L3G4200_CTRL_REG_1				0x20
#define	L3G4200_CTRL_REG_2				0x21
#define	L3G4200_CTRL_REG_3				0x22
#define	L3G4200_CTRL_REG_4				0x23
#define	L3G4200_CTRL_REG_5				0x24
#define	L3G4200_OUT_X_L					0x28
#define	L3G4200_OUT_X_H					0x29
#define	L3G4200_OUT_Y_L					0x2A
#define	L3G4200_OUT_Y_H					0x2B
#define	L3G4200_OUT_Z_L					0x2C
#define	L3G4200_OUT_Z_H					0x2D
#define	L3G4200_STATUS_REG				0x27

typedef enum {
	STATUS_OK       = 0x00U,
	STATUS_ERROR    = 0x01U,
	STATUS_BUSY     = 0x02U,
	STATUS_TIMEOUT  = 0x03U
}StatusTypeDef;

typedef struct {
	int16_t DataX;
	int16_t DataY;
	int16_t DataZ;
}SensorData;

/* Size of buffer */
#define BUFFERSIZE                     	(COUNTOF(aTxBuffer) - 1)
#define SPI_TIMEOUT_MAX					50
#define CMD_LENGTH                    	((uint16_t)0x0001)
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

void SystemClock_Config(void);
void Error_Handler(void);
void SpiConfig(void);
StatusTypeDef SensorInit(void);
void SetNSS(void);
void ResetNSS(void);
void UartConfig(void);
int PrintConfig (__const char * format,va_list args);
int Print (__const char * format, ...);
void GpioConfig(void);
uint8_t SensorReadReg(uint8_t);
void SensorWriteReg(uint8_t InAdd, uint8_t InData);
uint8_t SensorGetData(SensorData*);
void SensorPrintData(SensorData*);

#endif /* __CONFIG_H__ */
