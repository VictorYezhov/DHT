#include "pinController.h"


void PinController::setPinToMode(GPIO_TypeDef *port, uint16_t  pin,PinOptions option){
	         GPIO_InitTypeDef GPIO_InitStruct;
		 	GPIO_InitStruct.Pin  = pin;
		 	if(option==OUTPUT)
		 		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
		 	else
		 		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		 	GPIO_InitStruct.Pull = GPIO_NOPULL;
		 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		 	HAL_GPIO_Init(port, &GPIO_InitStruct);
}
