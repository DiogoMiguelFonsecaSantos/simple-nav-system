

#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BOOTDELAY_MS      5000
#define DELAY_MS          50
#define GPIO_LED          26
#define GPIO_BLUE         12
#define LED               22
#define RED               26 

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read(); // Declaração correta da função
#ifdef __cplusplus
}
#endif

void app_main() {
    while (1) {
        // Obtém a temperatura interna do ESP32
        uint8_t temp_f = temprature_sens_read();
        float temp_c = (temp_f - 32) / 1.8;

        // Exibe a temperatura no terminal
        printf("Temperature: %.2f C\n", temp_c);

        vTaskDelay(pdMS_TO_TICKS(5000)); // Aguarda 5 segundos
    }
}

