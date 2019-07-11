#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f4xx.h"
#include "Defines.h"

/**
 * 	@brief	GPIO Pins declarations
 */
#define GPIO_PIN_0      		((uint16_t)0x0001)
#define GPIO_PIN_1      		((uint16_t)0x0002)
#define GPIO_PIN_2      		((uint16_t)0x0004)
#define GPIO_PIN_3      		((uint16_t)0x0008)
#define GPIO_PIN_4      		((uint16_t)0x0010)
#define GPIO_PIN_5      		((uint16_t)0x0020)
#define GPIO_PIN_6      		((uint16_t)0x0040)
#define GPIO_PIN_7      		((uint16_t)0x0080)
#define GPIO_PIN_8      		((uint16_t)0x0100)
#define GPIO_PIN_9      		((uint16_t)0x0200)
#define GPIO_PIN_10     		((uint16_t)0x0400)
#define GPIO_PIN_11     		((uint16_t)0x0800)
#define GPIO_PIN_12     		((uint16_t)0x1000)
#define GPIO_PIN_13     		((uint16_t)0x2000)
#define GPIO_PIN_14     		((uint16_t)0x4000)
#define GPIO_PIN_15     		((uint16_t)0x8000)
#define GPIO_PIN_ALL    		((uint16_t)0xFFFF)

#define GPIO_PINS_NUM			((uint32_t)16)

/**
 * 	@brief 	GPIO Alternative Function declarations
 * 	@brief  AF 0 selection
 */
#define GPIO_AF0_RTC_50Hz   	((uint8_t)0x00U)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           	((uint8_t)0x00U)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        	((uint8_t)0x00U)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           	((uint8_t)0x00U)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         	((uint8_t)0x00U)  /* TRACE Alternate Function mapping                          */
/**
 *	@brief  AF 1 selection
 */
#define GPIO_AF1_TIM1          	((uint8_t)0x01U)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          	((uint8_t)0x01U)  /* TIM2 Alternate Function mapping */
/**
 * 	@brief 	AF 2 selection
 */
#define GPIO_AF2_TIM3          	((uint8_t)0x02U)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4          	((uint8_t)0x02U)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM5         	((uint8_t)0x02U)  /* TIM5 Alternate Function mapping */
/**
 * 	@brief 	AF 3 selection
 */
#define GPIO_AF3_TIM8          	((uint8_t)0x03U)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF3_TIM9          	((uint8_t)0x03U)  /* TIM9 Alternate Function mapping  */
#define GPIO_AF3_TIM10         	((uint8_t)0x03U)  /* TIM10 Alternate Function mapping */
#define GPIO_AF3_TIM11         	((uint8_t)0x03U)  /* TIM11 Alternate Function mapping */
/**
 * 	@brief 	AF 4 selection
 */
#define GPIO_AF4_I2C1          	((uint8_t)0x04U)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          	((uint8_t)0x04U)  /* I2C2 Alternate Function mapping */
#define GPIO_AF4_I2C3          	((uint8_t)0x04U)  /* I2C3 Alternate Function mapping */
/**
 * 	@brief	AF 5 selection
 */
#define GPIO_AF5_SPI1          	((uint8_t)0x05U)  /* SPI1 Alternate Function mapping        */
#define GPIO_AF5_SPI2          	((uint8_t)0x05U)  /* SPI2/I2S2 Alternate Function mapping   */
#define GPIO_AF5_SPI3          	((uint8_t)0x05U)  /* SPI3/I2S3 Alternate Function mapping   */
#define GPIO_AF5_SPI4          	((uint8_t)0x05U)  /* SPI4 Alternate Function mapping        */
#define GPIO_AF5_SPI5          	((uint8_t)0x05U)  /* SPI5 Alternate Function mapping        */
#define GPIO_AF5_SPI6          	((uint8_t)0x05U)  /* SPI6 Alternate Function mapping        */
#define GPIO_AF5_I2S3ext       	((uint8_t)0x05U)  /* I2S3ext_SD Alternate Function mapping  */
/**
 *	@brief	AF 6 selection
 */
#define GPIO_AF6_SPI3          	((uint8_t)0x06U)  /* SPI3/I2S3 Alternate Function mapping  */
#define GPIO_AF6_I2S2ext       	((uint8_t)0x06U)  /* I2S2ext_SD Alternate Function mapping */
#define GPIO_AF6_SAI1          	((uint8_t)0x06U)  /* SAI1 Alternate Function mapping       */
/**
 * 	@brief	AF 7 selection
 */
#define GPIO_AF7_USART1        	((uint8_t)0x07U)  /* USART1 Alternate Function mapping     */
#define GPIO_AF7_USART2        	((uint8_t)0x07U)  /* USART2 Alternate Function mapping     */
#define GPIO_AF7_USART3        	((uint8_t)0x07U)  /* USART3 Alternate Function mapping     */
#define GPIO_AF7_I2S3ext       	((uint8_t)0x07U)  /* I2S3ext_SD Alternate Function mapping */
/**
 * 	@brief 	AF 8 selection
 */
