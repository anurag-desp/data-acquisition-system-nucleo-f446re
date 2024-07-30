#include <stdint.h>
#include "pll.h"
#include "gpio.h"


int main (void) {

	clockSpeed_PLL();
	SysTick_Init();

	GPIOx_init(PA);
	GPIOx_config_mode(PA5, MODER_OUTPUT);
	GPIOx_config_mode(PA5, OSPEEDR_HIGH);

	for(;;) {
		GPIOx_set_odr(PA5);
		delay_ms(500);
		GPIOx_reset_odr(PA5);
		delay_ms(500);
	}

	return 0;
}

