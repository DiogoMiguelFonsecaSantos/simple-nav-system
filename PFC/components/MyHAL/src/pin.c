/*
 * pin.c
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#include "pin.h"
#include "driver/gpio.h"
#include "hal/aes_hal.h"
#include <sys/_stdint.h>
	
#define LED_BLUE 12
#define LED_GREEN 14
#define LED_RED 26
#define LED_YELLOW 27

/*the gpio config can also put open drain mode but ill do it on pinconfig*/
void PIN_SetDirection(uint8_t pin, PIN_Direction direction) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << pin),
        .mode = (direction == OUTPUT) ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

//place pin number or gpio num is the same thing
void PIN_SetLevel(uint8_t pin, uint32_t level) {
    gpio_set_level(pin, level);
}

void PIN_Clear(uint8_t pin){
	PIN_SetLevel(pin, 0);
}

void PIN_Set(uint8_t pin){
	PIN_SetLevel(pin, 1);
}

int PIN_GetLevel(uint8_t pin) {
    return gpio_get_level(pin);
}   

void PIN_ToggleLevel(uint8_t pin){
	printf("%d\n\n", PIN_GetLevel(pin));
	if(PIN_GetLevel(pin)){
		PIN_Clear(pin);
	}
	else{
		PIN_Set(pin);
	}
}


