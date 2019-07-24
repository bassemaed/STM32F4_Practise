#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include "diag/Trace.h"
#include <inttypes.h>
#include "stm32f4xx_hal.h"
#include "stm32469i_discovery.h"

UART_HandleTypeDef                      UartHandle1;
I2C_HandleTypeDef						I2CHandle1;

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

#define I2Cx                            I2C1
#define I2Cx_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define I2Cx_FORCE_RESET()              __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_8
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SDA_PIN                    GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2Cx_SCL_SDA_AF                 GPIO_AF4_I2C1

#define BMP180_ADDRESS			0xEE

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

#define I2C_TIMEOUT_MAX					50

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

void SystemClock_Config(void);
void Error_Hanlder(void);
void GpioConfig(void);
void UartConfig(void);
int PrintConfig (__const char * format, va_list args);
int Print (__const char * format, ...);
void I2CConfig(void);

StatusTypeDef BMP_SensorInit(void);
double BMP_GetTemp(void);


#endif
