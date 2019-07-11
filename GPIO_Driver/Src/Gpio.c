#include "Gpio.h"


uint16_t GPIO_GetPortIdx(GPIO_TypeDef* InPort){
	return ((uint32_t)InPort - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE));
}
void GPIO_PortClockEnable(GPIO_TypeDef* InPort){
	SETBIT(RCC->AHB1ENR, GPIO_GetPortIdx(InPort));
}
void GPIO_PortClockDisable(GPIO_TypeDef* InPort){
	RESETBIT(RCC->AHB1ENR, GPIO_GetPortIdx(InPort));
}
void GPIO_PinInit(GPIO_TypeDef* InPort,uint16_t InPin, GPIO_MODE_CONF InModeConf, GPIO_OUTPUT_TYPE_CONF InOutModeConf, GPIO_SPEED_CONF InSpeedConf ,GPIO_PUSHPULL_CONF InPushPullConf){
	uint32_t LocalIter;
	uint32_t CheckPosition = 0;
	uint32_t CurrPosition= 0;
	uint32_t TempReg =0x00;
	for(LocalIter = 0U; LocalIter<GPIO_PINS_NUM;LocalIter++){
		CheckPosition = ((uint32_t)1U)<<LocalIter;
		CurrPosition = (uint32_t)InPin & CheckPosition;
		if(CurrPosition == CheckPosition){
			/* 7.4.1- GPIOx_MODER REG */
			TempReg = InPort->MODER;
			RESETBIT_N(TempReg, LocalIter*2,0b11);
			SETBIT_N(TempReg, LocalIter*2, InModeConf);
			InPort->MODER = TempReg;

			/* 7.4.2- GPIOx_OTYPER REG */
			if((InModeConf == GPIO_MODE_OUTPUT) || (InModeConf == GPIO_MODE_ALT)){
				TempReg = InPort->OTYPER;
				RESETBIT(TempReg, LocalIter);
				SETBIT_N(TempReg, LocalIter,InOutModeConf);
				InPort->OTYPER = TempReg;

			/* 7.4.3- GPIOx_OSPEEDR REG */
				TempReg = InPort->OSPEEDR;
				RESETBIT_N(TempReg, LocalIter*2,0b11);
				SETBIT_N(TempReg, LocalIter*2, InSpeedConf);
				InPort->OSPEEDR = TempReg;
			}
			/* 7.4.4- GPIOx_PUPDR REG */
			TempReg = InPort->PUPDR;
			RESETBIT_N(TempReg, LocalIter*2,0b11);
			SETBIT_N(TempReg, LocalIter*2, InPushPullConf);
			InPort->PUPDR = TempReg;
		}
	}
}
void GPIO_PinAltInit(GPIO_TypeDef* InPort,uint16_t InPin, GPIO_MODE_CONF InModeConf, GPIO_OUTPUT_TYPE_CONF InOutModeConf, GPIO_SPEED_CONF InSpeedConf ,GPIO_PUSHPULL_CONF InPushPullConf, uint32_t InAltenate){
	uint32_t LocalIter;
	uint32_t CheckPosition = 0;
	uint32_t CurrPosition= 0;
	uint32_t TempReg =0x00;
	uint32_t ShiftBits = 0x00;
	for(LocalIter = 0U; LocalIter<GPIO_PINS_NUM;LocalIter++){
		CheckPosition = ((uint32_t)1U)<<LocalIter;
		CurrPosition = (uint32_t)InPin & CheckPosition;
		if(CurrPosition == CheckPosition){
			/* 7.4.1- GPIOx_MODER REG */
			TempReg = InPort->MODER;
			RESETBIT_N(TempReg, LocalIter*2,0b11);
			SETBIT_N(TempReg, LocalIter*2, InModeConf);
			InPort->MODER = TempReg;

			/* 7.4.2- GPIOx_OTYPER REG */
			if((InModeConf == GPIO_MODE_OUTPUT) || (InModeConf == GPIO_MODE_ALT)){
				TempReg = InPort->OTYPER;
				RESETBIT(TempReg, LocalIter);
				SETBIT_N(TempReg, LocalIter,InOutModeConf);
				InPort->OTYPER = TempReg;

			/* 7.4.3- GPIOx_OSPEEDR REG */
				TempReg = InPort->OSPEEDR;
				RESETBIT_N(TempReg, LocalIter*2,0b11);
				SETBIT_N(TempReg, LocalIter*2, InSpeedConf);
				InPort->OSPEEDR = TempReg;
			}
			/* 7.4.4- GPIOx_PUPDR REG */
			TempReg = InPort->PUPDR;
			RESETBIT_N(TempReg, LocalIter*2,0b11);
			SETBIT_N(TempReg, LocalIter*2, InPushPullConf);
			InPort->PUPDR = TempReg;

			/* 7.4.9- GPIOx_AFRL REG */
			/* 7.4.10- GPIOx_AFRH_REG */
			TempReg = InPort->AFR[LocalIter>>3];
			ShiftBits =  (uint32_t)(LocalIter & 0x07)*4;
			RESETBIT_N(TempReg,ShiftBits,0x0F);
			SETBIT_N(TempReg,ShiftBits, InAltenate);
			InPort->AFR[LocalIter>>3] = TempReg;
		}
	}
}
void GPIO_PinDeInit(GPIO_TypeDef* InPort,uint16_t InPin){
	uint32_t LocalIter;
	uint32_t CheckPosition = 0;
	uint32_t CurrPosition= 0;
	uint32_t TempReg =0x00;
	uint32_t ShiftBits =0x00;
	for(LocalIter = 0U; LocalIter<GPIO_PINS_NUM;LocalIter++){
		CheckPosition = ((uint32_t)1U)<<LocalIter;
		CurrPosition = (uint32_t)InPin & CheckPosition;
		if(CurrPosition == CheckPosition){
			/* 7.4.1- GPIOx_MODER REG */
			RESETBIT_N(InPort->MODER, LocalIter*2,0b11);

			/* 7.4.2- GPIOx_OTYPER REG */
			RESETBIT(InPort->OTYPER, LocalIter);

			/* 7.4.3- GPIOx_OSPEEDR REG */
			RESETBIT_N(InPort->OSPEEDR, LocalIter*2,0b11);

			/* 7.4.4- GPIOx_PUPDR REG */
			RESETBIT_N(InPort->PUPDR, LocalIter*2,0b11);

			/* 7.4.9- GPIOx_AFRL REG */
			/* 7.4.10- GPIOx_AFRH_REG */
			ShiftBits =  (uint32_t)(LocalIter & 0x07)*4;
			RESETBIT_N(InPort->AFR[LocalIter>>3],ShiftBits,0x0F);
		}
	}
}
void GPIO_PortInit(GPIO_TypeDef* InPort,uint16_t InPin, GPIO_MODE_CONF InModeConf, GPIO_OUTPUT_TYPE_CONF InOutModeConf, GPIO_SPEED_CONF InSpeedConf,GPIO_PUSHPULL_CONF InPushPullConf){
	GPIO_PortClockEnable(InPort);
	GPIO_PinInit(InPort,InPin,InModeConf,InOutModeConf,InSpeedConf,InPushPullConf);
}
void GPIO_PortAltInit(GPIO_TypeDef* InPort,uint16_t InPin, GPIO_MODE_CONF InModeConf, GPIO_OUTPUT_TYPE_CONF InOutModeConf, GPIO_SPEED_CONF InSpeedConf ,GPIO_PUSHPULL_CONF InPushPullConf, uint32_t InAltenate){
	GPIO_PortClockEnable(InPort);
	GPIO_PinAltInit(InPort,InPin,InModeConf,InOutModeConf,InSpeedConf,InPushPullConf, InAltenate);
}
void GPIO_PortDeInit(GPIO_TypeDef* InPort, uint16_t InPin){
	GPIO_PortClockDisable(InPort);
	GPIO_PinDeInit(InPort,InPin);
}
GPIO_PIN_STATE GPIO_ReadPin(GPIO_TypeDef* InPort, uint16_t InPin){
	if (READBIT(InPort->IDR, InPin) != GPIO_PIN_RESET)
		return GPIO_PIN_SET;
	else
		return GPIO_PIN_RESET;
}
void GPIO_WritePin(GPIO_TypeDef* InPort, uint16_t InPin, GPIO_PIN_STATE InState){
	if(InState != GPIO_PIN_RESET)
		InPort->BSRR = InPin;
	else
		InPort->BSRR = InPin<<16U;
}
void GPIO_TogglePin(GPIO_TypeDef* InPort, uint16_t InPin){
	InPort->ODR ^= InPin;
}
