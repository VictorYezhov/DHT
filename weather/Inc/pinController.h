

#include "gpio.h"
typedef enum {OUTPUT = 0, INPUT = 1} PinOptions;



class PinController{

public:
	void setPinToMode(GPIO_TypeDef *port, uint16_t  pin,PinOptions option);
};