#define GPIO_AF8_UART4         	((uint8_t)0x08U)  /* UART4 Alternate Function mapping  */
#define GPIO_AF8_UART5         	((uint8_t)0x08U)  /* UART5 Alternate Function mapping  */
#define GPIO_AF8_USART6        	((uint8_t)0x08U)  /* USART6 Alternate Function mapping */
#define GPIO_AF8_UART7         	((uint8_t)0x08U)  /* UART7 Alternate Function mapping  */
#define GPIO_AF8_UART8         	((uint8_t)0x08U)  /* UART8 Alternate Function mapping  */
/**
*	@brief	AF 9 selection
*/
#define GPIO_AF9_CAN1          	((uint8_t)0x09U)  /* CAN1 Alternate Function mapping    */
#define GPIO_AF9_CAN2          	((uint8_t)0x09U)  /* CAN2 Alternate Function mapping    */
#define GPIO_AF9_TIM12         	((uint8_t)0x09U)  /* TIM12 Alternate Function mapping   */
#define GPIO_AF9_TIM13        	((uint8_t)0x09U)  /* TIM13 Alternate Function mapping   */
#define GPIO_AF9_TIM14         	((uint8_t)0x09U)  /* TIM14 Alternate Function mapping   */
#define GPIO_AF9_LTDC          	((uint8_t)0x09U)  /* LCD-TFT Alternate Function mapping */
#define GPIO_AF9_QSPI          	((uint8_t)0x09U)  /* QSPI Alternate Function mapping    */
/**
*	@brief	AF 10 selection
*/
#define GPIO_AF10_OTG_FS  		((uint8_t)0x0AU)  /* OTG_FS Alternate Function mapping */
#define GPIO_AF10_OTG_HS     	((uint8_t)0x0AU)  /* OTG_HS Alternate Function mapping */
#define GPIO_AF10_QSPI        	((uint8_t)0x0AU)  /* QSPI Alternate Function mapping   */
/**
*	@brief 	AF 11 selection
*/
#define GPIO_AF11_ETH           ((uint8_t)0x0BU)  /* ETHERNET Alternate Function mapping */
/**
* 	@brief 	AF 12 selection
*/
#define GPIO_AF12_FMC           ((uint8_t)0x0CU)  /* FMC Alternate Function mapping                      */
#define GPIO_AF12_OTG_HS_FS     ((uint8_t)0x0CU)  /* OTG HS configured in FS, Alternate Function mapping */
#define GPIO_AF12_SDIO          ((uint8_t)0x0CU)  /* SDIO Alternate Function mapping                     */
/**
* 	@brief	AF 13 selection
*/
#define GPIO_AF13_DCMI          ((uint8_t)0x0DU)  /* DCMI Alternate Function mapping */
#define GPIO_AF13_DSI           ((uint8_t)0x0DU)  /* DSI Alternate Function mapping  */
/**
* 	@brief	AF 14 selection
*/
#define GPIO_AF14_LTDC     		((uint8_t)0x0EU)  /* LCD-TFT Alternate Function mapping */
/**
* 	@brief 	AF 15 selection
*/
#define GPIO_AF15_EVENTOUT    	((uint8_t)0x0FU)  /* EVENTOUT Alternate Function mapping */
/**
*	@brief 	GPIO pin state configurations
*/
typedef enum{
	GPIO_PIN_RESET 		= 0x00,
	GPIO_PIN_SET 		= 0x01,
}GPIO_PIN_STATE;
/**
*	@brief 	GPIO pin mode configurations
*/
typedef enum{
	GPIO_MODE_IN 		= 0x00,
	GPIO_MODE_OUTPUT 	= 0x01,
	GPIO_MODE_ALT 		= 0x02,
	GPIO_MODE_ANALOG 	= 0x03
}GPIO_MODE_CONF;
/**
 * @brief 	GPIO pin output type configurations
 */
typedef enum{
	GPIO_PUSH_PULL 		= 0x00,
	GPIO_OPEN_DRAIN 	= 0x01
}GPIO_OUTPUT_TYPE_CONF;
/**
 * @brief 	GPIO pin speed configurations
 */
typedef enum{
	GPIO_LOW_SPEED 		= 0x00,
	GPIO_MED_SPEED 		= 0x01,
	GPIO_HIGH_SPEED 	= 0x02,
	GPIO_VHIGH_SPEED 	= 0x03
}GPIO_SPEED_CONF;
/**
 * @brief 	GPIO pin pushup/pulldown configurations
 */
typedef enum{
	GPIO_NOPUSH_NOPULL 	= 0x00,
	GPIO_PULLUP 		= 0x01,
	GPIO_PULLDOWN 		= 0x02
}GPIO_PUSHPULL_CONF;
/**
 * @brief  	Gets port index for desired GPIO PORT
 * @param  	GPIOx: GPIO PORT for calculating port index
 * @retval 	Calculated port index for GPIOx
 */
uint16_t GPIO_GetPortIdx(GPIO_TypeDef*);
/**
 * @brief  	Enables clock for desired GPIO PORT
 * @param  	GPIOx: GPIO PORT for enabling its clock
 * @retval 	none
 */
