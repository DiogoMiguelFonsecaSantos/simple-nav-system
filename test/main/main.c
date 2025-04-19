#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"


void app_main(void)
{	
	gpio_reset_pin(12);
    gpio_dump_io_configuration(stdout, (1ULL << 12));

    while (true) {
        printf("Hello from app_main!\n");
        sleep(5);
    }
}