void GPIO_PortClockEnable(GPIO_TypeDef*);
/**
 * @brief  	Disables clock for desired GPIO PORT
 * @param  	GPIOx: GPIO PORT for disabling its clock
 * @retval 	none
 */
void GPIO_PortClockDisable(GPIO_TypeDef*);
/**
 * @brief  	Initializes the pin for the desired port and settings
 * @param  	GPIOx: GPIO PORT for initializing its pins
 * @param  	GPIO_PIN: pin to be initialized
 * @param 	GPIO_MODE_CONF: pin mode
 * @param	GPIO_OUTPUT_TYPE_CONF: output mode
 * @param	GPIO_SPEED_CONF: pin speed
 * @param	GPIO_PUSHPULL_CONF: push-up/pull-down resistors
 * @retval 	none
 */
void GPIO_PinInit(GPIO_TypeDef*,uint16_t, GPIO_MODE_CONF, GPIO_OUTPUT_TYPE_CONF, GPIO_SPEED_CONF,GPIO_PUSHPULL_CONF);
/**
 * @brief  	Initializes the alternative function pin for the desired port and settings
 * @param  	GPIOx: GPIO PORT for initializing its pins
 * @param  	GPIO_PIN: pin to be initialized
 * @param 	GPIO_MODE_CONF: pin mode
 * @param	GPIO_OUTPUT_TYPE_CONF: output mode
 * @param	GPIO_SPEED_CONF: pin speed
 * @param	GPIO_PUSHPULL_CONF: push-up/pull-down resistors
 * @param	Alternate function selection
 * @retval 	none
 */
void GPIO_PinAltInit(GPIO_TypeDef*,uint16_t, GPIO_MODE_CONF, GPIO_OUTPUT_TYPE_CONF, GPIO_SPEED_CONF,GPIO_PUSHPULL_CONF, uint32_t);
/**
 * @brief  	De-initializes the pin for the desired port and settings
 * @param  	GPIOx: GPIO PORT for de-initializing its pins
 * @param  	GPIO_PIN: pin to be de-initialized
 * @retval 	none
 */
void GPIO_PinDeInit(GPIO_TypeDef*,uint16_t);
/**
 * @brief  	Initializes the port with settings
 * @param  	GPIOx: GPIO PORT for initializing
 * @param  	GPIO_PIN: pin(s) to be initialized
 * @param 	GPIO_MODE_CONF: pin mode
 * @param	GPIO_OUTPUT_TYPE_CONF: output mode
 * @param	GPIO_SPEED_CONF: pin speed
 * @param	GPIO_PUSHPULL_CONF: push-up/pull-down resistors
 * @retval 	none
 */
void GPIO_PortInit (GPIO_TypeDef*,uint16_t, GPIO_MODE_CONF, GPIO_OUTPUT_TYPE_CONF, GPIO_SPEED_CONF,GPIO_PUSHPULL_CONF);
/**
 * @brief  	Initializes the port with alternative function
 * @param  	GPIOx: GPIO PORT for initializing
 * @param  	GPIO_PIN: pin(s) to be initialized
 * @param 	GPIO_MODE_CONF: pin mode
 * @param	GPIO_OUTPUT_TYPE_CONF: output mode
 * @param	GPIO_SPEED_CONF: pin speed
 * @param	GPIO_PUSHPULL_CONF: push-up/pull-down resistors
 * @param	Alternate function selection
 * @retval 	none
 */
void GPIO_PortAltInit(GPIO_TypeDef*,uint16_t,GPIO_MODE_CONF,GPIO_OUTPUT_TYPE_CONF,GPIO_SPEED_CONF,GPIO_PUSHPULL_CONF,uint32_t);
/**
 * @brief  	De-initializes the port
 * @param  	GPIOx: GPIO PORT for de-initializing
 * @param  	GPIO_PIN: pin(s) to be de-initialized
 * @retval 	none
 */
void GPIO_PortDeInit(GPIO_TypeDef*, uint16_t);
/**
 * @brief  	Read the value of a pin
 * @param  	GPIOx: GPIO PORT for reading its pin
 * @param  	GPIO_PIN: pin(s) to be read
 * @retval 	none
 */
GPIO_PIN_STATE GPIO_ReadPin(GPIO_TypeDef*, uint16_t);
/**
 * @brief  	Write the value desired value to a pin
 * @param  	GPIOx: GPIO PORT for writing to its pin
 * @param  	GPIO_PIN: pin(s) to write on
 * @param 	GPIO_PIN_STATE: set or reset the pin
 * @retval 	none
 */
void GPIO_WritePin(GPIO_TypeDef*, uint16_t, GPIO_PIN_STATE);
/**
 * @brief  	Toggle the desired pin
 * @param  	GPIOx: GPIO PORT for toggle to its pin
 * @param  	GPIO_PIN: pin(s) to toggle
 * @retval 	none
*/
void GPIO_TogglePin(GPIO_TypeDef*, uint16_t);

#endif /* __GPIO_H__ */
